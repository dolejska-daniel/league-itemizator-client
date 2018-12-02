#include "itemsetapi.h"
//#include <QtDebug>


ItemsetApi::ItemsetApi(QDir installDir, DataApi *api):
    _installDir(installDir),
    _api(api)
{
}

void ItemsetApi::Save(QJsonArray files)
{
    foreach (auto const& file, files)
    {
        QUrl source = QUrl(file["source"].toString());
        SaveToFile(file["filename"].toString(), file["destination"].toString(), _api->GetFile(source));
        //  TODO: File fails to be created
    }

    //  Find and open ItemSets config file
    QFile config(_installDir.filePath("Config/ItemSets.json"));
    if (!config.open(QIODevice::ReadWrite | QIODevice::Text))
        //  TODO: Failed to open config
        return;

    //  Read and parse file
    auto configData = config.readAll();
    auto configObject = QJsonDocument::fromJson((configData)).object();
    //  Update timestamp
    QJsonValueRef timestamp = configObject.find("timestamp").value();
    timestamp = QDateTime::currentMSecsSinceEpoch();
    //  Save changes
    if (config.write(QJsonDocument(configObject).toJson()) == -1)
        //  TODO: Failed to write changes
        return;

    config.close();
}

void ItemsetApi::SaveToFile(QString filename, QString destination, QByteArray data)
{
    QDir dest(_installDir);
    //  Try entering destination directory
    if (!dest.cd(destination))
    {
        //  Try creating path to destination directory
        if (!dest.mkpath(destination))
            //  TODO: Path failed to be created
            return;
        else
            //  Path was created
            dest.cd(destination);
    }

    QFile f(dest.filePath(filename));
    if (!f.open(QIODevice::WriteOnly))
        //  TODO: File failed to be open
        return;

    if (f.write(data) == -1)
        //  TODO Data failed to be written
        return;

    f.close();
}

void ItemsetApi::RemoveAll()
{
    QDir dir(_installDir);
    if (dir.cd("Config/Champions"))
    {
        QStringList itemsetFilter("itemizator-*");
        foreach (auto champDir, dir.entryList(QDir::Dirs))
        {
            if (dir.cd(champDir + "/Recommended"))
            {
                foreach (auto itemsetFile, dir.entryList(itemsetFilter))
                {
                    QFile f(dir.filePath(itemsetFile));
                    f.remove();
                }
                dir.cd("../../");
            }
        }
    }
}

