import sys, pickle, time

def within_distance(a, b, radius):
	'''Checks if within radius, saves on square root operation'''
	# print "CHECKPOINT Distance function called"
	square_distance = (a[0] - b[0]) ** 2 + (a[1] - b[1]) ** 2 + (a[2] - b[2]) ** 2
	if square_distance <= radius ** 2:
		return True
	# print "CHECKPOINT Distance function passed"
	return False

def brute_force(xMax, yMax, zMax, radius, index, locations):
	'''Parameters are - the space extents xMax, yMax, zMax; the radius of search, the index of particle whose neighbours are required, and the locations of all paticles in space'''
	neighbours = []
	for ind, part in enumerate(locations):
		if within_distance(locations[index], part, radius):
			neighbours.append(ind)
	return neighbours

def preprocess(xMax, yMax, zMax, radius, locations):
	# Start Preprocessing - associating particles with cells
	cell_0_max = int(xMax // radius + 1)
	cell_1_max = int(yMax // radius + 1)
	cell_2_max = int(zMax // radius + 1)
		# Cells with corresponding particles
	cellList = [[[ [] for z in range(0, cell_2_max)] for y in range(0, cell_1_max)] for x in range(0, cell_0_max)]
		# Generates a 3D list

		# Store corresponding particles in cells
	for ind, part in enumerate(locations):
		cellList[int(part[0] // radius)][int(part[1] // radius)][int(part[2] // radius)].append(ind)
		
		# particles with corresponding cells
	particle_cell = []
		# The list is inherently indexed. Just store corresponding locations
	for part in locations:
		particle_cell.append((int(part[0] // radius), int(part[1] // radius), int(part[2] // radius)))
	# End preprocessing
	return cellList, particle_cell	

def nearest_neighbours_list(xMax, yMax, zMax, radius, index, locations, cellList, particle_cell):
	'''Parameters are - the space extents xMax, yMax, zMax; the radius of search, the index of particle whose neighbours are required, the locations of all paticles in space, and two lists obtained from preprocessing'''
	'''Returns a list of nearest neighbours for each particle (indices for each index)'''
	cell_0_max = int(xMax // radius + 1)
	cell_1_max = int(yMax // radius + 1)
	cell_2_max = int(zMax // radius + 1)

	neighbours = []	# Initialize

	particle = locations[index]

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
										neighbours.append(other_particle_index)
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

def load(file_name, n_particles):
	'''Parameter - the file name, and the number of particles to be loaded'''
	test_sample_file = open(file_name, 'r')
	count = 0
	locations = []
	for string in test_sample_file:
		coords = string.split(',')
		coords = [float(el) for el in list(coords)]
		locations.append(tuple(coords))
		count += 1
		if count >= n_particles:
			break;
	test_sample_file.close()
	return locations
	# Returns a list of tuples

def unit_test():
	locations = [(0,0,0),(1,1,1),(0,1,0),(2,0,0)]
	xMax = 10.0
	yMax = 10.0
	zMax = 10.0
	radius = 1.0
	check = [[0,2],[1],[0,2],[3]]
	for i in range(0, 4):
		n1 = brute_force(xMax, yMax, zMax, radius, i, locations)
		n1.sort()
		cellList, particle_cell = preprocess(xMax, yMax, zMax, radius, locations)
		n2 = nearest_neighbours_list(xMax, yMax, zMax, radius, i, locations, cellList, particle_cell)
		n2.sort()
		if n1!=check[i] and n1!=n2:
			print "Unit Test FAIL"
			break

def main():
	xMax = 10.0
	yMax = 10.0
	zMax = 10.0
	radius = 1.5
	MAX = 1000

	locations = load("testSampleFile.txt", MAX)

	unit_test()

	for high in [MAX]:
		for index in range(0, high):
			startTime = time.time()
			brute_force(xMax, yMax, zMax, radius, index, locations)
			endTime = time.time()
		diffTime = (endTime - startTime)
		print "%.30f" %diffTime

	for high in [MAX]:
		cellList, particle_cell = preprocess(xMax, yMax, zMax, radius, locations)
		for index in range(0, high):
			startTime = time.time()
			nearest_neighbours_list(xMax, yMax, zMax, radius, index, locations, cellList, particle_cell)
			endTime = time.time()
		diffTime = (endTime - startTime)
		print "%.30f" %diffTime

if __name__ == '__main__':
	try:
		main()
	except Exception as e:
		print e