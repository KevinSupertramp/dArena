#include <QCoreApplication>
#include <csignal>

#include "Logs/Log.h"
#include "Chat/CommandLine.h"
#include "WorldServer.h"

CommandLine* commandLine = new CommandLine;

void stop(int /*s*/)
{
    WorldServer::Instance()->Delete();
    commandLine->exit();
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

    commandLine->start();

    Log::Write(LOG_TYPE_NORMAL, "Press ctrl + c to quit.");
    Log::Write(LOG_TYPE_NORMAL, "dArena started in %s sec.", QString::number(t.elapsed() / IN_MILLISECONDS).toLatin1().data());

    signal(SIGINT, &stop);
    signal(SIGTERM, &stop);
    #ifdef Q_OS_UNIX
        signal(SIGHUP, &stop);
    #elif defined(Q_OS_WIN)
        signal(SIGBREAK, &stop);
    #endif
    return a.exec();
}
