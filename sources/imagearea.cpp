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
#include "datasingleton.h"
#include "undocommand.h"

#include "instruments/abstractinstrument.h"
#include "instruments/pencilinstrument.h"
#include "instruments/lineinstrument.h"
#include "instruments/eraserinstrument.h"
#include "instruments/rectangleinstrument.h"
#include "instruments/ellipseinstrument.h"
#include "instruments/fillinstrument.h"
#include "instruments/sprayinstrument.h"
#include "instruments/magnifierinstrument.h"
#include "instruments/colorpickerinstrument.h"
#include "instruments/selectioninstrument.h"
#include "instruments/curvelineinstrument.h"
#include "instruments/textinstrument.h"

#include "effects/abstracteffect.h"
#include "effects/negativeeffect.h"
#include "effects/grayeffect.h"
#include "effects/binarizationeffect.h"
#include "effects/gaussianblureffect.h"
#include "effects/gammaeffect.h"
#include "effects/sharpeneffect.h"
#include "effects/customeffect.h"

#include <QApplication>
#include <QPainter>
#include <QFileDialog>
#include <QtCore/QDebug>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPrinter>
#include <QPrintDialog>
#include <QtCore/QTimer>
#include <QImageReader>
#include <QImageWriter>
#include <QUndoStack>

ImageArea::ImageArea(const bool &isOpen, const QString &filePath, QWidget *parent) :
    QWidget(parent), mIsEdited(false), mIsPaint(false), mIsResize(false)
{
    setMouseTracking(true);

    mRightButtonPressed = false;
    mFilePath.clear();
    makeFormatsFilters();
    initializeImage();
    mZoomFactor = 1;

    mAdditionalTools = new AdditionalTools(this);

    mUndoStack = new QUndoStack(this);
    mUndoStack->setUndoLimit(DataSingleton::Instance()->getHistoryDepth());

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
    autoSaveTimer->setInterval(DataSingleton::Instance()->getAutoSaveInterval() * 1000);
    connect(autoSaveTimer, SIGNAL(timeout()), this, SLOT(autoSave()));
    connect(mAdditionalTools, SIGNAL(sendNewImageSize(QSize)), this, SIGNAL(sendNewImageSize(QSize)));

    autoSaveTimer->start();

    SelectionInstrument *selectionInstrument = new SelectionInstrument(this);
    connect(selectionInstrument, SIGNAL(sendEnableCopyCutActions(bool)), this, SIGNAL(sendEnableCopyCutActions(bool)));
    connect(selectionInstrument, SIGNAL(sendEnableSelectionInstrument(bool)), this, SIGNAL(sendEnableSelectionInstrument(bool)));

    // Instruments handlers
    mInstrumentsHandlers.fill(0, (int)INSTRUMENTS_COUNT);
    mInstrumentsHandlers[CURSOR] = selectionInstrument;
    mInstrumentsHandlers[PEN] = new PencilInstrument(this);
    mInstrumentsHandlers[LINE] = new LineInstrument(this);
    mInstrumentsHandlers[ERASER] = new EraserInstrument(this);
    mInstrumentsHandlers[RECTANGLE] = new RectangleInstrument(this);
    mInstrumentsHandlers[ELLIPSE] = new EllipseInstrument(this);
    mInstrumentsHandlers[FILL] = new FillInstrument(this);
    mInstrumentsHandlers[SPRAY] = new SprayInstrument(this);
    mInstrumentsHandlers[MAGNIFIER] = new MagnifierInstrument(this);
    mInstrumentsHandlers[COLORPICKER] = new ColorpickerInstrument(this);
    mInstrumentsHandlers[CURVELINE] = new CurveLineInstrument(this);
    mInstrumentsHandlers[TEXT] = new TextInstrument(this);

    // Effects handlers
    mEffectsHandlers.fill(0, (int)EFFECTS_COUNT);
    mEffectsHandlers[NEGATIVE] = new NegativeEffect(this);
    mEffectsHandlers[GRAY] = new GrayEffect(this);
    mEffectsHandlers[BINARIZATION] = new BinarizationEffect(this);
    mEffectsHandlers[GAUSSIANBLUR] = new GaussianBlurEffect(this);
    mEffectsHandlers[GAMMA] = new GammaEffect(this);
    mEffectsHandlers[SHARPEN] = new SharpenEffect(this);
    mEffectsHandlers[CUSTOM] = new CustomEffect(this);
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
                                                    mOpenFilter, 0,
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
    else
    {
        qDebug()<<QString("Can't open file %1").arg(filePath);
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
        clearSelection();
        mImage->save(mFilePath);
        mIsEdited = false;
    }
}

void ImageArea::saveAs()
{
    QString filter;
    QString fileName(getFileName());
    clearSelection();
    if(fileName.isEmpty())
    {
        fileName = tr("Untitled image");
    }
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save image..."), fileName, mSaveFilter,
                                                    &filter,
                                                    QFileDialog::DontUseNativeDialog);

    QApplication::setOverrideCursor(Qt::WaitCursor);
    //parse file extension
    if(!filePath.isEmpty())
    {
        QString extension;
        //we should test it on windows, because of different slashes
        QString temp = filePath.split("/").last();
        //if user entered some extension
        if(temp.contains('.'))
        {
            temp = temp.split('.').last();
            if(QImageWriter::supportedImageFormats().contains(temp.toLatin1()))
                extension = temp;
            else
                extension = "png"; //if format is unknown, save it as png format, but with user extension
        }
        else
        {
            extension = filter.split('.').last().remove(')');
            filePath += '.' + extension;
        }
        mImage->save(filePath, extension.toLatin1().data());
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

void ImageArea::applyEffect(EffectsEnum effect)
{
    mEffectHandler = mEffectsHandlers.at(effect);
    mEffectHandler->applyEffect(*this);
}

bool ImageArea::zoomImage(qreal factor)
{
    return mAdditionalTools->zoomImage(factor);
}

void ImageArea::copyImage()
{
    SelectionInstrument *instrument = static_cast <SelectionInstrument*> (mInstrumentsHandlers.at(CURSOR));
    instrument->copyImage(*this);
}

void ImageArea::pasteImage()
{
    if(DataSingleton::Instance()->getInstrument() != CURSOR)
        emit sendSetInstrument(CURSOR);
    SelectionInstrument *instrument = static_cast <SelectionInstrument*> (mInstrumentsHandlers.at(CURSOR));
    instrument->pasteImage(*this);
}

void ImageArea::cutImage()
{
    SelectionInstrument *instrument = static_cast <SelectionInstrument*> (mInstrumentsHandlers.at(CURSOR));
    instrument->cutImage(*this);
}

void ImageArea::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton &&
            event->pos().x() < mImage->rect().right() + 6 &&
            event->pos().x() > mImage->rect().right() &&
            event->pos().y() > mImage->rect().bottom() &&
            event->pos().y() < mImage->rect().bottom() + 6)
    {
        mIsResize = true;
        setCursor(Qt::SizeFDiagCursor);
    }
    else if(DataSingleton::Instance()->getInstrument() != NONE_INSTRUMENT)
    {
        mInstrumentHandler = mInstrumentsHandlers.at(DataSingleton::Instance()->getInstrument());
        mInstrumentHandler->mousePressEvent(event, *this);
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
    }

    if(DataSingleton::Instance()->getInstrument() != NONE_INSTRUMENT)
    {
        mInstrumentHandler = mInstrumentsHandlers.at(DataSingleton::Instance()->getInstrument());
        mInstrumentHandler->mouseMoveEvent(event, *this);
    }
}

void ImageArea::mouseReleaseEvent(QMouseEvent *event)
{
    if(mIsResize)
    {
       mIsResize = false;
       restoreCursor();
    }
    else if(DataSingleton::Instance()->getInstrument() != NONE_INSTRUMENT)
    {
        mInstrumentHandler = mInstrumentsHandlers.at(DataSingleton::Instance()->getInstrument());
        mInstrumentHandler->mouseReleaseEvent(event, *this);
    }
}

void ImageArea::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter(this);
    //QRect *rect = new QRect(event->rect());

    painter->setBrush(QBrush(QPixmap(":media/textures/transparent.jpg")));
    painter->drawRect(0, 0,
                      mImage->rect().right() - 1,
                      mImage->rect().bottom() - 1);

    painter->drawImage(event->rect(), *mImage, event->rect());

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
    case INSTRUMENTS_COUNT:
        break;
    case MAGNIFIER:
        mPixmap = new QPixmap(":/media/instruments-icons/cursor_loupe.png");
        mCurrentCursor = new QCursor(*mPixmap);
        setCursor(*mCurrentCursor);
        break;
    case NONE_INSTRUMENT:
        mCurrentCursor = new QCursor(Qt::ArrowCursor);
        setCursor(*mCurrentCursor);
        break;
    case CURSOR:
        mCurrentCursor = new QCursor(Qt::CrossCursor);
        setCursor(*mCurrentCursor);
        break;
    case ERASER: case PEN:
        ImageArea::drawCursor();
        mCurrentCursor = new QCursor(*mPixmap);
        setCursor(*mCurrentCursor);
        break;
    case COLORPICKER:
        mPixmap = new QPixmap(":/media/instruments-icons/cursor_pipette.png");
        mCurrentCursor = new QCursor(*mPixmap);
        setCursor(*mCurrentCursor);
        break;
    case RECTANGLE: case ELLIPSE: case LINE: case CURVELINE: case TEXT:
        mCurrentCursor = new QCursor(Qt::CrossCursor);
        setCursor(*mCurrentCursor);
        break;
    case SPRAY:
        mPixmap = new QPixmap(":/media/instruments-icons/cursor_spray.png");
        mCurrentCursor = new QCursor(*mPixmap);
        setCursor(*mCurrentCursor);
        break;
    case FILL:
        mPixmap = new QPixmap(":/media/instruments-icons/cursor_fill.png");
        mCurrentCursor = new QCursor(*mPixmap);
        setCursor(*mCurrentCursor);
        break;
    }
}

void ImageArea::drawCursor()
{
    QPainter painter;
    mPixmap = new QPixmap(25, 25);
    QPoint center(13, 13);
    switch(DataSingleton::Instance()->getInstrument())
    {
    case NONE_INSTRUMENT: case LINE: case COLORPICKER: case MAGNIFIER: case  SPRAY:
    case FILL: case RECTANGLE: case ELLIPSE: case CURSOR: case INSTRUMENTS_COUNT:
    case CURVELINE: case TEXT:
        break;
    case PEN: case ERASER:
        mPixmap->fill(QColor(0, 0, 0, 0));
        break;
    }
    painter.begin(mPixmap);
    switch(DataSingleton::Instance()->getInstrument())
    {
    case NONE_INSTRUMENT: case LINE: case COLORPICKER: case MAGNIFIER: case  SPRAY:
    case FILL: case RECTANGLE: case ELLIPSE: case CURSOR: case INSTRUMENTS_COUNT:
    case CURVELINE: case TEXT:
        break;
    case PEN:
        if(mRightButtonPressed)
        {
            painter.setPen(QPen(DataSingleton::Instance()->getSecondaryColor()));
            painter.setBrush(QBrush(DataSingleton::Instance()->getSecondaryColor()));
        }
        else
        {
            painter.setPen(QPen(DataSingleton::Instance()->getPrimaryColor()));
            painter.setBrush(QBrush(DataSingleton::Instance()->getPrimaryColor()));
        }
        painter.drawEllipse(center, DataSingleton::Instance()->getPenSize()/2,
                        DataSingleton::Instance()->getPenSize()/2);
        break;
    case ERASER:
        painter.setBrush(QBrush(Qt::white));
        painter.drawEllipse(center, DataSingleton::Instance()->getPenSize()/2,
                        DataSingleton::Instance()->getPenSize()/2);
        break;
    }
    painter.setPen(Qt::black);
    painter.drawPoint(13, 13);
    painter.drawPoint(13, 3);
    painter.drawPoint(13, 5);
    painter.drawPoint(13, 21);
    painter.drawPoint(13, 23);
    painter.drawPoint(3, 13);
    painter.drawPoint(5, 13);
    painter.drawPoint(21, 13);
    painter.drawPoint(23, 13);
    painter.setPen(Qt::white);
    painter.drawPoint(13, 12);
    painter.drawPoint(13, 14);
    painter.drawPoint(12, 13);
    painter.drawPoint(14, 13);
    painter.drawPoint(13, 4);
    painter.drawPoint(13, 6);
    painter.drawPoint(13, 20);
    painter.drawPoint(13, 22);
    painter.drawPoint(4, 13);
    painter.drawPoint(6, 13);
    painter.drawPoint(20, 13);
    painter.drawPoint(22, 13);
    painter.end();
}

void ImageArea::makeFormatsFilters()
{
    QList<QByteArray> ba = QImageReader::supportedImageFormats();
    //make "all supported" part
    mOpenFilter = "All supported (";
    foreach (QByteArray temp, ba)
        mOpenFilter += "*." + temp + " ";
    mOpenFilter[mOpenFilter.length() - 1] = ')'; //delete last space
    mOpenFilter += ";;";

    //using ";;" as separator instead of "\n", because Qt's docs recomended it :)
    if(ba.contains("png"))
        mOpenFilter += "Portable Network Graphics(*.png);;";
    if(ba.contains("bmp"))
        mOpenFilter += "Windows Bitmap(*.bmp);;";
    if(ba.contains("gif"))
        mOpenFilter += "Graphic Interchange Format(*.gif);;";
    if(ba.contains("jpg") || ba.contains("jpeg"))
        mOpenFilter += "Joint Photographic Experts Group(*.jpg *.jpeg);;";
    if(ba.contains("mng"))
        mOpenFilter += "Multiple-image Network Graphics(*.mng);;";
    if(ba.contains("pbm"))
        mOpenFilter += "Portable Bitmap(*.pbm);;";
    if(ba.contains("pgm"))
        mOpenFilter += "Portable Graymap(*.pgm);;";
    if(ba.contains("ppm"))
        mOpenFilter += "Portable Pixmap(*.ppm);;";
    if(ba.contains("tiff") || ba.contains("tif"))
        mOpenFilter += "Tagged Image File Format(*.tiff, *tif);;";
    if(ba.contains("xbm"))
        mOpenFilter += "X11 Bitmap(*.xbm);;";
    if(ba.contains("xpm"))
        mOpenFilter += "X11 Pixmap(*.xpm);;";
    if(ba.contains("svg"))
        mOpenFilter += "Scalable Vector Graphics(*.svg);;";

    mOpenFilter += "All Files(*.*)";

    //make saveFilter
    ba = QImageWriter::supportedImageFormats();
    if(ba.contains("png"))
        mSaveFilter += "Portable Network Graphics(*.png)";
    if(ba.contains("bmp"))
        mSaveFilter += ";;Windows Bitmap(*.bmp)";
    if(ba.contains("jpg") || ba.contains("jpeg"))
        mSaveFilter += ";;Joint Photographic Experts Group(*.jpg)";
    if(ba.contains("ppm"))
        mSaveFilter += ";;Portable Pixmap(*.ppm)";
    if(ba.contains("tiff") || ba.contains("tif"))
        mSaveFilter += ";;Tagged Image File Format(*.tiff)";
    if(ba.contains("xbm"))
        mSaveFilter += ";;X11 Bitmap(*.xbm)";
    if(ba.contains("xpm"))
        mSaveFilter += ";;X11 Pixmap(*.xpm)";
}

void ImageArea::saveImageChanges()
{
    foreach (AbstractInstrument* instrument, mInstrumentsHandlers)
    {
        if (AbstractSelection *selection = qobject_cast<AbstractSelection*>(instrument))
            selection->saveImageChanges(*this);
    }
}

void ImageArea::clearSelection()
{
    foreach (AbstractInstrument* instrument, mInstrumentsHandlers)
    {
        if (AbstractSelection *selection = qobject_cast<AbstractSelection*>(instrument))
            selection->clearSelection(*this);
    }
}

void ImageArea::pushUndoCommand(UndoCommand *command)
{
    if(command != 0)
        mUndoStack->push(command);
}
