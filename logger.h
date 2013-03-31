#ifndef LOGGER_H
#define LOGGER_H
#include <QFile>
#include <QTextStream>
class Logger
{
	public:
		Logger();
		QFile loggingFile;
		QTextStream loggingStream;
		void writeLine(QString);
		~Logger();
};

#endif // LOGGER_H
