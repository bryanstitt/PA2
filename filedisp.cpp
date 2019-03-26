#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
	string test;
	
	if (string(argv[1]) == "-d") //if -d option, output directory cnt
	{
		getline(cin, test);
		cout << test << endl;
	}
	else if (string(argv[1]) == "-f") //if -f option, output file cnt
	{
		for (int i = 0; i < 2; i++){ //loop twice to get to line
			getline(cin, test);
		}
		cout << test << endl;
	}
	else if (string(argv[1]) == "-b") //if -b option, output total byte count
	{
		for (int i = 0; i < 3; i++) { //loop through three times for line
			getline(cin, test);
		}

		cout << test << endl;
	}
	else {
		cout << "Invalid option given.\n"; //if neither options, display eroor message
	}

	return 0;
}
