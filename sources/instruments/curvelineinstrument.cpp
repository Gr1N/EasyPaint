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

#include "curvelineinstrument.h"
#include "../imagearea.h"
#include "../datasingleton.h"

#include <QPen>
#include <QPainter>
#include <QImage>

CurveLineInstrument::CurveLineInstrument(QObject *parent) :
    AbstractInstrument(parent)
{
    mPointsCount = 0;
}

void CurveLineInstrument::mousePressEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if(event->button() == Qt::LeftButton || event->button() == Qt::RightButton)
    {
        if(DataSingleton::Instance()->isResetCurve())
        {
            mPointsCount = 0;
            DataSingleton::Instance()->setResetCurve(false);
        }
        switch(mPointsCount)
        {
        //draw linear Bezier curve
        case 0:
            mImageCopy = *imageArea.getImage();
            mStartPoint = mEndPoint = mFirstControlPoint = mSecondControlPoint = event->pos();
            ++mPointsCount;
            break;
        //draw square Bezier curve
        case 1:
            mFirstControlPoint = mSecondControlPoint = event->pos();
            ++mPointsCount;
            break;
        //draw cubic Bezier curve
        case 2:
            mSecondControlPoint = event->pos();
            mPointsCount = 0;
            break;
        }
        imageArea.setIsPaint(true);
        makeUndoCommand(imageArea);
    }
}

void CurveLineInstrument::mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if(imageArea.isPaint())
    {
        switch(mPointsCount)
        {
        //draw linear Bezier curve
        case 1:
            mEndPoint = event->pos();
            break;
        //draw square Bezier curve
        case 2:
            mFirstControlPoint = mSecondControlPoint = event->pos();
            break;
        //draw cubic Bezier curve
        case 0:
            mSecondControlPoint = event->pos();
            break;
        }

        imageArea.setImage(mImageCopy);
        if(event->buttons() & Qt::LeftButton)
            paint(imageArea, false);
        else if(event->buttons() & Qt::RightButton)
            paint(imageArea, true);
    }
}

void CurveLineInstrument::mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if(imageArea.isPaint())
    {
        imageArea.setImage(mImageCopy);
        if(event->button() == Qt::LeftButton)
            paint(imageArea, false);
        else if(event->button() == Qt::RightButton)
            paint(imageArea, true);
        imageArea.setIsPaint(false);
    }
}

void CurveLineInstrument::paint(ImageArea &imageArea, bool isSecondaryColor, bool)
{
    QPainter painter(imageArea.getImage());
    //make Bezier curve path
    QPainterPath path;
    path.moveTo(mStartPoint);
    path.cubicTo(mFirstControlPoint, mSecondControlPoint, mEndPoint);
    //choose color
    painter.setPen(QPen(isSecondaryColor ? DataSingleton::Instance()->getSecondaryColor() :
                                           DataSingleton::Instance()->getPrimaryColor(),
                        DataSingleton::Instance()->getPenSize() * imageArea.getZoomFactor(),
                        Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    //draw Bezier curve with given path
    painter.strokePath(path, painter.pen());

    imageArea.setEdited(true);
    painter.end();
    imageArea.update();
}
