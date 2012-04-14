#ifndef RECTANGLEINSTRUMENT_H
#define RECTANGLEINSTRUMENT_H

#include "abstractinstrument.h"

#include <QtCore/QObject>

/**
 * @brief Rectangle instrument class.
 *
 */
class RectangleInstrument : public AbstractInstrument
{
    Q_OBJECT
public:
    explicit RectangleInstrument(QObject *parent = 0);
    
    void mousePressEvent(QMouseEvent *event, ImageArea &imageArea);
    void mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea);
    void mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea);

protected:
    void paint(ImageArea &imageArea, bool isSecondaryColor = false, bool additionalFlag = false);
    
};

#endif // RECTANGLEINSTRUMENT_H
