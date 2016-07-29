# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = FirstTry

CONFIG += sailfishapp

db.files = db/
db.path = /usr/share/$${TARGET}/
INSTALLS += db

SOURCES += src/FirstTry.cpp \
    src/qmlhandler.cpp \
    src/searchhint.cpp \
    src/sqltoqml.cpp \
    src/PosRequest.cpp \
    src/NearestZoneFinder.cpp

OTHER_FILES += qml/FirstTry.qml \
    qml/cover/CoverPage.qml \
    qml/pages/FirstPage.qml \
    qml/pages/ThreadsPage.qml \
    qml/pages/ZonePage.qml \
    qml/pages/Util.js \
    rpm/FirstTry.changes.in \
    rpm/FirstTry.spec \
    rpm/FirstTry.yaml \
    translations/*.ts \
    FirstTry.desktop

SAILFISHAPP_ICONS = 86x86 108x108 128x128 256x256

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n

# German translation is enabled as an example. If you aren't
# planning to localize your app, remember to comment out the
# following TRANSLATIONS line. And also do not forget to
# modify the localized app name in the the .desktop file.
TRANSLATIONS += translations/FirstTry-de.ts

HEADERS += \
    src/qmlhandler.h \
    src/searchhint.h \
    src/sqltoqml.h \
    src/PosRequest.h \
    src/NearestZoneFinder.h

DISTFILES += \
    qml/views/SearchBox.qml \
    qml/pages/ThreadsPage.qml \
    qml/pages/ThreadInfo.qml \
    qml/cover/CryptoCover.qml

QT+= sql positioning
