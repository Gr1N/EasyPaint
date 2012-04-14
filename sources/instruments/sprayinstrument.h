#ifndef SPRAYINSTRUMENT_H
#define SPRAYINSTRUMENT_H

#include "abstractinstrument.h"

#include <QtCore/QObject>

/**
 * @brief Spray instrument class.
 *
 */
class SprayInstrument : public AbstractInstrument
{
    Q_OBJECT
public:
    explicit SprayInstrument(QObject *parent = 0);
    
    void mousePressEvent(QMouseEvent *event, ImageArea &imageArea);
    void mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea);
    void mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea);

protected:
    void paint(ImageArea &imageArea, bool isSecondaryColor = false, bool additionalFlag = false);
    
};

#endif // SPRAYINSTRUMENT_H
