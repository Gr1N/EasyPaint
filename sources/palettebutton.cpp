#include "palettebutton.h"

#include <QtGui/QMouseEvent>

PaletteButton::PaletteButton(const QColor &color)
{
    mColor = color;
    setMinimumSize(QSize(30, 30));
    setMaximumSize(QSize(30, 30));
    QPixmap* pixmap = new QPixmap(20, 20);
    pixmap->fill(color);
    setIcon(QPixmap(*pixmap));
    setStatusTip(color.name());
}

void PaletteButton::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        DataSingleton::Instance()->setPrimaryColor(mColor);
    }
    if(event->button() == Qt::RightButton)
    {
        DataSingleton::Instance()->setSecondaryColor(mColor);
    }
    colorPicked();
}
