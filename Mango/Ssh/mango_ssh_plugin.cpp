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
#include "mango_ssh_plugin.h"
#include <qqml.h>
#include "sftpupload.h"
#include "mangosshremoteprocess.h"
#include "generatekeys.h"
#include "remotefilemodel.h"

void MangoSshPlugin::registerTypes(const char *uri)
{
    // @uri Mango.Ssh
   qmlRegisterType<SftpUpload>(uri,0,1,"SftpUpload");
   qmlRegisterType<MangoSshRemoteProcess>(uri,0,1,"MangoSshRemoteProcess");
   qmlRegisterType<GenerateKeys>(uri,0,1,"GenerateKeys");
   qmlRegisterType<RemoteFileModel>(uri,0,1,"RemoteFileModel");
}

// singleton instance tyes

