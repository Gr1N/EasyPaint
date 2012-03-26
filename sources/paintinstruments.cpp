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

PaintInstruments::PaintInstruments(ImageArea *pImageArea, QObject *parent) :
    QObject(parent)
{
    mPImageArea = pImageArea;
}


PaintInstruments::~PaintInstruments()
{

}

void PaintInstruments::line(bool isSecondColor, bool isEraser)
{
    QPainter painter(mPImageArea->getImage());
    if(isEraser)
    {
        painter.setPen(QPen(Qt::white, DataSingleton::Instance()->getPenSize() * mPImageArea->getZoomFactor(),
                            Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    }
    else
    {
        if(isSecondColor)
        {
            painter.setPen(QPen(DataSingleton::Instance()->getSecondaryColor(),
                                DataSingleton::Instance()->getPenSize() * mPImageArea->getZoomFactor(),
                                Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        }
        else
        {
            painter.setPen(QPen(DataSingleton::Instance()->getPrimaryColor(),
                                DataSingleton::Instance()->getPenSize() * mPImageArea->getZoomFactor(),
                                Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        }
    }

    if(mStartPoint != mEndPoint)
    {
        painter.drawLine(mStartPoint, mEndPoint);
    }

    if(mStartPoint == mEndPoint)
    {
        painter.drawPoint(mStartPoint);
    }
    mPImageArea->setEdited(true);
//    int rad(DataSingleton::Instance()->getPenSize() + round(sqrt((mStartPoint.x() - mEndPoint.x()) *
//                                                                 (mStartPoint.x() - mEndPoint.x()) +
//                                                                 (mStartPoint.y() - mEndPoint.y()) *
//                                                                 (mStartPoint.y() - mEndPoint.y()))));
//    mPImageArea->update(QRect(mStartPoint, mEndPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
    painter.end();
    mPImageArea->update();
}

void PaintInstruments::colorPicker(bool isSecondColor)
{
    bool inArea(true);
    if(mStartPoint.x() < 0 || mStartPoint.y() < 0
            || mStartPoint.x() > mPImageArea->getImage()->width()
            || mStartPoint.y() > mPImageArea->getImage()->height())
        inArea = false;

    if(inArea && isSecondColor)
    {
        QRgb pixel(mPImageArea->getImage()->pixel(mStartPoint));
        QColor getColor(pixel);
        DataSingleton::Instance()->setSecondaryColor(getColor);
    }
    if(inArea)
    {
        QRgb pixel(mPImageArea->getImage()->pixel(mStartPoint));
        QColor getColor(pixel);
        DataSingleton::Instance()->setPrimaryColor(getColor);
    }
}

void PaintInstruments::rectangle(bool isSecondColor)
{
    QPainter painter(mPImageArea->getImage());
    painter.setPen(QPen(DataSingleton::Instance()->getPrimaryColor(),
                        DataSingleton::Instance()->getPenSize() * mPImageArea->getZoomFactor(),
                        Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    if(isSecondColor)
    {
        painter.setBrush(QBrush(DataSingleton::Instance()->getSecondaryColor()));
    }
    if(mStartPoint != mEndPoint)
    {
        painter.drawRect(QRect(mStartPoint, mEndPoint));
    }
    mPImageArea->setEdited(true);
//    int rad(DataSingleton::Instance()->getPenSize() + round(sqrt((mStartPoint.x() - mEndPoint.x()) *
//                                                                 (mStartPoint.x() - mEndPoint.x()) +
//                                                                 (mStartPoint.y() - mEndPoint.y()) *
//                                                                 (mStartPoint.y() - mEndPoint.y()))));
//    mPImageArea->update(QRect(mStartPoint, mEndPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
    painter.end();
    mPImageArea->update();
}

void PaintInstruments::ellipse(bool isSecondColor)
{
    QPainter painter(mPImageArea->getImage());
    painter.setPen(QPen(DataSingleton::Instance()->getPrimaryColor(),
                        DataSingleton::Instance()->getPenSize() * mPImageArea->getZoomFactor(),
                        Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    if(isSecondColor)
    {
        painter.setBrush(QBrush(DataSingleton::Instance()->getSecondaryColor()));
    }
    if(mStartPoint != mEndPoint)
    {
        painter.drawEllipse(QRect(mStartPoint, mEndPoint));
    }
    mPImageArea->setEdited(true);
//    int rad(DataSingleton::Instance()->getPenSize() + round(sqrt((mStartPoint.x() - mEndPoint.x()) *
//                                                                 (mStartPoint.x() - mEndPoint.x()) +
//                                                                 (mStartPoint.y() - mEndPoint.y()) *
//                                                                 (mStartPoint.y() - mEndPoint.y()))));
//    mPImageArea->update(QRect(mStartPoint, mEndPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
    painter.end();
    mPImageArea->update();
}

void PaintInstruments::spray(bool isSecondColor)
{
    QPainter painter(mPImageArea->getImage());
    if(isSecondColor)
    {
        painter.setPen(QPen(DataSingleton::Instance()->getSecondaryColor(),
                            sqrt(DataSingleton::Instance()->getPenSize() * mPImageArea->getZoomFactor()),
                            Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    }
    else
    {
        painter.setPen(QPen(DataSingleton::Instance()->getPrimaryColor(),
                            sqrt(DataSingleton::Instance()->getPenSize() * mPImageArea->getZoomFactor()),
                            Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    }

    int x, y;
    for(int i(0); i < 12; i++)
    {
        switch(i) {
        case 0: case 1: case 2: case 3:
            x = (qrand() % 5 - 2)
                    * sqrt(DataSingleton::Instance()->getPenSize() * mPImageArea->getZoomFactor());
            y = (qrand() % 5 - 2)
                    * sqrt(DataSingleton::Instance()->getPenSize() * mPImageArea->getZoomFactor());
            break;
        case 4: case 5: case 6: case 7:
            x = (qrand() % 10 - 4)
                    * sqrt(DataSingleton::Instance()->getPenSize() * mPImageArea->getZoomFactor());
            y = (qrand() % 10 - 4)
                    * sqrt(DataSingleton::Instance()->getPenSize() * mPImageArea->getZoomFactor());
            break;
        case 8: case 9: case 10: case 11:
            x = (qrand() % 15 - 7)
                    * sqrt(DataSingleton::Instance()->getPenSize() * mPImageArea->getZoomFactor());
            y = (qrand() % 15 - 7)
                    * sqrt(DataSingleton::Instance()->getPenSize() * mPImageArea->getZoomFactor());
            break;
        }
        painter.drawPoint(mEndPoint.x() + x,
                         mEndPoint.y() + y);
    }
    mPImageArea->setEdited(true);
    painter.end();
    mPImageArea->update();
}

void PaintInstruments::fill(bool isSecondColor)
{
    QColor switchColor;
    if(!isSecondColor)
    {
        switchColor = DataSingleton::Instance()->getPrimaryColor();
    }
    else
    {
        switchColor = DataSingleton::Instance()->getSecondaryColor();
    }

    QRgb pixel(mPImageArea->getImage()->pixel(mStartPoint));
    QColor oldColor(pixel);

    if(switchColor != oldColor)
    {
        fillRecurs(mStartPoint.x(), mStartPoint.y(),
                       switchColor, oldColor,
                       *mPImageArea->getImage());
    }

    mPImageArea->setEdited(true);
    mPImageArea->update();
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
            painter.drawRect(QRect(mStartPoint, mEndPoint));
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
            QRect source(mPImageArea->getSelectedTopLeftPoint(), mPImageArea->getSelectedBottomRightPoint());
            QRect target(mPImageArea->getSelectionTopLeftPoint(), mPImageArea->getSelectionBottomRightPoint());
            painter.drawImage(target, *(mPImageArea->getImage()), source);
        }
        mPImageArea->setEdited(true);
        painter.end();
        mPImageArea->update();
    }
}

void PaintInstruments::fillRecurs(int x, int y, QColor switchColor, QColor oldColor, QImage &tempImage)
{
    int temp_x(x), left_x(0);
    while(1)
    {
        QRgb pixsel(tempImage.pixel(temp_x, y));
        QColor currentColor;
        currentColor.setRgb(pixsel);
        if(currentColor != oldColor)
            break;
        pixsel = switchColor.rgb();
        tempImage.setPixel(temp_x, y, pixsel);
        if(temp_x > 0)
        {
            temp_x--;
            left_x = temp_x;
        }
        else
            break;
    }

    int right_x(0);
    temp_x = x + 1;
    while(1)
    {
        QRgb pixsel(tempImage.pixel(temp_x, y));
        QColor currentColor;
        currentColor.setRgb(pixsel);
        if(currentColor != oldColor)
            break;
        pixsel = switchColor.rgb();
        tempImage.setPixel(temp_x, y, pixsel);
        if(temp_x < tempImage.width() - 1)
        {
            temp_x++;
            right_x = temp_x;
        }
        else
            break;
    }

    for(int x_(left_x+1); x_ < right_x; x_++)
    {
        if(y < 1)
            break;
        if(right_x > tempImage.width())
            break;
        QRgb pixsel(tempImage.pixel(x_, y-1));
        QColor currentColor;
        currentColor.setRgb(pixsel);
        if(currentColor == oldColor && currentColor != switchColor)
            fillRecurs(x_, y-1, switchColor, oldColor, tempImage);
    }
    for(int x_(left_x+1); x_ < right_x; x_++)
    {
        if(y >= tempImage.height() - 1)
            break;
        if(right_x > tempImage.width())
            break;
        QRgb pixsel(tempImage.pixel(x_, y+1));
        QColor currentColor;
        currentColor.setRgb(pixsel);
        if(currentColor == oldColor && currentColor != switchColor)
            fillRecurs(x_, y+1, switchColor, oldColor, tempImage);
    }
}
