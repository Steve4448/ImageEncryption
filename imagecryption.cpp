#include "imagecryption.h"
#include <QDebug>
ImageCryption::ImageCryption()
{
    iE = new ImageEncryption();
    iD = new ImageDecryption();
}
