#ifndef CPL_MOD_MANAGER_REPOSITORY_H
#define CPL_MOD_MANAGER_REPOSITORY_H

#include <string>

using namespace std;

class Repository {
private:
    string name;
    string origin;

    bool exists();

    bool exec(string command, bool pipe_result = true);

public:
    explicit Repository(string name, string origin);

    string getDirName();

    string parseVersion();

    bool upToDate();

    void update(bool install_if_missing);
};

#endif //CPL_MOD_MANAGER_REPOSITORY_H
