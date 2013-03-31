#include "settings.h"
#include "ui_settings.h"
Settings::Settings(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Settings)
{
	ui->setupUi(this);
	connect(ui->enableAlpha, SIGNAL(toggled(bool)), this, SLOT(disableAlphaSettings(bool)));
}

void Settings::disableAlphaSettings(bool on) {
	ui->enableFourthBit->setEnabled(on);
	ui->enableHiding->setEnabled(on);
}

bool Settings::alphaEnabled() {
	return ui->enableAlpha->isChecked();
}

bool Settings::alphaBitEnabled() {
	return ui->enableFourthBit->isChecked();
}

Settings::~Settings()
{
	delete ui;
}
