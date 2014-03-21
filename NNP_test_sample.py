import random
import pickle
import sys

def generateTestSample(length):
	random.seed(3)
	testSample = [(random.random() * 10, random.random() * 10, random.random() * 10) for el in range(0, int(length))]
	# print test
	testSampleFile = open("testSampleFile.txt", "w")
	string = ""	# Initialize an empty string
	for testPoint in testSample:
		string += str(testPoint[0]) + "," + str(testPoint[1]) + "," + str(testPoint[2]) + "\n"
	testSampleFile.write(string)
	testSampleFile.close()

if __name__ == '__main__':
	try:
		print 'Populating a sample of ' + str(sys.argv[1]) + ' elements'
		generateTestSample(sys.argv[1])
		print 'Writing the list as a CSV file to the file testSampleFile.txt'
	except Exception as e:
		print e 
		print 'Pass the size of the sample as an argument'