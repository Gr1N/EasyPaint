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

#include "sprayinstrument.h"
#include "../imagearea.h"
#include "../datasingleton.h"

#include <QPen>
#include <QPainter>
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
        makeUndoCommand(imageArea);
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
