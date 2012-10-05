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

#ifndef TEXTINSTRUMENT_H
#define TEXTINSTRUMENT_H

#include "abstractselection.h"

#include <QtCore/QObject>

/**
 * @brief Text instrument class.
 *
 */
class TextInstrument : public AbstractSelection
{
    Q_OBJECT
public:
    explicit TextInstrument(QObject *parent = 0);

private:
    void startSelection(ImageArea &);
    void startResizing(ImageArea &);
    void startMoving(ImageArea &);
    void select(ImageArea &);
    void resize(ImageArea &imageArea);
    void move(ImageArea &imageArea);
    void completeSelection(ImageArea &imageArea);
    void completeResizing(ImageArea &);
    void completeMoving(ImageArea &);
    void clear();
    void paint(ImageArea &imageArea, bool = false, bool = false);

    QString mText;
    bool mIsEdited;

signals:
    void sendCloseTextDialog();

private slots:
    void updateText(ImageArea *, QString);
    /**
     * @brief Clears text and remove selection.
     *
     * @param imageArea ImageArea for applying changes.
     */
    void cancel(ImageArea *);

};

#endif // TEXTINSTRUMENT_H
