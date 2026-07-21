<h1 align="center">🏦 Bank Client Management System (C++)</h1>

<p align="center">
  ((الصورة هنا))
</p>


<table align="center" width="100%" border="1">
  <tr>
    <td align="center">
      <h2>🏦 Bank Client Management System (C++)</h2>
    </td>
  </tr>
  <tr>
    <td align="center">
     <img width="2056" height="768" alt="Firefly (3)" src="https://github.com/user-attachments/assets/7498dfff-f40c-4f8a-a8cd-7c9d475d88a0" />
    </td>
  </tr>
</table>




A console-based **Bank Client Management System** written in **C++** that manages client records with full **CRUD** operations (Create, Read, Update, Delete) using persistent **file handling** — no database required. Client data is stored and retrieved from a local text file (`Clients.txt`), with each record parsed and rebuilt using a custom delimiter-based line format.

This project is part of the **[Algorithms and Fundamentals – Level 03: Algorithms Problem-Solving Level 3](https://github.com/mostafa-000/Algorithms-and-Fundamentals/tree/master/Level%2003%20-%20Algorithms%20Problem-Solving%20Level%203)** course track.

---

# ✨ Features

- 📋 Show a full list of all clients
- ➕ Add one or multiple new clients in a row
- 🗑️ Delete a client by account number (with confirmation)
- ✏️ Update client information (PIN, name, phone, balance)
- 🔍 Find a client by account number
- 💾 Persistent storage using a local text file (no database needed)
- 🚫 Duplicate account number prevention when adding a new client
- 🎨 Styled console menu and client list display

---

# 🧠 Project Structure

The project follows a modular design where each function has a single responsibility, split across three concerns: **file handling**, **client operations**, and **menu/UI**.

### Main Components

| Function | Responsibility |
|----------|----------------|
| `SplitString()` | Splits a text line into parts using a custom delimiter |
| `ConvertLinetoRecord()` | Converts a text line into a `sClient` struct |
| `ConvertRecordToLine()` | Converts a `sClient` struct into a text line |
| `LoadCleintsDataFromFile()` | Loads all client records from the file into a vector |
| `SaveCleintsDataToFile()` | Saves the current client list back to the file |
| `AddDataLineToFile()` | Appends a new record line to the file |
| `ReadNewClient()` / `ReadNewOneClient()` | Reads new client data from user input |
| `AddOneClint()` / `AddNewClients()` | Adds one or more new clients |
| `FindClientByAccountNumber()` | Searches the loaded vector for a client |
| `SershForClient()` | Searches the file directly for a client by account number |
| `MarkClientForDeleteByAccountNumber()` | Flags a client record for deletion |
| `DeleteClients()` / `DeleteClient()` | Handles the full client deletion flow |
| `ChangeClientRecord()` | Reads updated field values for a client |
| `UpdateClientByAccountNumber()` / `UpdateClientInfo()` | Handles the full client update flow |
| `FindClient()` | Handles the full client search flow |
| `PrintClientRecord()` / `PrintClientCard()` / `PrintSersh()` | Display client data in different formats |
| `ShowClientList()` | Displays the full client list with a styled header |
| `ReadMainMenueOption()` / `PrefroMainMenueOption()` | Reads and routes the main menu selection |
| `GoBackToHome()` | Returns to the main menu after an operation |
| `ShowMainMenue()` | Displays the main menu and drives the program loop |

---

# ⚙️ Program Flow

```text
Start App
      │
      ▼
Show Main Menu
      │
      ├── [1] Show Client List ──► Load File ──► Display All Clients
      │
      ├── [2] Add New Client   ──► Check Duplicate ──► Append to File
      │
      ├── [3] Delete Client    ──► Find by Account # ──► Confirm ──► Save File
      │
      ├── [4] Update Client    ──► Find by Account # ──► Confirm ──► Edit ──► Save File
      │
      ├── [5] Find Client      ──► Search File ──► Display Result
      │
      └── [6] Exit App
      │
      ▼
Return to Main Menu (until Exit)
```

---

# 🎮 Usage

1. Run the program — the main menu appears with options **[1–6]**.
2. Choose an operation:
```
1 → Show Client List
2 → Add New Client
3 → Delete Client
4 → Update Client Info
5 → Find Client
6 → Exit
```
3. Follow the on-screen prompts for the selected operation.
4. After each operation, press any key to return to the main menu.

---

# 📥 Sample Input

```text
>>>>> Choose Any [1 to 6] ? 2

| Enter Data:
| Enter Account Number? 1001
| Enter PinCode? 2580
| Enter Name? Mostafa Saad
| Enter Phone? 01012345678
| Enter AccountBalance? 2500

>> Do you want to add a client? (Y OR N): N
```

---

# 📤 Sample Output

```text
*-------------------------*----
| Name saved successfully | :)
*-------------------------*----

  *=====================================================================================*
  * |AccountNumber       |PinCode        |Name           |Phone          |AccountBalance*
  *=====================================================================================*
  * |1001                |2580           |Mostafa Saad   |01012345678    |2500          *
  *=====================================================================================*
```

---

# 🛠️ Concepts Practiced

- Functions & Function Prototypes (Forward Declaration)
- Structs
- Vectors (`std::vector`)
- File Handling (`fstream`, `ios::in`, `ios::out`, `ios::app`)
- String Parsing & Delimiter-Based Serialization
- Pass-by-Reference (`&`)
- Default Function Parameters
- Enums for Menu Routing
- `switch` Statements
- Soft-Delete Pattern (`MarkForDelete` flag)
- Console Formatting (`iomanip`, `setw`, `left`)
- Modular Programming

---

# 💻 How to Run

1. Open the project in **Visual Studio** (or any C++ IDE).
2. Make sure the file includes `<iostream>`, `<fstream>`, `<string>`, `<vector>`, and `<iomanip>`.
3. Build and run the project (`Ctrl + F5` in Visual Studio).
4. On first run, if `Clients.txt` doesn't exist yet, it will be created automatically the first time a client is added.
5. Use the main menu to manage clients.

> ⚠️ Note: `system("cls")` and `system("pause>0")` are Windows-specific and will not work on Linux/macOS terminals.

---

# 📚 What I Learned

During this project I practiced:
- Designing a full CRUD system around a single data file
- Serializing and deserializing structs to/from text using a custom delimiter
- Separating file I/O logic from business logic and UI logic
- Implementing a soft-delete pattern before rewriting a file
- Preventing duplicate records through search-before-insert validation
- Structuring a multi-option console menu with clean navigation flow

---

# 🐞 Known Issues

- In `ChangeClientRecord()`, the line `Client.AccountNumber == AccountNumber;` uses a comparison (`==`) instead of an assignment (`=`), so the account number field is not actually reassigned during an update — though this has no practical side effect since the account number isn't meant to change.
- `LoadCleintsDataFromFile()` doesn't handle a missing file gracefully in every case; the program relies on the file being created through the "Add Client" flow.

---

# 🚀 Future Improvements

- Fix the comparison-instead-of-assignment issue in `ChangeClientRecord()`
- Add input validation (empty fields, non-numeric balance, duplicate PIN, etc.)
- Encrypt or mask the PIN code instead of storing it as plain text
- Replace the flat text file with a proper database (SQL Server)
- Add transaction operations (deposit / withdraw / transfer)
- Object-Oriented version (OOP) with a dedicated `Client` class and repository layer
- Cross-platform support (remove Windows-only `system()` calls)

---

# 💻 Built With

- C++
- Visual Studio
- Standard Library (`iostream`, `fstream`, `string`, `vector`, `iomanip`)

---

## ⭐ If you like this project, consider giving it a Star!
