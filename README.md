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

## Data Framing

| 0                   | 1              | 2    | 3        | 4        | 5        | 6        | 7        |
| :------------------ | -------------- | ---- | -------- | -------- | -------- | -------- | -------- |
| Control / Player ID | Start / Answer | Stop | RESERVED | RESERVED | RESERVED | RESERVED | RESERVED |

- If the Control bit is set, the rest of the byte should be interpreted as a bit field and all subsequent bytes (if any) of the message should be interpreted as an integer parameter to the corresponding control code.
- If the Control bit is NOT set, the next 3 bits of the message are interpreted as a Player ID
  - The remaining 4 bits should be checked for their corresponding