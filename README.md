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
        
        
        
        VERSION 2
        
        here i have added more builtin commands: cd, echo, pwd, export and unset. 
        
        for  cd: chdir() function is used for changing the directory
        
        for pwd: getcwd() is used for getting the current working directory.
        
        for echo we just print things out with a loop.
        
        for export: setenv(name, value, 1)
        
        for unset: unsetenv(name)
        
        
        the builtins.cpp is ugly right now. but it will be made cleaner later.
        
        
>>>>>>>>>>>>>>>>>>>>-------------------------------------------<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

VERSION 3(Ps: for Vidhan only, start understanding now otherwise your pach pach pach is bound to happen.)
    
    VERAION 3.1 
            here we are replacing the old stringstream tokeniser with a better one.
            
    VERSION 3.2
            this version has a very lengthy and a bit complex code. you should use different inputs to test this and also dry run, if possible.
            
            in this version the lexer has 3 states: Normal, singleQuote and doubleQuote. depending on the current we change states.
            from now echo "hello world", will work perfectly
            
    VERSION 3.3
            here we have are now even classifing symbols like |(piping), <, >, >> (i/o redirection).
            there a class Token in token.h which is the main figure head in this version.
            
    VERSION 3.4
            here we have made a command data structure.
            and integrated everything in main.
        
    
