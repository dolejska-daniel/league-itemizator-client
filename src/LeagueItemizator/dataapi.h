#ifndef DATAAPI_H
#define DATAAPI_H
#include <map>
#include <QtNetwork>

class DataApi
{
public:
    enum RequestMethod { GET, POST };

    DataApi();
    ~DataApi();


    //======================================================================dd==
    //  VERSION ENDPOINT
    //======================================================================dd==

    /**
     * @brief GetCurrentDataVersion
     * @return current data version
     */
    QPair<int, QString> GetCurrentDataVersion();

    /**
     * @brief GetCurrentProgramVersion
     * @return current program version
     */
    QPair<int, QString> GetCurrentProgramVersion();


    //======================================================================dd==
    //  DATA ENDPOINT
    //======================================================================dd==

    /**
     * @brief GetFileList
     * @return array of file information
     */
    QJsonArray GetFileList();

    /**
     * @brief GetFile
     * @param source
     * @return file data
     */
    QByteArray GetFile(QUrl source);


protected:
    const QString _baseUrl = "http://dev.itemizator.deploy.dolejska.me";

    QNetworkAccessManager *_nam;


    //======================================================================dd==
    //  CORE REQUEST FUNCTIONS
    //======================================================================dd==

    /**
     * @brief CreateRequest
     * @param endpoint
     * @param params
     * @return endpoint request instance
     */
    QNetworkRequest CreateRequest(QString endpoint, std::map<QString, QString> params = {});

    /**
     * @brief CreateRequest
     * @param target
     * @return url request
     */
    QNetworkRequest CreateRequest(QUrl url);

    /**
     * @brief MakeCall
     * @return parsed JSON reply
     */
    QJsonDocument MakeCall(QNetworkRequest request);


};

#endif // DATAAPI_H
