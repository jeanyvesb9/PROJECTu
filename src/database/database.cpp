#include "database.h"

Database::Database(QObject *parent) : QObject(parent),
  fileManagerThread{nullptr}
{
//    fileManager->moveToThread(fileManagerThread);
//    QObject::connect(fileManagerThread, &QThread::started,
//                     fileManager, &BackEnd::FileManager::private_startSearch);
//    QObject::connect(fileManager, &BackEnd::FileManager::private_finished,
//                     fileManagerThread, &QThread::quit);
}

Database::~Database()
{

}

