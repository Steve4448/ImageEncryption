#ifndef IMAGEDECRYPTION_H
#define IMAGEDECRYPTION_H

#include <QThread>
#include <QImage>
#include <QFile>
#include <QCryptographicHash>

class ImageDecryption : public QThread
{
		Q_OBJECT
	public:
		explicit ImageDecryption(QObject *parent = 0);
		void initSettings(QImage *fileRead, QFile *fileSave);
		void run();
	private:
		QImage* fileRead;
		QFile* fileSave;
};

#endif // IMAGEDECRYPTION_H
