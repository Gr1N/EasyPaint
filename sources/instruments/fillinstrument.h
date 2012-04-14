#ifndef FILLINSTRUMENT_H
#define FILLINSTRUMENT_H

#include "abstractinstrument.h"

#include <QtCore/QObject>

/**
 * @brief Fill instrument class.
 *
 */
class FillInstrument : public AbstractInstrument
{
    Q_OBJECT
public:
    explicit FillInstrument(QObject *parent = 0);
    
    void mousePressEvent(QMouseEvent *event, ImageArea &imageArea);
    void mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea);
    void mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea);

protected:
    void paint(ImageArea &imageArea, bool isSecondaryColor = false, bool additionalFlag = false);

private:
    void fillRecurs(int x, int y, QRgb switchColor, QRgb oldColor, QImage &tempImage);
    
};

#endif // FILLINSTRUMENT_H
