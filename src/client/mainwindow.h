#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "aboutdialog.h"
#include "settingsdialog.h"
#include "dataapi.h"

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
    DataApi *api;

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    //======================================================================dd==
    //  CONTROL FUNCTIONS
    //======================================================================dd==

    /**
     * @brief GetCurrentDataVersion
     */
    void GetCurrentDataVersion();

    /**
     * @brief GetCurrentAppVersion
     */
    void GetCurrentAppVersion();

public slots:
    //======================================================================dd==
    //  SLOTS
    //======================================================================dd==

    /**
     * @brief AutoUpdateData
     * @param value Is enabled?
     */
    void AutoUpdateData(bool value);
    /**
     * @brief UpdateData
     */
    void UpdateData();

    /**
     * @brief AutoUpdateClient
     * @param value Is enabled?
     */
    void AutoUpdateClient(bool value);
    /**
     * @brief UpdateClient
     */
    void UpdateClient();

private:
    Ui::MainWindow *ui;

    AboutDialog *_aboutDialog;
    SettingsDialog *_settingsDialog;
};

#endif // MAINWINDOW_H
