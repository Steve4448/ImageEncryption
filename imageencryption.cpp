#include "imageencryption.h"
#include "cryptionwindow.h"
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <math.h>
#include <QRgb>
ImageEncryption::ImageEncryption(QObject *parent) :
	QThread(parent)
{
}

void ImageEncryption::initSettings(QFile* fileRead, QFile* fileSave, bool useAlpha, bool useForFourth) {
	this->fileRead = fileRead;
	this->fileSave = fileSave;
	this->useAlpha = useAlpha;
	this->useForFourth = useForFourth;
}

void ImageEncryption::run() {
	CryptionWindow::log.writeLine("Starting Encryption...");
	QList<QRgb> encryptedData;
	fileRead->open(QIODevice::ReadOnly);
	CryptionWindow::log.writeLine(QString("Reading %1, %2 bytes.").arg(fileRead->fileName()).arg(fileRead->size()));
    quint8 bufferSize = useAlpha ? (useForFourth ? 4 : 3) : 3;
    uchar buffer[bufferSize];
    while(!fileRead->atEnd() && fileRead->read((char*)buffer, bufferSize))
        encryptedData << (QRgb)(useAlpha ? qRgba(buffer[0], buffer[1], buffer[2], useForFourth ? buffer[3] : 0) : qRgb(buffer[0], buffer[1], buffer[2]));

	int reqWidth = 0, reqHeight = 0;
    while(encryptedData.size() + 2 > reqWidth * reqHeight) {
		reqWidth++;
		reqHeight++;
	}
	CryptionWindow::log.writeLine(QString("Creating a %1x%2 image, with %3...").arg(reqWidth).arg(reqHeight).arg(useAlpha ? "alpha" : "no alpha"));
    QImage createdImage(reqWidth, reqHeight, useAlpha ? QImage::Format_ARGB32 : QImage::Format_RGB32);
    createdImage.fill((useAlpha ? qRgba(0, 0, 0, 0) : qRgb(0, 0, 0)));
	CryptionWindow::log.writeLine("Created image.");
	CryptionWindow::log.writeLine("Setting image pixel data...");
    int x = 2;
	int y = 0;

    createdImage.setPixel(0, 0, fileRead->size());
    createdImage.setPixel(1, 0, (useAlpha && useForFourth ? 1 : 0));
	foreach(QRgb current, encryptedData){
		createdImage.setPixel(x, y, current);
		x++;
		if(x >= createdImage.width()) {
			x = 0;
			y++;
		}
	}
	CryptionWindow::log.writeLine("Finished with the image, now saving...");
	createdImage.save(fileSave->fileName());
	CryptionWindow::log.writeLine("Finished Encrypting.");
	fileRead->deleteLater();
	fileSave->deleteLater();
}
