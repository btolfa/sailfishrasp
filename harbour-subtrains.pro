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
TARGET = harbour-subtrains

CONFIG += sailfishapp

db.files = db/
db.path = /usr/share/$${TARGET}/
INSTALLS += db

SOURCES += \
    src/QmlHandler.cpp \
    src/NearestZoneFinder.cpp \
    src/harbour-subtrains.cpp \
    src/OurResource.cpp \
    src/Positioning.cpp \
    src/ValuePair.cpp \
    src/SearchHint.cpp

OTHER_FILES += \
    qml/cover/CoverPage.qml \
    qml/pages/FirstPage.qml \
    qml/pages/ThreadsPage.qml \
    qml/pages/ZonePage.qml \
    qml/pages/Util.js \
    rpm/harbour-subtrains.changes.in \
    rpm/harbour-subtrains.spec \
    rpm/harbour-subtrains.yaml \
    translations/*.ts

SAILFISHAPP_ICONS = 86x86 108x108 128x128 256x256

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n

# German translation is enabled as an example. If you aren't
# planning to localize your app, remember to comment out the
# following TRANSLATIONS line. And also do not forget to
# modify the localized app name in the the .desktop file.
TRANSLATIONS += translations/harbour-subtrains.ts

HEADERS += \
    src/QmlHandler.h \
    src/NearestZoneFinder.h \
    src/OurResource.h \
    src/Positioning.h \
    src/ValuePair.h \
    src/SearchHint.h \

DISTFILES += \
    qml/views/SearchBox.qml \
    qml/pages/ThreadsPage.qml \
    qml/pages/ThreadInfo.qml \
    qml/cover/CryptoCover.qml \
    qml/pages/line-bot.svg \
    qml/pages/line-med.svg \
    qml/pages/line-top.svg \
    qml/pages/line-grey.svg \
    qml/harbour-subtrains.qml \
    harbour-subtrains.desktop

QT+= sql positioning
