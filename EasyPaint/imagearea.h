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
     * @param parent Pointer for parent.
     */
    explicit ImageArea(const bool &isOpen = false, QWidget *parent = 0);
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
    inline void resizeImage() { mAdditionalTools->resizeImage(); }
    
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

    QImage *mImage,  /**< Main image. */
           mImageCopy; /**< Copy of main image, need for events. */
    QSize mBaseSize; /**< Base size of image. */
    PaintInstruments *mPaintInstruments;
    AdditionalTools *mAdditionalTools;
    Effects *mEffects;
    QString mFilePath; /**< Path where located image. */
    bool mIsEdited, mIsPaint, mIsResize;

signals:
    /**
     * @brief Send first color for ToolBar.
     *
     */
    void sendFirstColorView();
    /**
     * @brief Send second color for ToolBar.
     *
     */
    void sendSecondColorView();
    
public slots:

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    
};

#endif // IMAGEAREA_H
