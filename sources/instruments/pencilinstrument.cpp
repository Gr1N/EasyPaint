#include "pencilinstrument.h"
#include "../imagearea.h"
#include "../datasingleton.h"
#include <QtGui/QPen>
#include <QtGui/QPainter>

PencilInstrument::PencilInstrument(QObject *parent) :
    AbstractInstrument(parent)
{
}

void PencilInstrument::mousePressEvent(QMouseEvent *event, ImageArea &imageArea)
{
    mStartPoint = mEndPoint = event->pos();
    imageArea.setIsPaint(true);
}

void PencilInstrument::mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea)
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

void PencilInstrument::mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea)
{
    mEndPoint = event->pos();
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

void PencilInstrument::paint(ImageArea &imageArea, bool isSecondaryColor, bool)
{
    QPainter painter(imageArea.getImage());
    if(isSecondaryColor)
    {
        painter.setPen(QPen(DataSingleton::Instance()->getSecondaryColor(),
                            DataSingleton::Instance()->getPenSize() * imageArea.getZoomFactor(),
                            Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    }
    else
    {
        painter.setPen(QPen(DataSingleton::Instance()->getPrimaryColor(),
                            DataSingleton::Instance()->getPenSize() * imageArea.getZoomFactor(),
                            Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    }

    if(mStartPoint != mEndPoint)
    {
        painter.drawLine(mStartPoint, mEndPoint);
    }

    if(mStartPoint == mEndPoint)
    {
        painter.drawPoint(mStartPoint);
    }
    imageArea.setEdited(true);
    //    int rad(DataSingleton::Instance()->getPenSize() + round(sqrt((mStartPoint.x() - mEndPoint.x()) *
    //                                                                 (mStartPoint.x() - mEndPoint.x()) +
    //                                                                 (mStartPoint.y() - mEndPoint.y()) *
    //                                                                 (mStartPoint.y() - mEndPoint.y()))));
    //    mPImageArea->update(QRect(mStartPoint, mEndPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
    painter.end();
    imageArea.update();
}
