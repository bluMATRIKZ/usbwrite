SU = sudo
BIN = usbwrite
INS = /usr/local/bin/usbwrite

all:
	$(SU) gcc main.c -o $(BIN)
	$(SU) strip -sv $(BIN)
	$(SU) install -m 0755 usbwrite $(INS)

remove:
	$(SU) rm -f $(INS)

clean:
	rm -f $(BIN)
