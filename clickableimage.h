#ifndef CLICKABLEIMAGE_H_
#define CLICKABLEIMAGE_H_
#include <QLabel>
#include <QMouseEvent>

using namespace Qt;

class ClickableImage:public QLabel
{
    Q_OBJECT
public:
    ClickableImage(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *eve );
    void mouseReleaseEvent(QMouseEvent *eve );
    void enterEvent(QEvent* eve );
    void leaveEvent(QEvent* eve );

signals:
    void leftButtonPressed(ClickableImage* sender);
    void rightButtonPressed(ClickableImage* sender);
    void middleButtonPressed(ClickableImage* sender);
    void leftButtonReleased(ClickableImage* sender);
    void rightButtonReleased(ClickableImage* sender);
    void middleButtonReleased(ClickableImage* sender);
    void mouseEntered(ClickableImage* sender );
    void mouseLeft(ClickableImage* sender);
};

#endif /*CLICKABLEIMAGE_H_*/
