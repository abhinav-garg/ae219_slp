import sys, pickle

def within_distance(a, b, radius):
	'''Checks if within radius, saves on square root operation'''
	# print "CHECKPOINT Distance function called"
	square_distance = (a[0] - b[0]) ** 2 + (a[1] - b[1]) ** 2 + (a[2] - b[2]) ** 2
	if square_distance <= radius ** 2:
		return True
	# print "CHECKPOINT Distance function passed"
	return False

def nearest_neighbours_list(xMax, yMax, zMax, radius, locations):
	'''Returns a list of nearest neighbours for each particle (indices for each index)'''
	cell_0_max = int(xMax // radius + 1)
	cell_1_max = int(yMax // radius + 1)
	cell_2_max = int(zMax // radius + 1)
		# Cells with corresponding particles
	cellList = [ [[ [] for z in range(0, cell_2_max)] for y in range(0, cell_1_max)] for x in range(0, cell_0_max)]
		# Generates a 3D list

		# Store corresponding particles in cells
	for index, particle in enumerate(locations):
		cellList[int(particle[0] // radius)][int(particle[1] // radius)][int(particle[2] // radius)].append(index)
		
		# particles with corresponding cells
	particle_cell = []
		# The list is inherently indexed. Just store corresponding locations
	for index, particle in enumerate(locations):
		
		particle_cell.append((int(particle[0] // radius), int(particle[1] // radius), int(particle[2] // radius)))
	
	# print cellList	
		# Neighbours corresponding to each particle
	neighbours = [[] for x in range(0, len(locations))]	# Initialize



	for index, particle in enumerate(locations):
		current_cell = particle_cell[index]		# Tuple
		for near_0 in [-1, 0, 1]:
			for near_1 in [-1, 0, 1]:
				for near_2 in [-1, 0, 1]:
					if current_cell[0] + near_0 >= 0 and current_cell[0] + near_0 < cell_0_max:
						if current_cell[1] + near_1 >= 0 and current_cell[1] + near_1 < cell_1_max:
							if current_cell[2] + near_2 >= 0 and current_cell[2] + near_2 < cell_2_max:
								for other_particle_index in cellList[current_cell[0] + near_0][current_cell[1] + near_1][current_cell[2] + near_2]:
									if within_distance(particle, locations[other_particle_index], radius):
										# print "Entering loop"
										neighbours[index].append(other_particle_index)
	return neighbours

def distance(a, b):
	'''Returns the distance'''
	return ((a[0] - b[0]) ** 2 + (a[1] - b[1]) ** 2 + (a[2] - b[2]) ** 2) ** 0.5
	
def check(neighbours, locations):
	for primary, secondaryIndices in enumerate(neighbours):
		for secondary in secondaryIndices:
			print primary, locations[primary], secondary, locations[secondary], distance(locations[primary], locations[secondary])

def print_all_distances(locations):
	print "Printing all distances"
	for indp, primary in enumerate(locations):
		for inds, secondary in enumerate(locations):
			print indp, primary, inds, secondary, distance(primary, secondary)

def main():
	xMax = 10.0
	yMax = 10.0
	zMax = 10.0
	radius = 4.0
	locations = []
	MAX = 10
	count = 0

	testSampleFile = open("testSampleFile.txt", "r")

	for string in testSampleFile:
		coords = string.split(',')
		coords = [float(el) for el in list(coords)]
		# print tuple(coords)
		locations.append(tuple(coords))

		count += 1
		if count >= MAX:
			break;

	testSampleFile.close()
	# print locations
	check(nearest_neighbours_list(xMax, yMax, zMax, radius, locations), locations)
	print_all_distances(locations)


if __name__ == '__main__':
	try:
		main()
	except Exception as e:
		print e