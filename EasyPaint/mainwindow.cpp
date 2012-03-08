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
#include "toolbar.h"
#include "imagearea.h"
#include "datasingleton.h"

#include <QtGui/QApplication>
#include <QtGui/QAction>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QMessageBox>
#include <QtGui/QScrollArea>
#include <QtGui/QLabel>
#include <QtGui/QtEvents>

MainWindow::MainWindow(QStringList filePaths, QWidget *parent)
    : QMainWindow(parent)
{
    initializeMainMenu();
    initializeToolBar();
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

        connect(imageArea, SIGNAL(sendFirstColorView()), mToolbar, SLOT(setFirstColorView()));
        connect(imageArea, SIGNAL(sendSecondColorView()), mToolbar, SLOT(setSecondColorView()));
        connect(imageArea, SIGNAL(sendNewImageSize(QSize)), this, SLOT(setNewSizeToSizeLabel(QSize)));
        connect(imageArea, SIGNAL(sendCursorPos(QPoint)), this, SLOT(setNewPosToPosLabel(QPoint)));

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

    QAction *newAction = new QAction(tr("&New"), this);
    newAction->setShortcut(QKeySequence::New);
    newAction->setIcon(QIcon::fromTheme("document-new"/*, QIcon("")*/));
    newAction->setIconVisibleInMenu(true);
//    newAction->setStatusTip();
    connect(newAction, SIGNAL(triggered()), this, SLOT(newAct()));
    fileMenu->addAction(newAction);

    QAction *openAction = new QAction(tr("&Open"), this);
    openAction->setShortcut(QKeySequence::Open);
    openAction->setIcon(QIcon::fromTheme("document-open"/*, QIcon("")*/));
    openAction->setIconVisibleInMenu(true);
//    newAction->setStatusTip();
    connect(openAction, SIGNAL(triggered()), this, SLOT(openAct()));
    fileMenu->addAction(openAction);

    QAction *saveAction = new QAction(tr("&Save"), this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setIcon(QIcon::fromTheme("document-save"/*, QIcon("")*/));
    saveAction->setIconVisibleInMenu(true);
//    newAction->setStatusTip();
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveAct()));
    fileMenu->addAction(saveAction);

    QAction *saveAsAction = new QAction(tr("Save as..."), this);
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    saveAsAction->setIcon(QIcon::fromTheme("document-save-as"/*, QIcon("")*/));
    saveAsAction->setIconVisibleInMenu(true);
//    newAction->setStatusTip();
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAsAct()));
    fileMenu->addAction(saveAsAction);

    QAction *closeAction = new QAction(tr("&Close"), this);
    closeAction->setShortcut(QKeySequence::Close);
    closeAction->setIcon(QIcon::fromTheme("window-close"/*, QIcon("")*/));
    closeAction->setIconVisibleInMenu(true);
//    newAction->setStatusTip();
    connect(closeAction, SIGNAL(triggered()), this, SLOT(closeTabAct()));
    fileMenu->addAction(closeAction);

    fileMenu->addSeparator();

    QAction *printAction = new QAction(tr("&Print"), this);
    printAction->setShortcut(QKeySequence::Print);
    printAction->setIcon(QIcon::fromTheme("document-print"/*, QIcon("")*/));
    printAction->setIconVisibleInMenu(true);
//    newAction->setStatusTip();
    connect(printAction, SIGNAL(triggered()), this, SLOT(printAct()));
    fileMenu->addAction(printAction);

    fileMenu->addSeparator();

    QAction *exitAction = new QAction(tr("&Exit"), this);
    exitAction->setShortcut(QKeySequence::Quit);
    exitAction->setIcon(QIcon::fromTheme("application-exit"/*, QIcon("")*/));
    exitAction->setIconVisibleInMenu(true);
//    newAction->setStatusTip();
    connect(exitAction, SIGNAL(triggered()), SLOT(close()));
    fileMenu->addAction(exitAction);

    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));

    QAction *undoAction = new QAction(tr("&Undo"), this);
    undoAction->setShortcut(QKeySequence::Undo);
    undoAction->setIcon(QIcon::fromTheme("edit-undo"/*, QIcon("")*/));
    undoAction->setIconVisibleInMenu(true);
//    newAction->setStatusTip();
//    connect();
    editMenu->addAction(undoAction);

    QAction *redoAction = new QAction(tr("&Redo"), this);
    redoAction->setShortcut(QKeySequence::Redo);
    redoAction->setIcon(QIcon::fromTheme("edit-redo"/*, QIcon("")*/));
    redoAction->setIconVisibleInMenu(true);
//    newAction->setStatusTip();
//    connect();
    editMenu->addAction(redoAction);

    editMenu->addSeparator();

    QAction *copyAction = new QAction(tr("&Copy"), this);
    copyAction->setShortcut(QKeySequence::Copy);
    copyAction->setIcon(QIcon::fromTheme("edit-copy"/*, QIcon("")*/));
    copyAction->setIconVisibleInMenu(true);
//    newAction->setStatusTip();
//    connect();
    editMenu->addAction(copyAction);

    QAction *pasteAction = new QAction(tr("&Paste"), this);
    pasteAction->setShortcut(QKeySequence::Paste);
    pasteAction->setIcon(QIcon::fromTheme("edit-paste"/*, QIcon("")*/));
    pasteAction->setIconVisibleInMenu(true);
//    newAction->setStatusTip();
//    connect();
    editMenu->addAction(pasteAction);

    QAction *cutAction = new QAction(tr("C&ut"), this);
    cutAction->setShortcut(QKeySequence::Cut);
    cutAction->setIcon(QIcon::fromTheme("edit-cut"/*, QIcon("")*/));
    cutAction->setIconVisibleInMenu(true);
//    newAction->setStatusTip();
//    connect();
    editMenu->addAction(cutAction);

    editMenu->addSeparator();

    QAction *settingsAction = new QAction(tr("&Settings"), this);
    settingsAction->setShortcut(QKeySequence::Preferences);
    settingsAction->setIcon(QIcon::fromTheme("document-properties"/*, QIcon("")*/));
    settingsAction->setIconVisibleInMenu(true);
//    newAction->setStatusTip();
//    connect();
    editMenu->addAction(settingsAction);

    QMenu *instrumentsMenu = menuBar()->addMenu(tr("&Instruments"));

    mCursorAction = new QAction(tr("Cursor"), this);
    mCursorAction->setCheckable(true);
    connect(mCursorAction, SIGNAL(triggered(bool)), this, SLOT(cursorAct(bool)));
    instrumentsMenu->addAction(mCursorAction);

    mLasticAction = new QAction(tr("Lastic"), this);
    mLasticAction->setCheckable(true);
    connect(mLasticAction, SIGNAL(triggered(bool)), this, SLOT(lasticAct(bool)));
    instrumentsMenu->addAction(mLasticAction);

    mPipetteAction = new QAction(tr("Pipette"), this);
    mPipetteAction->setCheckable(true);
    connect(mPipetteAction, SIGNAL(triggered(bool)), this, SLOT(pipetteAct(bool)));
    instrumentsMenu->addAction(mPipetteAction);

    mLoupeAction = new QAction(tr("Loupe"), this);
    mLoupeAction->setCheckable(true);
    connect(mLoupeAction, SIGNAL(triggered(bool)), this, SLOT(loupeAct(bool)));
    instrumentsMenu->addAction(mLoupeAction);

    mPenAction = new QAction(tr("Pen"), this);
    mPenAction->setCheckable(true);
    connect(mPenAction, SIGNAL(triggered(bool)), this, SLOT(penAct(bool)));
    instrumentsMenu->addAction(mPenAction);

    mLineAction = new QAction(tr("Line"), this);
    mLineAction->setCheckable(true);
    connect(mLineAction, SIGNAL(triggered(bool)), this, SLOT(lineAct(bool)));
    instrumentsMenu->addAction(mLineAction);

    mSprayAction = new QAction(tr("Spray"), this);
    mSprayAction->setCheckable(true);
    connect(mSprayAction, SIGNAL(triggered(bool)), this, SLOT(sprayAct(bool)));
    instrumentsMenu->addAction(mSprayAction);

    mFillAction = new QAction(tr("Fill"), this);
    mFillAction->setCheckable(true);
    connect(mFillAction, SIGNAL(triggered(bool)), this, SLOT(fillAct(bool)));
    instrumentsMenu->addAction(mFillAction);

    mRectAction = new QAction(tr("Rect"), this);
    mRectAction->setCheckable(true);
    connect(mRectAction, SIGNAL(triggered(bool)), this, SLOT(rectAct(bool)));
    instrumentsMenu->addAction(mRectAction);

    mEllipseAction = new QAction(tr("Ellipse"), this);
    mEllipseAction->setCheckable(true);
    connect(mEllipseAction, SIGNAL(triggered(bool)), this, SLOT(ellipseAct(bool)));
    instrumentsMenu->addAction(mEllipseAction);

    QMenu *effectsMenu = menuBar()->addMenu(tr("E&ffects"));

    QAction *grayEfAction = new QAction(tr("Gray"), this);
//    newAction->setStatusTip();
    connect(grayEfAction, SIGNAL(triggered()), this, SLOT(effectGrayAct()));
    effectsMenu->addAction(grayEfAction);

    QAction *negativeEfAction = new QAction(tr("Negative"), this);
//    newAction->setStatusTip();
    connect(negativeEfAction, SIGNAL(triggered()), this, SLOT(effectNegativeAct()));
    effectsMenu->addAction(negativeEfAction);

    QMenu *toolsMenu = menuBar()->addMenu(tr("&Tools"));

    QAction *resizeImAction = new QAction(tr("Resize"), this);
//    newAction->setStatusTip();
    connect(resizeImAction, SIGNAL(triggered()), this, SLOT(resizeImageAct()));
    toolsMenu->addAction(resizeImAction);

    QMenu *rotateMenu = new QMenu(tr("Rotate"));

    QAction *rotateLAction = new QAction(tr("Left"), this);
    rotateLAction->setIcon(QIcon::fromTheme("object-rotate-left"/*, QIcon("")*/));
    rotateLAction->setIconVisibleInMenu(true);
//    newAction->setStatusTip();
    connect(rotateLAction, SIGNAL(triggered()), this, SLOT(rotateLeftImageAct()));
    rotateMenu->addAction(rotateLAction);

    QAction *rotateRAction = new QAction(tr("Right"), this);
    rotateRAction->setIcon(QIcon::fromTheme("object-rotate-right"/*, QIcon("")*/));
    rotateRAction->setIconVisibleInMenu(true);
//    newAction->setStatusTip();
    connect(rotateRAction, SIGNAL(triggered()), this, SLOT(rotateRightImageAct()));
    rotateMenu->addAction(rotateRAction);

    toolsMenu->addMenu(rotateMenu);

    QMenu *aboutMenu = menuBar()->addMenu(tr("&About"));

    QAction *aboutAction = new QAction(tr("&About"), this);
    aboutAction->setShortcut(QKeySequence::HelpContents);
    aboutAction->setIcon(QIcon::fromTheme("help-browser"/*, QIcon("")*/));
    aboutAction->setIconVisibleInMenu(true);
//    newAction->setStatusTip();
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(helpAct()));
    aboutMenu->addAction(aboutAction);

    QAction *aboutQtAction = new QAction(tr("About Qt"), this);
//    newAction->setStatusTip();
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    aboutMenu->addAction(aboutQtAction);
}

void MainWindow::initializeStatusBar()
{
    mStatusBar = new QStatusBar();
    setStatusBar(mStatusBar);

    mSizeLabel = new QLabel();
    mPosLabel = new QLabel();

    mStatusBar->addPermanentWidget(mSizeLabel, -1);
    mStatusBar->addPermanentWidget(mPosLabel, 1);
}

void MainWindow::initializeToolBar()
{
    mToolbar = new ToolBar(this);
    addToolBar(Qt::LeftToolBarArea, mToolbar);
    connect(mToolbar, SIGNAL(sendInstrumentChecked(InstrumentsEnum)), this, SLOT(setInstrumentChecked(InstrumentsEnum)));
    connect(this, SIGNAL(sendInstrumentChecked(InstrumentsEnum)), mToolbar, SLOT(setInstrumentChecked(InstrumentsEnum)));
}

ImageArea* MainWindow::getCurrentImageArea()
{
    QScrollArea *tempScrollArea = qobject_cast<QScrollArea*>(mTabWidget->currentWidget());
    ImageArea *tempArea = qobject_cast<ImageArea*>(tempScrollArea->widget());
    return tempArea;
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
}

void MainWindow::setNewSizeToSizeLabel(const QSize &size)
{
    mSizeLabel->setText(QString("%1 x %2").arg(size.width()).arg(size.height()));
}

void MainWindow::setNewPosToPosLabel(const QPoint &pos)
{
    mPosLabel->setText(QString("%1,%2").arg(pos.x()).arg(pos.y()));
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
    mTabWidget->setTabText(mTabWidget->currentIndex(), getCurrentImageArea()->getFileName());
}

void MainWindow::saveAsAct()
{
    getCurrentImageArea()->saveAs();
    mTabWidget->setTabText(mTabWidget->currentIndex(), getCurrentImageArea()->getFileName());
}

void MainWindow::printAct()
{
    getCurrentImageArea()->print();
}

void MainWindow::effectGrayAct()
{
    getCurrentImageArea()->effectGray();
}

void MainWindow::effectNegativeAct()
{
    getCurrentImageArea()->effectNegative();
}

void MainWindow::resizeImageAct()
{
    getCurrentImageArea()->resizeImage();
}

void MainWindow::rotateLeftImageAct()
{
    getCurrentImageArea()->rotateImage(true);
}

void MainWindow::rotateRightImageAct()
{
    getCurrentImageArea()->rotateImage(false);
}

void MainWindow::closeTabAct()
{
    closeTab(mTabWidget->currentIndex());
}

void MainWindow::closeTab(int index)
{
    //ImageArea *ia = static_cast<ImageArea*>(static_cast<QScrollArea*>(mTabWidget->widget(index))->widget());

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
    QWidget *wid = mTabWidget->widget(index);
    mTabWidget->removeTab(index);
    delete wid;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(!isSomethingModified())
        event->accept();
    else if(closeAllTabs())
        event->accept();
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
    if(action != mCursorAction)
        mCursorAction->setChecked(false);
    if(action != mLasticAction)
        mLasticAction->setChecked(false);
    if(action != mPipetteAction)
        mPipetteAction->setChecked(false);
    if(action != mLoupeAction)
        mLoupeAction->setChecked(false);
    if(action != mPenAction)
        mPenAction->setChecked(false);
    if(action != mLineAction)
        mLineAction->setChecked(false);
    if(action != mSprayAction)
        mSprayAction->setChecked(false);
    if(action != mFillAction)
        mFillAction->setChecked(false);
    if(action != mRectAction)
        mRectAction->setChecked(false);
    if(action != mEllipseAction)
        mEllipseAction->setChecked(false);
}

void MainWindow::setInstrumentChecked(InstrumentsEnum instrument)
{
    setAllInstrumentsUnchecked(new QAction(this));
    switch(instrument)
    {
    case NONE:
        mCursorAction->setChecked(true);
        break;
    case LASTIC:
        mLasticAction->setChecked(true);
        break;
    case PIPETTE:
        mPipetteAction->setChecked(true);
        break;
    case LOUPE:
        mLoupeAction->setChecked(true);
        break;
    case PEN:
        mPenAction->setChecked(true);
        break;
    case LINE:
        mLineAction->setChecked(true);
        break;
    case SPRAY:
        mSprayAction->setChecked(true);
        break;
    case FILL:
        mFillAction->setChecked(true);
        break;
    case RECT:
        mRectAction->setChecked(true);
        break;
    case ELLIPSE:
        mEllipseAction->setChecked(true);
        break;
    }
}

void MainWindow::cursorAct(const bool &state)
{
    if(state)
    {
        setAllInstrumentsUnchecked(mCursorAction);
        mCursorAction->setChecked(true);
        DataSingleton::Instance()->setInstrument(NONE);
        emit sendInstrumentChecked(NONE);
    }
    else
    {
        setAllInstrumentsUnchecked(new QAction(this));
        DataSingleton::Instance()->setInstrument(NONE);
        emit sendInstrumentChecked(NONE);
    }
}

void MainWindow::lasticAct(const bool &state)
{
    if(state)
    {
        setAllInstrumentsUnchecked(mLasticAction);
        mLasticAction->setChecked(true);
        DataSingleton::Instance()->setInstrument(LASTIC);
        emit sendInstrumentChecked(LASTIC);
    }
    else
    {
        setAllInstrumentsUnchecked(new QAction(this));
        DataSingleton::Instance()->setInstrument(NONE);
        emit sendInstrumentChecked(NONE);
    }
}

void MainWindow::pipetteAct(const bool &state)
{
    if(state)
    {
        setAllInstrumentsUnchecked(mPipetteAction);
        mPipetteAction->setChecked(true);
        DataSingleton::Instance()->setInstrument(PIPETTE);
        emit sendInstrumentChecked(PIPETTE);
    }
    else
    {
        setAllInstrumentsUnchecked(new QAction(this));
        DataSingleton::Instance()->setInstrument(NONE);
        emit sendInstrumentChecked(NONE);
    }
}

void MainWindow::loupeAct(const bool &state)
{
    if(state)
    {
        setAllInstrumentsUnchecked(mLoupeAction);
        mLoupeAction->setChecked(true);
        DataSingleton::Instance()->setInstrument(LOUPE);
        emit sendInstrumentChecked(LOUPE);
    }
    else
    {
        setAllInstrumentsUnchecked(new QAction(this));
        DataSingleton::Instance()->setInstrument(NONE);
        emit sendInstrumentChecked(NONE);
    }
}

void MainWindow::penAct(const bool &state)
{
    if(state)
    {
        setAllInstrumentsUnchecked(mPenAction);
        mPenAction->setChecked(true);
        DataSingleton::Instance()->setInstrument(PEN);
        emit sendInstrumentChecked(PEN);
    }
    else
    {
        setAllInstrumentsUnchecked(new QAction(this));
        DataSingleton::Instance()->setInstrument(NONE);
        emit sendInstrumentChecked(NONE);
    }
}

void MainWindow::lineAct(const bool &state)
{
    if(state)
    {
        setAllInstrumentsUnchecked(mLineAction);
        mLineAction->setChecked(true);
        DataSingleton::Instance()->setInstrument(LINE);
        emit sendInstrumentChecked(LINE);
    }
    else
    {
        setAllInstrumentsUnchecked(new QAction(this));
        DataSingleton::Instance()->setInstrument(NONE);
        emit sendInstrumentChecked(NONE);
    }
}

void MainWindow::sprayAct(const bool &state)
{
    if(state)
    {
        setAllInstrumentsUnchecked(mSprayAction);
        mSprayAction->setChecked(true);
        DataSingleton::Instance()->setInstrument(SPRAY);
        emit sendInstrumentChecked(SPRAY);
    }
    else
    {
        setAllInstrumentsUnchecked(new QAction(this));
        DataSingleton::Instance()->setInstrument(NONE);
        emit sendInstrumentChecked(NONE);
    }
}

void MainWindow::fillAct(const bool &state)
{
    if(state)
    {
        setAllInstrumentsUnchecked(mFillAction);
        mLasticAction->setChecked(true);
        DataSingleton::Instance()->setInstrument(FILL);
        emit sendInstrumentChecked(FILL);
    }
    else
    {
        setAllInstrumentsUnchecked(new QAction(this));
        DataSingleton::Instance()->setInstrument(NONE);
        emit sendInstrumentChecked(NONE);
    }
}

void MainWindow::rectAct(const bool &state)
{
    if(state)
    {
        setAllInstrumentsUnchecked(mRectAction);
        mRectAction->setChecked(true);
        DataSingleton::Instance()->setInstrument(RECT);
        emit sendInstrumentChecked(RECT);
    }
    else
    {
        setAllInstrumentsUnchecked(new QAction(this));
        DataSingleton::Instance()->setInstrument(NONE);
        emit sendInstrumentChecked(NONE);
    }
}

void MainWindow::ellipseAct(const bool &state)
{
    if(state)
    {
        setAllInstrumentsUnchecked(mEllipseAction);
        mEllipseAction->setChecked(true);
        DataSingleton::Instance()->setInstrument(ELLIPSE);
        emit sendInstrumentChecked(ELLIPSE);
    }
    else
    {
        setAllInstrumentsUnchecked(new QAction(this));
        DataSingleton::Instance()->setInstrument(NONE);
        emit sendInstrumentChecked(NONE);
    }
}

void MainWindow::helpAct()
{
    QMessageBox::about(this, tr("About EasyPaint"),
                       QString("EasyPaint version: %1 <br> <br> Site: "
                               "<a href=\"https://github.com/Gr1N/EasyPaint/\">https://github.com/Gr1N/EasyPaint/</a>"
                               "<br> <br>Copyright (c) 2012 Nikita Grishko"
                               "<br> <br>Authors:<ul>"
                               "<li>Nikita Grishko (Gr1N)</li>"
                               "<li>Artem Stepanyuk (faulknercs)</li>"
                               "<li>Denis Klimenko (DenisKlimenko)</li>"
                               "</ul>")
                       .arg(tr("0.0.1")));
}
