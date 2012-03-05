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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

QT_BEGIN_NAMESPACE
//class QAction;
class QStatusBar;
class QTabWidget;
class ToolBar;
class ImageArea;
QT_END_NAMESPACE

/**
 * @brief Main wondow class.
 *
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void initializeMainMenu();
    void initializeStatusBar();
    void initializeToolBar();
    void initializeTabWidget();
    /**
     * @brief Initialize new tab for tab bar with new ImageArea and connect all needed slots.
     *
     * @param isOpen Flag which shows opens a new image or from file.
     */
    void initializeNewTab(const bool &isOpen = false);
    /**
     * @brief Get current ImageArea from current tab.
     *
     * @return ImageArea Geted ImageArea.
     */
    ImageArea* getCurrentImageArea();

    QStatusBar *mStatusBar;
    QTabWidget *mTabWidget;
    ToolBar *mToolbar;
//    QAction
//            *mCloseAction, *mPrintAction, *mUndoAction, *mRedoAction,
//            *mCopyAction, *mPasteAction, *mSettingsAction;

private slots:
    void newAct();
    void openAct();
    void helpAct();
    void saveAct();
    void saveAsAct();
    void effectGrayAct();
    void effectNegativeAct();

};

#endif // MAINWINDOW_H
