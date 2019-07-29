#include "deskaretro.h"
#include "ui_deskaretro.h"

DeskaRetro::DeskaRetro(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DeskaRetro)
{
    thicknessComboBoxCount = 0;
    thickerWood = false;
    expensiveColor= true;
    ui->setupUi(this);
    this->setWindowTitle("Deska Retro");

    connect(ui->RetroBrownImage, &ClickableImage::leftButtonPressed, this, &DeskaRetro::woodTextureSelected);
    connect(ui->RetroPurpleImage, &ClickableImage::leftButtonPressed, this, &DeskaRetro::woodTextureSelected);
    connect(ui->RetroRawImage, &ClickableImage::leftButtonPressed, this, &DeskaRetro::woodTextureSelected);
    connect(ui->RetroSwampyImage, &ClickableImage::leftButtonPressed, this, &DeskaRetro::woodTextureSelected);

    connect(ui->CarvedEndingImage, &ClickableImage::leftButtonPressed, this, &DeskaRetro::woodEndingSelected);
    connect(ui->BeveledEndingImage, &ClickableImage::leftButtonPressed, this, &DeskaRetro::woodEndingSelected);

    connect(ui->lengthSlider, &QSlider::valueChanged, this, &DeskaRetro::lengthSlider_valueChanged);
    connect(ui->widthSlider, &QSlider::valueChanged, this, &DeskaRetro::widthSlider_valueChanged);
    connect(ui->quantitySlider, &QSlider::valueChanged, this, &DeskaRetro::quantitySlider_valueChanged);
    connect(ui->thicknessComboBox, static_cast<void(QComboBox::*)(int)> (&QComboBox::currentIndexChanged), this, &DeskaRetro::thicknessComboBox_currentIndexChanged);

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

DeskaRetro::~DeskaRetro()
{
    delete ui;
}

void DeskaRetro::lengthSlider_valueChanged(int value)
{
    currentLength = value;
    ui->lengthBox->setText(QString::number(value) + " cm");
    priceCalculation();
    ui->GLWidget->resizeObject(currentLength/SCALE, currentWidth/SCALE, currentHeight/SCALE);
}

void DeskaRetro::widthSlider_valueChanged(int value)
{
    currentWidth = value;
    ui->widthBox->setText(QString::number(value) + " cm");
    priceCalculation();
    ui->GLWidget->resizeObject(currentLength/SCALE, currentWidth/SCALE, currentHeight/SCALE);
}

void DeskaRetro::quantitySlider_valueChanged(int value)
{
    currentQuantity = value;
    ui->quantityBox->setText(QString::number(currentQuantity));
    priceCalculation();
}

void DeskaRetro::purchaseButton_clicked()
{

}

void DeskaRetro::thicknessComboBox_currentIndexChanged(int index)
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

void DeskaRetro::priceCalculation()
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

void DeskaRetro::updatePriceBoxes()
{
    ui->nettoPriceBox->setText(QString::number(roundf(100.0 * currentNettoPrice) / 100.0) + " zł");
    ui->bruttoPriceBox->setText(QString::number(roundf(100.0 * currentBruttoPrice) / 100.0) + " zł");
    ui->nettoWholePriceBox->setText(QString::number(roundf(100.0 * currentNettoWholePrice) / 100.0) + " zł");
    ui->bruttoWholePriceBox->setText(QString::number(roundf(100.0 * currentBruttoWholePrice) / 100.0) + " zł");
}

void DeskaRetro::woodTextureSelected(ClickableImage *sender)
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

void DeskaRetro::clearImages()
{
    ui->RetroBrownImage->setPixmap(QPixmap(":/images/Old_Retro/kolory_i_wzory/old_braz_etykieta.jpg"));
    ui->RetroPurpleImage->setPixmap(QPixmap(":/images/Old_Retro/kolory_i_wzory/old_purpura_etykieta.jpg"));
    ui->RetroRawImage->setPixmap(QPixmap(":/images/Old_Retro/kolory_i_wzory/old_surowy_etykieta.jpg"));
    ui->RetroSwampyImage->setPixmap(QPixmap(":/images/Old_Retro/kolory_i_wzory/old_bagienny_etykieta.jpg"));
}

void DeskaRetro::woodEndingSelected(ClickableImage *sender)
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
