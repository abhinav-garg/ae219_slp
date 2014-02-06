import random
import pickle
import sys

def generate_test(length):
	random.seed(3)
	test = [random.random() * 10 for el in range(0, int(length))]
	# print test
	pickle.dump(test, open('NNP_test_' + str(length) + '.p', 'wb'))

if __name__ == '__main__':
	try:
		print 'Populating a sample of ' + str(sys.argv[1]) + ' elements'
		generate_test(sys.argv[1])
		print 'Dumping the list in the file NNP_test_' + str(sys.argv[1])
	except Exception as e:
		print e 
		print 'Pass the size of the sample as an argument'