# 4-digit-key-press-counter-with-persistence
Implement a 4 digit key press counter with persistence using Internal EEPROM. 

Output Requirements:
- As soon as the board is powered up or reset, counter should display 0000 on SSDs.
- On every key press  counter value should increment by 1.
- On a  long key press (2 seconds), Count should  reset to zero.
- On pressing STORE switch, the current count should be  stored in internal EEPROM.
- On subsequent power ups or reset the counter should start from the previous stored value in the EEPROM.
Inputs:
DKS 1 as Count input .
DKS 1 Long press to reset the count .
DKS 2 Store Input.
