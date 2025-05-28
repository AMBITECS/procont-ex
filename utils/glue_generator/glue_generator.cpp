#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>

#define MAX_LINE_INPUT 1024
#define MAX_LOCAL_BUFFER 100

using namespace std;

void generateHeader(ostream& glueVars) {
    glueVars << "//-----------------------------------------------------------------------------\n";
    glueVars << "// Автоматически сгенерированный файл связывания переменных\n";
    glueVars << "//-----------------------------------------------------------------------------\n\n";
    glueVars << "#include \"iec_std_lib.h\"\n";
    glueVars << "#include \"gateway.h\"\n\n";
    glueVars << "#define __LOCATED_VAR(type, name, ...) type __##name;\n";
    glueVars << "#include \"LOCATED_VARIABLES.h\"\n";
    glueVars << "#undef __LOCATED_VAR\n\n";
    glueVars << "#define __BIND(reg, var) BindingManager::instance().bind(reg, (void*)##var)\n\n";
    glueVars << "void glueVars() {\n";
}

void generateBottom(ostream& glueVars) {
    glueVars << "}\n";
}

void findPositions(char* varName, int* pos1, int* pos2) {
    int i = 4, j = 0;
    char tempBuffer[100];

    while (varName[i] != '_' && varName[i] != '\0') {
        tempBuffer[j] = varName[i];
        i++; j++;
        tempBuffer[j] = '\0';
    }
    *pos1 = atoi(tempBuffer);

    if (varName[i] == '\0') {
        *pos2 = 0;
        return;
    }

    j = 0; i++;
    while (varName[i] != '\0') {
        tempBuffer[j] = varName[i];
        i++; j++;
        tempBuffer[j] = '\0';
    }
    *pos2 = atoi(tempBuffer);
}

string getRegisterNotation(char* varName) {
    int pos1, pos2;
    findPositions(varName, &pos1, &pos2);

    char category = varName[2];
    char type = varName[3];

    string reg;
    reg += category;
    reg += type;

    if (type == 'X') {
        reg += to_string(pos1) + "." + to_string(pos2);
    } else {
        reg += to_string(pos1);
    }

    return reg;
}

void glueVar(ostream& glueVars, char* varName, char* varType) {
    string reg = getRegisterNotation(varName);
    string var = varName;

    glueVars << "\t__BIND(\"" << reg << "\", " << var << ");\n";
}

int parseIecVars(istream& locatedVars, char* varName, char* varType) {
    string line;
    char buffer[MAX_LINE_INPUT];

    if (getline(locatedVars, line)) {
        int i = 0, j = 0;
        strncpy(buffer, line.c_str(), MAX_LINE_INPUT);

        for (i = 0; i < MAX_LINE_INPUT && buffer[i] != '('; i++);
        i++;

        j = 0;
        while (i < MAX_LINE_INPUT && buffer[i] != ',') {
            if (j < MAX_LOCAL_BUFFER) {
                varType[j] = buffer[i];
                i++; j++;
                varType[j] = '\0';
            }
        }
        i++;

        j = 0;
        while (i < MAX_LINE_INPUT && buffer[i] != ',') {
            if (j < MAX_LOCAL_BUFFER) {
                varName[j] = buffer[i];
                i++; j++;
                varName[j] = '\0';
            }
        }

        return 1;
    }
    return 0;
}

void generateBody(istream& locatedVars, ostream& glueVars) {
    char iecVar_name[MAX_LOCAL_BUFFER];
    char iecVar_type[MAX_LOCAL_BUFFER];

    while (parseIecVars(locatedVars, iecVar_name, iecVar_type)) {
        glueVar(glueVars, iecVar_name, iecVar_type);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }

    ifstream locatedVars(argv[1]);
    if (!locatedVars.is_open()) {
        cerr << "Error opening input file: " << argv[1] << endl;
        return 1;
    }

    ofstream glueVars(argv[2]);
    if (!glueVars.is_open()) {
        cerr << "Error opening output file: " << argv[2] << endl;
        return 1;
    }

    generateHeader(glueVars);
    generateBody(locatedVars, glueVars);
    generateBottom(glueVars);

    return 0;
}
