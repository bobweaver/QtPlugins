## This is a Alpha Software that is under **HEAVEY DEVELOPMENT**

## Deps for compiling
## Linux

## Building
## Deps for compiling

### debian 

```bash
sudo apt-get install libavahi-compat-libdnssd-dev libbotan1.10-dev mysql-client-5.5 libmysqlclient-dev libmodbus-dev asciidoc autoconf automake autotools-dev dh-autoreconf libtool xmlto xsltproc libcurl
```
### Qml Plugins and Tools Application
```bash
mkdir build
cd build
qmake ../qmlplugins.pro
make
make install
cd ../
rm -r build
```
### Documentation for the plugins

```bash
mkdir build
cd build
qmake ../qmlplugins.pro
make docs
make install
cd ../
```

## Depedencys
***
### QT
Qt 5.X should be installed This code has not yet been tested against < qt5
check with your distro on this.
Or build it yourself or get the online installer.  If you are building yourself and or using the online installer
libavahi-compat-libdnssd-dev

### Botan
This is used for the Qml ssh plugins and the ssh lib's also

multiplatform crypto library (development)

Botan is a C++ library which provides support for many common cryptographic operations,
including encryption,
authentication,
and X.509v3 certificates and CRLs.
A wide variety of algorithms is supported, including RSA, DSA, DES, AES, MD5, and SHA-1.

This package contains the development files.

package: libbotan1.10-dev

### Avahi
Used for the qmlplugin from creating scanning and alot that has to do with bonjour/avahi/zeroconf

Development headers for the Avahi Apple Bonjour compatibility library

Avahi is a fully LGPL framework for Multicast DNS Service Discovery.
It allows programs to publish and discover services and hosts running on a local network with no specific configuration.
For example you can plug into a network and instantly find printers to print to, files to look at and people to talk to.

This package contains the development headers for Apple Bonjour compatibility library of Avahi.

package: libavahi-compat-libdnssd-dev 

### Mysql Api
You must also build the plugin for mysql database,
So that one can alter tables and coloumns and Rows.

The lugins that are used include
sqlQuery and sqlQueryModel 

```bash
cd <Qt Path to Src>/qtbase/src/plugins/sqldrivers/mysql/

## This may be different for you.  the include path is the header files from libmysqlclient-dev The Libs is the linked so file that comes with the mysql-client-5.5
## These are needed in order to compile the mysql driver for qt. Feel free to compile the other drivers that are also in the dir 

qmake "INCLUDE_PATH=/usr/include/mysql/" "LIBS+=-L/usr/lib/x86_64-linux-gnu/libmysqlclient_r.so"  mysql.pro
make
make install
```

package: mysql-client-5.5 libmysqlclient-dev

### modbus
This is for expermentall use of modbus.  This binding is under **HEAVEY DEVELOPMENT**.
Header file needed is
modbus/modbus.h
modbus-version.h

packages: libmodbus-dev asciidoc autoconf automake autotools-dev dh-autoreconf libtool xmlto xsltproc


### cUrl 
This is a binding for cUrl. This is under **HEAVEY DEVELOPMENT**.
The header that is needed is curl/curl.h

package: libcurl4-gnutls-dev 

## Windows
coming soon

## Mac
coming soon
