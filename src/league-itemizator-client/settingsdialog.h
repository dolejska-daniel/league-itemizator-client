#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>


namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QSettings *settings, QWidget *parent = nullptr);
    ~SettingsDialog();

private:
    Ui::SettingsDialog *ui;

    QSettings *_settings;
};

#endif // SETTINGSDIALOG_H
