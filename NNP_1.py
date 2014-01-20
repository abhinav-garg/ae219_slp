import code

def distance(a, b):
	if type(a) == int or type(a) == float:
		return abs(a-b)
	elif type(a) == tuple:
		return sum((x1 - x2)**2 for x1, x2 in zip(a, b))**0.5	
	else:
		return -1

xMax = 10.0
radius = 4.0
partLocList = [0.0, 6.0, 2.0, 5.0, 1.0, 7.0, 10.0]	# Particle Location List

# Create cells first, to get rid of potential key/index errors

cellPartList = [[] for x in range(0, int((xMax // radius + 1)))]	# Stores all particles corresponding to a cell; Initialize a list of lists

for ind, part in enumerate(partLocList):
	cellPartList[int(part // radius)].append(ind)	# Yields associated cell
		# Store particle index, as you need to store reference to the particle and not the particle itself

partCellList = []	# Stores the cell corresponding to each particle
for ind, part in enumerate(partLocList):
	partCellList.append(int(part // radius))

neighborList = [[] for x in range(0, len(partLocList))]	# Stores all the neighboring particles for a given particle; Initialize a list of lists

for ind, part in enumerate(partLocList):
	currCell = partCellList[ind]
	# code.interact(local=locals())
	for near in [-1, 0, 1]:
		if currCell + near >= 0 and currCell + near < len(cellPartList):
			for otherPartInd in cellPartList[currCell + near]:
				if distance(part, partLocList[otherPartInd]) <= radius:
					neighborList[ind].append(otherPartInd)
					# print currCell, ind, part, otherPartInd, partLocList[otherPartInd], distance(part, partLocList[otherPartInd])
					# print neighborList
			# print
code.interact(local=locals())

