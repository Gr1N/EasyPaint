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

#include <QtGui/QLayout>

#include "customfiltersettings.h"

CustomFilterSettings::CustomFilterSettings(QWidget *parent) :
    AbstractEffectSettings(parent)
{
    mSpinBox_11 = new QDoubleSpinBox(this);
    mSpinBox_11->setButtonSymbols(QAbstractSpinBox::NoButtons);
    mSpinBox_12 = new QDoubleSpinBox(this);
    mSpinBox_12->setButtonSymbols(QAbstractSpinBox::NoButtons);
    mSpinBox_13 = new QDoubleSpinBox(this);
    mSpinBox_13->setButtonSymbols(QAbstractSpinBox::NoButtons);
    mSpinBox_21 = new QDoubleSpinBox(this);
    mSpinBox_21->setButtonSymbols(QAbstractSpinBox::NoButtons);
    mSpinBox_22 = new QDoubleSpinBox(this);
    mSpinBox_22->setButtonSymbols(QAbstractSpinBox::NoButtons);
    mSpinBox_23 = new QDoubleSpinBox(this);
    mSpinBox_23->setButtonSymbols(QAbstractSpinBox::NoButtons);
    mSpinBox_31 = new QDoubleSpinBox(this);
    mSpinBox_31->setButtonSymbols(QAbstractSpinBox::NoButtons);
    mSpinBox_32 = new QDoubleSpinBox(this);
    mSpinBox_32->setButtonSymbols(QAbstractSpinBox::NoButtons);
    mSpinBox_33 = new QDoubleSpinBox(this);
    mSpinBox_33->setButtonSymbols(QAbstractSpinBox::NoButtons);

    QGridLayout *gLayout = new QGridLayout();

    gLayout->addWidget(mSpinBox_11, 0, 0);
    gLayout->addWidget(mSpinBox_12, 0, 1);
    gLayout->addWidget(mSpinBox_13, 0, 2);
    gLayout->addWidget(mSpinBox_21, 1, 0);
    gLayout->addWidget(mSpinBox_22, 1, 1);
    gLayout->addWidget(mSpinBox_23, 1, 2);
    gLayout->addWidget(mSpinBox_31, 2, 0);
    gLayout->addWidget(mSpinBox_32, 2, 1);
    gLayout->addWidget(mSpinBox_33, 2, 2);

    setLayout(gLayout);
}

QList<double> CustomFilterSettings::getConvolutionMatrix()
{
   QList<double> matrix;

   matrix << mSpinBox_11->value() << mSpinBox_12->value() << mSpinBox_13->value()
          << mSpinBox_21->value() << mSpinBox_22->value() << mSpinBox_23->value()
          << mSpinBox_31->value() << mSpinBox_32->value() << mSpinBox_33->value();

   return matrix;
}
