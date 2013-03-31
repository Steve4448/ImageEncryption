#ifndef CryptionWindow_H
#define CryptionWindow_H

#include <QMainWindow>
#include "imagecryption.h"
#include "logger.h"

#include "settings.h"
namespace Ui {
    class CryptionWindow;
}

class CryptionWindow : public QMainWindow
{
        Q_OBJECT

    public:
        explicit CryptionWindow(QWidget *parent = 0);
        ~CryptionWindow();
        static Logger log;
    private:
        Ui::CryptionWindow *ui;
        Settings set;
        ImageCryption* iC;
    private slots:
        void changeFileToEncryptPath();
        void changeFileEncryptedPath();
        void changeFileToDecryptPath();
        void changeFileDecryptedPath();
        void changeSettings();
        void startEncrypt();
        void startDecrypt();
        void finishedEncrypt();
        void finishedDecrypt();
};

#endif // CryptionWindow_H
