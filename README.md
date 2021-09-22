# CS 100 - RShell
Summer A01 2019
Chris Ceron SID: 862091143
Edmund Hwang SID:860931903
Isaac Gallegos SID: 861237839


# Introduction

This program will simulate a shell program which will be able to do the following things when executed:

     1. Print a command prompt (e.g. '$')
     2. Read in a line of command(s) (and connector(s)) from standard input
     3. Execute the appropriate commands using fork, execvp, and waitpid

# Diagram

![Shell Classes](https://github.com/cs100/assignment-yes/blob/master/images/ShellClasses2.png)

# Classes

### Command

This is the base class of every other class in our program. It has a left and right pointer that will be used by the connector subclass and a char pointer that will be used by the execute class. The only public function it has is a virtual execute that gets implemented differently by each sub class.

### Executable

This is a subclass of command that stores a char pointer containing the tokens used for the execute to run. It also contains an execute function that uses fork(), execvp(), and waitpid() to execute the commands.

### And

And is one of the subclasses that distinguish what to do when a connector is used in the user input. It contains a left and right pointer that point to execute leafs and executes from left to right. If the left pointer returns false, it will not execute the right pointer and return false.

### Or

Or is one of the subclasses that distinguish what to do when a connector is used in the user input. It contains a left and right pointer that point to execute leafs and executes from left to right. If the left pointer returns true, it will not execute the right pointer and return true.

### Semicolon

Semicolon is one of the subclasses that distinguish what to do when a connector is used in the user input. It contains a left and right pointer that point to execute leafs and executes from left to right. It executes the right pointer regardless of whether the left returns true or false and returns true if the right pointer successfully executes.

### Test

Test is a subclass of Command that receives a flag and a test/path to check if the directory/file exists. It contains a vector of strings that is either parsed in the constructor or passed from the Executable function. Its execute function prints whether the file/directory exists, and returns 1 once the execution has been completed.

# Prototypes/Research
In order to test what fork(), execvp(), and waitpid() do, we must include the libraries <unistd.h>, <stdio.h>, and <sys/wait.h> in order to run these functions.From the given resources for Assignment 2, we know that fork() creates a duplicate of a process which returns 0. The original process should return a number bigger than zero. If either of the processes return a number less than zero, then the fork() did not duplicate properly and we must kill the process.

# Development and Testing Roadmap
Our assignment will approximately follow this structure.

* CMakeLists.txt
* README.md
* googletest
* header
  * And.h        (Composite class)
  * Command.h    (Base class)
  * Executable.h (Leaf class)
  * Or.h         (Composite class)
  * Semicolon.h  (Composite class)
  * Test.h  (Composite class)
* src
  * main.cpp
* unit_tests
  * and_test.cpp
  * exec_test.cpp
  * or_test.cpp
  * semicolon_test.cpp
  * unit_test.cpp (includes above 4 tests to execute at all of them at once)
  * precedence_test.cpp
  * test_literal.cpp
  * test_symbolic.cpp
* integrations_tests
  * single_command_tests.sh
  * multiple_commands_tests.sh
  * commented_command_tests.sh
  * exit_commmand_tests.sh
  * test_literal_tests.sh
  * test_symbolic_tests.sh
  * precendence_tests.sh

The **src/** directory will contain all of the .cc/.cpp files used in our project. Header files will be saved in a **header/** folder. The **unit_tests/** directory will contain all of the unit tests that are written using the Google Unit Test framework. The **integration_tests/** directory will contain all of the tests written using bash. The tests will consist of several cases.

  1. Only a valid executable is passed in. (e.g. ls)
  2. First executable is invalid (display error)
  3. Valid executable with valid argument
  4. Valid executable with invalid argument
  5. Valid executable and argument with valid connector
  6. Input with a combination of 1-5. (Multiple Command Tests)
  7. Testing the special exit command.
  8. Checking for comments from user input.
  9. Checking for parenthesis from user input.
  10. Checking for brackets or test literal commands.

It will also include a .gitignore which contains the executable files, CMakeCache.txt, CMakeFiles/ directory and other files that should be ignored.

