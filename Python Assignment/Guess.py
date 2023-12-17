import os
from StringDatabase import StringDatabase
from Game import Game
class Guess:
	def __init__(self, test_mode = False):
		#Get play mode from words.py
		self.test_mode = test_mode
		#Word getter method from StringDatabase class
		self.getWord = StringDatabase().getWord
		#Game report method from Game class
		self.getReport = Game().getReport
		#all played games
		self.game = None
		#main game loop
		self.play()

	def Display_Game(self):
		#clear screen
		os.system('clear')
		#display title
		print("++")
		print("++ The great guessing game")
		print("++")
		print()
		#display guess word if in test mode
		if (self.test_mode):
			print("Current Word:", self.secret)
		print("Current Guess:", "".join(self.curr_guess))
		print("Letters gussed:", " ".join(self.all_guesses))
		print()
		print("g = guess, t = tell me, l for a letter, and q to quit")	

	#Method to display a message in feedback format
	def Feedback(self, message):
		print("\n@@")
		print("@@ FEEDBACK:",message)
		print("@@\n")

	#Player decides to guess a letter
	def Guess_Letter(self):

		#letter input
		letter = input("\nEnter a letter: ")
		#letter lower cased
		letter = letter.lower()
		#number of gusses made
		n = len(self.all_guesses)
		#new guess added to set of guesses made
		self.all_guesses.add(letter)
		#if set size changed then new guess
		if (n != len(self.all_guesses)):
			#number of letters left to guess
			p = self.letters_left
			#goes through every letter in word to find guessed letter
			for i in range(self.word_count):
				if self.secret[i] == letter:
					self.curr_guess[i] = letter
					#everytime letter is guessed, number of letters left is reduced
					self.letters_left -= 1

			#if no more letters are left then user won the round
			if (self.letters_left == 0) :
				self.Feedback(f"You guessed the word \"{self.secret}\", good job!")
				self.win = True
				self.init_var()
				return True
			#if user gussed n letters then message is displayed saying n letters were gussed
			if (self.letters_left < p):
				self.Feedback(f"Hey you guessed {p-self.letters_left} letters!")
			#no correct guesses were made
			else:
				self.wrong_letters += 1
				self.scoring_from = self.letters_left
				self.Feedback("No correct guesses")
		#set size didnt change meaning word was already used
		else:
			self.Feedback(f"You already gussed '{letter}'")
		#word was not gussed
		return False

	#Player decideds to guess whole word
	def Guess_Word(self):
		#input word
		word = input("\nMake your guess: ")
		#see if word mathces
		output = self.secret == word.lower()
		#player gussed correctly
		if (output):
			self.Feedback(f"WOW you guessed the word \"{self.secret}\"")
			self.win = True
			self.init_var()
		#incorrect guess
		else:
			self.wrong_words += 1
			self.Feedback("Incorrect guess, try again!")

		return output

	#Initialize variables per round
	def init_var(self):
		#first condition is true if at least one round has been played, else running game for first time
		#self.game contains data for each round used for scoring player
		if (self.game != None) :
			self.game.append((self.secret, self.scoring_from, self.wrong_letters, self.wrong_words, self.win))
		else:
			self.game = []
		#data used for scoring
		self.scoring_from = 0
		self.wrong_letters = 0
		self.wrong_words = 0
		self.win = False

		#data used by game
		self.secret = self.getWord()
		self.word_count = len(self.secret)
		self.curr_guess = ["-" for i in range(self.word_count)]
		self.letters_left = self.word_count
		self.all_guesses = set()
		
	#Player has given up round
	def Tell_Word(self):
		self.Feedback(f"You lost!!!, word was \"{self.secret}\"")
		self.init_var()

	def play(self):
		#Game loop will run until quit
		playing = True
		#Initialize variables at start of game
		self.init_var()
		while playing:
			#display menu after each option
			self.Display_Game()
			#Choose option
			option = input("\nEnter Option: ")
			#Loop will run until correct option chosen
			while True:
				#guess word
				if option == "g":
					self.Guess_Word()
				#give up and tell word
				elif option == "t":
					self.Tell_Word()
				#guess letter
				elif option == "l":
					self.Guess_Letter()
				#quit game and show report
				elif option == "q":
					playing = False
					break
				#incorrect option was chosen
				else:
					option = input("Invalid option. Please re-enter: ")
					continue
				#proceed to next choice
				input("\nPress any key to continue...")
				break
		#clear screen after game ends
		os.system('clear')
		#show report
		self.getReport(self.game)