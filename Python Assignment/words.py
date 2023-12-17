from Guess import Guess
import sys

#check if parameter passed
if len(sys.argv) == 2:

	#store mode
	mode = sys.argv[1]
	
	#play mode
	if mode == "play":
		Guess()
	#test mode with guess word shown
	elif mode == "test":
		Guess(True)
	#incase neither mode is chosen
	else:
		print("Please enter play or test")
#incase neither mode is chosen
else:
	print("Please enter play or test")
