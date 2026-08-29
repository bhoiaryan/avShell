#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <cerrno>
#include <cstring>

#include "builtins.h"
#include "token.h"
#include "parser.h"
#include "lexer.h"
#include "expansion.h"

using namespace std;

int executeCommand(const Command& command) {
    if (command.arguments.empty()) {
        return 1;
    }

    if (!command.redirections.empty()) {
        cerr << "avShell: redirection is not supported yet\n";
        return 101;
    }

    vector<char*> argv;

    for (const auto& a : command.arguments) {
        argv.push_back(const_cast<char*>(a.c_str())); // const char* -> char*
    }

    argv.push_back(nullptr);

    pid_t pid = fork();

    if (pid == -1) {
        cout << "error" << endl;
        return 1;
    }

    if (pid == 0) {
        execvp(argv[0], argv.data());

        cerr << "avShell: "
             << command.arguments[0]
             << ": "
             << strerror(errno)
             << '\n';

        _exit(127);
    }

    int status;

    if (waitpid(pid, &status, 0) == -1) {
        cerr << "avShell: waitpid failed\n";
    }
    if(WIFEXITED(status)){
      return WEXITSTATUS(status);
    }
    return 1;
}

int main() {
    string input;
    int lastExitStatus = 0;

    while (true) {
        cout << "avShell$ ";
        cout.flush();

        if (!getline(cin, input)) {
            cout << '\n';
            break;
        }

        try {
            auto tokens = tokenize(input);

            if (tokens.empty()) {
                continue;
            }

            Pipeline pipeline = parse(tokens);
            
            

            if (pipeline.commands.empty()) {
                cerr << "avShell: pipes are not supported yet\n";
                continue;
            }
            for (auto& command : pipeline.commands) {
                for(size_t i=0; i<command.arguments.size();i++){
                        command.arguments[i] =
                        expandToken(
                        command.argumentTokens[i],
                        lastExitStatus
                      );
                  }
                    
               // for (auto& redirection : command.redirections) {
               //     redirection.target =
              //          expandVariables(redirection.target, lastExitStatus);
                //}
            }

            Command& command = pipeline.commands[0];

            if (command.arguments.empty()) {
                continue;
            }

            if (isBuiltin(command.arguments[0])) {
                BuiltinResult result = executeBuiltin(command.arguments);
                
                lastExitStatus = result.exitStatus;
                
                if (result.shouldExit) {
                    break;
                }

                continue;
            }

           lastExitStatus =  executeCommand(command);
        }
        catch (const exception& e) {
            cerr << "avShell: syntax error: "
                 << e.what()
                 << endl;
        }
    }

    return 0;
}
