import os

def toMatrixFunc(filename):
	nodeNum = 0

	f = open(filename, "r")
	line = f.readline()
	if line.find("*Vertices") != -1:
		alist = line.split()
		nodeNum = int(alist[-1])

	# get the node number from the *Vertices row
	print("Node Number: %d\n" %(nodeNum), end = "")

	# find and seek the "*Edges" row
	line = f.readline()
	while line != "*Edges\n":
		line = f.readline()

	# init the adjancency matrix of the graph
	matrix = [[0 for x in range(nodeNum)] for y in range(nodeNum)]

	line = f.readline()
	while line:
		edgeInfo = line.split()
		start = int(edgeInfo[0])
		end = int(edgeInfo[1])
		# get the adjancency matrix of the graph
		matrix[start-1][end-1] = 1
		matrix[end-1][start-1] = 1
		line = f.readline()

	f.close()

    # change the extension of the filename
	newFileExt = ".txt"
	oldFileExt = os.path.splitext(filename)[1]
	newname = filename.replace(oldFileExt, newFileExt)

	# write the adjancency matrix to the file
	outfile = open(newname, "w")
	for i in range(nodeNum):
		for j in range(nodeNum):
			print("%d " %(matrix[i][j]), end = "", file = outfile),
			#sys.stdout.write(" %d" %(matrix[i][j]))
			
		print("\n", end = "", file = outfile)
		
	outfile.close()
