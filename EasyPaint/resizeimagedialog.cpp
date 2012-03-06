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

#include "resizeimagedialog.h"

#include <QtGui/QLabel>
#include <QtGui/QGridLayout>
#include <QtGui/QRadioButton>
#include <QtGui/QSpinBox>
#include <QtCore/QDebug>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QCheckBox>

ResizeImageDialog::ResizeImageDialog(const QSize &size, QWidget *parent) :
    QDialog(parent), mWidth(size.width()), mHeight(size.height()),
    mOrigWidth(size.width()), mOrigHeight(size.height())
{
    initializeGui();
    layout()->setSizeConstraint(QLayout::SetFixedSize);
    setWindowTitle(tr("Resize"));
}

void ResizeImageDialog::initializeGui()
{
    QLabel *label1 = new QLabel(tr("Original size:"));
    QLabel *label2 = new QLabel(QString("%1 x %2").arg(mWidth).arg(mHeight));
    QLabel *label3 = new QLabel(tr("New size:"));
    mNewSizeLabel = new QLabel(QString("%1 x %2").arg(mWidth).arg(mHeight));

    QRadioButton *pixelButton = new QRadioButton(tr("Pixels"));
    pixelButton->setChecked(true);
    connect(pixelButton, SIGNAL(clicked(bool)), this, SLOT(pixelsButtonClicked(bool)));

    mPixelWButton = new QSpinBox();
    mPixelWButton->setRange(1, 9999);
    mPixelWButton->setValue(mWidth);
    connect(mPixelWButton, SIGNAL(valueChanged(int)), this, SLOT(pixelsWValueChanged(int)));

    mPixelHButton = new QSpinBox();
    mPixelHButton->setRange(1, 9999);
    mPixelHButton->setValue(mHeight);
    connect(mPixelHButton, SIGNAL(valueChanged(int)), this, SLOT(pixelsHValueChanged(int)));

    QLabel *label4 = new QLabel(tr("Width:"));
    QLabel *label5 = new QLabel(tr("x Height:"));

    QRadioButton *percentButton = new QRadioButton(tr("Percent"));
    connect(percentButton, SIGNAL(clicked(bool)), this, SLOT(percentButtonClicked(bool)));

    mPercentWButton = new QSpinBox();
    mPercentWButton->setRange(1, 200);
    mPercentWButton->setValue(100);
    mPercentWButton->setEnabled(false);
    connect(mPercentWButton, SIGNAL(valueChanged(int)), this, SLOT(percentWValueChanged(int)));

    mPercentHButton = new QSpinBox();
    mPercentHButton->setRange(1, 200);
    mPercentHButton->setValue(100);
    mPercentHButton->setEnabled(false);
    connect(mPercentHButton, SIGNAL(valueChanged(int)), this, SLOT(percentHValueChanged(int)));

    QLabel *label6 = new QLabel(tr("Width:"));
    QLabel *label7 = new QLabel(tr("% x Height:"));
    QLabel *label8 = new QLabel(tr("%"));

    mPreserveAspectBox = new QCheckBox(tr("Preserve Aspect Ratio"));

    QGridLayout *gLayout = new QGridLayout();
    gLayout->addWidget(label1, 0, 0);
    gLayout->addWidget(label2, 0, 1);
    gLayout->addWidget(label3, 1, 0);
    gLayout->addWidget(mNewSizeLabel, 1, 1);
    gLayout->addWidget(pixelButton, 2, 0);
    gLayout->addWidget(label4, 2, 1);
    gLayout->addWidget(mPixelWButton, 2, 2);
    gLayout->addWidget(label5, 2, 3);
    gLayout->addWidget(mPixelHButton, 2, 4);
    gLayout->addWidget(percentButton, 3, 0);
    gLayout->addWidget(label6, 3, 1);
    gLayout->addWidget(mPercentWButton, 3, 2);
    gLayout->addWidget(label7, 3, 3);
    gLayout->addWidget(mPercentHButton, 3, 4);
    gLayout->addWidget(label8, 3, 5);
    gLayout->addWidget(mPreserveAspectBox, 4, 0, 1, 6);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok |
                                                       QDialogButtonBox::Cancel);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    gLayout->addWidget(buttonBox, 5, 0, 1, 6);

    setLayout(gLayout);
}

void ResizeImageDialog::pixelsButtonClicked(bool flag)
{
    if(flag)
    {
        mPixelWButton->setEnabled(true);
        mPixelHButton->setEnabled(true);
        mPercentWButton->setEnabled(false);
        mPercentHButton->setEnabled(false);
    }
}

void ResizeImageDialog::percentButtonClicked(bool flag)
{
    if(flag)
    {
        mPixelWButton->setEnabled(false);
        mPixelHButton->setEnabled(false);
        mPercentWButton->setEnabled(true);
        mPercentHButton->setEnabled(true);
    }
}

void ResizeImageDialog::pixelsWValueChanged(const int &value)
{
    if(mPreserveAspectBox->isChecked())
    {
        mHeight = mOrigHeight * value / mOrigWidth;
        mWidth = value;
        mPixelHButton->setValue(mHeight);
    }
    else
    {
        mWidth = value;
    }
    mNewSizeLabel->setText(QString("%1 x %2").arg(mWidth).arg(mHeight));
}

void ResizeImageDialog::pixelsHValueChanged(const int &value)
{
    if(mPreserveAspectBox->isChecked())
    {
        mWidth = mOrigWidth * value / mOrigHeight;
        mHeight = value;
        mPixelWButton->setValue(mWidth);
    }
    else
    {
        mHeight = value;
    }
    mNewSizeLabel->setText(QString("%1 x %2").arg(mWidth).arg(mHeight));
}

void ResizeImageDialog::percentWValueChanged(const int &value)
{
    if(mPreserveAspectBox->isChecked())
    {
        mPercentHButton->setValue(value);
        mWidth = mOrigWidth / 100 * value;
        mHeight = mOrigHeight / 100 * value;
    }
    else
    {
        mWidth = mOrigWidth / 100 * value;
    }
    mNewSizeLabel->setText(QString("%1 x %2").arg(mWidth).arg(mHeight));
}

void ResizeImageDialog::percentHValueChanged(const int &value)
{
    if(mPreserveAspectBox->isChecked())
    {
        mPercentWButton->setValue(value);
        mWidth = mOrigWidth / 100 * value;
        mHeight = mOrigHeight / 100 * value;
    }
    else
    {
        mHeight = mOrigHeight / 100 * value;
    }
    mNewSizeLabel->setText(QString("%1 x %2").arg(mWidth).arg(mHeight));
}
