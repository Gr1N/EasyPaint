#include "sprayinstrument.h"
#include "../imagearea.h"
#include "../datasingleton.h"

#include <QtGui/QPen>
#include <QtGui/QPainter>
#include <math.h>

SprayInstrument::SprayInstrument(QObject *parent) :
    AbstractInstrument(parent)
{
}

void SprayInstrument::mousePressEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if(event->button() == Qt::LeftButton || event->button() == Qt::RightButton)
    {
        mStartPoint = mEndPoint = event->pos();
        imageArea.setIsPaint(true);
        imageArea.pushUndoCommand();
    }
}

void SprayInstrument::mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if(imageArea.isPaint())
    {
        mEndPoint = event->pos();
        if(event->buttons() & Qt::LeftButton)
        {
            paint(imageArea, false);
        }
        else if(event->buttons() & Qt::RightButton)
        {
            paint(imageArea, true);
        }
        mStartPoint = event->pos();
    }
}

void SprayInstrument::mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if(imageArea.isPaint())
    {
        if(event->button() == Qt::LeftButton)
        {
            paint(imageArea, false);
        }
        else if(event->button() == Qt::RightButton)
        {
            paint(imageArea, true);
        }
        imageArea.setIsPaint(false);
    }
}

void SprayInstrument::paint(ImageArea &imageArea, bool isSecondaryColor, bool)
{
    QPainter painter(imageArea.getImage());
    if(isSecondaryColor)
    {
        painter.setPen(QPen(DataSingleton::Instance()->getSecondaryColor(),
                            sqrt(DataSingleton::Instance()->getPenSize() * imageArea.getZoomFactor()),
                            Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    }
    else
    {
        painter.setPen(QPen(DataSingleton::Instance()->getPrimaryColor(),
                            sqrt(DataSingleton::Instance()->getPenSize() * imageArea.getZoomFactor()),
                            Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    }

    int x, y;
    for(int i(0); i < 12; i++)
    {
        switch(i) {
        case 0: case 1: case 2: case 3:
            x = (qrand() % 5 - 2)
                    * sqrt(DataSingleton::Instance()->getPenSize() * imageArea.getZoomFactor());
            y = (qrand() % 5 - 2)
                    * sqrt(DataSingleton::Instance()->getPenSize() * imageArea.getZoomFactor());
            break;
        case 4: case 5: case 6: case 7:
            x = (qrand() % 10 - 4)
                    * sqrt(DataSingleton::Instance()->getPenSize() * imageArea.getZoomFactor());
            y = (qrand() % 10 - 4)
                    * sqrt(DataSingleton::Instance()->getPenSize() * imageArea.getZoomFactor());
            break;
        case 8: case 9: case 10: case 11:
            x = (qrand() % 15 - 7)
                    * sqrt(DataSingleton::Instance()->getPenSize() * imageArea.getZoomFactor());
            y = (qrand() % 15 - 7)
                    * sqrt(DataSingleton::Instance()->getPenSize() * imageArea.getZoomFactor());
            break;
        }
        painter.drawPoint(mEndPoint.x() + x,
                         mEndPoint.y() + y);
    }
    imageArea.setEdited(true);
    painter.end();
    imageArea.update();
}
