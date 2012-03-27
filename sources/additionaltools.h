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

#ifndef ADDITIONALTOOLS_H
#define ADDITIONALTOOLS_H

#include <QtCore/QObject>

QT_BEGIN_NAMESPACE
class ImageArea;
class QSize;
QT_END_NAMESPACE

/**
 * @brief Class for implementation of additional tools which changing state of image.
 *
 */
class AdditionalTools : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     *
     * @param pImageArea A pointer to ImageArea.
     * @param parent Pointer for parent.
     */
    explicit AdditionalTools(ImageArea *pImageArea, QObject *parent = 0);
    ~AdditionalTools();

    /**
     * @brief Resize image area
     *
     * @param width
     * @param height
     */
    void resizeCanvas(int width, int height, bool flag = false);

    /**
     * @brief Resize image
     *
     */
    void resizeImage();

    /**
     * @brief Rotate image
     *
     * @param flag Left or right
     */
    void rotateImage(bool flag);
    /**
     * @brief Zoom image
     *
     * @param factor Scale factor
     * @return returns true in case of success
     */
    bool zoomImage(qreal factor);
    
private:
    ImageArea *mPImageArea; /**< A pointer to ImageArea */
    qreal mZoomedFactor; /**< Difference between original and current image */

signals:
    void sendNewImageSize(const QSize&);
    
public slots:
    
};

#endif // ADDITIONALTOOLS_H
