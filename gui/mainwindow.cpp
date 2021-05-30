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

void MainWindow::on_updateSelectedButton_clicked() {
    refreshModsTree();
}

#include <iostream>

//https://stackoverflow.com/questions/1814189/how-to-change-string-into-qstring
#define toQString(str)             QString::fromLocal8Bit(str)
#define CHILDREN_TMP_FIX(entry)    \
    if (entry->childCount() != 0)  \
    entry = entry->child(0);

void MainWindow::refreshModsTree() {
    for (auto mod : modsMap) {
        string version = mod.second->parseVersion();
        auto modEntry = ui->modsTree->findItems(toQString(mod.first), Qt::MatchExactly, 0)[0];

        CHILDREN_TMP_FIX(modEntry);
        modEntry->setText(1, toQString(version));

        if (version == "") {
            modEntry->setText(2, toQString("install"));
        } else if (!mod.second->upToDate()) {
            modEntry->setText(2, toQString("update available"));
        } else {
            modEntry->setText(2, toQString("up to date"));
        }
    }
}
