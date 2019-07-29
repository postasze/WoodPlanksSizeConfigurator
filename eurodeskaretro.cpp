#include "eurodeskaretro.h"
#include "ui_eurodeskaretro.h"

EuroDeskaRetro::EuroDeskaRetro(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EuroDeskaRetro)
{
    lengthComboBoxCount = 0;
    longerPlank = false;

    ui->setupUi(this);
    this->setWindowTitle("EuroDeska Retro");

    connect(ui->quantitySlider, &QSlider::valueChanged, this, &EuroDeskaRetro::quantitySlider_valueChanged);
    connect(ui->lengthComboBox, static_cast<void(QComboBox::*)(int)> (&QComboBox::currentIndexChanged), this, &EuroDeskaRetro::lengthComboBox_currentIndexChanged);

    ui->lengthComboBox->addItem("145 cm");
    ui->lengthComboBox->addItem("290 cm");
    ui->lengthComboBox->setCurrentIndex(0);

    ui->widthComboBox->addItem("20 cm");
    ui->widthComboBox->setCurrentIndex(0);

    ui->thicknessComboBox->addItem("10 mm");
    ui->thicknessComboBox->setCurrentIndex(0);

    ui->materialComboBox->addItem("EPS 200");
    ui->materialComboBox->setCurrentIndex(0);

    currentLength = INITIAL_EUROPLANK_LENGTH;
    currentWidth = INITIAL_EUROPLANK_WIDTH;
    currentHeight = INITIAL_EUROPLANK_HEIGHT;

    currentQuantity = 1;

    priceCalculation();
}

EuroDeskaRetro::~EuroDeskaRetro()
{
    delete ui;
}

void EuroDeskaRetro::quantitySlider_valueChanged(int value)
{
    currentQuantity = value;
    ui->quantityBox->setText(QString::number(currentQuantity));
    priceCalculation();
}

void EuroDeskaRetro::purchaseButton_clicked()
{

}

void EuroDeskaRetro::lengthComboBox_currentIndexChanged(int index)
{
    lengthComboBoxCount++;
    if(lengthComboBoxCount == 1)
        return;

    switch(index)
    {
    case 0:
        longerPlank = false;
        currentLength = 145;
        priceCalculation();
        ui->GLWidget->resizeObject(currentLength/SCALE, currentWidth/SCALE, currentHeight/SCALE);
        break;
    case 1:
        longerPlank = true;
        currentLength = 290;
        priceCalculation();
        ui->GLWidget->resizeObject(currentLength/SCALE, currentWidth/SCALE, currentHeight/SCALE);
        break;
    }
}

void EuroDeskaRetro::priceCalculation()
{
    currentNettoPrice = (currentLength/100.0) * (currentWidth/100.0);
    if(longerPlank)
        currentNettoPrice = currentNettoPrice * PRICE_FOR_LONG_RETRO_EUROPLANK_QUADRATIC_METER;
    else
        currentNettoPrice = currentNettoPrice * PRICE_FOR_SHORT_RETRO_EUROPLANK_QUADRATIC_METER;
    currentBruttoPrice = 1.23 * currentNettoPrice;
    currentNettoWholePrice = currentNettoPrice * currentQuantity;
    currentBruttoWholePrice = currentBruttoPrice * currentQuantity;
    updatePriceBoxes();
}

void EuroDeskaRetro::updatePriceBoxes()
{
    ui->nettoPriceBox->setText(QString::number(roundf(100.0 * currentNettoPrice) / 100.0) + " zł");
    ui->bruttoPriceBox->setText(QString::number(roundf(100.0 * currentBruttoPrice) / 100.0) + " zł");
    ui->nettoWholePriceBox->setText(QString::number(roundf(100.0 * currentNettoWholePrice) / 100.0) + " zł");
    ui->bruttoWholePriceBox->setText(QString::number(roundf(100.0 * currentBruttoWholePrice) / 100.0) + " zł");
}
