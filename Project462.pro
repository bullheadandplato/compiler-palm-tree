#-------------------------------------------------
#
# Project created by QtCreator 2016-12-19T14:32:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Project462
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    codeeditor.cpp \
    syntaxhighlighter.cpp \
    LexicalAnalyzer/Base.cpp \
    LexicalAnalyzer/LexAn.cpp \
    Parser/TableStack.cpp \
    Parser/Parser.cpp


HEADERS  += mainwindow.h \
    codeeditor.h \
    syntaxhighlighter.h \
    LexicalAnalyzer/Base.h \
    LexicalAnalyzer/LexAn.h \
    Parser/TableStack.h \
    Parser/Parser.h

FORMS    += mainwindow.ui

DISTFILES += \
    Parser/output.txt \
    Parser/product.txt \
    README.md
