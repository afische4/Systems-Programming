num = 100

for i in range(1, num+1):
  if not(i % 15):
    print('fizzbuzz')
  elif not(i % 3):
    print("fizz")
  elif not(i % 5):
    print('buzz' )
  else:
    print(i)

