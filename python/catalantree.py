import svgwrite
import math

class Node:
	def __init__(self):
		# left subtree
		self.llink = None
		# right subtree
		self.rlink = None
		# parent node
		self.plink = None
		# id of node (assigned after enumerating or manually)
		self.id = -1
		# Prefix  for enumeration
		# This is the auxiliary variable for DOT format generation
		self.prefix = ""

	def size(self):
		""" Get number of nodes in the tree """
		lsz = 0
		if (self.llink != None):
			lsz = self.llink.size()
		rsz = 0
		if (self.rlink != None):
			rsz = self.rlink.size()
		return lsz + rsz + 1

	def toDict(self):
		""" Represent tree as recursive structure dictionary:
				{'id': id, 'llink': {...}, 'rlink': {...}}
		"""
		d = {}
		d['id'] = self.id
		if (self.llink != None):
			d['llink'] = self.llink.toDict()
		if (self.rlink != None):
			d['rlink'] = self.rlink.toDict()
		return d

	def enumerate(self, id0 = None, prefix=""):
		""" Enumerate nodes of the tree in the DFS order and assign ids """
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

	def depth(self):
		""" Calculate maximum depth of the tree """
		md = 0
		if self.llink or self.rlink:
			md = 1
		ml = 0
		if self.llink:
			ml = self.llink.depth()
		mr = 0
		if self.rlink:
			mr = self.rlink.depth()
		md += max(ml, mr)
		return md

	def lwidth(self):
		""" width of the left subtree """
		w = 0
		if self.llink:
			w = self.llink.width() + 1
		return w

	def rwidth(self):
		""" width of the right subtree """
		w = 0
		if self.rlink:
			w = self.rlink.width() + 1
		return w

	def width(self):
		""" width of the tree """
		return self.lwidth() + self.rwidth()

	def toDot(self):
		""" Generate representation of the subtree in the DOT format and retur it as string
				For DOT format description and usage see http://www.graphviz.org/pdf/dotguide.pdf
		"""
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

	def toSvg(self, dwg = None, center = (0, 0)):
		""" Generate SVG drawing representation of this tree """
		first_call = False
		radius = 30
		dx = 50
		dy = 100
		if dwg is None:
			h = self.depth()*dy + radius*2 + 20
			w = self.width()*dx + radius*2 + 20
			dwg = svgwrite.Drawing(size=(w, h))
			dwg.add(dwg.rect((0, 0), (w, h), fill='none'))
			lw = 0
			if self.llink:
				lw = self.llink.width() + 1
			center = (lw*dx + radius, radius + 10)
			first_call = True
		c = tuple(center)
		xl = c[0]
		if self.llink:
			xl -= (self.llink.rwidth() + 1)*dx
		xr = c[0]
		if self.rlink:
			xr += (self.rlink.lwidth() + 1)*dx
		cl = (xl, c[1] + dy)
		cr = (xr, c[1] + dy)

		if self.llink:
			self.llink.toSvg(dwg, cl)
			alpha = abs(math.atan2(dy, c[0] - cl[0]))
			c1 = (c[0] - radius*math.cos(alpha), c[1] + radius*math.sin(alpha))
			c2 = (cl[0] + radius*math.cos(alpha), cl[1] - radius*math.sin(alpha))
			dwg.add(dwg.line(c1, c2, stroke='black', stroke_width=3))
		if self.rlink:
			self.rlink.toSvg(dwg, cr)
			alpha = abs(math.atan2(dy, cr[0] - c[0]))
			c1 = (c[0] + radius*math.cos(alpha), c[1] + radius*math.sin(alpha))
			c2 = (cr[0] - radius*math.cos(alpha), cr[1] - radius*math.sin(alpha))
			dwg.add(dwg.line(c1, c2, stroke='black', stroke_width=3))
		dwg.add(dwg.circle(c, radius, fill = 'white', stroke='black', stroke_width=3))
		if not self.id is None:
			dwg.add(dwg.text("{0}".format(self.id), x=[c[0]], y=[c[1]], fill = 'black', style="font-size: 30px; text-anchor: middle; dominant-baseline: middle;"))
		if first_call:
			return dwg


def factorial(n):
	if n == 0 or n == 1:
		return 1
	return n*factorial(n - 1)

def catalan(n):
	f0 = factorial(n)
	f1 = factorial(2*n)
	return f1//(f0*f0*(n + 1))

def cached_catalan(n, cache):
	if n in cache:
		return cache[n]
	else:
		c = catalan(n)
		cache[n] = c
		return c

ctr = 0

def decode(I, N, use_cache = False, cache = {}):
	""" Decode index of the tree I with nodes number N to the Node object
			For algorithm description see https://www.dropbox.com/s/boj4hc4caqu0i8h/paper_tree_encoding_fixed.docx?dl=0 (in Russian)
	"""
	if (N == 0):
		return None
	if use_cache:
		I = I % cached_catalan(N, cache)
	else:
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
		if use_cache:
			Cl = cached_catalan(Nl, cache)
			Cr = cached_catalan(Nr, cache)
		else:
			Cl = catalan(Nl)
			Cr = catalan(Nr)
		olds = s
		s = s + Cl*Cr
		K = K + 1
	I = I - olds
	Ir = I // Cl
	Il = I - Ir*Cl
	root.llink = decode(Il, Nl, use_cache, cache)
	root.rlink = decode(Ir, Nr, use_cache, cache)
	return root

def encode(root):
	""" Encode tree to its index I
			For algorithm description see https://www.dropbox.com/s/boj4hc4caqu0i8h/paper_tree_encoding_fixed.docx?dl=0 (in Russian)
	"""
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
