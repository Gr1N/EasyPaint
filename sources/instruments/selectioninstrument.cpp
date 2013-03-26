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

#include "selectioninstrument.h"
#include "../imagearea.h"
#include "../undocommand.h"
#include "math.h"

#include <QPainter>
#include <QApplication>
#include <QClipboard>

SelectionInstrument::SelectionInstrument(QObject *parent) :
    AbstractSelection(parent)
{
}

void SelectionInstrument::copyImage(ImageArea &imageArea)
{
    if (mIsSelectionExists)
    {
        imageArea.setImage(mImageCopy);
        QClipboard *globalClipboard = QApplication::clipboard();
        QImage copyImage;
        if(mIsImageSelected)
        {
            copyImage = mSelectedImage;
        }
        else
        {
            copyImage = imageArea.getImage()->copy(mTopLeftPoint.x(), mTopLeftPoint.y(), mWidth, mHeight);
        }
        globalClipboard->setImage(copyImage, QClipboard::Clipboard);
    }
}

void SelectionInstrument::cutImage(ImageArea &imageArea)
{
    if (mIsSelectionExists)
    {
        copyImage(imageArea);
        if(mIsSelectionExists)
        {
            imageArea.setImage(mImageCopy);
            paint(imageArea);
        }
        makeUndoCommand(imageArea);
        if (/*mSelectedImage != mPasteImage || !*/mIsImageSelected)
        {
            imageArea.setImage(mImageCopy);
        }
        else
        {
            clearSelectionBackground(imageArea);
        }
        mTopLeftPoint = QPoint(0, 0);
        mBottomRightPoint = QPoint(0, 0);
        mImageCopy = *imageArea.getImage();
        imageArea.update();
        mIsSelectionExists = false;
        imageArea.restoreCursor();
        emit sendEnableCopyCutActions(false);
    }
}

void SelectionInstrument::pasteImage(ImageArea &imageArea)
{
    QClipboard *globalClipboard = QApplication::clipboard();
    if(mIsSelectionExists)
    {
        imageArea.setImage(mImageCopy);
        paint(imageArea);
        mImageCopy = *imageArea.getImage();
    }
    makeUndoCommand(imageArea);
    mPasteImage = globalClipboard->image();
    if (!mPasteImage.isNull())
    {
        mSelectedImage = mPasteImage;
        mImageCopy = *imageArea.getImage();
        mTopLeftPoint = QPoint(0, 0);
        mBottomRightPoint = QPoint(mPasteImage.width(), mPasteImage.height()) - QPoint(1, 1);
        mHeight = mPasteImage.height();
        mWidth = mPasteImage.width();
        mIsImageSelected = mIsSelectionExists = true;
        paint(imageArea);
        drawBorder(imageArea);
        imageArea.restoreCursor();
        emit sendEnableCopyCutActions(true);
    }
}

void SelectionInstrument::startSelection(ImageArea &)
{
}

void SelectionInstrument::startResizing(ImageArea &imageArea)
{
    if (!mIsImageSelected)
    {
        clearSelectionBackground(imageArea);
    }
}

void SelectionInstrument::startMoving(ImageArea &imageArea)
{
    clearSelectionBackground(imageArea);
}

void SelectionInstrument::select(ImageArea &)
{
}

void SelectionInstrument::resize(ImageArea &)
{
}

void SelectionInstrument::move(ImageArea &)
{
}

void SelectionInstrument::completeSelection(ImageArea &imageArea)
{
    mSelectedImage = imageArea.getImage()->copy(mTopLeftPoint.x(),
                                                mTopLeftPoint.y(),
                                                mWidth, mHeight);
    emit sendEnableCopyCutActions(true);
}

void SelectionInstrument::completeResizing(ImageArea &imageArea)
{
    mSelectedImage = imageArea.getImage()->copy(mTopLeftPoint.x(),
                                                mTopLeftPoint.y(),
                                                mWidth, mHeight);
}

void SelectionInstrument::completeMoving(ImageArea &)
{
}

void SelectionInstrument::clearSelectionBackground(ImageArea &imageArea)
{
    QPainter blankPainter(imageArea.getImage());
    blankPainter.setPen(Qt::white);
    blankPainter.setBrush(QBrush(Qt::white));
    blankPainter.setBackgroundMode(Qt::OpaqueMode);
    blankPainter.drawRect(QRect(mTopLeftPoint, mBottomRightPoint - QPoint(1, 1)));
    blankPainter.end();
    mImageCopy = *imageArea.getImage();
}

void SelectionInstrument::clear()
{
    mSelectedImage = QImage();
    emit sendEnableCopyCutActions(false);
}

void SelectionInstrument::paint(ImageArea &imageArea, bool, bool)
{
    if (mIsSelectionExists)
    {
        if(mTopLeftPoint != mBottomRightPoint)
        {
            QPainter painter(imageArea.getImage());
            QRect source(0, 0, mSelectedImage.width(), mSelectedImage.height());
            QRect target(mTopLeftPoint, mBottomRightPoint);
            painter.drawImage(target, mSelectedImage, source);
            painter.end();
        }
        imageArea.setEdited(true);
        imageArea.update();
    }
}
