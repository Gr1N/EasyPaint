#include "undoselection.h"
#include "paintinstruments.h"

UndoSelection::UndoSelection(QPoint topLeft, QPoint bottomRight, QImage selectedImage,
                             ImageArea &area, QUndoCommand *parent) :
    QUndoCommand(parent), mTopLeft(topLeft), mBottomRight(bottomRight),
    mSelectedImage(selectedImage), mImageArea(area)
{
}

void UndoSelection::undo()
{
    mImageArea.clearImageChanges();
    mImageArea.setIsSelectonExists(true);
    mImageArea.setIsImageSelected(true);
    mImageArea.getPaintInstruments()->setStartPoint(mTopLeft);
    mImageArea.getPaintInstruments()->setEndPoint(mBottomRight);
    mImageArea.setSelectedImage(mSelectedImage);
    mImageArea.getPaintInstruments()->selection(true, true);
}

void UndoSelection::redo()
{
    mImageArea.clearImageChanges();
    mImageArea.setIsSelectonExists(true);
    mImageArea.setIsImageSelected(true);
    mImageArea.getPaintInstruments()->setStartPoint(mTopLeft);
    mImageArea.getPaintInstruments()->setEndPoint(mBottomRight);
    mImageArea.setSelectedImage(mSelectedImage);
    mImageArea.getPaintInstruments()->selection(true, true);
}
