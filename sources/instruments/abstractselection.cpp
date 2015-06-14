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

#include "abstractselection.h"
#include "../imagearea.h"
#include "../undocommand.h"
#include "math.h"

#include <QPainter>

AbstractSelection::AbstractSelection(QObject *parent) :
    AbstractInstrument(parent)
{
    mIsSelectionExists = mIsSelectionMoving = mIsSelectionResizing
            = mIsPaint = mIsImageSelected = mIsMouseMoved
            = mIsSelectionAdjusting = false;
}

void AbstractSelection::mousePressEvent(QMouseEvent *event, ImageArea &imageArea)
{
    mButton = event->button();
    mIsMouseMoved = false;
    if (mIsSelectionExists)
    {
        imageArea.setImage(mImageCopy);
        paint(imageArea);
        if (mButton == Qt::RightButton)
        {
            mIsSelectionAdjusting = true;
            startAdjusting(imageArea);
        }
        if (event->pos().x() > mTopLeftPoint.x() &&
                event->pos().x() < mBottomRightPoint.x() &&
                event->pos().y() > mTopLeftPoint.y() &&
                event->pos().y() < mBottomRightPoint.y())
        {
            if (!mIsSelectionAdjusting)
            {
                makeUndoCommand(imageArea);
            }
            if (!mIsImageSelected)
            {
                startMoving(imageArea);
                if (!mIsSelectionAdjusting)
                {
                    mIsImageSelected = true;
                }
            } 
            else
            {
                drawBorder(imageArea);
            }
            mIsSelectionMoving = true;
            mMoveDiffPoint = mBottomRightPoint - event->pos();
            return;
        }
        else if (event->pos().x() >= mBottomRightPoint.x() &&
                 event->pos().x() <= mBottomRightPoint.x() + 6 &&
                 event->pos().y() >= mBottomRightPoint.y() &&
                 event->pos().y() <= mBottomRightPoint.y() + 6)
        {
            if (!mIsSelectionAdjusting)
            {
                makeUndoCommand(imageArea);
            }
            startResizing(imageArea);
            mIsSelectionResizing = true;
            return;
        }
        else
        {
            clearSelection(imageArea);
        }
    }
    if (event->button() == Qt::LeftButton)
    {
        mBottomRightPoint = mTopLeftPoint = event->pos();
        mHeight =  mWidth = 0;
        mImageCopy = *imageArea.getImage();
        startSelection(imageArea);
        mIsPaint = true;
    }
}

void AbstractSelection::mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea)
{
    mIsMouseMoved = true;
    if (mIsSelectionExists)
    {
        if (mIsSelectionMoving)
        {
            mBottomRightPoint = event->pos() +
                                           mMoveDiffPoint;
            mTopLeftPoint = event->pos() + mMoveDiffPoint -
                                  QPoint(mWidth - 1, mHeight - 1);
            imageArea.setImage(mImageCopy);
            move(imageArea);
            drawBorder(imageArea);
            mIsPaint = false;
        }
        else if (mIsSelectionResizing)
        {
            mBottomRightPoint = event->pos();
            mHeight = abs(mTopLeftPoint.y() - mBottomRightPoint.y()) + 1;
            mWidth = abs(mTopLeftPoint.x() - mBottomRightPoint.x()) + 1;
            imageArea.setImage(mImageCopy);
            resize(imageArea);
            drawBorder(imageArea);
            mIsPaint = false;
        }
    }
    if (mIsPaint)
    {
        mBottomRightPoint = event->pos();
        mHeight = abs(mTopLeftPoint.y() - mBottomRightPoint.y()) + 1;
        mWidth = abs(mTopLeftPoint.x() - mBottomRightPoint.x()) + 1;
        imageArea.setImage(mImageCopy);
        drawBorder(imageArea);
        select(imageArea);
    }
    updateCursor(event, imageArea);
}

void AbstractSelection::mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea)
{
    int right = mTopLeftPoint.x() > mBottomRightPoint.x() ? mTopLeftPoint.x() : mBottomRightPoint.x();
    int bottom = mTopLeftPoint.y() > mBottomRightPoint.y() ? mTopLeftPoint.y() : mBottomRightPoint.y();
    int left = mTopLeftPoint.x() < mBottomRightPoint.x() ? mTopLeftPoint.x() : mBottomRightPoint.x();
    int top = mTopLeftPoint.y() < mBottomRightPoint.y() ? mTopLeftPoint.y() : mBottomRightPoint.y();
    mBottomRightPoint = QPoint(right, bottom);
    mTopLeftPoint = QPoint(left, top);
    if (mIsSelectionExists)
    {
        updateCursor(event, imageArea);
        if (mButton == Qt::RightButton && !mIsMouseMoved)
        {
            showMenu(imageArea);
            paint(imageArea);
            drawBorder(imageArea);
            mIsPaint = false;
            mIsSelectionMoving = mIsImageSelected = false;
        }
        else if (mIsSelectionMoving)
        {
            imageArea.setImage(mImageCopy);
            completeMoving(imageArea);
            paint(imageArea);
            drawBorder(imageArea);
            mIsPaint = false;
            mIsSelectionMoving = false;
        }
        else if (mIsSelectionResizing)
        {
            imageArea.setImage(mImageCopy);
            paint(imageArea);
            completeResizing(imageArea);
            paint(imageArea);
            drawBorder(imageArea);
            mIsPaint = false;
            mIsSelectionResizing = false;
        }
    }
    if (mIsPaint)
    {
        if (event->button() == Qt::LeftButton)
        {
            imageArea.setImage(mImageCopy);
            if (mTopLeftPoint != mBottomRightPoint)
            {
                imageArea.setImage(mImageCopy);
                paint(imageArea);
                completeSelection(imageArea);
                paint(imageArea);
                mIsSelectionExists = true;
            }
            drawBorder(imageArea);
            mIsPaint = false;
        }
    }
    mIsSelectionAdjusting = false;
}

void AbstractSelection::drawBorder(ImageArea &imageArea)
{
    if (mWidth > 1 && mHeight > 1)
    {
        QPainter painter(imageArea.getImage());
        painter.setPen(QPen(Qt::blue, 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
        painter.setBackgroundMode(Qt::TransparentMode);
        if(mTopLeftPoint != mBottomRightPoint)
        {
            painter.drawRect(QRect(mTopLeftPoint, mBottomRightPoint - QPoint(1, 1)));
        }
        imageArea.setEdited(true);
        painter.end();
        imageArea.update();
    }
}

void AbstractSelection::clearSelection(ImageArea &imageArea)
{
    if (mIsSelectionExists)
    {
        imageArea.setImage(mImageCopy);
        paint(imageArea);
        mImageCopy = *imageArea.getImage();
        mIsSelectionExists = mIsSelectionMoving = mIsSelectionResizing
                = mIsPaint = mIsImageSelected = false;
        imageArea.update(); 
        imageArea.restoreCursor();
        clear();
    }
}

void AbstractSelection::saveImageChanges(ImageArea &)
{
}

void AbstractSelection::updateCursor(QMouseEvent *event, ImageArea &imageArea)
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
        else if (event->pos().x() >= mBottomRightPoint.x() &&
                 event->pos().x() <= mBottomRightPoint.x() + 6 &&
                 event->pos().y() >= mBottomRightPoint.y() &&
                 event->pos().y() <= mBottomRightPoint.y() + 6)
        {
            imageArea.setCursor(Qt::SizeFDiagCursor);
        }
        else
        {
            imageArea.restoreCursor();
        }
    }
    else
    {
        imageArea.restoreCursor();
    }
}
