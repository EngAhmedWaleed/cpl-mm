#include "cmdmanager.h"
#include <iostream>
#include "../files/utilities.h"
//https://stackoverflow.com/a/40230786
#include <direct.h>

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

string CMDManager::initializeModsFolder(Launcher game_launcher) {
    switch (game_launcher) {
        case STEAM:
        case EPIC_GAMES:
            return readFile(TMP_FILE);
        default:
            return setModsFolder();
    }
}

string CMDManager::setModsFolder() {
    string path;
    if (modsFolder.empty()) {
        bool userFound = !system((DIR(NOT_FOUND) + "cd" + PIPE_OUTPUT).c_str());
        if (!userFound)
            path = BrowseFolder("", "Please Locate Civilization VI Mods Folder");
        else
            path = BrowseFolder(readFile(TMP_FILE), "Please Locate Civilization VI Mods Folder");
        if (path.empty())
            path = setModsFolder();
    } else
        path = BrowseFolder(modsFolder, "Please Locate Civilization VI Mods Folder");

    if (!path.empty())
        modsFolder = path;
    return modsFolder;
}

string CMDManager::getModsFolder() {
    return modsFolder;
}

void CMDManager::cd(const char *path) {
    if (0 != _chdir(path)) {
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
            return R"(%userprofile%"\Documents\My Games\Sid Meier's Civilization VI\Mods")";
        case EPIC_GAMES:
            return R"(%userprofile%"\Documents\My Games\Sid Meier's Civilization VI (Epic)\Mods")";
        default:
            return R"("%userprofile%\Documents")";
    }
}

