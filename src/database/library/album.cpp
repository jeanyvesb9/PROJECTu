#include "src/database/album.h"

using namespace Database;

Album::Album(QObject *parent)
    :QObject(parent)
{

}

Album::Album(quint64 id, QByteArray name, quint64 albumArtist, bool uniqueArtist,
             bool multipleDisc, QObject *parent)
    :QObject {parent}, id{id}, name{name}, albumArtist{albumArtist}, albumLenght{0},
      uniqueArtist{uniqueArtist}, multipleDisc{multipleDisc}
{

}

Album::~Album()
{
    emit albumDeleted(this);
}

void Album::setId(quint64 id)
{
    this->id = id;
}

void Album::setName(QString name)
{
    this->name = name.toUtf8();
}

void Album::setName(QByteArray name)
{
    this->name = name;
}

void Album::setAlbumArtist(quint64 albumArtist)
{
    this->albumArtist = albumArtist;
}

void Album::setSongList(QMap<quint16, QMap<quint16, quint64> > songs)
{
    this->songList = songs;
}

quint16 Album::getSongListLenght() const
{
    quint16 len = 0;
    for(auto cd : songList)
    {
        for(auto song : cd)
        {
            Q_UNUSED(song);
            len++;
        }
    }
    return len;
}

void Album::addSong(quint16 disc, quint16 possition, quint64 songNumber)
{
    this->songList[disc][possition] = songNumber;
}

void Album::removeSong(quint16 disc, quint16 possition)
{
    this->songList[disc].remove(possition);
}

void Album::moveSong(quint16 discFrom, quint16 from, quint16 discTo, quint16 to)
{
    quint32 temp = songList.value(discFrom).value(from);
    songList[discFrom].remove(from);
    songList[discTo][to] = temp;
}

void Album::setAlbumLenght(quint32 lenght)
{
    this->albumLenght = lenght;
}
void Album::setUniqueArtist(bool value)
{
    uniqueArtist = value;
}
void Album::setYear(const quint16 &value)
{
    year = value;
}
void Album::setMultipleDisc(bool value)
{
    multipleDisc = value;
}
