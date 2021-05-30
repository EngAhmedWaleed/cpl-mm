#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <unordered_map>
#include "../utilities/cli/cmdmanager.h"
#include "../utilities/git/repository.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(unordered_map<string, Repository *> map, QWidget *parent = nullptr);

    ~MainWindow() override;

private slots:

    void on_browseButton_clicked();

    void on_updateButton_clicked();

    void on_modsTree_itemSelectionChanged();

    void on_updateSelectedButton_clicked();

private:
    CMDManager *cmd;
    Ui::MainWindow *ui;

    vector<string> selectedMods;
    unordered_map<string, Repository *> modsMap;

    void refreshModsTree();
};

#endif // MAINWINDOW_H
