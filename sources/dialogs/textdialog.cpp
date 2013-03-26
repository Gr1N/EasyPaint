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

#include "textdialog.h"
#include "../imagearea.h"
#include "../datasingleton.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFont>
#include <QFontDialog>
#include <QDialogButtonBox>
#include <QMessageBox>

TextDialog::TextDialog(ImageArea *parent) :
    QDialog(parent)
{
    initializeGui();
    layout()->setSizeConstraint(QLayout::SetFixedSize);
    setWindowTitle(tr("Text"));
}

void TextDialog::initializeGui()
{
    QPushButton *mFontButton = new QPushButton(tr("Select Font..."));
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok |
                                                       QDialogButtonBox::Cancel);
    connect(mFontButton, SIGNAL(clicked()), this, SLOT(selectFont()));
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(cancel()));
    QHBoxLayout *hBox = new QHBoxLayout();
    hBox->addWidget(mFontButton);
    hBox->addWidget(buttonBox);
    mTextEdit = new QTextEdit();
    mTextEdit->setLineWrapMode(QTextEdit::NoWrap);
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(mTextEdit);
    mainLayout->addLayout(hBox);
    setLayout(mainLayout);
    connect(mTextEdit, SIGNAL(textChanged()), this, SLOT(textChanged()));
}

void TextDialog::textChanged()
{
    emit textChanged(qobject_cast<ImageArea*>(this->parent()), mTextEdit->toPlainText());
}

void TextDialog::selectFont()
{
    bool ok;
    QFont font = DataSingleton::Instance()->getTextFont();
    font = QFontDialog::getFont(&ok, font, this);
    if (ok)
    {
        DataSingleton::Instance()->setTextFont(font);
        textChanged();
        mTextEdit->setFocus();
    }
}

void TextDialog::cancel()
{
    emit canceled(qobject_cast<ImageArea*>(this->parent()));
    QDialog::reject();
}

void TextDialog::reject() 
{
    if (mTextEdit->toPlainText().isEmpty() ||
        QMessageBox::question(this, tr("Question"), tr("Clear text?"),
                              QMessageBox::Yes | QMessageBox::No,
                              QMessageBox::No) == QMessageBox::Yes)
    {
        emit canceled(qobject_cast<ImageArea*>(this->parent()));
    }
    QDialog::reject();
}
