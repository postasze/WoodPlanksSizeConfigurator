#include "emptyprofilekarbon.h"
#include "ui_emptyprofilekarbon.h"

EmptyProfileKarbon::EmptyProfileKarbon(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EmptyProfileKarbon)
{
    materialComboBoxCount = 0;
    decoratedEdges = false;
    expensiveMaterial= false;
    ui->setupUi(this);
    this->setWindowTitle("Profil przelotowy Karbon");

    connect(ui->DarkSwampyImage, &ClickableImage::leftButtonPressed, this, &EmptyProfileKarbon::woodTextureSelected);
    connect(ui->LightSwampyImage, &ClickableImage::leftButtonPressed, this, &EmptyProfileKarbon::woodTextureSelected);
    connect(ui->WhiteImage, &ClickableImage::leftButtonPressed, this, &EmptyProfileKarbon::woodTextureSelected);
    connect(ui->DarkBrownImage, &ClickableImage::leftButtonPressed, this, &EmptyProfileKarbon::woodTextureSelected);
    connect(ui->LightBrownImage, &ClickableImage::leftButtonPressed, this, &EmptyProfileKarbon::woodTextureSelected);
    connect(ui->ExoticImage, &ClickableImage::leftButtonPressed, this, &EmptyProfileKarbon::woodTextureSelected);
    connect(ui->DarkPurpleImage, &ClickableImage::leftButtonPressed, this, &EmptyProfileKarbon::woodTextureSelected);
    connect(ui->LightPurpleImage, &ClickableImage::leftButtonPressed, this, &EmptyProfileKarbon::woodTextureSelected);

    connect(ui->CarvedEndingImage, &ClickableImage::leftButtonPressed, this, &EmptyProfileKarbon::woodEndingSelected);
    connect(ui->BeveledEndingImage, &ClickableImage::leftButtonPressed, this, &EmptyProfileKarbon::woodEndingSelected);

    connect(ui->lengthSlider, &QSlider::valueChanged, this, &EmptyProfileKarbon::lengthSlider_valueChanged);
    connect(ui->widthSlider, &QSlider::valueChanged, this, &EmptyProfileKarbon::widthSlider_valueChanged);
    connect(ui->heightSlider, &QSlider::valueChanged, this, &EmptyProfileKarbon::heightSlider_valueChanged);
    connect(ui->quantitySlider, &QSlider::valueChanged, this, &EmptyProfileKarbon::quantitySlider_valueChanged);
    connect(ui->endCapSlider, &QSlider::valueChanged, this, &EmptyProfileKarbon::endCapSlider_valueChanged);
    connect(ui->decoratedEdgesCheckBox, static_cast<void(QCheckBox::*)(bool)> (&QCheckBox::clicked), this, &EmptyProfileKarbon::decoratedEdgesCheckBox_clicked);
    connect(ui->materialComboBox, static_cast<void(QComboBox::*)(int)> (&QComboBox::currentIndexChanged), this, &EmptyProfileKarbon::materialComboBox_currentIndexChanged);

    ui->thicknessComboBox->addItem("2.5 cm");
    ui->thicknessComboBox->setCurrentIndex(0);

    ui->materialComboBox->addItem("EPS lekki styropianowy");
    ui->materialComboBox->addItem("EPS utwardzony styropianowy");
    ui->materialComboBox->setCurrentIndex(0);

    currentLength = INITIAL_EMPTY_PROFILE_LENGTH;
    currentWidth = INITIAL_EMPTY_PROFILE_WIDTH;
    currentHeight = INITIAL_EMPTY_PROFILE_HEIGHT;

    currentQuantity = 1;
    currentEndCapQuantity = 0;

    priceCalculation();
}

EmptyProfileKarbon::~EmptyProfileKarbon()
{
    delete ui;
}

void EmptyProfileKarbon::lengthSlider_valueChanged(int value)
{
    currentLength = value;
    ui->lengthBox->setText(QString::number(value) + " cm");
    priceCalculation();
    ui->GLWidget->resizeObject(currentLength/SCALE, currentWidth/SCALE, currentHeight/SCALE);
}

void EmptyProfileKarbon::widthSlider_valueChanged(int value)
{
    currentWidth = value;
    ui->widthBox->setText(QString::number(value) + " cm");
    priceCalculation();
    ui->GLWidget->resizeObject(currentLength/SCALE, currentWidth/SCALE, currentHeight/SCALE);
}

void EmptyProfileKarbon::heightSlider_valueChanged(int value)
{
    currentHeight = value;
    ui->heightBox->setText(QString::number(value) + " cm");
    priceCalculation();
    ui->GLWidget->resizeObject(currentLength/SCALE, currentWidth/SCALE, currentHeight/SCALE);
}

void EmptyProfileKarbon::quantitySlider_valueChanged(int value)
{
    currentQuantity = value;
    ui->quantityBox->setText(QString::number(currentQuantity));
    priceCalculation();
}

void EmptyProfileKarbon::endCapSlider_valueChanged(int value)
{
    currentEndCapQuantity = value;
    ui->endCapBox->setText(QString::number(currentEndCapQuantity));
    priceCalculation();
}

void EmptyProfileKarbon::purchaseButton_clicked()
{

}

void EmptyProfileKarbon::materialComboBox_currentIndexChanged(int index)
{
    materialComboBoxCount++;
    if(materialComboBoxCount == 1)
        return;

    switch(index)
    {
    case 0:
        expensiveMaterial = false;
        priceCalculation();
        break;
    case 1:
        expensiveMaterial = true;
        priceCalculation();
        updatePriceBoxes();
        break;
    }
}


void EmptyProfileKarbon::decoratedEdgesCheckBox_clicked(bool state)
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

void EmptyProfileKarbon::priceCalculation()
{
    currentNettoPrice = (currentLength/100.0) * ((2*currentWidth/100.0) + (2*currentHeight/100.0)) * PRICE_FOR_EMPTY_PROFILE_QUADRATIC_METER + 10*currentEndCapQuantity;
    if(expensiveMaterial)
        currentNettoPrice = 1.18 * currentNettoPrice;
    if(decoratedEdges)
        currentNettoPrice += (currentLength/100.0) * PRICE_FOR_DECORATED_EDGES_PER_METER;
    currentBruttoPrice = 1.23 * currentNettoPrice;
    currentNettoWholePrice = currentNettoPrice * currentQuantity;
    currentBruttoWholePrice = currentBruttoPrice * currentQuantity;
    updatePriceBoxes();
}

void EmptyProfileKarbon::updatePriceBoxes()
{
    ui->nettoPriceBox->setText(QString::number(roundf(100.0 * currentNettoPrice) / 100.0) + " zł");
    ui->bruttoPriceBox->setText(QString::number(roundf(100.0 * currentBruttoPrice) / 100.0) + " zł");
    ui->nettoWholePriceBox->setText(QString::number(roundf(100.0 * currentNettoWholePrice) / 100.0) + " zł");
    ui->bruttoWholePriceBox->setText(QString::number(roundf(100.0 * currentBruttoWholePrice) / 100.0) + " zł");
}

void EmptyProfileKarbon::woodTextureSelected(ClickableImage *sender)
{
    if(sender == ui->DarkSwampyImage)
    {
        ui->GLWidget->setTexture(0);
        clearImages();
        ui->DarkSwampyImage->setPixmap(QPixmap(":/images/Rustic_Karbon/kolory_i_wzory/bagienny_ciemny_etykieta_wybrany.jpg"));

    } else if(sender == ui->LightSwampyImage)
    {
        ui->GLWidget->setTexture(1);
        clearImages();
        ui->LightSwampyImage->setPixmap(QPixmap(":/images/Rustic_Karbon/kolory_i_wzory/bagienny_jasny_etykieta_wybrany.jpg"));
    } else if(sender == ui->WhiteImage)
    {
        ui->GLWidget->setTexture(2);
        clearImages();
        ui->WhiteImage->setPixmap(QPixmap(":/images/Rustic_Karbon/kolory_i_wzory/biały_etykieta_wybrany.jpg"));
    } else if(sender == ui->DarkBrownImage)
    {
        ui->GLWidget->setTexture(3);
        clearImages();
        ui->DarkBrownImage->setPixmap(QPixmap(":/images/Rustic_Karbon/kolory_i_wzory/braz_ciemny_etykieta_wybrany.jpg"));
    } else if(sender == ui->LightBrownImage)
    {
        ui->GLWidget->setTexture(4);
        clearImages();
        ui->LightBrownImage->setPixmap(QPixmap(":/images/Rustic_Karbon/kolory_i_wzory/braz_jasny_etykieta_wybrany.jpg"));
    } else if(sender == ui->ExoticImage)
    {
        ui->GLWidget->setTexture(5);
        clearImages();
        ui->ExoticImage->setPixmap(QPixmap(":/images/Rustic_Karbon/kolory_i_wzory/exotic_etykieta_wybrany.jpg"));
    } else if(sender == ui->DarkPurpleImage)
    {
        ui->GLWidget->setTexture(6);
        clearImages();
        ui->DarkPurpleImage->setPixmap(QPixmap(":/images/Rustic_Karbon/kolory_i_wzory/purpura_ciemna_etykieta_wybrany.jpg"));
    } else if(sender == ui->LightPurpleImage)
    {
        ui->GLWidget->setTexture(7);
        clearImages();
        ui->LightPurpleImage->setPixmap(QPixmap(":/images/Rustic_Karbon/kolory_i_wzory/purpura_jasna_etykieta_wybrany.jpg"));
    }
}

void EmptyProfileKarbon::clearImages()
{
    ui->DarkSwampyImage->setPixmap(QPixmap(":/images/Rustic_Karbon/kolory_i_wzory/bagienny_ciemny_etykieta.jpg"));
    ui->LightSwampyImage->setPixmap(QPixmap(":/images/Rustic_Karbon/kolory_i_wzory/bagienny_jasny_etykieta.jpg"));
    ui->WhiteImage->setPixmap(QPixmap(":/images/Rustic_Karbon/kolory_i_wzory/biały_etykieta.jpg"));
    ui->DarkBrownImage->setPixmap(QPixmap(":/images/Rustic_Karbon/kolory_i_wzory/braz_ciemny_etykieta.jpg"));
    ui->LightBrownImage->setPixmap(QPixmap(":/images/Rustic_Karbon/kolory_i_wzory/braz_jasny_etykieta.jpg"));
    ui->ExoticImage->setPixmap(QPixmap(":/images/Rustic_Karbon/kolory_i_wzory/exotic_etykieta.jpg"));
    ui->DarkPurpleImage->setPixmap(QPixmap(":/images/Rustic_Karbon/kolory_i_wzory/purpura_ciemna_etykieta.jpg"));
    ui->LightPurpleImage->setPixmap(QPixmap(":/images/Rustic_Karbon/kolory_i_wzory/purpura_jasna_etykieta.jpg"));
}

void EmptyProfileKarbon::woodEndingSelected(ClickableImage *sender)
{
    if(sender == ui->CarvedEndingImage)
    {
        ui->CarvedEndingImage->setPixmap(QPixmap(":/images/Rustic_Karbon/wykonczenie_profili/ciosane_krawedzie_wybrany.jpg"));
        ui->BeveledEndingImage->setPixmap(QPixmap(":/images/Rustic_Karbon/wykonczenie_profili/fazowane_krawedzie.jpg"));
    } else if(sender == ui->BeveledEndingImage)
    {
        ui->CarvedEndingImage->setPixmap(QPixmap(":/images/Rustic_Karbon/wykonczenie_profili/ciosane_krawedzie.jpg"));
        ui->BeveledEndingImage->setPixmap(QPixmap(":/images/Rustic_Karbon/wykonczenie_profili/fazowane_krawedzie_wybrany.jpg"));
    }
}
