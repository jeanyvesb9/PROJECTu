#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QtGlobal>
#include <QList>
#include "song.h"

namespace Database
{

class Playlist : public QObject
{
    Q_OBJECT
public:
    Playlist(QObject *parent = 0);
    Playlist(quint32 id, QString name, QObject *parent = 0);
    ~Playlist();

    void setId(quint32 id);
    quint32 getId() const { return id; }

    void setName(QString name);
    void setName(QByteArray name);
    QString getName() const {return QString::fromUtf8(name); }
    QByteArray getNameByteArray() const { return this->name; }

    void setSongList(QList<quint64> songs);
    const QList<quint64> *getSongList() const { return &songList; }
    void addSong(qint16 possition, quint64 song);
    void removeSong(qint16 possition);
    void moveSong(qint16 from, qint16 to);

    bool operator==(const Playlist &p) const { return this->id == p.id; }
    bool operator!=(const Playlist &p) const { return !( *this == p); }

private:
    quint32 id;
    QByteArray name;
    QList<quint64> songList;

signals:
    void playlistDeleted(Playlist*);

public slots:
};

}
#endif // PLAYLIST_H
