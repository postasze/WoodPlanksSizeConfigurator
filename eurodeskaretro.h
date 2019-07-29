#ifndef EURODESKARETRO_H
#define EURODESKARETRO_H

#include <QMainWindow>
#include "constants.h"
#include "math.h"
#include "clickableimage.h"

namespace Ui {
class EuroDeskaRetro;
}

class EuroDeskaRetro : public QMainWindow
{
    Q_OBJECT

public:
    explicit EuroDeskaRetro(QWidget *parent = 0);
    ~EuroDeskaRetro();

private slots:
    void quantitySlider_valueChanged(int value);
    void purchaseButton_clicked();
    void lengthComboBox_currentIndexChanged(int index);

private:
    Ui::EuroDeskaRetro *ui;
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

#endif // EURODESKARETRO_H
