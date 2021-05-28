#include "cmdmanager.h"
#include <iostream>
//https://stackoverflow.com/a/40230786
#include <direct.h>
//https://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
#include <fstream>
#include <streambuf>

#define DIR(launcher)  "cd " + getModFolderPath(launcher) + " && "
#define TMP_FILE progFolder + "\\output.tmp"
#define PIPE_OUTPUT  " >" + TMP_FILE

string getModFolderPath(Launcher mods_folder);

CMDManager::CMDManager() {

    progFolder = cwd();
    cd("C:\\");

    Launcher mf = NOT_FOUND;
    bool isSteam = !system((DIR(STEAM) + "cd" + PIPE_OUTPUT).c_str());
    if (!isSteam) {
        bool isEpic = !system((DIR(EPIC_GAMES) + "cd" + PIPE_OUTPUT).c_str());
        if (isEpic)
            mf = EPIC_GAMES;
    } else
        mf = STEAM;

    modsFolder = initializeModsFolder(mf);

    if (!modsFolder.empty())
        cout << modsFolder;
}

string readFile(string path);

string CMDManager::initializeModsFolder(Launcher game_launcher) {
    switch (game_launcher) {
        case STEAM:
        case EPIC_GAMES:
            return readFile(TMP_FILE);
        default:
            return "";
    }
}

string CMDManager::getModsFolder() {
    return modsFolder;
}

void CMDManager::cd(const char *path) {
    if (0 != _chdir("C:\\")) {
        cerr << "Failed to change cwd!" << endl;
        throw new exception();
    }
}

string CMDManager::cwd() {
    char buf[4096];
    memset(buf, 0, 4096);
    _getcwd(buf, 4096 - 1);
    return buf;
}

string getModFolderPath(Launcher mods_folder) {
    switch (mods_folder) {
        case STEAM:
            return "%userprofile%\"\\Documents\\My Games\\Sid Meier's Civilization VI\\Mods\"";
        case EPIC_GAMES:
            return "%userprofile%\"\\Documents\\My Games\\Sid Meier's Civilization VI (Epic)\\Mods\"";
        default:
            return "%userprofile%\\Documents";
    }
}

string readFile(string path) {
    std::ifstream stream(path);
    std::string str((std::istreambuf_iterator<char>(stream)),
                    std::istreambuf_iterator<char>());
    return str.substr(0, str.length() - 1);
}
