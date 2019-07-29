#include "deskamodern.h"
#include "ui_deskamodern.h"

DeskaModern::DeskaModern(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DeskaModern)
{
    thicknessComboBoxCount = 0;
    thickerWood = false;
    expensiveColor= true;
    ui->setupUi(this);
    this->setWindowTitle("Deska Modern");

    connect(ui->ModernBrownImage, &ClickableImage::leftButtonPressed, this, &DeskaModern::woodTextureSelected);
    connect(ui->ModernPurpleImage, &ClickableImage::leftButtonPressed, this, &DeskaModern::woodTextureSelected);
    connect(ui->ModernRawImage, &ClickableImage::leftButtonPressed, this, &DeskaModern::woodTextureSelected);
    connect(ui->ModernSwampyImage, &ClickableImage::leftButtonPressed, this, &DeskaModern::woodTextureSelected);

    connect(ui->CarvedEndingImage, &ClickableImage::leftButtonPressed, this, &DeskaModern::woodEndingSelected);
    connect(ui->BeveledEndingImage, &ClickableImage::leftButtonPressed, this, &DeskaModern::woodEndingSelected);

    connect(ui->lengthSlider, &QSlider::valueChanged, this, &DeskaModern::lengthSlider_valueChanged);
    connect(ui->widthSlider, &QSlider::valueChanged, this, &DeskaModern::widthSlider_valueChanged);
    connect(ui->quantitySlider, &QSlider::valueChanged, this, &DeskaModern::quantitySlider_valueChanged);
    connect(ui->thicknessComboBox, static_cast<void(QComboBox::*)(int)> (&QComboBox::currentIndexChanged), this, &DeskaModern::thicknessComboBox_currentIndexChanged);

    ui->thicknessComboBox->addItem("2.5 cm");
    ui->thicknessComboBox->addItem("5 cm");
    ui->thicknessComboBox->setCurrentIndex(0);

    ui->materialComboBox->addItem("EPS z powłoką PCT");
    ui->materialComboBox->setCurrentIndex(0);

    currentLength = INITIAL_PLANK_LENGTH;
    currentWidth = INITIAL_PLANK_WIDTH;
    currentHeight = INITIAL_PLANK_HEIGHT;

    currentQuantity = 1;

    priceCalculation();
}

DeskaModern::~DeskaModern()
{
    delete ui;
}

void DeskaModern::lengthSlider_valueChanged(int value)
{
    currentLength = value;
    ui->lengthBox->setText(QString::number(value) + " cm");
    priceCalculation();
    ui->GLWidget->resizeObject(currentLength/SCALE, currentWidth/SCALE, currentHeight/SCALE);
}

void DeskaModern::widthSlider_valueChanged(int value)
{
    currentWidth = value;
    ui->widthBox->setText(QString::number(value) + " cm");
    priceCalculation();
    ui->GLWidget->resizeObject(currentLength/SCALE, currentWidth/SCALE, currentHeight/SCALE);
}

void DeskaModern::quantitySlider_valueChanged(int value)
{
    currentQuantity = value;
    ui->quantityBox->setText(QString::number(currentQuantity));
    priceCalculation();
}

void DeskaModern::purchaseButton_clicked()
{

}

void DeskaModern::thicknessComboBox_currentIndexChanged(int index)
{
    thicknessComboBoxCount++;
    if(thicknessComboBoxCount == 1)
        return;

    switch(index)
    {
    case 0:
        thickerWood = false;
        priceCalculation();
        currentHeight = 2.5;
        ui->GLWidget->resizeObject(currentLength/SCALE, currentWidth/SCALE, currentHeight/SCALE);
        break;
    case 1:
        thickerWood = true;
        priceCalculation();
        currentHeight = 5.0;
        ui->GLWidget->resizeObject(currentLength/SCALE, currentWidth/SCALE, currentHeight/SCALE);
        break;
    }
}

void DeskaModern::priceCalculation()
{
    currentNettoPrice = (currentLength/100.0) * (currentWidth/100.0) * PRICE_FOR_PLANK_QUADRATIC_METER;
    if(thickerWood)
        currentNettoPrice = 1.3 * currentNettoPrice;
    if(expensiveColor)
        currentNettoPrice = 1.18 * currentNettoPrice;
    currentBruttoPrice = 1.23 * currentNettoPrice;
    currentNettoWholePrice = currentNettoPrice * currentQuantity;
    currentBruttoWholePrice = currentBruttoPrice * currentQuantity;
    updatePriceBoxes();
}

void DeskaModern::updatePriceBoxes()
{
    ui->nettoPriceBox->setText(QString::number(roundf(100.0 * currentNettoPrice) / 100.0) + " zł");
    ui->bruttoPriceBox->setText(QString::number(roundf(100.0 * currentBruttoPrice) / 100.0) + " zł");
    ui->nettoWholePriceBox->setText(QString::number(roundf(100.0 * currentNettoWholePrice) / 100.0) + " zł");
    ui->bruttoWholePriceBox->setText(QString::number(roundf(100.0 * currentBruttoWholePrice) / 100.0) + " zł");
}

void DeskaModern::woodTextureSelected(ClickableImage *sender)
{
    if(sender == ui->ModernBrownImage)
    {
        ui->GLWidget->setTexture(12);
        expensiveColor = true;
        priceCalculation();
        clearImages();
        ui->ModernBrownImage->setPixmap(QPixmap(":/images/Medium_Modern/kolory_i_wzory/medium_braz_etykieta_wybrany.jpg"));

    } else if(sender == ui->ModernPurpleImage)
    {
        ui->GLWidget->setTexture(13);
        expensiveColor = true;
        priceCalculation();
        clearImages();
        ui->ModernPurpleImage->setPixmap(QPixmap(":/images/Medium_Modern/kolory_i_wzory/medium_purpura_etykieta_wybrany.jpg"));
    } else if(sender == ui->ModernRawImage)
    {
        ui->GLWidget->setTexture(14);
        expensiveColor = false;
        priceCalculation();
        clearImages();
        ui->ModernRawImage->setPixmap(QPixmap(":/images/Medium_Modern/kolory_i_wzory/medium_surowy_etykieta_wybrany.jpg"));
    } else if(sender == ui->ModernSwampyImage)
    {
        ui->GLWidget->setTexture(15);
        expensiveColor = true;
        priceCalculation();
        clearImages();
        ui->ModernSwampyImage->setPixmap(QPixmap(":/images/Medium_Modern/kolory_i_wzory/medium_bagienny_etykieta_wybrany.jpg"));
    }
}

void DeskaModern::clearImages()
{
    ui->ModernBrownImage->setPixmap(QPixmap(":/images/Medium_Modern/kolory_i_wzory/medium_braz_etykieta.jpg"));
    ui->ModernPurpleImage->setPixmap(QPixmap(":/images/Medium_Modern/kolory_i_wzory/medium_purpura_etykieta.jpg"));
    ui->ModernRawImage->setPixmap(QPixmap(":/images/Medium_Modern/kolory_i_wzory/medium_surowy_etykieta.jpg"));
    ui->ModernSwampyImage->setPixmap(QPixmap(":/images/Medium_Modern/kolory_i_wzory/medium_bagienny_etykieta.jpg"));
}

void DeskaModern::woodEndingSelected(ClickableImage *sender)
{
    if(sender == ui->CarvedEndingImage)
    {
        ui->CarvedEndingImage->setPixmap(QPixmap(":/images/Medium_Modern/wykonczenie_profili/modern_medium_ciosane_krawedzie_wybrany.jpg"));
        ui->BeveledEndingImage->setPixmap(QPixmap(":/images/Medium_Modern/wykonczenie_profili/modern_medium_fazowane_krawedzie.jpg"));
    } else if(sender == ui->BeveledEndingImage)
    {
        ui->CarvedEndingImage->setPixmap(QPixmap(":/images/Medium_Modern/wykonczenie_profili/modern_medium_ciosane_krawedzie.jpg"));
        ui->BeveledEndingImage->setPixmap(QPixmap(":/images/Medium_Modern/wykonczenie_profili/modern_medium_fazowane_krawedzie_wybrany.jpg"));
    }
}
