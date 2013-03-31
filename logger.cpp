#include "logger.h"
#include <QDebug>
#include <QTime>
Logger::Logger() : loggingFile("informative.log"), loggingStream(&loggingFile)
{
	loggingFile.open(QIODevice::Append | QIODevice::WriteOnly);
	writeLine("Started up...");
}

void Logger::writeLine(QString ln) {
    QString out(QString("[%1]: %2").arg(QTime::currentTime().toString("hh:mm:ss.zzz AP")).arg(ln));
    loggingStream << out << '\r' << endl;
    qDebug() << out;
}

Logger::~Logger() {
}
