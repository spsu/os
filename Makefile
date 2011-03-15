# =======================================
# Makefile Setup
# I *really* need to learn the Autotools
# =======================================

C = g++ -O0 -g -Wall -fPIC -std=c++0x
LN = g++ -O0 -g -lstdc++
SHARED = g++ -shared -lstdc++
CD = cd
RM = /bin/rm -f
#INC = -I/usr/include/boost/tr1/tr1
LIB = -lboost_regex-mt -lpthread
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
	$(RM) uniprocessor multiprocessor main test
	$(RM) *.o *.a *.so *.out
	cd ./build && $(RM) *.o *.so
	cd ./build && $(RM) */*.o */*.so */*/*.o */*/*.so

.PHONY: stats
stats:
	@echo " Lines\tWords\tBytes\t"
	@wc -l -w -c */*.*pp 
	@echo " Lines\tWords\tBytes\t"


# ==============
# Build Targets 
# ==============

### UNIPROCESSOR MAIN #############################
uniprocessor: source/uniprocessor.cpp required 
	@echo "[compile] uniprocessor"
	@$(CD) ./build && $(C) $(INC) -c ../source/uniprocessor.cpp
	@echo "[link] linking to ALL built files"
	@$(RM) ./build/multiprocessor.o
	@$(LN) $(LIB) build/*.o -o uniprocessor
	@chmod +x uniprocessor 
	@echo "\nBuild Success!\n"

### MULTIPROCESSOR MAIN #############################
multiprocessor: source/multiprocessor.cpp required 
	@echo "[compile] multiprocessor"
	@$(CD) ./build && $(C) $(INC) -c ../source/multiprocessor.cpp
	@echo "[link] linking to ALL built files"
	@$(RM) ./build/uniprocessor.o
	@$(LN) $(LIB) build/*.o -o multiprocessor
	@chmod +x multiprocessor 
	@echo "\nBuild Success!\n"


# ==========
# Libraries 
# ==========

### ALL LIBS ##########################
required: \
	build/loader.o \
	build/store.o \
	build/memory.o \
	build/number.o \
	build/instruction.o \
	build/processlist.o \
	build/ltscheduler.o \
	build/stscheduler.o \
	build/dispatcher.o \
	build/pcb.o \
	build/cpu.o
		@$(CD) .


# Normally you don't maintain something like this by hand...
# ==========================================================

build/loader.o: source/loader.hpp source/loader.cpp
	@echo "[compile] loader"
	@$(CD) ./build && $(C) $(INC) -c ../source/loader.cpp

build/store.o: source/store.hpp source/store.cpp
	@echo "[compile] store"
	@$(CD) ./build && $(C) $(INC) -c ../source/store.cpp

build/memory.o: source/memory.hpp source/memory.cpp
	@echo "[compile] memory"
	@$(CD) ./build && $(C) $(INC) -c ../source/memory.cpp

build/number.o: source/number.hpp source/number.cpp
	@echo "[compile] number"
	@$(CD) ./build && $(C) $(INC) -c ../source/number.cpp

build/processlist.o: source/processlist.hpp source/processlist.cpp
	@echo "[compile] processlist"
	@$(CD) ./build && $(C) $(INC) -c ../source/processlist.cpp

build/instruction.o: source/instruction.hpp source/instruction.cpp
	@echo "[compile] instruction"
	@$(CD) ./build && $(C) $(INC) -c ../source/instruction.cpp

build/ltscheduler.o: source/ltscheduler.hpp source/ltscheduler.cpp
	@echo "[compile] ltscheduler"
	@$(CD) ./build && $(C) $(INC) -c ../source/ltscheduler.cpp

build/stscheduler.o: source/stscheduler.hpp source/stscheduler.cpp
	@echo "[compile] stscheduler"
	@$(CD) ./build && $(C) $(INC) -c ../source/stscheduler.cpp

build/dispatcher.o: source/dispatcher.hpp source/dispatcher.cpp
	@echo "[compile] dispatcher"
	@$(CD) ./build && $(C) $(INC) -c ../source/dispatcher.cpp

build/pcb.o: source/pcb.hpp source/pcb.cpp
	@echo "[compile] pcb"
	@$(CD) ./build && $(C) $(INC) -c ../source/pcb.cpp

build/cpu.o: source/cpu.hpp source/cpu.cpp
	@echo "[compile] cpu"
	@$(CD) ./build && $(C) $(INC) -c ../source/cpu.cpp

