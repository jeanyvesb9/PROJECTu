#include <QCoreApplication>
#include <QDebug>
#include <QThread>
#include <QObject>
#include "src/database/filemanager.h"
#include "src/database/filemanagerdb.h"

namespace The
{
    QThread *fileTrackerThread = new QThread();
    BackEnd::FileManager *fileTracker = new BackEnd::FileManager();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    The::fileTracker->moveToThread(The::fileTrackerThread);

    QObject::connect(The::fileTrackerThread, &QThread::started,
                     The::fileTracker, &BackEnd::FileManager::private_startSearch);
    QObject::connect(The::fileTracker, &BackEnd::FileManager::private_finished,
                     The::fileTrackerThread, &QThread::quit);

    The::fileTracker->setSearchDirectory("E:/iTunes/iTunes Media/Music");
    The::fileTracker->setRecursive(true);
    The::fileTracker->setFileFormats({"*.m4a", "*.mp3"});
    The::fileTrackerThread->start();

    return a.exec();
}
