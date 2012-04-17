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

#ifndef SELECTIONINSTRUMENT_H
#define SELECTIONINSTRUMENT_H

#include "abstractinstrument.h"

QT_BEGIN_NAMESPACE
class QUndoStack;
QT_END_NAMESPACE

class SelectionInstrument : public AbstractInstrument
{
    Q_OBJECT

public:
    explicit SelectionInstrument(QObject *parent = 0);

    void mousePressEvent(QMouseEvent *event, ImageArea &imageArea);
    void mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea);
    void mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea);

    /**
     * @brief Clears background image at selection area.
     *
     * @param imageArea ImageArea for applying changes.
     */
    void clearSelectionBackground(ImageArea &imageArea);
    /**
     * @brief Copying image to the clipboard.
     *
     * @param imageArea ImageArea for applying changes.
     */
    void copyImage(ImageArea &imageArea);
    /**
     * @brief Paste image from the clipboard.
     *
     * @param imageArea ImageArea for applying changes.
     */
    void pasteImage(ImageArea &imageArea);
    /**
     * @brief Cut image to the clipboard.
     *
     * @param imageArea ImageArea for applying changes.
     */
    void cutImage(ImageArea &imageArea);
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
    void saveImageChanges(ImageArea &imageArea);


protected:
    void paint(ImageArea &imageArea, bool isSelected, bool isDrawBorders);

private:
    QPoint mBottomRightPoint, mTopLeftPoint, mMoveDiffPoint;
    bool mIsPaint, mIsSelectionExists, mIsSelectionMoving, mIsSelectionResizing, mIsImageSelected;
    QImage mSelectedImage, /**< Copy of selected image. */
           mPasteImage; /**< Image to paste */
    int mHeight, mWidth;

signals:
    void sendEnableCopyCutActions(bool enable);
    void sendEnableSelectionInstrument(bool enable);

};

#endif // SELECTIONINSTRUMENT_H
