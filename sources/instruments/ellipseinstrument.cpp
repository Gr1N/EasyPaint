#include "ellipseinstrument.h"
#include "../imagearea.h"
#include "../datasingleton.h"

#include <QtGui/QPen>
#include <QtGui/QPainter>

EllipseInstrument::EllipseInstrument(QObject *parent) :
    AbstractInstrument(parent)
{
}

void EllipseInstrument::mousePressEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if(event->button() == Qt::LeftButton || event->button() == Qt::RightButton)
    {
        mStartPoint = mEndPoint = event->pos();
        imageArea.setIsPaint(true);
        mImageCopy = *imageArea.getImage();
        imageArea.pushUndoCommand();
    }
}

void EllipseInstrument::mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if(imageArea.isPaint())
    {
        mEndPoint = event->pos();
        imageArea.setImage(mImageCopy);
        if(event->buttons() & Qt::LeftButton)
        {
            paint(imageArea, false);
        }
        else if(event->buttons() & Qt::RightButton)
        {
            paint(imageArea, true);
        }
    }
}

void EllipseInstrument::mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if(imageArea.isPaint())
    {
        imageArea.setImage(mImageCopy);
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

void EllipseInstrument::paint(ImageArea &imageArea, bool isSecondaryColor, bool)
{
    QPainter painter(imageArea.getImage());
    painter.setPen(QPen(DataSingleton::Instance()->getPrimaryColor(),
                        DataSingleton::Instance()->getPenSize() * imageArea.getZoomFactor(),
                        Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    if(isSecondaryColor)
    {
        painter.setBrush(QBrush(DataSingleton::Instance()->getSecondaryColor()));
    }
    if(mStartPoint != mEndPoint)
    {
        painter.drawEllipse(QRect(mStartPoint, mEndPoint));
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
