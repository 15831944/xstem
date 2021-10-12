
unix {
    macx {
        INSTALLDIR = ../../
    } else {
        INSTALLDIR = ../../unix
    }
}

win32 {
    INSTALLDIR = ../../windows
}

RESOURCES += \
    $$PWD/librecad/res/digitalcontrol/digitalcontrol.qrc \
    $$PWD/librecad/res/draw/draw.qrc

