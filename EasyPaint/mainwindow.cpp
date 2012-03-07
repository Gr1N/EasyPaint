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

#include <QtGui/QApplication>
#include <QtGui/QAction>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QMessageBox>
#include <QtGui/QScrollArea>
#include <QtGui/QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initializeMainMenu();
    initializeToolBar();
    initializeStatusBar();
    initializeTabWidget();
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
    setCentralWidget(mTabWidget);
    initializeNewTab();
}

void MainWindow::initializeNewTab(const bool &isOpen)
{
    ImageArea *imageArea;
    QString fileName("new");
    if(isOpen)
    {
        imageArea = new ImageArea(isOpen);
        fileName = imageArea->getFileName();
    }
    else
    {
        imageArea = new ImageArea();
    }

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
}

void MainWindow::initializeMainMenu()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    QAction *newAction = new QAction(tr("&New"), this);
    newAction->setShortcut(QKeySequence::New);
    newAction->setIcon(QIcon::fromTheme("document-new"/*, QIcon("")*/));
//    newAction->setStatusTip();
    connect(newAction, SIGNAL(triggered()), this, SLOT(newAct()));
    fileMenu->addAction(newAction);

    QAction *openAction = new QAction(tr("&Open"), this);
    openAction->setShortcut(QKeySequence::Open);
    openAction->setIcon(QIcon::fromTheme("document-open"/*, QIcon("")*/));
//    newAction->setStatusTip();
    connect(openAction, SIGNAL(triggered()), this, SLOT(openAct()));
    fileMenu->addAction(openAction);

    QAction *saveAction = new QAction(tr("&Save"), this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setIcon(QIcon::fromTheme("document-save"/*, QIcon("")*/));
//    newAction->setStatusTip();
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveAct()));
    fileMenu->addAction(saveAction);

    QAction *saveAsAction = new QAction(tr("Save as..."), this);
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    saveAsAction->setIcon(QIcon::fromTheme("document-save-as"/*, QIcon("")*/));
//    newAction->setStatusTip();
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAsAct()));
    fileMenu->addAction(saveAsAction);

    QAction *closeAction = new QAction(tr("&Close"), this);
    closeAction->setShortcut(QKeySequence::Close);
    closeAction->setIcon(QIcon::fromTheme("window-close"/*, QIcon("")*/));
//    newAction->setStatusTip();
//    connect();
    fileMenu->addAction(closeAction);

    fileMenu->addSeparator();

    QAction *printAction = new QAction(tr("&Print"), this);
    printAction->setShortcut(QKeySequence::Print);
    printAction->setIcon(QIcon::fromTheme("document-print"/*, QIcon("")*/));
//    newAction->setStatusTip();
    connect(printAction, SIGNAL(triggered()), this, SLOT(printAct()));
    fileMenu->addAction(printAction);

    fileMenu->addSeparator();

    QAction *exitAction = new QAction(tr("&Exit"), this);
    exitAction->setShortcut(QKeySequence::Quit);
    exitAction->setIcon(QIcon::fromTheme("application-exit"/*, QIcon("")*/));
//    newAction->setStatusTip();
//    connect();
    fileMenu->addAction(exitAction);

    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));

    QAction *undoAction = new QAction(tr("&Undo"), this);
    undoAction->setShortcut(QKeySequence::Undo);
    undoAction->setIcon(QIcon::fromTheme("edit-undo"/*, QIcon("")*/));
//    newAction->setStatusTip();
//    connect();
    editMenu->addAction(undoAction);

    QAction *redoAction = new QAction(tr("&Redo"), this);
    redoAction->setShortcut(QKeySequence::Redo);
    redoAction->setIcon(QIcon::fromTheme("edit-redo"/*, QIcon("")*/));
//    newAction->setStatusTip();
//    connect();
    editMenu->addAction(redoAction);

    editMenu->addSeparator();

    QAction *copyAction = new QAction(tr("&Copy"), this);
    copyAction->setShortcut(QKeySequence::Copy);
    copyAction->setIcon(QIcon::fromTheme("edit-copy"/*, QIcon("")*/));
//    newAction->setStatusTip();
//    connect();
    editMenu->addAction(copyAction);

    QAction *pasteAction = new QAction(tr("&Paste"), this);
    pasteAction->setShortcut(QKeySequence::Paste);
    pasteAction->setIcon(QIcon::fromTheme("edit-paste"/*, QIcon("")*/));
//    newAction->setStatusTip();
//    connect();
    editMenu->addAction(pasteAction);

    QAction *cutAction = new QAction(tr("C&ut"), this);
    cutAction->setShortcut(QKeySequence::Cut);
    cutAction->setIcon(QIcon::fromTheme("edit-cut"/*, QIcon("")*/));
//    newAction->setStatusTip();
//    connect();
    editMenu->addAction(cutAction);

    editMenu->addSeparator();

    QAction *settingsAction = new QAction(tr("&Settings"), this);
    settingsAction->setShortcut(QKeySequence::Preferences);
    settingsAction->setIcon(QIcon::fromTheme("document-properties"/*, QIcon("")*/));
//    newAction->setStatusTip();
//    connect();
    editMenu->addAction(settingsAction);

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
//    newAction->setStatusTip();
    connect(rotateLAction, SIGNAL(triggered()), this, SLOT(rotateLeftImageAct()));
    rotateMenu->addAction(rotateLAction);

    QAction *rotateRAction = new QAction(tr("Right"), this);
    rotateRAction->setIcon(QIcon::fromTheme("object-rotate-right"/*, QIcon("")*/));
//    newAction->setStatusTip();
    connect(rotateRAction, SIGNAL(triggered()), this, SLOT(rotateRightImageAct()));
    rotateMenu->addAction(rotateRAction);

    toolsMenu->addMenu(rotateMenu);

    QMenu *aboutMenu = menuBar()->addMenu(tr("&About"));

    QAction *aboutAction = new QAction(tr("&About"), this);
    aboutAction->setShortcut(QKeySequence::HelpContents);
    aboutAction->setIcon(QIcon::fromTheme("help-browser"/*, QIcon("")*/));
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
}

ImageArea* MainWindow::getCurrentImageArea()
{
    QScrollArea *tempScrollArea = qobject_cast<QScrollArea*>(mTabWidget->currentWidget());
    ImageArea *tempArea = qobject_cast<ImageArea*>(tempScrollArea->widget());
    return tempArea;
}

void MainWindow::activateTab(const int &index)
{
    mTabWidget->setCurrentIndex(index);
    QSize size = getCurrentImageArea()->getImage()->size();
    mSizeLabel->setText(QString("%1 x %2").arg(size.width()).arg(size.height()));
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

void MainWindow::helpAct()
{
    QMessageBox::about(this, tr("About EasyPaint"),
                       QString("EasyPaint version: %1 <br> <br> Site: "
                               "<a href=\"https://github.com/Gr1N/EasyPaint/\">https://github.com/Gr1N/EasyPaint/</a>"
                               "<br> <br>Copyright (c) 2012 Nikita Grishko"
                               "<br> <br>Authors:<ul>"
                               "<li>Nikita Grishko (Gr1N)</li>"
                               "</ul>")
                       .arg(tr("0.0.1")));
}
