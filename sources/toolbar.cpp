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
#include "datasingleton.h"

#include <QtGui/QToolButton>
#include <QtGui/QGridLayout>
#include <QtGui/QSpinBox>

ToolBar::ToolBar(QWidget *parent) :
    QToolBar(tr("Instruments"), parent)
{
    setMovable(false);
    initializeItems();
}

QToolButton* ToolBar::createToolButton(const char *name, const QString &iconPath)
{
    QToolButton *toolButton = new QToolButton();
    toolButton->setMinimumSize(QSize(30, 30));
    toolButton->setMaximumSize(QSize(30, 30));
    toolButton->setIcon(QPixmap(iconPath));
    toolButton->setStatusTip(tr(name));
    toolButton->setCheckable(true);
    return toolButton;
}

void ToolBar::initializeItems()
{
    mCursorButton = createToolButton("Cursor", ":/media/instruments-icons/cursor.png");
    connect(mCursorButton, SIGNAL(toggled(bool)), this, SLOT(setCursor(bool)));

    mLasticButton = createToolButton("Lastic", ":/media/instruments-icons/lastic.png");
    connect(mLasticButton, SIGNAL(toggled(bool)), this, SLOT(setLastic(bool)));

    mPenButton = createToolButton("Pen", ":/media/instruments-icons/pencil.png");
    connect(mPenButton, SIGNAL(toggled(bool)), this, SLOT(setPen(bool)));

    mLineButton = createToolButton("Line", ":/media/instruments-icons/line.png");
    connect(mLineButton, SIGNAL(toggled(bool)), this, SLOT(setLine(bool)));

    mPipetteButton = createToolButton("Pipette", ":/media/instruments-icons/pipette.png");
    connect(mPipetteButton, SIGNAL(toggled(bool)), this, SLOT(setPipette(bool)));

    mLoupeButton = createToolButton("Loupe", ":/media/instruments-icons/loupe.png");
    connect(mLoupeButton, SIGNAL(toggled(bool)), this, SLOT(setLoupe(bool)));

    mSprayButton = createToolButton("Spray", ":/media/instruments-icons/spray.png");
    connect(mSprayButton, SIGNAL(toggled(bool)), this, SLOT(setSpray(bool)));

    mFillButton = createToolButton("Fill", ":/media/instruments-icons/fill.png");
    connect(mFillButton, SIGNAL(toggled(bool)), this, SLOT(setFill(bool)));

    mRectButton = createToolButton("Rect", ":/media/instruments-icons/rectangle.png");
    connect(mRectButton, SIGNAL(toggled(bool)), this, SLOT(setRect(bool)));

    mEllipseButton = createToolButton("Ellipse", ":/media/instruments-icons/ellipse.png");
    connect(mEllipseButton, SIGNAL(toggled(bool)), this, SLOT(setEllipse(bool)));


    QGridLayout *bLayout = new QGridLayout();
    bLayout->setMargin(3);
    bLayout->addWidget(mCursorButton, 0, 0);
    bLayout->addWidget(mLasticButton, 0, 1);
    bLayout->addWidget(mPipetteButton, 1, 0);
    bLayout->addWidget(mLoupeButton, 1, 1);
    bLayout->addWidget(mPenButton, 2, 0);
    bLayout->addWidget(mLineButton, 2, 1);
    bLayout->addWidget(mSprayButton, 3, 0);
    bLayout->addWidget(mFillButton, 3, 1);
    bLayout->addWidget(mRectButton, 4, 0);
    bLayout->addWidget(mEllipseButton, 4, 1);

    QWidget *bWidget = new QWidget();
    bWidget->setLayout(bLayout);

    mFColorChooser = new ColorChooser(0, 0, 0, this);
    mFColorChooser->setStatusTip(tr("First color"));
    connect(mFColorChooser, SIGNAL(sendColor(QColor)), this, SLOT(firstColorChanged(QColor)));

    mSColorChooser = new ColorChooser(255, 255, 255, this);
    mSColorChooser->setStatusTip(tr("Second color"));
    connect(mSColorChooser, SIGNAL(sendColor(QColor)), this, SLOT(secondColorChanged(QColor)));

    QSpinBox *penSizeSpin = new QSpinBox();
    penSizeSpin->setRange(1, 20);
    penSizeSpin->setValue(1);
    penSizeSpin->setStatusTip(tr("Pen size"));
    connect(penSizeSpin, SIGNAL(valueChanged(int)), this, SLOT(penValueChanged(int)));

    QGridLayout *tLayout = new QGridLayout();
    tLayout->setMargin(3);
    tLayout->addWidget(mFColorChooser, 0, 0);
    tLayout->addWidget(mSColorChooser, 0, 1);
    tLayout->addWidget(penSizeSpin, 1, 0, 1, 2);

    QWidget *tWidget = new QWidget();
    tWidget->setLayout(tLayout);

    addWidget(bWidget);
    addSeparator();
    addWidget(tWidget);
    addSeparator();

    // add palette
}

void ToolBar::penValueChanged(const int &value)
{
    DataSingleton::Instance()->setPenSize(value);
}

void ToolBar::firstColorChanged(const QColor &color)
{
    DataSingleton::Instance()->setFirstColor(color);
}

void ToolBar::secondColorChanged(const QColor &color)
{
    DataSingleton::Instance()->setSecondColor(color);
}

void ToolBar::setFirstColorView()
{
    mFColorChooser->setColor(DataSingleton::Instance()->getFirstColor());
}

void ToolBar::setSecondColorView()
{
    mSColorChooser->setColor(DataSingleton::Instance()->getSecondColor());
}

void ToolBar::setAllButtonsUnchecked(QToolButton *button)
{
    if(button != mCursorButton)
        mCursorButton->setChecked(false);
    if(button != mLasticButton)
        mLasticButton->setChecked(false);
    if(button != mPenButton)
        mPenButton->setChecked(false);
    if(button != mLineButton)
        mLineButton->setChecked(false);
    if(button != mPipetteButton)
        mPipetteButton->setChecked(false);
    if(button != mLoupeButton)
        mLoupeButton->setChecked(false);
    if(button != mSprayButton)
        mSprayButton->setChecked(false);
    if(button != mFillButton)
        mFillButton->setChecked(false);
    if(button != mRectButton)
        mRectButton->setChecked(false);
    if(button != mEllipseButton)
        mEllipseButton->setChecked(false);
}

void ToolBar::setInstrumentChecked(InstrumentsEnum instrument)
{
    setAllButtonsUnchecked(new QToolButton());
    switch(instrument)
    {
    case NONE:
        mCursorButton->setChecked(true);
        break;
    case LASTIC:
        mLasticButton->setChecked(true);
        break;
    case PIPETTE:
        mPipetteButton->setChecked(true);
        break;
    case LOUPE:
        mLoupeButton->setChecked(true);
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
    case RECT:
        mRectButton->setChecked(true);
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
        DataSingleton::Instance()->setInstrument(NONE);
        emit sendInstrumentChecked(NONE);
    }
    else
    {
        setAllButtonsUnchecked(new QToolButton());
        DataSingleton::Instance()->setInstrument(NONE);
        emit sendInstrumentChecked(NONE);
    }
}

void ToolBar::setLastic(const bool &state)
{
    if(state)
    {
        setAllButtonsUnchecked(mLasticButton);
        mLasticButton->setChecked(true);
        DataSingleton::Instance()->setInstrument(LASTIC);
        emit sendInstrumentChecked(LASTIC);
    }
    else
    {
        setAllButtonsUnchecked(new QToolButton());
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
        setAllButtonsUnchecked(new QToolButton());
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
        setAllButtonsUnchecked(new QToolButton());
        DataSingleton::Instance()->setInstrument(NONE);
        emit sendInstrumentChecked(NONE);
    }
}

void ToolBar::setPipette(const bool &state)
{
    if(state)
    {
        setAllButtonsUnchecked(mPipetteButton);
        mPipetteButton->setChecked(true);
        DataSingleton::Instance()->setInstrument(PIPETTE);
        emit sendInstrumentChecked(PIPETTE);
    }
    else
    {
        setAllButtonsUnchecked(new QToolButton());
        DataSingleton::Instance()->setInstrument(NONE);
        emit sendInstrumentChecked(NONE);
    }
}

void ToolBar::setLoupe(const bool &state)
{
    if(state)
    {
        setAllButtonsUnchecked(mLoupeButton);
        mLoupeButton->setChecked(true);
        DataSingleton::Instance()->setInstrument(LOUPE);
        emit sendInstrumentChecked(LOUPE);
    }
    else
    {
        setAllButtonsUnchecked(new QToolButton());
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
        setAllButtonsUnchecked(new QToolButton());
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
        setAllButtonsUnchecked(new QToolButton());
        DataSingleton::Instance()->setInstrument(NONE);
        emit sendInstrumentChecked(NONE);
    }
}

void ToolBar::setRect(const bool &state)
{
    if(state)
    {
        setAllButtonsUnchecked(mRectButton);
        mRectButton->setChecked(true);
        DataSingleton::Instance()->setInstrument(RECT);
        emit sendInstrumentChecked(RECT);
    }
    else
    {
        setAllButtonsUnchecked(new QToolButton());
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
        setAllButtonsUnchecked(new QToolButton());
        DataSingleton::Instance()->setInstrument(NONE);
        emit sendInstrumentChecked(NONE);
    }
}
