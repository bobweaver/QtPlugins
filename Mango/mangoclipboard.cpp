/*
 * Copyright 2014 Joseph Mills.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Joseph Mills  <josephjamesmills@gmail.com>
 */
#include "mangoclipboard.h"
/*!
  \qmltype MangoClipboard
  \inqmlmodule Mango 0.1
  \ingroup Mango
  \inherits Item
  \since 5.3
   The MangoClipboard Qml Plugin provides access to the window system clipboard.

The clipboard offers a simple mechanism to copy and paste data between applications.

MangoClipboard Qml Plugin supports the same data types that QDrag does, and uses similar mechanisms. For advanced clipboard usage read Drag and Drop.
 */
/*!
  \qmlproperty strin MangoClipboard::text
  The Text that one would like to send to the clipboard
*/
