import random
import os
import filecmp
import sys
from collections import defaultdict 
  
class Graph(): 
  
    def __init__(self, V): 
        self.V = V 
        self.graph  = defaultdict(list) 
  
    def addEdge(self, v, w): 
        # Add w to v ist. 
        self.graph[v].append(w)  
        # Add v to w list. 
        self.graph[w].append(v)  
  
    # A recursive function that uses visited[]  
    # and parent to detect cycle in subgraph  
    # reachable from vertex v. 
    def isCyclicUtil(self, v, visited, parent): 
  
        # Mark current node as visited 
        visited[v] = True
  
        # Recur for all the vertices adjacent  
        # for this vertex 
        for i in self.graph[v]: 
            # If an adjacent is not visited,  
            # then recur for that adjacent 
            if visited[i] == False: 
                if self.isCyclicUtil(i, visited, v) == True: 
                    return True
  
            # If an adjacent is visited and not  
            # parent of current vertex, then there  
            # is a cycle. 
            elif i != parent: 
                return True
  
        return False
  
    # Returns true if the graph is a tree,  
    # else false. 
    def isTree(self): 
        # Mark all the vertices as not visited  
        # and not part of recursion stack 
        visited = [False] * self.V 
  
        # The call to isCyclicUtil serves multiple  
        # purposes. It returns true if graph reachable  
        # from vertex 0 is cyclcic. It also marks  
        # all vertices reachable from 0. 
        if self.isCyclicUtil(0, visited, -1) == True: 
            return False
  
        # If we find a vertex which is not reachable 
        # from 0 (not marked by isCyclicUtil(),  
        # then we return false 
        for i in range(self.V): 
            if visited[i] == False: 
                return False
  
        return True



def rr(min, max):
    if(min == max):
        return min
    return random.randrange(min, max)


###  config

testfile = "__test_gen_cls.txt"
good_prog = "java -jar tako.jar"
baad_prog = "repair_roads.exe"

good_out = "__good_out_cls.txt"
baad_out = "__baad_out_cls.txt"

###
while True: #main loop for retrying with different data
    N = rr(2, 10)
    #print(f"N: {N}")
    arr = []
    for xdddddddd in range(100): # try to make a tree
        gr = Graph(N)
        arr = []
        while len(arr) < N-1:
            #print(f"arlen: {len(arr)}")
            a = rr(0,N)
            b = rr(0,N)
            #print(f"Picked: {a} {b}")
            if a != b and (a, b) not in arr and (b, a) not in arr:
                arr.append((a,b))
                gr.addEdge(a,b)
                #tf.write(f"{a} {b}\n")
            #else:
            #    print("Random failed")
        #print("checking")
        #print("x", end="")
        if gr.isTree():
            #print("tree!")
            break
    #print("")

    tf = open(testfile, "w")
    tf.write(f"1\n{N}\n")
    for e in arr:
        tf.write(f"{e[0]} {e[1]}\n")
    tf.close()

    ###################################
    #print(f"{good_prog} < {testfile} > {good_out}")
    #print(f"{good_prog} < {testfile} > {good_out}")
    #print(f"{baad_prog} < {testfile} > {baad_out}")
    os.system(f"{good_prog} < {testfile} > {good_out} 2> err.txt")
    os.system(f"{baad_prog} < {testfile} > {baad_out} 2> debug.txt")
    good = open(good_out, "r")
    baad = open(baad_out, "r")

    lg = good.readlines()
    #lg = lg[:-1]
    lb = baad.readlines()
    #lb = lb[:-1]

    good.close()
    baad.close()

    if lg[-1] != lb[-1]:
        print(f"g: {lg[-1]}\nb: {lb[-1]}")
        break
    print("Test OK")
            