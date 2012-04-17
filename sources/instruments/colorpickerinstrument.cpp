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
