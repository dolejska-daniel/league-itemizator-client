#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "aboutdialog.h"
#include "settingsdialog.h"

#include <QMainWindow>
#include <QSettings>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QSettings *settings;

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


//======================================================================dd==
//  SLOTS
//======================================================================dd==
public slots:
    void AutoUpdateData(bool value);
    void UpdateData();

    void AutoUpdateClient(bool value);
    void UpdateClient();

private:
    Ui::MainWindow *ui;

    AboutDialog *_aboutDialog;
    SettingsDialog *_settingsDialog;
};

#endif // MAINWINDOW_H
