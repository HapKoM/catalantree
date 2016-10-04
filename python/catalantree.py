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

def factorial(n):
	if n == 0 or n == 1:
		return 1
	return n*factorial(n - 1)

def catalan(n):
	f0 = factorial(n)
	f1 = factorial(2*n)
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
	nmax = 20
	for N in range(1, nmax + 1):
		count = 100
		max_count = 1000
		tstart = datetime.now()
		c = 0
		for C in range(0, count):
			for I in range(0, catalan(N)):
				tree = decode(I, N)
				#enc = encode(tree)
				#if (I != enc):
				#	print("I/enc mismatch: I = " + str(I) + "; enc = " + str(enc) + "; n = " + str(N))
				c = c + 1
				if c > max_count:
					break
			if c > max_count:
				break
		tend = datetime.now()
		diff = tend - tstart
		t = diff.total_seconds()/c
		print("Average time for N = {0} is {1} (number of iterations = {2})".format(N, t, c))