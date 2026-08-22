#include "builtins.h"

bool isBuiltin(const string& command){

  return command == "exit";
}

int executeBuiltin(const vector<string>& args){

  if(args[0]=="exit"){
  return 1;
  }
  return 0;
  }
