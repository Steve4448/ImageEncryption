#ifndef IMAGECRYPTION_H
#define IMAGECRYPTION_H
#include "imageencryption.h"
#include "imagedecryption.h"
class ImageCryption
{
	public:
		ImageCryption();
		ImageEncryption* iE;
		ImageDecryption* iD;
};

#endif // IMAGECRYPTION_H
