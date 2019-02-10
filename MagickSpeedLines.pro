TARGET=MagickSpeedLines
OBJECTS_DIR=obj
MOC_DIR=moc
SOURCES+=$$PWD/src/*.cpp
HEADERS+=$$PWD/include/*.h
INCLUDEPATH+= /usr/include/ImageMagick-6 \
                /usr/include/boost \
                $$PWD/include
LIBS+= -L /usr/lib64/ -lMagick++-6.Q16 \
        -L /usr/lib64/ -lboost_filesystem \
        -L /usr/lib64/ -lboost_system \
