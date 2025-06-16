#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdexcept>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>

//#define MAX_LINE_INPUT 1024
//#define MAX_LOCAL_BUFFER 100

using namespace std;

void generateHeader(ostream& glueVars) {
    glueVars << "//-----------------------------------------------------------------------------\n";
    glueVars << "// Автоматически сгенерированный файл связывания переменных\n";
    glueVars << "//-----------------------------------------------------------------------------\n\n";
    glueVars << "#include \"iec_std_lib.h\"\n";
    glueVars << "#include \"global.h\"\n\n";
    glueVars << "#define __LOCATED_VAR(type, name, ...) type __##name;\n";
    glueVars << "#include \"LOCATED_VARIABLES.h\"\n";
    glueVars << "#undef __LOCATED_VAR\n\n";
    glueVars << "#define __LOCATED_VAR(type, name, ...) type* name = &__##name;\n";
    glueVars << "#include \"LOCATED_VARIABLES.h\"\n";
    glueVars << "#undef __LOCATED_VAR\n\n";
    glueVars << "#define __BIND(reg, var, type) Binder::instance().bind(reg, (void*) var, type)\n\n";
    glueVars << "void glueVars() {\n";
}

void generateBottom(ostream& glueVars) {
    glueVars << "}\n";
}

std::string extract_brackets_content(const std::string& input) {
    size_t start = input.find('(');
    size_t end = input.rfind(')');

    if (start == std::string::npos || end == std::string::npos || end <= start) {
        throw std::invalid_argument("Invalid input format - no matching brackets found");
    }

    // +1 to skip '(', end-start-1 to exclude ')'
    return input.substr(start + 1, end - start - 1);
}

class PLCVariableParser {
    std::vector<std::string> parts;

    void parse_input(const std::string& input) {
        // Очищаем предыдущие результаты
        parts.clear();

        // Разбиваем строку на части по запятым
        std::istringstream iss(input);
        std::string part;

        while (std::getline(iss, part, ',')) {
            // Удаляем пробелы и лишние подчеркивания
            part.erase(0, part.find_first_not_of(" _\t"));
            part.erase(part.find_last_not_of(" _\t") + 1);
            parts.push_back(part);
        }
    }

    std::string get_plc_type() const {
        if (parts.empty()) throw std::invalid_argument("Empty input string");
        return parts[0];
    }

    std::string get_plc_var() const {
        if (parts.size() < 2) throw std::invalid_argument("Input must contain at least 2 parameters");
        return parts[1];
    }

    std::string get_plc_address() const {
        static const char* const category_prefixes = "IQMS";
        static const char* const type_prefixes = "XBWDLRF";

        if (parts.size() < 4) {
            throw std::invalid_argument("Invalid input format - not enough parameters");
        }

        // Проверяем что 2-й и 3-й параметры - один символ
        if (parts[2].length() != 1 || parts[3].length() != 1) {
            throw std::invalid_argument("Second and third parameters must be single characters");
        }

        // Проверяем допустимость символов
        char category = parts[2][0];
        char type = parts[3][0];

        if (strchr(category_prefixes, category) == nullptr) {
            throw std::invalid_argument(std::string("Invalid category prefix '") + category +
                                        "' (allowed: I, Q, M, S)");
        }

        if (strchr(type_prefixes, type) == nullptr) {
            throw std::invalid_argument(std::string("Invalid type prefix '") + type +
                                        "' (allowed: X, B, W, D, L, R, F)");
        }

        // Проверяем наличие 4-го параметра (номера)
        if (parts[4].empty()) {
            throw std::invalid_argument("Register number cannot be empty");
        }

        // Проверяем что номер регистра состоит из цифр
        if (!std::all_of(parts[4].begin(), parts[4].end(), ::isdigit)) {
            throw std::invalid_argument("Register number must contain only digits");
        }

        // Собираем основную часть адреса
        std::string result = parts[2] + parts[3] + parts[4];

        // Обработка битового смещения
        if (type == 'X') {
            if (parts.size() > 5 && !parts[5].empty()) {
                // Проверяем что бит - число в диапазоне 0..63
                try {
                    int bit_offset = std::stoi(parts[5]);
                    if (bit_offset < 0 || bit_offset > 63) {
                        throw std::invalid_argument("Bit offset must be in range 0..63");
                    }
                    result += "." + parts[5];
                } catch (...) {
                    throw std::invalid_argument("Bit offset must be a valid number");
                }
            } else {
                result += ".0";
            }
        } else if (parts.size() > 5 && !parts[5].empty()) {
            throw std::invalid_argument("Bit offset is only allowed for 'X' type addresses");
        }

        return result;
    }

public:
    std::string parse(const std::string& input) {
        parse_input(input);

        std::string addr = get_plc_address();
        std::string var  = get_plc_var();
        std::string type = get_plc_type();

        return "\"" + addr + "\", __" + var + ", PLC_" + type;
    }
};

void generateBody(istream& locatedVars, ostream& glueVars) {
    PLCVariableParser parser;
    string line;
    while (getline(locatedVars, line)) {
        try {
            string input = extract_brackets_content(line);
            glueVars << "\t__BIND(" << parser.parse(input) << ");\n";
        } catch(...) {}
    }
}

/// This is our main function. We define it with a different name and then
/// call it from the main function so that we can mock it for the purpose
/// of testing.
int mainImpl(int argc, char *argv[])
{
    // Parse the command line arguments - if they exist. Show the help if there are too many arguments
    // or if the first argument is for help.
    bool show_help = argc >= 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0);
    if (show_help || (argc != 1 && argc != 3)) {
        cout << "Usage " << endl << endl;
        cout << "  glue_generator [options] <path-to-located-variables.h> <path-to-glue-vars.cpp>" << endl << endl;
        cout << "Reads the LOCATED_VARIABLES.h file generated by the MATIEC compiler and produces" << endl;
        cout << "glueVars.cpp for the OpenPLC runtime. If not specified, paths are relative to" << endl;
        cout << "the current directory." << endl << endl;
        cout << "Options" << endl;
        cout << "  --help,-h   = Print usage information and exit." << endl;
        return 0;
    }

    // If we have 3 arguments, then the user provided input and output paths
    string input_file_name("LOCATED_VARIABLES.h");
    string output_file_name("glueVars.cpp");
    if (argc == 3) {
        input_file_name = argv[1];
        output_file_name = argv[2];
    }

    // Try to open the files for reading and writing.
    ifstream locatedVars(input_file_name, ios::in);
    if (!locatedVars.is_open()) {
        cout << "Error opening located variables file at " << input_file_name << endl;
        return 1;
    }
    ofstream glueVars(output_file_name, ios::trunc);
    if (!glueVars.is_open()) {
        cout << "Error opening glue variables file at " << output_file_name << endl;
        return 2;
    }

    generateHeader(glueVars);
    generateBody(locatedVars, glueVars);
    generateBottom(glueVars);

    return 0;
}

// For testing, we need to allow omitting the main function defined here.
#ifndef OPLCGLUE_OMIT_MAIN
int main(int argc, char *argv[]) {
    return mainImpl(argc, argv);
}
#endif // OPLCGLUE_OMIT_MAIN


//int main(int argc, char* argv[]) {
//    if (argc != 3) {
//        cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
//        return 1;
//    }
//
//    ifstream locatedVars(argv[1]);
//    if (!locatedVars.is_open()) {
//        cerr << "Error opening input file: " << argv[1] << endl;
//        return 1;
//    }
//
//    ofstream glueVars(argv[2]);
//    if (!glueVars.is_open()) {
//        cerr << "Error opening output file: " << argv[2] << endl;
//        return 1;
//    }
//
//    generateHeader(glueVars);
//    generateBody(locatedVars, glueVars);
//    generateBottom(glueVars);
//
//    return 0;
//}
