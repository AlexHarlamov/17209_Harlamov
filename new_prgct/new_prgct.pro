#-------------------------------------------------
#
# Project created by QtCreator 2019-01-23T09:33:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = new_prgct
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    ../lab2/CommandList/Command.cpp \
    ../lab2/CommandList/PrimitiveInstructions.cpp \
    ../lab2/Arguments.cpp \
    ../lab2/CmFactory.cpp \
    ../lab2/Field.cpp \
    ../lab2/HgInstruction.cpp \
    ../lab2/InstrPointer.cpp \
    ../lab2/ListOfWarriors.cpp \
    ../lab2/Warrior.cpp \
    dialog.cpp \
    fieldwidget.cpp

HEADERS += \
        mainwindow.h \
    ../lab2/CommandList/Command.h \
    ../lab2/CommandList/DAT.h \
    ../lab2/CommandList/JMP.h \
    ../lab2/CommandList/MOV.h \
    ../lab2/CommandList/NOP.h \
    ../lab2/CommandList/PrimitiveInstructions.h \
    ../lab2/CommandList/SEQ.h \
    ../lab2/CommandList/SLT.h \
    ../lab2/CommandList/SNE.h \
    ../lab2/CommandList/SPL.h \
    ../lab2/Arguments.h \
    ../lab2/CmFactory.h \
    ../lab2/Field.h \
    ../lab2/HgInstruction.h \
    ../lab2/Includes.h \
    ../lab2/InstrPointer.h \
    ../lab2/ListOfWarriors.h \
    ../lab2/Warrior.h \
    dialog.h \
    fieldwidget.h

FORMS += \
        mainwindow.ui \
    dialog.ui

DISTFILES += \
    ../lab2/WarriorList/w1.txt \
    ../lab2/WarriorList/w2.txt \
    ../lab2/WarriorList/w3.txt
