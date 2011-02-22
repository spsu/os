# =======================================
# Makefile Setup
# I *really* need to learn the Autotools
# =======================================

C = g++ -g -Wall -fPIC -std=c++0x
LN = g++ -g -lstdc++
SHARED = g++ -shared -lstdc++
CD = cd
RM = /bin/rm -f
#INC = -I/usr/include/boost/tr1/tr1
LIB = -lboost_regex-mt
#INC = `pkg-config --cflags-only-I ......` #
#LIB = `pkg-config --libs ...... ` #


# ================
# Helpful Targets
# ================

all: 
	@echo 'Cannot compile all programs at once.'
	@echo '"make \tab" to see targets.'

.PHONY: clean
clean: 
	$(RM) main os test
	$(RM) *.o *.a *.so *.out
	cd ./build && $(RM) *.o *.so
	cd ./build && $(RM) */*.o */*.so */*/*.o */*/*.so

.PHONY: stats
stats:
	@wc -l -w -c -L */*.*pp */*/*.*pp */*/*/*.*pp */*/*/*/*.*pp
	@echo " Lines\tWords\tBytes\tLine\t"


# ==============
# Build Targets 
# ==============

### MAIN #############################
main: source/main.cpp required 
	@echo "[compile] main"
	@$(CD) ./build && $(C) $(INC) -c ../source/main.cpp
	@echo "[link] naively linking main to all built files"
	@$(LN) $(LIB) build/*.o -o main
	@chmod +x main
	@echo "\nBuild Success!\n"


# ==========
# Libraries 
# ==========

### ALL LIBS ##########################
required: \
	build/loader.o \
	build/memory.o \
	build/number.o
		@$(CD) .


# Normally you don't maintain something like this by hand...
# ==========================================================

build/loader.o: source/loader.hpp source/loader.cpp
	@echo "[compile] loader"
	@$(CD) ./build && $(C) $(INC) -c ../source/loader.cpp

build/memory.o: source/memory.hpp source/memory.cpp
	@echo "[compile] memory"
	@$(CD) ./build && $(C) $(INC) -c ../source/memory.cpp

build/number.o: source/number.hpp source/number.cpp
	@echo "[compile] number"
	@$(CD) ./build && $(C) $(INC) -c ../source/number.cpp

