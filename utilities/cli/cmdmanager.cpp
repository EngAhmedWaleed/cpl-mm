#include <iostream>
//https://stackoverflow.com/a/40230786
#include <direct.h>

#include "cmdmanager.h"
#include "../files.h"

#define SUPPRESSED          " 2> " + " \"" + progFolder + "\\" + "suppressed.tmp\""
#define DIR(dir)            (dir == ""? "" : ("cd " + dir + SUPPRESSED + " && "))
#define MODS_DIR(launcher)  DIR(getModFolderPath(launcher))

CMDManager *CMDManager::_singleton = nullptr;

string getModFolderPath(Launcher mods_folder);

CMDManager::CMDManager() {
    progFolder = cwd();
    cd("C:\\");

    Launcher mf = NOT_FOUND;
    bool isSteam = exec(MODS_DIR(STEAM) + "cd", true);
    if (!isSteam) {
        bool isEpic = exec(MODS_DIR(EPIC_GAMES) + "cd", true);
        if (isEpic)
            mf = EPIC_GAMES;
    } else
        mf = STEAM;

    modsFolder = cd(initializeModsFolder(mf));
}

CMDManager *CMDManager::getInstance() {
    if (_singleton == nullptr)
        _singleton = new CMDManager();
    return _singleton;
}

bool CMDManager::exec(string command, bool pipe_result) {
    return exec(command, "", pipe_result);
}

#define TMP_FILE            (" \""+ progFolder + "\\" + "output.tmp\"")
#define PIPE_OUTPUT(cond)   (cond ? (" >" + TMP_FILE) : "")

bool CMDManager::exec(string command, string dir, bool pipe_result) {
    return !system((DIR(dir) + command + PIPE_OUTPUT(pipe_result) + SUPPRESSED).c_str());
}

#undef  TMP_FILE
#define TMP_FILE progFolder + "\\output.tmp"

string CMDManager::exec_result() {
    return readFile(TMP_FILE);
}

string CMDManager::setModsFolder() {
    string start_path;
    if (modsFolder.empty()) {
        bool userFound = exec(MODS_DIR(NOT_FOUND) + "cd", true);
        start_path = userFound ? exec_result() : "";
    } else
        start_path = modsFolder;

    string path = browseFolder(start_path, "Please Locate Civilization VI Mods Folder", modsFolder.empty());

    if (!path.empty())
        modsFolder = cd(path);

    return modsFolder;
}

string CMDManager::getModsFolder() {
    return modsFolder;
}

string CMDManager::initializeModsFolder(Launcher game_launcher) {
    switch (game_launcher) {
        case STEAM:
        case EPIC_GAMES:
            return exec_result();
        default:
            return setModsFolder();
    }
}

#define DRIVE_LETTER(path) path.substr(0, 3).c_str()

string CMDManager::cd(string path) {
    if (0 != _chdir(DRIVE_LETTER(path)) || 0 != _chdir(path.c_str())) {
        cerr << "Failed to change cwd! (" << DRIVE_LETTER(path) << ", " << path << ")" << endl;
        throw new exception();
    }
    return path;
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
