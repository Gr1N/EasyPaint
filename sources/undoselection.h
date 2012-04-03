#ifndef UNDOSELECTION_H
#define UNDOSELECTION_H

#include <QtGui/QUndoCommand>
#include "imagearea.h"

/**
 * @brief Class which provides undo/redo actions for selection area
 *
 */
class UndoSelection : public QUndoCommand
{
public:
    UndoSelection(QPoint topLeft, QPoint bottomRight, QImage selectedImage,
                           ImageArea &area, QUndoCommand *parent = 0);

    virtual void undo();
    virtual void redo();

signals:

public slots:

private:
    QPoint mTopLeft, mBottomRight;
    QImage mSelectedImage;
    ImageArea& mImageArea;
};

#endif // UNDOSELECTION_H
