TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c

LIBS += -L$$PWD\\conio2 -llibconio
LIBS += -L$$PWD\\curl -lurl_fopen -llibcurl -llibcurldll -llibws2_32

