
CC      = arm-linux-gcc
LD      = arm-linux-ld
AR      = arm-linux-ar
OBJCOPY = arm-linux-objcopy
OBJDUMP = arm-linux-objdump

INCLUDEDIR 	:= $(shell pwd)/include
CFLAGS 		:= -Wall -Os -fno-builtin
CPPFLAGS   	:= -nostdinc -I$(INCLUDEDIR)

export 	CC AR LD OBJCOPY OBJDUMP INCLUDEDIR CFLAGS CPPFLAGS 

objs := start.o  clock.o uart.o timer.o sdram.o main.o lib/libc.a nand.o

timer.bin: $(objs)
	${LD} -Ttimer.lds -o timer.elf $^
	${OBJCOPY} -O binary -S timer.elf $@
	${OBJDUMP} -D timer.elf > timer.dis

.PHONY : lib/libc.a
lib/libc.a:
	cd lib; make; cd ..
	
%.o:%.c
	${CC} $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

%.o:%.S
	${CC} $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
INCLUDEDIR 	:= $(shell pwd)/include
CFLAGS 		:= -Wall -Os -fno-builtin
CPPFLAGS   	:= -nostdinc -I$(INCLUDEDIR)

export 	CC AR LD OBJCOPY OBJDUMP INCLUDEDIR CFLAGS CPPFLAGS 

objs := start.o main.o uart.o clock.o lib/libc.a buzzer.o nand.o sdram.o

buzzer.bin: $(objs)
	${LD} -Tbuzzer.lds -o buzzer.elf $^
	${OBJCOPY} -O binary -S buzzer.elf $@
	${OBJDUMP} -D buzzer.elf > buzzer.dis

.PHONY : lib/libc.a
lib/libc.a:
	cd lib; make; cd ..
	
%.o:%.c
	${CC} $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

%.o:%.S
	${CC} $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
	make  clean -C lib
	rm -f buzzer.bin buzzer.elf buzzer.dis *.o
	make  clean -C lib
	rm -f *.bin *.elf *.dis *.o
	
