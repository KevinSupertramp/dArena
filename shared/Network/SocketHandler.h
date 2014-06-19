#ifndef SOCKETREADER_H
#define SOCKETREADER_H

#include <QtNetwork>
#include <QTcpSocket>
#include "Packets/WorldPacket.h"
#include "Opcodes/Opcodes.h"

class WorldPacket;

class SocketHandler : public QObject
{
    Q_OBJECT
public:
    SocketHandler(QTcpSocket* socket);

    QString GetIp() const { return m_socket->peerAddress().toString(); }

    virtual void ProcessPacket() = 0;
    void SendPacket(WorldPacket& data);

public slots:
    void OnRead();
    void OnDisconnect();

    virtual void OnClose();
    virtual void OnError(QAbstractSocket::SocketError error);

protected:
    QTcpSocket* m_socket;
    quint16 m_packetSize;
};

#endif // SOCKETREADER_H
