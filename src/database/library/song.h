#ifndef SONG_H
#define SONG_H

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QtGlobal>
#include "src/global.h"

namespace DB
{

class Song : public QObject
{
    Q_OBJECT
public:
    Song(QObject *parent = 0);
    Song(quint64 id, QByteArray name, QByteArray file, quint32 time, quint16 trackNumber,
                  quint16 discNumber, quint64 album, quint64 artist, QObject *parent = 0);
    ~Song();

    void setId(quint64 id);
    quint64 getId() const { return id; }

    void setName(QString name);
    void setName(QByteArray name);
    QString getName() const { return QString::fromUtf8(name); }
    QByteArray getNameByteArray() const { return this->name; }

    const QByteArray &getFile() const { return file; }
    void setFile(const QByteArray &value);

    void setAlbum(quint64 album);
    quint64 getAlbum() const { return this->album; }

    void setTime(quint32 time);
    quint32 getTime() const { return time; }

    void setTrackNumber(quint16 trackNumber);
    quint16 getTrackNumber() const { return trackNumber; }

    void setDiscNumber(quint16 discNumber);
    quint16 getDiscNumber() const { return discNumber; }

    void setArtist(quint64 artist);
    quint64 getArtist() const { return artist; }

    bool operator==(const Song &s) const { return this->id == s.id; }
    bool operator!=(const Song &s) const { return !( *this == s); }

private:

    quint64 id;
    QByteArray name;
    QByteArray file;
    quint32 time;
    quint16 trackNumber;
    quint16 discNumber;
    quint64 album;
    quint64 artist;
    
signals:
    void songDeleted(Song *s);

public slots:
};

}
#endif // SONG_H
