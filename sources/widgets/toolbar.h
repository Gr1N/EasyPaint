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

#ifndef TOOLBAR_H
#define TOOLBAR_H

#include "../easypaintenums.h"

#include <QtGui/QToolBar>

QT_BEGIN_NAMESPACE
class QToolButton;
class ColorChooser;
QT_END_NAMESPACE

/**
 * @brief Toolbar with instrumets buttons, color choosers and etc.
 *
 */
class ToolBar : public QToolBar
{
    Q_OBJECT

public:
    explicit ToolBar(QWidget *parent = 0);

private:
    /**
     * @brief Initialize all buttons, color choosers and etc.
     *
     */
    void initializeItems();
    void setAllButtonsUnchecked(QToolButton *button);
    /**
     * @brief Create new QToolButton
     *
     * @param name Name of button
     * @param iconPath Path to button icon.
     * @return QToolButton Created QToolButton.
     */
    QToolButton* createToolButton(const QString &name, const QString &iconPath);

    QToolButton *mCursorButton, *mEraserButton, *mPenButton, *mLineButton,
                *mColorPickerButton, *mMagnifierButton, *mSprayButton, *mFillButton,
                *mRectangleButton, *mEllipseButton;
    ColorChooser *mPColorChooser, *mSColorChooser;
    bool mPrevInstrumentSetted;
    
signals:
    void sendInstrumentChecked(InstrumentsEnum);
    void sendClearStatusBarColor();
    void sendClearImageSelection();

public slots:
    void setPrimaryColorView();
    void setSecondaryColorView();
    void setInstrumentChecked(InstrumentsEnum instrument);
    void restorePreviousInstrument();
    
private slots:
    void penValueChanged(const int &value);
    void primaryColorChanged(const QColor &color);
    void secondaryColorChanged(const QColor &color);
    void setCursor(const bool &state);
    void setLastic(const bool &state);
    void setPen(const bool &state);
    void setLine(const bool &state);
    void setPipette(const bool &state);
    void setLoupe(const bool &state);
    void setSpray(const bool &state);
    void setFill(const bool &state);
    void setRect(const bool &state);
    void setEllipse(const bool &state);

protected:
    void contextMenuEvent(QContextMenuEvent *);
    
};

#endif // TOOLBAR_H
