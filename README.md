                            avShell Lifecycle History
                            

Version 0

    This version contains a just the project structure with all the directories and important files which we will need throughout the project.
    
    Project Structure:
    
                avShell/
            ├── src/
            │   └── main.cpp
            ├── include/
            ├── tests/
            ├── CMakeLists.txt
            ├── .gitignore
            └── README.md
            
    The main.cpp contains just -> cout<<"avShell starting...";
    
and CMakeLists.txt is an instruction file for CMAKE. For now, think it as something which will help us to comiple all the files at once.



VERSION 1

        In Version 1.1: I am taking input from user in a string and printing "You enetered: cmd";
        
        
        In Version 1.2:
        The core function of the shell is implemented, i.e fork(), execv(), and wait().
        
        I have implemented two major functions here parseInt() and executeCommand() functions in this version.
        the parse function converts the command in one string to parts which are seperated by the delimiter spaces. it then stores them in the vector args and returs.
        
        the executeCommand first converts the args given by parseInput to type char* as execvp accpets this type and in args there is string data type.
        
        
        Version 1.3:
        
        Here we just improve our shell by
        
        1) check if command is exit, if so then terminate
        
        2) i included error handling effiiently for execvp , in simple words for invalid commands
        
        3) checking if waitpid fails
        
        thats all for version 1..........
        
..................................__________________________________________.......................
        
