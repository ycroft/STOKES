PROG_NAME=UT_MATH
include env.mk
PROG_PATH=$(DEST)$(PROG_NAME)
OBJ=ut_math.o math.o complex.o
# compile:
$(PROG_PATH): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LIBS)
ut_math.o: ut_math.cpp testsuite.h math.h
	$(CC) -c $< $(INCPATH)
math.o: math.cpp math.h complex.h
	$(CC) -c $< $(INCPATH)
complex.o: complex.cpp complex.h
	$(CC) -c $< $(INCPATH)
