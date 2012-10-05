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

#include "gammaeffect.h"
#include "../imagearea.h"

#include <math.h>

GammaEffect::GammaEffect(QObject *parent) :
    AbstractEffect(parent)
{
}

void GammaEffect::applyEffect(ImageArea &imageArea)
{
    makeUndoCommand(imageArea);

    // TODO: add dialog for setting parameters
    makeGamma(imageArea, 2);

    imageArea.setEdited(true);
    imageArea.update();
}

void GammaEffect::makeGamma(ImageArea &imageArea, float modificator)
{
    for(int x(0); x < imageArea.getImage()->width(); x++)
    {
        for(int y(0); y < imageArea.getImage()->height(); y++)
        {
            QRgb pixel = imageArea.getImage()->pixel(x, y);
            float r = qRed(pixel);
            r = 255 * pow(r / 255, modificator);
            float g = qGreen(pixel);
            g = 255 * pow(g / 255, modificator);
            float b = qBlue(pixel);
            b = 255 * pow(b / 255, modificator);
            pixel = qRgb(r, g, b);
            imageArea.getImage()->setPixel(x, y, pixel);
        }
    }
}
