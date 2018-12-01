#ifndef ITEMSETAPI_H
#define ITEMSETAPI_H
#include <QDir>
#include <QFile>
#include <QJsonObject>


class ItemsetApi
{
public:
    ItemsetApi(QDir dir);

    void SaveToFile(QString name, QByteArray data);

protected:
    QDir _dir;
};

#endif // ITEMSETAPI_H
