/*
 * This source file is part of EasyPaint.
 *
 * Copyright (c) 2012 EasyPaint <https://github.com/Gr1N/EasyPaint>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "mainwindow.h"
#include "widgets/toolbar.h"
#include "imagearea.h"
#include "datasingleton.h"
#include "dialogs/settingsdialog.h"
#include "widgets/palettebar.h"

#include <QApplication>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QScrollArea>
#include <QLabel>
#include <QtEvents>
#include <QPainter>
#include <QInputDialog>
#include <QUndoGroup>
#include <QtCore/QTimer>
#include <QtCore/QMap>

MainWindow::MainWindow(QStringList filePaths, QWidget *parent)
    : QMainWindow(parent), mPrevInstrumentSetted(false)
{
    QSize winSize = DataSingleton::Instance()->getWindowSize();
    if (DataSingleton::Instance()->getIsRestoreWindowSize() &&  winSize.isValid()) {
        resize(winSize);
    }

    setWindowIcon(QIcon(":/media/logo/easypaint_64.png"));

    mUndoStackGroup = new QUndoGroup(this);

    initializeMainMenu();
    initializeToolBar();
    initializePaletteBar();
    initializeStatusBar();
    initializeTabWidget();

    if(filePaths.isEmpty())
    {
        initializeNewTab();
    }
    else
    {
        for(int i(0); i < filePaths.size(); i++)
        {
            initializeNewTab(true, filePaths.at(i));
        }
    }
    qRegisterMetaType<InstrumentsEnum>("InstrumentsEnum");
}

MainWindow::~MainWindow()
{
    
}

void MainWindow::initializeTabWidget()
{
    mTabWidget = new QTabWidget();
    mTabWidget->setUsesScrollButtons(true);
    mTabWidget->setTabsClosable(true);
    mTabWidget->setMovable(true);
    connect(mTabWidget, SIGNAL(currentChanged(int)), this, SLOT(activateTab(int)));
    connect(mTabWidget, SIGNAL(currentChanged(int)), this, SLOT(enableActions(int)));
    connect(mTabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
    setCentralWidget(mTabWidget);
}

void MainWindow::initializeNewTab(const bool &isOpen, const QString &filePath)
{
    ImageArea *imageArea;
    QString fileName(tr("Untitled Image"));
    if(isOpen && filePath.isEmpty())
    {
        imageArea = new ImageArea(isOpen);
        fileName = imageArea->getFileName();
    }
    else if(isOpen && !filePath.isEmpty())
    {
        imageArea = new ImageArea(isOpen, filePath);
        fileName = imageArea->getFileName();
    }
    else
    {
        imageArea = new ImageArea();
    }

    if (!fileName.isEmpty())
    {
        QScrollArea *scrollArea = new QScrollArea();
        scrollArea->setAttribute(Qt::WA_DeleteOnClose);
        scrollArea->setBackgroundRole(QPalette::Dark);
        scrollArea->setWidget(imageArea);

        mTabWidget->addTab(scrollArea, fileName);
        mTabWidget->setCurrentIndex(mTabWidget->count()-1);

        mUndoStackGroup->addStack(imageArea->getUndoStack());
        connect(imageArea, SIGNAL(sendPrimaryColorView()), mToolbar, SLOT(setPrimaryColorView()));
        connect(imageArea, SIGNAL(sendSecondaryColorView()), mToolbar, SLOT(setSecondaryColorView()));
        connect(imageArea, SIGNAL(sendRestorePreviousInstrument()), this, SLOT(restorePreviousInstrument()));
        connect(imageArea, SIGNAL(sendSetInstrument(InstrumentsEnum)), this, SLOT(setInstrument(InstrumentsEnum)));
        connect(imageArea, SIGNAL(sendNewImageSize(QSize)), this, SLOT(setNewSizeToSizeLabel(QSize)));
        connect(imageArea, SIGNAL(sendCursorPos(QPoint)), this, SLOT(setNewPosToPosLabel(QPoint)));
        connect(imageArea, SIGNAL(sendColor(QColor)), this, SLOT(setCurrentPipetteColor(QColor)));
        connect(imageArea, SIGNAL(sendEnableCopyCutActions(bool)), this, SLOT(enableCopyCutActions(bool)));
        connect(imageArea, SIGNAL(sendEnableSelectionInstrument(bool)), this, SLOT(instumentsAct(bool)));

        setWindowTitle(QString("%1 - EasyPaint").arg(fileName));
    }
    else
    {
        delete imageArea;
    }
}

void MainWindow::initializeMainMenu()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    mNewAction = new QAction(tr("&New"), this);
    mNewAction->setIcon(QIcon::fromTheme("document-new", QIcon(":/media/actions-icons/document-new.png")));
    mNewAction->setIconVisibleInMenu(true);
    connect(mNewAction, SIGNAL(triggered()), this, SLOT(newAct()));
    fileMenu->addAction(mNewAction);

    mOpenAction = new QAction(tr("&Open"), this);
    mOpenAction->setIcon(QIcon::fromTheme("document-open", QIcon(":/media/actions-icons/document-open.png")));
    mOpenAction->setIconVisibleInMenu(true);
    connect(mOpenAction, SIGNAL(triggered()), this, SLOT(openAct()));
    fileMenu->addAction(mOpenAction);

    mSaveAction = new QAction(tr("&Save"), this);
    mSaveAction->setIcon(QIcon::fromTheme("document-save", QIcon(":/media/actions-icons/document-save.png")));
    mSaveAction->setIconVisibleInMenu(true);
    connect(mSaveAction, SIGNAL(triggered()), this, SLOT(saveAct()));
    fileMenu->addAction(mSaveAction);

    mSaveAsAction = new QAction(tr("Save as..."), this);
    mSaveAsAction->setIcon(QIcon::fromTheme("document-save-as", QIcon(":/media/actions-icons/document-save-as.png")));
    mSaveAsAction->setIconVisibleInMenu(true);
    connect(mSaveAsAction, SIGNAL(triggered()), this, SLOT(saveAsAct()));
    fileMenu->addAction(mSaveAsAction);

    mCloseAction = new QAction(tr("&Close"), this);
    mCloseAction->setIcon(QIcon::fromTheme("window-close", QIcon(":/media/actions-icons/window-close.png")));
    mCloseAction->setIconVisibleInMenu(true);
    connect(mCloseAction, SIGNAL(triggered()), this, SLOT(closeTabAct()));
    fileMenu->addAction(mCloseAction);

    fileMenu->addSeparator();

    mPrintAction = new QAction(tr("&Print"), this);
    mPrintAction->setIcon(QIcon::fromTheme("document-print", QIcon(":/media/actions-icons/document-print.png")));
    mPrintAction->setIconVisibleInMenu(true);
    connect(mPrintAction, SIGNAL(triggered()), this, SLOT(printAct()));
    fileMenu->addAction(mPrintAction);

    fileMenu->addSeparator();

    mExitAction = new QAction(tr("&Exit"), this);
    mExitAction->setIcon(QIcon::fromTheme("application-exit", QIcon(":/media/actions-icons/application-exit.png")));
    mExitAction->setIconVisibleInMenu(true);
    connect(mExitAction, SIGNAL(triggered()), SLOT(close()));
    fileMenu->addAction(mExitAction);

    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));

    mUndoAction = mUndoStackGroup->createUndoAction(this, tr("&Undo"));
    mUndoAction->setIcon(QIcon::fromTheme("edit-undo", QIcon(":/media/actions-icons/edit-undo.png")));
    mUndoAction->setIconVisibleInMenu(true);
    mUndoAction->setEnabled(false);
    editMenu->addAction(mUndoAction);

    mRedoAction = mUndoStackGroup->createRedoAction(this, tr("&Redo"));
    mRedoAction->setIcon(QIcon::fromTheme("edit-redo", QIcon(":/media/actions-icons/edit-redo.png")));
    mRedoAction->setIconVisibleInMenu(true);
    mRedoAction->setEnabled(false);
    editMenu->addAction(mRedoAction);

    editMenu->addSeparator();

    mCopyAction = new QAction(tr("&Copy"), this);
    mCopyAction->setIcon(QIcon::fromTheme("edit-copy", QIcon(":/media/actions-icons/edit-copy.png")));
    mCopyAction->setIconVisibleInMenu(true);
    mCopyAction->setEnabled(false);
    connect(mCopyAction, SIGNAL(triggered()), this, SLOT(copyAct()));
    editMenu->addAction(mCopyAction);

    mPasteAction = new QAction(tr("&Paste"), this);
    mPasteAction->setIcon(QIcon::fromTheme("edit-paste", QIcon(":/media/actions-icons/edit-paste.png")));
    mPasteAction->setIconVisibleInMenu(true);
    connect(mPasteAction, SIGNAL(triggered()), this, SLOT(pasteAct()));
    editMenu->addAction(mPasteAction);

    mCutAction = new QAction(tr("C&ut"), this);
    mCutAction->setIcon(QIcon::fromTheme("edit-cut", QIcon(":/media/actions-icons/edit-cut.png")));
    mCutAction->setIconVisibleInMenu(true);
    mCutAction->setEnabled(false);
    connect(mCutAction, SIGNAL(triggered()), this, SLOT(cutAct()));
    editMenu->addAction(mCutAction);

    editMenu->addSeparator();

    QAction *settingsAction = new QAction(tr("&Settings"), this);
    settingsAction->setShortcut(QKeySequence::Preferences);
    settingsAction->setIcon(QIcon::fromTheme("document-properties", QIcon(":/media/actions-icons/document-properties.png")));
    settingsAction->setIconVisibleInMenu(true);
    connect(settingsAction, SIGNAL(triggered()), this, SLOT(settingsAct()));
    editMenu->addAction(settingsAction);

    mInstrumentsMenu = menuBar()->addMenu(tr("&Instruments"));

    QAction *mCursorAction = new QAction(tr("Selection"), this);
    mCursorAction->setCheckable(true);
    mCursorAction->setIcon(QIcon(":/media/instruments-icons/cursor.png"));
    connect(mCursorAction, SIGNAL(triggered(bool)), this, SLOT(instumentsAct(bool)));
    mInstrumentsMenu->addAction(mCursorAction);
    mInstrumentsActMap.insert(CURSOR, mCursorAction);

    QAction *mEraserAction = new QAction(tr("Eraser"), this);
    mEraserAction->setCheckable(true);
    mEraserAction->setIcon(QIcon(":/media/instruments-icons/lastic.png"));
    connect(mEraserAction, SIGNAL(triggered(bool)), this, SLOT(instumentsAct(bool)));
    mInstrumentsMenu->addAction(mEraserAction);
    mInstrumentsActMap.insert(ERASER, mEraserAction);

    QAction *mColorPickerAction = new QAction(tr("Color picker"), this);
    mColorPickerAction->setCheckable(true);
    mColorPickerAction->setIcon(QIcon(":/media/instruments-icons/pipette.png"));
    connect(mColorPickerAction, SIGNAL(triggered(bool)), this, SLOT(instumentsAct(bool)));
    mInstrumentsMenu->addAction(mColorPickerAction);
    mInstrumentsActMap.insert(COLORPICKER, mColorPickerAction);

    QAction *mMagnifierAction = new QAction(tr("Magnifier"), this);
    mMagnifierAction->setCheckable(true);
    mMagnifierAction->setIcon(QIcon(":/media/instruments-icons/loupe.png"));
    connect(mMagnifierAction, SIGNAL(triggered(bool)), this, SLOT(instumentsAct(bool)));
    mInstrumentsMenu->addAction(mMagnifierAction);
    mInstrumentsActMap.insert(MAGNIFIER, mMagnifierAction);

    QAction *mPenAction = new QAction(tr("Pen"), this);
    mPenAction->setCheckable(true);
    mPenAction->setIcon(QIcon(":/media/instruments-icons/pencil.png"));
    connect(mPenAction, SIGNAL(triggered(bool)), this, SLOT(instumentsAct(bool)));
    mInstrumentsMenu->addAction(mPenAction);
    mInstrumentsActMap.insert(PEN, mPenAction);

    QAction *mLineAction = new QAction(tr("Line"), this);
    mLineAction->setCheckable(true);
    mLineAction->setIcon(QIcon(":/media/instruments-icons/line.png"));
    connect(mLineAction, SIGNAL(triggered(bool)), this, SLOT(instumentsAct(bool)));
    mInstrumentsMenu->addAction(mLineAction);
    mInstrumentsActMap.insert(LINE, mLineAction);

    QAction *mSprayAction = new QAction(tr("Spray"), this);
    mSprayAction->setCheckable(true);
    mSprayAction->setIcon(QIcon(":/media/instruments-icons/spray.png"));
    connect(mSprayAction, SIGNAL(triggered(bool)), this, SLOT(instumentsAct(bool)));
    mInstrumentsMenu->addAction(mSprayAction);
    mInstrumentsActMap.insert(SPRAY, mSprayAction);

    QAction *mFillAction = new QAction(tr("Fill"), this);
    mFillAction->setCheckable(true);
    mFillAction->setIcon(QIcon(":/media/instruments-icons/fill.png"));
    connect(mFillAction, SIGNAL(triggered(bool)), this, SLOT(instumentsAct(bool)));
    mInstrumentsMenu->addAction(mFillAction);
    mInstrumentsActMap.insert(FILL, mFillAction);

    QAction *mRectangleAction = new QAction(tr("Rectangle"), this);
    mRectangleAction->setCheckable(true);
    mRectangleAction->setIcon(QIcon(":/media/instruments-icons/rectangle.png"));
    connect(mRectangleAction, SIGNAL(triggered(bool)), this, SLOT(instumentsAct(bool)));
    mInstrumentsMenu->addAction(mRectangleAction);
    mInstrumentsActMap.insert(RECTANGLE, mRectangleAction);

    QAction *mEllipseAction = new QAction(tr("Ellipse"), this);
    mEllipseAction->setCheckable(true);
    mEllipseAction->setIcon(QIcon(":/media/instruments-icons/ellipse.png"));
    connect(mEllipseAction, SIGNAL(triggered(bool)), this, SLOT(instumentsAct(bool)));
    mInstrumentsMenu->addAction(mEllipseAction);
    mInstrumentsActMap.insert(ELLIPSE, mEllipseAction);

    QAction *curveLineAction = new QAction(tr("Curve"), this);
    curveLineAction->setCheckable(true);
    curveLineAction->setIcon(QIcon(":/media/instruments-icons/curve.png"));
    connect(curveLineAction, SIGNAL(triggered(bool)), this, SLOT(instumentsAct(bool)));
    mInstrumentsMenu->addAction(curveLineAction);
    mInstrumentsActMap.insert(CURVELINE, curveLineAction);

    QAction *mTextAction = new QAction(tr("Text"), this);
    mTextAction->setCheckable(true);
    mTextAction->setIcon(QIcon(":/media/instruments-icons/text.png"));
    connect(mTextAction, SIGNAL(triggered(bool)), this, SLOT(instumentsAct(bool)));
    mInstrumentsMenu->addAction(mTextAction);
    mInstrumentsActMap.insert(TEXT, mTextAction);
    // TODO: Add new instrument action here

    mEffectsMenu = menuBar()->addMenu(tr("E&ffects"));

    QAction *grayEfAction = new QAction(tr("Gray"), this);
    connect(grayEfAction, SIGNAL(triggered()), this, SLOT(effectsAct()));
    mEffectsMenu->addAction(grayEfAction);
    mEffectsActMap.insert(GRAY, grayEfAction);

    QAction *negativeEfAction = new QAction(tr("Negative"), this);
    connect(negativeEfAction, SIGNAL(triggered()), this, SLOT(effectsAct()));
    mEffectsMenu->addAction(negativeEfAction);
    mEffectsActMap.insert(NEGATIVE, negativeEfAction);

    QAction *binarizationEfAction = new QAction(tr("Binarization"), this);
    connect(binarizationEfAction, SIGNAL(triggered()), this, SLOT(effectsAct()));
    mEffectsMenu->addAction(binarizationEfAction);
    mEffectsActMap.insert(BINARIZATION, binarizationEfAction);

    QAction *gaussianBlurEfAction = new QAction(tr("Gaussian Blur"), this);
    connect(gaussianBlurEfAction, SIGNAL(triggered()), this, SLOT(effectsAct()));
    mEffectsMenu->addAction(gaussianBlurEfAction);
    mEffectsActMap.insert(GAUSSIANBLUR, gaussianBlurEfAction);

    QAction *gammaEfAction = new QAction(tr("Gamma"), this);
    connect(gammaEfAction, SIGNAL(triggered()), this, SLOT(effectsAct()));
    mEffectsMenu->addAction(gammaEfAction);
    mEffectsActMap.insert(GAMMA, gammaEfAction);

    QAction *sharpenEfAction = new QAction(tr("Sharpen"), this);
    connect(sharpenEfAction, SIGNAL(triggered()), this, SLOT(effectsAct()));
    mEffectsMenu->addAction(sharpenEfAction);
    mEffectsActMap.insert(SHARPEN, sharpenEfAction);

    QAction *customEfAction = new QAction(tr("Custom"), this);
    connect(customEfAction, SIGNAL(triggered()), this, SLOT(effectsAct()));
    mEffectsMenu->addAction(customEfAction);
    mEffectsActMap.insert(CUSTOM, customEfAction);

    mToolsMenu = menuBar()->addMenu(tr("&Tools"));

    QAction *resizeImAction = new QAction(tr("Image size"), this);
    connect(resizeImAction, SIGNAL(triggered()), this, SLOT(resizeImageAct()));
    mToolsMenu->addAction(resizeImAction);

    QAction *resizeCanAction = new QAction(tr("Canvas size"), this);
    connect(resizeCanAction, SIGNAL(triggered()), this, SLOT(resizeCanvasAct()));
    mToolsMenu->addAction(resizeCanAction);

    QMenu *rotateMenu = new QMenu(tr("Rotate"));

    QAction *rotateLAction = new QAction(tr("Counter-clockwise"), this);
    rotateLAction->setIcon(QIcon::fromTheme("object-rotate-left", QIcon(":/media/actions-icons/object-rotate-left.png")));
    rotateLAction->setIconVisibleInMenu(true);
    connect(rotateLAction, SIGNAL(triggered()), this, SLOT(rotateLeftImageAct()));
    rotateMenu->addAction(rotateLAction);

    QAction *rotateRAction = new QAction(tr("Clockwise"), this);
    rotateRAction->setIcon(QIcon::fromTheme("object-rotate-right", QIcon(":/media/actions-icons/object-rotate-right.png")));
    rotateRAction->setIconVisibleInMenu(true);
    connect(rotateRAction, SIGNAL(triggered()), this, SLOT(rotateRightImageAct()));
    rotateMenu->addAction(rotateRAction);

    mToolsMenu->addMenu(rotateMenu);

    QMenu *zoomMenu = new QMenu(tr("Zoom"));

    mZoomInAction = new QAction(tr("Zoom In"), this);
    mZoomInAction->setIcon(QIcon::fromTheme("zoom-in", QIcon(":/media/actions-icons/zoom-in.png")));
    mZoomInAction->setIconVisibleInMenu(true);
    connect(mZoomInAction, SIGNAL(triggered()), this, SLOT(zoomInAct()));
    zoomMenu->addAction(mZoomInAction);

    mZoomOutAction = new QAction(tr("Zoom Out"), this);
    mZoomOutAction->setIcon(QIcon::fromTheme("zoom-out", QIcon(":/media/actions-icons/zoom-out.png")));
    mZoomOutAction->setIconVisibleInMenu(true);
    connect(mZoomOutAction, SIGNAL(triggered()), this, SLOT(zoomOutAct()));
    zoomMenu->addAction(mZoomOutAction);

    QAction *advancedZoomAction = new QAction(tr("Advanced Zoom..."), this);
    advancedZoomAction->setIconVisibleInMenu(true);
    connect(advancedZoomAction, SIGNAL(triggered()), this, SLOT(advancedZoomAct()));
    zoomMenu->addAction(advancedZoomAction);

    mToolsMenu->addMenu(zoomMenu);

    QMenu *aboutMenu = menuBar()->addMenu(tr("&About"));

    QAction *aboutAction = new QAction(tr("&About EasyPaint"), this);
    aboutAction->setShortcut(QKeySequence::HelpContents);
    aboutAction->setIcon(QIcon::fromTheme("help-about", QIcon(":/media/actions-icons/help-about.png")));
    aboutAction->setIconVisibleInMenu(true);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(helpAct()));
    aboutMenu->addAction(aboutAction);

    QAction *aboutQtAction = new QAction(tr("About Qt"), this);
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    aboutMenu->addAction(aboutQtAction);

    updateShortcuts();
}

void MainWindow::initializeStatusBar()
{
    mStatusBar = new QStatusBar();
    setStatusBar(mStatusBar);

    mSizeLabel = new QLabel();
    mPosLabel = new QLabel();
    mColorPreviewLabel = new QLabel();
    mColorRGBLabel = new QLabel();

    mStatusBar->addPermanentWidget(mSizeLabel, -1);
    mStatusBar->addPermanentWidget(mPosLabel, 1);
    mStatusBar->addPermanentWidget(mColorPreviewLabel);
    mStatusBar->addPermanentWidget(mColorRGBLabel, -1);
}

void MainWindow::initializeToolBar()
{
    mToolbar = new ToolBar(mInstrumentsActMap, this);
    addToolBar(Qt::LeftToolBarArea, mToolbar);
    connect(mToolbar, SIGNAL(sendClearStatusBarColor()), this, SLOT(clearStatusBarColor()));
    connect(mToolbar, SIGNAL(sendClearImageSelection()), this, SLOT(clearImageSelection()));
}

void MainWindow::initializePaletteBar()
{
    mPaletteBar = new PaletteBar(mToolbar);
    addToolBar(Qt::BottomToolBarArea, mPaletteBar);
}

ImageArea* MainWindow::getCurrentImageArea()
{
    if (mTabWidget->currentWidget()) {
        QScrollArea *tempScrollArea = qobject_cast<QScrollArea*>(mTabWidget->currentWidget());
        ImageArea *tempArea = qobject_cast<ImageArea*>(tempScrollArea->widget());
        return tempArea;
    }
    return NULL;
}

ImageArea* MainWindow::getImageAreaByIndex(int index)
{
    QScrollArea *sa = static_cast<QScrollArea*>(mTabWidget->widget(index));
    ImageArea *ia = static_cast<ImageArea*>(sa->widget());
    return ia;
}

void MainWindow::activateTab(const int &index)
{
    if(index == -1)
        return;
    mTabWidget->setCurrentIndex(index);
    QSize size = getCurrentImageArea()->getImage()->size();
    mSizeLabel->setText(QString("%1 x %2").arg(size.width()).arg(size.height()));

    if(!getCurrentImageArea()->getFileName().isEmpty())
    {
        setWindowTitle(QString("%1 - EasyPaint").arg(getCurrentImageArea()->getFileName()));
    }
    else
    {
        setWindowTitle(QString("%1 - EasyPaint").arg(tr("Untitled Image")));
    }
    mUndoStackGroup->setActiveStack(getCurrentImageArea()->getUndoStack());
}

void MainWindow::setNewSizeToSizeLabel(const QSize &size)
{
    mSizeLabel->setText(QString("%1 x %2").arg(size.width()).arg(size.height()));
}

void MainWindow::setNewPosToPosLabel(const QPoint &pos)
{
    mPosLabel->setText(QString("%1,%2").arg(pos.x()).arg(pos.y()));
}

void MainWindow::setCurrentPipetteColor(const QColor &color)
{
    mColorRGBLabel->setText(QString("RGB: %1,%2,%3").arg(color.red())
                         .arg(color.green()).arg(color.blue()));

    QPixmap statusColorPixmap = QPixmap(10, 10);
    QPainter statusColorPainter;
    statusColorPainter.begin(&statusColorPixmap);
    statusColorPainter.fillRect(0, 0, 15, 15, color);
    statusColorPainter.end();
    mColorPreviewLabel->setPixmap(statusColorPixmap);
}

void MainWindow::clearStatusBarColor()
{
    mColorPreviewLabel->clear();
    mColorRGBLabel->clear();
}

void MainWindow::newAct()
{
    initializeNewTab();
}

void MainWindow::openAct()
{
    initializeNewTab(true);
}

void MainWindow::saveAct()
{
    getCurrentImageArea()->save();
    mTabWidget->setTabText(mTabWidget->currentIndex(), getCurrentImageArea()->getFileName().isEmpty() ?
                               tr("Untitled Image") : getCurrentImageArea()->getFileName() );
}

void MainWindow::saveAsAct()
{
    getCurrentImageArea()->saveAs();
    mTabWidget->setTabText(mTabWidget->currentIndex(), getCurrentImageArea()->getFileName().isEmpty() ?
                               tr("Untitled Image") : getCurrentImageArea()->getFileName() );
}

void MainWindow::printAct()
{
    getCurrentImageArea()->print();
}

void MainWindow::settingsAct()
{
    SettingsDialog settingsDialog;
    if(settingsDialog.exec() == QDialog::Accepted)
    {
        settingsDialog.sendSettingsToSingleton();
        DataSingleton::Instance()->writeSettings();
        updateShortcuts();
    }
}

void MainWindow::copyAct()
{
    if (ImageArea *imageArea = getCurrentImageArea())
        imageArea->copyImage();
}

void MainWindow::pasteAct()
{
    if (ImageArea *imageArea = getCurrentImageArea())
        imageArea->pasteImage();
}

void MainWindow::cutAct()
{
    if (ImageArea *imageArea = getCurrentImageArea())
        imageArea->cutImage();
}

void MainWindow::updateShortcuts()
{
    mNewAction->setShortcut(DataSingleton::Instance()->getFileShortcutByKey("New"));
    mOpenAction->setShortcut(DataSingleton::Instance()->getFileShortcutByKey("Open"));
    mSaveAction->setShortcut(DataSingleton::Instance()->getFileShortcutByKey("Save"));
    mSaveAsAction->setShortcut(DataSingleton::Instance()->getFileShortcutByKey("SaveAs"));
    mCloseAction->setShortcut(DataSingleton::Instance()->getFileShortcutByKey("Close"));
    mPrintAction->setShortcut(DataSingleton::Instance()->getFileShortcutByKey("Print"));
    mExitAction->setShortcut(DataSingleton::Instance()->getFileShortcutByKey("Exit"));

    mUndoAction->setShortcut(DataSingleton::Instance()->getEditShortcutByKey("Undo"));
    mRedoAction->setShortcut(DataSingleton::Instance()->getEditShortcutByKey("Redo"));
    mCopyAction->setShortcut(DataSingleton::Instance()->getEditShortcutByKey("Copy"));
    mPasteAction->setShortcut(DataSingleton::Instance()->getEditShortcutByKey("Paste"));
    mCutAction->setShortcut(DataSingleton::Instance()->getEditShortcutByKey("Cut"));

    mInstrumentsActMap[CURSOR]->setShortcut(DataSingleton::Instance()->getInstrumentShortcutByKey("Cursor"));
    mInstrumentsActMap[ERASER]->setShortcut(DataSingleton::Instance()->getInstrumentShortcutByKey("Lastic"));
    mInstrumentsActMap[COLORPICKER]->setShortcut(DataSingleton::Instance()->getInstrumentShortcutByKey("Pipette"));
    mInstrumentsActMap[MAGNIFIER]->setShortcut(DataSingleton::Instance()->getInstrumentShortcutByKey("Loupe"));
    mInstrumentsActMap[PEN]->setShortcut(DataSingleton::Instance()->getInstrumentShortcutByKey("Pen"));
    mInstrumentsActMap[LINE]->setShortcut(DataSingleton::Instance()->getInstrumentShortcutByKey("Line"));
    mInstrumentsActMap[SPRAY]->setShortcut(DataSingleton::Instance()->getInstrumentShortcutByKey("Spray"));
    mInstrumentsActMap[FILL]->setShortcut(DataSingleton::Instance()->getInstrumentShortcutByKey("Fill"));
    mInstrumentsActMap[RECTANGLE]->setShortcut(DataSingleton::Instance()->getInstrumentShortcutByKey("Rect"));
    mInstrumentsActMap[ELLIPSE]->setShortcut(DataSingleton::Instance()->getInstrumentShortcutByKey("Ellipse"));
    mInstrumentsActMap[CURVELINE]->setShortcut(DataSingleton::Instance()->getInstrumentShortcutByKey("Curve"));
    mInstrumentsActMap[TEXT]->setShortcut(DataSingleton::Instance()->getInstrumentShortcutByKey("Text"));
    // TODO: Add new instruments' shorcuts here

    mZoomInAction->setShortcut(DataSingleton::Instance()->getToolShortcutByKey("ZoomIn"));
    mZoomOutAction->setShortcut(DataSingleton::Instance()->getToolShortcutByKey("ZoomOut"));
}

void MainWindow::effectsAct()
{
    QAction *currentAction = static_cast<QAction*>(sender());
    getCurrentImageArea()->applyEffect(mEffectsActMap.key(currentAction));
}

void MainWindow::resizeImageAct()
{
    getCurrentImageArea()->resizeImage();
}

void MainWindow::resizeCanvasAct()
{
    getCurrentImageArea()->resizeCanvas();
}

void MainWindow::rotateLeftImageAct()
{
    getCurrentImageArea()->rotateImage(false);
}

void MainWindow::rotateRightImageAct()
{
    getCurrentImageArea()->rotateImage(true);
}

void MainWindow::zoomInAct()
{
    getCurrentImageArea()->zoomImage(2.0);
    getCurrentImageArea()->setZoomFactor(2.0);
}

void MainWindow::zoomOutAct()
{
    getCurrentImageArea()->zoomImage(0.5);
    getCurrentImageArea()->setZoomFactor(0.5);
}

void MainWindow::advancedZoomAct()
{
    bool ok;
    qreal factor = QInputDialog::getDouble(this, tr("Enter zoom factor"), tr("Zoom factor:"), 2.5, 0, 1000, 5, &ok);
    if (ok)
    {
        getCurrentImageArea()->zoomImage(factor);
        getCurrentImageArea()->setZoomFactor(factor);
    }
}

void MainWindow::closeTabAct()
{
    closeTab(mTabWidget->currentIndex());
}

void MainWindow::closeTab(int index)
{
    ImageArea *ia = getImageAreaByIndex(index);
    if(ia->getEdited())
    {
        int ans = QMessageBox::warning(this, tr("Closing Tab..."),
                                       tr("File has been modified\nDo you want to save changes?"),
                                       QMessageBox::Yes | QMessageBox::Default,
                                       QMessageBox::No, QMessageBox::Cancel | QMessageBox::Escape);
        switch(ans)
        {
        case QMessageBox::Yes:
            ia->save();
            break;
        case QMessageBox::Cancel:
            return;
        }
    }
    mUndoStackGroup->removeStack(ia->getUndoStack()); //for safety
    QWidget *wid = mTabWidget->widget(index);
    mTabWidget->removeTab(index);
    delete wid;
    if (mTabWidget->count() == 0)
    {
        setWindowTitle("Empty - EasyPaint");
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(!isSomethingModified() || closeAllTabs())
    {
        DataSingleton::Instance()->setWindowSize(size());
        DataSingleton::Instance()->writeState();
        event->accept();
    }
    else
        event->ignore();
}

bool MainWindow::isSomethingModified()
{
    for(int i = 0; i < mTabWidget->count(); ++i)
    {
        if(getImageAreaByIndex(i)->getEdited())
            return true;
    }
    return false;
}

bool MainWindow::closeAllTabs()
{

    while(mTabWidget->count() != 0)
    {
        ImageArea *ia = getImageAreaByIndex(0);
        if(ia->getEdited())
        {
            int ans = QMessageBox::warning(this, tr("Closing Tab..."),
                                           tr("File has been modified\nDo you want to save changes?"),
                                           QMessageBox::Yes | QMessageBox::Default,
                                           QMessageBox::No, QMessageBox::Cancel | QMessageBox::Escape);
            switch(ans)
            {
            case QMessageBox::Yes:
                ia->save();
                break;
            case QMessageBox::Cancel:
                return false;
            }
        }
        QWidget *wid = mTabWidget->widget(0);
        mTabWidget->removeTab(0);
        delete wid;
    }
    return true;
}

void MainWindow::setAllInstrumentsUnchecked(QAction *action)
{
    clearImageSelection();
    foreach (QAction *temp, mInstrumentsActMap)
    {
        if(temp != action)
            temp->setChecked(false);
    }
}

void MainWindow::setInstrumentChecked(InstrumentsEnum instrument)
{
    setAllInstrumentsUnchecked(NULL);
    if(instrument == NONE_INSTRUMENT || instrument == INSTRUMENTS_COUNT)
        return;
    mInstrumentsActMap[instrument]->setChecked(true);
}

void MainWindow::instumentsAct(bool state)
{
    QAction *currentAction = static_cast<QAction*>(sender());
    if(state)
    {
        if(currentAction == mInstrumentsActMap[COLORPICKER] && !mPrevInstrumentSetted)
        {
            DataSingleton::Instance()->setPreviousInstrument(DataSingleton::Instance()->getInstrument());
            mPrevInstrumentSetted = true;
        }
        setAllInstrumentsUnchecked(currentAction);
        currentAction->setChecked(true);
        DataSingleton::Instance()->setInstrument(mInstrumentsActMap.key(currentAction));
        emit sendInstrumentChecked(mInstrumentsActMap.key(currentAction));
    }
    else
    {
        setAllInstrumentsUnchecked(NULL);
        DataSingleton::Instance()->setInstrument(NONE_INSTRUMENT);
        emit sendInstrumentChecked(NONE_INSTRUMENT);
        if(currentAction == mInstrumentsActMap[CURSOR])
            DataSingleton::Instance()->setPreviousInstrument(mInstrumentsActMap.key(currentAction));
    }
}

void MainWindow::enableActions(int index)
{
    //if index == -1 it means, that there is no tabs
    bool isEnable = index == -1 ? false : true;

    mToolsMenu->setEnabled(isEnable);
    mEffectsMenu->setEnabled(isEnable);
    mInstrumentsMenu->setEnabled(isEnable);
    mToolbar->setEnabled(isEnable);
    mPaletteBar->setEnabled(isEnable);

    mSaveAction->setEnabled(isEnable);
    mSaveAsAction->setEnabled(isEnable);
    mCloseAction->setEnabled(isEnable);
    mPrintAction->setEnabled(isEnable);

    if(!isEnable)
    {
        setAllInstrumentsUnchecked(NULL);
        DataSingleton::Instance()->setInstrument(NONE_INSTRUMENT);
        emit sendInstrumentChecked(NONE_INSTRUMENT);
    }
}

void MainWindow::enableCopyCutActions(bool enable)
{
    mCopyAction->setEnabled(enable);
    mCutAction->setEnabled(enable);
}

void MainWindow::clearImageSelection()
{
    if (getCurrentImageArea())
    {
        getCurrentImageArea()->clearSelection();
        DataSingleton::Instance()->setPreviousInstrument(NONE_INSTRUMENT);
    }
}

void MainWindow::restorePreviousInstrument()
{
    setInstrumentChecked(DataSingleton::Instance()->getPreviousInstrument());
    DataSingleton::Instance()->setInstrument(DataSingleton::Instance()->getPreviousInstrument());
    emit sendInstrumentChecked(DataSingleton::Instance()->getPreviousInstrument());
    mPrevInstrumentSetted = false;
}

void MainWindow::setInstrument(InstrumentsEnum instrument)
{
    setInstrumentChecked(instrument);
    DataSingleton::Instance()->setInstrument(instrument);
    emit sendInstrumentChecked(instrument);
    mPrevInstrumentSetted = false;
}

void MainWindow::helpAct()
{
    QMessageBox::about(this, tr("About EasyPaint"),
                       QString("<b>EasyPaint</b> %1: %2 <br> <br> %3: "
                               "<a href=\"https://github.com/Gr1N/EasyPaint/\">https://github.com/Gr1N/EasyPaint/</a>"
                               "<br> <br>Copyright (c) 2012 EasyPaint team"
                               "<br> <br>%4:<ul>"
                               "<li><a href=\"mailto:grin.minsk@gmail.com\">Nikita Grishko</a> (Gr1N)</li>"
                               "<li><a href=\"mailto:faulknercs@yandex.ru\">Artem Stepanyuk</a> (faulknercs)</li>"
                               "<li><a href=\"mailto:denis.klimenko.92@gmail.com\">Denis Klimenko</a> (DenisKlimenko)</li>"
                               "<li><a href=\"mailto:bahdan.siamionau@gmail.com\">Bahdan Siamionau</a> (Bahdan)</li>"
                               "</ul>"
                               "<br> %5")
                       .arg(tr("version")).arg("0.1.0").arg(tr("Site")).arg(tr("Authors"))
                       .arg(tr("If you like <b>EasyPaint</b> and you want to share your opinion, or send a bug report, or want to suggest new features, we are waiting for you on our <a href=\"https://github.com/Gr1N/EasyPaint/issues?milestone=&sort=created&direction=desc&state=open\">tracker</a>.")));
}
