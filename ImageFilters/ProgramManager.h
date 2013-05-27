#ifndef PROGRAM_MANAGER_H
#define PROGRAM_MANAGER_H

#include <map>
#include <algorithm>
#include <string>
#include <fstream>

#include "base.h"

using namespace std;

class ProgramManager
{
	protected:
		map<string, int> programHash;
		static GLchar* FileToString(ifstream*);
		static ProgramManager* instance;
	public:
		ProgramManager();
		static ProgramManager* GetProgramManager();
		void AddProgram(string, int); //associate string with id
		int CreateProgram(string = "", string = "", string = ""); //returns the id of the newly created program
		int GetProgram(string);
};

#endif