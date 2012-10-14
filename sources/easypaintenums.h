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

#ifndef EASYPAINTENUMS_H
#define EASYPAINTENUMS_H

/**
 * @brief Enum with instruments names
 *
 */
typedef enum
{
    NONE_INSTRUMENT = 0,
    CURSOR,
    ERASER,
    PEN,
    LINE,
    COLORPICKER,
    MAGNIFIER,
    SPRAY,
    FILL,
    RECTANGLE,
    ELLIPSE,
    CURVELINE,
    TEXT,

    // Don't use it. (Used to know count of current instrument)
    INSTRUMENTS_COUNT
} InstrumentsEnum;

/**
 * @brief Enum with effects names
 *
 */
typedef enum
{
    NONE_EFFECT = 0,
    NEGATIVE,
    GRAY,
    BINARIZATION,
    GAUSSIANBLUR,
    GAMMA,
    SHARPEN,
    CUSTOM,

    // Don't use it. (Used to know count of current instrument)
    EFFECTS_COUNT
} EffectsEnum;

#endif // EASYPAINTENUMS_H
