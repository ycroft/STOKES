# environment setting:
vpath %cpp ../UnitTest
vpath %cpp ../Universal
vpath %cpp ../DataCollection
vpath %cpp ../DataProcessing
vpath %cpp ../UI
vpath %h ../UnitTest
vpath %h ../include/Universal
vpath %h ../include/DataCollection
vpath %h ../include/DataProcessing
vpath %h ../include/UI
CC=g++
DEST=../bin/TestSuite/
INCPATH=-I../include/ -I/usr/include/qt4 -I/usr/include/qwt\
-I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui
