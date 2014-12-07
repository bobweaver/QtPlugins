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
#include <QMutexLocker>
#include <QDebug>

#include "iorequestworker.h"
#include "iorequest.h"

/*!
  Lives on an IOWorkerThread.

  Responsible for running IORequest jobs on the thread instance, and
  disposing of their resources once they are done.
 */
IORequestWorker::IORequestWorker()
    : QThread()
    , mTimeToQuit(false)
{
}

void IORequestWorker::addRequest(IORequest *request)
{
    request->moveToThread(this);

    // TODO: queue requests so we run the most important one first
    QMutexLocker lock(&mMutex);
    mRequests.append(request);

    // wake run()
    mWaitCondition.wakeOne();
}

void IORequestWorker::run()
{
    forever {
        QMutexLocker lock(&mMutex);

        if (mTimeToQuit)
            return;

        if (mRequests.empty())
            mWaitCondition.wait(&mMutex);

        while (!mRequests.isEmpty()) {
            IORequest *request = mRequests.takeFirst();

            lock.unlock();

            request->run();
            request->deleteLater();

            lock.relock();
        }
    }
}

void IORequestWorker::exit()
{
    qDebug() << Q_FUNC_INFO << "Quitting";
    QMutexLocker lock(&mMutex);
    mTimeToQuit = true;
    mWaitCondition.wakeOne();
}
