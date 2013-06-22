#ifndef QPALETTEBUTTON_H
#define QPALETTEBUTTON_H

#include "../datasingleton.h"

#include <QToolButton>

class PaletteButton : public QToolButton
{
    Q_OBJECT

public:
    PaletteButton(const QColor &color);

signals:
    void colorPicked();

private:
    QColor mColor;

protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // QPALETTEBUTTON_H
