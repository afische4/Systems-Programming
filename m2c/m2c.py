import sys
import argparse
import exrex
import ray
import time
import pdb 
from Crypto.Hash import MD5
#fd = open('results.txt', 'a')

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
print(threads, regex, clean)
#function definitions ****************************

ray.init()
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
        print('Thread ', i , ' trying ', poss[i+x])
        results.append(thread.remote(poss[x+i],pswd))
    out = ray.get(results)
    #print(out)
    #print(poss[x:x+4])
    if True in out:
      return out[x:x+int(threads)], poss[x:x+int(threads)]
  return 0, 0

def ref(bools, ans):
  for i in range(0,len(bools)):
    if bools[i] == True:
      return ans[i]
  return 'No Matches'

def write_file(threads, pass_match, regex, start_time, datfile=None, pswd=None, clean=None):
  fd = open('results.txt', 'a')
  t_string = 'Using ' + str(threads) + ' threads it took '
  time1 = round(time.time() - start_time, 2)
  time1 = str(time1)
  if pswd:
    pswdstr = ' seconds to find ' + regex + ' match for ' + pswd + ' as ' + pass_match + '\n'
  elif clean == None:
    pswdstr = ' seconds to find ' + regex + ' match for ' + clean + '.\n'
  else:
    pswdstr = ' seconds to find ' + regex + 'matches in ' + datfile + '.\n'
  fd.write(t_string + time1 + pswdstr)
  return

# begin main code **********************************
if clean:
  pswd = clean.encode()
  m5 = MD5.new()
  m5.update(pswd)
  pswd = m5.hexdigest()

poss = list()
poss = list(exrex.generate(regex))

if datfile:
  f = open(datfile, 'r')
  pass_matches = list()
  for test in f:
    bools, ans = run_Threads(threads, test, poss)
    temp = ref(bools, ans)
    pass_matches.append(temp)
    #print(pass_matches)
  #write_file(threads, 'none', regex, start_time, datfile=datfile)
else:
  bools, ans = run_Threads(threads, pswd, poss)
  pass_match = ref(bools, ans)
  #print(pass_match, pswd)
  write_file(threads, pass_match, regex, start_time, datfile=None, pswd=pswd, clean=clean)




#fd.write('Using ', threads, ' it took ')
#fd.write(str(time.time() - start_time))
#fd.write(' seconds to find a match for ', args.pswd, '\n')

