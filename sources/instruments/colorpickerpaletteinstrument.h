#ifndef COLORPICKERPALETTEINSTRUMENT_H
#define COLORPICKERPALETTEINSTRUMENT_H

#include "abstractinstrument.h"

#include <QtCore/QObject>

/**
 * @brief ColorpickerPalette instrument class.
 *
 */

class ColorpickerPaletteInstrument : public AbstractInstrument
{
    Q_OBJECT

public:
    explicit ColorpickerPaletteInstrument(QObject *parent = 0);

    void mousePressEvent(QMouseEvent *event, ImageArea &imageArea);
    void mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea);
    void mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea);

protected:
    void paint(ImageArea &imageArea, bool isSecondaryColor = false, bool additionalFlag = false);

};

#endif // COLORPICKERPALETTEINSTRUMENT_H
