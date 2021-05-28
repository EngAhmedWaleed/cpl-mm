#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../utilities/cli/cmdmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private slots:

    void on_browseButton_clicked();

    void on_updateButton_clicked();

    void on_modsTree_itemSelectionChanged();

private:
    CMDManager *cmd;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
