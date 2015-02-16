/******************************************************************************
* Copyright (c) 2012 Jørgen Lind
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
******************************************************************************/

#ifndef TERMINALITEM_H
#define TERMINALITEM_H

#include <QtCore/QObject>
#include <QtQuick/QQuickItem>
#include <QInputMethodEvent>
#include <QKeyEvent>

#include "screen.h"

class TerminalScreen : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(Screen *screen READ screen CONSTANT)
public:
    TerminalScreen(QQuickItem *parent = 0);
    ~TerminalScreen();

    Screen *screen() const;

    QVariant inputMethodQuery(Qt::InputMethodQuery query) const;

public slots:
    void hangupReceived();
signals:
    void aboutToBeDestroyed(TerminalScreen *screen);

protected:
    void inputMethodEvent(QInputMethodEvent *event);

private:
    Screen *m_screen;
};

#endif // TERMINALITEM_H
