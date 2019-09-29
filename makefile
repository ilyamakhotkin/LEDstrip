all:
	msp430-gcc -c -mmcu=msp430g2533 src/main.c
	msp430-gcc -c -mmcu=msp430g2533 src/uart.c
	msp430-gcc -Os -mmcu=msp430g2533 -o ledStrip.elf main.o uart.o
	msp430-objcopy -O ihex ledStrip.elf ledStrip.hex # generate hex file
	mspdebug rf2500 "prog ledStrip.hex"
