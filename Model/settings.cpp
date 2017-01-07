#include "settings.h"

#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QMessageBox>
#include <QString>
#include <QStringListModel>

#include <utility>

namespace Ps
{
    static auto RESOURCE_PREFIX = QStringLiteral(":/json");

    Settings::Settings(QObject *parent, QString filename) :
        QObject(parent),
        m_filename (filename),
        m_modelCommands (*new QStringListModel(this))
    {
    }

    void Settings::ParseJsonData()
    {
        QString raw_json = ReadJsonFile();

        if (0 == raw_json.size())
        {
            return;
        }

        auto json_result = GetJsonObject(raw_json);
        auto json_err = json_result.second; // json_parse_error

        if (json_err.error != QJsonParseError::NoError)
        {
            ShowJsonParseError(json_err);
        }

        auto json_obj = json_result.first; // jsob_obj

        m_applicationName = json_obj["applicationName"].toString();
        m_appShortName = json_obj["appShortName"].toString();
        m_hostName = json_obj["hostName"].toString();
        m_portNumber = json_obj["port"].toInt();
        m_waitMs = json_obj["tcpLongWaitMs"].toInt();
        m_readWaitMs = json_obj["tcpShortWaitMs"].toInt();

        SetupCommands(json_obj);
    }

    JsonObjErrorPair Settings::GetJsonObject(const QString& rawJson)
    {
        QJsonParseError json_parse_error;
        QJsonDocument json_doc = QJsonDocument::fromJson(rawJson.toUtf8(), &json_parse_error);
        QJsonObject json_obj = json_doc.object();

        return std::make_pair(json_obj, json_parse_error);
    }

    QString Settings::ReadJsonFile()
    {
        auto default_settings = ReadJsonFromInternalResource();

        return default_settings;
    }

    QString Settings::ReadJsonFromInternalResource()
    {
        QDir res_dir (RESOURCE_PREFIX);

        if (!res_dir.exists())
        {
            SendErrorMessage("Internal resource path missing " + res_dir.canonicalPath());

            return "";
        }

        auto path = res_dir.filePath(m_filename);

        QFile res_file(path);

        if (!res_file.open(QFile::ReadOnly | QFile::Text))
        {
            SendErrorMessage("Could not open internal resource " + path);

            return "";
        }

        QString settings = res_file.readAll();

        return settings;
    }

    void Settings::SetupCommands(QJsonObject json_obj)
    {
        QJsonArray cmd_array = json_obj["commands"].toArray();
        QStringList cmd_list;

        for(auto item: cmd_array)
        {
            cmd_list.append(item.toString());
        }
        m_modelCommands.setStringList(cmd_list);
    }

    void Settings::ShowJsonParseError(QJsonParseError jsonError)
    {
        QString msg = tr("Error parsing Json settings file.\n");
        msg.append(jsonError.errorString());
        QMessageBox::critical(0, tr("VFP"), msg);
    }

    void Settings::SendErrorMessage(const QString& msg)
    {
        emit NotifyStatusMessage(msg);
    }
}
