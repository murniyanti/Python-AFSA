import random, math
from scipy.spatial import distance
from operator import attrgetter

class Fish():
	"""docstring for Fish"""
	def __init__(self, p, f):
		self.position = p
		self.fitness= f

def initialize(dim, pop, GroupFish):
	for i in range(pop):
		s=[]
		for j in range(dim):
			s.append(random.random())
		fit=calcFitness(s)
		F=Fish(s, fit)
		GroupFish.append(F)
	
def calcFitness(s):
	sum=0
	i=0
	while i<(len(s)-1):
		r=100 * math.pow( (s[i+1]-math.pow(s[i],2) ) ,2) + math.pow( (s[i]-1), 2)
		sum=sum+r
		#print i
		i=i+1
	return sum
	
def makeTemp(ind, Visual):
	temp_pos=[]
	for i in range(len(ind.position)):
		temp=ind.position[i]+(Visual*random.random())
		temp_pos.append(temp)	
	temp_fit=calcFitness(temp_pos)
	F=Fish(temp_pos, temp_fit)
	return F

def prey(ind, TF, B, dim, step, n):
	crowdFactor=random.uniform(0.5, 1)
	new_State=[]
	for i in range(dim):
		m = ind.position[i] + (((TF.position[i]-ind.position[i])/abs(TF.position[i]-ind.position[i]))*step*random.random())
		new_State.append(m)
	#ind.position=new_State
	new_fit=calcFitness(ind.position)

	nf= distance.euclidean(ind.position, new_State)
	#ind.position=new_State
	#ind.fitness=new_fit

	#Swarm
	if B.fitness>ind.fitness and (nf/n)<crowdFactor:
		swarm(ind, B, dim, step)

	#follow
	elif new_fit>ind.fitness and (nf/n)<crowdFactor:
		follow(ind, TF, dim, step)
		
	else:
		ind.position=new_State
		ind.fitness=new_fit

def moveRandomly(ind, Visual):
	new_State=[]
	for i in range(len(ind.position)):
		n=ind.position[i]+ (Visual*random.random())
		new_State.append(n)
	ind.position=new_State
	ind.fitness=calcFitness(ind.position)
	
def getBestFish(GroupFish):
	L = sorted(GroupFish, key=attrgetter('fitness'))
	return L[-1]

def swarm(ind, B,dim, step):
	new_State2=[]
	for i in range(dim):
		m = ind.position[i] + (((B.position[i]-ind.position[i])/abs(B.position[i]-ind.position[i]))*step*random.random())
		new_State2.append(m)
	ind.position=new_State2
	ind.fitness=calcFitness(new_State2)

def follow(ind, TF, dim, step):
	new_State3=[]
	for i in range(dim):
		O = ind.position[i] + (((TF.position[i]-ind.position[i])/abs(TF.position[i]-ind.position[i]))*step*random.random())
		new_State3.append(O)
	ind.position=new_State3
	ind.fitness=calcFitness(new_State3)