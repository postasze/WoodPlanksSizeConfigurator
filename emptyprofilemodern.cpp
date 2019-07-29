#include "emptyprofilemodern.h"
#include "ui_emptyprofilemodern.h"

EmptyProfileModern::EmptyProfileModern(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EmptyProfileModern)
{
    decoratedEdges = false;
    expensiveColor = true;
    ui->setupUi(this);
    this->setWindowTitle("Profil przelotowy Modern");

    connect(ui->ModernBrownImage, &ClickableImage::leftButtonPressed, this, &EmptyProfileModern::woodTextureSelected);
    connect(ui->ModernPurpleImage, &ClickableImage::leftButtonPressed, this, &EmptyProfileModern::woodTextureSelected);
    connect(ui->ModernRawImage, &ClickableImage::leftButtonPressed, this, &EmptyProfileModern::woodTextureSelected);
    connect(ui->ModernSwampyImage, &ClickableImage::leftButtonPressed, this, &EmptyProfileModern::woodTextureSelected);

    connect(ui->CarvedEndingImage, &ClickableImage::leftButtonPressed, this, &EmptyProfileModern::woodEndingSelected);
    connect(ui->BeveledEndingImage, &ClickableImage::leftButtonPressed, this, &EmptyProfileModern::woodEndingSelected);

    connect(ui->lengthSlider, &QSlider::valueChanged, this, &EmptyProfileModern::lengthSlider_valueChanged);
    connect(ui->widthSlider, &QSlider::valueChanged, this, &EmptyProfileModern::widthSlider_valueChanged);
    connect(ui->heightSlider, &QSlider::valueChanged, this, &EmptyProfileModern::heightSlider_valueChanged);
    connect(ui->quantitySlider, &QSlider::valueChanged, this, &EmptyProfileModern::quantitySlider_valueChanged);
    connect(ui->endCapSlider, &QSlider::valueChanged, this, &EmptyProfileModern::endCapSlider_valueChanged);
    connect(ui->decoratedEdgesCheckBox, static_cast<void(QCheckBox::*)(bool)> (&QCheckBox::clicked), this, &EmptyProfileModern::decoratedEdgesCheckBox_clicked);

    ui->thicknessComboBox->addItem("2.5 cm");
    ui->thicknessComboBox->setCurrentIndex(0);

    ui->materialComboBox->addItem("EPS z powłoką PCT");
    ui->materialComboBox->setCurrentIndex(0);

    currentLength = INITIAL_EMPTY_PROFILE_LENGTH;
    currentWidth = INITIAL_EMPTY_PROFILE_WIDTH;
    currentHeight = INITIAL_EMPTY_PROFILE_HEIGHT;

    currentQuantity = 1;
    currentEndCapQuantity = 0;

    priceCalculation();
}

EmptyProfileModern::~EmptyProfileModern()
{
    delete ui;
}

void EmptyProfileModern::lengthSlider_valueChanged(int value)
{
    currentLength = value;
    ui->lengthBox->setText(QString::number(value) + " cm");
    priceCalculation();
    ui->GLWidget->resizeObject(currentLength/SCALE, currentWidth/SCALE, currentHeight/SCALE);
}

void EmptyProfileModern::widthSlider_valueChanged(int value)
{
    currentWidth = value;
    ui->widthBox->setText(QString::number(value) + " cm");
    priceCalculation();
    ui->GLWidget->resizeObject(currentLength/SCALE, currentWidth/SCALE, currentHeight/SCALE);
}

void EmptyProfileModern::heightSlider_valueChanged(int value)
{
    currentHeight = value;
    ui->heightBox->setText(QString::number(value) + " cm");
    priceCalculation();
    ui->GLWidget->resizeObject(currentLength/SCALE, currentWidth/SCALE, currentHeight/SCALE);
}

void EmptyProfileModern::quantitySlider_valueChanged(int value)
{
    currentQuantity = value;
    ui->quantityBox->setText(QString::number(currentQuantity));
    priceCalculation();
}

void EmptyProfileModern::endCapSlider_valueChanged(int value)
{
    currentEndCapQuantity = value;
    ui->endCapBox->setText(QString::number(currentEndCapQuantity));
    priceCalculation();
}

void EmptyProfileModern::purchaseButton_clicked()
{

}

void EmptyProfileModern::decoratedEdgesCheckBox_clicked(bool state)
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

void EmptyProfileModern::priceCalculation()
{
    currentNettoPrice = (currentLength/100.0) * ((2*currentWidth/100.0) + (2*currentHeight/100.0)) * PRICE_FOR_EMPTY_PROFILE_QUADRATIC_METER + 10*currentEndCapQuantity;
    if(expensiveColor)
        currentNettoPrice = 1.18 * currentNettoPrice;
    if(decoratedEdges)
        currentNettoPrice += (currentLength/100.0) * PRICE_FOR_DECORATED_EDGES_PER_METER;
    currentBruttoPrice = 1.23 * currentNettoPrice;
    currentNettoWholePrice = currentNettoPrice * currentQuantity;
    currentBruttoWholePrice = currentBruttoPrice * currentQuantity;
    updatePriceBoxes();
}

void EmptyProfileModern::updatePriceBoxes()
{
    ui->nettoPriceBox->setText(QString::number(roundf(100.0 * currentNettoPrice) / 100.0) + " zł");
    ui->bruttoPriceBox->setText(QString::number(roundf(100.0 * currentBruttoPrice) / 100.0) + " zł");
    ui->nettoWholePriceBox->setText(QString::number(roundf(100.0 * currentNettoWholePrice) / 100.0) + " zł");
    ui->bruttoWholePriceBox->setText(QString::number(roundf(100.0 * currentBruttoWholePrice) / 100.0) + " zł");
}

void EmptyProfileModern::woodTextureSelected(ClickableImage *sender)
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

void EmptyProfileModern::clearImages()
{
    ui->ModernBrownImage->setPixmap(QPixmap(":/images/Medium_Modern/kolory_i_wzory/medium_braz_etykieta.jpg"));
    ui->ModernPurpleImage->setPixmap(QPixmap(":/images/Medium_Modern/kolory_i_wzory/medium_purpura_etykieta.jpg"));
    ui->ModernRawImage->setPixmap(QPixmap(":/images/Medium_Modern/kolory_i_wzory/medium_surowy_etykieta.jpg"));
    ui->ModernSwampyImage->setPixmap(QPixmap(":/images/Medium_Modern/kolory_i_wzory/medium_bagienny_etykieta.jpg"));
}

void EmptyProfileModern::woodEndingSelected(ClickableImage *sender)
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
