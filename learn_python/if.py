#!/usr/bin/python
#filename:if.py
number = 23
guess = int(raw_input('Enter an integer:'))

if guess == number:
	print'congratulations!'
elif guess < number:
	print'a little higher'
else:
	print'No, a little lower'

print("done")
