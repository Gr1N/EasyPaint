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

#include "resizedialog.h"

#include <QLabel>
#include <QGridLayout>
#include <QRadioButton>
#include <QSpinBox>
#include <QtCore/QDebug>
#include <QDialogButtonBox>
#include <QCheckBox>
#include <QGroupBox>
#include <QVBoxLayout>

ResizeDialog::ResizeDialog(const QSize &size, QWidget *parent) :
    QDialog(parent), mWidth(size.width()), mHeight(size.height()),
    mOrigWidth(size.width()), mOrigHeight(size.height())
{
    initializeGui();
    layout()->setSizeConstraint(QLayout::SetFixedSize);
    setWindowTitle(tr("Resize"));
}

void ResizeDialog::initializeGui()
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

    QGridLayout *gLayout1 = new QGridLayout();
    gLayout1->addWidget(label1, 0, 0);
    gLayout1->addWidget(label2, 0, 1);
    gLayout1->addWidget(label3, 1, 0);
    gLayout1->addWidget(mNewSizeLabel, 1, 1);
    QGridLayout *gLayout2 = new QGridLayout();
    gLayout2->addWidget(pixelButton, 0, 0);
    gLayout2->addWidget(label4, 0, 1);
    gLayout2->addWidget(mPixelWButton, 0, 2);
    gLayout2->addWidget(label5, 0, 3);
    gLayout2->addWidget(mPixelHButton, 0, 4);
    gLayout2->addWidget(percentButton, 1, 0);
    gLayout2->addWidget(label6, 1, 1);
    gLayout2->addWidget(mPercentWButton, 1, 2);
    gLayout2->addWidget(label7, 1, 3);
    gLayout2->addWidget(mPercentHButton, 1, 4);
    gLayout2->addWidget(label8, 1, 5);
    gLayout2->addWidget(mPreserveAspectBox, 2, 0, 1, 6);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok |
                                                       QDialogButtonBox::Cancel);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QGroupBox *groupBox1 = new QGroupBox();
    groupBox1->setLayout(gLayout1);

    QGroupBox *groupBox2 = new QGroupBox();
    groupBox2->setLayout(gLayout2);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(groupBox1);
    mainLayout->addWidget(groupBox2);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);
}

void ResizeDialog::pixelsButtonClicked(bool flag)
{
    if(flag)
    {
        mPixelWButton->setEnabled(true);
        mPixelHButton->setEnabled(true);
        mPercentWButton->setEnabled(false);
        mPercentHButton->setEnabled(false);
    }
}

void ResizeDialog::percentButtonClicked(bool flag)
{
    if(flag)
    {
        mPixelWButton->setEnabled(false);
        mPixelHButton->setEnabled(false);
        mPercentWButton->setEnabled(true);
        mPercentHButton->setEnabled(true);
    }
}

void ResizeDialog::pixelsWValueChanged(const int &value)
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

void ResizeDialog::pixelsHValueChanged(const int &value)
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

void ResizeDialog::percentWValueChanged(const int &value)
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

void ResizeDialog::percentHValueChanged(const int &value)
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
