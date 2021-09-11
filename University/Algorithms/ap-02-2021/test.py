import random
import os
import filecmp

def rr(min, max):
    if(min == max):
        return min
    return random.randrange(min, max)

###  config

testfile = "__test_gen.txt"
good_prog = "clnrbt.exe"
baad_prog = "cleaning_robot.exe"

good_out = "__good_out.txt"
baad_out = "__baad_out.txt"

###

while True:

    tf = open(testfile, "w")

    H = random.randrange(1, 20)
    W = random.randrange(1, 20)

    rob = (rr(1, W), rr(1, H))


    array_dirt = []
    array_obst = []
    dirts = rr(0, min(10, H*W-1))
    obsts = rr(0, min(10, H*W-1-dirts))
    for i in range(dirts):
        d = (rr(1, W), rr(1, H))
        if d != rob and d not in array_dirt:
            array_dirt.append(d)
    for i in range(obsts):
        d = (rr(1, W), rr(1, H))
        if d != rob and d not in array_dirt and d not in array_obst:
            array_obst.append(d)

    tf.write(str(W))
    tf.write(' ')
    tf.write(str(H))
    tf.write('\n')

    for i in range(1, H+1):
        for j in range(1, W+1):
            if (j, i) == rob:
                tf.write('o')
            elif (j, i) in array_dirt:
                tf.write('*')
            elif (j, i) in array_obst:
                tf.write('x')
            else:
                tf.write('.')
        tf.write('\n')
    tf.write("0 0\n")

    tf.close()

    ###################################
    #print(f"{good_prog} < {testfile} > {good_out}")
    #print(f"{good_prog} < {testfile} > {good_out}")
    #print(f"{baad_prog} < {testfile} > {baad_out}")
    os.system(f"{good_prog} < {testfile} > {good_out}")
    os.system(f"{baad_prog} < {testfile} > {baad_out}")
    if not filecmp.cmp(good_out, baad_out):
       break
    print("Test OK")
            