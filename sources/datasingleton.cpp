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

#include "datasingleton.h"

#include <QtCore/QSettings>

DataSingleton* DataSingleton::m_pInstance = 0;

DataSingleton::DataSingleton()
{
    mPrimaryColor = Qt::black;
    mSecondaryColor = Qt::white;
    mPenSize = 1;
    mCurrentInstrument = NONE;
    mPreviousInstrument = NONE;
    readSetting();
}

DataSingleton* DataSingleton::Instance()
{
    if(!m_pInstance)
        m_pInstance = new DataSingleton;

    return m_pInstance;
}

void DataSingleton::readSetting()
{
    QSettings settings;
    mBaseSize = settings.value("/Settings/BaseSize", QSize(400, 300)).toSize();
    mIsAutoSave = settings.value("/Settings/IsAutoSave", false).toBool();
    mAutoSaveInterval = settings.value("/Settings/AutoSaveInterval", 300000).toInt();
    mHistoryDepth = settings.value("/Settings/HistoryDepth", 40).toInt();
    mAppLanguage = settings.value("/Settings/AppLanguage", "system").toString();

    //read shortcuts for file menu
    mFileShortcuts.insert("New", settings.value("/Shortcuts/File/New", "Ctrl+N").toString());
    mFileShortcuts.insert("Open", settings.value("/Shortcuts/File/Open", "Ctrl+O").toString());
    mFileShortcuts.insert("Save", settings.value("/Shortcuts/File/Save", "Ctrl+S").toString());
    mFileShortcuts.insert("SaveAs", settings.value("/Shortcuts/File/SaveAs", "Ctrl+Shift+S").toString());
    mFileShortcuts.insert("Close", settings.value("/Shortcuts/File/Close", "Ctrl+W").toString());
    mFileShortcuts.insert("Print", settings.value("/Shortcuts/File/Print", "Ctrl+P").toString());
    mFileShortcuts.insert("Exit", settings.value("/Shortcuts/File/Exit", "Ctrl+Q").toString());

    //read shortcuts for edit menu
    mEditShortcuts.insert("Undo", settings.value("/Shortcuts/Edit/Undo", "Ctrl+Z").toString());
    mEditShortcuts.insert("Redo", settings.value("/Shortcuts/Edit/Redo", "Ctrl+Shift+Z").toString());
    mEditShortcuts.insert("Copy", settings.value("/Shortcuts/Edit/Copy", "Ctrl+C").toString());
    mEditShortcuts.insert("Paste", settings.value("/Shortcuts/Edit/Paste", "Ctrl+V").toString());
    mEditShortcuts.insert("Cut", settings.value("/Shortcuts/Edit/Cut", "Ctrl+X").toString());

    //read shortcuts for instruments menu
    mInstrumentsShortcuts.insert("Cursor", settings.value("/Shortcuts/Instruments/Cursor", "Ctrl+1").toString());
    mInstrumentsShortcuts.insert("Lastic", settings.value("/Shortcuts/Instruments/Lastic", "Ctrl+2").toString());
    mInstrumentsShortcuts.insert("Pipette", settings.value("/Shortcuts/Instruments/Pipette", "Ctrl+3").toString());
    mInstrumentsShortcuts.insert("Loupe", settings.value("/Shortcuts/Instruments/Loupe", "Ctrl+4").toString());
    mInstrumentsShortcuts.insert("Pen", settings.value("/Shortcuts/Instruments/Pen", "Ctrl+5").toString());
    mInstrumentsShortcuts.insert("Line", settings.value("/Shortcuts/Instruments/Line", "Ctrl+6").toString());
    mInstrumentsShortcuts.insert("Spray", settings.value("/Shortcuts/Instruments/Spray", "Ctrl+7").toString());
    mInstrumentsShortcuts.insert("Fill", settings.value("/Shortcuts/Instruments/Fill", "Ctrl+8").toString());
    mInstrumentsShortcuts.insert("Rect", settings.value("/Shortcuts/Instruments/Rect", "Ctrl+9").toString());
    mInstrumentsShortcuts.insert("Ellipse", settings.value("/Shortcuts/Instruments/Ellipse", "Ctrl+0").toString());

    //read shortcuts for tools menu
    mToolsShortcuts.insert("ZoomIn", settings.value("/Shortcuts/Tools/Zoom/ZoomIn", "Ctrl++").toString());
    mToolsShortcuts.insert("ZoomOut", settings.value("/Shortcuts/Tools/Zoom/ZoomOut", "Ctrl+-").toString());
}

void DataSingleton::writeSettings()
{
    QSettings settings;
    settings.setValue("/Settings/BaseSize", mBaseSize);
    settings.setValue("/Settings/IsAutoSave", mIsAutoSave);
    settings.setValue("/Settings/AutoSaveInterval", mAutoSaveInterval);
    settings.setValue("/Settings/HistoryDepth", mHistoryDepth);
    settings.setValue("/Settings/AppLanguage", mAppLanguage);

    //write shortcuts for file menu
    settings.setValue("/Shortcuts/File/New", mFileShortcuts["New"]);
    settings.setValue("/Shortcuts/File/Open", mFileShortcuts["Open"]);
    settings.setValue("/Shortcuts/File/Save", mFileShortcuts["Save"]);
    settings.setValue("/Shortcuts/File/SaveAs", mFileShortcuts["SaveAs"]);
    settings.setValue("/Shortcuts/File/Close", mFileShortcuts["Close"]);
    settings.setValue("/Shortcuts/File/Print", mFileShortcuts["Print"]);
    settings.setValue("/Shortcuts/File/Exit", mFileShortcuts["Exit"]);

    //write shortcuts for edit menu
    settings.setValue("/Shortcuts/Edit/Undo", mEditShortcuts["Undo"]);
    settings.setValue("/Shortcuts/Edit/Redo", mEditShortcuts["Redo"]);
    settings.setValue("/Shortcuts/Edit/Copy", mEditShortcuts["Copy"]);
    settings.setValue("/Shortcuts/Edit/Paste", mEditShortcuts["Paste"]);
    settings.setValue("/Shortcuts/Edit/Cut", mEditShortcuts["Cut"]);

    //write shortcuts for instruments menu
    settings.setValue("/Shortcuts/Instruments/Cursor", mInstrumentsShortcuts["Cursor"]);
    settings.setValue("/Shortcuts/Instruments/Lastic", mInstrumentsShortcuts["Lastic"]);
    settings.setValue("/Shortcuts/Instruments/Pipette", mInstrumentsShortcuts["Pipette"]);
    settings.setValue("/Shortcuts/Instruments/Loupe", mInstrumentsShortcuts["Loupe"]);
    settings.setValue("/Shortcuts/Instruments/Pen", mInstrumentsShortcuts["Pen"]);
    settings.setValue("/Shortcuts/Instruments/Line", mInstrumentsShortcuts["Line"]);
    settings.setValue("/Shortcuts/Instruments/Spray", mInstrumentsShortcuts["Spray"]);
    settings.setValue("/Shortcuts/Instruments/Fill", mInstrumentsShortcuts["Fill"]);
    settings.setValue("/Shortcuts/Instruments/Rect", mInstrumentsShortcuts["Rect"]);
    settings.setValue("/Shortcuts/Instruments/Ellipse", mInstrumentsShortcuts["Ellipse"]);

    //write shortcuts for tools menu
    settings.setValue("/Shortcuts/Tools/Zoom/ZoomIn", mToolsShortcuts["ZoomIn"]);
    settings.setValue("/Shortcuts/Tools/Zoom/ZoomOut", mToolsShortcuts["ZoomOut"]);
}
