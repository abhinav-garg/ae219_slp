def distance(a, b):
	'''1D distance'''
	return abs(a-b)

def nearest_neighbours_list(xMax, radius, locations):
	'''Returns a list of nearest neighbourss for eahc particle (indexices for each index)'''
		# Cells with corresponding particles
	cell_allocation = [[] for x in range(0, int((xMax // radius + 1)))]	# Initialize
		# Store corresponding particles in cells
	for index, particle in enumerate(locations):
		cell_allocation[int(particle // radius)].append(index)
		# particles with corresponding cells
	particle_cell = []
		# The list is inherently indexed. Just store corresponding locations
	for index, particle in enumerate(locations):
		particle_cell.append(int(particle // radius))
		# Neighbours corresponding to each particle
	neighbours = [[] for x in range(0, len(locations))]	# Initialize	
	for index, particle in enumerate(locations):
		current_cell = particle_cell[index]
		for near in [-1, 0, 1]:
			if current_cell + near >= 0 and current_cell + near < len(cell_allocation):
				for other_particle_index in cell_allocation[current_cell + near]:
					if distance(particle, locations[other_particle_index]) <= radius:
						neighbours[index].append(other_particle_index)
	return neighbours

xMax = 10.0
radius = 4.0
locations = [0.0, 6.0, 2.0, 5.0, 1.0, 7.0, 10.0]	# particle Location List

print nearest_neighbours_list(xMax, radius, locations)
