#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <string>
#include <stack>
#include <queue>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

#include "../header/Command.h"
#include "../header/Executable.h"
#include "../header/And.h"
#include "../header/Or.h"
#include "../header/Semicolon.h"
#include "../header/Test.h"

using namespace std;

Command* parse(string uI);

int main() {

	while (true)
	{
		string userInput;
		Command* userCommands;

		cout << "$ ";
		getline(cin, userInput);

		userCommands = parse(userInput);
		userCommands->execute();
	}
	return 0;
}

Command* parse(string uI)
{
	int cursor = 0;
	bool openQuote = false;
	bool connectCheck = false;
	vector<string> separatedUI;

	for (int i = 0; i < uI.size(); i++)
	{
		if (uI.at(i) == '"')
		{
			if (openQuote)
			{
				openQuote = false;
			}
			else
				openQuote = true;
		}

		if (openQuote == false && uI.at(i) == '&' || uI.at(i) == '|' || uI.at(i) == ';')
		{
			connectCheck = true;
		}

		if (uI.at(i) == '#' && openQuote == false)
		{
			uI = uI.substr(0, i);
			break;
		}
	}

	if (connectCheck == true)
	{
		for (int i = 0; i < uI.size(); i++)
		{
			if (uI.at(i) == '&' && openQuote == false)
			{
				if (uI.at(i + 1) == '&')
				{
					separatedUI.push_back(uI.substr(cursor, i - cursor - 1));
					separatedUI.push_back("&");
					i += 2;
					cursor = i + 1;
				}
			}
			else if (uI.at(i) == '|' && openQuote == false)
			{
				if (uI.at(i + 1) == '|')
				{
					separatedUI.push_back(uI.substr(cursor, i - cursor - 1));
					separatedUI.push_back("|");
					i += 2;
					cursor = i + 1;
				}
			}
			else if (uI.at(i) == ';' && openQuote == false)
			{
				separatedUI.push_back(uI.substr(cursor, i - cursor));
				separatedUI.push_back(";");
				i++;
				cursor = i + 1;
			}
			else if(uI.at(i) == '(' && openQuote == false)
			  {
			    separatedUI.push_back("(");
			    cursor = i + 1;
			  } 
			else if(uI.at(i) == ')' && openQuote == false)
			  {
			    if(i == (uI.size() -1))
			      {
				separatedUI.push_back(uI.substr(cursor, i - cursor));
				separatedUI.push_back(")");
			      }
			    else
			      {
				if (uI.at(i + 1) == ' ') 
				  {
				    if (uI.at(i + 2) == '&' && uI.at(i + 3) == '&') 
				      {
				      separatedUI.push_back(uI.substr(cursor, i - cursor));
				      separatedUI.push_back(")");
				      separatedUI.push_back("&");
				      i = i + 4;
				      cursor = i + 1;
				      }
				    
				    else if (uI.at(i + 2) == '|' && uI.at(i + 3) == '|') 
				      {
					separatedUI.push_back(uI.substr(cursor, i - cursor));
					separatedUI.push_back(")");
					separatedUI.push_back("|");
					i = i + 4;
					cursor = i + 1;
				      }
				  }
				
				else if (uI.at(i + 1) == ';') 
				  {
				    separatedUI.push_back(uI.substr(cursor, i - cursor));
				    separatedUI.push_back(")");
				    separatedUI.push_back(";");
				    i = i + 2;
				    cursor = i + 1;
				  }
				
				else if (uI.at(i + 1) == ')') 
				  {
				  separatedUI.push_back(uI.substr(cursor, i - cursor));
				  separatedUI.push_back(")");
				  separatedUI.push_back(")");
				  i = i + 2;
				  cursor = i + 1;
				}
			      }
			  }
			
			
			else if (i == (uI.size() - 1))
			  {
			    separatedUI.push_back(uI.substr(cursor, i - cursor + 1));
			  }
		}
	}
	else
	{
		separatedUI.push_back(uI);
	}


	stack<string>opStack;
	queue<string>comQueue;

	for (int i = 0; i < separatedUI.size(); i++)
	{
		if (separatedUI.at(i) == "&" || separatedUI.at(i) == "|" || separatedUI.at(i) == ";")
		{
			if (opStack.empty())
			{
				opStack.push(separatedUI.at(i));
				continue;
			}
			else if(opStack.top() != "(")
			{
				comQueue.push(opStack.top());
				opStack.pop();
			}
			opStack.push(separatedUI.at(i));
		}
		else if(separatedUI.at(i) == "(")
		  {
		    opStack.push(separatedUI.at(i));
		  }
		else if(separatedUI.at(i) == ")")
		  {
		    while(opStack.top() != "(")
		      {
			comQueue.push(opStack.top());
			opStack.pop();
		      }
		    opStack.pop();
		  }
		else
		{
			comQueue.push(separatedUI.at(i));
		}
	}

	while (!opStack.empty())
	{
		comQueue.push(opStack.top());
		opStack.pop();
	}

	stack<Command*> finalStack;

	while (!finalStack.empty())
	{
		finalStack.pop();
	}

	Command* X;

	while (!comQueue.empty())
	{
		if (comQueue.front() == "&")
		{
			X = new And();
		}
		else if (comQueue.front() == "|")
		{
			X = new Or();
		}
		else if (comQueue.front() == ";")
		{
			X = new Semicolon();
		}
		else
		{
			X = new Executable(comQueue.front());
		}

		if (X->isConnector() == true)
		{
			Command* right = finalStack.top();
			finalStack.pop();
			Command* left = finalStack.top();
			finalStack.pop();
			X->set(left, right);
			finalStack.push(X);
		}
		else
		{
			finalStack.push(X);
		}

		comQueue.pop();
	}

	Command* root = finalStack.top();

	while (!finalStack.empty())
	{
		finalStack.pop();
	}

	return root;

}
