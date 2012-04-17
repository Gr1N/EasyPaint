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

#include <QtGui/QToolButton>
#include <QtGui/QGridLayout>
#include <QtGui/QSpinBox>

ToolBar::ToolBar(QWidget *parent) :
    QToolBar(tr("Instruments"), parent)
{
    setMovable(false);
    initializeItems();
    mPrevInstrumentSetted = false;
}

QToolButton* ToolBar::createToolButton(const QString &name, const QString &iconPath)
{
    QToolButton *toolButton = new QToolButton();
    toolButton->setMinimumSize(QSize(30, 30));
    toolButton->setMaximumSize(QSize(30, 30));
    toolButton->setIcon(QPixmap(iconPath));
    toolButton->setStatusTip(name);
    toolButton->setToolTip(name);
    toolButton->setCheckable(true);
    return toolButton;
}

void ToolBar::initializeItems()
{
    mCursorButton = createToolButton(tr("Selection"), ":/media/instruments-icons/cursor.png");
    connect(mCursorButton, SIGNAL(toggled(bool)), this, SLOT(setCursor(bool)));

    mEraserButton = createToolButton(tr("Eraser"), ":/media/instruments-icons/lastic.png");
    connect(mEraserButton, SIGNAL(toggled(bool)), this, SLOT(setLastic(bool)));

    mPenButton = createToolButton(tr("Pen"), ":/media/instruments-icons/pencil.png");
    connect(mPenButton, SIGNAL(toggled(bool)), this, SLOT(setPen(bool)));

    mLineButton = createToolButton(tr("Line"), ":/media/instruments-icons/line.png");
    connect(mLineButton, SIGNAL(toggled(bool)), this, SLOT(setLine(bool)));

    mColorPickerButton = createToolButton(tr("Color picker"), ":/media/instruments-icons/pipette.png");
    connect(mColorPickerButton, SIGNAL(toggled(bool)), this, SLOT(setPipette(bool)));

    mMagnifierButton = createToolButton(tr("Magnifier"), ":/media/instruments-icons/loupe.png");
    connect(mMagnifierButton, SIGNAL(toggled(bool)), this, SLOT(setLoupe(bool)));

    mSprayButton = createToolButton(tr("Spray"), ":/media/instruments-icons/spray.png");
    connect(mSprayButton, SIGNAL(toggled(bool)), this, SLOT(setSpray(bool)));

    mFillButton = createToolButton(tr("Fill"), ":/media/instruments-icons/fill.png");
    connect(mFillButton, SIGNAL(toggled(bool)), this, SLOT(setFill(bool)));

    mRectangleButton = createToolButton(tr("Rectangle"), ":/media/instruments-icons/rectangle.png");
    connect(mRectangleButton, SIGNAL(toggled(bool)), this, SLOT(setRect(bool)));

    mEllipseButton = createToolButton(tr("Ellipse"), ":/media/instruments-icons/ellipse.png");
    connect(mEllipseButton, SIGNAL(toggled(bool)), this, SLOT(setEllipse(bool)));


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

void ToolBar::setAllButtonsUnchecked(QToolButton *button)
{
    if(button != mCursorButton)
    {
        mCursorButton->setChecked(false);
        if (DataSingleton::Instance()->getPreviousInstrument() == CURSOR)
        {
            emit sendClearImageSelection();
        }
    }
    if(button != mEraserButton)
        mEraserButton->setChecked(false);
    if(button != mPenButton)
        mPenButton->setChecked(false);
    if(button != mLineButton)
        mLineButton->setChecked(false);
    if(button != mColorPickerButton)
    {
        mColorPickerButton->setChecked(false);
        emit sendClearStatusBarColor();
    }
    if(button != mMagnifierButton)
        mMagnifierButton->setChecked(false);
    if(button != mSprayButton)
        mSprayButton->setChecked(false);
    if(button != mFillButton)
        mFillButton->setChecked(false);
    if(button != mRectangleButton)
        mRectangleButton->setChecked(false);
    if(button != mEllipseButton)
        mEllipseButton->setChecked(false);
}

void ToolBar::setInstrumentChecked(InstrumentsEnum instrument)
{
    setAllButtonsUnchecked(NULL);
    switch(instrument)
    {
    case NONE: case COUNT:
        break;
    case CURSOR:
        mCursorButton->setChecked(true);
        break;
    case ERASER:
        mEraserButton->setChecked(true);
        break;
    case COLORPICKER:
        mColorPickerButton->setChecked(true);
        break;
    case MAGNIFIER:
        mMagnifierButton->setChecked(true);
        break;
    case PEN:
        mPenButton->setChecked(true);
        break;
    case LINE:
        mLineButton->setChecked(true);
        break;
    case SPRAY:
        mSprayButton->setChecked(true);
        break;
    case FILL:
        mFillButton->setChecked(true);
        break;
    case RECTANGLE:
        mRectangleButton->setChecked(true);
        break;
    case ELLIPSE:
        mEllipseButton->setChecked(true);
        break;
    }
}

void ToolBar::setCursor(const bool &state)
{
    if(state)
    {
        setAllButtonsUnchecked(mCursorButton);
        mCursorButton->setChecked(true);
        DataSingleton::Instance()->setInstrument(CURSOR);
        emit sendInstrumentChecked(CURSOR);
    }
    else
    {
        setAllButtonsUnchecked(NULL);
        DataSingleton::Instance()->setInstrument(NONE);
        emit sendInstrumentChecked(NONE);
        DataSingleton::Instance()->setPreviousInstrument(CURSOR);
    }
}

void ToolBar::setLastic(const bool &state)
{
    if(state)
    {
        setAllButtonsUnchecked(mEraserButton);
        mEraserButton->setChecked(true);
        DataSingleton::Instance()->setInstrument(ERASER);
        emit sendInstrumentChecked(ERASER);
    }
    else
    {
        setAllButtonsUnchecked(NULL);
        DataSingleton::Instance()->setInstrument(NONE);
        emit sendInstrumentChecked(NONE);
    }
}

void ToolBar::setPen(const bool &state)
{
    if(state)
    {
        setAllButtonsUnchecked(mPenButton);
        mPenButton->setChecked(true);
        DataSingleton::Instance()->setInstrument(PEN);
        emit sendInstrumentChecked(PEN);
    }
    else
    {
        setAllButtonsUnchecked(NULL);
        DataSingleton::Instance()->setInstrument(NONE);
        emit sendInstrumentChecked(NONE);
    }
}

void ToolBar::setLine(const bool &state)
{
    if(state)
    {
        setAllButtonsUnchecked(mLineButton);
        mLineButton->setChecked(true);
        DataSingleton::Instance()->setInstrument(LINE);
        emit sendInstrumentChecked(LINE);
    }
    else
    {
        setAllButtonsUnchecked(NULL);
        DataSingleton::Instance()->setInstrument(NONE);
        emit sendInstrumentChecked(NONE);
    }
}

void ToolBar::setPipette(const bool &state)
{
    if(state)
    {
        if (!mPrevInstrumentSetted)
        {
            DataSingleton::Instance()->setPreviousInstrument(DataSingleton::Instance()->getInstrument());
            mPrevInstrumentSetted = true;
        }
        setAllButtonsUnchecked(mColorPickerButton);
        mColorPickerButton->setChecked(true);
        DataSingleton::Instance()->setInstrument(COLORPICKER);
        emit sendInstrumentChecked(COLORPICKER);
    }
    else
    {
        setAllButtonsUnchecked(NULL);
        DataSingleton::Instance()->setInstrument(NONE);
        emit sendInstrumentChecked(NONE);
    }
}

void ToolBar::setLoupe(const bool &state)
{
    if(state)
    {
        setAllButtonsUnchecked(mMagnifierButton);
        mMagnifierButton->setChecked(true);
        DataSingleton::Instance()->setInstrument(MAGNIFIER);
        emit sendInstrumentChecked(MAGNIFIER);
    }
    else
    {
        setAllButtonsUnchecked(NULL);
        DataSingleton::Instance()->setInstrument(NONE);
        emit sendInstrumentChecked(NONE);
    }
}

void ToolBar::setSpray(const bool &state)
{
    if(state)
    {
        setAllButtonsUnchecked(mSprayButton);
        mSprayButton->setChecked(true);
        DataSingleton::Instance()->setInstrument(SPRAY);
        emit sendInstrumentChecked(SPRAY);
    }
    else
    {
        setAllButtonsUnchecked(NULL);
        DataSingleton::Instance()->setInstrument(NONE);
        emit sendInstrumentChecked(NONE);
    }
}

void ToolBar::setFill(const bool &state)
{
    if(state)
    {
        setAllButtonsUnchecked(mFillButton);
        mFillButton->setChecked(true);
        DataSingleton::Instance()->setInstrument(FILL);
        emit sendInstrumentChecked(FILL);
    }
    else
    {
        setAllButtonsUnchecked(NULL);
        DataSingleton::Instance()->setInstrument(NONE);
        emit sendInstrumentChecked(NONE);
    }
}

void ToolBar::setRect(const bool &state)
{
    if(state)
    {
        setAllButtonsUnchecked(mRectangleButton);
        mRectangleButton->setChecked(true);
        DataSingleton::Instance()->setInstrument(RECTANGLE);
        emit sendInstrumentChecked(RECTANGLE);
    }
    else
    {
        setAllButtonsUnchecked(NULL);
        DataSingleton::Instance()->setInstrument(NONE);
        emit sendInstrumentChecked(NONE);
    }
}

void ToolBar::setEllipse(const bool &state)
{
    if(state)
    {
        setAllButtonsUnchecked(mEllipseButton);
        mEllipseButton->setChecked(true);
        DataSingleton::Instance()->setInstrument(ELLIPSE);
        emit sendInstrumentChecked(ELLIPSE);
    }
    else
    {
        setAllButtonsUnchecked(NULL);
        DataSingleton::Instance()->setInstrument(NONE);
        emit sendInstrumentChecked(NONE);
    }
}

void ToolBar::restorePreviousInstrument()
{
    setInstrumentChecked(DataSingleton::Instance()->getPreviousInstrument());
    DataSingleton::Instance()->setInstrument(DataSingleton::Instance()->getPreviousInstrument());
    emit sendInstrumentChecked(DataSingleton::Instance()->getPreviousInstrument());
    mPrevInstrumentSetted = false;
    emit sendClearStatusBarColor();
}

void ToolBar::contextMenuEvent(QContextMenuEvent *)
{

}
