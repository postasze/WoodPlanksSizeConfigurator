#ifndef EMPTYPROFILEMODERN_H
#define EMPTYPROFILEMODERN_H

#include <QMainWindow>
#include "constants.h"
#include "math.h"
#include "clickableimage.h"

namespace Ui {
class EmptyProfileModern;
}

class EmptyProfileModern : public QMainWindow
{
    Q_OBJECT

public:
    explicit EmptyProfileModern(QWidget *parent = 0);
    ~EmptyProfileModern();

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
    Ui::EmptyProfileModern *ui;
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

#endif // EMPTYPROFILEMODERN_H
