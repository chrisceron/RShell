#ifndef __SEMICOLON_H__
#define __SEMICOLON_H__

#include "Command.h"
#include <string>

class Semicolon : public Command {
public:
	Semicolon() { this->execPassed = false; }
	Semicolon(Command* l, Command* r) {
		this->left = l;
		this->right = r;
		this->execPassed = false;
	}

	int execute() {
		if (!(left == NULL)) { left->execute(); }
		if (!(right == NULL)) 
		{
			right->execute();
			if(right->getExecPassed())
			{
				execPassed = true;
			}
		}
		return 1;
	}

	bool isConnector()
	{
		return true;
	}
};

#endif
