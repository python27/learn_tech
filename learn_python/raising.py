#!usr/bin/python
#FileName: raising.py

class ShortInputException(Exception):
	'''A user-defined exception class'''
	def __init__(self,length,atleast):
		Exception.__init__(self)
		self.length = length
		self.atleast = atleast

try:
	s = raw_input("Enter something-->")
	if len(s)<3:
			raise ShortInputException(len(s),3)
except EOFError:
	print "\n Why did you do an EOF on me?"
except ShortInputException,x:
	print 'ShortInputException: the input length is %d,\
	was excepting at least %d' %(x.length, x.atleast)
else:
	print "No exception was raised."
