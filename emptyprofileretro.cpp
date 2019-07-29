#include "emptyprofileretro.h"
#include "ui_emptyprofileretro.h"

EmptyProfileRetro::EmptyProfileRetro(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EmptyProfileRetro)
{
    decoratedEdges = false;
    expensiveColor = true;
    ui->setupUi(this);
    this->setWindowTitle("Profil przelotowy Retro");

    connect(ui->RetroBrownImage, &ClickableImage::leftButtonPressed, this, &EmptyProfileRetro::woodTextureSelected);
    connect(ui->RetroPurpleImage, &ClickableImage::leftButtonPressed, this, &EmptyProfileRetro::woodTextureSelected);
    connect(ui->RetroRawImage, &ClickableImage::leftButtonPressed, this, &EmptyProfileRetro::woodTextureSelected);
    connect(ui->RetroSwampyImage, &ClickableImage::leftButtonPressed, this, &EmptyProfileRetro::woodTextureSelected);

    connect(ui->CarvedEndingImage, &ClickableImage::leftButtonPressed, this, &EmptyProfileRetro::woodEndingSelected);
    connect(ui->BeveledEndingImage, &ClickableImage::leftButtonPressed, this, &EmptyProfileRetro::woodEndingSelected);

    connect(ui->lengthSlider, &QSlider::valueChanged, this, &EmptyProfileRetro::lengthSlider_valueChanged);
    connect(ui->widthSlider, &QSlider::valueChanged, this, &EmptyProfileRetro::widthSlider_valueChanged);
    connect(ui->heightSlider, &QSlider::valueChanged, this, &EmptyProfileRetro::heightSlider_valueChanged);
    connect(ui->quantitySlider, &QSlider::valueChanged, this, &EmptyProfileRetro::quantitySlider_valueChanged);
    connect(ui->endCapSlider, &QSlider::valueChanged, this, &EmptyProfileRetro::endCapSlider_valueChanged);
    connect(ui->decoratedEdgesCheckBox, static_cast<void(QCheckBox::*)(bool)> (&QCheckBox::clicked), this, &EmptyProfileRetro::decoratedEdgesCheckBox_clicked);

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

EmptyProfileRetro::~EmptyProfileRetro()
{
    delete ui;
}

void EmptyProfileRetro::lengthSlider_valueChanged(int value)
{
    currentLength = value;
    ui->lengthBox->setText(QString::number(value) + " cm");
    priceCalculation();
    ui->GLWidget->resizeObject(currentLength/SCALE, currentWidth/SCALE, currentHeight/SCALE);
}

void EmptyProfileRetro::widthSlider_valueChanged(int value)
{
    currentWidth = value;
    ui->widthBox->setText(QString::number(value) + " cm");
    priceCalculation();
    ui->GLWidget->resizeObject(currentLength/SCALE, currentWidth/SCALE, currentHeight/SCALE);
}

void EmptyProfileRetro::heightSlider_valueChanged(int value)
{
    currentHeight = value;
    ui->heightBox->setText(QString::number(value) + " cm");
    priceCalculation();
    ui->GLWidget->resizeObject(currentLength/SCALE, currentWidth/SCALE, currentHeight/SCALE);
}

void EmptyProfileRetro::quantitySlider_valueChanged(int value)
{
    currentQuantity = value;
    ui->quantityBox->setText(QString::number(currentQuantity));
    priceCalculation();
}

void EmptyProfileRetro::endCapSlider_valueChanged(int value)
{
    currentEndCapQuantity = value;
    ui->endCapBox->setText(QString::number(currentEndCapQuantity));
    priceCalculation();
}

void EmptyProfileRetro::purchaseButton_clicked()
{

}

void EmptyProfileRetro::decoratedEdgesCheckBox_clicked(bool state)
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

void EmptyProfileRetro::priceCalculation()
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

void EmptyProfileRetro::updatePriceBoxes()
{
    ui->nettoPriceBox->setText(QString::number(roundf(100.0 * currentNettoPrice) / 100.0) + " zł");
    ui->bruttoPriceBox->setText(QString::number(roundf(100.0 * currentBruttoPrice) / 100.0) + " zł");
    ui->nettoWholePriceBox->setText(QString::number(roundf(100.0 * currentNettoWholePrice) / 100.0) + " zł");
    ui->bruttoWholePriceBox->setText(QString::number(roundf(100.0 * currentBruttoWholePrice) / 100.0) + " zł");
}

void EmptyProfileRetro::woodTextureSelected(ClickableImage *sender)
{
    if(sender == ui->RetroBrownImage)
    {
        ui->GLWidget->setTexture(8);
        expensiveColor = true;
        priceCalculation();
        clearImages();
        ui->RetroBrownImage->setPixmap(QPixmap(":/images/Old_Retro/kolory_i_wzory/old_braz_etykieta_wybrany.jpg"));

    } else if(sender == ui->RetroPurpleImage)
    {
        ui->GLWidget->setTexture(9);
        expensiveColor = true;
        priceCalculation();
        clearImages();
        ui->RetroPurpleImage->setPixmap(QPixmap(":/images/Old_Retro/kolory_i_wzory/old_purpura_etykieta_wybrany.jpg"));
    } else if(sender == ui->RetroRawImage)
    {
        ui->GLWidget->setTexture(10);
        expensiveColor = false;
        priceCalculation();
        clearImages();
        ui->RetroRawImage->setPixmap(QPixmap(":/images/Old_Retro/kolory_i_wzory/old_surowy_etykieta_wybrany.jpg"));
    } else if(sender == ui->RetroSwampyImage)
    {
        ui->GLWidget->setTexture(11);
        expensiveColor = true;
        priceCalculation();
        clearImages();
        ui->RetroSwampyImage->setPixmap(QPixmap(":/images/Old_Retro/kolory_i_wzory/old_bagienny_etykieta_wybrany.jpg"));
    }
}

void EmptyProfileRetro::clearImages()
{
    ui->RetroBrownImage->setPixmap(QPixmap(":/images/Old_Retro/kolory_i_wzory/old_braz_etykieta.jpg"));
    ui->RetroPurpleImage->setPixmap(QPixmap(":/images/Old_Retro/kolory_i_wzory/old_purpura_etykieta.jpg"));
    ui->RetroRawImage->setPixmap(QPixmap(":/images/Old_Retro/kolory_i_wzory/old_surowy_etykieta.jpg"));
    ui->RetroSwampyImage->setPixmap(QPixmap(":/images/Old_Retro/kolory_i_wzory/old_bagienny_etykieta.jpg"));
}

void EmptyProfileRetro::woodEndingSelected(ClickableImage *sender)
{
    if(sender == ui->CarvedEndingImage)
    {
        ui->CarvedEndingImage->setPixmap(QPixmap(":/images/Old_Retro/wykonczenie_profili/old_ciosane_krawedzie_wybrany.jpg"));
        ui->BeveledEndingImage->setPixmap(QPixmap(":/images/Old_Retro/wykonczenie_profili/old_fazowane_krawedzie.jpg"));
    } else if(sender == ui->BeveledEndingImage)
    {
        ui->CarvedEndingImage->setPixmap(QPixmap(":/images/Old_Retro/wykonczenie_profili/old_ciosane_krawedzie.jpg"));
        ui->BeveledEndingImage->setPixmap(QPixmap(":/images/Old_Retro/wykonczenie_profili/old_fazowane_krawedzie_wybrany.jpg"));
    }
}
