#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(unordered_map<string, Repository *> map, QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    this->modsMap = map;
    ui->setupUi(this);
    cmd = CMDManager::getInstance();
    ui->modsLocation->setText(cmd->getModsFolder().c_str());
    refreshModsTree();
}

MainWindow::~MainWindow() {
    delete ui;
    delete cmd;
}

void MainWindow::on_browseButton_clicked() {
    cmd->setModsFolder();
    ui->modsLocation->setText(cmd->getModsFolder().c_str());
    refreshModsTree();
}

void MainWindow::on_updateButton_clicked() {
    for (auto mod : modsMap)
        mod.second->update(false);
    refreshModsTree();
}

void MainWindow::on_updateSelectedButton_clicked() {
    for (string selected_mod : selectedMods)
        modsMap[selected_mod]->update(true);
    refreshModsTree();
}

void MainWindow::on_modsTree_itemSelectionChanged() {
    selectedMods.clear();
    ui->updateSelectedButton->setEnabled(false);
    if (ui->modsTree->selectedItems().empty()) return;

    for (int i = 0; i < ui->modsTree->selectedItems().length(); i++)
        selectedMods.push_back(ui->modsTree->selectedItems().at(i)->text(0).toStdString());

    if (!selectedMods.empty()) ui->updateSelectedButton->setEnabled(true);
}

//https://stackoverflow.com/questions/1814189/how-to-change-string-into-qstring
#define toQString(str)  QString::fromLocal8Bit(str)

void MainWindow::refreshModsTree() {
    cout << "Retrieving mod data";
    for (auto mod : modsMap) {
        cout << " .";
        string version = mod.second->parseVersion();
        auto modEntry = ui->modsTree->findItems(toQString(mod.first), Qt::MatchExactly, 0)[0];

        modEntry->setText(1, toQString(version));

        if (version == "") {
            modEntry->setText(2, toQString("install"));
        } else if (!mod.second->upToDate()) {
            modEntry->setText(2, toQString("update available"));
        } else {
            modEntry->setText(2, toQString("up to date"));
        }
    }
    cout << " Done" << endl;
}
