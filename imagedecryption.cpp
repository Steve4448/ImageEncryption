#include "imagedecryption.h"
#include "cryptionwindow.h"
#include <QImage>
#include <QColor>
#include <QFile>
#include "math.h"
#include <QDebug>
ImageDecryption::ImageDecryption(QObject *parent) :
	QThread(parent)
{
}

void ImageDecryption::initSettings(QImage* fileRead, QFile* fileSave) {
	this->fileRead = fileRead;
	this->fileSave = fileSave;
}

void ImageDecryption::run() {
    CryptionWindow::log.writeLine("Starting Decryption...");
	if(!fileSave->open(QIODevice::WriteOnly))
		return;
	uchar buffer[4];
    CryptionWindow::log.writeLine("Now parsing image...");
    quint64 fileSize = fileRead->pixel(0, 0);
    bool usesFourthBit = fileRead->pixel(1, 0) & 0xFF;
	CryptionWindow::log.writeLine(QString("The image shows the encrypted file having %1 bytes and %2.").arg(fileSize).arg(usesFourthBit ? "has alpha" : "does not have alpha"));
	quint64 i = 0;
    int actuallyUsed = 0;
	for(int y = 0; y < fileRead->height(); y++) {
		for(int x = 0; x < fileRead->width(); x++) {
			if(y == 0)
				if(x < 2)
                    continue; //Skip the first 2 pixels of data, as it's used for the 'header'.
            QRgb rgb = fileRead->pixel(x, y);
            buffer[0] = qRed(rgb); if(i++ >= fileSize) goto fin; else actuallyUsed++;

            buffer[1] = qGreen(rgb); if(i++ >= fileSize) goto fin; else actuallyUsed++;
            buffer[2] = qBlue(rgb); if(i++ >= fileSize) goto fin; else actuallyUsed++;
            if(usesFourthBit) {
                buffer[3] = qAlpha(rgb); if(i++ >= fileSize) goto fin; else actuallyUsed++;
			}
            fin:
            fileSave->write((char*)buffer, actuallyUsed);
            actuallyUsed = 0;
		}
	}
	CryptionWindow::log.writeLine("Finished Decrypting.");
	fileRead = new QImage();
    fileSave->flush();
    fileSave->close();
	fileSave->deleteLater();
}
