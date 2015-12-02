#include "artist.h"

using namespace DB;

Artist::Artist(QObject *parent)
    :QObject(parent)
{

}

Artist::Artist(quint64 id, QByteArray name, bool albumArtist, QObject *parent)
    : QObject(parent), id{id}, albumArtist{albumArtist}, name{name}
{

}

Artist::~Artist()
{
    emit artistDeleted(this);
}
void Artist::setId(quint64 id)
{
    this->id = id;
}

void Artist::setName(QString name)
{
    this->name = name.toUtf8();
}

void Artist::setName(QByteArray name)
{
    this->name = name;
}

void Artist::setAlbumArtist(bool albumArtist)
{
    this->albumArtist = albumArtist;
}

void Artist::setAlbumList(QList<quint64> albums)
{
    this->albumList = albums;
}

void Artist::addAlbum(quint16 possition, quint64 albumNumber)
{
    this->albumList.insert(possition, albumNumber);
}

void Artist::appendAlbum(quint64 albumNumber)
{
    this->albumList.append(albumNumber);
}

void Artist::removeAlbum(quint16 possition)
{
    this->albumList.removeAt(possition);
}

void Artist::moveAlbum(quint16 from, quint16 to)
{
    this->albumList.move(from, to);
}
