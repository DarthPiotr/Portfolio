import random
import os
import filecmp

def rr(min, max):
    if(min == max):
        return min
    return random.randrange(min, max)

testfile = "__test_gen.txt"
good_prog = "gss3_good.exe"
baad_prog = "gss1.exe"

good_out = "__good_out.txt"
baad_out = "__baad_out.txt"

while True:

    tf = open(testfile, "w")

    N = rr(9, 16)
    tf.write(f"{N}\n")

    array = []
    for i in range(N):
        array.append(rr(-10, 10))
        tf.write(f"{array[i]} ")
    tf.write("\n1\n")
    p = rr(1, N)
    k = rr(p, N)
    tf.write(f"1 {p} {k}\n")
    tf.close()

    os.system(f"{good_prog} < {testfile} > {good_out}")
    os.system(f"{baad_prog} < {testfile} > {baad_out} 2> debug.txt")
    if not filecmp.cmp(good_out, baad_out):
       break
    print("Test OK")

