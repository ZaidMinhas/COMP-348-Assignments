class Game:
	def __init__(self):
		#Letter frequencies extracted from assignment
		self.freq = {'a': 8.17, 'b': 1.49, 'c': 2.78, 'd': 4.25, 'e': 12.7, 'f': 2.23, 'g': 2.02, 'h': 6.09, 'i': 6.97, 'j': 0.15, 'k': 0.77, 'l': 4.03, 'm': 2.41, 'n': 6.75, 'o': 7.51, 'p': 1.93, 'q': 0.1, 'r': 5.99, 's': 6.33, 't': 9.06, 'u': 2.76, 'v': 0.98, 'w': 2.36, 'x': 0.15, 'y': 1.97, 'z': 0.07}
		

	def getReport(self, data):
		#Number of games played
		games = len(data)

		#Total score
		total = 0

		#Report title
		print("++")
		print("++ Game Report")
		print("++\n")

		#Actual report
		print("Game\t\tWord\t\tStatus\t\tBad Guesses\t\tMissed Letters\t\tScores")
		print("----\t\t----\t\t------\t\t-----------\t\t--------------\t\t------")
		for game in range(games):

			word, index, letters, words, win = data[game]
			#round status if won or gave up
			if (win):
				msg = "Success"
			else:
				msg = "Give up"

			#send round data to get score
			score = self.getScore(*data[game])
			#add score to total
			total += score
			#print round stats
			print(f"{game+1}\t\t{word}\t\t{msg}\t\t{words}\t\t\t{letters}\t\t\t{score}")

		#print final score
		print(f"Final Score: {round(total,2)}")

	def getScore(self, word, index, letters, words, win):

		#score is sum of final consecetive guesses (this was my interpretation of the instructions)
		score = sum([self.freq[word[i]] for i in range(index, len(word))])

		#divide score by wrong letter guesses (if any)
		if (letters > 0):
			score /= letters

		#subtract 10%*number of wrong word guesses
		score *= (1 - 0.1*words)

		#score is negative if player gave up
		if not win:
			score *= -1

		#round score to 2 decimal places
		return round(score,2)
