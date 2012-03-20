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

#ifndef PAINTINSTRUMENTS_H
#define PAINTINSTRUMENTS_H

#include <QtCore/QObject>
#include <QtGui/QColor>
#include <QtCore/QPoint>
#include <QtGui/QImage>

QT_BEGIN_NAMESPACE
class ImageArea;
QT_END_NAMESPACE

/**
 * @brief Class for implementation of painting instruments.
 *
 */
class PaintInstruments : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     *
     * @param pImageArea A pointer to ImageArea.
     * @param parent Pointer for parent.
     */
    explicit PaintInstruments(ImageArea *pImageArea, QObject *parent = 0);
    ~PaintInstruments();

    inline void setStartPoint(const QPoint &point) { mStartPoint = point; }
    inline void setEndPoint(const QPoint &point) { mEndPoint = point; }

    /**
     * @brief Pencil, line and lastic instruments.
     *
     * @param isSecondColor Flag which shows what color use: first or second.
     * @param isLastic Flag which show that instrument is lastic.
     */
    void line(bool isSecondColor, bool isEraser = false);
    /**
     * @brief Pipette instrument.
     *
     * @param isSecondColor Flag which shows what color use: first or second.
     */
    void colorPicker(bool isSecondColor);
    /**
     * @brief Rect instrument.
     *
     * @param isSecondColor Flag which shows paint whit brush or not.
     */
    void rectangle(bool isSecondColor);
    /**
     * @brief Ellipse instrument.
     *
     * @param isSecondColor Flag which shows paint whit brush or not.
     */
    void ellipse(bool isSecondColor);
    /**
     * @brief Spray instrument.
     *
     * @param isSecondColor Flag which shows what color use: first or second.
     */
    void spray(bool isSecondColor);
    /**
     * @brief Fill instrument.
     *
     * @param isSecondColor Flag which shows what color use: first or second.
     */
    void fill(bool isSecondColor);
    
private:
    void fillRecurs(int x, int y, QColor switchColor, QColor oldColor, QImage& tempImage);

    ImageArea *mPImageArea; /**< A pointer to ImageArea. */
    QPoint mStartPoint, mEndPoint;

signals:
    
public slots:
    
};

#endif // PAINTINSTRUMENTS_H
