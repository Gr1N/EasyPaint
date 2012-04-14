#ifndef ELLIPSEINSTRUMENT_H
#define ELLIPSEINSTRUMENT_H

#include "abstractinstrument.h"

#include <QtCore/QObject>

/**
 * @brief Ellipse instrument class.
 *
 */
class EllipseInstrument : public AbstractInstrument
{
    Q_OBJECT

public:
    explicit EllipseInstrument(QObject *parent = 0);
    
    void mousePressEvent(QMouseEvent *event, ImageArea &imageArea);
    void mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea);
    void mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea);

protected:
    void paint(ImageArea &imageArea, bool isSecondaryColor = false, bool additionalFlag = false);
    
};

#endif // ELLIPSEINSTRUMENT_H
