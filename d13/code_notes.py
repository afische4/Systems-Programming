import socket
import sys

s = socket.socket()
host = 'localhost'
s.bind((host, 4444))
s.listen()

while True:
  c, addr = s.accept()
  #addr is whoever connected
  #c is a new socket (like new clone phone)
  while True:
    dat = c.recv(1024) #listen to what 'they' say and write it down
    if not dat:
      break             #until they say nothing
    
    dat = dat.decode('utf-8')
    dat = dat.rstrip() #always remember this

    print(dat)
