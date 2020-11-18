
import socket
import sys

s = socket.socket()
host = 'localhost'
s.bind((host, 9999))

s.listen()

while True:
	c, addr = s.accept()
	
	while True:
		dat = c.recv(1024)
		if not dat:
			break

		dat = dat.decode('utf-8')
		dat = dat.rstrip()

		print(dat)

