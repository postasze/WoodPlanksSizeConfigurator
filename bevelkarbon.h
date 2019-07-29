#ifndef BEVELKARBON_H
#define BEVELKARBON_H

#include <QMainWindow>
#include "constants.h"
#include "math.h"
#include "clickableimage.h"

namespace Ui {
class BevelKarbon;
}

class BevelKarbon : public QMainWindow
{
    Q_OBJECT

public:
    explicit BevelKarbon(QWidget *parent = 0);
    ~BevelKarbon();

private slots:
    void lengthSlider_valueChanged(int value);
    void widthSlider_valueChanged(int value);
    void heightSlider_valueChanged(int value);
    void quantitySlider_valueChanged(int value);
    void purchaseButton_clicked();
    void materialComboBox_currentIndexChanged(int index);
    void woodTextureSelected(ClickableImage * sender);
    void woodEndingSelected(ClickableImage * sender);
    void decoratedEdgesCheckBox_clicked(bool state);

private:
    Ui::BevelKarbon *ui;
    qreal currentLength;
    qreal currentWidth;
    qreal currentHeight;
    qreal currentNettoPrice;
    qreal currentBruttoPrice;
    qreal currentNettoWholePrice;
    qreal currentBruttoWholePrice;
    quint16 currentQuantity;
    int materialComboBoxCount;
    bool decoratedEdges;
    bool expensiveMaterial;

    void priceCalculation();
    void updatePriceBoxes();
    void clearImages();
};

#endif // BEVELKARBON_H
