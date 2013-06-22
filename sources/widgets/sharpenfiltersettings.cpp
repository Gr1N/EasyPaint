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

#include <QLabel>
#include <QLayout>

#include "sharpenfiltersettings.h"

SharpenFilterSettings::SharpenFilterSettings(QWidget *parent) :
    AbstractEffectSettings(parent)
{
    QLabel *label = new QLabel(tr("Intensity"), this);

    mIntensitySlider = new QSlider(Qt::Horizontal, this);
    mIntensitySlider->setTickPosition(QSlider::TicksBothSides);
    mIntensitySlider->setMinimum(1);
    mIntensitySlider->setMaximum(10);
    mIntensitySlider->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    connect(mIntensitySlider, SIGNAL(valueChanged(int)), this, SIGNAL(matrixChanged()));

    QVBoxLayout *vLayout = new QVBoxLayout();

    vLayout->addWidget(label);
    vLayout->addWidget(mIntensitySlider);
    vLayout->addStretch();
    setLayout(vLayout);
}

QList<double> SharpenFilterSettings::getConvolutionMatrix()
{
    QList<double> matrix;
    int intensity = mIntensitySlider->value();

    matrix << 0            << -(intensity)        << 0
           << -(intensity) << (intensity * 4) + 1 << -(intensity)
           << 0            << -(intensity)        << 0;

    return matrix;
}
