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

QToolButton* PaletteBar::createColorButton(const QString &name, const QColor &color)
{
    QToolButton *toolButton = new QToolButton();
    toolButton->setMinimumSize(QSize(30, 30));
    toolButton->setMaximumSize(QSize(30, 30));
    QPixmap* pixmap = new QPixmap(20, 20);
    pixmap->fill(color);
    toolButton->setIcon(QPixmap(*pixmap));
    toolButton->setStatusTip(name);
    return toolButton;
}

void PaletteBar::initializeItems()
{
    mSignalMapper = new QSignalMapper();
    connect(mSignalMapper, SIGNAL(mapped(int)),
            this, SLOT(colorClicked(int)));

    mColorButton = createColorButton(tr("Black"), Qt::black);
    mSignalMapper->setMapping(mColorButton, 0);
    connect(mColorButton, SIGNAL(clicked()), mSignalMapper, SLOT(map()));
    addWidget(mColorButton);

    mColorButton = createColorButton(tr("White"), Qt::white);
    mSignalMapper->setMapping(mColorButton, 1);
    connect(mColorButton, SIGNAL(clicked()), mSignalMapper, SLOT(map()));
    addWidget(mColorButton);

    mColorButton = createColorButton(tr("Red"), Qt::red);
    mSignalMapper->setMapping(mColorButton, 2);
    connect(mColorButton, SIGNAL(clicked()), mSignalMapper, SLOT(map()));
    addWidget(mColorButton);

    mColorButton = createColorButton(tr("Dark red"), Qt::darkRed);
    mSignalMapper->setMapping(mColorButton, 3);
    connect(mColorButton, SIGNAL(clicked()), mSignalMapper, SLOT(map()));
    addWidget(mColorButton);

    mColorButton = createColorButton(tr("Green"), Qt::green);
    mSignalMapper->setMapping(mColorButton, 4);
    connect(mColorButton, SIGNAL(clicked()), mSignalMapper, SLOT(map()));
    addWidget(mColorButton);

    mColorButton = createColorButton(tr("Dark green"), Qt::darkGreen);
    mSignalMapper->setMapping(mColorButton, 5);
    connect(mColorButton, SIGNAL(clicked()), mSignalMapper, SLOT(map()));
    addWidget(mColorButton);

    mColorButton = createColorButton(tr("Blue"), Qt::blue);
    mSignalMapper->setMapping(mColorButton, 6);
    connect(mColorButton, SIGNAL(clicked()), mSignalMapper, SLOT(map()));
    addWidget(mColorButton);

    mColorButton = createColorButton(tr("Dark blue"), Qt::darkBlue);
    mSignalMapper->setMapping(mColorButton, 7);
    connect(mColorButton, SIGNAL(clicked()), mSignalMapper, SLOT(map()));
    addWidget(mColorButton);

    mColorButton = createColorButton(tr("Cyan"), Qt::cyan);
    mSignalMapper->setMapping(mColorButton, 8);
    connect(mColorButton, SIGNAL(clicked()), mSignalMapper, SLOT(map()));
    addWidget(mColorButton);

    mColorButton = createColorButton(tr("Dark cyan"), Qt::darkCyan);
    mSignalMapper->setMapping(mColorButton, 9);
    connect(mColorButton, SIGNAL(clicked()), mSignalMapper, SLOT(map()));
    addWidget(mColorButton);

    mColorButton = createColorButton(tr("Magenta"), Qt::magenta);
    mSignalMapper->setMapping(mColorButton, 10);
    connect(mColorButton, SIGNAL(clicked()), mSignalMapper, SLOT(map()));
    addWidget(mColorButton);

    mColorButton = createColorButton(tr("Dark magenta"), Qt::darkMagenta);
    mSignalMapper->setMapping(mColorButton, 11);
    connect(mColorButton, SIGNAL(clicked()), mSignalMapper, SLOT(map()));
    addWidget(mColorButton);

    mColorButton = createColorButton(tr("Yellow"), Qt::yellow);
    mSignalMapper->setMapping(mColorButton, 12);
    connect(mColorButton, SIGNAL(clicked()), mSignalMapper, SLOT(map()));
    addWidget(mColorButton);

    mColorButton = createColorButton(tr("Dark yellow"), Qt::darkYellow);
    mSignalMapper->setMapping(mColorButton, 13);
    connect(mColorButton, SIGNAL(clicked()), mSignalMapper, SLOT(map()));
    addWidget(mColorButton);

    mColorButton = createColorButton(tr("Gray"), Qt::gray);
    mSignalMapper->setMapping(mColorButton, 14);
    connect(mColorButton, SIGNAL(clicked()), mSignalMapper, SLOT(map()));
    addWidget(mColorButton);

}

void PaletteBar::colorClicked(int i)
{
    switch (i)
    {
    case 0:
        DataSingleton::Instance()->setFirstColor(Qt::black); break;
    case 1:
        DataSingleton::Instance()->setFirstColor(Qt::white); break;
    case 2:
        DataSingleton::Instance()->setFirstColor(Qt::red); break;
    case 3:
        DataSingleton::Instance()->setFirstColor(Qt::darkRed); break;
    case 4:
        DataSingleton::Instance()->setFirstColor(Qt::green); break;
    case 5:
        DataSingleton::Instance()->setFirstColor(Qt::darkGreen); break;
    case 6:
        DataSingleton::Instance()->setFirstColor(Qt::blue); break;
    case 7:
        DataSingleton::Instance()->setFirstColor(Qt::darkBlue); break;
    case 8:
        DataSingleton::Instance()->setFirstColor(Qt::cyan); break;
    case 9:
        DataSingleton::Instance()->setFirstColor(Qt::darkCyan); break;
    case 10:
        DataSingleton::Instance()->setFirstColor(Qt::magenta); break;
    case 11:
        DataSingleton::Instance()->setFirstColor(Qt::darkMagenta); break;
    case 12:
        DataSingleton::Instance()->setFirstColor(Qt::yellow); break;
    case 13:
        DataSingleton::Instance()->setFirstColor(Qt::darkYellow); break;
    case 14:
        DataSingleton::Instance()->setFirstColor(Qt::gray); break;
    }
    mToolBar->setFirstColorView();
}
