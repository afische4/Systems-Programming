import ray
import time

ray.init()

@ray.remote
def foo(x):
	time.sleep(5)
	print(x*x)
	return(x*x)

f1 = foo.remote(5)
f2 = foo.remote(6)

print(ray.get(f1))
print(ray.get(f2))

