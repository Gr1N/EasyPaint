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

#include "shortcutedit.h"
#include <QKeyEvent>
#include <QKeySequence>
#include <QToolButton>
#include <QStyle>

ShortcutEdit::ShortcutEdit(QWidget *parent) :
    QLineEdit(parent)
{
    setReadOnly(true);

    QPixmap icon(":/media/actions-icons/clear-gray.png");
    //Create and set clear text button
    mClearButton = new QToolButton(this);
    mClearButton->setIcon(QIcon(icon));
    mClearButton->setIconSize(icon.size());
    mClearButton->setCursor(Qt::ArrowCursor);
    mClearButton->setStyleSheet("QToolButton { border: none; padding: 0px; }");
    mClearButton->setToolTip(tr("Clear"));
    mClearButton->hide();

    int fr = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    setStyleSheet(QString("QLineEdit { padding-right: %1px; }").arg(mClearButton->sizeHint().width()
                                                                    + fr + 1));
    QSize msz = minimumSizeHint();
    setMinimumSize(qMax(msz.width(), mClearButton->sizeHint().height() + fr * 2 + 2),
                   qMax(msz.height(),mClearButton->sizeHint().height() + fr * 2 + 2));

    connect(mClearButton, SIGNAL(clicked()), this, SLOT(clear()));
    connect(this, SIGNAL(textChanged(QString)), SLOT(updateClearButton(QString)));
}

void ShortcutEdit::keyPressEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat() || isModifier(event->key()))
        return;
\
    QKeySequence keySeq(event->modifiers() + event->key());
    setText(keySeq.toString());
}

void ShortcutEdit::resizeEvent(QResizeEvent *)
{
    int fr = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    mClearButton->move(rect().right() - fr - mClearButton->sizeHint().width(),
                       (rect().bottom() + 1 -mClearButton->sizeHint().height()) / 2);
}

bool ShortcutEdit::isModifier(int key)
{
    if(key == Qt::Key_Control || key == Qt::Key_Meta || key == Qt::Key_Alt
            || key == Qt::Key_AltGr || key == Qt::Key_Shift)
        return true;
    return false;
}

void ShortcutEdit::updateClearButton(const QString &text)
{
    mClearButton->setVisible(!text.isEmpty());
}
