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
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN Button OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "toolbar.h"
#include "colorchooser.h"
#include "../datasingleton.h"

#include <QToolButton>
#include <QGridLayout>
#include <QSpinBox>
#include <QAction>
#include <QtCore/QMap>

ToolBar::ToolBar(const QMap<InstrumentsEnum, QAction *> &actMap, QWidget *parent) :
    QToolBar(tr("Instruments"), parent), mActMap(actMap)
{
    setMovable(false);
    initializeItems();
    mPrevInstrumentSetted = false;
}

QToolButton* ToolBar::createToolButton(QAction *act)
{
    QToolButton *toolButton = new QToolButton();
    toolButton->setMinimumSize(QSize(30, 30));
    toolButton->setMaximumSize(QSize(30, 30));
    toolButton->setDefaultAction(act);
    toolButton->setStatusTip(act->text());
    return toolButton;
}

void ToolBar::initializeItems()
{
    mCursorButton = createToolButton(mActMap[CURSOR]);
    mEraserButton = createToolButton(mActMap[ERASER]);
    mPenButton = createToolButton(mActMap[PEN]);
    mLineButton = createToolButton(mActMap[LINE]);
    mColorPickerButton = createToolButton(mActMap[COLORPICKER]);
    mMagnifierButton = createToolButton(mActMap[MAGNIFIER]);
    mSprayButton = createToolButton(mActMap[SPRAY]);
    mFillButton = createToolButton(mActMap[FILL]);
    mRectangleButton = createToolButton(mActMap[RECTANGLE]);
    mEllipseButton = createToolButton(mActMap[ELLIPSE]);
    mCurveButton = createToolButton(mActMap[CURVELINE]);
    mTextButton = createToolButton(mActMap[TEXT]);

    QGridLayout *bLayout = new QGridLayout();
    bLayout->setMargin(3);
    bLayout->addWidget(mCursorButton, 0, 0);
    bLayout->addWidget(mEraserButton, 0, 1);
    bLayout->addWidget(mColorPickerButton, 1, 0);
    bLayout->addWidget(mMagnifierButton, 1, 1);
    bLayout->addWidget(mPenButton, 2, 0);
    bLayout->addWidget(mLineButton, 2, 1);
    bLayout->addWidget(mSprayButton, 3, 0);
    bLayout->addWidget(mFillButton, 3, 1);
    bLayout->addWidget(mRectangleButton, 4, 0);
    bLayout->addWidget(mEllipseButton, 4, 1);
    bLayout->addWidget(mCurveButton, 5, 0);
    bLayout->addWidget(mTextButton, 5, 1);

    QWidget *bWidget = new QWidget();
    bWidget->setLayout(bLayout);

    mPColorChooser = new ColorChooser(0, 0, 0, this);
    mPColorChooser->setStatusTip(tr("Primary color"));
    mPColorChooser->setToolTip(tr("Primary color"));
    connect(mPColorChooser, SIGNAL(sendColor(QColor)), this, SLOT(primaryColorChanged(QColor)));

    mSColorChooser = new ColorChooser(255, 255, 255, this);
    mSColorChooser->setStatusTip(tr("Secondary color"));
    mSColorChooser->setToolTip(tr("Secondary color"));
    connect(mSColorChooser, SIGNAL(sendColor(QColor)), this, SLOT(secondaryColorChanged(QColor)));

    QSpinBox *penSizeSpin = new QSpinBox();
    penSizeSpin->setRange(1, 20);
    penSizeSpin->setValue(1);
    penSizeSpin->setStatusTip(tr("Pen size"));
    penSizeSpin->setToolTip(tr("Pen size"));
    connect(penSizeSpin, SIGNAL(valueChanged(int)), this, SLOT(penValueChanged(int)));

    QGridLayout *tLayout = new QGridLayout();
    tLayout->setMargin(3);
    tLayout->addWidget(mPColorChooser, 0, 0);
    tLayout->addWidget(mSColorChooser, 0, 1);
    tLayout->addWidget(penSizeSpin, 1, 0, 1, 2);

    QWidget *tWidget = new QWidget();
    tWidget->setLayout(tLayout);

    addWidget(bWidget);
    addSeparator();
    addWidget(tWidget);
}

void ToolBar::penValueChanged(const int &value)
{
    DataSingleton::Instance()->setPenSize(value);
}

void ToolBar::primaryColorChanged(const QColor &color)
{
    DataSingleton::Instance()->setPrimaryColor(color);
}

void ToolBar::secondaryColorChanged(const QColor &color)
{
    DataSingleton::Instance()->setSecondaryColor(color);
}

void ToolBar::setPrimaryColorView()
{
    mPColorChooser->setColor(DataSingleton::Instance()->getPrimaryColor());
}

void ToolBar::setSecondaryColorView()
{
    mSColorChooser->setColor(DataSingleton::Instance()->getSecondaryColor());
}

void ToolBar::contextMenuEvent(QContextMenuEvent *)
{
}
