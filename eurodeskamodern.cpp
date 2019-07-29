#include "eurodeskamodern.h"
#include "ui_eurodeskamodern.h"

EuroDeskaModern::EuroDeskaModern(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EuroDeskaModern)
{
    lengthComboBoxCount = 0;
    longerPlank = false;

    ui->setupUi(this);
    this->setWindowTitle("EuroDeska Modern");

    connect(ui->quantitySlider, &QSlider::valueChanged, this, &EuroDeskaModern::quantitySlider_valueChanged);
    connect(ui->lengthComboBox, static_cast<void(QComboBox::*)(int)> (&QComboBox::currentIndexChanged), this, &EuroDeskaModern::lengthComboBox_currentIndexChanged);

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

EuroDeskaModern::~EuroDeskaModern()
{
    delete ui;
}

void EuroDeskaModern::quantitySlider_valueChanged(int value)
{
    currentQuantity = value;
    ui->quantityBox->setText(QString::number(currentQuantity));
    priceCalculation();
}

void EuroDeskaModern::purchaseButton_clicked()
{

}

void EuroDeskaModern::lengthComboBox_currentIndexChanged(int index)
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

void EuroDeskaModern::priceCalculation()
{
    currentNettoPrice = (currentLength/100.0) * (currentWidth/100.0);
    if(longerPlank)
        currentNettoPrice = currentNettoPrice * PRICE_FOR_LONG_MODERN_EUROPLANK_QUADRATIC_METER;
    else
        currentNettoPrice = currentNettoPrice * PRICE_FOR_SHORT_MODERN_EUROPLANK_QUADRATIC_METER;
    currentBruttoPrice = 1.23 * currentNettoPrice;
    currentNettoWholePrice = currentNettoPrice * currentQuantity;
    currentBruttoWholePrice = currentBruttoPrice * currentQuantity;
    updatePriceBoxes();
}

void EuroDeskaModern::updatePriceBoxes()
{
    ui->nettoPriceBox->setText(QString::number(roundf(100.0 * currentNettoPrice) / 100.0) + " zł");
    ui->bruttoPriceBox->setText(QString::number(roundf(100.0 * currentBruttoPrice) / 100.0) + " zł");
    ui->nettoWholePriceBox->setText(QString::number(roundf(100.0 * currentNettoWholePrice) / 100.0) + " zł");
    ui->bruttoWholePriceBox->setText(QString::number(roundf(100.0 * currentBruttoWholePrice) / 100.0) + " zł");
}
