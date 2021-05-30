#include <iostream>
#include <QApplication>
#include "gui/mainwindow.h"

unordered_map<string, Repository *> modsMap;

void initializeMods();

int main(int argc, char *argv[]) {
    /// TODO
    if (!CMDManager::getInstance()->exec("git --version", false)) {
        cout << "Couldn't find git, please install: https://git-scm.com/downloads\n" << endl;
        system("pause");
        return 0;
    }
    /// TODO
    initializeMods();

    QApplication app(argc, argv);
    MainWindow window(modsMap);
    window.show();
    return app.exec();
}

void initializeMods() {
    modsMap["Better Balanced Game"] = new Repository("BBG", "https://github.com/iElden/BetterBalancedGame");
    modsMap["Better Balanced Starts"] = new Repository("BBS\\1958135962",
                                                       "https://github.com/d-jackthenarrator/Civ6-BBS");
    modsMap["Better Spectator Mod"] = new Repository("BSM\\1916397407",
                                                     "https://github.com/d-jackthenarrator/Civ6-BSM");
    modsMap["Multiplayer Helper"] = new Repository("MPH\\2357532056",
                                                   "https://github.com/d-jackthenarrator/Civ6-MPH");
}
