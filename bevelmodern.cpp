#include "bevelmodern.h"
#include "ui_bevelmodern.h"

BevelModern::BevelModern(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BevelModern)
{
    decoratedEdges = false;
    expensiveColor = true;
    ui->setupUi(this);
    this->setWindowTitle("Kątownik Modern");

    connect(ui->ModernBrownImage, &ClickableImage::leftButtonPressed, this, &BevelModern::woodTextureSelected);
    connect(ui->ModernPurpleImage, &ClickableImage::leftButtonPressed, this, &BevelModern::woodTextureSelected);
    connect(ui->ModernRawImage, &ClickableImage::leftButtonPressed, this, &BevelModern::woodTextureSelected);
    connect(ui->ModernSwampyImage, &ClickableImage::leftButtonPressed, this, &BevelModern::woodTextureSelected);

    connect(ui->CarvedEndingImage, &ClickableImage::leftButtonPressed, this, &BevelModern::woodEndingSelected);
    connect(ui->BeveledEndingImage, &ClickableImage::leftButtonPressed, this, &BevelModern::woodEndingSelected);

    connect(ui->lengthSlider, &QSlider::valueChanged, this, &BevelModern::lengthSlider_valueChanged);
    connect(ui->widthSlider, &QSlider::valueChanged, this, &BevelModern::widthSlider_valueChanged);
    connect(ui->heightSlider, &QSlider::valueChanged, this, &BevelModern::heightSlider_valueChanged);
    connect(ui->quantitySlider, &QSlider::valueChanged, this, &BevelModern::quantitySlider_valueChanged);
    connect(ui->decoratedEdgesCheckBox, static_cast<void(QCheckBox::*)(bool)> (&QCheckBox::clicked), this, &BevelModern::decoratedEdgesCheckBox_clicked);

    ui->thicknessComboBox->addItem("2.5 cm");
    ui->thicknessComboBox->setCurrentIndex(0);

    ui->materialComboBox->addItem("EPS z powłoką PCT");
    ui->materialComboBox->setCurrentIndex(0);

    currentLength = INITIAL_BEVEL_LENGTH;
    currentWidth = INITIAL_BEVEL_WIDTH;
    currentHeight = INITIAL_BEVEL_HEIGHT;

    currentQuantity = 1;

    priceCalculation();
}

BevelModern::~BevelModern()
{
    delete ui;
}

void BevelModern::lengthSlider_valueChanged(int value)
{
    currentLength = value;
    ui->lengthBox->setText(QString::number(value) + " cm");
    priceCalculation();
    ui->GLWidget->resizeObject(currentLength/SCALE, currentWidth/SCALE, currentHeight/SCALE);
}

void BevelModern::widthSlider_valueChanged(int value)
{
    currentWidth = value;
    ui->widthBox->setText(QString::number(value) + " cm");
    priceCalculation();
    ui->GLWidget->resizeObject(currentLength/SCALE, currentWidth/SCALE, currentHeight/SCALE);
}

void BevelModern::heightSlider_valueChanged(int value)
{
    currentHeight = value;
    ui->heightBox->setText(QString::number(value) + " cm");
    priceCalculation();
    ui->GLWidget->resizeObject(currentLength/SCALE, currentWidth/SCALE, currentHeight/SCALE);
}

void BevelModern::quantitySlider_valueChanged(int value)
{
    currentQuantity = value;
    ui->quantityBox->setText(QString::number(currentQuantity));
    priceCalculation();
}

void BevelModern::decoratedEdgesCheckBox_clicked(bool state)
{
    if(state)
    {
        decoratedEdges = true;
        priceCalculation();
    }
    else
    {
        decoratedEdges = false;
        priceCalculation();
    }
}

void BevelModern::purchaseButton_clicked()
{

}

void BevelModern::priceCalculation()
{
    currentNettoPrice = (currentLength/100.0) * ((currentWidth/100.0) + (currentHeight/100.0))  * PRICE_FOR_BEVEL_QUADRATIC_METER;
    if(expensiveColor)
        currentNettoPrice = 1.18 * currentNettoPrice;
    if(decoratedEdges)
        currentNettoPrice += (currentLength/100.0) * PRICE_FOR_DECORATED_EDGES_PER_METER;
    currentBruttoPrice = 1.23 * currentNettoPrice;
    currentNettoWholePrice = currentNettoPrice * currentQuantity;
    currentBruttoWholePrice = currentBruttoPrice * currentQuantity;
    updatePriceBoxes();
}

void BevelModern::updatePriceBoxes()
{
    ui->nettoPriceBox->setText(QString::number(roundf(100.0 * currentNettoPrice) / 100.0) + " zł");
    ui->bruttoPriceBox->setText(QString::number(roundf(100.0 * currentBruttoPrice) / 100.0) + " zł");
    ui->nettoWholePriceBox->setText(QString::number(roundf(100.0 * currentNettoWholePrice) / 100.0) + " zł");
    ui->bruttoWholePriceBox->setText(QString::number(roundf(100.0 * currentBruttoWholePrice) / 100.0) + " zł");
}

void BevelModern::woodTextureSelected(ClickableImage *sender)
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

void BevelModern::clearImages()
{
    ui->ModernBrownImage->setPixmap(QPixmap(":/images/Medium_Modern/kolory_i_wzory/medium_braz_etykieta.jpg"));
    ui->ModernPurpleImage->setPixmap(QPixmap(":/images/Medium_Modern/kolory_i_wzory/medium_purpura_etykieta.jpg"));
    ui->ModernRawImage->setPixmap(QPixmap(":/images/Medium_Modern/kolory_i_wzory/medium_surowy_etykieta.jpg"));
    ui->ModernSwampyImage->setPixmap(QPixmap(":/images/Medium_Modern/kolory_i_wzory/medium_bagienny_etykieta.jpg"));
}

void BevelModern::woodEndingSelected(ClickableImage *sender)
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
