#ifndef ARTIST_H
#define ARTIST_H

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QtGlobal>

namespace Database
{

class Artist : public QObject
{
    Q_OBJECT
public:
    Artist(QObject *parent = 0);
    Artist(quint64 id, QByteArray name, bool albumArtist = 1, QObject *parent = 0);
    ~Artist();

    void setId(quint64 id);
    quint64 getId() const { return id; }

    void setAlbumArtist(bool albumArtist);
    bool getAlbumArtist() const { return albumArtist; }

    void setName(QString name);
    void setName(QByteArray name);
    QString getName() const { return QString::fromUtf8(name); }
    QByteArray getNameByteArray() const { return this->name; }

    void setAlbumList(QList<quint64> albums);
    const QList<quint64> *getAlbumList() const { return &albumList; }
    void addAlbum(quint16 possition, quint64 albumNumber);
    void appendAlbum(quint64 albumNumber);
    void removeAlbum(quint16 possition);
    void moveAlbum(quint16 from, quint16 to);

    bool operator==(const Artist &a) const { return this->id == a.id; }
    bool operator!=(const Artist &a) const { return !( *this == a); }

private:
    quint64 id;
    bool albumArtist;
    QByteArray name;
    QList<quint64> albumList;

signals:
    void artistDeleted(Artist *artist);

public slots:
};

}

#endif // ARTIST_H
