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

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QComboBox;
class QSpinBox;
class QCheckBox;
class QLineEdit;
class QTreeWidget;
class QTreeWidgetItem;
class QPushButton;
class QKeySequence;
QT_END_NAMESPACE

class ShortcutEdit;

/**
 * @brief Dialog for changing application settings.
 *
 */
class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

    /**
     * @brief Get all settings from form and send it to data singleton.
     *
     */
    void sendSettingsToSingleton();

private:
    void initializeGui();
    int getLanguageIndex();
    /**
     * @brief Create top level item in tree widget and create children items with shortcuts.
     *
     * @param name Top level item name.
     * @param QMap<QString, QString> Map with all shortcuts for this group.
     */
    void createItemsGroup(const QString &name, const QMap<QString, QKeySequence> &shortcuts);

    QComboBox *mLanguageBox;
    QSpinBox *mWidth, *mHeight, *mHistoryDepth, *mAutoSaveInterval;
    QCheckBox *mIsAutoSave;
    QCheckBox *mIsRestoreWindowSize;
    ShortcutEdit *mShortcutEdit;
    QTreeWidget *mShortcutsTree;
    
signals:
    
private slots:
    void itemSelectionChanged();
    void textChanged(const QString &text);
    void reset();
    
};

#endif // SETTINGSDIALOG_H
