#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <sys/stat.h>
#include <cstdlib>

using namespace std;

void displaySize(string, string); //early declarations
int dirCount(string, string);
int regCount(string, string);
string getCommand(string);

int main(int argc, char *argv[])
{
	string path = argv[1], files;
	
	if (argc < 2) { //if there are no arguments
		cout << "Please input an argument\n";
		return 0;
	}

	if (argc > 2) { //if there are too many arguments
		cout << "Please input only one argument\n";
		return 0;
	}
	
	files = getCommand("ls -r " + path); //get results from calling ls command

	cout << "The total number of directories in directory " << path
	<< " is: " << dirCount(files, path) << endl; //output results
	cout << "The total number of files in directory " << path << " is: " << regCount(files, path) << endl;
	displaySize(files, path);

	return 0;
}

void displaySize(string files, string path) // displays sizes of files, then total size
{
	stringstream s(files);
	string word, token, fullPath, fileData;
	struct stat sb;
	int i = 0, totalSize = 0;

	while (s >> word) //read files one by one
	{	
		i = 0;
		fullPath = "";
		fullPath = path + "/" + word;

		if (stat(fullPath.c_str(), &sb) == 0 && S_ISREG(sb.st_mode)) //if reg file
		{
			fileData = getCommand("ls -l " + fullPath); //get ls -l result

			stringstream t(fileData);

			while (t >> token) //go through each token
			{
				i++;
				if (i == 5) { //find token with bytes info
					totalSize += atoi(token.c_str());
				}
			}
		}
	}
	cout << "The total number of bytes occupied by all files in directory " << path << " is: " << totalSize << endl;
}

int dirCount(string files, string path) //count amount of directories
{
	int count = 0;
	stringstream s(files);
	string word, fullPath;
	struct stat sb;

	while (s >> word) //read files one by one
	{
		fullPath = "";
		fullPath = path + "/" + word;
		if (stat(fullPath.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode)) { //if file is directory
			count++;
		}
	}

	return count;
}

int regCount(string files, string path) //count amount of regular files
{
	int count = 0;
	stringstream s(files);
	string word, fullPath;
	struct stat sb;

	while (s >> word) //read files one by one
	{
		fullPath = "";
		fullPath = path + "/" + word;
		if (stat(fullPath.c_str(), &sb) == 0 && S_ISREG(sb.st_mode)) { //if reg file
			count++;
		}
	}

	return count;
}

string getCommand(string command) //processes command output into a string
{
	const int MAX_SIZE = 256;
	string data;
	FILE * fstream;
	char buffer[MAX_SIZE];

	command.append(" 2>&1");

	fstream = popen(command.c_str(), "r");
	
	if (fstream) //while stream doesn't end
	{
		while (!feof(fstream)) 
			if (fgets(buffer, MAX_SIZE, fstream) != NULL)  //get character if there
				data.append(buffer);
				pclose(fstream);
	}
	
	return data;
}
