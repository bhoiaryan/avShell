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

void executeCommand(const Command& command) {
    if (command.arguments.empty()) {
        return;
    }

    if (!command.redirections.empty()) {
        cerr << "avShell: redirection is not supported yet\n";
        return;
    }

    vector<char*> argv;

    for (const auto& a : command.arguments) {
        argv.push_back(const_cast<char*>(a.c_str())); // const char* -> char*
    }

    argv.push_back(nullptr);

    pid_t pid = fork();

    if (pid == -1) {
        cout << "error" << endl;
        return;
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
}

int main() {
    string input;

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
                for (auto& arg : command.arguments) {
                    arg = expandVariables(arg);
                }

                for (auto& redirection : command.redirections) {
                    redirection.target =
                        expandVariables(redirection.target);
                }
            }

            Command& command = pipeline.commands[0];

            if (command.arguments.empty()) {
                continue;
            }

            if (isBuiltin(command.arguments[0])) {
                int result = executeBuiltin(command.arguments);

                if (result == 1) {
                    break;
                }

                continue;
            }

            executeCommand(command);
        }
        catch (const exception& e) {
            cerr << "avShell: syntax error: "
                 << e.what()
                 << endl;
        }
    }

    return 0;
}
