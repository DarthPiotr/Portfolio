import random
import os
import filecmp
from networkx.algorithms.components.connected import is_connected
from networkx.generators.random_graphs import erdos_renyi_graph
import networkx as nx
import matplotlib.pyplot as plt

def rr(min, max):
    if(min == max):
        return min
    return random.randrange(min, max)

testfile = "__test_gen.txt"
good_prog = "cable_good.exe"
baad_prog = "cabletv.exe"

good_out = "__good_out.txt"
baad_out = "__baad_out.txt"
debug    = "__debug.txt"
gd       = "__debug_good.txt"

while True:

    # tf = open(testfile, "w")

    # tf.write("1\n");

    # result = False
    # while not result:
    #     n = rr(5, 10)
    #     p = rr(20,100) / 100
    #     g = erdos_renyi_graph(n, p)
    #     result = is_connected(g)

    # tf.write(f"{n} {len(g.edges)} ")

    # for t in g.edges:
    #     tf.write(f"({t[0]},{t[1]}) ")
    # tf.write("\n")
    # tf.close()

    os.system(f"{good_prog} < {testfile} > {good_out} 2> {gd}")
    os.system(f"{baad_prog} < {testfile} > {baad_out} 2> {debug}")
    if not filecmp.cmp(good_out, baad_out):
        print ("FAIL")
        #nx.draw_networkx(g)
        #plt.show()
        break
    print("Test OK")

