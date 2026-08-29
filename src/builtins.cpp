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

BuiltinResult executeBuiltin(const std::vector<std::string>& args){

  if(args[0]=="exit"){
  return {true,0};
  }
  if(args[0]=="cd"){
    if(args.size()<2){
      std::cerr<<"avShell: cd: missing arguement\n";
      return {false,1};
    }
    if(chdir(args[1].c_str())==-1){
      std::perror("avShell: cd");
      return {false,1};
    }
    return {false,0};
  }
  if(args[0] == "pwd")
  {
    char cwd[PATH_MAX];
    
    if(getcwd(cwd, sizeof(cwd)) == nullptr){
      std::perror("avShell: pwd");
      return {false,1};
    }
      std::cout<< cwd << '\n';
      return {false,0};
      }
    if(args[0] == "echo") {
      for(size_t i = 1;i<args.size(); i++){
        if(i>1){
          std::cout<< ' ';
          }
        std::cout << args[i];
        }
        
        std::cout<<'\n';
        return {false,0};
        }
      if(args[0] == "export"){
        if(args.size()<2){
          std::cerr<<"avShell: export: missing argument\n";
          return {false,1};
        }
        
        size_t pos = args[1].find('=');
        
        if(pos == std::string::npos){
          std::cerr<<"avShell: export: expected NAME=value\n";
          return {false,1};
        }
        
        std::string name = args[1].substr(0,pos);
        std::string value = args[1].substr(pos+1);
        
        if(setenv(name.c_str(), value.c_str(), 1)==-1){
          std::perror("avShell: export");
          return {false,1};
      }
      return {false,0};
      }
      
      if(args[0]== "unset"){
      if(args.size()<2){
          std::cerr<<"avShell: export: missing argument\n";
          return {false,1};
        }
      if(unsetenv(args[1].c_str())==-1){
        std::perror("avShell: unset");
        return {false,1};
      }
      return {false,0};
      }
        
        
  return {false,0};
}
