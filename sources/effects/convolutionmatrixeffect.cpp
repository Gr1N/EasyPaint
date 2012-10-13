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

#include <cmath>

#include "convolutionmatrixeffect.h"
#include "../imagearea.h"

ConvolutionMatrixEffect::ConvolutionMatrixEffect(QObject *parent) :
    AbstractEffect(parent)
{
}

void ConvolutionMatrixEffect::applyEffect(ImageArea &imageArea)
{
    makeUndoCommand(imageArea);

    QImage copy(*imageArea.getImage());


    for(int i = 2; i < imageArea.getImage()->height() - 2; ++i)
    {
        for(int j = 2; j < imageArea.getImage()->width() - 2; ++j)
        {
            copy.setPixel(j, i, convolutePixel(*imageArea.getImage(), j, i, getConvolutionMatrix()));
        }
    }

    imageArea.setImage(copy);
    imageArea.setEdited(true);
    imageArea.update();
}


// TODO: remove, use EffectSettingsDialog
QRgb ConvolutionMatrixEffect::convolutePixel(const QImage &image, int x, int y, const QList<double> &kernelMatrix)
{
    int kernelSize = sqrt(kernelMatrix.size());

    double total = 0;
    double red = 0;
    double green = 0;
    double blue = 0;
    // TODO: some optimization can be made
    for(int r = -kernelSize / 2; r <= kernelSize / 2; ++r)
    {
        for(int c = -kernelSize / 2; c <= kernelSize / 2; ++c)
        {
            int kernelValue = kernelMatrix[(kernelSize / 2 + r) * kernelSize + (kernelSize / 2 + c)];
            total += kernelValue;
            red += qRed(image.pixel(x + c, y + r)) * kernelValue;
            green += qGreen(image.pixel(x + c, y + r)) * kernelValue;
            blue += qBlue(image.pixel(x + c, y + r)) * kernelValue;
        }
    }

    if(total == 0)
        return qRgb(qBound(0, qRound(red), 255), qBound(0, qRound(green), 255), qBound(0, qRound(blue), 255));

    return qRgb(qBound(0, qRound(red / total), 255), qBound(0, qRound(green / total), 255), qBound(0, qRound(blue / total), 255));
}
