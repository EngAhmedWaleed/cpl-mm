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

    void cd(const char *path);

    string cwd();

    string initializeModsFolder(Launcher game_launcher);

public:
    explicit CMDManager();

    string exec(const string &command);

    bool setModsFolder(string path);

    string getModsFolder();
};

#endif //CMDMANAGER_H
