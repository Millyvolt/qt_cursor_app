QT += core widgets

CONFIG += c++17

TARGET = QtTwoButtonsApp
TEMPLATE = app

SOURCES += main.cpp

# Copy styles.qss to output directory
styles.files = styles.qss
styles.path = $$OUT_PWD
INSTALLS += styles

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
