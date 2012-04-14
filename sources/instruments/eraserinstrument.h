#ifndef ERASERINSTRUMENT_H
#define ERASERINSTRUMENT_H

#include "abstractinstrument.h"

#include <QtCore/QObject>

/**
 * @brief Eraser instrument class.
 *
 */
class EraserInstrument : public AbstractInstrument
{
    Q_OBJECT

public:
    explicit EraserInstrument(QObject *parent = 0);
    
    void mousePressEvent(QMouseEvent *event, ImageArea &imageArea);
    void mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea);
    void mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea);

protected:
    void paint(ImageArea &imageArea, bool isSecondaryColor = false, bool additionalFlag = false);
    
};

#endif // ERASERINSTRUMENT_H
