#include "axCore/axCrashHandler/CrashHandler.h"
#include <QDebug>
#include <QCoreApplication>
#include <iostream>
 
int buggyFunc()
{
    delete reinterpret_cast<QString*>(0xFEE1DEAD);
    return 0;
}
 
int main(int argc, char * argv[])
{
    qDebug() << "App start";
    QCoreApplication app(argc, argv);
 
#if defined(Q_OS_WIN32)
    Atomix::CrashHandler::instance()->Init("c:\\dump");
#elif defined(Q_OS_LINUX)
    Atomix::CrashHandler::instance()->Init("/Users/dev/dump");
#elif defined(Q_OS_MAC)
    Atomix::CrashHandler::instance()->Init("/Users/User/dump");
#endif
 
    qDebug() << "CrashHandlerSet";
    buggyFunc();
    return 0;
}