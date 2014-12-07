/*
 * Copyright (C) 2014 Joseph Mills.
 *
 */
#ifndef MANGO_H
#define MANGO_H

#include <QQuickItem>

class Mango : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(Mango)

public:
    Mango(QQuickItem *parent = 0);
    ~Mango();
};

#endif // MANGO_H

