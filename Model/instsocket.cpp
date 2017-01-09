#include "instsocket.h"
#include "utils.h"

#include <QDebug>
#include <QTcpSocket>

namespace Ps
{
    // Constructor and destructor
    InstSocket::InstSocket(QObject *parent) :
        QObject(parent),
        m_socket(*new QTcpSocket(this)),
        m_hostName(""),
        m_port(0),
        m_longWaitMs(0),
        m_shortWaitMs(0)
    {
        connect(&m_socket, &QTcpSocket::connected, this, &InstSocket::onConnected);
        connect(&m_socket, &QTcpSocket::disconnected, this, &InstSocket::onDisconnected);
    }

    InstSocket::~InstSocket()
    {
        Utils::DestructorMsg(this);
    }

    // Getters and setters
    QString InstSocket::hostName() const
    {
        return m_hostName;
    }

    void InstSocket::setHostName(const QString &hostName)
    {
        m_hostName = hostName;
    }

    quint16 InstSocket::port() const
    {
        return m_port;
    }

    void InstSocket::setPort(const quint16 &port)
    {
        m_port = port;
    }

    int InstSocket::longWaitMs() const
    {
        return m_longWaitMs;
    }

    void InstSocket::setLongWaitMs(int longWaitMs)
    {
        m_longWaitMs = longWaitMs;
    }

    int InstSocket::shortWaitMs() const
    {
        return m_shortWaitMs;
    }

    void InstSocket::setShortWaitMs(int shortWaitMs)
    {
        m_shortWaitMs = shortWaitMs;
    }

    // Other methods
    bool InstSocket::Connect()
    {
        qDebug() << "Attempting to connect to " << m_hostName << " on port " << m_port;
        m_socket.connectToHost(m_hostName, m_port, QTcpSocket::ReadWrite);

        return m_socket.waitForConnected(m_longWaitMs);
    }

    bool InstSocket::IsOpen()
    {
        return m_socket.isOpen();
    }

    void InstSocket::Disconnect()
    {
        if (IsOpen())
        {
            m_socket.disconnectFromHost();
        }
    }

    void InstSocket::writeData(const QString &data) const
    {
        int bytes_written = m_socket.write(qPrintable(data));

        qDebug() << "Bytes written: " << bytes_written;
    }

    QString InstSocket::readData() const
    {
        if (!m_socket.isReadable())
        {
            return "ERROR: Socket is not readable";
        }

        QString result;

        while(!m_socket.atEnd())
        {
            result.append(m_socket.readAll());
            m_socket.waitForReadyRead(m_shortWaitMs);
        }

        return result;
    }

    // Other slots
    void InstSocket::onConnected()
    {
        emit NotifyConnected();
    }

    void InstSocket::onDisconnected()
    {
        emit NotifyDisconnected();
    }

}
