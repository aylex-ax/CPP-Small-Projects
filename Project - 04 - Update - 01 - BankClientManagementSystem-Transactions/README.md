

<table align="center" width="100%" border="1">
  <tr>
    <td align="center">
      <h2>BankClientManagementSystem — Update 01: Transactions</h2>
    </td>
  </tr>
  <tr>
    <td align="center">
    <img width="1448" height="1086" alt="ChatGPT Image 21 يوليو 2026، 05_49_10 ص" src="https://github.com/user-attachments/assets/e4bd920c-e3c7-482c-b239-00e1d1706e39" />
    </td>
  </tr>
</table>

🔄 **This project is an Update/Extension of [Project - 03 - BankClientManagementSystem](../Project%20-%2003%20-%20BankClientManagementSystem), adding a full Transactions module (Deposit, Withdraw, Total Balances) on top of the original CRUD system.**







A console-based **Bank Client Management System** written in **C++**, extended with a dedicated **Transactions Menu** that allows depositing and withdrawing money from a client's account, in addition to the original client management features (Add / Delete / Update / Find / Show List). All data is still persisted using a local text file (`Clients.txt`), with no database required.

---

# ✨ Features

**Carried over from the base project:**
- 📋 Show a full list of all clients
- ➕ Add one or multiple new clients in a row
- 🗑️ Delete a client by account number (with confirmation)
- ✏️ Update client information (PIN, name, phone, balance)
- 🔍 Find a client by account number
- 💾 Persistent storage using a local text file

**New in this update:**
- 💰 **Deposit** money into a client's account
- 💸 **Withdraw** money from a client's account (blocked if the amount exceeds the balance)
- 📊 **Total Balances** report — displays all clients with their current balances
- 🧭 A separate **Transactions sub-menu**, accessible from the main menu

---

# 🧠 Project Structure

The project keeps the same modular design as the base project, with a new Transactions layer added on top.

### New / Updated Components

| Function | Responsibility |
|----------|----------------|
| `DepositMaenyByAccountBalance()` | Adds a specified amount to a client's balance and saves the file |
| `WithdrawMaenyByAccountBalance()` | Subtracts a specified amount from a client's balance, blocking over-withdrawal |
| `Deposit()` | Handles the full deposit flow (find client → confirm → deposit) |
| `Withdraw()` | Handles the full withdraw flow (find client → confirm → withdraw) |
| `TotalBalances()` | Loads all clients and displays a balances summary table |
| `PrintTotalBalancesClientRecord()` | Displays a single client's balance row |
| `TransactionsMenueScreen()` | Displays the Transactions sub-menu |
| `TransactionsMenueOption()` | Reads and routes the Transactions sub-menu selection |
| `GoBackToTransactionsMenueScreen()` | Returns to the Transactions sub-menu after an operation |
| `MainMenu()` | Returns from the Transactions sub-menu back to the main menu |

> All other components (file handling, client CRUD, main menu) are unchanged from [Project 03](../Project%20-%2003%20-%20BankClientManagementSystem).

---

# ⚙️ Program Flow

```text
Start App
      │
      ▼
Show Main Menu [1–7]
      │
      ├── [1–5] Client CRUD (same as base project)
      │
      ├── [6] Transactions ──► Show Transactions Menu
      │                             │
      │                             ├── [1] Deposit   ──► Find Client ──► Confirm ──► Update Balance
      │                             ├── [2] Withdraw  ──► Find Client ──► Confirm ──► Check Funds ──► Update Balance
      │                             ├── [3] Total Balances ──► Display All Balances
      │                             └── [4] Back to Main Menu
      │
      └── [7] Exit App
```

---

# 🎮 Usage

1. Run the program — the main menu appears with options **[1–7]**.
2. Choose **[6] Transactions** to open the sub-menu:
```
1 → Deposit
2 → Withdraw
3 → Total Balances
4 → Main Menu
```
3. For Deposit/Withdraw: enter the account number, confirm the client, then enter the amount.
4. For Withdraw, if the amount exceeds the balance, you'll be prompted to enter a smaller amount.
5. Choose **[3] Total Balances** to view all clients with their current balances.

---

# 📥 Sample Input

```text
>>>>> Choose Any [1 to 7] ? 6

===========================
 Transactions Menu Screen
===========================
[1] Deposit.
[2] Withdraw.
[3] Total Balances.
[4] Main Menu.
===========================
>>>>> Choose Any [1 to 4] ? 1

| Please enter AccountNumber? 1001
Are you sure about this procedure?(Y/N) Y
| Enter:amount of money? 500
```

---

# 📤 Sample Output

```text
<------------------------------------------>
   >> The following are the client details:
<------------------------------------------>
  | Accout Number: 1001
  | Pin Code : 2580
  | Name : Mostafa Saad
  | Phone : 01012345678
  | Account Balance: 2500
<------------------------------------------>

  >> Done Successfully. New balance is: 3000
```

---

# 🛠️ Concepts Practiced

All concepts from the base project (structs, vectors, file handling, string parsing, pass-by-reference), plus:
- Designing a **sub-menu system** nested inside a main menu
- Validating a monetary operation before committing it (deposit/withdraw confirmation)
- Preventing invalid state (withdrawal amount exceeding balance) with a validation loop
- Extending an existing enum-based menu system (`enTransactionsMenue`) without breaking the original one (`enMenu`)
- Reusing existing search/save functions (`SershForClient`, `SaveCleintsDataToFile`) across a new feature

---

# 💻 How to Run

1. Open the project in **Visual Studio** (or any C++ IDE).
2. Make sure the file includes `<iostream>`, `<fstream>`, `<string>`, `<vector>`, and `<iomanip>`.
3. Build and run the project (`Ctrl + F5` in Visual Studio).
4. On first run, if `Clients.txt` doesn't exist yet, it will be created automatically the first time a client is added.
5. Use the main menu to manage clients, and option **[6] Transactions** to deposit, withdraw, or view total balances.

> ⚠️ Note: `system("cls")` and `system("pause>0")` are Windows-specific and will not work on Linux/macOS terminals.

---

# 📚 What I Learned

During this update I practiced:
- Extending an existing system with a new feature without rewriting the core logic
- Designing a nested menu (main menu → sub-menu) with its own navigation loop
- Handling monetary logic safely (preventing negative balances on withdrawal)
- Reusing and composing existing functions instead of duplicating logic
- Managing two related `enum` types for two separate menu levels

---

# 🐞 Known Issues

- In `Withdraw()`, the printed header still says `"Deposit :"` instead of `"Withdraw :"` (copy-paste leftover from the Deposit function).
- Same issue carried over from Project 03: in `ChangeClientRecord()`, `Client.AccountNumber == AccountNumber;` is a comparison, not an assignment (no practical side effect).
- In `DepositMaenyByAccountBalance()` and `WithdrawMaenyByAccountBalance()`, answering "N" to the confirmation prompt triggers `Show_ClientwithAccountNumber()`, which prints a "Client not found" message even though the client *was* found — the user simply declined the operation. The message is misleading in this case.

---

# 🚀 Future Improvements

- Fix the "Deposit" label bug inside `Withdraw()`
- Fix the comparison-instead-of-assignment issue in `ChangeClientRecord()`
- Replace the misleading "Client not found" message on cancelled transactions with a proper "Operation cancelled" message
- Add a transaction history log per client
- Add input validation (negative amounts, non-numeric input)
- Encrypt or mask the PIN code instead of storing it as plain text
- Replace the flat text file with a proper database (SQL Server)
- Object-Oriented version (OOP) with a dedicated `Client`/`Account` class and repository layer
- Cross-platform support (remove Windows-only `system()` calls)

---

# 💻 Built With

- C++
- Visual Studio
- Standard Library (`iostream`, `fstream`, `string`, `vector`, `iomanip`)

---

## ⭐ If you like this project, consider giving it a Star!
