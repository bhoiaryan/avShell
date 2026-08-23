#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<unistd.h>
#include<sys/wait.h>
#include<cerrno>
#include<cstring>
#include "builtins.h"
using namespace std;

vector<string> pI(const string& input){
    stringstream ss(input);
    vector<string> args;
    string token;
    
    while(ss>>token){
    args.push_back(token);
    }
    return args;
    
}

void executeCommand(const vector<string>& args){
	vector<char*> argv;
	
	for(const auto& a: args)
	{
		argv.push_back(const_cast<char*>(a.c_str()));// chr* -> char* 
	}
	argv.push_back(nullptr);
	
	pid_t pid = fork();
	
	if(pid==-1)
	{
		cout<<"error"<<endl;
		return;
	}
	if(pid==0)
	{
		execvp(argv[0], argv.data());
		cerr<<"avShell: "<<args[0] << ": " <<strerror(errno)<<'\n';
		_exit(127);
	}
	int status;
	if(waitpid(pid, &status, 0)==-1){
	cerr<<"avShell: waitpid failed\n";
	}
}
  
int main(){
  string input;
  
  while(true){
    cout<<"avShell$ ";
    
    if(!getline(cin,input)){
      cout<<'\n';
      break;
    }
    vector<string> args = pI(input);
    
    if(args.empty()){
    continue;
    }
    if(isBuiltin(args[0])){
      int result = executeBuiltin(args);
      if(result == 1){
        break;
        }
        continue;
     }
    executeCommand(args);
  }
  return 0;
}
