import serial

ser = serial.Serial('/dev/cu.usbserial-AD0JIUAP', 460800, rtscts=False)


while (1):
	# Add Workaround to use flow control (using getCTS()) because rtscts flag doesn't work as expected
	while not ser.getCTS():
		continue

	ser.write("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n")
	ser.write("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb\n")
	ser.write("cccccccccccccccccccccccccccccccccccccccccccccccccc\n")
	ser.flush()

# ser.close()
