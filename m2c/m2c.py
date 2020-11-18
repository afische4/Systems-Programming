import sys
import argparse
import exrex
import ray
import time
import pdb 
from Crypto.Hash import MD5

start_time = time.time()


descr = """Usage: m2c.py [-h] -r REGEX [-t NUMTHREADS] (-f PWF | -e EPW | -p PW)

      -r      regex
      -t      number of threads
      -f      file to read passwords from
      -e      single encrypted password
      -p      read cleartext password and encrypt, then crack encryption (debug purposes)"""

parser = argparse.ArgumentParser(description = descr, formatter_class=argparse.RawTextHelpFormatter)
parser.add_argument('-r', dest ='regex')
parser.add_argument('-t', dest='threads', default=2)
group = parser.add_mutually_exclusive_group()
group.add_argument('-f', dest ='datfile')
group.add_argument('-e', dest = 'crypt')
group.add_argument('-p', dest = 'clean')
args = parser.parse_args()

#set params
threads = args.threads
regex = args.regex
clean = args.clean
datfile = args.datfile
pswd = args.crypt
#function definitions ****************************

@ray.remote
def thread(match, pswd):
  #encrypts to MD5
  h = MD5.new()
  match = match.encode()
  h.update(match)
  if h.hexdigest() == pswd:
    return True
  else:
    return False

def run_Threads(threads, pswd, poss):
  results = list()
  lim = len(poss)-1
  for x in range(0, lim, int(threads)):
    for i in range(int(threads)):
      if i+x < lim:
        results.append(thread.remote(poss[x+i],pswd))
    out = ray.get(results)
    if True in out:
      return out[x:x+int(threads)], poss[x:x+int(threads)]
  return [False], [0]

def ref(bools, ans):
  for i in range(0,len(bools)):
    if bools[i] == True:
      return ans[i]
  return 'NONE'

def write_file(threads, pass_match, regex, start_time, pswd):
  fd = open('report.txt', 'a')
  t_string =   time1 = round(time.time() - start_time, 2)
  time1 = str(time1)
  pswdstr ='  '+str(threads)+'\t\t'+pswd+'\t'+pass_match+'\t'+regex+'\t'+time1+'\n'
  fd.write(pswdstr)
  return

# begin main code **********************************
if clean != None:
  pswd = clean.encode()
  m5 = MD5.new()
  m5.update(pswd)
  pswd = m5.hexdigest()

poss = list()
poss = list(exrex.generate(regex))

header='threads\t\tencrypted password\t\t\tmatch\tregex\t\ttime(s)\n'
open('report.txt','a').write(header)

if datfile != None:
  f = open(datfile, 'r')
  ray.init()
  for test in f:
    test = test.strip()
    bools, ans = run_Threads(threads, test, poss) 
    pass_match = ref(bools, ans)
    write_file(threads, pass_match, regex, start_time,test)
else:
  ray.init()
  bools, ans = run_Threads(threads, pswd, poss)
  pass_match = ref(bools, ans)
  write_file(threads, pass_match, regex, start_time, pswd)


