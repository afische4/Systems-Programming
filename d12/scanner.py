import socket
import pdb
import sys

datfile = sys.argv[1]
f = open(datfile, 'r')

#s.connect(('student00.cse.nd.edu', 22))

for line in f:
  s = socket.socket()
  s.settimeout(2)
  temp = line.split(':')
  host = temp[0]
  port = temp[1]
  line = line.rstrip('\n').lstrip()
  try:
    s.connect((host, int(port)))
    hostver = s.recv(64)
    hostver = str(hostver).lstrip('b\'')
    hostver = hostver.rstrip('b\'\\r\\n') 
    print(f'{line:<30s}{hostver}')
  except ConnectionRefusedError as msg:
    print(f'{line:<30s}<connection refused>')
  except socket.timeout as msg:
    print(f'{line:<30s}<connection timeout>')


f.close()


