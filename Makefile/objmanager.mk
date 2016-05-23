# var:
PROG_NAME=UT_OBJMANAGER
include env.mk
LIBS=-L/usr/lib/x86_64-linux-gnu/ -lboost_thread -lboost_system -lQtCore
PROG_PATH=$(DEST)$(PROG_NAME)
OBJ=ut_objmanager.o objmanager.o innerdata.o complex.o math.o\
spectrograph.o processor.o
# compile:
$(PROG_PATH): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LIBS)
ut_objmanager.o: ut_objmanager.cpp testsuite.h objmanager.h
	$(CC) -c $< $(INCPATH)
objmanager.o: objmanager.cpp objmanager.h processor.h
	$(CC) -c $< $(INCPATH)
spectrograph.o: spectrograph.cpp spectrograph.h
	$(CC) -c $< $(INCPATH)
innerdata.o: innerdata.cpp innerdata.h
	$(CC) -c $< $(INCPATH)
complex.o: complex.cpp complex.h
	$(CC) -c $< $(INCPATH)
math.o: math.cpp math.h complex.h
	$(CC) -c $< $(INCPATH)
processor.o: processor.cpp processor.h
	$(CC) -c $< $(INCPATH)
.PHONY: clean
clean:
	-rm ./*.o