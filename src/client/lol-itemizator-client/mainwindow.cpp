#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtNetwork>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QNetworkAccessManager net;
    QNetworkRequest request(QUrl(""));
    QNetworkReply *reply = net.get(request);

    while(!reply->isFinished())
        qApp->processEvents();

    QByteArray response_data = reply->readAll();
    QJsonDocument dataDocument = QJsonDocument::fromJson(response_data);
    QJsonObject data = dataDocument.object();

    this->statusBar()->showMessage(data["success"].toString());

    reply->deleteLater();
}

MainWindow::~MainWindow()
{
    delete ui;
}
