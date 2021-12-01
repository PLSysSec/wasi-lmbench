# $Id$

# Make targets:
#
# lmbench	[default] builds the benchmark suite for the current os/arch
# results	builds, configures run parameters, and runs the benchmark
# rerun		reruns the benchmark using the same parameters as last time
# scaling	reruns the benchmark using same parameters as last time,
#		except it asks what scaling value to use
# hardware	reruns the hardware benchmarks using the same parameters
# os		reruns the OS benchmarks using the same parameters
# clean		cleans out sources and run configuration
# clobber	clean and removes the bin directories
# shar		obsolete, use cd .. && make shar
# depend	builds make dependencies (needs gcc)
# debug		builds all the benchmarks with '-g' debugging flag
# assembler	builds the .s files for each benchmark
#
# This is largely self configuring.  Most stuff is pretty portable.  
#
# If you don't have gcc, try make CC=cc and see if that works.
#
# If you want to do cross-compilation try make OS=armv5tel-linux-gnu
# or whatever your OS string should be in the target environment.
# Since many embedded development environments also have a special
# cross-compiler, you might want to also select a particular compiler,
# so your build command would look something like:
#	make OS=armv5tel-linux-gnu CC=gcc-arm
#
# Overriding the OS and CC make parameters needs to be done as an
# argument to make, not as an environment variable.  See above comments.
#

# I finally know why Larry Wall's Makefile says "Grrrr".
SHELL=/bin/sh

RLBOX_ROOT = ../../../rlbox_wasm2c_sandbox
WASM2C_SRC_ROOT = $(RLBOX_ROOT)/build/_deps/mod_wasm2c-src/wasm2c
WASM2C_BIN_ROOT = $(RLBOX_ROOT)/build/_deps/mod_wasm2c-src/bin

WASICLANG_ROOT = $(RLBOX_ROOT)/build/_deps/wasiclang-src/build/install/opt/wasi-sdk
WASILIBC_ROOT =  $(RLBOX_ROOT)/build/_deps/wasiclang-src/src/wasi-libc
CC = $(WASICLANG_ROOT)/bin/clang                        
CXX = $(WASICLANG_ROOT)/bin/clang++                   
CFLAGS = --sysroot  $(WASILIBC_ROOT)/sysroot/ 
LD = $(WASICLANG_ROOT)/bin/wasm-ld
LDFLAGS = -Wl,--export-all -Wl,--growable-table 
NM = $(WASICLANG_ROOT)/bin/llvm-nm
AR = $(WASICLANG_ROOT)/bin/llvm-ar
RANLIB = $(WASICLANG_ROOT)/bin/llvm-ranlib
VERIWASI_ROOT = ../../..
# Using O0 for debuggability. 
# This should not affect results since we are benchmarking the runtime not the compiled Wasm code
WASM2C_NATIVE_FLAGS = -shared -fPIC -O0 -I$(WASM2C_SRC_ROOT) $(WASM2C_SRC_ROOT)/wasm-rt-impl.c $(WASM2C_SRC_ROOT)/wasm-rt-os-unix.c $(WASM2C_SRC_ROOT)/wasm-rt-os-win.c $(WASM2C_SRC_ROOT)/wasm-rt-wasi.c -L$(VERIWASI_ROOT)/target/release/ -l:libveriwasi.so -I$(VERIWASI_ROOT)/bindings

#CC=`../scripts/compiler`
MAKE=`../scripts/make`
#AR=ar
ARCREATE=cr

# base of installation location
BASE=/usr/local
O= ../bin/unknown
D= ../doc
TRUE=/bin/true
OS=`../scripts/os`
TARGET=`../scripts/target`
BINDIR=../bin/$(OS)
CONFIG=../bin/$(OS)/`../scripts/config`
UTILS=../scripts/target ../scripts/os ../scripts/gnu-os ../scripts/compiler \
	../scripts/info ../scripts/info-template ../scripts/version \
	../scripts/config ../scripts/config-run ../scripts/results \
	../scripts/lmbench ../scripts/make ../scripts/build
INSTALL=cp
RESULTS=Results/$(OS)
SAMPLES=lmbench/Results/aix/rs6000 lmbench/Results/hpux/snake \
	lmbench/Results/irix/indigo2 lmbench/Results/linux/pentium \
	lmbench/Results/osf1/alpha lmbench/Results/solaris/ss20* 

COMPILE=$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)



INCS =	bench.h lib_mem.h stats.h timing.h lib_dummy.h
#  lib_tcp.h lib_udp.h

SRCS =  bw_file_rd.c bw_mem.c 	\
	cache.c clock.c  enough.c flushdisk.c getopt.c hello.c	\
	lat_mem_rd.c lat_ops.c 	lat_syscall.c	\
	lat_usleep.c  \
	lib_debug.c lib_mem.c lib_stats.c lib_timing.c 	\
	lib_sched.c	line.c loop_o.c 	\
	mhz.c msleep.c seek.c timing_o.c tlb.c		\
	bench.h lib_debug.h  names.h 	\
	stats.h timing.h version.h
#	bw_tcp.c bw_udp.c 
#	lat_connect.c lat_rpc.c lat_tcp.c lat_udp.c  lat_fs.c 
#	lib_tcp.c lib_udp.c lmhttp.c rhttp.c
# 	lib_tcp.h lib_udp.h disk.c

ASMS =  $O/bw_file_rd.s $O/bw_mem.s   	\
	$O/clock.s			\
	$O/enough.s $O/flushdisk.s $O/getopt.s $O/hello.s	\
	$O/lat_mem_rd.s  $O/lat_ops.s		\
	$O/lat_syscall.s $O/lib_debug.s $O/lib_mem.s	\
	$O/lib_stats.s  $O/lib_timing.s $O/lib_sched.s	\
	$O/line.s $O/loop_o.s $O/mhz.s $O/msleep.s	\
	$O/rhttp.s $O/timing_o.s $O/tlb.s			\
	$O/cache.s $O/lat_dram_page.s $O/lat_rand.s	\
	$O/lat_usleep.s 
# $O/bw_tcp.s $O/bw_udp.s $O/lat_connect.s $O/lmhttp.s $O/lib_udp.s
# $O/lat_udp.s $O/lat_tcp.s $O/lat_rpc.s $O/lib_tcp.s
# $O/lat_fs.s $O/disk.s
EXES =	$O/bw_file_rd $O/bw_mem 	\
	$O/hello  $O/lat_syscall	\
	$O/mhz $O/lat_mem_rd	\
	$O/timing_o $O/enough		\
	$O/msleep $O/loop_o		\
	$O/flushdisk		\
	$O/lat_ops $O/line $O/tlb
#	$O/bw_tcp  $O/lat_udp $O/lat_connect $O/lmhttp $O/lat_http $O/lat_rpc $O/lat_tcp $O/lat_fs $O/disk
OPT_EXES=$O/cache $O/lat_dram_page $O/lat_rand 		\
	$O/lat_usleep 
LIBOBJS=  $O/lib_timing.o $O/lib_dummy.o	\
	$O/lib_mem.o $O/lib_stats.o $O/lib_debug.o $O/getopt.o		\
	$O/lib_sched.o
#$O/lib_tcp.o $O/lib_udp.o

lmbench: $(UTILS)
	@env CFLAGS=-O MAKE="$(MAKE)" MAKEFLAGS="$(MAKEFLAGS)" CC="$(CC)" OS="$(OS)" ../scripts/build all
	-@env CFLAGS=-O MAKE="$(MAKE)" MAKEFLAGS="-k $(MAKEFLAGS)" CC="$(CC)" OS="$(OS)" ../scripts/build opt

results: lmbench
	@env OS="${OS}" ../scripts/config-run
	@env OS="${OS}" ../scripts/results

rerun: lmbench
	@if [ ! -f $(CONFIG) ]; then env OS="${OS}" ../scripts/config-run; fi
	@env OS="${OS}" ../scripts/results

scaling: lmbench
	@if [ ! -f $(CONFIG) ]; then env OS="${OS}" ../scripts/config-run; \
	 else ../scripts/config-scaling $(CONFIG); fi
	@env OS="${OS}" ../scripts/results

hardware: lmbench
	@if [ ! -f $(CONFIG) ]; then env OS="${OS}" ../scripts/config-run; fi
	@env OS="${OS}" BENCHMARK_HARDWARE=YES BENCHMARK_OS=NO  ../scripts/results

os: lmbench
	@if [ ! -f $(CONFIG) ]; then env OS="${OS}" ../scripts/config-run; fi
	@env OS="${OS}" BENCHMARK_HARDWARE=NO  BENCHMARK_OS=YES ../scripts/results

install: lmbench
	@env CFLAGS=-O MAKE="$(MAKE)"  MAKEFLAGS="$(MAKEFLAGS)" CC="${CC}" OS="${OS}" ../scripts/build install-target

install-target:
	if [ ! -d $(BASE) ]; then mkdir $(BASE); fi
	if [ ! -d $(BASE)/bin ]; then mkdir $(BASE)/bin; fi
	if [ ! -d $(BASE)/include ]; then mkdir $(BASE)/include; fi
	if [ ! -d $(BASE)/lib ]; then mkdir $(BASE)/lib; fi
	cp $(EXES) $(BASE)/bin
	cp $(INCS) $(BASE)/include
	cp $O/lmbench.a $(BASE)/lib/libmbench.a
	cd ../doc; env MAKEFLAGS="$(MAKEFLAGS)" make CC="${CC}" OS="${OS}" BASE="$(BASE)" install


# No special handling for all these
all: $(EXES) $O/lmbench
opt: $(OPT_EXES)
asm: $(ASMS)
$(ASMS):
	$(CC) -S $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ `basename $@ .s`.c

Wall:
	@env CFLAGS="-Wall -ansi" MAKE="$(MAKE)" MAKEFLAGS="$(MAKEFLAGS)" CC="${CC}" OS="${OS}" ../scripts/build all opt

debug:
	@env CFLAGS="-g -O" MAKE="$(MAKE)" MAKEFLAGS="$(MAKEFLAGS)" CC="${CC}" OS="${OS}" ../scripts/build all opt

assembler:
	@env CFLAGS=-O MAKE="$(MAKE)" MAKEFLAGS="$(MAKEFLAGS)" CC="${CC}" OS="${OS}" ../scripts/build asm

bk.ver: ../SCCS/s.ChangeSet
	rm -f bk.ver
	-echo `bk prs -hr+ -d'$$if(:SYMBOL:){:SYMBOL: }:UTC:' ../ChangeSet;` > bk.ver
	touch bk.ver

dist: bk.ver
	@if [ "X`cd ..; bk sfiles -c`" != "X" ]; then \
		echo "modified files!"; \
		false; \
	 fi
	@if [ "X`cd ..; bk pending`" != "X" ]; then \
		echo "pending changes!"; \
		false; \
	 fi
	cd ..; \
		SRCDIR=`pwd`; \
		DIR=`basename $${SRCDIR}`; \
		VERSION=`cat src/bk.ver| awk '{print $$1;}' | sed -e 's/Version-//g'`; \
		cd ..; \
		bk clone $${DIR} /tmp/lmbench-$${VERSION}; \
		cd /tmp/lmbench-$${VERSION}; \
		bk sfiles | xargs touch; \
		sleep 5; \
		bk get -s; \
		for d in doc results scripts src; do \
			cd $$d; bk get -s; cd ..; \
		done; \
		bk sfiles -U -g | xargs touch; \
		cd src; \
		make bk.ver; \
		cd /tmp; \
		tar czf $${SRCDIR}/../lmbench-$${VERSION}.tgz \
			lmbench-$${VERSION}; \
		rm -rf /tmp/lmbench-$${VERSION};

get $(SRCS):
	-get -s $(SRCS)

edit get-e:
	get -e -s $(SRCS)

clean:
	/bin/rm -f ../bin/*/CONFIG ../bin/*/*.[oas]
	/bin/rm -f *.[oas]
	-bk clean

clobber:
	/bin/rm -rf ../bin* SHAR
	-bk clean

shar:
	cd ../.. && shar lmbench/Results/Makefile $(SAMPLES) lmbench/scripts/* lmbench/src/Makefile lmbench/src/*.[ch] > lmbench/SHAR

depend: ../scripts/depend
	../scripts/depend

testmake: $(SRCS) $(UTILS) # used by scripts/make to test gmake
	@true

.PHONY: lmbench results rerun hardware os install all Wall debug \
	install install-target dist get edit get-e clean clobber \
	share depend testmake

$O/lmbench : ../scripts/lmbench bk.ver
	rm -f $O/lmbench
	sed -e "s/<version>/`cat bk.ver`/g" < ../scripts/lmbench > $O/lmbench
	chmod +x $O/lmbench

$O/lmbench.a: $(LIBOBJS)
	/bin/rm -f $O/lmbench.a
	$(AR) $(ARCREATE) $O/lmbench.a $(LIBOBJS)
	$(RANLIB) $O/lmbench.a


$O/lib_dummy.o : lib_dummy.c $(INCS)
	$(COMPILE) -c lib_dummy.c -o $O/lib_dummy.o
$O/lib_timing.o : lib_timing.c $(INCS)
	$(COMPILE) -c lib_timing.c -o $O/lib_timing.o
$O/lib_mem.o : lib_mem.c $(INCS)
	$(COMPILE) -c lib_mem.c -o $O/lib_mem.o
# $O/lib_tcp.o : lib_tcp.c $(INCS)
# 	$(COMPILE) -c lib_tcp.c -o $O/lib_tcp.o
# $O/lib_udp.o : lib_udp.c $(INCS)
# 	$(COMPILE) -c lib_udp.c -o $O/lib_udp.o
$O/lib_debug.o : lib_debug.c $(INCS)
	$(COMPILE) -c lib_debug.c -o $O/lib_debug.o
$O/lib_stats.o : lib_stats.c $(INCS)
	$(COMPILE) -c lib_stats.c -o $O/lib_stats.o
$O/lib_sched.o : lib_sched.c $(INCS)
	$(COMPILE) -c lib_sched.c -o $O/lib_sched.o
$O/getopt.o : getopt.c $(INCS)
	$(COMPILE) -c getopt.c -o $O/getopt.o

$(UTILS) :
	-cd ../scripts; make get

# Do not remove the next line, $(MAKE) depend needs it
# MAKEDEPEND follows
# $O/rhttp.s:rhttp.c timing.h stats.h bench.h 
# $O/rhttp:  rhttp.c timing.h stats.h bench.h $O/lmbench.a
# 	$(COMPILE) -o $O/rhttp rhttp.c $O/lmbench.a $(LDLIBS)

# $O/http.s:http.c timing.h stats.h bench.h 
# $O/http:  http.c timing.h stats.h bench.h $O/lmbench.a
# 	$(COMPILE) -o $O/http http.c $O/lmbench.a $(LDLIBS)

$O/flushdisk.s:flushdisk.c 
$O/flushdisk:  flushdisk.c 
	$(COMPILE) -DMAIN -o $O/flushdisk flushdisk.c
	$(WASM2C_BIN_ROOT)/wasm2c -o $O/flushdisk.wasm.c $O/flushdisk
	gcc -o $(RUNTIME)/flushdisk $O/flushdisk.wasm.c $(WASM2C_NATIVE_FLAGS)

$O/mhz.s: mhz.c timing.h stats.h bench.h
$O/mhz: mhz.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/mhz mhz.c $O/lmbench.a $(LDLIBS) -lm
	$(WASM2C_BIN_ROOT)/wasm2c -o $O/mhz.wasm.c $O/mhz
	gcc -o $(RUNTIME)/mhz $O/mhz.wasm.c $(WASM2C_NATIVE_FLAGS)


# $O/lmhttp.s:lmhttp.c timing.h stats.h bench.h
# $O/lmhttp:  lmhttp.c timing.h stats.h bench.h $O/lmbench.a
# 	$(COMPILE) -o $O/lmhttp lmhttp.c $O/lmbench.a $(LDLIBS)

# $O/lat_http.s:lat_http.c timing.h stats.h bench.h
# $O/lat_http:  lat_http.c timing.h stats.h bench.h $O/lmbench.a
# 	$(COMPILE) -o $O/lat_http lat_http.c $O/lmbench.a $(LDLIBS)

$O/bw_file_rd.s:bw_file_rd.c timing.h stats.h bench.h 
$O/bw_file_rd:  bw_file_rd.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/bw_file_rd bw_file_rd.c $O/lmbench.a $(LDLIBS)
	$(WASM2C_BIN_ROOT)/wasm2c -o $O/bw_file_rd.wasm.c $O/bw_file_rd
	gcc -o $(RUNTIME)/bw_file_rd $O/bw_file_rd.wasm.c $(WASM2C_NATIVE_FLAGS)


$O/bw_mem.s:bw_mem.c timing.h stats.h bench.h
$O/bw_mem:  bw_mem.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/bw_mem bw_mem.c $O/lmbench.a $(LDLIBS)
	$(WASM2C_BIN_ROOT)/wasm2c -o $O/bw_mem.wasm.c $O/bw_mem
	gcc -o $(RUNTIME)/bw_mem $O/bw_mem.wasm.c $(WASM2C_NATIVE_FLAGS)



# $O/bw_tcp.s:bw_tcp.c bench.h timing.h stats.h lib_tcp.h
# $O/bw_tcp:  bw_tcp.c bench.h timing.h stats.h lib_tcp.h $O/lmbench.a
# 	$(COMPILE) -o $O/bw_tcp bw_tcp.c $O/lmbench.a $(LDLIBS)

# $O/bw_udp.s:bw_udp.c bench.h timing.h stats.h lib_udp.h
# $O/bw_udp:  bw_udp.c bench.h timing.h stats.h lib_udp.h $O/lmbench.a
# 	$(COMPILE) -o $O/bw_udp bw_udp.c $O/lmbench.a $(LDLIBS)

# $O/disk.s:disk.c flushdisk.c bench.h timing.h stats.h lib_tcp.h
# $O/disk:  disk.c flushdisk.c bench.h timing.h stats.h lib_tcp.h $O/lmbench.a
# 	$(COMPILE) -o $O/disk disk.c $O/lmbench.a $(LDLIBS)

$O/clock.s:clock.c timing.h stats.h bench.h
$O/clock:  clock.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/clock clock.c $O/lmbench.a $(LDLIBS)
	gcc -o $(RUNTIME)/clock $O/clock.wasm.c $(WASM2C_NATIVE_FLAGS)


$O/hello.s:hello.c
$O/hello:  hello.c $O/lmbench.a
	$(COMPILE) -o $O/hello hello.c $O/lmbench.a $(LDLIBS)
	$(WASM2C_BIN_ROOT)/wasm2c -o $O/hello.wasm.c $O/hello
	gcc -o $(RUNTIME)/hello $O/hello.wasm.c $(WASM2C_NATIVE_FLAGS)


$O/lat_alarm.s:lat_alarm.c timing.h stats.h bench.h
$O/lat_alarm:  lat_alarm.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_alarm lat_alarm.c $O/lmbench.a $(LDLIBS)
	$(WASM2C_BIN_ROOT)/wasm2c -o $O/lat_alarm.wasm.c $O/lat_alarm
	gcc -o $(RUNTIME)/lat_alarm $O/lat_alarm.wasm.c $(WASM2C_NATIVE_FLAGS)


# $O/lat_connect.s:lat_connect.c lib_tcp.c bench.h lib_tcp.h timing.h stats.h
# $O/lat_connect:  lat_connect.c lib_tcp.c bench.h lib_tcp.h timing.h stats.h $O/lmbench.a
# 	$(COMPILE) -o $O/lat_connect lat_connect.c $O/lmbench.a $(LDLIBS)

# $O/lat_fs.s:lat_fs.c timing.h stats.h bench.h
# $O/lat_fs:  lat_fs.c timing.h stats.h bench.h $O/lmbench.a
# 	$(COMPILE) -o $O/lat_fs lat_fs.c $O/lmbench.a $(LDLIBS)

$O/lat_mem_rd.s:lat_mem_rd.c timing.h stats.h bench.h
$O/lat_mem_rd:  lat_mem_rd.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_mem_rd lat_mem_rd.c $O/lmbench.a $(LDLIBS)
	$(WASM2C_BIN_ROOT)/wasm2c -o $O/lat_mem_rd.wasm.c $O/lat_mem_rd
	gcc -o $(RUNTIME)/lat_mem_rd $O/lat_mem_rd.wasm.c $(WASM2C_NATIVE_FLAGS)


$O/lat_mem_rd2.s:lat_mem_rd2.c timing.h stats.h bench.h
$O/lat_mem_rd2:  lat_mem_rd2.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_mem_rd2 lat_mem_rd2.c $O/lmbench.a $(LDLIBS)
	$(WASM2C_BIN_ROOT)/wasm2c -o $O/lat_mem_rd2.wasm.c $O/lat_mem_rd2
	gcc -o $(RUNTIME)/lat_mem_rd2 $O/lat_mem_rd2.wasm.c $(WASM2C_NATIVE_FLAGS)

$O/lat_mem_wr.s:lat_mem_wr.c timing.h stats.h bench.h
$O/lat_mem_wr:  lat_mem_wr.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_mem_wr lat_mem_wr.c $O/lmbench.a $(LDLIBS)
	$(WASM2C_BIN_ROOT)/wasm2c -o $O/lat_mem_wr.wasm.c $O/lat_mem_wr
	gcc -o $(RUNTIME)/lat_mem_wr $O/lat_mem_wr.wasm.c $(WASM2C_NATIVE_FLAGS)

$O/lat_mem_wr2.s:lat_mem_wr2.c timing.h stats.h bench.h
$O/lat_mem_wr2:  lat_mem_wr2.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_mem_wr2 lat_mem_wr2.c $O/lmbench.a $(LDLIBS)
	$(WASM2C_BIN_ROOT)/wasm2c -o $O/lat_mem_wr2.wasm.c $O/lat_mem_wr2
	gcc -o $(RUNTIME)/lat_mem_wr2 $O/lat_mem_wr2.wasm.c $(WASM2C_NATIVE_FLAGS)

$O/lat_ops.s:lat_ops.c timing.h stats.h bench.h
$O/lat_ops:  lat_ops.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_ops lat_ops.c $O/lmbench.a $(LDLIBS)
	$(WASM2C_BIN_ROOT)/wasm2c -o $O/lat_ops.wasm.c $O/lat_ops
	gcc -o $(RUNTIME)/lat_ops $O/lat_ops.wasm.c $(WASM2C_NATIVE_FLAGS)

# $O/lat_rpc.s:lat_rpc.c timing.h stats.h bench.h
# $O/lat_rpc:  lat_rpc.c timing.h stats.h bench.h $O/lmbench.a
# 	$(COMPILE) -o $O/lat_rpc lat_rpc.c $O/lmbench.a $(LDLIBS)

$O/lat_syscall.s:lat_syscall.c timing.h stats.h bench.h
$O/lat_syscall:  lat_syscall.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_syscall lat_syscall.c $O/lmbench.a $(LDLIBS)
	$(WASM2C_BIN_ROOT)/wasm2c -o $O/lat_syscall.wasm.c $O/lat_syscall
	gcc -o $(RUNTIME)/lat_syscall $O/lat_syscall.wasm.c $(WASM2C_NATIVE_FLAGS)

# $O/lat_tcp.s:lat_tcp.c timing.h stats.h bench.h lib_tcp.h
# $O/lat_tcp:  lat_tcp.c timing.h stats.h bench.h lib_tcp.h $O/lmbench.a
# 	$(COMPILE) -o $O/lat_tcp lat_tcp.c $O/lmbench.a $(LDLIBS)

# $O/lat_udp.s:lat_udp.c timing.h stats.h bench.h lib_udp.h
# $O/lat_udp:  lat_udp.c timing.h stats.h bench.h lib_udp.h $O/lmbench.a
# 	$(COMPILE) -o $O/lat_udp lat_udp.c $O/lmbench.a $(LDLIBS)

# $O/lib_tcp.s:lib_tcp.c bench.h lib_tcp.h
# $O/lib_tcp:  lib_tcp.c bench.h lib_tcp.h $O/lmbench.a
# 	$(COMPILE) -o $O/lib_tcp lib_tcp.c $O/lmbench.a $(LDLIBS)

# $O/lib_udp.s:lib_udp.c bench.h lib_udp.h
# $O/lib_udp:  lib_udp.c bench.h lib_udp.h $O/lmbench.a
# 	$(COMPILE) -o $O/lib_udp lib_udp.c $O/lmbench.a $(LDLIBS)

$O/enough.s:enough.c timing.h stats.h bench.h
$O/enough:  enough.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/enough enough.c $O/lmbench.a $(LDLIBS)
	$(WASM2C_BIN_ROOT)/wasm2c -o $O/enough.wasm.c $O/enough
	gcc -o $(RUNTIME)/enough $O/enough.wasm.c $(WASM2C_NATIVE_FLAGS)


$O/loop_o.s:loop_o.c timing.h stats.h bench.h
$O/loop_o:  loop_o.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/loop_o loop_o.c $O/lmbench.a $(LDLIBS)
	$(WASM2C_BIN_ROOT)/wasm2c -o $O/loop_o.wasm.c $O/loop_o
	gcc -o $(RUNTIME)/loop_o $O/loop_o.wasm.c $(WASM2C_NATIVE_FLAGS)


$O/timing_o.s:timing_o.c timing.h stats.h bench.h
$O/timing_o:  timing_o.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/timing_o timing_o.c $O/lmbench.a $(LDLIBS)
	$(WASM2C_BIN_ROOT)/wasm2c -o $O/timing_o.wasm.c $O/timing_o
	gcc -o $(RUNTIME)/timing_o $O/timing_o.wasm.c $(WASM2C_NATIVE_FLAGS)

$O/msleep.s:msleep.c timing.h stats.h bench.h
$O/msleep:  msleep.c timing.h stats.h bench.h 
	$(COMPILE) -o $O/msleep msleep.c
	$(WASM2C_BIN_ROOT)/wasm2c -o $O/msleep.wasm.c $O/msleep
	gcc -o $(RUNTIME)/msleep $O/msleep.wasm.c $(WASM2C_NATIVE_FLAGS)

$O/line.s:  line.c timing.h stats.h bench.h
$O/line:  line.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/line line.c $O/lmbench.a $(LDLIBS)
	$(WASM2C_BIN_ROOT)/wasm2c -o $O/line.wasm.c $O/line
	gcc -o $(RUNTIME)/line $O/line.wasm.c $(WASM2C_NATIVE_FLAGS)

$O/tlb.s:tlb.c timing.h stats.h bench.h
$O/tlb:  tlb.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/tlb tlb.c $O/lmbench.a $(LDLIBS)
	$(WASM2C_BIN_ROOT)/wasm2c -o $O/tlb.wasm.c $O/tlb
	gcc -o $(RUNTIME)/tlb $O/tlb.wasm.c $(WASM2C_NATIVE_FLAGS)

$O/cache.s:cache.c timing.h stats.h bench.h
$O/cache:  cache.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/cache cache.c $O/lmbench.a $(LDLIBS)
	$(WASM2C_BIN_ROOT)/wasm2c -o $O/cache.wasm.c $O/cache
	gcc -o $(RUNTIME)/cache $O/cache.wasm.c $(WASM2C_NATIVE_FLAGS)

$O/lat_dram_page.s:lat_dram_page.c timing.h stats.h bench.h
$O/lat_dram_page:  lat_dram_page.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_dram_page lat_dram_page.c $O/lmbench.a $(LDLIBS)
	$(WASM2C_BIN_ROOT)/wasm2c -o $O/lat_dram_page.wasm.c $O/lat_dram_page
	gcc -o $(RUNTIME)/lat_dram_page $O/lat_dram_page.wasm.c $(WASM2C_NATIVE_FLAGS)

$O/lat_usleep.s:lat_usleep.c timing.h stats.h bench.h
$O/lat_usleep:  lat_usleep.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_usleep lat_usleep.c $O/lmbench.a $(LDLIBS)
	$(WASM2C_BIN_ROOT)/wasm2c -o $O/lat_usleep.wasm.c $O/lat_usleep
	gcc -o $(RUNTIME)/lat_usleep $O/lat_usleep.wasm.c $(WASM2C_NATIVE_FLAGS)

$O/lat_rand.s:lat_rand.c timing.h stats.h bench.h
$O/lat_rand:  lat_rand.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_rand lat_rand.c $O/lmbench.a $(LDLIBS)
	$(WASM2C_BIN_ROOT)/wasm2c -o $O/lat_rand.wasm.c $O/lat_rand
	gcc -o $(RUNTIME)/lat_rand $O/lat_rand.wasm.c $(WASM2C_NATIVE_FLAGS)


