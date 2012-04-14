#include "colorpickerinstrument.h"
#include "../imagearea.h"
#include "../datasingleton.h"

ColorpickerInstrument::ColorpickerInstrument(QObject *parent) :
    AbstractInstrument(parent)
{
}

void ColorpickerInstrument::mousePressEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if(event->button() == Qt::LeftButton || event->button() == Qt::RightButton)
    {
        imageArea.setIsPaint(true);
    }
}

void ColorpickerInstrument::mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea)
{
    QRgb pixel(imageArea.getImage()->pixel(event->pos()));
    QColor getColor(pixel);
    imageArea.emitColor(getColor);
}

void ColorpickerInstrument::mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if(imageArea.isPaint())
    {
        mStartPoint = mEndPoint = event->pos();
        if(event->button() == Qt::LeftButton)
        {
            paint(imageArea, false);
            imageArea.emitPrimaryColorView();
        }
        else if(event->button() == Qt::RightButton)
        {
            paint(imageArea, true);
            imageArea.emitSecondaryColorView();
        }
        imageArea.setIsPaint(false);
        imageArea.emitRestorePreviousInstrument();
    }
}

void ColorpickerInstrument::paint(ImageArea &imageArea, bool isSecondaryColor, bool)
{
    bool inArea(true);
    if(mStartPoint.x() < 0 || mStartPoint.y() < 0
            || mStartPoint.x() > imageArea.getImage()->width()
            || mStartPoint.y() > imageArea.getImage()->height())
        inArea = false;

    if(inArea && isSecondaryColor)
    {
        QRgb pixel(imageArea.getImage()->pixel(mStartPoint));
        QColor getColor(pixel);
        DataSingleton::Instance()->setSecondaryColor(getColor);
    }
    if(inArea)
    {
        QRgb pixel(imageArea.getImage()->pixel(mStartPoint));
        QColor getColor(pixel);
        DataSingleton::Instance()->setPrimaryColor(getColor);
    }
}
