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

    static void cd(const char *path);

    static string cwd();

    string initializeModsFolder(Launcher game_launcher);

public:
    explicit CMDManager();

    string exec(const string &command);

    string setModsFolder();

    string getModsFolder();
};

#endif //CMDMANAGER_H
