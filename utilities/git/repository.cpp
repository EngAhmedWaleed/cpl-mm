#include <iostream>
#include "../files.h"
#include "repository.h"
#include "../cli/cmdmanager.h"

Repository::Repository(string name, string origin) {
    this->name = name;
    this->origin = origin;
}

string Repository::getDirName() {
    auto first_separator = name.find("\\");
    if (first_separator == std::string::npos)
        return name;
    return name.substr(0, first_separator);
}

#define MOD_PATH        CMDManager::getInstance()->getModsFolder() + "\\" + name
#define MOD_INFO_FILE   ls(MOD_PATH, "*.modinfo")[0]

string regex_first_match(string str, string regex);

string Repository::parseVersion() {
    if (!exists()) return "";

    string modinfo = searchFile(MOD_PATH + "\\" + MOD_INFO_FILE, "<Version>[0-9]+</Version>");
    string version = regex_first_match(regex_first_match(modinfo, "<Version>[0-9]+</Version>"), "[0-9]+");

    version = version[0] + version.substr(version.length() - 2);
    for (int i = 0; i < version.length() - 1; i += 2)
        version.insert(i + 1, ".");

    return version;
}

bool Repository::upToDate() {
    if (exec("git fetch --no-tags", false))
        if (exec("git status"))
            //https://stackoverflow.com/questions/2340281/check-if-a-string-contains-a-string-in-c
            return CMDManager::getInstance()->exec_result().find("up to date") != std::string::npos;
    return false;
}

void Repository::update(bool install_if_missing) {
    if (!exists()) {
        if (install_if_missing) {
            std::cout << "Installing " + getDirName() + " . . . .";
            CMDManager::getInstance()->exec("git clone " + origin + " \"" + getDirName() + '\"', false);
            std::cout << " Done" << std::endl;
        }
        return;
    }
    exec("git pull origin master", false);
    exec("git checkout master");
}

bool Repository::exists() {
    if (exec("cd"))
        if (exec("git remote get-url origin"))
            if (CMDManager::getInstance()->exec_result().compare(origin) == 0)
                return true;
    return false;
}

bool Repository::exec(string command, bool pipe_result) {
    return CMDManager::getInstance()->exec(command, name, pipe_result);
}

//https://www.geeksforgeeks.org/regex-regular-expression-in-c/
string regex_first_match(string str, string reg) {
    regex r(reg);
    smatch m;
    regex_search(str, m, r);
    return m[0];
}
