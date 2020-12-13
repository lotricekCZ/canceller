#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <fstream>

using namespace std;

class program{
	public:
	uint32_t time_shutdown = 0;		// in seconds time in how long the program will be taken down 
	uint32_t time_current = 0;		// current time since launch
	string name;
	program(string name){
		this -> name = name;
		}
	};
	
vector <program> blacklist;

ifstream config("running");

void make_list(){
	ifstream config("list.txt");
	string myText;
	while (getline (config, myText)) {
		// Output the text from the file
		blacklist.push_back(program(myText));
}
	}
int main(int argc, char *argv[]){
	make_list();
	for (auto i: blacklist)
		cout << i.name << endl;
	}
	system("ps -aux > running");
	std::string current;
