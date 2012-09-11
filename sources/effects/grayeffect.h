#ifndef GRAYEFFECT_H
#define GRAYEFFECT_H

#include "abstracteffect.h"

#include <QtCore/QObject>

/**
 * @brief Gray effect class.
 *
 */
class GrayEffect : public AbstractEffect
{
    Q_OBJECT
public:
    explicit GrayEffect(QObject *parent = 0);
    
    void applyEffect(ImageArea &imageArea);

};

#endif // GRAYEFFECT_H
