#include "deskakarbon.h"
#include "ui_deskakarbon.h"

DeskaKarbon::DeskaKarbon(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DeskaKarbon)
{
    thicknessComboBoxCount = 0;
    materialComboBoxCount = 0;
    thickerWood = false;
    expensiveMaterial= false;
    ui->setupUi(this);
    this->setWindowTitle("Deska Karbon");

    connect(ui->DarkSwampyImage, &ClickableImage::leftButtonPressed, this, &DeskaKarbon::woodTextureSelected);
    connect(ui->LightSwampyImage, &ClickableImage::leftButtonPressed, this, &DeskaKarbon::woodTextureSelected);
    connect(ui->WhiteImage, &ClickableImage::leftButtonPressed, this, &DeskaKarbon::woodTextureSelected);
    connect(ui->DarkBrownImage, &ClickableImage::leftButtonPressed, this, &DeskaKarbon::woodTextureSelected);
    connect(ui->LightBrownImage, &ClickableImage::leftButtonPressed, this, &DeskaKarbon::woodTextureSelected);
    connect(ui->ExoticImage, &ClickableImage::leftButtonPressed, this, &DeskaKarbon::woodTextureSelected);
    connect(ui->DarkPurpleImage, &ClickableImage::leftButtonPressed, this, &DeskaKarbon::woodTextureSelected);
    connect(ui->LightPurpleImage, &ClickableImage::leftButtonPressed, this, &DeskaKarbon::woodTextureSelected);

    connect(ui->CarvedEndingImage, &ClickableImage::leftButtonPressed, this, &DeskaKarbon::woodEndingSelected);
    connect(ui->BeveledEndingImage, &ClickableImage::leftButtonPressed, this, &DeskaKarbon::woodEndingSelected);

    connect(ui->lengthSlider, &QSlider::valueChanged, this, &DeskaKarbon::lengthSlider_valueChanged);
    connect(ui->widthSlider, &QSlider::valueChanged, this, &DeskaKarbon::widthSlider_valueChanged);
    connect(ui->quantitySlider, &QSlider::valueChanged, this, &DeskaKarbon::quantitySlider_valueChanged);
    connect(ui->thicknessComboBox, static_cast<void(QComboBox::*)(int)> (&QComboBox::currentIndexChanged), this, &DeskaKarbon::thicknessComboBox_currentIndexChanged);
    connect(ui->materialComboBox, static_cast<void(QComboBox::*)(int)> (&QComboBox::currentIndexChanged), this, &DeskaKarbon::materialComboBox_currentIndexChanged);

    ui->thicknessComboBox->addItem("2.5 cm");
    ui->thicknessComboBox->addItem("5 cm");
    ui->thicknessComboBox->setCurrentIndex(0);

    ui->materialComboBox->addItem("EPS lekki styropianowy");
    ui->materialComboBox->addItem("EPS utwardzony styropianowy");
    ui->materialComboBox->setCurrentIndex(0);

    currentLength = INITIAL_PLANK_LENGTH;
    currentWidth = INITIAL_PLANK_WIDTH;
    currentHeight = INITIAL_PLANK_HEIGHT;

    currentQuantity = 1;

    priceCalculation();
}

DeskaKarbon::~DeskaKarbon()
{
    delete ui;
}

void DeskaKarbon::lengthSlider_valueChanged(int value)
{
    currentLength = value;
    ui->lengthBox->setText(QString::number(value) + " cm");
    priceCalculation();
    ui->GLWidget->resizeObject(currentLength/SCALE, currentWidth/SCALE, currentHeight/SCALE);
}

void DeskaKarbon::widthSlider_valueChanged(int value)
{
    currentWidth = value;
    ui->widthBox->setText(QString::number(value) + " cm");
    priceCalculation();
    ui->GLWidget->resizeObject(currentLength/SCALE, currentWidth/SCALE, currentHeight/SCALE);
}

void DeskaKarbon::quantitySlider_valueChanged(int value)
{
    currentQuantity = value;
    ui->quantityBox->setText(QString::number(currentQuantity));
    priceCalculation();
}

void DeskaKarbon::purchaseButton_clicked()
{

}

void DeskaKarbon::thicknessComboBox_currentIndexChanged(int index)
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

void DeskaKarbon::materialComboBox_currentIndexChanged(int index)
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

void DeskaKarbon::priceCalculation()
{
    currentNettoPrice = (currentLength/100.0) * (currentWidth/100.0) * PRICE_FOR_PLANK_QUADRATIC_METER;
    if(thickerWood)
        currentNettoPrice = 1.3 * currentNettoPrice;
    if(expensiveMaterial)
        currentNettoPrice = 1.18 * currentNettoPrice;
    currentBruttoPrice = 1.23 * currentNettoPrice;
    currentNettoWholePrice = currentNettoPrice * currentQuantity;
    currentBruttoWholePrice = currentBruttoPrice * currentQuantity;
    updatePriceBoxes();
}

void DeskaKarbon::updatePriceBoxes()
{
    ui->nettoPriceBox->setText(QString::number(roundf(100.0 * currentNettoPrice) / 100.0) + " zł");
    ui->bruttoPriceBox->setText(QString::number(roundf(100.0 * currentBruttoPrice) / 100.0) + " zł");
    ui->nettoWholePriceBox->setText(QString::number(roundf(100.0 * currentNettoWholePrice) / 100.0) + " zł");
    ui->bruttoWholePriceBox->setText(QString::number(roundf(100.0 * currentBruttoWholePrice) / 100.0) + " zł");
}

void DeskaKarbon::woodTextureSelected(ClickableImage *sender)
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

void DeskaKarbon::clearImages()
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

void DeskaKarbon::woodEndingSelected(ClickableImage *sender)
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
