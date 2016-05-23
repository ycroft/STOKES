# var:
PROG_NAME=UT_INNERDATA
include env.mk
PROG_PATH=$(DEST)$(PROG_NAME)
# compile:
$(PROG_PATH): ut_innerdata.o innerdata.o complex.o
	$(CC) -o $@ ut_innerdata.o complex.o innerdata.o
ut_innerdata.o: ut_innerdata.cpp testsuite.h innerdata.h
	$(CC) -c $< $(INCPATH)
innerdata.o: innerdata.cpp innerdata.h
	$(CC) -c $< $(INCPATH)
complex.o: complex.cpp complex.h
	$(CC) -c $< $(INCPATH)
.PHONY: clean
clean:
	-rm ./*.o