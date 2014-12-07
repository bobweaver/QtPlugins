## assign a template
TEMPLATE = subdirs
CONFIG   += ordered
## add the subdirs for all the projects
SUBDIRS += \
        Mango/Ssh/QSsh/qssh.pro \
	Mango \
        Mango/Ssh 

OTHER_FILES += \
README.md





##for docs
include(doc/docs.pri)
