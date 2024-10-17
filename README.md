# BATTLESHIPS
## ENCE260 Assignment 2 by Morgan Lee (mle150) and Kaden Adlington (kad112)

This is a simple adaptation of the popular board game **Battleships** for the UC FunKit4. In addition to the traditional gameplay, this version introduces new attack options.

## Game Phases

### **Setup Phase**
The game starts in the **setup phase**, where players place their ships using the joystick. Here’s how it works:

- **Joystick Navigation**: Use the joystick to move ships around the matrix.
- **Rotation**: Press the button to rotate the ships.
- **Placing Ships**: Push down on the joystick to place the ship, allowing the player to place the next one.

Once both players have positioned all their ships, one player must press the button to initiate the gameplay.

### **Gameplay Phase**
The game alternates between the **defender** and the **attacker** phases.

#### **Defender Phase**
The defender's screen displays the current positions of their ships. Ships will flash at the locations where the attacker has successfully hit. If an entire ship is flashing, it has been sunk.

- When the **blue LED** turns on for the attacker, the defender phase ends, and the attacker can press their button to enter their phase.

#### **Attacker Phase**
The attacker’s screen displays a target, indicating where they are aiming. The attacker only sees successful hits—misses will not be shown on the display.

- **Attack**: Once the target is selected, press down the navswitch to send the attack.
- **Hit/Miss Confirmation**: Both sides will confirm whether the attack was a hit or miss. After confirmation, the game automatically switches back to the defender phase.

### **Winning and Losing**
The game ends when one side loses all their ships:

- **Defender Loss**: When the defender presses their button, it will confirm they’ve lost.
- **Attacker Win/Loss**: After the final attack, the attacker will automatically see either:
  - **W** for a win.
  - **L** for a loss.

## Special Attacks

In addition to normal attacks, every few turns, the attacker will gain access to powerful attacks:

1. **Area Attack (Every 3rd turn)**
   - This is a 3x3 attack that hits everything in a 3x3 square area.

2. **Torpedo Attack (Every 6th turn)**
   - This attack hits an entire column, regardless of what's in it.