import random
import os
import filecmp
from datetime import datetime

def rr(min, max):
    if(min == max):
        return min
    return random.randrange(min, max)

testfile = "__test_gen_lite.txt"
good_prog = "lite_good.exe"
baad_prog = "lite.exe"

good_out = "__good_out_lite.txt"
baad_out = "__baad_out_lite.txt"

#while True:

tf = open(testfile, "w")

N = rr(33, 65)
M = 10 #rr(100, 10001)

currtime = datetime.now().strftime("%d.%m.%Y %H:%M:%S")
print(f"[{currtime}] Testing with N: {N}, M: {M} ...")

tf.write(f"{N} {M}\n")

for i in range(M-1):
    a = rr(1, N+1)
    b = rr(a, N+1)
    tf.write(f"{0 if rr(0, 100) < 66 else 1} {a} {b}\n")

a = rr(1, N+1)
b = rr(a, N+1)
tf.write(f"1 {a} {b}\n")
tf.close()

os.system(f"{good_prog} < {testfile} > {good_out}")
os.system(f"{baad_prog} < {testfile} > {baad_out} 2> debug_lite.txt")
#if not filecmp.cmp(good_out, baad_out):
#    break
currtime = datetime.now().strftime("%d.%m.%Y %H:%M:%S")
print(f"[{currtime}] Test OK")

