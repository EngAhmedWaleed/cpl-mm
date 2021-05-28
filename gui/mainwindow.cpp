#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    cmd = new CMDManager();
    ui->modsLocation->setText(cmd->getModsFolder().c_str());
}

MainWindow::~MainWindow() {
    delete ui;
    delete cmd;
}

void refreshModsTree();

void MainWindow::on_browseButton_clicked() {
    cmd->setModsFolder();
    ui->modsLocation->setText(cmd->getModsFolder().c_str());
    refreshModsTree();
}

void MainWindow::on_updateButton_clicked() {
    refreshModsTree();
}

void MainWindow::on_modsTree_itemSelectionChanged() {

}

void refreshModsTree() {

}
