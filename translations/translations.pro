### eqmake4 was here ###
CONFIG -= debug_and_release debug
CONFIG += release

LANGUAGES =  # We only create engineering English in the application package
CATALOGNAME = libwifiapplet
SOURCEDIR = ..//libwifiapplet
TRANSLATIONDIR = $$PWD
include($$[QT_INSTALL_DATA]/mkspecs/features/meegotouch_defines.prf)
include($$[QT_INSTALL_DATA]/mkspecs/features/meegotouch_translations.prf)
