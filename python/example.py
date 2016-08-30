#!/usr/bin/python
# coding=utf-8

import os
import sys
import math
import subprocess

class Node:
	def __init__(self):
		self.llink = None
		self.rlink = None
		self.plink = None
		self.id = -1
		self.prefix = ""

	def size(self):
		lsz = 0
		if (self.llink != None):
			lsz = self.llink.size()
		rsz = 0
		if (self.rlink != None):
			rsz = self.rlink.size()
		return lsz + rsz + 1

	def dfs(self):
		print(self.id)
		if (self.llink != None):
			self.llink.dfs()
		if (self.rlink != None):
			self.rlink.dfs()

	def toDict(self):
		d = {}
		d['id'] = self.id
		if (self.llink != None):
			d['llink'] = self.llink.toDict()
		if (self.rlink != None):
			d['rlink'] = self.rlink.toDict()
		return d

	def enumerate(self, id0 = None, prefix=""):
		if (id0 == None):
			self.id = 0
		else:
			self.id = id0 + 1
		self.prefix = prefix
		ret = self.id
		if (self.llink != None):
			ret = self.llink.enumerate(ret, prefix=prefix)
		if (self.rlink != None):
			ret = self.rlink.enumerate(ret, prefix=prefix)
		return ret

	def toDot(self):
		ret = "\tn" + self.prefix + str(self.id) + " [shape=doublecircle, label=\"" + str(self.id) + "\"];\n"
		lname = "n" + self.prefix +str(self.id) + "_l"
		mname = "n" + self.prefix +str(self.id) + "_m"
		rname = "n" + self.prefix +str(self.id) + "_r"
		if (self.llink != None):
			lname = "n" + self.prefix +str(self.llink.id)
		if (self.rlink != None):
			rname = "n" + self.prefix +str(self.rlink.id)
		ret += "\tn" + self.prefix +str(self.id) + " -> " + lname;

		if (self.llink == None):
			ret += " [style=invis];\n"
		else:
			ret += ";\n"

		ret += "\tn" + self.prefix +str(self.id) + " -> " + mname + " [style=invis];\n";
		ret += "\tn" + self.prefix +str(self.id) + " -> " + rname;
		
		if (self.rlink == None):
			ret += " [style=invis];\n"
		else:
			ret += ";\n"

		if (self.llink == None):
			ret += "\t" + lname + " [label=\"\",width=.1,style=invis];\n"
		if (self.rlink == None):
			ret += "\t" + rname + " [label=\"\",width=.1,style=invis];\n"

		ret += "\t" + mname + " [label=\"\",width=.1,style=invis];\n"

		rankstr = "\t{rank=same " + lname + " -> " + mname + " -> " + rname + " [style=invis]};\n"
		ret += rankstr;
		if (self.llink != None):
			ret += self.llink.toDot()
		if (self.rlink != None):
			ret += self.rlink.toDot()
		return ret

def catalan(n):
	f0 = math.factorial(n)
	f1 = math.factorial(2*n)
	return f1/(f0*f0*(n + 1))

ctr = 0

def decode(I, N):
	if (N == 0):
		return None
	I = I % catalan(N)
	root = Node()
	global ctr
	root.id = ctr
	ctr = ctr + 1
	if (N == 1):
		return root
	Nl = N - 1
	Nr = 0
	s = 0
	olds = 0
	K = 0
	Cl = 1
	Cr = 1
	while (s <= I):
		Nl = N - K - 1
		Nr = K
		Cl = catalan(Nl)
		Cr = catalan(Nr)
		olds = s
		s = s + Cl*Cr
		K = K + 1
	I = I - olds
	Ir = I // Cl
	Il = I - Ir*Cl
	root.llink = decode(Il, Nl)
	root.rlink = decode(Ir, Nr)
	return root

def encode(root):
	if (root == None):
		return 0
	N = root.size()
	NL = 0
	if (root.llink != None):
		NL = root.llink.size()
	IL = encode(root.llink)
	IR = encode(root.rlink)
	NR = N - NL - 1
	I = 0
	for k in range(0, NR):
		I = I + catalan(N - k - 1)*catalan(k)
	I = I + catalan(NL)*IR
	I = I + IL
	return I

def test():
	nmax = 5
	for N in range(1, nmax + 1):
		for I in range(0, catalan(N)):
			tree = decode(I, N)
			enc = encode(tree)
			if (I != enc):
				print("I/enc mismatch: I = " + str(I) + "; enc = " + str(enc) + "; n = " + str(N))

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

N = 3

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


for N in range(1, 11):
	for K in range(1, N):
		I = 0
		for i in range(0, K+1):
			I = I + catalan(N - i - 1)*catalan(i)
		print("I(" + str(N) + ", " + str(K) + ") = " + str(I))