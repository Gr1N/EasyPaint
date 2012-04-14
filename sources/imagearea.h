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

#ifndef IMAGEAREA_H
#define IMAGEAREA_H

#include "easypaintenums.h"
#include "effects.h"
#include "additionaltools.h"

#include <QtGui/QWidget>
#include <QtGui/QImage>

QT_BEGIN_NAMESPACE
class PaintInstruments;
class QUndoStack;
class AbstractInstrument;
QT_END_NAMESPACE

/**
 * @brief Base class which contains view image and controller for painting
 *
 */
class ImageArea : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     *
     * @param isOpen Flag which shows opens a new image or from file.
     * @param filePath Image file path to open.
     * @param parent Pointer for parent.
     */
    explicit ImageArea(const bool &isOpen = false, const QString &filePath = "", QWidget *parent = 0);
    ~ImageArea();

    /**
     * @brief Save image to file with existing path.
     *
     */
    void save();
    /**
     * @brief Save image to file with unknown path.
     *
     */
    void saveAs();
    /**
     * @brief Print image.
     *
     */
    void print();
    /**
     * @brief Resize image.
     *
     */
    void resizeImage();
    /**
     * @brief Resize canvas using resize dialog.
     *
     */
    void resizeCanvas();
    /**
     * @brief Rotate image.
     *
     * @param flag Rotate to left or to right.
     */
    void rotateImage(bool flag);

    inline QString getFileName() { return mFilePath.split('/').last(); }
    inline QImage* getImage() { return mImage; }
    inline void setImage(const QImage &image) { *mImage = image; }
    /**
     * @brief Set flag which shows that image edited.
     *
     * @param flag Boolean flag.
     */
    inline void setEdited(bool flag) { mIsEdited = flag; }
    /**
     * @brief Get flag which shows that image edited.
     *
     * @return bool Flag.
     */
    inline bool getEdited() { return mIsEdited; }
    /**
     * @brief Apply gray effect.
     *
     */
    inline void effectGray() { mEffects->gray(); }
    /**
     * @brief Apply negative effect.
     *
     */
    inline void effectNegative() { mEffects->negative(); }
    /**
     * @brief Restores previous cursor image.
     *
     */
    void restoreCursor();
    /**
     * @brief Zoom image
     *
     * @param factor Scale factor
     */
    bool zoomImage(qreal factor);
    inline void setZoomFactor(qreal factor) { mZoomFactor *= factor; }
    inline qreal getZoomFactor() { return mZoomFactor; }
    inline QUndoStack* getUndoStack() { return mUndoStack; }
    inline void setSelectionBottomRightPoint(const QPoint &point) { mSelectionBottomRightPoint = point; }
    inline void setSelectionTopLeftPoint(const QPoint &point) { mSelectionTopLeftPoint = point; }
    inline void setSelectionSize(int width, int height) { mSelectionWidth = width;  mSelectionHeight = height; }
    inline void setSelectedImage(const QImage &image) { mSelectedImage = image; }
    inline void setIsSelectonExists(bool selection) { mIsSelectionExists = selection; }
    inline void setIsImageSelected(bool selected) { mIsImageSelected = selected; }
    inline QPoint getSelectionBottomRightPoint() { return mSelectionBottomRightPoint; }
    inline QPoint getSelectionTopLeftPoint() { return mSelectionTopLeftPoint; }
    inline int getSelectionHeight() { return mSelectionHeight; }
    inline int getSelectionWidth() { return mSelectionWidth; }
    inline QImage getSelectedImage() { return mSelectedImage; }
    inline void setIsPaint(bool isPaint) { mIsPaint = isPaint; }
    inline bool isPaint() { return mIsPaint; }
    inline void emitPrimaryColorView() { emit sendPrimaryColorView(); }
    inline void emitSecondaryColorView() { emit sendSecondaryColorView(); }
    inline void emitColor(QColor &color) { emit sendColor(color); }
    inline void emitRestorePreviousInstrument() { emit sendRestorePreviousInstrument(); }

    /**
     * @brief Copying image to the clipboard.
     *
     */
    void copyImage();
    /**
     * @brief Paste image from the clipboard.
     *
     */
    void pasteImage();
    /**
     * @brief Cut image to the clipboard.
     *
     */
    void cutImage();
    /**
     * @brief Clears background image at selection area.
     *
     */
    void clearSelectionBackground();
    /**
     * @brief Roll back all image changes to image copy.
     *
     */
    void clearImageChanges();
    /**
     * @brief Save all image changes to image copy.
     *
     */
    void saveImageChanges();
    /**
     * @brief Removes selection borders from image and clears all selection varaibles to default.
     *
     */
    void clearSelection();
    /**
     * @brief Push current image to undo stack.
     *
     */
    void pushUndoCommand();
    
private:
    /**
     * @brief Initialize image with base params.
     *
     */
    void initializeImage();
    /**
     * @brief Open file from file.
     *
     */
    void open();
    /**
     * @brief Open file from file.
     *
     * @param filePath File path
     */
    void open(const QString &filePath);
    /**
     * @brief Draw cursor for instruments 'pencil' and 'lastic', that depends on pencil's width.
     *
     */
    void drawCursor();
    /**
     * @brief Creates filters' strings, which contain supported formats for reading & writing.
     *
     */
    void makeFormatsFilters();

    QImage *mImage,  /**< Main image. */
           mImageCopy, /**< Copy of main image, need for events. */ // ?????????????
           mSelectedImage, /**< Copy of selected image. */
           mPasteImage; /**< Image to paste */
    PaintInstruments *mPaintInstruments;
    AdditionalTools *mAdditionalTools;
    Effects *mEffects;
    QString mFilePath; /**< Path where located image. */
    QString mOpenFilter; /**< Supported open formats filter. */
    QString mSaveFilter; /**< Supported save formats filter. */
    bool mIsEdited, mIsPaint, mIsResize, mRightButtonPressed, mIsSelectionExists,
         mIsSelectionMoving, mIsSelectionResizing, mIsImageSelected;
    QPixmap *mPixmap;
    QCursor *mCurrentCursor;
    qreal mZoomFactor;
    QUndoStack *mUndoStack;
    QPoint mSelectionBottomRightPoint, mSelectionTopLeftPoint, mSelectionMoveDiffPoint;
    int mSelectionHeight, mSelectionWidth;
    QVector<AbstractInstrument*> mInstrumentsHandlers;
    AbstractInstrument *mInstrumentHandler;


signals:
    /**
     * @brief Send primary color for ToolBar.
     *
     */
    void sendPrimaryColorView();
    /**
     * @brief Send secondary color for ToolBar.
     *
     */
    void sendSecondaryColorView();
    void sendNewImageSize(const QSize&);
    void sendCursorPos(const QPoint&);
    void sendColor(const QColor&);
    /**
     * @brief Send signal to restore previous checked instrument for ToolBar.
     *
     */
    void sendRestorePreviousInstrument();
    /**
     * @brief Send signal to enable copy cut actions in menu.
     *
     */
    void sendEnableCopyCutActions(bool enable);
    
private slots:
    void autoSave();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    
};

#endif // IMAGEAREA_H
