#ifndef COLORPICKERINSTRUMENT_H
#define COLORPICKERINSTRUMENT_H

#include "abstractinstrument.h"

#include <QtCore/QObject>

/**
 * @brief Colorpicker instrument class.
 *
 */
class ColorpickerInstrument : public AbstractInstrument
{
    Q_OBJECT

public:
    explicit ColorpickerInstrument(QObject *parent = 0);
    
    void mousePressEvent(QMouseEvent *event, ImageArea &imageArea);
    void mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea);
    void mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea);

protected:
    void paint(ImageArea &imageArea, bool isSecondaryColor = false, bool additionalFlag = false);
    
};

#endif // COLORPICKERINSTRUMENT_H
