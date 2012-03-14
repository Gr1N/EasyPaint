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

#ifndef DATASINGLETON_H
#define DATASINGLETON_H

#include <QtGui/QColor>
#include <QtCore/QSize>
#include <QtCore/QString>
#include <QtCore/QMap>

#include "easypaintenums.h"

/**
 * @brief Singleton for variables needed for the program.
 *
 */
class DataSingleton
{
public:
    /**
     * @brief Instance of singleton (static)
     *
     * @return DataSingleton Pointer of singleton
     */
    static DataSingleton* Instance();

    inline QColor getFirstColor() { return mFirstColor; }
    inline void setFirstColor(const QColor &color) { mFirstColor = color; }
    inline QColor getSecondColor() { return mSecondColor; }
    inline void setSecondColor(const QColor &color) { mSecondColor = color; }
    inline int getPenSize() { return mPenSize; }
    inline void setPenSize(const int &size) { mPenSize = size; }
    inline InstrumentsEnum getInstrument() { return mCurrentInstrument; }
    inline void setInstrument(const InstrumentsEnum &instrument) { mCurrentInstrument = instrument; }
    inline InstrumentsEnum getPreviousInstrument() { return mPreviousInstrument; }
    inline void setPreviousInstrument(const InstrumentsEnum &instrument) { mPreviousInstrument = instrument; }
    inline QSize getBaseSize() { return mBaseSize; }
    inline void setBaseSize(const QSize &baseSize) { mBaseSize = baseSize; }
    inline bool getIsAutoSave() { return mIsAutoSave; }
    inline void setIsAutoSave(const bool &isAutoSave) { mIsAutoSave = isAutoSave; }
    inline int getAutoSaveInterval() { return mAutoSaveInterval; }
    inline void setAutoSaveInterval(const int &interval) { mAutoSaveInterval = interval; }
    inline int getHistoryDepth() { return mHistoryDepth; }
    inline void setHistoryDepth(const int &historyDepth) { mHistoryDepth = historyDepth; }
    inline QString getAppLanguage() { return mAppLanguage; }
    inline void setAppLanguage(const QString &appLanguage) { mAppLanguage = appLanguage; }
    inline QMap<QString, QString> getFileShortcuts() { return mFileShortcuts; }
    inline QString getFileShortcutByKey(const QString &key) { return mFileShortcuts[key]; }
    inline void setFileShortcutByKey(const QString &key, const QString &value) { mFileShortcuts[key] = value; }
    inline QMap<QString, QString> getEditShortcuts() { return mEditShortcuts; }
    inline QString getEditShortcutByKey(const QString &key) { return mEditShortcuts[key]; }
    inline void setEditShortcutByKey(const QString &key, const QString &value) { mEditShortcuts[key] = value; }
    inline QMap<QString, QString> getInstrumentsShortcuts() { return mInstrumentsShortcuts; }
    inline QString getInstrumentShortcutByKey(const QString &key) { return mInstrumentsShortcuts[key]; }
    inline void setInstrumentShortcutByKey(const QString &key, const QString &value) { mInstrumentsShortcuts[key] = value; }

    void readSetting();
    void writeSettings();

private:
    DataSingleton();
    DataSingleton(DataSingleton const&){}

    static DataSingleton* m_pInstance;
    QColor mFirstColor,
           mSecondColor;
    int mPenSize;
    InstrumentsEnum mCurrentInstrument, mPreviousInstrument;
    QSize mBaseSize;
    bool mIsAutoSave;
    int mAutoSaveInterval, mHistoryDepth;
    QString mAppLanguage;
    QMap<QString, QString> mFileShortcuts, mEditShortcuts, mInstrumentsShortcuts, mToolsShortcuts;

};

#endif // DATASINGLETON_H
