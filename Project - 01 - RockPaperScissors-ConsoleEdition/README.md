<h1 align="center">🎮 Rock - Paper - Scissors Game (C++)</h1>

<p align="center">
  <img src="https://github.com/user-attachments/assets/61c691e0-e78b-45f2-a4aa-65236b62a1f5" width="650">
</p>
</p>

A simple console-based **Rock, Paper, Scissors** game written in **C++** where the player competes against the computer over multiple rounds.

The project was built after completing **Algorithms Level 2**, before learning **Object-Oriented Programming (OOP)**. It focuses on writing clean procedural code using functions, enums, structs, and pass-by-reference.

---

# ✨ Features

- 🎮 Play against the computer
- 🔢 Choose the number of rounds (1–10)
- 🎲 Random computer choices
- 📊 Live score tracking
- 🏆 Automatic game winner detection
- 🎨 Console color changes depending on the round result
- 🔁 Play again without restarting the program

---

# 🧠 Project Structure

The project follows a modular design where each function has a single responsibility.

### Main Components

| Function | Responsibility |
|----------|----------------|
| `ReadHowManyRounds()` | Reads and validates the number of rounds |
| `Choice_Player()` | Gets the player's choice |
| `Choice_Computer()` | Generates a random computer choice |
| `RandomNumber()` | Generates random numbers |
| `WhoWonTheRound()` | Determines the winner of a round |
| `WinnerName()` | Converts the winner enum into readable text |
| `ChoiceName()` | Converts the choice enum into readable text |
| `PrintRoundGame()` | Displays round information |
| `WhoWonTheGame()` | Determines the overall game winner |
| `FillGameResults()` | Stores the final game statistics |
| `PlayGame()` | Runs all game rounds |
| `ShowGameOverScreen()` | Displays the game over screen |
| `showFinalGame()` | Prints the final game results |
| `StartGame()` | Controls the game loop and replay option |

---

# ⚙️ Program Flow

```text
Start Game
      │
      ▼
Choose Number of Rounds
      │
      ▼
For Each Round
      │
      ├── Player Chooses
      ├── Computer Chooses Randomly
      ├── Determine Winner
      ├── Update Score
      └── Display Round Result
      │
      ▼
Display Final Results
      │
      ▼
Play Again?
```

---

# 🎮 Gameplay

1. Enter the number of rounds (**1–10**).
2. Choose:

```
1 → Stone
2 → Paper
3 → Scissor
```

3. The computer randomly selects its move.
4. The winner of the round is displayed.
5. Scores are updated after every round.
6. When all rounds finish, the final winner is announced.
7. The player can choose to play again.

---

# 📥 Sample Input

```text
How Many Rounds (1) to (10)? 3

Enter Choice:
1

Enter Choice:
2

Enter Choice:
3
```

---

# 📤 Sample Output

```text
Round [1]

Player Choice   : Stone
Computer Choice : Paper

Round Winner : Mr Computer

----------------------------

Game Results

Player Wins   : 1
Computer Wins : 2
Draws         : 0

Game Winner : Mr Computer
```

---

# 🛠️ Concepts Practiced

- Functions
- Pass-by-Reference (`&`)
- Enums
- Structs
- Random Number Generation (`rand()`)
- Control Flow
- Loops
- Switch Statements
- Console Applications
- Input Validation
- Modular Programming

---

# 📚 What I Learned

During this project I practiced:

- Designing a complete console application
- Splitting logic into reusable functions
- Working with `enum` and `struct`
- Passing objects by reference
- Organizing procedural code
- Tracking game state across multiple rounds
- Building a project before learning OOP

---

# 🚀 Future Improvements

- Add difficulty levels
- Better console UI
- ASCII Art animations
- Sound effects
- Statistics history
- Scoreboard
- Object-Oriented version (OOP)
- Cross-platform color support

---

# 💻 Built With

- C++
- Visual Studio
- Standard Library (`iostream`, `cstdlib`, `ctime`)

---

## ⭐ If you like this project, consider giving it a Star!
