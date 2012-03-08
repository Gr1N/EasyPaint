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

#include "imagearea.h"
#include "paintinstruments.h"
#include "datasingleton.h"

#include <QtGui/QApplication>
#include <QtGui/QPainter>
#include <QtGui/QFileDialog>
#include <QtCore/QDebug>
#include <QtGui/QMouseEvent>
#include <QtGui/QPaintEvent>
#include <QtGui/QPrinter>
#include <QtGui/QPrintDialog>

ImageArea::ImageArea(const bool &isOpen, QWidget *parent) :
    QWidget(parent), mBaseSize(400, 300),
    mIsEdited(false), mIsPaint(false), mIsResize(false), mIsModified(false)
{
    setMouseTracking(true);

    mFilePath.clear();
    initializeImage();

    mPaintInstruments = new PaintInstruments(this);
    mAdditionalTools = new AdditionalTools(this);
    mEffects = new Effects(this);

    if(isOpen)
    {
        open();
    }
    else
    {
        QPainter *painter = new QPainter(mImage);
        painter->fillRect(0, 0, mBaseSize.width(), mBaseSize.height(), Qt::white);
        painter->end();

        resize(mImage->rect().right() + 6,
               mImage->rect().bottom() + 6);
    }
}

ImageArea::~ImageArea()
{

}

void ImageArea::initializeImage()
{
    mImage = new QImage(mBaseSize, QImage::Format_ARGB32_Premultiplied);
}

void ImageArea::open()
{
    QString filters("All suported (*.bmp *gif *.jpg *.jpeg *.mng *.png *.pbm"
                    "*.pgm *.ppm *.tiff *.xbm *.xpm *.svg)\n"
                    "Windows Bitmap(*.bmp)\n"
                    "Graphic Interchange Format(*.gif)\n"
                    "Joint Photographic Experts Group(*.jpg *.jpeg)\n"
                    "Multiple-image Network Graphics(*.mng)\n"
                    "Portable Network Graphics(*.png)\n"
                    "Portable Bitmap(*.pbm)\n"
                    "Portable Graymap(*.pgm)\n"
                    "Portable Pixmap(*.ppm)\n"
                    "Tagged Image File Format(*.tiff)\n"
                    "X11 Bitmap(*.xbm)\n"
                    "X11 Pixmap(*.xpm)\n"
                    "Scalable Vector Graphics(*.svg)\n"
                    "All Files(*.*)");
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open image..."), "",
                                                    filters, new QString(),
                                                    QFileDialog::DontUseNativeDialog);

    QApplication::setOverrideCursor(Qt::WaitCursor);
    if(!filePath.isEmpty())
    {
        mImage->load(filePath);
        *mImage = mImage->convertToFormat(QImage::Format_ARGB32_Premultiplied);
        mFilePath = filePath;

        resize(mImage->rect().right() + 6,
               mImage->rect().bottom() + 6);
    }
    QApplication::restoreOverrideCursor();
}

void ImageArea::save()
{
    if(mFilePath.isEmpty())
    {
        saveAs();
    }
    else
    {
        mImage->save(mFilePath);
        mIsEdited = false;
    }
}

void ImageArea::saveAs()
{
    QString filter;
    QString fileName(getFileName());
    if(fileName.isEmpty())
    {
        fileName = tr("Untitled image");
    }
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save image..."), fileName,
                                                    tr("*.png;;*.jpg;;*.jpeg;;*.bmp;;*.xbm;;*.xpm"),
                                                    &filter,
                                                    QFileDialog::DontUseNativeDialog);

    QApplication::setOverrideCursor(Qt::WaitCursor);
    if(!filePath.isEmpty())
    {
        for(int i(filter.size() - 1); i > 0; i--)
        {
            if(filter[i] != filePath[filePath.size() - filter.size() + i])
            {
                filePath += filter.mid(1);
                break;
            }
        }
        mImage->save(filePath);
        mFilePath = filePath;
        mIsEdited = false;
    }
    QApplication::restoreOverrideCursor();
}

void ImageArea::print()
{
    QPrinter *printer = new QPrinter();
    QPrintDialog *printDialog = new QPrintDialog(printer);
    if(printDialog->exec())
    {
        QPainter painter(printer);
        QRect rect = painter.viewport();
        QSize size = mImage->size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(mImage->rect());
        painter.drawImage(0, 0, *mImage);
    }
}

void ImageArea::resizeImage()
{
    mAdditionalTools->resizeImage();
    emit sendNewImageSize(mImage->size());
}

void ImageArea::rotateImage(bool flag)
{
    mAdditionalTools->rotateImage(flag);
    emit sendNewImageSize(mImage->size());
}

void ImageArea::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        if(event->pos().x() < mImage->rect().right() + 6 &&
                event->pos().x() > mImage->rect().right() &&
                event->pos().y() > mImage->rect().bottom() &&
                event->pos().y() < mImage->rect().bottom() + 6)
        {
            mIsResize = true;
        }
        else
        {
            switch(DataSingleton::Instance()->getInstrument())
            {
            case NONE: case LOUPE:
                break;
            case PEN: case LASTIC: case PIPETTE: case SPRAY: case FILL:
                mPaintInstruments->setStartPoint(event->pos());
                mPaintInstruments->setEndPoint(event->pos());
                mIsPaint = true;
                break;
            case LINE: case RECT: case ELLIPSE:
                mPaintInstruments->setStartPoint(event->pos());
                mPaintInstruments->setEndPoint(event->pos());
                mIsPaint = true;
                mImageCopy = *mImage;
                break;
            }
        }
    }
    if(event->button() == Qt::RightButton)
    {
        switch(DataSingleton::Instance()->getInstrument())
        {
        case NONE: case LASTIC: case LOUPE:
            break;
        case PEN: case PIPETTE: case SPRAY:  case FILL:
            mPaintInstruments->setStartPoint(event->pos());
            mPaintInstruments->setEndPoint(event->pos());
            mIsPaint = true;
            break;
        case LINE: case RECT: case ELLIPSE:
            mPaintInstruments->setStartPoint(event->pos());
            mPaintInstruments->setEndPoint(event->pos());
            mIsPaint = true;
            mImageCopy = *mImage;
            break;
        }
    }
}

void ImageArea::mouseMoveEvent(QMouseEvent *event)
{
    if(mIsResize)
    {
         mAdditionalTools->resizeArea(event->x(), event->y());
         emit sendNewImageSize(mImage->size());
    }
    if(event->pos().x() <= mImage->width() &&
            event->pos().y() <= mImage->height())
    {
        emit sendCursorPos(event->pos());
    }
    if((event->buttons() & Qt::LeftButton) && mIsPaint)
    {
        switch(DataSingleton::Instance()->getInstrument())
        {
        case NONE: case LOUPE: case PIPETTE:
        case FILL:
            break;
        case PEN:
            mPaintInstruments->setEndPoint(event->pos());
            mPaintInstruments->line(false);
            mPaintInstruments->setStartPoint(event->pos());
            break;
        case LASTIC:
            mPaintInstruments->setEndPoint(event->pos());
            mPaintInstruments->line(false, true);
            mPaintInstruments->setStartPoint(event->pos());
            break;
        case LINE:
            mPaintInstruments->setEndPoint(event->pos());
            *mImage = mImageCopy;
            mPaintInstruments->line(false);
            break;
        case RECT:
            mPaintInstruments->setEndPoint(event->pos());
            *mImage = mImageCopy;
            mPaintInstruments->rect(false);
            break;
        case ELLIPSE:
            mPaintInstruments->setEndPoint(event->pos());
            *mImage = mImageCopy;
            mPaintInstruments->ellipse(false);
            break;
        case SPRAY:
            mPaintInstruments->setEndPoint(event->pos());
            mPaintInstruments->spray(false);
            mPaintInstruments->setStartPoint(event->pos());
            break;
        }
    }
    if((event->buttons() & Qt::RightButton) && mIsPaint)
    {
        switch(DataSingleton::Instance()->getInstrument())
        {
        case NONE: case LASTIC: case LOUPE: case PIPETTE:
        case FILL:
            break;
        case PEN:
            mPaintInstruments->setEndPoint(event->pos());
            mPaintInstruments->line(true);
            mPaintInstruments->setStartPoint(event->pos());
            break;
        case LINE:
            mPaintInstruments->setEndPoint(event->pos());
            *mImage = mImageCopy;
            mPaintInstruments->line(true);
            break;
        case RECT:
            mPaintInstruments->setEndPoint(event->pos());
            *mImage = mImageCopy;
            mPaintInstruments->rect(true);
            break;
        case ELLIPSE:
            mPaintInstruments->setEndPoint(event->pos());
            *mImage = mImageCopy;
            mPaintInstruments->ellipse(true);
            break;
        case SPRAY:
            mPaintInstruments->setEndPoint(event->pos());
            mPaintInstruments->spray(true);
            mPaintInstruments->setStartPoint(event->pos());
            break;
        }
    }
}

void ImageArea::mouseReleaseEvent(QMouseEvent *event)
{
    if(mIsResize)
       mIsResize = false;
    if(event->button() == Qt::LeftButton && mIsPaint)
    {
        mPaintInstruments->setEndPoint(event->pos());
        switch(DataSingleton::Instance()->getInstrument())
        {
        case NONE: case LOUPE:
            break;
        case PEN:
            mPaintInstruments->line(false);
            mIsPaint = false;
            break;
        case LASTIC:
            mPaintInstruments->line(false, true);
            mIsPaint = false;
            break;
        case LINE:
            *mImage = mImageCopy;
            mPaintInstruments->line(false);
            mIsPaint = false;
            break;
        case PIPETTE:
            mPaintInstruments->pipette(false);
            mIsPaint = false;
            emit sendFirstColorView();
            break;
        case RECT:
            *mImage = mImageCopy;
            mPaintInstruments->rect(false);
            mIsPaint = false;
            break;
        case ELLIPSE:
            *mImage = mImageCopy;
            mPaintInstruments->ellipse(false);
            mIsPaint = false;
            break;
        case SPRAY:
            mPaintInstruments->spray(false);
            mIsPaint = false;
            break;
        case FILL:
            mPaintInstruments->fill(false);
            mIsPaint = false;
            break;
        }
    }
    if(event->button() == Qt::RightButton && mIsPaint)
    {
        mPaintInstruments->setEndPoint(event->pos());
        switch(DataSingleton::Instance()->getInstrument())
        {
        case NONE: case LASTIC: case LOUPE:
            break;
        case PEN:
            mPaintInstruments->line(true);
            mIsPaint = false;
            break;
        case LINE:
            *mImage = mImageCopy;
            mPaintInstruments->line(true);
            mIsPaint = false;
            break;
        case PIPETTE:
            mPaintInstruments->pipette(true);
            mIsPaint = false;
            emit sendSecondColorView();
            break;
        case RECT:
            *mImage = mImageCopy;
            mPaintInstruments->rect(true);
            mIsPaint = false;
            break;
        case ELLIPSE:
            *mImage = mImageCopy;
            mPaintInstruments->ellipse(true);
            mIsPaint = false;
            break;
        case SPRAY:
            mPaintInstruments->spray(true);
            mIsPaint = false;
            break;
        case FILL:
            mPaintInstruments->fill(true);
            mIsPaint = false;
            break;
        }
    }
}

void ImageArea::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter(this);
    QRect *rect = new QRect(event->rect());
    painter->drawImage(*rect, *mImage, *rect);

    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(Qt::black));
    painter->drawRect(QRect(mImage->rect().right(),
                            mImage->rect().bottom(), 6, 6));

    painter->end();
}
