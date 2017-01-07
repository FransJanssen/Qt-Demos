
#pragma once
#include <QObject>

class QDir;
class QFile;
class QJsonObject;
class QJsonParseError;
class QString;
class QStringListModel;

namespace Ps{

    typedef std::pair<QJsonObject, QJsonParseError> JsonObjErrorPair;

    class Settings : public QObject
    {
        Q_OBJECT
    public:
        explicit Settings(QObject *parent, QString filename);
        void ParseJsonData();

    signals:
        void NotifyStatusMessage(QString message);

    private:
        QString m_filename;
        QString m_applicationName;
        QString m_appShortName;
        QString m_hostName;
        quint16 m_portNumber;
        int m_waitMs;
        int m_readWaitMs;
        QStringListModel& m_modelCommands;

        QString ReadJsonFile();
        QString ReadJsonFromInternalResource();

        explicit Settings(const Settings& rhs) = delete;
        Settings& operator= (const Settings& rhs) = delete;

        void SendErrorMessage(const QString &msg);
        JsonObjErrorPair GetJsonObject(const QString &rawJson);
        void ShowJsonParseError(QJsonParseError jsonError);
        void SetupCommands(QJsonObject json_obj);
    };
}


