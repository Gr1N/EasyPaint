#include "fillinstrument.h"
#include "../imagearea.h"
#include "../datasingleton.h"

#include <QtGui/QPen>
#include <QtGui/QPainter>

FillInstrument::FillInstrument(QObject *parent) :
    AbstractInstrument(parent)
{
}

void FillInstrument::mousePressEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if(event->button() == Qt::LeftButton || event->button() == Qt::RightButton)
    {
        mStartPoint = mEndPoint = event->pos();
        imageArea.setIsPaint(true);
        imageArea.pushUndoCommand();
    }
}

void FillInstrument::mouseMoveEvent(QMouseEvent *, ImageArea &)
{

}

void FillInstrument::mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if(imageArea.isPaint())
    {
        if(event->button() == Qt::LeftButton)
        {
            paint(imageArea, false);
        }
        else if(event->button() == Qt::RightButton)
        {
            paint(imageArea, true);
        }
        imageArea.setIsPaint(false);
    }
}

void FillInstrument::paint(ImageArea &imageArea, bool isSecondaryColor, bool)
{
    QColor switchColor;
    if(!isSecondaryColor)
        switchColor = DataSingleton::Instance()->getPrimaryColor();
    else
        switchColor = DataSingleton::Instance()->getSecondaryColor();

    QRgb pixel(imageArea.getImage()->pixel(mStartPoint));
    QColor oldColor(pixel);

    if(switchColor != oldColor)
    {
        fillRecurs(mStartPoint.x(), mStartPoint.y(),
                   switchColor.rgb(), oldColor.rgb(),
                   *imageArea.getImage());
    }
    imageArea.setEdited(true);
    imageArea.update();
}

void FillInstrument::fillRecurs(int x, int y, QRgb switchColor, QRgb oldColor, QImage &tempImage)
{
    int temp_x(x), left_x(0);
    while(true)
    {
        if(tempImage.pixel(temp_x, y) != oldColor)
            break;
        tempImage.setPixel(temp_x, y, switchColor);
        if(temp_x > 0)
        {
            --temp_x;
            left_x = temp_x;
        }
        else
            break;
    }

    int right_x(0);
    temp_x = x + 1;
    while(true)
    {
        if(tempImage.pixel(temp_x, y) != oldColor)
            break;
        tempImage.setPixel(temp_x, y, switchColor);
        if(temp_x < tempImage.width() - 1)
        {
            temp_x++;
            right_x = temp_x;
        }
        else
            break;
    }

    for(int x_(left_x+1); x_ < right_x; ++x_)
    {
        if(y < 1 || y >= tempImage.height() - 1)
            break;
        if(right_x > tempImage.width())
            break;
        QRgb currentColor = tempImage.pixel(x_, y-1);
        if(currentColor == oldColor && currentColor != switchColor)
            fillRecurs(x_, y-1, switchColor, oldColor, tempImage);
        currentColor = tempImage.pixel(x_, y+1);
        if(currentColor == oldColor && currentColor != switchColor)
            fillRecurs(x_, y+1, switchColor, oldColor, tempImage);
    }
}
