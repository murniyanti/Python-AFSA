import random, math
from cfish import *
#from scipy.spatial import distance
import copy

#algo params
dim=2
population=10
GroupFish=[]
trytimes=3
#Fish params
Visual=0.2
step=0.3

#params
i=0
iteration=10

StoreBest=[]
#init Fish 
initialize(dim, population, GroupFish)

B=getBestFish(GroupFish)
StoreBest.append(copy.deepcopy(B))

#Start iteration
while i< iteration:
	j=0
	while j<population:
		k=0
		while k<trytimes:	
			temp_Position=makeTemp(GroupFish[j], Visual)
			if GroupFish[j].fitness<temp_Position.fitness:
				prey(GroupFish[j], temp_Position, B, dim, step, population, Visual, GroupFish, j)
				break
			k=k+1
		moveRandomly(GroupFish[j], Visual)
		j=j+1
		#leapFish(GroupFish)
	i=i+1
	B=getBestFish(GroupFish)
	StoreBest.append(copy.deepcopy(B))

BE=getBestFish(StoreBest)
print BE.fitness


