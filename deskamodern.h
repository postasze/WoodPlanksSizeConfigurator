#ifndef DESKAMODERN_H
#define DESKAMODERN_H

#include <QMainWindow>
#include "constants.h"
#include "math.h"
#include "clickableimage.h"

namespace Ui {
class DeskaModern;
}

class DeskaModern : public QMainWindow
{
    Q_OBJECT

public:
    explicit DeskaModern(QWidget *parent = 0);
    ~DeskaModern();

private slots:
    void lengthSlider_valueChanged(int value);
    void widthSlider_valueChanged(int value);
    void quantitySlider_valueChanged(int value);
    void purchaseButton_clicked();
    void thicknessComboBox_currentIndexChanged(int index);
    void woodTextureSelected(ClickableImage * sender);
    void woodEndingSelected(ClickableImage * sender);

private:
    Ui::DeskaModern *ui;
    qreal currentLength;
    qreal currentWidth;
    qreal currentHeight;
    qreal currentNettoPrice;
    qreal currentBruttoPrice;
    qreal currentNettoWholePrice;
    qreal currentBruttoWholePrice;
    quint16 currentQuantity;
    int thicknessComboBoxCount;
    bool thickerWood;
    bool expensiveColor;

    void priceCalculation();
    void updatePriceBoxes();
    void clearImages();
};

#endif // DESKAMODERN_H
