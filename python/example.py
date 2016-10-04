#!/usr/bin/python
# coding=utf-8

import os
import sys
import math
import subprocess
from datetime import datetime

from catalantree import Node, decode, encode, catalan

#test()

#N = 6

#bstr = '00001'

#print("Binary sequence = " + bstr)

#I = int(bstr, 2) % catalan(N)

# I = 22

#print("tree index = " + str(I) + " of total " + str(catalan(N)))

#tree = decode(I, N)

#ret = tree.enumerate()

#print("enumerate = " + str(ret))

#print(tree.toDict())

#enc = bin(encode(tree))

#print("enc = " + str(enc))

#print("digraph G {\n" + tree.toDot() + "\n}\n")

N = 4

f = open("data_" + str(N) + ".dot", "w")

f.write("digraph G {\n")

for I in range(0, catalan(N)):
	tree = decode(I, N)
	tree.enumerate(prefix="_" + str(N) + "_" + str(I) + "_")
	dotstr = "subgraph sg_" + str(N) + "_" + str(I) + " {\n"\
			 + "\tlabel=\"index " + str(I) + "\";\n"\
	         + tree.toDot()\
	         + "\n}\n"
	f.write(dotstr)

f.write("}\n")

f.close()

task = subprocess.Popen("dot -Tpng data_" + str(N) + ".dot > data_" + str(N) + ".png", shell=True, stdout=subprocess.PIPE)


# for i in range(2, 5000):
# 	x = i
# 	c = catalan(x)
# 	l = int(math.ceil(math.log(c, 2)))
# 	print(str(x) + "; " + str(l) + "; " + str(2*x) )

# print("N\tH\tL1\tL2\tL3\tR1\t\tR2\tR3\n")

# for N in (2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000):
# 	L1 = 2*N
# 	C = catalan(N)
# 	H = math.log(C, 2)
# 	L2 = int(math.ceil(math.log(C, 2)))
# 	L3 = int(math.ceil(math.log(C, 2))) + int(math.ceil(math.log(N, 2)))
# 	R1 = float(L1 - H)/float(L1)
# 	R2 = float(L2 - H)/float(L2)
# 	R3 = float(L3 - H)/float(L3)
# 	print(str(N) + "\t" + str(H) +"\t" + str(L1) +"\t" + str(L2) +"\t" + str(L3) + "\t" + str(R1) + "\t" + str(R2) + "\t"+ str(R3) + "\n")

# test()
