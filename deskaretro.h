#ifndef DESKARETRO_H
#define DESKARETRO_H

#include <QMainWindow>
#include "constants.h"
#include "math.h"
#include "clickableimage.h"

namespace Ui {
class DeskaRetro;
}

class DeskaRetro : public QMainWindow
{
    Q_OBJECT

public:
    explicit DeskaRetro(QWidget *parent = 0);
    ~DeskaRetro();

private slots:
    void lengthSlider_valueChanged(int value);
    void widthSlider_valueChanged(int value);
    void quantitySlider_valueChanged(int value);
    void purchaseButton_clicked();
    void thicknessComboBox_currentIndexChanged(int index);
    void woodTextureSelected(ClickableImage * sender);
    void woodEndingSelected(ClickableImage * sender);

private:
    Ui::DeskaRetro *ui;
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

#endif // DESKARETRO_H
