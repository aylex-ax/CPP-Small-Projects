<table align="center" width="100%" border="1">
  <tr>
    <td align="center">
      <h2>BankClientManagementSystem-UsersAndPermissions</h2>
    </td>
  </tr>
  <tr>
    <td align="center">
<img width="1536" height="1024" alt="345" src="https://github.com/user-attachments/assets/b0109290-34f9-44ab-9a80-f886bb1b1d60" />
    </td>
  </tr>
</table>








> 🔄 This project is **Update 02** on [Project - 03 - BankClientManagementSystem](https://github.com/mostafa-000/CPP-Small-Projects/tree/main/Project%20-%2003%20-%20BankClientManagementSystem), adding a full **Login System** and **User Permissions Management** module on top of the original bank client management system.

---

## 📌 Description

An extension of the Bank Client Management System that introduces multi-user access control. Instead of anyone running the program freely, users now log in with a username and password, and each user's actions are restricted based on a set of assigned permissions (view clients, add, delete, update, search, transactions, and user management itself).

---

## ✨ Features

- Secure login screen with repeated attempts until valid credentials are entered
- Permission-based access control using bitwise flags (`enMainMenuePermissions`)
- Full **Manage Users** menu: list, add, delete, update, and find users
- Granular permission assignment when creating a new user (Y/N per feature, or full access)
- Every main menu action checks the current user's permission before executing
- Persistent user storage in a separate `User.txt` file
- Reuses and extends the original Deposit / Withdraw / Total Balances transaction system

---

## 🗂️ Project Structure

| Function | Responsibility |
|---|---|
| `Logen()` | Handles the login loop until valid credentials are provided |
| `LoadUserInfo()` / `FindUserByUserNameAndPassword()` | Validates login credentials against `User.txt` |
| `CheckAccessPermission()` | Checks if the current user has permission for a given action |
| `ReadPermissionsToSet()` | Interactively builds a permission bitmask when adding a new user |
| `ShowUserMenue()` / `PrefroUserMenueOption()` | Displays and routes the Manage Users menu |
| `AddOneUser()` / `ReadNewOneUser()` | Adds a new user with name, password, and permissions |
| `DeleteUser()` / `UpdateClientByAccountNumber(string, vector<stUser>&)` | Deletes or updates an existing user |
| `FindUserClient()` / `SearchFor_User()` | Searches for a user by username |
| `ShowListUSERS()` | Lists all registered users |
| `ConvertLinetoRecordUser()` / `ConvertRecordUserToLine()` | Converts between file lines and `stUser` records |

---

## 🔁 Program Flow

1. Program starts and immediately shows the **Login Screen**.
2. User enters username and password; the program keeps retrying until valid credentials are found in `User.txt`.
3. On success, the **Main Menu** is shown, now including a new option: **Manage Users**.
4. Every main menu option first checks the logged-in user's permissions via `CheckAccessPermission()`. If denied, an access-denied message is shown and the action is blocked.
5. Inside **Manage Users**, an authorized user can list, add, delete, update, or search users, and assign permissions individually or grant full access.
6. Logout returns back to the Login Screen.

---

## 🕹️ Gameplay

Not applicable — this is a menu-driven business application, not a game.

---

## 💻 Sample Input

```
>| Enter Username?
admin
>| Enter password?
1234

>>>>> Choose Any [1 to 8] ? 7

  >>>>> Choose Any [1 to 6] ? 2
  | Enter Data:
  | Enter Name User? mostafa
  | Enter Password? pass123
Do You Want To Give Full access? Y/N >> N
Show Client List? Y/N Y
Add New Client? Y/N N
```

---

## 🖥️ Sample Output

```
<========================================>
  | Manage (Users) Menue Screen          |
<========================================>
  | [1] List Users.                      |
  | [2] Add New User.                    |
  | [3] Delete User.                     |
  | [4] Update User.                     |
  | [5] Find User.                       |
  | [6] Main Menue.                      |
<========================================>

    *-------------------------*----
    | Name saved successfully | :) 
    *-------------------------*----
```

---

## 🧠 Concepts Practiced

- Structs (`stUser`, `stClient`)
- Enums and bitwise permission flags
- File handling with `fstream` (read/write/append)
- Function overloading
- Pass-by-reference vs pass-by-value
- Menu-driven program design with switch statements
- Access control logic (authentication vs authorization)

---

## ▶️ How to Run

1. Open the project in Visual Studio (or any C++ IDE).
2. Build and run the project.
3. On first run, make sure a `User.txt` file exists in the same directory with at least one valid user record, otherwise login will always fail.
4. Log in using a username and password from `User.txt`, then navigate the menu.

---

## 📚 What I Learned

- How to design a simple authentication system using file-based storage
- How to represent multiple permissions in a single integer using bitwise OR (`|=`) and AND (`&`)
- The difference between checking "is logged in" (authentication) and "is allowed to do this" (authorization)
- How overloading a function with different parameter types can help reuse similar logic, and the naming risks that come with it

---

## ⚠️ Known Issues

- Several functions (`DeleteClients()`, `UpdateClientByAccountNumber()` for both clients and users, `DeleteUser()`) are missing a `return` statement on the "answered No" path, which can lead to undefined behavior since the function is declared to return a `bool`.
- Two different functions share the name `UpdateClientByAccountNumber()` — one updates a `stClient`, the other updates a `stUser`. The shared name is misleading since they operate on different data types.
- `EnterNumberClint()` is defined but never called anywhere in the program (dead code).
- `ChangeUserRecord()` only allows updating the password; there is no way to update a user's permissions after creation.
- Passwords are stored as plain text in `User.txt` with no encryption or hashing.

---

## 🚀 Future Improvements

- Add proper `return` statements on all code paths in `bool` functions
- Rename the overloaded `UpdateClientByAccountNumber()` for users to something like `UpdateUserByUserName()`
- Allow editing a user's permissions after creation
- Hash passwords before storing them in the file
- Remove unused/dead code such as `EnterNumberClint()`

---

## 🛠️ Built With

- C++
- Standard Library: `iostream`, `fstream`, `string`, `vector`, `iomanip`

---

⭐ If you found this project useful, consider giving the repo a star!
