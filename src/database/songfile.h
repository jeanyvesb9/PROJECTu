#ifndef SONGFILE_H
#define SONGFILE_H

#include <QObject>
#include <QFileInfo>
#include <QImage>
#include <cstring>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/mp4file.h>
#include <taglib/id3v2tag.h>
#include <taglib/mpegfile.h>
#include <taglib/attachedpictureframe.h>
#include <taglib/textidentificationframe.h>

namespace BackEnd {

enum class FileType { Null = 0, M4A, MP3, FLAC, AAC, WAV};

class SongFile
{
public:
    SongFile(QString url);
    ~SongFile();

    QString getName();
    QString getAlbum();
    QString getArtist();
    QString getAlbumArtist();
    quint16 getTrackNumber();
    quint16 getDiskNumber();
    quint32 getTime();
    QString getGenre();
    quint16 getYear();
    QImage getArtwork();
    QString getFile();
    FileType getFileType();

    void setName(QString name);
    void setAlbum(QString album);
    void setArtist(QString artist);
    void setAlbumArtist(QString albumArtist);
    void setTrackNumber(quint16 trackNumber);
    void setDiskNumber(quint16 diskNumber);
    void setGenre(QString genre);
    void setYear(quint16 year);

private:
    QString url;
    FileType fileType;
    TagLib::MP4::File *MP4File;
    TagLib::MP4::Tag *MP4Tag;
    TagLib::MPEG::File *MPEGFile;
    TagLib::ID3v2::Tag *ID3v2Tag;

};

}

#endif // SONGFILE_H
