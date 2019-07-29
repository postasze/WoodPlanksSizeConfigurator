#ifndef DESKAKARBON_H
#define DESKAKARBON_H

#include <QMainWindow>
#include "constants.h"
#include "math.h"
#include "clickableimage.h"

namespace Ui {
class DeskaKarbon;
}

class DeskaKarbon : public QMainWindow
{
    Q_OBJECT

public:
    explicit DeskaKarbon(QWidget *parent = 0);
    ~DeskaKarbon();

private slots:
    void lengthSlider_valueChanged(int value);
    void widthSlider_valueChanged(int value);
    void quantitySlider_valueChanged(int value);
    void purchaseButton_clicked();
    void thicknessComboBox_currentIndexChanged(int index);
    void materialComboBox_currentIndexChanged(int index);
    void woodTextureSelected(ClickableImage * sender);
    void woodEndingSelected(ClickableImage * sender);

private:
    Ui::DeskaKarbon *ui;
    qreal currentLength;
    qreal currentWidth;
    qreal currentHeight;
    qreal currentNettoPrice;
    qreal currentBruttoPrice;
    qreal currentNettoWholePrice;
    qreal currentBruttoWholePrice;
    quint16 currentQuantity;
    int materialComboBoxCount;
    int thicknessComboBoxCount;
    bool thickerWood;
    bool expensiveMaterial;

    void priceCalculation();
    void updatePriceBoxes();
    void clearImages();
};

#endif // DESKAKARBON_H
