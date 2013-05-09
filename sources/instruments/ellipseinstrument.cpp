/*
 * This source file is part of EasyPaint.
 *
 * Copyright (c) 2012 EasyPaint <https://github.com/Gr1N/EasyPaint>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "ellipseinstrument.h"
#include "../imagearea.h"
#include "../datasingleton.h"

#include <QPen>
#include <QPainter>

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
        makeUndoCommand(imageArea);
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
