#include "magnifierinstrument.h"
#include "../imagearea.h"

MagnifierInstrument::MagnifierInstrument(QObject *parent) :
    AbstractInstrument(parent)
{
}

void MagnifierInstrument::mousePressEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if(event->button() == Qt::LeftButton || event->button() == Qt::RightButton)
    {
        imageArea.setIsPaint(true);
    }
}

void MagnifierInstrument::mouseMoveEvent(QMouseEvent *, ImageArea &)
{

}

void MagnifierInstrument::mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if(imageArea.isPaint())
    {
        if(event->button() == Qt::LeftButton)
        {
            if(imageArea.zoomImage(2.0))
            {
                imageArea.setZoomFactor(2.0);
            }
        }
        else if(event->button() == Qt::RightButton)
        {
            if(imageArea.zoomImage(0.5))
            {
                imageArea.setZoomFactor(0.5);
            }
        }
        imageArea.setIsPaint(false);
    }
}

void MagnifierInstrument::paint(ImageArea &, bool, bool)
{

}
