#ifndef CHANNELRETRO_H
#define CHANNELRETRO_H

#include <QMainWindow>
#include "constants.h"
#include "math.h"
#include "clickableimage.h"

namespace Ui {
class ChannelRetro;
}

class ChannelRetro : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChannelRetro(QWidget *parent = 0);
    ~ChannelRetro();

private slots:
    void lengthSlider_valueChanged(int value);
    void widthSlider_valueChanged(int value);
    void heightSlider_valueChanged(int value);
    void quantitySlider_valueChanged(int value);
    void endCapSlider_valueChanged(int value);
    void purchaseButton_clicked();
    void woodTextureSelected(ClickableImage * sender);
    void woodEndingSelected(ClickableImage * sender);
    void decoratedEdgesCheckBox_clicked(bool state);

private:
    Ui::ChannelRetro *ui;
    qreal currentLength;
    qreal currentWidth;
    qreal currentHeight;
    qreal currentNettoPrice;
    qreal currentBruttoPrice;
    qreal currentNettoWholePrice;
    qreal currentBruttoWholePrice;
    quint16 currentQuantity;
    quint8 currentEndCapQuantity;
    bool decoratedEdges;
    bool expensiveColor;

    void priceCalculation();
    void updatePriceBoxes();
    void clearImages();
};

#endif // CHANNELRETRO_H
