/*
 * This source file is part of EasyPaint.
 *
 * Copyright (c) 2020 EasyPaint(Maifee Ul Asad) <https://github.com/maifeeulasad/EasyPaint>
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

#include "colorpickerpaletteinstrument.h"
#include "../imagearea.h"
#include "../datasingleton.h"
#include <QColorDialog>

ColorpickerPaletteInstrument::ColorpickerPaletteInstrument(QObject *parent) :
    AbstractInstrument(parent)
{
}

void ColorpickerPaletteInstrument::mousePressEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if(event->button() == Qt::LeftButton || event->button() == Qt::RightButton)
    {
        imageArea.setIsPaint(true);
    }
}

void ColorpickerPaletteInstrument::mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea)
{

}

void ColorpickerPaletteInstrument::mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if(imageArea.isPaint())
    {
        DataSingleton *dataSingleton = DataSingleton::Instance();
        QColor color = QColorDialog::getColor(dataSingleton->getPrimaryColor(), &imageArea, "Pick a color",  QColorDialog::DontUseNativeDialog);
        dataSingleton->setPrimaryColor(color);
        imageArea.emitPrimaryColorView();
        imageArea.setIsPaint(false);
        imageArea.emitRestorePreviousInstrument();
    }
}

void ColorpickerPaletteInstrument::paint(ImageArea &imageArea, bool isSecondaryColor, bool)
{

}
