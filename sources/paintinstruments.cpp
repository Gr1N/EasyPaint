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

#include "paintinstruments.h"
#include "imagearea.h"
#include "easypaintenums.h"
#include "datasingleton.h"

#include <QtGui/QPainter>
#include <QtGui/QLabel>
#include <math.h>
#include <QDebug>

PaintInstruments::PaintInstruments(ImageArea *pImageArea, QObject *parent) :
    QObject(parent)
{
    mPImageArea = pImageArea;
}


PaintInstruments::~PaintInstruments()
{

}

void PaintInstruments::selection(bool isSelected, bool isDrawBorders)
{
    int right = mStartPoint.x() > mEndPoint.x() ? mStartPoint.x() : mEndPoint.x();
    int bottom = mStartPoint.y() > mEndPoint.y() ? mStartPoint.y() : mEndPoint.y();
    int left = mStartPoint.x() < mEndPoint.x() ? mStartPoint.x() : mEndPoint.x();
    int top = mStartPoint.y() < mEndPoint.y() ? mStartPoint.y() : mEndPoint.y();
    int height = fabs(mStartPoint.y() - mEndPoint.y());
    int width = fabs(mStartPoint.x() - mEndPoint.x());
    mPImageArea->setSelectionBottomRightPoint(QPoint(right, bottom));
    mPImageArea->setSelectionSize(width, height);
    mPImageArea->setSelectionTopLeftPoint(QPoint(left, top));

    if (isDrawBorders)
    {
        QPainter painter(mPImageArea->getImage());
        painter.setPen(QPen(Qt::blue, 1 * mPImageArea->getZoomFactor(),
                            Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
        painter.setBackgroundMode(Qt::TransparentMode);

        if(mStartPoint != mEndPoint)
        {
            painter.drawRect(QRect(mStartPoint - QPoint(1, 1), mEndPoint));
        }

        mPImageArea->setEdited(true);
        painter.end();
        mPImageArea->update();
    }
    if (isSelected)
    {
        QPainter painter(mPImageArea->getImage());
        if(mStartPoint != mEndPoint)
        {
            QRect source(0, 0, mPImageArea->getSelectedImage().width(), mPImageArea->getSelectedImage().height());
            QRect target(mPImageArea->getSelectionTopLeftPoint(), mPImageArea->getSelectionBottomRightPoint());
            if(mSelectionImage.isNull())
            {
                painter.drawImage(target, mPImageArea->getSelectedImage(), source);
                mPImageArea->setSelectedImage(mPImageArea->getSelectedImage().
                                              scaled(width, height));
            }
            else
            {
                painter.drawImage(target, mSelectionImage, source);
                mPImageArea->setSelectedImage(
                            mSelectionImage.scaled(QSize(width, height)));
            }
        }
        mPImageArea->setEdited(true);
        painter.end();
        mPImageArea->update();
    }
}

