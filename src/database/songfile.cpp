#include "songfile.h"

using namespace BackEnd;

SongFile::SongFile(QString url)
    :MP4File{nullptr}, MP4Tag{nullptr}, MPEGFile{nullptr}, ID3v2Tag{nullptr}
{
    QFileInfo fileInfo(url);
    if(!fileInfo.isReadable())
    {
        this->fileType = FileType::Null;
        return;
    }

    if(fileInfo.suffix() == "m4a")
    {
        this->MP4File = new TagLib::MP4::File(url.toStdWString().data());
        if(!this->MP4File->isValid())
        {
            this->fileType = FileType::Null;
            return;
        }
        else
        {
            this->fileType = FileType::M4A;
            this->MP4Tag = this->MP4File->tag();
        }
    }

    else if(fileInfo.suffix() == "mp3")
    {
        this->MPEGFile = new TagLib::MPEG::File(url.toStdWString().data());
        if(!this->MPEGFile->isValid())
        {
            this->fileType = FileType::Null;
            return;
        }
        else
        {
            this->fileType = FileType::MP3;
            this->ID3v2Tag = this->MPEGFile->ID3v2Tag(true);
        }
    }
    else
    {
        this->fileType = FileType::Null;
        return;
    }
}

BackEnd::SongFile::~SongFile()
{
    if(this->MP4File)
        delete this->MP4File;
    if(this->MP4Tag)
        delete this->MP4Tag;
    if(this->MPEGFile)
        delete this->MPEGFile;
    if(this->ID3v2Tag)
        delete this->ID3v2Tag;
}

QString BackEnd::SongFile::getName()
{
    if(this->fileType == FileType::M4A)
    {
        return QString::fromWCharArray(this->MP4Tag->title().toCWString());
    }

    else if(this->fileType == FileType::MP3)
    {
        return QString::fromWCharArray(this->ID3v2Tag->title().toCWString());
    }

    else
    {
        return QString("NULLFILE");
    }
}

QString BackEnd::SongFile::getAlbum()
{
    if(this->fileType == FileType::M4A)
    {
        return QString::fromWCharArray(this->MP4Tag->album().toCWString());
    }

    else if(this->fileType == FileType::MP3)
    {
        return QString::fromWCharArray(this->ID3v2Tag->album().toCWString());
    }

    else
    {
        return QString("NULLFILE");
    }
}

QString BackEnd::SongFile::getArtist()
{
    if(this->fileType == FileType::M4A)
    {
        return QString::fromWCharArray(this->MP4Tag->artist().toCWString());
    }

    else if(this->fileType == FileType::MP3)
    {
        return QString::fromWCharArray(this->ID3v2Tag->artist().toCWString());
    }

    else
    {
        return QString("NULLFILE");
    }
}

QString BackEnd::SongFile::getAlbumArtist()
{
    if(this->fileType == FileType::M4A)
    {
        if(this->MP4Tag->contains("aART"))
        {
            TagLib::StringList albumArtist = this->MP4Tag->item("aART").toStringList();
            if(albumArtist.front().size() != 0)
            {
                return QString::fromWCharArray(albumArtist.front().toCWString());
            }
            else
            {
                return QString("");
            }
        }
        else
        {
            return QString("");
        }
    }

    else if(this->fileType == FileType::MP3)
    {
        if(!this->ID3v2Tag->frameList("TPE2").isEmpty())
        {
            TagLib::ID3v2::FrameList albumArtist = this->ID3v2Tag->frameList("TPE2");
            if(albumArtist.front()->size() != 0)
            {
                return QString::fromWCharArray(albumArtist.front()->toString().toCWString());
            }
            else
            {
                return QString("");
            }
        }
        else
        {
            return QString("");
        }
    }

    else
    {
        return QString("NULLFILE");
    }
}

quint16 BackEnd::SongFile::getTrackNumber()
{
    if(this->fileType == FileType::M4A)
    {
        return this->MP4Tag->track();
    }

    else if(this->fileType == FileType::MP3)
    {
        return this->ID3v2Tag->track();
    }

    else
    {
        return 0;
    }
}

quint16 BackEnd::SongFile::getDiskNumber()
{
    if(this->fileType == FileType::M4A)
    {
        if(this->MP4Tag->itemListMap().contains("disk"))
        {
            int cd = this->MP4Tag->itemListMap()["disk"].toIntPair().first;
            return cd < 1? 1 : cd;
        }
        else
        {
            return 1;
        }
    }

    else if(this->fileType == FileType::MP3)
    {
        if(!this->ID3v2Tag->frameList("TPOS").isEmpty())
        {
            TagLib::ID3v2::FrameList discNumber = this->ID3v2Tag->frameList("TPOS");
            if(discNumber.front()->size() != 0)
            {
                int cd = discNumber.front()->toString().split('/')[0].toInt();
                return cd < 1? 1 : cd;
            }
            else
            {
                return 1;
            }
        }
        else
        {
            return 1;
        }
    }

    else
    {
        return 0;
    }
}

quint32 BackEnd::SongFile::getTime()
{
    if(this->fileType == FileType::M4A)
    {
        return this->MP4File->length();
    }

    else if(this->fileType == FileType::MP3)
    {
        return this->MPEGFile->length();
    }

    else
    {
        return 0;
    }
}

QString BackEnd::SongFile::getGenre()
{
    if(this->fileType == FileType::M4A)
    {
        return QString::fromWCharArray(this->MP4Tag->genre().toCWString());
    }

    else if(this->fileType == FileType::MP3)
    {
        return QString::fromWCharArray(this->ID3v2Tag->genre().toCWString());
    }

    else
    {
        return QString("NULLFILE");
    }
}

quint16 BackEnd::SongFile::getYear()
{
    if(this->fileType == FileType::M4A)
    {
        return this->MP4Tag->year();
    }

    else if(this->fileType == FileType::MP3)
    {
        return this->ID3v2Tag->year();
    }

    else
    {
        return 0;
    }
}

QImage BackEnd::SongFile::getArtwork()
{
    if(this->fileType == FileType::M4A)
    {
        TagLib::MP4::ItemListMap map = this->MP4Tag->itemListMap();
        TagLib::MP4::Item coverItem = map["covr"];
        TagLib::MP4::CoverArtList coverArtList = coverItem.toCoverArtList();
        if(!coverArtList.isEmpty())
        {
            TagLib::MP4::CoverArt coverArt = coverArtList.front();
            return QImage::fromData(QByteArray::fromRawData(coverArt.data().data(),
                                                            coverArt.data().size()));
        }
        else
        {
            return QImage();
        }
    }

    else if(this->fileType == FileType::MP3)
    {
        TagLib::ID3v2::FrameList frames = this->ID3v2Tag->frameList("APIC");
        if(!frames.isEmpty())
        {
            TagLib::ID3v2::AttachedPictureFrame *frame =
                    static_cast<TagLib::ID3v2::AttachedPictureFrame*>(frames.front());
            return QImage::fromData(QByteArray::fromRawData(frame->picture().data(),
                                                            frame->picture().size()));
        }
        else
        {
            return QImage();
        }
    }

    else if(this->fileType == FileType::FLAC)
    {
//        TagLib::FLAC::File file = File("myfile.flac");
//        const TagLib::List<TagLib::FLAC::Picture*>& picList = file.pictureList();
//        TagLib::FLAC::Picture* pic = picList[0];
        return QImage();
    }

    else
    {
        return QImage();
    }
}

QString BackEnd::SongFile::getFile()
{
    return this->url;
}

BackEnd::FileType BackEnd::SongFile::getFileType()
{
    return this->fileType;
}

void SongFile::setName(QString name)
{
    if(this->fileType == FileType::M4A)
    {
        this->MP4Tag->setTitle(TagLib::String(name.toStdWString()));
    }

    else if(this->fileType == FileType::MP3)
    {
        this->ID3v2Tag->setTitle(TagLib::String(name.toStdWString()));
    }

    else
    {
        return;
    }
}

void SongFile::setAlbum(QString album)
{
    if(this->fileType == FileType::M4A)
    {
        this->MP4Tag->setAlbum(TagLib::String(album.toStdWString()));
    }

    else if(this->fileType == FileType::MP3)
    {
        this->ID3v2Tag->setAlbum(TagLib::String(album.toStdWString()));
    }

    else
    {
        return;
    }}

void SongFile::setArtist(QString artist)
{
    if(this->fileType == FileType::M4A)
    {
        this->MP4Tag->setArtist(TagLib::String(artist.toStdWString()));
    }

    else if(this->fileType == FileType::MP3)
    {
        this->ID3v2Tag->setArtist(TagLib::String(artist.toStdWString()));
    }

    else
    {
        return;
    }
}

void SongFile::setAlbumArtist(QString albumArtist)
{
    if(this->fileType == FileType::M4A)
    {
        this->MP4Tag->itemListMap()["aART"] = TagLib::StringList(
                                              TagLib::String(albumArtist.toStdWString()));
        this->MP4Tag->save();
    }

    else if(this->fileType == FileType::MP3)
    {
        TagLib::ByteVector handle = "TPE2";
        TagLib::String value(albumArtist.toStdWString());

        if(this->ID3v2Tag->frameListMap().contains(handle) &&
           !this->ID3v2Tag->frameListMap()[handle].isEmpty())
        {
            this->ID3v2Tag->frameListMap()[handle].front()->setText(value);
        }
        else
        {
            TagLib::ID3v2::TextIdentificationFrame *frame =
                new TagLib::ID3v2::TextIdentificationFrame(handle,
                    TagLib::ID3v2::FrameFactory::instance()->defaultTextEncoding());
            frame->setText(value);
            this->ID3v2Tag->addFrame(frame);

            //CHECK: MIGHT HAVE TO DELETE FRAME POINTER
        }
        this->MPEGFile->save();
    }

    else
    {
        return;
    }
}

void SongFile::setTrackNumber(quint16 trackNumber)
{
    if(this->fileType == FileType::M4A)
    {
        this->MP4Tag->setTrack(trackNumber);
    }

    else if(this->fileType == FileType::MP3)
    {
        this->ID3v2Tag->setTrack(trackNumber);
    }

    else
    {
        return;
    }
}

void SongFile::setDiskNumber(quint16 diskNumber)
{
    if(this->fileType == FileType::M4A)
    {
        this->MP4Tag->itemListMap()["disk"] = TagLib::MP4::Item(diskNumber, 0);
        this->MP4Tag->save();
    }

    else if(this->fileType == FileType::MP3)
    {
        TagLib::ByteVector handle = "TPOS";
        TagLib::String value(QString::number(diskNumber).toStdWString());

        if(this->ID3v2Tag->frameListMap().contains(handle) &&
                !this->ID3v2Tag->frameListMap()[handle].isEmpty())
        {
            this->ID3v2Tag->frameListMap()[handle].front()->setText(value);
        }
        else
        {
            TagLib::ID3v2::TextIdentificationFrame *frame =
                    new TagLib::ID3v2::TextIdentificationFrame(handle,
                                                               TagLib::ID3v2::FrameFactory::instance()->defaultTextEncoding());
            frame->setText(value);
            this->ID3v2Tag->addFrame(frame);

            //CHECK: MIGHT HAVE TO DELETE FRAME POINTER
        }
    this->MPEGFile->save();
    }

    else
    {
        return;
    }
}

void SongFile::setGenre(QString genre)
{
    if(this->fileType == FileType::M4A)
    {
        this->MP4Tag->setGenre(TagLib::String(genre.toStdWString()));
    }

    else if(this->fileType == FileType::MP3)
    {
        this->ID3v2Tag->setGenre(TagLib::String(genre.toStdWString()));
    }

    else
    {
        return;
    }
}

void SongFile::setYear(quint16 year)
{
    if(this->fileType == FileType::M4A)
    {
        this->MP4Tag->setYear(year);
    }

    else if(this->fileType == FileType::MP3)
    {
        this->ID3v2Tag->setYear(year);
    }

    else
    {
        return;
    }
}
