#ifndef __AND_H__
#define __AND_H__

#include "Command.h"
#include <string>

class And : public Command {
public:


	And() {
		this->left = NULL;
		this->right = NULL;
		this->execPassed = false;
	}
	And(Command* l, Command* r) {
		this->left = l;
		this->right = r;
		this->execPassed = false;
	}

	int execute() {
		if (!(left == NULL))
		{
			left->execute();
			if (left->getExecPassed() && right != NULL)
			{
				this->right->execute();
				if (right->getExecPassed())
				{
					execPassed = true;
				}
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
