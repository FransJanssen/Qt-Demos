
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

        QString applicationName() const;
        void setApplicationName(const QString &applicationName);

        QString appShortName() const;
        void setAppShortName(const QString &appShortName);

        QString hostName() const;
        void setHostName(const QString &hostName);

        quint16 portNumber() const;
        void setPortNumber(const quint16 &portNumber);

        int waitMs() const;
        void setWaitMs(int waitMs);

        int readWaitMs() const;
        void setReadWaitMs(int readWaitMs);

        QStringListModel &modelCommands() const;

    signals:
        void NotifyStatusMessage(QString message);

    private:
        QString m_filename;
        QString m_applicationName;
        QString m_appShortName;
        QString m_hostName;
        quint16 m_portNumber;
        int m_longWaitMs;
        int m_shotWaitMs;
        QStringListModel& m_modelCommands;

        QString ReadJsonFile();
        QString ReadJsonFromInternalResource();

        void SendErrorMessage(const QString &msg);
        JsonObjErrorPair GetJsonObject(const QString &rawJson);
        void ShowJsonParseError(QJsonParseError jsonError);
        void SetupCommands(QJsonObject json_obj);
        QDir OpenConfigDirectory();
        void WriteDefaultsToStdConfigFile(QFile &stdConfigFile, const QString &Settings);

        explicit Settings(const Settings& rhs) = delete;
        Settings& operator= (const Settings& rhs) = delete;

    };
}


