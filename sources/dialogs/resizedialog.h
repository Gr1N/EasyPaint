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

#ifndef RISEZEDIALOG_H
#define RISEZEDIALOG_H

#include <QtGui/QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QSpinBox;
class QCheckBox;
QT_END_NAMESPACE

/**
 * @brief QDialog for resizing image.
 *
 */
class ResizeDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     *
     * @param size Current image size.
     * @param parent Pointer for parent.
     */
    explicit ResizeDialog(const QSize &size, QWidget *parent = 0);

    /**
     * @brief Return new image size
     *
     * @return QSize New size.
     */
    inline QSize getNewSize() { return QSize(mWidth, mHeight); }
    
private:
    void initializeGui();

    QLabel *mNewSizeLabel; /**< Label for showing new size */
    QSpinBox *mPixelWButton, *mPixelHButton,
             *mPercentWButton, *mPercentHButton;
    QCheckBox *mPreserveAspectBox;
    int mWidth, mHeight,
        mOrigWidth, mOrigHeight;

signals:
    
private slots:
    void pixelsButtonClicked(bool flag);
    void percentButtonClicked(bool flag);
    void pixelsWValueChanged(const int &value);
    void pixelsHValueChanged(const int &value);
    void percentWValueChanged(const int &value);
    void percentHValueChanged(const int &value);
    
};

#endif // RISEZEDIALOG_H
