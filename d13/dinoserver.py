import socket
import sys
import dinodata
import argparse

descr = 'Calculates Prey-Predator Ratio of specified animals'
examples = """recieves a string of prey adn predators, calculates ratio, returns result to client program"""
parser = argparse.ArgumentParser(description=descr, epilog=examples, formatter_class=argparse.RawTextHelpFormatter)
parser.add_argument('-p', dest = 'port', type=int, default='4444', help='port to connect')
parser.add_argument('-d', dest='datfile_in', type=str, default='dinosaur.dat', help='data file to read')
parser.add_argument('-e', dest='encryptpw', type=str, default='', help='encrypt, if specified, with given password')
parser.add_argument('-n', dest='hostname', type=str, default='localhost', help='host number for connection')
args = parser.parse_args()
#recieve a string in format described in dinoclient with the prey,prey|pred,pred
#calculate ratio use dinodata
#return result to client program

datfile = args.datfile_in
port = args.port
encryptpw = args.encryptpw
host = args.hostname
dinos = dinodata.dinodata(encryptpw)
dinos.readdinos(datfile)
s = socket.socket()
s.bind((host, port))
s.listen()

while True:
  c, addr = s.accept()
  #addr is whoever connected
  #c is a new socket (like new clone phone)
  while True:
    msg = c.recv(1024) #listen to what 'they' say and write it down
  #print(msg)
    if not msg:
      break             #until they say nothing
    msg = msg.decode('utf-8')
    msg = msg.rstrip() #always remember this
    #print(msg)
    msg = msg.split('|')
    prey = msg[0] 
    pred = msg[1]
    preys = prey.split(',')
    preds = pred.split(',')

    (num_prey, num_pred, yyrat) = dinos.preypredrat(preys, preds)
    #print(f'{num_prey}\t{num_pred}\t{yyrat}')
    out = f'{num_prey}\t{num_pred}\t{yyrat}' 
    out = out.encode('utf-8')
    c.send(out)
  #print('end test 1')
  #print(msg)
    
