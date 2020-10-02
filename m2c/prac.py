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

args = parser.parse_args()

#set params
threads = args.threads
regex = args.regex

datfile = args.datfile
pswd = args.crypt
print(threads, regex)
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

# begin main code **********************************

poss = list()
poss = list(exrex.generate(regex))


results = list()
lim = len(poss)-1
for x in range(0, lim, int(threads)):
  for i in range(int(threads)):
    if i+x < lim:
      results.append(thread.remote(poss[x+i],pswd))
  out = ray.get(results)
  print(out)
  if True in out:
    bools = out
    ans = poss[x-int(threads):x]
    print(out, poss[x-int(threads):x])

for i in range(len(bools)):
  if bools[i]:
    print(bools[i], ans[i])
  else:
    print('No Matches')

print(time.time() - start_time)
