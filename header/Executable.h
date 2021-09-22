#ifndef __EXECUTABLE_H__
#define __EXECUTABLE_H__

#include "Test.h"
#include "Command.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

class Executable : public Command {
public:

	vector<string> toExecute;

	Executable() {execPassed = true; }

	Executable(string input)
	{
		char* cstr = new char[input.size() + 1];
		strcpy(cstr, input.c_str());
		char* token = strtok(cstr, " ");
		execPassed = true;

		while (token != NULL)
		{
			toExecute.push_back(token);
			token = strtok(NULL, " ");
		}
	}

	int execute()
	{
		if (toExecute.at(0) == "exit")
		{
			exit(0);
		}
		if (toExecute.at(0) == "test" || toExecute.at(0) == "[")
		{
			Test* leaf = new Test(toExecute);
			leaf->execute();
			if(leaf->execPassed) { this->execPassed = true; }
			else { this->execPassed = false; }
			return 1;
		}
		pid_t c_pid, pid;
		int status;

		c_pid = fork();

		if (c_pid == 0)
		{
			char* arg[toExecute.size() + 1];

			for (int i = 0; i < toExecute.size(); i++)
			{
				arg[i] = const_cast<char*>(toExecute.at(i).c_str());
			}
			arg[toExecute.size()] = NULL;

			if (execvp(*arg, arg) < 0)
			{
				perror("execvp() failed");
				execPassed = false;
				exit(1);
			}
			exit(0);
		}
		else if (c_pid > 0)
		{
			pid = waitpid(c_pid, &status, 0);
			if (status != 0)
			{
				//perror("Child failed");
				execPassed = false;
			}
		}
		else
		{
			perror("fork() failed");
			execPassed = false;
		}
		return 1;
	}
	bool getExecPassed(){return this->execPassed;}
	bool isConnector()
	{
		return false;
	}

};

#endif
