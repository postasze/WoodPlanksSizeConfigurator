#ifndef EURODESKAMODERN_H
#define EURODESKAMODERN_H

#include <QMainWindow>
#include "constants.h"
#include "math.h"
#include "clickableimage.h"

namespace Ui {
class EuroDeskaModern;
}

class EuroDeskaModern : public QMainWindow
{
    Q_OBJECT

public:
    explicit EuroDeskaModern(QWidget *parent = 0);
    ~EuroDeskaModern();

private slots:
    void quantitySlider_valueChanged(int value);
    void purchaseButton_clicked();
    void lengthComboBox_currentIndexChanged(int index);

private:
    Ui::EuroDeskaModern *ui;
    qreal currentLength;
    qreal currentWidth;
    qreal currentHeight;
    qreal currentNettoPrice;
    qreal currentBruttoPrice;
    qreal currentNettoWholePrice;
    qreal currentBruttoWholePrice;
    quint16 currentQuantity;
    int lengthComboBoxCount;
    bool longerPlank;

    void priceCalculation();
    void updatePriceBoxes();
};

#endif // EURODESKAMODERN_H
