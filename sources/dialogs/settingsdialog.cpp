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

#include "settingsdialog.h"
#include "../datasingleton.h"
#include "../widgets/shortcutedit.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QTabWidget>
#include <QDialogButtonBox>
#include <QLabel>
#include <QComboBox>
#include <QGroupBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QTreeWidget>
#include <QLineEdit>
#include <QPushButton>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent)
{
    initializeGui();
    layout()->setSizeConstraint(QLayout::SetFixedSize);
    setWindowTitle(tr("Settings"));
}

SettingsDialog::~SettingsDialog()
{

}

void SettingsDialog::initializeGui()
{
    QTabWidget *tabWidget = new QTabWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok |
                                                       QDialogButtonBox::Cancel);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    QLabel *label1 = new QLabel(tr("Language:"));
    mLanguageBox = new QComboBox();
    mLanguageBox->addItem(tr("<System>"));
    mLanguageBox->addItem("English");
    mLanguageBox->addItem("Czech");
    mLanguageBox->addItem("French");
    mLanguageBox->addItem("Russian");
    mLanguageBox->setCurrentIndex(getLanguageIndex());
    QHBoxLayout *hBox1 = new QHBoxLayout();
    hBox1->addWidget(label1);
    hBox1->addWidget(mLanguageBox);
    QVBoxLayout *vBox1 = new QVBoxLayout();
    vBox1->addLayout(hBox1);
    QLabel *label4 = new QLabel(tr("Note: language changing requires application restart"));
    vBox1->addWidget(label4);
    mIsRestoreWindowSize = new QCheckBox(tr("Restore window size on start"));
    mIsRestoreWindowSize->setChecked(DataSingleton::Instance()->getIsRestoreWindowSize());
    vBox1->addWidget(mIsRestoreWindowSize);

    QGroupBox *groupBox1 = new QGroupBox(tr("User interface"));
    groupBox1->setLayout(vBox1);

    QLabel *label2 = new QLabel(tr("Base size:"));
    QLabel *label3 = new QLabel(" x ");
    mWidth = new QSpinBox();
    mWidth->setRange(1, 9999);
    mWidth->setValue(DataSingleton::Instance()->getBaseSize().width());
    mHeight = new QSpinBox();
    mHeight->setRange(1, 9999);
    mHeight->setValue(DataSingleton::Instance()->getBaseSize().height());
    QHBoxLayout *hBox2 = new QHBoxLayout();
    hBox2->addWidget(mWidth);
    hBox2->addWidget(label3);
    hBox2->addWidget(mHeight);

    QLabel *label5 = new QLabel(tr("History depth:"));
    mHistoryDepth = new QSpinBox();
    mHistoryDepth->setRange(1, 99);
    mHistoryDepth->setValue(DataSingleton::Instance()->getHistoryDepth());
    mHistoryDepth->setFixedWidth(80);

    mIsAutoSave = new QCheckBox(tr("Autosave"));
    mIsAutoSave->setChecked(DataSingleton::Instance()->getIsAutoSave());
    QLabel *label6 = new QLabel(tr("Autosave interval (sec):"));
    mAutoSaveInterval = new QSpinBox();
    mAutoSaveInterval->setRange(1, 3000);
    mAutoSaveInterval->setValue(DataSingleton::Instance()->getAutoSaveInterval());
    mAutoSaveInterval->setFixedWidth(80);

    QGridLayout *gLayout = new QGridLayout();
    gLayout->addWidget(label2, 0, 0);
    gLayout->addLayout(hBox2, 0, 1);
    gLayout->addWidget(label5, 1, 0);
    gLayout->addWidget(mHistoryDepth, 1, 1);
    gLayout->addWidget(mIsAutoSave, 2, 0);
    gLayout->addWidget(label6, 3, 0);
    gLayout->addWidget(mAutoSaveInterval, 3, 1);

    QGroupBox *groupBox2 = new QGroupBox(tr("Image"));
    groupBox2->setLayout(gLayout);

    QVBoxLayout *vBox2 = new QVBoxLayout();
    vBox2->addWidget(groupBox1);
    vBox2->addWidget(groupBox2);

    QWidget *firstTabWidget = new QWidget();
    firstTabWidget->setLayout(vBox2);

    tabWidget->addTab(firstTabWidget, tr("General"));

    QGroupBox *groupBox3 = new QGroupBox(tr("Keyboard shortcuts"));
    QVBoxLayout *vBox3 = new QVBoxLayout();
    groupBox3->setLayout(vBox3);

    mShortcutsTree = new QTreeWidget();
    QStringList header;
    header<<tr("Command")<<tr("Shortcut");
    mShortcutsTree->setHeaderLabels(header);
    connect(mShortcutsTree, SIGNAL(itemSelectionChanged()),
            this, SLOT(itemSelectionChanged()));

    createItemsGroup("File", DataSingleton::Instance()->getFileShortcuts());
    createItemsGroup("Edit", DataSingleton::Instance()->getEditShortcuts());
    createItemsGroup("Instruments", DataSingleton::Instance()->getInstrumentsShortcuts());
    createItemsGroup("Tools", DataSingleton::Instance()->getToolsShortcuts());

    vBox3->addWidget(mShortcutsTree);

    QGroupBox *groupBox4 = new QGroupBox(tr("Shortcut"));
    QHBoxLayout *hBox5 = new QHBoxLayout();
    groupBox4->setLayout(hBox5);

    QLabel *label7 = new QLabel(tr("Key sequence:"));
    mShortcutEdit = new ShortcutEdit();
    mShortcutEdit->setEnabled(false);
    connect(mShortcutEdit, SIGNAL(textChanged(QString)), this, SLOT(textChanged(QString)));
    hBox5->addWidget(label7);
    hBox5->addWidget(mShortcutEdit);

    QVBoxLayout *vBox5 = new QVBoxLayout();
    vBox5->addWidget(groupBox3);
    vBox5->addWidget(groupBox4);

    QWidget *secondTabWidget = new QWidget();
    secondTabWidget->setLayout(vBox5);

    tabWidget->addTab(secondTabWidget, tr("Keyboard"));
}

int SettingsDialog::getLanguageIndex()
{
    QStringList languages;
    languages<<"system"<<"easypaint_en_EN"<<"easypaint_cs_CZ"<<"easypaint_fr_FR"<<"easypaint_ru_RU";
    return languages.indexOf(DataSingleton::Instance()->getAppLanguage());
}

void SettingsDialog::sendSettingsToSingleton()
{
    DataSingleton::Instance()->setBaseSize(QSize(mWidth->value(), mHeight->value()));
    DataSingleton::Instance()->setHistoryDepth(mHistoryDepth->value());
    DataSingleton::Instance()->setIsAutoSave(mIsAutoSave->isChecked());
    DataSingleton::Instance()->setIsRestoreWindowSize(mIsRestoreWindowSize->isChecked());
    DataSingleton::Instance()->setAutoSaveInterval(mAutoSaveInterval->value());

    QStringList languages;
    languages<<"system"<<"easypaint_en_EN"<<"easypaint_cs_CZ"<<"easypaint_fr_FR"<<"easypaint_ru_RU";
    DataSingleton::Instance()->setAppLanguage(languages.at(mLanguageBox->currentIndex()));

    QTreeWidgetItem *item;
    for(int i(0); i < mShortcutsTree->topLevelItemCount(); i++)
    {
        item = mShortcutsTree->topLevelItem(i);
        for(int y(0); y < item->childCount(); y++)
        {
            if(item->text(0) == "File")
            {
                DataSingleton::Instance()->setFileShortcutByKey(item->child(y)->text(0),
                                                                item->child(y)->data(1, Qt::DisplayRole).value<QKeySequence>());
            }
            else if(item->text(0) == "Edit")
            {
                DataSingleton::Instance()->setEditShortcutByKey(item->child(y)->text(0),
                                                                item->child(y)->data(1, Qt::DisplayRole).value<QKeySequence>());
            }
            else if(item->text(0) == "Instruments")
            {
                DataSingleton::Instance()->setInstrumentShortcutByKey(item->child(y)->text(0),
                                                                item->child(y)->data(1, Qt::DisplayRole).value<QKeySequence>());
            }
            else if(item->text(0) == "Tools")
            {
                DataSingleton::Instance()->setToolShortcutByKey(item->child(y)->text(0),
                                                                item->child(y)->data(1, Qt::DisplayRole).value<QKeySequence>());
            }
        }
    }
}

void SettingsDialog::createItemsGroup(const QString &name, const QMap<QString, QKeySequence> &shortcuts)
{
    QTreeWidgetItem *topLevel = new QTreeWidgetItem(mShortcutsTree);
    mShortcutsTree->addTopLevelItem(topLevel);
    topLevel->setText(0, name);
    topLevel->setExpanded(true);
    QMapIterator<QString, QKeySequence> iterator(shortcuts);
    while(iterator.hasNext())
    {
        iterator.next();
        QTreeWidgetItem *subLevel = new QTreeWidgetItem(topLevel);
        subLevel->setText(0, iterator.key());
        subLevel->setData(1, Qt::DisplayRole, iterator.value());
    }
}

void SettingsDialog::itemSelectionChanged()
{
    if(mShortcutsTree->selectedItems().at(0)->childCount() != 0)
    {
        mShortcutEdit->setEnabled(false);
        mShortcutEdit->clear();
    }
    else
    {
        mShortcutEdit->setEnabled(true);
        mShortcutEdit->setText(mShortcutsTree->selectedItems().at(0)->text(1));
    }
    mShortcutEdit->setFocus();
}

void SettingsDialog::textChanged(const QString &text)
{
    mShortcutsTree->selectedItems().at(0)->setData(1, Qt::DisplayRole, text);
}

void SettingsDialog::reset()
{
    mShortcutEdit->clear();
}
