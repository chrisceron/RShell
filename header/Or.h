#ifndef __OR_H__
#define __OR_H__

#include "Command.h"
#include <string>

class Or : public Command {

public:
	Or() { this->execPassed = false; }
	Or(Command* l, Command* r) {
		this->left = l;
		this->right = r;
		this->execPassed = false;
	}

	int execute() {
		if (!(left == NULL))
		{
			if (left->execute() && left->getExecPassed())
			{
				execPassed = true;
				return 1;
			}
		}
		if (!(right == NULL))
		{
			if (right->execute() && right->getExecPassed()) { execPassed = true; }
		}
		return 1;
	}

	bool isConnector()
	{
		return true;
	}
};

#endif
