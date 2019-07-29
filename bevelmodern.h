#ifndef BEVELMODERN_H
#define BEVELMODERN_H

#include <QMainWindow>
#include "constants.h"
#include "math.h"
#include "clickableimage.h"

namespace Ui {
class BevelModern;
}

class BevelModern : public QMainWindow
{
    Q_OBJECT

public:
    explicit BevelModern(QWidget *parent = 0);
    ~BevelModern();

private slots:
    void lengthSlider_valueChanged(int value);
    void widthSlider_valueChanged(int value);
    void heightSlider_valueChanged(int value);
    void quantitySlider_valueChanged(int value);
    void purchaseButton_clicked();
    void woodTextureSelected(ClickableImage * sender);
    void woodEndingSelected(ClickableImage * sender);
    void decoratedEdgesCheckBox_clicked(bool state);

private:
    Ui::BevelModern *ui;
    qreal currentLength;
    qreal currentWidth;
    qreal currentHeight;
    qreal currentNettoPrice;
    qreal currentBruttoPrice;
    qreal currentNettoWholePrice;
    qreal currentBruttoWholePrice;
    quint16 currentQuantity;
    bool decoratedEdges;
    bool expensiveColor;

    void priceCalculation();
    void updatePriceBoxes();
    void clearImages();
};

#endif // BEVELMODERN_H
