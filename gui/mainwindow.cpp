#include "mainwindow.h"
#include "ui_mainwindow.h"

void refreshModsTree();

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
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
    cmd->exec("cd", false);
    cmd->exec("cd", true);
    refreshModsTree();
}

void refreshModsTree() {

}
