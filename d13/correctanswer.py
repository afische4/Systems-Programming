import socket
import sys
import dinodata
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('-p', dest = 'port', type=int, default='4444', help='port to connect')
parser.add_argument('-d', dest='datfile_in', type=str, default='dinosaur.dat', help='data file to read')
args = parser.parse_args()

datfile = args.datfile_in
port = args.port
host = 'localhost'
dinos = dinodata.dinodata('')
dinos.readdinos(datfile)
s = socket.socket()
s.bind((host, port))
s.listen()

def handle_call(c, addr):
  while True:
    dat = c.recv(1024)
    if not dat:
      break
    dat = dat.decode('utf-8')
    dat = dat.rstrip() 
    (preys, preds) = dat.split('|')
    prey = preys.split(',')
    pred = preds.split(',')
    try:
      (num_prey, num_pred, yyrat) = dinos.preypredrat(prey, pred)
      ret = f'{num_prey}\t{num_pred}\t{yyrat}'
    except ZeroDivisionError:
      ret = '<divide by zero error>'

    ret = ret.encode('utf-8')
    c.send(ret)
  c.close()

while True:
  c, addr = s.accept()
  handle_call(c, addr)
    
