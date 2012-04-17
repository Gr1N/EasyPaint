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
#include "../datasingleton.h"
#include <QtGui/QPainter>
#include <QtGui/QApplication>
#include <QtGui/QClipboard>


SelectionInstrument::SelectionInstrument(QObject *parent) :
    AbstractInstrument(parent)
{
    mIsSelectionExists = mIsSelectionMoving = mIsSelectionResizing
            = mIsPaint = mIsImageSelected = false;
}

void SelectionInstrument::mousePressEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if (mIsSelectionExists)
    {
        if (event->pos().x() > mTopLeftPoint.x() &&
                event->pos().x() < mBottomRightPoint.x() &&
                event->pos().y() > mTopLeftPoint.y() &&
                event->pos().y() < mBottomRightPoint.y())
        {
            mIsSelectionMoving = true;
            if(!mIsImageSelected)
            {
                imageArea.pushUndoCommand();
                mSelectedImage = imageArea.getImage()->copy(mTopLeftPoint.x(),
                                                  mTopLeftPoint.y(),
                                                  mWidth, mHeight);
                clearSelectionBackground(imageArea);
                mIsImageSelected = true;
            }
            mMoveDiffPoint = mBottomRightPoint - event->pos();
            return;
        }
        else if (event->pos().x() > mBottomRightPoint.x() &&
                 event->pos().x() < mBottomRightPoint.x() + 6 &&
                 event->pos().y() > mBottomRightPoint.y() &&
                 event->pos().y() < mBottomRightPoint.y() + 6)
        {
            mIsSelectionResizing = true;
            return;
        }
        else
        {
            *imageArea.getImage() = mImageCopy;
            if(mIsImageSelected)
            {
                paint(imageArea, true, false);
                mIsImageSelected = false;
            }
            mImageCopy = *imageArea.getImage();
            mIsSelectionExists = false;
            emit sendEnableCopyCutActions(false);
        }
    }
    if(event->button() == Qt::LeftButton)
    {
        mBottomRightPoint = event->pos();
        mTopLeftPoint = event->pos();
        mSelectedImage = QImage();
        mIsPaint = true;
        mImageCopy = *imageArea.getImage();
    }
}

void SelectionInstrument::mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if (mIsSelectionExists)
    {
        if (event->pos().x() > mTopLeftPoint.x() &&
                event->pos().x() < mBottomRightPoint.x() &&
                event->pos().y() > mTopLeftPoint.y() &&
                event->pos().y() < mBottomRightPoint.y())
        {
            imageArea.setCursor(Qt::SizeAllCursor);
        }
        else if (event->pos().x() > mBottomRightPoint.x() &&
                 event->pos().x() < mBottomRightPoint.x() + 6 &&
                 event->pos().y() > mBottomRightPoint.y() &&
                 event->pos().y() < mBottomRightPoint.y() + 6)
        {
            imageArea.setCursor(Qt::SizeFDiagCursor);
        }
        else
        {
            imageArea.restoreCursor();
        }

        if (mIsSelectionMoving)
        {

            mIsPaint = false;
            mBottomRightPoint = event->pos() +
                                           mMoveDiffPoint;
            mTopLeftPoint = event->pos() + mMoveDiffPoint -
                                  QPoint(mWidth, mHeight);
            *imageArea.getImage() = mImageCopy;
            paint(imageArea, false, true);
        }
        else if (mIsSelectionResizing)
        {
            mIsPaint = false;
            mWidth += event->pos().x() - mBottomRightPoint.x();
            mHeight += event->pos().y() - mBottomRightPoint.y();
            mBottomRightPoint = event->pos();
            *imageArea.getImage() = mImageCopy;
            paint(imageArea, false, true);
        }
        else
        {
            *imageArea.getImage() = mImageCopy;
        }
    }
    if (mIsPaint)
    {
        mBottomRightPoint = event->pos();
        *imageArea.getImage() = mImageCopy;
        paint(imageArea, false, true);
    }
}

void SelectionInstrument::mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea)
{
    int right = mTopLeftPoint.x() > mBottomRightPoint.x() ? mTopLeftPoint.x() : mBottomRightPoint.x();
    int bottom = mTopLeftPoint.y() > mBottomRightPoint.y() ? mTopLeftPoint.y() : mBottomRightPoint.y();
    int left = mTopLeftPoint.x() < mBottomRightPoint.x() ? mTopLeftPoint.x() : mBottomRightPoint.x();
    int top = mTopLeftPoint.y() < mBottomRightPoint.y() ? mTopLeftPoint.y() : mBottomRightPoint.y();
    mBottomRightPoint = QPoint(right, bottom);
    mTopLeftPoint = QPoint(left, top);

    if (mIsSelectionExists)
    {
        if(mIsSelectionMoving)
        {
            *imageArea.getImage() = mImageCopy;
            paint(imageArea, true, true);
            mIsPaint = false;
            mIsSelectionMoving = false;
        }
        else if (mIsSelectionResizing)
        {
            *imageArea.getImage() = mImageCopy;
            paint(imageArea, true, true);
            mIsPaint = false;
            mIsSelectionResizing = false;
        }
    }
    if (mIsPaint)
    {
        if (event->button() == Qt::LeftButton)
        {
            *imageArea.getImage() = mImageCopy;
            paint(imageArea, false, true);
            mIsPaint = false;
            if (mTopLeftPoint != mBottomRightPoint)
            {
                mIsSelectionExists = true;
                emit sendEnableCopyCutActions(true);
            }
        }
    }
}

void SelectionInstrument::paint(ImageArea &imageArea, bool isSelected, bool isDrawBorders)
{
    mHeight = fabs(mTopLeftPoint.y() - mBottomRightPoint.y());
    mWidth = fabs(mTopLeftPoint.x() - mBottomRightPoint.x());

    if (mWidth == 0 || mHeight == 0)
    {
        isDrawBorders = false;
    }

    if (isDrawBorders)
    {
        QPainter painter(imageArea.getImage());
        painter.setPen(QPen(Qt::blue, 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
        painter.setBackgroundMode(Qt::TransparentMode);

        if(mTopLeftPoint != mBottomRightPoint)
        {
            painter.drawRect(QRect(mTopLeftPoint - QPoint(1, 1), mBottomRightPoint));
        }

        imageArea.setEdited(true);
        painter.end();
        imageArea.update();
    }

    if (isSelected)
    {
        QPainter painter(imageArea.getImage());
        if(mTopLeftPoint != mBottomRightPoint)
        {
            QRect source(0, 0, mSelectedImage.width(), mSelectedImage.height());
            QRect target(mTopLeftPoint, mBottomRightPoint);
            painter.drawImage(target, mSelectedImage, source);
        }
        imageArea.setEdited(true);
        painter.end();
        imageArea.update();
    }
}

void SelectionInstrument::clearSelectionBackground(ImageArea &imageArea)
{
    QPainter blankPainter(imageArea.getImage());
    blankPainter.setPen(Qt::white);
    blankPainter.setBrush(QBrush(Qt::white));
    blankPainter.setBackgroundMode(Qt::OpaqueMode);
    blankPainter.drawRect(QRect(mTopLeftPoint - QPoint(1, 1), mBottomRightPoint));
    blankPainter.end();
    mImageCopy = *imageArea.getImage();
}

void SelectionInstrument::copyImage(ImageArea &imageArea)
{
    if (mIsSelectionExists)
    {
        QClipboard *globalClipboard = QApplication::clipboard();
        QImage copyImage;
        if(mIsImageSelected)
        {
            copyImage = mSelectedImage;
        }
        else
        {
            copyImage = imageArea.getImage()->copy(mTopLeftPoint.x(), mTopLeftPoint.y(), mWidth - 1, mHeight - 1);
        }
        globalClipboard->setImage(copyImage, QClipboard::Clipboard);
    }
}

void SelectionInstrument::cutImage(ImageArea &imageArea)
{
    if (mIsSelectionExists)
    {
        copyImage(imageArea);
        if (/*mSelectedImage != mPasteImage || !*/mIsImageSelected)
        {
            *imageArea.getImage() = mImageCopy;
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
        emit sendEnableCopyCutActions(false);
    }
}

void SelectionInstrument::pasteImage(ImageArea &imageArea)
{
    QClipboard *globalClipboard = QApplication::clipboard();
    if(mIsSelectionExists)
    {
        *imageArea.getImage() = mImageCopy;
        paint(imageArea, true, false);
        mImageCopy = *imageArea.getImage();
        imageArea.pushUndoCommand();
    }
    if (DataSingleton::Instance()->getInstrument() != CURSOR)
    {
        emit sendEnableSelectionInstrument(true);
    }
    mPasteImage = globalClipboard->image();
    if (!mPasteImage.isNull())
    {
        mSelectedImage = mPasteImage;
        mImageCopy = *imageArea.getImage();
        mTopLeftPoint = QPoint(0, 0);
        mBottomRightPoint = QPoint(mPasteImage.width(), mPasteImage.height());
        paint(imageArea, true, true);
        mIsImageSelected = mIsSelectionExists = true;
        emit sendEnableCopyCutActions(true);
        if (DataSingleton::Instance()->getInstrument() != CURSOR)
        {
            emit sendEnableSelectionInstrument(true);
        }
    }
}

void SelectionInstrument::clearSelection(ImageArea &imageArea)
{
    if (mIsSelectionExists)
    {
        *imageArea.getImage() = mImageCopy;
        paint(imageArea, mIsImageSelected, false);
        mImageCopy = *imageArea.getImage();
        mIsSelectionExists = mIsSelectionMoving
                = mIsSelectionResizing = mIsImageSelected = false;
        imageArea.update();
        emit sendEnableCopyCutActions(false);
    }
}

void SelectionInstrument::saveImageChanges(ImageArea &imageArea)
{
    mImageCopy = *imageArea.getImage();
}
