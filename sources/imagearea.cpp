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
#include <QtCore/QTimer>
#include <QtGui/QImageReader>
#include <QtGui/QImageWriter>

ImageArea::ImageArea(const bool &isOpen, const QString &filePath, QWidget *parent) :
    QWidget(parent), mIsEdited(false), mIsPaint(false), mIsResize(false)
{
    setMouseTracking(true);

    mRightButtonPressed = false;
    mFilePath.clear();
    makeFormatsFilters();
    initializeImage();
    mZoomFactor = 1;

    mPaintInstruments = new PaintInstruments(this);
    mAdditionalTools = new AdditionalTools(this);
    mEffects = new Effects(this);

    if(isOpen && filePath.isEmpty())
    {
        open();
    }
    else if(isOpen && !filePath.isEmpty())
    {
        open(filePath);
    }
    else
    {
        QPainter *painter = new QPainter(mImage);
        painter->fillRect(0, 0,
                          DataSingleton::Instance()->getBaseSize().width(),
                          DataSingleton::Instance()->getBaseSize().height(),
                          Qt::white);
        painter->end();

        resize(mImage->rect().right() + 6,
               mImage->rect().bottom() + 6);
    }

    QTimer *autoSaveTimer = new QTimer(this);
    autoSaveTimer->setInterval(DataSingleton::Instance()->getAutoSaveInterval());
    connect(autoSaveTimer, SIGNAL(timeout()), this, SLOT(autoSave()));
    connect(mAdditionalTools, SIGNAL(sendNewImageSize(QSize)), this, SIGNAL(sendNewImageSize(QSize)));

    autoSaveTimer->start();
}

ImageArea::~ImageArea()
{

}

void ImageArea::initializeImage()
{
    mImage = new QImage(DataSingleton::Instance()->getBaseSize(),
                        QImage::Format_ARGB32_Premultiplied);
}

void ImageArea::open()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open image..."), "",
                                                    openFilter, 0,
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



void ImageArea::open(const QString &filePath)
{
    if(mImage->load(filePath))
    {
        *mImage = mImage->convertToFormat(QImage::Format_ARGB32_Premultiplied);
        mFilePath = filePath;

        resize(mImage->rect().right() + 6,
               mImage->rect().bottom() + 6);
    }
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
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save image..."), fileName, saveFilter
                                                    /*tr("*.png;;*.jpg;;*.jpeg;;*.bmp;;*.xbm;;*.xpm")*/,
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

void ImageArea::autoSave()
{
    if(mIsEdited && !mFilePath.isEmpty() && DataSingleton::Instance()->getIsAutoSave())
    {
        mImage->save(mFilePath);
        mIsEdited = false;
    }
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

void ImageArea::resizeCanvas()
{
    mAdditionalTools->resizeCanvas(mImage->width(), mImage->height(), true);
    emit sendNewImageSize(mImage->size());
}

void ImageArea::rotateImage(bool flag)
{
    mAdditionalTools->rotateImage(flag);
    emit sendNewImageSize(mImage->size());
}

void ImageArea::zoomImage(qreal factor)
{
    mAdditionalTools->zoomImage(factor);
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
            setCursor(Qt::SizeFDiagCursor);
        }
        else
        {
            switch(DataSingleton::Instance()->getInstrument())
            {
            case NONE:
                break;
            case PIPETTE: case LOUPE:
                mIsPaint = true;
                break;
            case PEN: case LASTIC: case SPRAY: case FILL:
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
        mRightButtonPressed = true;
        restoreCursor();
        switch(DataSingleton::Instance()->getInstrument())
        {
        case NONE: case LASTIC:
            break;
        case PIPETTE: case LOUPE:
            mIsPaint = true;
            break;
        case PEN: case SPRAY:  case FILL:
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
         mAdditionalTools->resizeCanvas(event->x(), event->y());
         emit sendNewImageSize(mImage->size());
    }
    else if(event->pos().x() < mImage->rect().right() + 6 &&
            event->pos().x() > mImage->rect().right() &&
            event->pos().y() > mImage->rect().bottom() &&
            event->pos().y() < mImage->rect().bottom() + 6)
    {
        setCursor(Qt::SizeFDiagCursor);
    }
    else
    {
        restoreCursor();
    }
    if(event->pos().x() < mImage->width() &&
            event->pos().y() < mImage->height())
    {
        emit sendCursorPos(event->pos());
        if(DataSingleton::Instance()->getInstrument() == PIPETTE)
        {
            QRgb pixel(mImage->pixel(event->pos()));
            QColor getColor(pixel);
            emit sendColor(getColor);
        }
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
    {
       mIsResize = false;
       restoreCursor();
    }
    if(event->button() == Qt::LeftButton && mIsPaint)
    {
        mPaintInstruments->setEndPoint(event->pos());
        switch(DataSingleton::Instance()->getInstrument())
        {
        case NONE:
            break;
        case LOUPE:
            mAdditionalTools->zoomImage(2.0);
            setZoomFactor(2.0);
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
            mPaintInstruments->setStartPoint(event->pos());
            mPaintInstruments->setEndPoint(event->pos());
            mPaintInstruments->pipette(false);
            mIsPaint = false;
            emit sendFirstColorView();
            emit sendRestorePreviousInstrument();
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
        mRightButtonPressed = false;
        restoreCursor();
        mPaintInstruments->setEndPoint(event->pos());
        switch(DataSingleton::Instance()->getInstrument())
        {
        case NONE: case LASTIC:
            break;
        case LOUPE:
            mAdditionalTools->zoomImage(0.5);
            setZoomFactor(0.5);
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
            mPaintInstruments->setStartPoint(event->pos());
            mPaintInstruments->setEndPoint(event->pos());
            mPaintInstruments->pipette(true);
            mIsPaint = false;
            emit sendSecondColorView();
            emit sendRestorePreviousInstrument();
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

    painter->setBrush(QBrush(QPixmap(":media/textures/transparent.jpg")));
    painter->drawRect(mImage->rect());

    painter->drawImage(*rect, *mImage, *rect);

    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(Qt::black));
    painter->drawRect(QRect(mImage->rect().right(),
                            mImage->rect().bottom(), 6, 6));

    painter->end();
}

void ImageArea::restoreCursor()
{
    switch(DataSingleton::Instance()->getInstrument())
    {
    case LOUPE:
        pixmap = new QPixmap(":/media/instruments-icons/cursor_loupe.png");
        currentCursor = new QCursor(*pixmap);
        setCursor(*currentCursor);
        break;
    case NONE:
        currentCursor = new QCursor(Qt::ArrowCursor);
        setCursor(*currentCursor);
        break;
    case LASTIC: case PEN:
        ImageArea::drawCursor();
        currentCursor = new QCursor(*pixmap);
        setCursor(*currentCursor);
        break;
    case PIPETTE:
        pixmap = new QPixmap(":/media/instruments-icons/cursor_pipette.png");
        currentCursor = new QCursor(*pixmap);
        setCursor(*currentCursor);
        break;
    case RECT: case ELLIPSE: case LINE:
        currentCursor = new QCursor(Qt::CrossCursor);
        setCursor(*currentCursor);
        break;
    case SPRAY:
        pixmap = new QPixmap(":/media/instruments-icons/cursor_spray.png");
        currentCursor = new QCursor(*pixmap);
        setCursor(*currentCursor);
        break;
    case FILL:
        pixmap = new QPixmap(":/media/instruments-icons/cursor_fill.png");
        currentCursor = new QCursor(*pixmap);
        setCursor(*currentCursor);
        break;
    }
}

void ImageArea::drawCursor()
{
    QPainter painter;
    pixmap = new QPixmap(DataSingleton::Instance()->getPenSize() + 1,
                         DataSingleton::Instance()->getPenSize() + 1);
    switch(DataSingleton::Instance()->getInstrument())
    {
    case NONE: case LINE: case PIPETTE: case LOUPE: case  SPRAY:
    case FILL: case RECT: case ELLIPSE:
        break;
    case PEN: case LASTIC:
        pixmap->fill(QColor(0, 0, 0, 0));
        break;
    }
    painter.begin(pixmap);
    switch(DataSingleton::Instance()->getInstrument())
    {
    case NONE: case LINE: case PIPETTE: case LOUPE: case  SPRAY:
    case FILL: case RECT: case ELLIPSE:
        break;
    case PEN:
        if(mRightButtonPressed)
            painter.setBrush(QBrush(DataSingleton::Instance()->getSecondColor()));
        else
            painter.setBrush(QBrush(DataSingleton::Instance()->getFirstColor()));
        painter.drawEllipse(0, 0, DataSingleton::Instance()->getPenSize(),
                        DataSingleton::Instance()->getPenSize());
        break;
    case LASTIC:
        painter.setBrush(QBrush(Qt::white));
        painter.drawEllipse(0, 0, DataSingleton::Instance()->getPenSize(),
                        DataSingleton::Instance()->getPenSize());
        break;
    }
    painter.end();
}

void ImageArea::makeFormatsFilters()
{
    QList<QByteArray> ba = QImageReader::supportedImageFormats();
    //make "all supported" part
    openFilter = "All supported (";
    foreach (QByteArray temp, ba)
        openFilter += "*." + temp + " ";
    openFilter[openFilter.length() - 1] = ')'; //delete last space
    openFilter += ";;";

    //using ";;" as separator instead of "\n", because Qt's docs recomended it :)
    if(ba.contains("bmp"))
        openFilter += "Windows Bitmap(*.bmp);;";
    if(ba.contains("gif"))
        openFilter += "Graphic Interchange Format(*.gif);;";
    if(ba.contains("jpg") || ba.contains("jpeg"))
        openFilter += "Joint Photographic Experts Group(*.jpg *.jpeg);;";
    if(ba.contains("mng"))
        openFilter += "Multiple-image Network Graphics(*.mng);;";
    if(ba.contains("png"))
        openFilter += "Portable Network Graphics(*.png);;";
    if(ba.contains("pbm"))
        openFilter += "Portable Bitmap(*.pbm);;";
    if(ba.contains("pgm"))
        openFilter += "Portable Graymap(*.pgm);;";
    if(ba.contains("ppm"))
        openFilter += "Portable Pixmap(*.ppm);;";
    if(ba.contains("tiff") || ba.contains("tif"))
        openFilter += "Tagged Image File Format(*.tiff);;";
    if(ba.contains("xbm"))
        openFilter += "X11 Bitmap(*.xbm);;";
    if(ba.contains("xpm"))
        openFilter += "X11 Pixmap(*.xpm);;";
    if(ba.contains("svg"))
        openFilter += "Scalable Vector Graphics(*.svg);;";

    openFilter += "All Files(*.*)";

    //make saveFilter
    ba = QImageWriter::supportedImageFormats();
    if(ba.contains("bmp"))
        saveFilter += "Windows Bitmap(*.bmp)";
    if(ba.contains("jpg") || ba.contains("jpeg"))
        saveFilter += ";;Joint Photographic Experts Group(*.jpg *.jpeg)";
    if(ba.contains("png"))
        saveFilter += ";;Portable Network Graphics(*.png)";
    if(ba.contains("ppm"))
        saveFilter += ";;Portable Pixmap(*.ppm)";
    if(ba.contains("tiff") || ba.contains("tif"))
        saveFilter += ";;Tagged Image File Format(*.tiff)";
    if(ba.contains("xbm"))
        saveFilter += ";;X11 Bitmap(*.xbm)";
    if(ba.contains("xpm"))
        saveFilter += ";;X11 Pixmap(*.xpm)";
}
