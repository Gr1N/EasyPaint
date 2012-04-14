#ifndef ABSTRACTINSTRUMENT_H
#define ABSTRACTINSTRUMENT_H

#include <QtCore/QObject>
#include <QtGui/QMouseEvent>
#include <QtGui/QImage>

QT_BEGIN_NAMESPACE
class ImageArea;
QT_END_NAMESPACE

/**
 * @brief Abstract instrument class.
 *
 */
class AbstractInstrument : public QObject
{
    Q_OBJECT

public:
    explicit AbstractInstrument(QObject *parent = 0);
    virtual ~AbstractInstrument(){}

    virtual void mousePressEvent(QMouseEvent *event, ImageArea &imageArea)=0;
    virtual void mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea)=0;
    virtual void mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea)=0;
    
signals:
    
protected:
    QPoint mStartPoint, mEndPoint; /**< Point for events. */
    QImage mImageCopy; /**< Image for storing copy of current image on imageArea, needed for some instruments. */

    virtual void paint(ImageArea &imageArea, bool isSecondaryColor = false, bool additionalFlag = false)=0;
    
};

#endif // ABSTRACTINSTRUMENT_H
