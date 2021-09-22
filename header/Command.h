#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <iostream>
#include <string>
#include <string.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

class Command { //virtual function that won't get instantiated
public:
	Command* left;
	Command* right;
	bool execPassed;
	Command() { }
	void set(Command* left, Command* right)
	{
		this->left = left;
		this->right = right;
	}
	virtual int execute() = 0;
	virtual bool isConnector() = 0;
	virtual bool getExecPassed() { return execPassed; }
	virtual void setExecPassed(bool exec) { execPassed = exec; }
};

#endif
