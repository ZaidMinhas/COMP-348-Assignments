import re
from random import randint
class StringDatabase:
	def __init__(self):
		#regex to get every word from a file
		word_re = re.compile(r"\w+")
		#open file containing words
		with open("four_letters.txt") as f:
			#find all instances of words
			self.word_list = word_re.findall(f.read())
		#number of words stored in a list
		self.word_count = len(self.word_list)

	def getWord(self):
		#get a random word from list
		n = randint(0,self.word_count-1)
		return self.word_list[n]


