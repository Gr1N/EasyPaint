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

#ifndef CUSTOMFILTERSETTINGS_H
#define CUSTOMFILTERSETTINGS_H

#include <QWidget>
#include <QSpinBox>

#include "abstracteffectsettings.h"

class CustomFilterSettings : public AbstractEffectSettings
{
    Q_OBJECT
public:
    explicit CustomFilterSettings(QWidget *parent = 0);
    
    QList<double> virtual getConvolutionMatrix();

private:
    QDoubleSpinBox *mSpinBox_11;
    QDoubleSpinBox *mSpinBox_12;
    QDoubleSpinBox *mSpinBox_13;
    QDoubleSpinBox *mSpinBox_21;
    QDoubleSpinBox *mSpinBox_22;
    QDoubleSpinBox *mSpinBox_23;
    QDoubleSpinBox *mSpinBox_31;
    QDoubleSpinBox *mSpinBox_32;
    QDoubleSpinBox *mSpinBox_33;

    QDoubleSpinBox* createSpinBox();
};

#endif // CUSTOMFILTERSETTINGS_H
