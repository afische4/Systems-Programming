import socket
import sys
import dinodata
import argparse
import ray

parser = argparse.ArgumentParser( )
parser.add_argument('-p', dest = 'port', type=int, default='4444', help='port to connect')
parser.add_argument('-n', dest='hostname', type=str, default='localhost', help='host number for connection')
args = parser.parse_args()

datfile = 'dinosaur.dat'
port = args.port
host = args.hostname

s = socket.socket()
s.connect((host, port))

dinos = dinodata.dinodata()
dinos.readdinos(datfile)

  
#def getDinos(dino):
#  num = dinos.preypredrat(preys)
#  return num
#while True:
  #c, addr = s.accept()
  #addr is whoever connected
  #c is a new socket (like new clone phone)
#while True:

ray.init()
@ray.remote
def func(s, i):    
    out = str(0)
    out = out.encode('utf-8')
    s.send(out)
    msg = s.recv(1024) #listen to what 'they' say and write it down
      
      #print(msg)
      #if not msg:
      #  break  
    msg = msg.decode('utf-8')
    msg = msg.rstrip() #always remember this
    num_prey = dinos.preypredrat(msg)
    #print(f'{num_prey}')
    out = f'{num_prey}' 
    out = out.encode('utf-8')
    return out
    #s.send(out)
results=[]
for i in range(0,9):
  results.append(func.remote(s,i))

out=ray.get(results)
for i in out:
  s.send(i)
    #  print(i) 
