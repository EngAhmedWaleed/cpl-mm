#ifndef CMDMANAGER_H
#define CMDMANAGER_H

#include <string>

enum Launcher {
    STEAM, EPIC_GAMES, NOT_FOUND
};

using namespace std;

class CMDManager {
private:
    string progFolder;
    string modsFolder;

    // https://refactoring.guru/design-patterns/singleton/cpp/example
    static CMDManager *_singleton;

    explicit CMDManager();

    static string cd(string path);

    static string cwd();

    string initializeModsFolder(Launcher game_launcher);

public:
    // Singletons should not be cloneable.
    CMDManager(CMDManager &other) = delete;

    // Singletons should not be assignable.
    void operator=(const CMDManager &) = delete;

    static CMDManager *getInstance();

    bool exec(string command, bool pipe_result = true);

    bool exec(string command, string dir = "", bool pipe_result = true);

    string exec_result();

    string setModsFolder();

    string getModsFolder();
};

#endif //CMDMANAGER_H
