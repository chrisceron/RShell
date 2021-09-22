#ifndef __TEST_H__
#define __TEST_H__

#include "Command.h"

#include <string>
#include <string.h>
#include <sys/stat.h>
#include <vector>

using namespace std;

class Test : public Command {
public:
	
	vector<string> toExecute;

	Test() { execPassed = false; }

	Test(string input){
		char* cstr = new char[input.size() + 1];
		strcpy(cstr, input.c_str());
		char* token = strtok(cstr, " ");
		execPassed = false;

		while (token != NULL)
		{
			toExecute.push_back(token);
			token = strtok(NULL, " ");
		}
	}

	Test(vector<string> toExec) {
		toExecute = toExec;
	}
		
	int execute() {
		struct stat buf;
		int i = 0;

		if (toExecute.at(i) == "[") i++;
		
		if(toExecute.at(i) == "test") i++;

		if (toExecute.at(i).size() == 2 && toExecute.at(i).at(0) == '-') //next element is a flag
		{
			execPassed = (stat(toExecute.at(i+1).c_str(), &buf) == 0);

			if (toExecute.at(i) == "-e")
			{
				if (execPassed)
					cout << "(true)" << endl;
				else cout << "(false)" << endl;
			}
			else if (toExecute.at(i) == "-d")
			{
				execPassed = S_ISDIR(buf.st_mode);
				if(execPassed)
					cout << "(true)" << endl;
				else cout << "(false)" << endl;
			}
			else if (toExecute.at(i) == "-f")
			{
				execPassed = S_ISREG(buf.st_mode); 
				if(execPassed)
                                        cout << "(true)" << endl;
                                else cout << "(false)" << endl;

			}
			else std::cout << "Error. Invalid flag" << std::endl;
		}

		else {															//next element is the path
			execPassed = (stat(toExecute.at(i).c_str(), &buf) == 0);
                        if (execPassed)
                        	cout <<  "(true)" << endl;
                        else cout << "(false)" << endl;
		}


		return 1;
	}

	bool isConnector()
	{
		return true;
	}

};

#endif
