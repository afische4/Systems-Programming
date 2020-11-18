from Crypto.Hash import MD5

f = open('words.txt', 'r')
g = open('crypts.txt', 'a')
for word in f:
  word = word.strip()
  h = MD5.new()
  word = word.encode()
  h.update(word)
  g.write(h.hexdigest())
  g.write('\n')
