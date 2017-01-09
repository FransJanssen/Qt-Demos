#pragma once
#include <QObject>

class QTcpSocket;

namespace Ps{
    class InstSocket : public QObject
    {
        Q_OBJECT
    public:
        explicit InstSocket(QObject *parent=0);
        ~InstSocket();

        bool Connect();
        bool IsOpen();
        void Disconnect();

        QString hostName() const;
        void setHostName(const QString &hostName);

        quint16 port() const;
        void setPort(const quint16 &port);

        int longWaitMs() const;
        void setLongWaitMs(int longWaitMs);

        int shortWaitMs() const;
        void setShortWaitMs(int shortWaitMs);

        QString readData() const;
        void writeData(const QString &data) const;

    signals:
        void NotifyConnected();
        void NotifyDisconnected();

    private slots:
        void onConnected();
        void onDisconnected();

    private:
        QTcpSocket& m_socket;
        QString m_hostName;
        quint16 m_port;
        int m_longWaitMs;
        int m_shortWaitMs;

        explicit InstSocket(const InstSocket& rhs) = delete;
        InstSocket& operator= (const InstSocket& rhs) = delete;
    };
}


