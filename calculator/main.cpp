#include "calculator.h"

#include <QApplication>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QTimer>

QScopedPointer<QFile> logFile;

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // Open stream file writes
    QTextStream out(logFile.data());

    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");

    switch (type)
    {
    case QtInfoMsg:     out << "INF "; break;
    case QtDebugMsg:    out << "DBG "; break;
    case QtWarningMsg:  out << "WRN "; break;
    case QtCriticalMsg: out << "CRT "; break;
    case QtFatalMsg:    out << "FTL "; break;
    }

    out << context.category << ": " << msg  << Qt::endl;
    out.flush();
}

int main(int argc, char *argv[])
{
    logFile.reset(new QFile("./log.txt"));
    logFile.data()->open(QFile::Append | QFile::Text);
    qInstallMessageHandler(messageHandler);

    QApplication::setAttribute(Qt::AA_DisableWindowContextHelpButton);

    QApplication a(argc, argv);
    Calculator w;
    w.show();
    return a.exec();
}
