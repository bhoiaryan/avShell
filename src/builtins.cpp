#include "builtins.h"
#include<iostream>
#include<unistd.h>
#include<limits.h>

bool isBuiltin(const std::string& command){

  return command == "exit" ||
          command == "cd" ||
          command == "pwd" ||
          command == "echo" ||
          command == "export" ||
          command == "unset";
          
}

int executeBuiltin(const std::vector<std::string>& args){

  if(args[0]=="exit"){
  return 1;
  }
  if(args[0]=="cd"){
    if(args.size()<2){
      std::cerr<<"avShell: cd: missing arguement\n";
      return 0;
    }
    if(chdir(args[1].c_str())==-1){
      std::perror("avShell: cd");
    }
    return 0;
  }
  if(args[0] == "pwd")
  {
    char cwd[PATH_MAX];
    
    if(getcwd(cwd, sizeof(cwd)) == nullptr){
      std::perror("avShell: pwd");
      return 0;
    }
      std::cout<< cwd << '\n';
      return 0;
      }
    if(args[0] == "echo") {
      for(size_t i = 1;i<args.size(); i++){
        if(i>1){
          std::cout<< ' ';
          }
        std::cout << args[i];
        }
        
        std::cout<<'\n';
        return 0;
        }
      if(args[0] == "export"){
        if(args.size()<2){
          std::cerr<<"avShell: export: missing argument\n";
          return 0;
        }
        
        size_t pos = args[1].find('=');
        
        if(pos == std::string::npos){
          std::cerr<<"avShell: export: expected NAME=value\n";
          return 0;
        }
        
        std::string name = args[1].substr(0,pos);
        std::string value = args[1].substr(pos+1);
        
        if(setenv(name.c_str(), value.c_str(), 1)==-1){
          std::perror("avShell: export");
      }
      return 0;
      }
      
      if(args[0]== "unset"){
      if(args.size()<2){
          std::cerr<<"avShell: export: missing argument\n";
          return 0;
        }
      if(unsetenv(args[1].c_str())==-1){
        std::perror("avShell: unset");
      }
      return 0;
      }
        
        
  return 0;
}
