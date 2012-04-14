#ifndef ABSTRACTINSTRUMENT_H
#define ABSTRACTINSTRUMENT_H

#include <QtCore/QObject>
#include <QtGui/QMouseEvent>

QT_BEGIN_NAMESPACE
class ImageArea;
QT_END_NAMESPACE

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
    QPoint mStartPoint, mEndPoint;

    virtual void paint(ImageArea &imageArea, bool isSecondaryColor = false, bool additionalFlag = false)=0;
    
};

#endif // ABSTRACTINSTRUMENT_H
