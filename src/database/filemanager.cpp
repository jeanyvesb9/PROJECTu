#include "filemanager.h"

using namespace BackEnd;

FileManager::FileManager(QObject *parent) : QObject(parent)
{

}

QString FileManager::getSearchDirectory() const
{
    return searchDirectory;
}

void FileManager::setSearchDirectory(const QString &value)
{
    mutex.lock();
    searchDirectory = value;
    mutex.unlock();
}

QStringList FileManager::getFileFormats() const
{
    return fileFormats;
}

void FileManager::setFileFormats(const QStringList &value)
{
    mutex.lock();
    fileFormats = value;
    mutex.unlock();
}

bool FileManager::getRecursive() const
{
    return recursive;
}

void FileManager::setRecursive(bool value)
{
    mutex.lock();
    recursive = value;
    mutex.unlock();
}

bool FileManager::getCheckDB() const
{
    return checkDB;
}

void FileManager::setCheckDB(bool value)
{
    mutex.lock();
    checkDB = value;
    mutex.unlock();
}

void FileManager::setLibrary(QSharedPointer<DB::Library> lib)
{
    mutex.lock();
    library = lib;
    mutex.unlock();
}

bool FileManager::parseDir(QString url)
{
    QDir current(url);
    if(!current.isReadable())
    {
        return false;
    }

    QFileInfoList fileList = current.entryInfoList(fileFormats, QDir::Files | QDir::Readable);

    //DO GENRES
    QList<SongExtraMetadata> metaList;
    QList<QSharedPointer<DB::Song>> songList;


    for(QFileInfo file : fileList)
    {
        SongExtraMetadata meta;
        QSharedPointer<DB::Song>song = parseFile(file.absoluteFilePath(), &meta);
        if(!song.isNull())
        {
            DB::Item_ID id = DB::Item_ID::fromHash(song->getFile());
            song->setId(id.to64bitID());
            metaList.append(meta);
            songList.append(song);
        }
    }

    if(recursive)
    {
        QFileInfoList dirList = current.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::Readable);
        for(QFileInfo file : dirList)
        {
            parseDir(file.absoluteFilePath());
        }
    }
    return true;


}

QSharedPointer<DB::Song> FileManager::parseFile(QString url, SongExtraMetadata *meta)
{
    QFileInfo fileInfo(url);
    if(!fileInfo.isReadable())
    {
        return QSharedPointer<DB::Song>(nullptr);
    }

    if(fileInfo.suffix() == "m4a")
    {
        TagLib::MP4::File file(url.toStdWString().data());
        if(!file.isValid())
        {
            return QSharedPointer<DB::Song>(nullptr);
        }

        QSharedPointer<DB::Song> song(new DB::Song());
        TagLib::MP4::Tag *tag = file.tag();
        song->setName(QString::fromWCharArray(tag->title().toCWString()).toUtf8());
        song->setTrackNumber(tag->track());
        song->setTime(file.length());
        song->setFile(url.toUtf8());
        meta->album.append(QString::fromWCharArray(tag->album().toCWString()));
        meta->artist.append(QString::fromWCharArray(tag->artist().toCWString()));
        meta->genre.append(QString::fromWCharArray(tag->genre().toCWString()));
        meta->year = tag->year();

        if(tag->contains("aART")) //Album Artist
        {
            TagLib::StringList albumArtist = tag->item("aART").toStringList();
            if(albumArtist.front().size() != 0)
            {
                meta->albumArtist.append(QString::fromWCharArray(albumArtist.front().toCWString()));
            }
            else
            {
                meta->albumArtist.append("");
            }
        }
        else
        {
            meta->albumArtist.append("");
        }

        if(tag->itemListMap().contains("disk")) //Disc Number
        {
            int cd = tag->itemListMap()["disk"].toIntPair().first;
            if(cd < 1)
                cd = 1;
            song->setDiscNumber(cd);
        }
        else
        {
            song->setDiscNumber(1);
        }

        return song;
    }

    else if(fileInfo.suffix() == "mp3")
    {
        TagLib::MPEG::File file(url.toStdWString().data());
        if(!file.isValid())
        {
            return QSharedPointer<DB::Song>(nullptr);
        }

        QSharedPointer<DB::Song> song(new DB::Song());
        TagLib::ID3v2::Tag *tag = file.ID3v2Tag(true);
        song->setName(QString::fromWCharArray(tag->title().toCWString()).toUtf8());
        song->setTrackNumber(tag->track());
        song->setTime(file.length());
        song->setFile(url.toUtf8());
        meta->album.append(QString::fromWCharArray(tag->album().toCWString()));
        meta->artist.append(QString::fromWCharArray(tag->artist().toCWString()));
        meta->genre.append(QString::fromWCharArray(tag->genre().toCWString()));
        meta->year = tag->year();

        if(!tag->frameList("TPE2").isEmpty()) //Album Artist
        {
            TagLib::ID3v2::FrameList albumArtist = tag->frameList("TPE2");
            if(albumArtist.front()->size() != 0)
            {
                meta->albumArtist.append(QString::fromWCharArray(albumArtist.front()->toString().toCWString()));
            }
            else
            {
                meta->albumArtist.append("");
            }
        }
        else
        {
            meta->albumArtist.append("");
        }



        return song;
    }

    return QSharedPointer<DB::Song>(nullptr);
}

void FileManager::private_startSearch()
{
    parseDir(searchDirectory);
}
