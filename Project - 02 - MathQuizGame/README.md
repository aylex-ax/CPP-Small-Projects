<table align="center" width="100%" border="1">
  <tr>
    <td align="center">
      <h2>➗ Math Quiz Game (C++)</h2>
    </td>
  </tr>
  <tr>
    <td align="center">
      <img width="700" alt="Math Quiz Game" src="https://github.com/user-attachments/assets/6687cfc9-90fa-46bf-a5a0-6ed6a1c63ba0" />
    </td>
  </tr>
</table>




A console-based **Math Quiz Game** written in **C++** that generates random math questions based on the player's chosen difficulty level and operation type, then evaluates the answers and displays a final report with a Pass/Fail result.
The project focuses on procedural design using `enum`, `struct` arrays, and pass-by-reference to manage a full quiz session from start to finish.

---

# ✨ Features

- 🧮 Choose the number of questions (1–10)
- 🎯 Choose difficulty level: Easy / Medium / Hard / Mix
- ➕ Choose operation type: Add / Sub / Mult / Div / Mix
- 🎲 Random question generation based on difficulty range
- ✅ Automatic answer correction with instant feedback
- 📊 Final report with right/wrong answer count
- 🏆 Pass/Fail evaluation based on performance
- 🔁 Play again without restarting the program

---

# 🧠 Project Structure

The project follows a modular design where each function has a single responsibility.

### Main Components

| Function | Responsibility |
|----------|----------------|
| `RandomNumber()` | Generates a random number within a range |
| `ReadHowManyQuestions()` | Reads and validates the number of questions |
| `ReadQuestionLivel()` | Reads and validates the chosen difficulty level |
| `ReadOpType()` | Reads and validates the chosen operation type |
| `GenerateOperationType()` | Randomly generates an operation type (used in Mix mode) |
| `SimpleCalculator()` | Calculates the correct answer for a question |
| `GenerateQuestion()` | Builds a single question based on level and operation |
| `GetOpTypeSymbol()` | Converts the operation enum into a printable symbol |
| `GenerateQuizzQuestion()` | Fills the quiz's question list |
| `PrintTheQuestion()` | Displays a question to the player |
| `ReadQuesttionAnswer()` | Reads the player's answer |
| `CorrectTheQuestionAnswer()` | Checks the answer and updates the score |
| `GetQuestionLevelText()` | Converts the level enum into readable text |
| `AskAndCorrectQuestionListAnswers()` | Runs the full question/answer loop |
| `GetFinalResultsText()` | Converts the Pass/Fail result into readable text |
| `PrintQuizzResults()` | Displays the final quiz report |
| `PlayMathGame()` | Runs a complete quiz session |
| `ResetScreen()` | Clears the console between sessions |
| `StartGame()` | Controls the game loop and replay option |

---

# ⚙️ Program Flow

```text
Start Game
      │
      ▼
Choose Number of Questions
      │
      ▼
Choose Difficulty Level
      │
      ▼
Choose Operation Type
      │
      ▼
Generate Question List
      │
      ▼
For Each Question
      │
      ├── Display Question
      ├── Read Player Answer
      ├── Check Answer
      └── Update Score
      │
      ▼
Calculate Pass/Fail
      │
      ▼
Display Final Report
      │
      ▼
Play Again?
```

---

# 🎮 Gameplay

1. Enter the number of questions (**1–10**).
2. Choose the difficulty level:
```
1 → Easy
2 → Medium
3 → Hard
5 → Mix
```
3. Choose the operation type:
```
1 → Addition (+)
2 → Subtraction (-)
3 → Multiplication (*)
4 → Division (/)
5 → Mix
```
4. Answer each question as it appears.
5. Get instant feedback (Right/Wrong) after every answer.
6. At the end, view the final report and Pass/Fail result.
7. Choose to play again.

---

# 📥 Sample Input

```text
How Many Questions Do you Want to ansewr? 2
Enter Question Level { (1)Easy (2)Med (3)Hard (5)Mix } 1
Enter ReadOpType  1{+}  2{-}  3{*}  4{/}  5{Mix} 1
7
15
```

---

# 📤 Sample Output

```text
Question [1/2]

3
5 +
------------
Right Answer :)

Question [2/2]

8
2 +
------------
Worng Answer :(
The right answer is:10

------------------------------

Final Resuls is Fail :(

------------------------------

Number Of Question: 2
Question Level: Easy
OpType: +
Number Of Right Answers: 1
Number Of Wrong Answers: 1

------------------------------
```

---

# 🛠️ Concepts Practiced

- Functions
- Pass-by-Reference (`&`)
- Enums
- Structs & Struct Arrays
- Random Number Generation (`rand()` / `srand()`)
- `switch` Statements
- `do-while` Input Validation Loops
- Console Clearing & Color Reset (`system("cls")`, `system("color")`)
- Modular Programming

---

# 💻 How to Run

1. Open the project in **Visual Studio** (or any C++ IDE).
2. Make sure the file includes `<iostream>` and standard library support for `rand()`, `srand()`, and `system()`.
3. Build and run the project (`Ctrl + F5` in Visual Studio).
4. Follow the on-screen instructions to answer the quiz.

> ⚠️ Note: `system("cls")` and `system("color ...")` are Windows-specific and will not work on Linux/macOS terminals.

---

# 📚 What I Learned

During this project I practiced:
- Designing a multi-step console flow (setup → generate → play → report)
- Managing a collection of questions using a struct array
- Separating question generation logic from question presentation logic
- Building a scoring and evaluation system
- Validating user input with `do-while` loops
- Structuring a replay loop across full sessions

---

# 🐞 Known Issues

- The `Mix` difficulty level (value `5`) cannot currently be selected due to the validation condition in `ReadQuestionLivel()` only accepting values up to `4`.

---

# 🚀 Future Improvements

- Fix the `Mix` difficulty level validation
- Add a timer per question
- Track and display quiz history across sessions
- Add negative number support in Medium/Hard levels
- Object-Oriented version (OOP)
- Cross-platform support (remove Windows-only `system()` calls)
- Configurable pass threshold (currently right ≥ wrong)

---

# 💻 Built With

- C++
- Visual Studio
- Standard Library (`iostream`, `cstdlib`, `ctime`)

---

## ⭐ If you like this project, consider giving it a Star!
