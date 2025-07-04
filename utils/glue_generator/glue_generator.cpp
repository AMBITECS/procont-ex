#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>

#define MAX_LINE_INPUT 1024
#define MAX_LOCAL_BUFFER 100

using namespace std;

/// Write the header to the output stream.
/// The header is common among all glueVars files.
/// @param glueVars The output stream to write to.
void generateHeader(ostream& glueVars)
{
/*
//Booleans
extern IEC_BOOL *IX[][8];
extern IEC_BOOL *QX[][8];

//Bytes
extern IEC_BYTE *IB[];
extern IEC_BYTE *QB[];

//Analog I/O
extern IEC_UINT *IW[];
extern IEC_UINT *QW[];

//32bit I/O
extern IEC_UDINT *ID[];
extern IEC_UDINT *QD[];

//64bit I/O
extern IEC_ULINT *IL[];
extern IEC_ULINT *QL[];

//Memory
extern IEC_UINT *MW[];
extern IEC_UDINT *MD[];
extern IEC_ULINT *ML[];
 */
	glueVars << 	"\
//-----------------------------------------------------------------------------\r\n\
// Copyright 2018 Ambitecs\r\n\
//-----------------------------------------------------------------------------\r\n\
// This file is responsible for gluing the variables\r\n\
// from the IEC program to the Procont memory pointers.\r\n\
// It is automatically generated. PLEASE DON'T EDIT THIS FILE!\r\n\
//-----------------------------------------------------------------------------\r\n\
\r\n\
#include \"iec_std_lib.h\"\r\n\
#include \"gateway.h\"\r\n\
\r\n\
\r\n\
#define __LOCATED_VAR(type, name, ...) type __##name;\r\n\
#include \"LOCATED_VARIABLES.h\"\r\n\
#undef __LOCATED_VAR\r\n\
#define __LOCATED_VAR(type, name, ...) type* name = &__##name;\r\n\
#include \"LOCATED_VARIABLES.h\"\r\n\
#undef __LOCATED_VAR\r\n\
\r\n\
void glueVars()\r\n\
{\r\n";
}

int parseIecVars(istream& locatedVars, char *varName, char *varType)
{
	string line;
	char buffer[MAX_LINE_INPUT];

	if (getline(locatedVars, line))
	{
		int i = 0, j = 0;
		strncpy(buffer, line.c_str(), MAX_LINE_INPUT);
		for (i = 0; i < MAX_LINE_INPUT && buffer[i] != '('; i++);
		i++;

		while (i < MAX_LINE_INPUT && buffer[i] != ',')
		{
			if(j < MAX_LOCAL_BUFFER)
			{
				varType[j] = buffer[i];
				i++; j++;
				varType[j] = '\0';
			}
		}
		i++; j=0;

		while (i < MAX_LINE_INPUT && buffer[i] != ',')
		{
			if(j < MAX_LOCAL_BUFFER)
			{
				varName[j] = buffer[i];
				i++; j++;
				varName[j] = '\0';
			}
		}

		return 1;
	}
	else
	{
		return 0;
	}
}

void findPositions(char *varName, int *pos1, int *pos2)
{
	int i=4, j=0;
	char tempBuffer[100];

	while (varName[i] != '_' && varName[i] != '\0')
	{
		tempBuffer[j] = varName[i];
		i++; j++;
		tempBuffer[j] = '\0';
	}
	*pos1 = atoi(tempBuffer);

	if (varName[i] == '\0')
	{
		*pos2 = 0;
		return;
	}

	j = 0; i++;

	while (varName[i] != '\0')
	{
		tempBuffer[j] = varName[i];
		i++; j++;
		tempBuffer[j] = '\0';
	}
	*pos2 = atoi(tempBuffer);
}

void glueVar(ostream& glueVars, char *varName, char *varType)
{
	cout << "varName: " << varName << "\tvarType: " << varType << endl;
	int pos1, pos2;

	findPositions(varName, &pos1, &pos2);

	if (pos2 >= 8)
	{
		cout << "***Invalid addressing on located variable" << varName << "***" << endl;
	}

	if (varName[2] == 'I')
	{
		//INPUT
		switch (varName[3])
		{
			case 'X':
				glueVars << "\tIX[" << pos1 << "][" << pos2 << "] = (IEC_BOOL *)" << varName << ";\r\n";
				break;
			case 'B':
				glueVars << "\tIB[" << pos1 << "] = (IEC_BYTE *)" << varName << ";\r\n";
				break;
			case 'W':
				glueVars << "\tIW[" << pos1 << "] = (IEC_UINT *)" << varName << ";\r\n";
				break;
			case 'D':
				glueVars << "\tID[" << pos1 << "] = (IEC_UDINT *)" << varName << ";\r\n";
				break;
			case 'L':
				glueVars << "\tIL[" << pos1 << "] = (IEC_ULINT *)" << varName << ";\r\n";
				break;
		}
	}
	else if (varName[2] == 'Q')
	{
		//OUTPUT
		switch (varName[3])
		{
			case 'X':
				glueVars << "\tQX[" << pos1 << "][" << pos2 << "] = (IEC_BOOL *)" << varName << ";\r\n";
				break;
           	case 'B':
				glueVars << "\tQB[" << pos1 << "] = (IEC_BYTE *)" << varName << ";\r\n";
				break;
			case 'W':
				glueVars << "\tQW[" << pos1 << "] = (IEC_UINT *)" << varName << ";\r\n";
				break;
			case 'D':
				glueVars << "\tQD[" << pos1 << "] = (IEC_UDINT *)" << varName << ";\r\n";
				break;
			case 'L':
				glueVars << "\tQL[" << pos1 << "] = (IEC_ULINT *)" << varName << ";\r\n";
				break;
		}
	}
	else if (varName[2] == 'M')
	{
		//MEMORY
		switch (varName[3])
		{
			case 'W':
				glueVars << "\tMW[" << pos1 << "] = (IEC_UINT *)" << varName << ";\r\n";
				break;
			case 'D':
				glueVars << "\tMD[" << pos1 << "] = (IEC_UDINT *)" << varName << ";\r\n";
				break;
			case 'L':
				if (pos1 > 1023)
					glueVars << "\tspecial_functions[" << (pos1-1024) << "] = (IEC_ULINT *)" << varName << ";\r\n";
				else
					glueVars << "\tML[" << pos1 << "] = (IEC_ULINT *)" << varName << ";\r\n";
				break;
		}
	}
}

void generateBottom(ostream& glueVars)
{
	glueVars << "}\r\n";
}

void generateBody(istream& locatedVars, ostream& glueVars) {
    // Start the generation process.
    char iecVar_name[100];
    char iecVar_type[100];

    while (parseIecVars(locatedVars, iecVar_name, iecVar_type))
    {
        glueVar(glueVars, iecVar_name, iecVar_type);
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
