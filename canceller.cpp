#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <fstream>

using namespace std;
string command ("ps -eo user,etime,comm | grep ");
string name;

class program{
	public:
	uint32_t time_shutdown = 2;		// in seconds time in how long the program will be taken down 
	
	string name;
	program(string name){
		this -> name = name;
		}
		
	program(string name, uint32_t time_shutdown){
		this -> name = name;
		this -> time_shutdown = time_shutdown;
		}
		
	void parse(string line){
		cout << this->name << endl;
		size_t usefuls[4] = {0 ,line.find(":"), 0, 0};
		usefuls[0] = line.rfind(" ", usefuls[1]);
		usefuls[2] = line.find(":", usefuls[1]+1);
		usefuls[3] = line.find(" ", usefuls[2]);
		//~ usefuls[4] = line.find(" ", usefuls[3]);
		
		uint8_t value[3];
		for (uint8_t i = 0; i < 3; i++){
			value[2-i] = atoi(line.substr(usefuls[i]+1, usefuls[i+1] - (usefuls[i]+1)).c_str());
			}
		
		end(value[0]*3600 + value[1] + value[2]*60);
		cout << value[0]*3600 + value[1] + value[2]*60 << endl;
		
		}
		
	void end(uint32_t time){
		if(time >= time_shutdown){
			string killer("killall ");
			string killed("echo killed ");
			killer += this->name;
			killed += this->name;
			system(killer.c_str());
			system(killed.c_str());
			//~ system();
			}
		}
	};
	
vector <program> blacklist;

ifstream config("running");

void make_list(){
	
	ifstream config("list.txt");
	string myText;
	while (getline (config, myText)) {
		// Output the text from the file
		if (myText == "config:") {
			getline (config, myText);
			name = myText;
			command += name;
			command += " > running";
			break;
		}
		if (myText != ""){
			if(myText.find(" ") != std::string::npos){
				cout << myText.find(" ") << endl;
				blacklist.push_back(program(myText.substr(0, myText.find(" ")), atoi(myText.substr(myText.rfind(" ")).c_str())));
				}
			else {
				blacklist.push_back(program(myText));
				}
		}
	}
}

void refresh(){
	ifstream list("running");
	string f;
	while(getline(list, f))
		for(auto i: blacklist){
			//~ cout << i.name << endl;
			if(f.find(i.name.substr(0, (i.name.length() >= 15? 15 :i.name.length()))) != std::string::npos)
				i.parse(f);
		}
	}

int main(int argc, char *argv[]){
	if (argc > 1)
		switch(*argv[1]){
			case 'a':
				if(argc == 3){}
				break;
			case 'k':
				system("rm running");
				system("killall canceller.o");				
				break;
				}
	else{
		
		make_list();
			for (auto i: blacklist)
				cout << i.name << endl;
			system("rm running");
			//~ cout << command << endl;
			system(command.c_str());
			std::string current;
			while(1){
				system("sleep 2");
				system(command.c_str());
				refresh();
				}
		}
}
