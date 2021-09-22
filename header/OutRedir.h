#ifndef __OUTREDIR_H__
#define __OUTREDIR_H__


#include "Command.h"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

class OutRedir : public Command {
public:

	string userCommand;
	string file;
	bool append;

	OutRedir() {execPassed = true; }

	OutRedir(string input, string file, bool append)
	{
		userCommand = input;
		this->file = file;
		this->append = append;
		execPassed = true;
	}

	int execute()
	{
		int fd, newDup, savestd;

		if (append)
		{
			fd = open(file, O_CREAT | O_APPEND | O_WRONLY);
		}
		else {
			fd = open(file, O_CREAT | O_TRUNC | O_WRONLY);
		}

		if (fd < 0)
		{
			perror("Error opening file");
			this->execPassed = false;
			return 1;
		}
		
		savestd = dup(0);

		newDup = dup2(fd, 1);

		system(input);

		dup(savestd, 0);

		close(fd);

		return 1;
	}

	bool getExecPassed(){return this->execPassed;}

	bool isConnector()
	{
		return false;
	}

};

#endif
