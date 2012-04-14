#include "eraserinstrument.h"
#include "../imagearea.h"
#include "../datasingleton.h"

#include <QtGui/QPen>
#include <QtGui/QPainter>

EraserInstrument::EraserInstrument(QObject *parent) :
    AbstractInstrument(parent)
{
}

void EraserInstrument::mousePressEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if(event->button() == Qt::LeftButton || event->button() == Qt::RightButton)
    {
        mStartPoint = mEndPoint = event->pos();
        imageArea.setIsPaint(true);
        imageArea.pushUndoCommand();
    }
}

void EraserInstrument::mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if(imageArea.isPaint())
    {
        mEndPoint = event->pos();
        paint(imageArea, false);
        mStartPoint = event->pos();
    }
}

void EraserInstrument::mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if(imageArea.isPaint())
    {
        mEndPoint = event->pos();
        paint(imageArea);
        imageArea.setIsPaint(false);
    }
}

void EraserInstrument::paint(ImageArea &imageArea, bool, bool)
{
    QPainter painter(imageArea.getImage());
    painter.setPen(QPen(Qt::white,
                        DataSingleton::Instance()->getPenSize() * imageArea.getZoomFactor(),
                        Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

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
