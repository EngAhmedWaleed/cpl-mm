#ifndef CPL_MOD_MANAGER_REPOSITORY_H
#define CPL_MOD_MANAGER_REPOSITORY_H

#include <string>

using namespace std;

class Repository {
private:
    string origin;

    bool exists();

    bool exec(string command, bool pipe_result = true);

public:
    string name;

    explicit Repository(string name, string origin);

    string parseVersion();

    bool upToDate();
};

#endif //CPL_MOD_MANAGER_REPOSITORY_H
