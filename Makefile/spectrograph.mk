# var:
PROG_NAME=UT_SPECTROGRAPH
include env.mk
LIBS=
PROG_PATH=$(DEST)$(PROG_NAME)
OBJ=ut_spectrograph.o spectrograph.o innerdata.o complex.o math.o
# compile:
$(PROG_PATH): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LIBS)
ut_spectrograph.o: ut_spectrograph.cpp testsuite.h spectrograph.h
	$(CC) -c $< $(INCPATH)
spectrograph.o: spectrograph.cpp spectrograph.h
	$(CC) -c $< $(INCPATH)
innerdata.o: innerdata.cpp innerdata.h
	$(CC) -c $< $(INCPATH)
complex.o: complex.cpp complex.h
	$(CC) -c $< $(INCPATH)
math.o: math.cpp math.h complex.h
	$(CC) -c $< $(INCPATH)
.PHONY: clean
clean:
	-rm ./*.o