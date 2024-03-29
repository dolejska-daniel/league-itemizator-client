#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "aboutdialog.h"
#include "settingsdialog.h"
#include "dataapi.h"
#include "itemsetapi.h"

#include <QMainWindow>
#include <QSettings>
#include <QSystemTrayIcon>

extern const int APP_VERSION;
extern const QString APP_VERSION_STRING;
extern const QString APP_VERSION_DATE;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QSettings *settings;
    DataApi *api;
    ItemsetApi *itemsets;

    QString unknownText = "<html><head/><body><p><span style=\" color:#555555;\">Unknown</span></p></body></html>";
    QString yesText = "<html><head/><body><p><span style=\" font-weight:600; color:#4e9a06;\">YES</span></p></body></html>";
    QString noText = "<html><head/><body><p><span style=\" font-weight:600; color:#ff0000;\">NO</span></p></body></html>";

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void closeEvent(QCloseEvent *e);


    //======================================================================dd==
    //  SYSTEM TRAY FUNCTIONS
    //======================================================================dd==

    /**
     * @brief CreateTrayIcon
     */
    void CreateTrayIcon();

    /**
     * @brief ShowTrayIcon
     */
    void ShowTrayIcon();

    /**
     * @brief HideTrayIcon
     */
    void HideTrayIcon();


    //======================================================================dd==
    //  SETTINGS MODIFICATION FUNCTIONS
    //======================================================================dd==

    /**
     * @brief SetDataVersion
     * @param version
     */
    void SetDataVersion( QPair<int, QString> const& version );

    /**
     * @brief SetAppVersion
     * @param version
     */
    void SetAppVersion( QPair<int, QString> const& version  );


    //======================================================================dd==
    //  UI MODIFICATION FUNCTIONS
    //======================================================================dd==

    /**
     * @brief DisplayDataVersion
     */
    void DisplayDataVersion();

    /**
     * @brief DisplayAppVersion
     */
    void DisplayAppVersion();


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
    void UpdateData(bool force = true);

    /**
     * @brief AutoUpdateClient
     * @param value Is enabled?
     */
    void AutoUpdateApp(bool value);
    /**
     * @brief UpdateClient
     */
    void UpdateApp();

    /**
     * @brief ToggleVisibility
     */
    void ToggleVisibility();

    /**
     * @brief Exit
     */
    void Exit();

private:
    Ui::MainWindow *ui;
    QSystemTrayIcon *_trayIcon;

    AboutDialog *_aboutDialog;
    SettingsDialog *_settingsDialog;
};

#endif // MAINWINDOW_H
