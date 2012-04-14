#ifndef MAGNIFIERINSTRUMENT_H
#define MAGNIFIERINSTRUMENT_H

#include "abstractinstrument.h"

#include <QtCore/QObject>

/**
 * @brief Magnifier instrument class.
 *
 */
class MagnifierInstrument : public AbstractInstrument
{
    Q_OBJECT
public:
    explicit MagnifierInstrument(QObject *parent = 0);
    
    void mousePressEvent(QMouseEvent *event, ImageArea &imageArea);
    void mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea);
    void mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea);

protected:
    void paint(ImageArea &imageArea, bool isSecondaryColor = false, bool additionalFlag = false);
    
};

#endif // MAGNIFIERINSTRUMENT_H
