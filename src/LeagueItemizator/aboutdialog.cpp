#include "mainwindow.h"
#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    ui->labelVersion->setText(APP_VERSION_STRING);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
