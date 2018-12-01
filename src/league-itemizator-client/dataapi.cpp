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

QPair<int, QString> DataApi::GetCurrentDataVersion()
{
    auto data = MakeCall(CreateRequest("/src/league-itemizator-server/index.php", {{"f", "getDataVersion"}}));
    return {
        data["version"].toInt(),
        data["version_string"].toString(),
    };
}

QPair<int, QString> DataApi::GetCurrentProgramVersion()
{
    auto data = MakeCall(CreateRequest("/src/league-itemizator-server/index.php", {{"f", "getAppVersion"}}));
    return {
        data["version"].toInt(),
        data["version_string"].toString(),
    };
}


//======================================================================dd==
//  DATA ENDPOINT
//======================================================================dd==



//======================================================================dd==
//  CORE REQUEST FUNCTIONS
//======================================================================dd==

QNetworkRequest DataApi::CreateRequest(QString endpoint, std::map<QString, QString> params)
{
    auto url = QUrl();
    url.setUrl(_baseUrl);
    url.setPath(endpoint);

    auto urlQuery = QUrlQuery();
    for (auto param: params)
        urlQuery.addQueryItem(param.first, param.second);
    url.setQuery(urlQuery);

    auto request = QNetworkRequest(url);
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
