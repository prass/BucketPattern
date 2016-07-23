PROGRAMMER=avrispmkII
DEVICE=/dev/ttyUSB0

CC=avr-gcc

main.hex: main
	avr-objcopy -j .text -j .data -O ihex $^ $@
main: $(OBJS)
	${CC} -Os -mmcu=${MCU} -o $@ $^
	avr-size --mcu=${MCU} $@
%.o: %.c
	${CC} -c -Os -mmcu=${MCU} -o $@ $^
burn: main.hex
	avrdude -p${MCU_AVRDUDE} -c${PROGRAMMER} -P${DEVICE} -U flash:w:$<
dump:
	avrdude -p${MCU_AVRDUDE} -c${PROGRAMMER} -P${DEVICE} -U flash:r:flashdump.hex:i
fuses:
	avrdude -p${MCU_AVRDUDE} -c${PROGRAMMER} -P${DEVICE} ${FUSES}
clean:
	-rm main
	-rm $(OBJS)
	-rm *.hex
.PHONY: clean burn dump
