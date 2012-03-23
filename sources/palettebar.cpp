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

#include "palettebar.h"
#include "datasingleton.h"

PaletteBar::PaletteBar(ToolBar *toolbar) :
    QToolBar(tr("Colors"))
{
    mToolBar = toolbar;
    setMovable(false);
    initializeItems();
}

void PaletteBar::initializeItems()
{
    mColorButton = new PaletteButton(Qt::black);
    connect(mColorButton, SIGNAL(colorPicked()), this, SLOT(colorClicked()));
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::white);
    connect(mColorButton, SIGNAL(colorPicked()), this, SLOT(colorClicked()));
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::red);
    connect(mColorButton, SIGNAL(colorPicked()), this, SLOT(colorClicked()));
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::darkRed);
    connect(mColorButton, SIGNAL(colorPicked()), this, SLOT(colorClicked()));
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::green);
    connect(mColorButton, SIGNAL(colorPicked()), this, SLOT(colorClicked()));
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::darkGreen);
    connect(mColorButton, SIGNAL(colorPicked()), this, SLOT(colorClicked()));
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::blue);
    connect(mColorButton, SIGNAL(colorPicked()), this, SLOT(colorClicked()));
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::darkBlue);
    connect(mColorButton, SIGNAL(colorPicked()), this, SLOT(colorClicked()));
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::cyan);
    connect(mColorButton, SIGNAL(colorPicked()), this, SLOT(colorClicked()));
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::darkCyan);
    connect(mColorButton, SIGNAL(colorPicked()), this, SLOT(colorClicked()));
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::magenta);
    connect(mColorButton, SIGNAL(colorPicked()), this, SLOT(colorClicked()));
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::darkMagenta);
    connect(mColorButton, SIGNAL(colorPicked()), this, SLOT(colorClicked()));
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::yellow);
    connect(mColorButton, SIGNAL(colorPicked()), this, SLOT(colorClicked()));
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::darkYellow);
    connect(mColorButton, SIGNAL(colorPicked()), this, SLOT(colorClicked()));
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::gray);
    connect(mColorButton, SIGNAL(colorPicked()), this, SLOT(colorClicked()));
    addWidget(mColorButton);
}

void PaletteBar::colorClicked()
{
    mToolBar->setPrimaryColorView();
    mToolBar->setSecondaryColorView();
}

void PaletteBar::contextMenuEvent(QContextMenuEvent *) { }
