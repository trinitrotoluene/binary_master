# Binary Master

Server
- Accept 3 button inputs for the 3 digits in decimal
- Send the input number to Arduino 2
- Display random (wrong) numbers in binary N times (randomly generated N)
- Send the number it's displaying to Arduino 2
- Wait for Arduino 2 to send back whether someone got the right answer, and which player it was

Client
- Read the correct number and store it
- Read the number displayed by Arduino 2
- Wait for a button input
- If a player presses the button,
	- RIGHT: Send the number of the player, and true
	- WRONG: Send the number of the player, and false
- Wait for next number