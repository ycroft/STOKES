# var:
PROG_NAME=UT_COMPLEX
include env.mk
PROG_PATH=$(DEST)$(PROG_NAME)
# compile:
$(PROG_PATH): ut_complex.o complex.o
	$(CC) -o $@ ut_complex.o complex.o
ut_complex.o: ut_complex.cpp testsuite.h complex.h
	$(CC) -c $< $(INCPATH)
complex.o: complex.cpp complex.h
	$(CC) -c $< $(INCPATH)
.PHONY: clean
clean:
	-rm ./*.o