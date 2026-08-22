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
