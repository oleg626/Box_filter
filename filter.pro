TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.c \
    stb_image.c \
    blur.c

HEADERS += \
    stb.h \
    stb_image.h \
    stb_image_write.h \
    blur.h
