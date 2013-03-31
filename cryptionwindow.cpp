#include "cryptionwindow.h"
#include "ui_cryptionwindow.h"
#include <QFileDialog>
#include <QMessageBox>
Logger CryptionWindow::log;
CryptionWindow::CryptionWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::CryptionWindow),
	set(this)
{
	iC = new ImageCryption();
	ui->setupUi(this);
	connect(ui->changeFileToEncryptPathButton, SIGNAL(clicked()), this, SLOT(changeFileToEncryptPath()));
	connect(ui->changeFileEncryptedSavePathButton, SIGNAL(clicked()), this, SLOT(changeFileEncryptedPath()));
	connect(ui->changeFileToDecryptPathButton, SIGNAL(clicked()), this, SLOT(changeFileToDecryptPath()));
	connect(ui->changeFileDecryptedSavePathButton, SIGNAL(clicked()), this, SLOT(changeFileDecryptedPath()));
	connect(ui->settingsButton, SIGNAL(clicked()), this, SLOT(changeSettings()));
	connect(ui->encryptButton, SIGNAL(clicked()), this, SLOT(startEncrypt()));
	connect(ui->decryptButton, SIGNAL(clicked()), this, SLOT(startDecrypt()));
	connect(iC->iE, SIGNAL(finished()), this, SLOT(finishedEncrypt()));
	connect(iC->iD, SIGNAL(finished()), this, SLOT(finishedDecrypt()));
}

void CryptionWindow::changeFileToEncryptPath() {
	QString returnVal = QFileDialog::getOpenFileName(this, "Choose a file to encrypt...");
	if(!returnVal.isNull())
		ui->fileToEncryptPath->setText(returnVal);
}

void CryptionWindow::changeFileEncryptedPath() {
	QString returnVal = QFileDialog::getSaveFileName(this, "Choose a location to save the encrypted data...");
	if(!returnVal.isNull())
		ui->encryptedFileSavePath->setText(returnVal);
}

void CryptionWindow::startEncrypt() {
	if(ui->fileToEncryptPath->text() == "" || ui->encryptedFileSavePath->text() == "") {
		QMessageBox::information(this, "Information", "Please complete the encryption form before trying to start.");
		return;
	}
	QFile* fileToRead = new QFile(ui->fileToEncryptPath->text());
	QFile* fileToWrite = new QFile(ui->encryptedFileSavePath->text());
	if(!fileToRead->exists()) {
		QMessageBox::information(this, "File not found", "The file to be read for encryption could not be found.");
		return;
	}
	ui->encryptButton->setEnabled(false);
	iC->iE->initSettings(fileToRead, fileToWrite, set.alphaEnabled(), set.alphaBitEnabled());
	iC->iE->start();
}

void CryptionWindow::finishedEncrypt() {
	ui->encryptButton->setEnabled(true);
}

void CryptionWindow::changeFileToDecryptPath() {
	QString returnVal = QFileDialog::getOpenFileName(this, "Choose a file to decrypt...");
	if(!returnVal.isNull())
		ui->fileToDecryptPath->setText(returnVal);
}

void CryptionWindow::changeFileDecryptedPath() {
	QString returnVal = QFileDialog::getSaveFileName(this, "Choose a location to save the decrypted data...");
	if(!returnVal.isNull())
		ui->decryptedFileSavePath->setText(returnVal);
}

void CryptionWindow::startDecrypt() {
	if(ui->fileToDecryptPath->text() == "" || ui->decryptedFileSavePath->text() == "") {
		QMessageBox::information(this, "Information", "Please complete the decryption form before trying to start.");
		return;
	}
	QFile* fileToRead = new QFile(ui->fileToDecryptPath->text());
	QFile* fileToWrite = new QFile(ui->decryptedFileSavePath->text());
	if(!fileToRead->exists()) {
		QMessageBox::information(this, "File not found", "The file to be read for encryption could not be found.");
		return;
	}
	QImage* nowImage = new QImage();
	if(!nowImage->load(fileToRead->fileName())) {
		QMessageBox::information(this, "Incorrect file", "There was either a error reading or this is not a proper image.\nI'm too lazy to properly handle this error.");
		return;
	}
	ui->decryptButton->setEnabled(false);
	iC->iD->initSettings(nowImage, fileToWrite);
	iC->iD->start();
}

void CryptionWindow::finishedDecrypt() {
	ui->decryptButton->setEnabled(true);
}

void CryptionWindow::changeSettings() {
	if(set.isVisible())
		set.setFocus(Qt::PopupFocusReason);
	else
		set.show();
}

CryptionWindow::~CryptionWindow()
{
	delete ui;
}
