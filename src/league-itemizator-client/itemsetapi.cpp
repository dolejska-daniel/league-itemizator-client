#include "itemsetapi.h"


ItemsetApi::ItemsetApi(QDir dir):
    _dir(dir)
{
}

void ItemsetApi::SaveToFile(QString name, QByteArray data)
{
    QString filename = _dir.filePath(name);
    QFile f(filename);
    f.open(QIODevice::WriteOnly);
    f.write(data);
    f.close();
}
