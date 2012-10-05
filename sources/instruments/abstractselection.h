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

#ifndef ABSTRACTSELECTION_H
#define ABSTRACTSELECTION_H

#include "abstractinstrument.h"

QT_BEGIN_NAMESPACE
class QUndoStack;
class ImageArea;
QT_END_NAMESPACE

class AbstractSelection : public AbstractInstrument
{
    Q_OBJECT

public:
    explicit AbstractSelection(QObject *parent = 0);

    void mousePressEvent(QMouseEvent *event, ImageArea &imageArea);
    void mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea);
    void mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea);

    /**
     * @brief Removes selection borders from image and clears all selection varaibles to default.
     *
     * @param imageArea ImageArea for applying changes.
     */
    void clearSelection(ImageArea &imageArea);
    /**
     * @brief Save all image changes to image copy.
     *
     */
    void saveImageChanges(ImageArea &);

    virtual void startSelection(ImageArea &imageArea) = 0;
    virtual void startResizing(ImageArea &imageArea) = 0;
    virtual void startMoving(ImageArea &imageArea) = 0;
    virtual void select(ImageArea &imageArea) = 0;
    virtual void resize(ImageArea &imageArea) = 0;
    virtual void move(ImageArea &imageArea) = 0;
    virtual void completeSelection(ImageArea &imageArea) = 0;
    virtual void completeResizing(ImageArea &imageArea) = 0;
    virtual void completeMoving(ImageArea &imageArea) = 0;
    virtual void clear() = 0;

protected:
    void drawBorder(ImageArea &imageArea);
    void updateCursor(QMouseEvent *event, ImageArea &imageArea);

    QPoint mBottomRightPoint, mTopLeftPoint, mMoveDiffPoint;
    bool mIsPaint, mIsSelectionExists, mIsSelectionMoving, mIsSelectionResizing, mIsImageSelected;
    int mHeight, mWidth;

};

#endif // ABSTRACTSELECTION_H
