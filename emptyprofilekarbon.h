#ifndef EMPTYPROFILEKARBON_H
#define EMPTYPROFILEKARBON_H

#include <QMainWindow>
#include "constants.h"
#include "math.h"
#include "clickableimage.h"

namespace Ui {
class EmptyProfileKarbon;
}

class EmptyProfileKarbon : public QMainWindow
{
    Q_OBJECT

public:
    explicit EmptyProfileKarbon(QWidget *parent = 0);
    ~EmptyProfileKarbon();

private slots:
    void lengthSlider_valueChanged(int value);
    void widthSlider_valueChanged(int value);
    void heightSlider_valueChanged(int value);
    void quantitySlider_valueChanged(int value);
    void endCapSlider_valueChanged(int value);
    void purchaseButton_clicked();
    void materialComboBox_currentIndexChanged(int index);
    void woodTextureSelected(ClickableImage * sender);
    void woodEndingSelected(ClickableImage * sender);
    void decoratedEdgesCheckBox_clicked(bool state);

private:
    Ui::EmptyProfileKarbon *ui;
    qreal currentLength;
    qreal currentWidth;
    qreal currentHeight;
    qreal currentNettoPrice;
    qreal currentBruttoPrice;
    qreal currentNettoWholePrice;
    qreal currentBruttoWholePrice;
    quint16 currentQuantity;
    quint8 currentEndCapQuantity;
    int materialComboBoxCount;
    bool decoratedEdges;
    bool expensiveMaterial;

    void priceCalculation();
    void updatePriceBoxes();
    void clearImages();
};

#endif // EMPTYPROFILEKARBON_H
