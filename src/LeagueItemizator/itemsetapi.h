#ifndef ITEMSETAPI_H
#define ITEMSETAPI_H
#include "dataapi.h"
#include <QDir>
#include <QFile>
#include <QJsonObject>


class ItemsetApi
{
public:
    ItemsetApi(QDir installDir, DataApi *api);

    /**
     * @brief Save
     * @param files
     */
    void Save(QJsonArray files);

    /**
     * @brief SaveToFile
     * @param filename
     * @param destination
     * @param data
     */
    void SaveToFile(QString filename, QString destination, QByteArray data);

    /**
     * @brief RemoveAll
     */
    void RemoveAll();

protected:
    QDir _installDir;
    DataApi *_api;
};

#endif // ITEMSETAPI_H
