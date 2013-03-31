#ifndef IMAGEENCRYPTION_H
#define IMAGEENCRYPTION_H

#include <QThread>
#include <QFile>
#include <QRgb>
#include <QCryptographicHash>

class ImageEncryption : public QThread
{
		Q_OBJECT
	public:
		explicit ImageEncryption(QObject *parent = 0);
		void initSettings(QFile* fileRead, QFile* fileSave, bool useAlpha, bool useForFourth);
		void run();

	private:
		QFile* fileRead;
		QFile* fileSave;
		bool useAlpha;
		bool useForFourth;
};

#endif // IMAGEENCRYPTION_H
