#include<iostream>
#include<string>
using namespace std;

int main(){
  string input;
  
  while(true){
    cout<<"avShell$";
    
    if(!getline(cin,input)){
      cout<<'\n';
      break;
    }
    
    cout<<"You entered: "<<input<<endl;
  }
  
  
  return 0;
}
