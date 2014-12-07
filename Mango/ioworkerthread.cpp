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
#include "ioworkerthread.h"


/*!
  Hosts a thread, lives on the main thread.

  Responsible for relaying interaction between the main thread and an IOWorkerThread.
 */
IOWorkerThread::IOWorkerThread(QObject *parent) :
    QObject(parent)
{
    mWorker.start(QThread::IdlePriority);
}

/*!
  Destroys an IOWorkerThread instance.
 */
IOWorkerThread::~IOWorkerThread()
{
    mWorker.exit();
    mWorker.wait();
}

/*!
  Attempts an asynchronous attempt to start a \a request.

  If the request may be run, it is queued, and true is returned, otherwise, false.
 */
bool IOWorkerThread::addRequest(IORequest *request)
{
    mWorker.addRequest(request);
    return true;
}
