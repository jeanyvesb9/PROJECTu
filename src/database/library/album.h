#ifndef ALBUM_H
#define ALBUM_H

#include <QObject>
#include <QtDebug>
#include <QString>
#include <QSharedPointer>
#include <QByteArray>
#include <QtGlobal>
#include <QMap>
#include <QImage>

namespace Database
{

class Album : public QObject
{
    Q_OBJECT
public:
    Album(QObject *parent = 0);
    Album(quint64 id, QByteArray name, quint64 albumArtist, bool uniqueArtist = 1, bool multipleDisc = 0, QObject *parent = 0);
    ~Album();

    void setId(quint64 id);
    quint64 getId() const { return id; }

    void setName(QString name);
    void setName(QByteArray name);
    QString getName() const { return QString::fromUtf8(name); }
    QByteArray getNameByteArray() const { return this->name; }

    void setAlbumArtist(quint64 albumArtist);
    quint64 getAlbumArtist() const { return albumArtist; }

    void setSongList(QMap<quint16, QMap<quint16, quint64> > songs);
    const QMap<quint16, QMap<quint16, quint64> > *getSongList() const { return &songList; }
    quint16 getSongListLenght() const;
    void addSong(quint16 disc, quint16 possition, quint64 songNumber);
    void removeSong(quint16 disc, quint16 possition);
    void moveSong(quint16 discFrom, quint16 from, quint16 discTo, quint16 to);

    void setAlbumLenght(quint32 lenght);
    quint32 getAlbumLenght() const { return albumLenght; }
    void reduceAlbumLenght(quint32 lenght) { this->albumLenght -= lenght; }
    void increaseAlbumLenght(quint32 lenght) { this->albumLenght += lenght; }

    bool operator==(const Album &a) const { return this->id == a.id; }
    bool operator!=(const Album &a) const { return !( *this == a); }
    
    void setUniqueArtist(bool value);
    bool getUniqueArtist() { return this->uniqueArtist; }

    void setYear(const quint16 &value);
    quint16 getYear() const { return this->year; }

    void setMultipleDisc(bool value);
    bool getMultipleDisc() const { return this->multipleDisc; }

private:
    quint64 id;
    QByteArray name;
    quint64 albumArtist;
    quint32 albumLenght;
    bool uniqueArtist;
    bool multipleDisc;
    quint16 year;
    QMap<quint16, QMap<quint16, quint64> > songList;

signals:
    void albumDeleted(Album *a);

public slots:
};

}

#endif // ALBUM_H
