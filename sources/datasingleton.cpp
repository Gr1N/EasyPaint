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
    mFirstColor = Qt::black;
    mSecondColor = Qt::white;
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
    mBaseSize = settings.value("/BaseSize", QSize(400, 300)).toSize();
    mIsAutoSave = settings.value("/IsAutoSave", false).toBool();
    mAutoSaveInterval = settings.value("/AutoSaveInterval", 300000).toInt();
    mHistoryDepth = settings.value("/HistoryDepth", 40).toInt();
    mAppLanguage = settings.value("/AppLanguage", "system").toString();

    //read shortcuts for file menu
    mFileShortcuts.insert("New", settings.value("/Shortcuts/File/New", "Ctrl+N").toString());
    mFileShortcuts.insert("Open", settings.value("/Shortcuts/File/Open", "Ctrl+O").toString());
}

void DataSingleton::writeSettings()
{
    QSettings settings;
    settings.setValue("/BaseSize", mBaseSize);
    settings.setValue("/IsAutoSave", mIsAutoSave);
    settings.setValue("/AutoSaveInterval", mAutoSaveInterval);
    settings.setValue("/HistoryDepth", mHistoryDepth);
    settings.setValue("/AppLanguage", mAppLanguage);
}
