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

#include "grayeffect.h"
#include "../imagearea.h"

GrayEffect::GrayEffect(QObject *parent) :
    AbstractEffect(parent)
{
}

void GrayEffect::applyEffect(ImageArea &imageArea)
{
    imageArea.clearSelection();
    makeUndoCommand(imageArea);

    for(int i(0); i < imageArea.getImage()->width(); i++)
    {
        for(int y(0); y < imageArea.getImage()->height(); y++)
        {
            QRgb pixel(imageArea.getImage()->pixel(i, y));
            int rgb = (int)(0.299 * qRed(pixel) + 0.587 * qGreen(pixel) + 0.114 * qBlue(pixel));
            pixel = qRgb(rgb, rgb, rgb);
            imageArea.getImage()->setPixel(i, y, pixel);
        }
    }
    imageArea.setEdited(true);
    imageArea.update();
}
