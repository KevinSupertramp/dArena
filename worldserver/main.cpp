#include <QCoreApplication>
#include <csignal>

#include "Logs/Log.h"
#include "Game/Chat/CommandLine.h"

void stop(int /*s*/)
{
    WorldServer::Instance()->Delete();
    QCoreApplication::exit();
}

int close()
{
    stop(0);
    return 0;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTime t;
    t.start();

    Log::Write(LOG_TYPE_NORMAL, "     _                               ");
    Log::Write(LOG_TYPE_NORMAL, "    | |   /\\                         ");
    Log::Write(LOG_TYPE_NORMAL, "  __| |  /  \\   _ __ ___ _ __   __ _ ");
    Log::Write(LOG_TYPE_NORMAL, " / _` | / /\\ \\ | '__/ _ \\ '_ \\ / _` |");
    Log::Write(LOG_TYPE_NORMAL, "| (_| |/ ____ \\| | |  __/ | | | (_| |      Dofus Arena Emulator");
    Log::Write(LOG_TYPE_NORMAL, " \\__,_/_/    \\_\\_|  \\___|_| |_|\\__,_|           by Sgt Fatality");
    Log::Write(LOG_TYPE_NORMAL, " ==============================================================");
    Log::Write(LOG_TYPE_NORMAL, "");

    if (!WorldServer::Instance()->Initialize())
        return close();

    Log::Write(LOG_TYPE_NORMAL, "Press ctrl + c to quit.");
    Log::Write(LOG_TYPE_NORMAL, "dArena started in %s sec.", QString::number(t.elapsed() / IN_MILLISECONDS).toLatin1().data());

    Chat::Instance();
    CommandLine commandLine(&a);
    commandLine.start();

    signal(SIGINT, &stop);
    signal(SIGTERM, &stop);
    #ifdef Q_OS_UNIX
        signal(SIGHUP, &stop);
    #elif defined(Q_OS_WIN)
        signal(SIGBREAK, &stop);
    #endif
    return a.exec();
}
