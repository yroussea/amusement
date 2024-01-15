from collections import *
from random import *
from copy import deepcopy

def get_map(h= randint(50,70), w= randint(10,15), salle= randint(10,15), taille_cercle=2, nb_collectible=4, couleur=0):
	m = [[float('inf') if k == 0 or k == h-1 or j == 0 or j == w-1 else float('inf') for k in range(h)] for j in range(w)]
	topleft = [(j,k) for k in range(h//2) for j in range(w//2) if m[j][k] == float('inf')]
	topright = [(j,k) for k in range(h//2, h) for j in range(w//2) if m[j][k] == float('inf')]
	downleft = [(j,k) for k in range(h//2, h) for j in range(w//2, w) if m[j][k] == float('inf')]
	downright = [(j,k) for k in range(h//2) for j in range(w//2, w) if m[j][k] == float('inf')]
	shuffle(topleft)
	shuffle(topright)
	shuffle(downleft)
	shuffle(downright)
	child = []
	for i in range(salle):
		if i%4==0:
			child.append(topleft[i//4])
		if i%4==1:
			child.append(topright[i//4])
		if i%4==2:
			child.append(downleft[i//4])
		if i%4==3:
			child.append(downright[i//4])
	t = test(deepcopy(m), h, w, child, taille_cercle, nb_collectible,couleur)
	t.finir()

class test:
	def __init__(self, mapi, h, w, child, taille_cercle=2, nb_c=4, affichage_couleur=0):
		self.ma = mapi
		self.h = h
		self.w = w
		self.child = child
		self.reliage(taille_cercle, nb_c)
		self.affichage_couleur = affichage_couleur
	
	def __str__(self, what:str="ma"):
		def prRed(skk): return ("\033[91m{}\033[00m" .format(skk)) if skk == "C" else prCyan(skk)
		def prCyan(skk): return ("\033[96m{}\033[00m" .format(skk))if skk in ['P', 'E'] else skk
		def line(l): return "".join([prRed(ele) for ele in l])
	
		ma = ""
		if self.affichage_couleur:
			for l in self.__getattribute__(what):
				ma = ma + line(l) + '\n'
		else:
			for l in self.__getattribute__(what):
				ma = ma + "".join([ele for ele in l]) + '\n'
		return (ma)[:-1]
	
	def affichage(self, taille_cercle=2, nb_c=4):

		new_m = []
		new_m.append(['1' for e in range(self.h+2)])
		for ele in self.ma:
			x = ['1'] + ['1' if e>5 else '0' for e in ele] + [1]
			new_m.append(['1'] + ['1' if e>taille_cercle else '0' for e in ele] + ['1'])
		new_m.append(['1' for e in range(self.h+2)])
		vide = [(j,k) for k in range(self.h) for j in range(self.w) if new_m[j][k] == '0']
		shuffle(vide)
		self.player, end, *self.enfant = vide[:2+nb_c]
		x,y = self.player
		new_m[x][y] = "P"
		x,y = end
		new_m[x][y] = "E"
		for c in self.enfant:
			x,y = c
			new_m[x][y] = "C"
		self.ma = new_m
		self.h += 2
		self.w += 2

	def te(self, taille_cercle=2, nb_c=4):
		for c in self.child:
			self.t(*c, 0)
		self.affichage(taille_cercle, nb_c)

	def t(self, x,y, i):
		if 0<=x<self.w and 0<=y<self.h and self.ma[x][y] > i:
			self.ma[x][y] = i
			self.t(x-1, y, i+1)
			self.t(x+1, y, i+1)
			self.t(x, y-1, i+1)
			self.t(x, y+1, i+1)

	def floodfill(self, x, y):
		if 0<=x<self.w and 0<=y<self.h and self.m[x][y] not in ['1', 'F']:
			self.m[x][y] = 'F'
			self.floodfill(x-1, y)
			self.floodfill(x+1, y)
			self.floodfill(x, y-1)
			self.floodfill(x, y+1)

	def reliage(self, taille_cercle=2, nb_c=4):
		self.te(taille_cercle, nb_c)
		self.child.sort(key=lambda a: a[1])
		for k in range(len(self.child) -1):
			a = list(self.chemin(list(self.child[k]), list(self.child[k+1])))
			for x,y in a:
				if self.ma[x][y] == '1' and 0<x<self.w-1 and 0<y<self.h-1:
					self.ma[x][y] = '0'

	def chemin(self,a,b):
		yield a
		while a != b:
			direction = choice([ele for ele in [(0, ((a[1]-b[1]<0)-(a[1]-b[1]>0))), ((a[0]-b[0]<0)-(a[0]-b[0]>0), 0)] if ele != (0,0)])
			a = [a[0]+direction[0], a[1]+direction[1]]
			yield a
		yield b
	
	def trouver(self):
		return [(j,k) for k in range(self.h) for j in range(self.w) if self.m[j][k] == 'C']

	def finir(self):
		self.m = deepcopy(self.ma)
		self.floodfill(*self.player)
		while 1:
			self.m = deepcopy(self.ma)
			self.floodfill(*self.player)
			x = self.trouver()
			if not x:
				break
			ele = x[0]
			a = list(self.chemin(list(ele), list(self.player)))
			for x,y in a:
				if self.ma[x][y] == '1' and 0<x<self.w-1 and 0<y<self.h-1:
					self.ma[x][y] = '0'
		print(self.__str__('ma'))

#pour choisir la largeur, h=
#pour choisir la hauteur, w=
#pour choisir a quoi resemble la map:
#le nb de salle: salle=
#la taille des salles=
#pour choisir le nb de collectibles, nb_collectible=
#randint veut dire un nombre aléatoire entre a et b
get_map(h=randint(27,33), w=randint(12,15), salle=randint(30,35), taille_cercle=2, nb_collectible=4)