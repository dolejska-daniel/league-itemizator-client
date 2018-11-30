#include "dataapi.h"
#include <QtNetwork>


DataApi::DataApi()
{
    _nam = new QNetworkAccessManager();
}

DataApi::~DataApi()
{
    delete _nam;
}


//======================================================================dd==
//  VERSION ENDPOINT
//======================================================================dd==

QString DataApi::GetCurrentDataVersion()
{
    auto data = MakeCall(CreateRequest("/version/data"));
    return data["data"].toString();
}

QString DataApi::GetCurrentProgramVersion()
{
    auto data = MakeCall(CreateRequest("/version/program"));
    return data["data"].toString();
}


//======================================================================dd==
//  DATA ENDPOINT
//======================================================================dd==



//======================================================================dd==
//  CORE REQUEST FUNCTIONS
//======================================================================dd==

QNetworkRequest DataApi::CreateRequest(QString endpoint, std::map<QString, QString> params)
{
    auto request = QNetworkRequest();
    endpoint+= "?";
    for (auto param: params)
        endpoint+= param.first + "=" + param.second;
    request.setUrl(_baseUrl + endpoint);
    //request.setAttribute("", "");
    return request;
}

QJsonObject DataApi::MakeCall(QNetworkRequest request)
{
    QNetworkReply *reply = _nam->get(request);
    while(!reply->isFinished())
        qApp->processEvents();

    auto dataDocument = QJsonDocument::fromJson(reply->readAll());
    reply->deleteLater();

    return dataDocument.object();
}
