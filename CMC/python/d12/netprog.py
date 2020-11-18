import socket

s = socket.socket()
s.settimeout(60)

s.connect(('student00.cse.nd.edu', 22))

while True:
	data = s.recv(64)

	if not data:
		break

	data = data.decode('utf-8')

	print(data)

