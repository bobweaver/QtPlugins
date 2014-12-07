/*
 * Copyright (C) 2014 Joseph Mills.
 *
 */
#include "randompassword.h"
RandomPassword::RandomPassword(QObject *parent) :
    QObject(parent),
    i_number(10)
{
}

QString RandomPassword::getRandomPassword()
{
    return m_pass;
}

int RandomPassword::numberOfCharecters()
{
    return i_number;
}

void RandomPassword::setNumberOfCharecters(const int &numberOfCharecters)
{
   i_number = numberOfCharecters;
}

QString RandomPassword::generateRandomPassword()
{
   const QString possibleCharacters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
   const int randomStringLength = i_number;

   QString rString;
   for(int i=0; i<randomStringLength; ++i)
   {
       int index = qrand() % possibleCharacters.length();
       QChar nextChar = possibleCharacters.at(index);
       rString.append(nextChar);
   }
   m_pass = rString;
   qDebug() << rString;
   return m_pass;
}
