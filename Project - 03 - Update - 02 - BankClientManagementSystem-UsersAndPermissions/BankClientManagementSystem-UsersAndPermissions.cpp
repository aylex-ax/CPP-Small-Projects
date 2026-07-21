#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

enum enMainMenu { eShowClientList = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClientInfo = 4, eFindClient = 5, eTransactions = 6, ManageUsers =7 ,eExit = 8 };

enum enTransactionsMenue { eDeposit = 1, eWithdraw = 2, eTotalBalances = 3, eMainMenu = 4 };

enum enUsersMenue { eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5 , eMainMenue = 6};

enum enMainMenuePermissions{eALL =-1 , pListClient = 1, pAddNewClient = 2, pDeleteClient = 4, pUpdateClientInfo = 8, pFindClient = 16,pTransactions = 32, pManageUsers = 64 };

const string File_Clients = "Clients.txt";
const string File_UserName = "User.txt";
struct stClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};
struct stUser
{
	string Name;
	string Password;
	int Permissions;
	bool MarkForDelete = false;
};


stUser CurrentUser;

void GoBackToTransactionsMenueScreen();
void TransactionsMenueScreen();
void ShowMainMenue();
void ShowUserMenue();
void Logen();


void showAccessDeniedMessage()
{
	cout << "\n<=*========================================*=>";
	cout << "\n  | You do not have access >> GO BACK |";
	cout << "\n<=*========================================*=>";
}

bool CheckAccessPermission(enMainMenuePermissions Permission)
{
	if (CurrentUser.Permissions == enMainMenuePermissions::eALL)
		return true;

	if ((Permission & CurrentUser.Permissions) == Permission)
		return true;
	else
		return false;
}

vector<string> SplitString(string S1, string Delim)
{

	vector<string> vString;

	short pos = 0;
	string sWord; // define a string variable

	// use find() function to get the position of the delimiters
	while ((pos = S1.find(Delim)) != std::string::npos)
	{
		sWord = S1.substr(0, pos); // store the word
		if (sWord != "")
		{
			vString.push_back(sWord);
		}
		S1.erase(0, pos + Delim.length());
	}
	if (S1 != "")
	{
		vString.push_back(S1); // it adds last word of the string.
	}
	return vString;
}

stClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
	stClient Client;
	vector<string> vClientData;
	vClientData = SplitString(Line, Seperator);

	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]); //cast string to double
	return Client;
}

vector<stClient> LoadCleintsDataFromFile(string FileName)
{
	vector<stClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in); //read Mode

	if (MyFile.is_open())
	{
		string Line; //*
		stClient Client;

		while (getline(MyFile, Line))
		{
			Client = ConvertLinetoRecord(Line);

			vClients.push_back(Client);


		}
		MyFile.close();
	}
	return vClients;
}

void PrintClientRecord(stClient Client)
{
	cout << "  * |" << left << setw(20) << Client.AccountNumber;
	cout << "|" << left << setw(15) << Client.PinCode;
	cout << "|" << left << setw(15) << Client.Name;
	cout << "|" << left << setw(15) << Client.Phone;
	cout << "|" << left << setw(14) << Client.AccountBalance << "*";;
	cout << endl;

}

stClient ReadNewOneClient()
{
	stClient Client;
	cout << "Enter Account Number? ";
	getline(cin, Client.AccountNumber);
	cout << "Enter PinCode? ";
	getline(cin, Client.PinCode);
	cout << "Enter Name? ";
	getline(cin, Client.Name);
	cout << "Enter Phone? ";
	getline(cin, Client.Phone);
	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;
	return Client;
}

string ConvertRecordToLine(stClient Client, string Seperator = "#//#")
{
	string strClientRecord = "";
	strClientRecord += Client.AccountNumber + Seperator;
	strClientRecord += Client.PinCode + Seperator;
	strClientRecord += Client.Name + Seperator;
	strClientRecord += Client.Phone + Seperator;
	strClientRecord += to_string(Client.AccountBalance);
	return strClientRecord;
}


bool SearchForClient(string AccountNumber, stClient& Client);
stClient ReadNewClient()
{

	stClient Client;
	cout << "  | Enter Account Number? ";
	do
	{
		getline(cin >> ws, Client.AccountNumber);
		if (SearchForClient(Client.AccountNumber, Client))
		{

			cout << "  | Account already exists! Enter another number: ";
		}
	} while (SearchForClient(Client.AccountNumber, Client));

	cout << "  | Enter PinCode? ";
	getline(cin, Client.PinCode);
	cout << "  | Enter Name? ";
	getline(cin, Client.Name);
	cout << "  | Enter Phone? ";
	getline(cin, Client.Phone);
	cout << "  | Enter AccountBalance? ";
	cin >> Client.AccountBalance;
	return Client;
}

void AddDataLineToFile(string FilName, string sLineData)
{

	fstream MyFile;
	MyFile.open(FilName, ios::out | ios::app);

	if (MyFile.is_open())
	{
		MyFile << sLineData << endl;
		MyFile.close();
		cout << "\n    *-------------------------*----";
		cout << "\n    | Name saved successfully | :) ";
		cout << "\n    *-------------------------*----";
	}
	else
	{
		cout << "\n    *------------------------------*----";
		cout << "\n    | Dont Name saved successfully | :( ";
		cout << "\n    *------------------------------*----";

	}


}

void AddOneClint()
{
	stClient Add = ReadNewClient();
	//Sersh(string AccountNumber, sClient & Client)

	AddDataLineToFile(File_Clients, ConvertRecordToLine(Add, "#//#"));
}

void Show_ClientwithAccountNumber(string AccountNumber)
{
	system("cls");
	cout << "\n <=======================================================================>";
	cout << "\n  | Client with Account Number (" << AccountNumber << ") is Not Found!";
	cout << "\n <=======================================================================>";
}

bool FindClientByAccountNumber(string AccountNumber, stClient& Client, vector <stClient>& vClients)
{

	for (stClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <stClient>& vClients)
{

	for (stClient& c : vClients)
	{
		if (c.AccountNumber == AccountNumber)
		{
			c.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

vector <stClient> SaveCleintsDataToFile(vector <stClient>& vClients, string FileName)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);

	string DataLine;
	if (MyFile.is_open())
	{
		for (stClient c : vClients)
		{
			if (c.MarkForDelete == false)
			{
				DataLine = ConvertRecordToLine(c);
				MyFile << DataLine << endl;
			}

		}
		MyFile.close();
		cout << "\n    *-------------------------*----";
		cout << "\n    | Successful attempt      | :) ";
		cout << "\n    *-------------------------*----";

	}
	return vClients;
}

void PrintClientCard(stClient& Client)
{

	cout << "\n <------------------------------------------>";
	cout << "\n   >> The following are the client details:";
	cout << "\n <------------------------------------------>";
	cout << "\n  | Accout Number: " << Client.AccountNumber;
	cout << "\n  | Pin Code : " << Client.PinCode;
	cout << "\n  | Name : " << Client.Name;
	cout << "\n  | Phone : " << Client.Phone;
	cout << "\n  | Account Balance: " << Client.AccountBalance;
	cout << "\n <------------------------------------------>\n";
}

bool DeleteClients(vector <stClient>& vClients, string AccountNumber)
{
	stClient Client;
	char Ask = 'Y';

	if (FindClientByAccountNumber(AccountNumber, Client, vClients))
	{
		PrintClientCard(Client);
		cout << "  >> Are you sure you want to delete? (Y/N): ";
		cin >> Ask;

		if (Ask == 'Y' || Ask == 'y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveCleintsDataToFile(vClients, File_Clients);
			return true;
		}
		else
		{
			system("cls");
			cout << "\n <==================*============>";
			cout << "\n  | AOK MR Client   |  :)   ";
			cout << "\n <==================*============>";

		}

	}
	else
	{
		Show_ClientwithAccountNumber(AccountNumber);
		return false;
	}
}

stClient ChangeClientRecord(stClient Client, string AccountNumber)
{
	Client.AccountNumber = AccountNumber;
	cout << "\n <==========================================>\n";
	cout << "  | Enter Update PinCode: ";
	getline(cin >> ws, Client.PinCode);
	cout << "  | Enter Update Name: ";
	getline(cin, Client.Name);
	cout << "  | Enter Update Phone: ";
	getline(cin, Client.Phone);
	cout << "  | Enter Update Account Balance: ";
	cin >> Client.AccountBalance;
	cout << " <==========================================>\n";
	return Client;
}

bool UpdateClientByAccountNumber(vector <stClient>& vClients, string AccountNumber)
{
	stClient Client;
	char Ask = 'Y';

	if (FindClientByAccountNumber(AccountNumber, Client, vClients))
	{
		PrintClientCard(Client);

		cout << "  >> Are you sure you want to update? (Y/N): ";
		cin >> Ask;

		if (Ask == 'Y' || Ask == 'y')
		{
			for (stClient& c : vClients)
			{
				if (c.AccountNumber == AccountNumber)
				{
					system("cls");
					c = ChangeClientRecord(c, AccountNumber);
					break;
				}
			}

			SaveCleintsDataToFile(vClients, File_Clients);

			return true;
		}

		else
		{
			system("cls");
			cout << "\n <==================*============>";
			cout << "\n  |  OK MR Client   |  :)   ";
			cout << "\n <==================*============>";
		}

	}
	else
	{
		Show_ClientwithAccountNumber(AccountNumber);
		return false;
	}
}

bool SearchForClient(string AccountNumber, stClient& Client)
{
	vector <stClient> oneClient = LoadCleintsDataFromFile(File_Clients);

	for (stClient c : oneClient)
	{
		if (c.AccountNumber == AccountNumber)
		{
			Client = c;
			return true;
		}
	}
	return false;
}

void PrintSersh(stClient Client)
{
	cout << "\n---------------------------------------";
	cout << "\nThe following are the client details:";
	cout << "\n---------------------------------------";
	cout << "\nAccout Number: " << Client.AccountNumber;
	cout << "\nPin Code : " << Client.PinCode;
	cout << "\nName : " << Client.Name;
	cout << "\nPhone : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;
	cout << "\n---------------------------------------";
	cout << "\nSuccessful attempt";
	cout << "\n---------------------------------------";
}

void FindClient(vector <stClient>& vClients, string AccountNumber)
{
	stClient Client;
	if (SearchForClient(AccountNumber, Client))
	{
		PrintSersh(Client);
	}
	else
	{
		Show_ClientwithAccountNumber(AccountNumber);
	}


}

string ReadClientAccountNumber()
{
	string AccountNumber = "";
	cout << "\n  | Please enter AccountNumber? ";
	cin >> AccountNumber;
	return AccountNumber;
}

int EnterNumberClint()
{
	int NumberClint = 6;
	cout << "\nPlease enter AccountNumber? ";
	cin >> NumberClint;
	return NumberClint;
}

bool DepositMaenyByAccountBalance(vector <stClient>& vClients, double Amount, string AccountNumber)
{
	char choose = 'y';
	cout << "Are you sure about this procedure?(Y/N) ";
	cin >> choose;

	if (choose == 'Y' || choose == 'y')
	{
		for (stClient& C : vClients)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance += Amount;
				SaveCleintsDataToFile(vClients, File_Clients);
				cout << "\n\n  >> Done Successfully. New balance is: " << C.AccountBalance;
				return true;

			}

		}

	}
	else
	{
		Show_ClientwithAccountNumber(AccountNumber);
		return false;
	}
	return false;
}

bool WithdrawMaenyByAccountBalance(vector <stClient>& vClients, double Amount, string AccountNumber)
{
	char choose = 'y';
	cout << "Are you sure about this procedure?(Y/N) ";
	cin >> choose;

	if (choose == 'Y' || choose == 'y')
	{
		for (stClient& C : vClients)
		{
			if (C.AccountNumber == AccountNumber)
			{
				while (Amount > C.AccountBalance)
				{
					cout << "The money you want is more than your account( " << C.AccountBalance << " ) :Entar >>";
					cin >> Amount;
				}

				C.AccountBalance -= Amount;
				SaveCleintsDataToFile(vClients, File_Clients);
				cout << "\n\n  >> Done Successfully. New balance is: " << C.AccountBalance;
				return true;
			}


		}


	}
	else
	{
		Show_ClientwithAccountNumber(AccountNumber);
		return false;
	}

	return false;
}



//Interface elements (_1_)
void ShowClientList()
{
	if (!CheckAccessPermission(enMainMenuePermissions::pListClient))
	{
		showAccessDeniedMessage();
		return;
	}

	vector<stClient> vClient = LoadCleintsDataFromFile(File_Clients);
	cout << "                              .^^^^^^^^^^^^^^^^^^^^^^^^. \n";
	cout << "                             |  Mr Aylex Private Bank   |\n";
	cout << "  ***************************************************************************************\n";
	cout << "  |-------------------------------------------------------------------------------------|\n";
	cout << "  |----------------------------[  Welcom Iam Aylex ]------------------------------------|\n";
	cout << "  |--------- /\\\\---------------[   This is my Bank ]------------ \\\\ // -----------------|\n";
	cout << "  |-------  //_\\\\ -------------[>> customers Is(" << vClient.size() << ") ]------------  //   ----------------|\n";
	cout << "  |------- //   \\\\----------------------------------------------  // \\\\   --------------|\n";
	cout << "  |-------------------------------------------------------------------------------------|\n";
	cout << "  | . .. .  .  . .  ..   ..  .  . .   . .  . . . .   .   .   .   . . .    .  .   .  .   |\n";
	cout << "  |   . . .  .   .   .   .    .    .   .  .    .   .   .   .   .   .  .   .   .   . .  .|\n";
	cout << "  *=====================================================================================*\n";
	cout << "  * |" << left << setw(20) << "AccountNumber";
	cout << "|" << left << setw(15) << "PinCode";
	cout << "|" << left << setw(15) << "Name";
	cout << "|" << left << setw(15) << "Phone";
	cout << "|" << left << setw(14) << "AccountBalance" << "*";
	cout << "\n  *=====================================================================================*\n";

	for (stClient s : vClient)
	{
		PrintClientRecord(s);

	}

	cout << "\n  *=====================================================================================*\n";

	cout << "\n\n\n\n   *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^* \n";
	cout << "  | Note >> (0_0)                                                                    |\n";
	cout << "   *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^* \n";
	cout << "  |Mr Aylex has a vast amount of money that no single bank can handle,               |\n";
	cout << "  |so he established his own private banks to store his wealth.                      |\n";
	cout << "  |He also allowed a select few exceptional individuals to conduct                   |\n";
	cout << "  |transactions with his exclusive banks. That makes you one of the lucky ones now.  |\n";
	cout << "  |Be careful—Mr.Aylex is extremely dangerous.Beware!                                |\n";
	cout << "   *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^* \n";
}

void AddNewClients()
{
	if (!CheckAccessPermission(enMainMenuePermissions::pAddNewClient))
	{
		showAccessDeniedMessage();
		return;
	}

	vector<stClient> vClient = LoadCleintsDataFromFile(File_Clients);

	char Ch = 'Y';

	do
	{
		system("cls");
		cout << "\n <==========================================>";
		cout << "\n  | Enter Data:                            |";
		cout << "\n <==========================================>\n";

		AddOneClint();

		cout << "\n  <==========================================>";
		cout << "\n>> Do you want to add a client? (Y OR N): \n";
		cin >> Ch;
	} while (toupper(Ch) == 'Y');

}

void DeleteClient()
{
	if (!CheckAccessPermission(enMainMenuePermissions::pDeleteClient))
	{
		showAccessDeniedMessage();
		return;
	}

	cout << "\n <==========================================>";
	cout << "\n  | Delete Client:                         |";
	cout << "\n <==========================================>";

	vector<stClient> vClient = LoadCleintsDataFromFile(File_Clients);
	string AccountNumber = ReadClientAccountNumber();
	system("cls");

	DeleteClients(vClient, AccountNumber);
}

void UpdateClientInfo()
{
	if (!CheckAccessPermission(enMainMenuePermissions::pUpdateClientInfo))
	{
		showAccessDeniedMessage();
		return;
	}
	vector<stClient> vClient = LoadCleintsDataFromFile(File_Clients);
	cout << "\n <==========================================>";
	cout << "\n  | Update Client:                         |";
	cout << "\n <==========================================>";

	string AccountNumber = ReadClientAccountNumber();
	system("cls");

	UpdateClientByAccountNumber(vClient, AccountNumber);

}

void FindClient()
{
	if (!CheckAccessPermission(enMainMenuePermissions::pFindClient))
	{
		showAccessDeniedMessage();
		return;
	}
	vector<stClient> vClient = LoadCleintsDataFromFile(File_Clients);

	cout << "\n <==========================================>";
	cout << "\n  |  Find Client:                          |";
	cout << "\n <==========================================>";
	string AccountNumber = ReadClientAccountNumber();
	system("cls");

	FindClient(vClient, AccountNumber);

}

void Logout()
{

	Logen();

}

void PrintTotalBalancesClientRecord(stClient Client)
{
	cout << "\n  |" << left << setw(20) << Client.AccountNumber;
	cout << "|" << left << setw(20) << Client.Name;
	cout << "|" << left << setw(20) << Client.AccountBalance;

}


//Interface elements (_2_)
void Deposit()
{
	stClient Client;
	vector<stClient> vClients = LoadCleintsDataFromFile(File_Clients);
	cout << "\n <==========================================>";
	cout << "\n  | Deposit :                         |";
	cout << "\n <==========================================>";
	string AccountNumber = ReadClientAccountNumber();

	while (!SearchForClient(AccountNumber, Client))
	{
		cout << "\n  | Username not found, try again? ";
		AccountNumber = ReadClientAccountNumber();
	}
	system("cls");
	PrintClientCard(Client);

	double Amount = 0;
	cout << "\n  | Enter:amount of money? ";
	cin >> Amount;
	DepositMaenyByAccountBalance(vClients, Amount, AccountNumber);

}

void Withdraw()
{
	stClient Client;
	vector<stClient> vClients = LoadCleintsDataFromFile(File_Clients);

	cout << "\n <=*===============================*==>";
	cout << "\n   | Withdraw  :                   |";
	cout << "\n <=*===============================*==>";
	string AccountNumber = ReadClientAccountNumber();

	while (!SearchForClient(AccountNumber, Client))
	{
		cout << "\n  | Username not found, try again? ";
		AccountNumber = ReadClientAccountNumber();
	}

	PrintClientCard(Client);

	double Amount = 0;
	cout << "\n  | Enter:amount of money? ";
	cin >> Amount;

	WithdrawMaenyByAccountBalance(vClients, Amount, AccountNumber);

}

void TotalBalances()
{
	vector<stClient> vClients = LoadCleintsDataFromFile(File_Clients);
	cout << "\n\t\tBalances List [" << vClients.size() << "]";
	cout << "\n  ======================================================================";
	cout << "\n  |" << left << setw(20) << "Account Number";
	cout << "|" << left << setw(20) << "Client Name";
	cout << "|" << left << setw(20) << "Balance  |";
	cout << "\n  ======================================================================";

	for (stClient c : vClients)
	{
		PrintTotalBalancesClientRecord(c);
	}

}

void MainMenu()
{

	ShowMainMenue();
}

void GoBackToMainMenue()
{
	cout << "\nPress Any Kay To Go Back To Main Menue...!!";
	system("pause>0");
	system("cls");
	ShowMainMenue();
}

short ReadMainMenueOption()
{
	short Choose = 0;
	cout << "\n  >>>>> Choose Any [1 to 6] ? ";
	cin >> Choose;
	return Choose;
}

void GoBackToTransactionsMenueScreen()
{
	cout << "\nPress Any Kay To Go Back To Main Menue...!!";
	system("pause>0");
	system("cls");
	TransactionsMenueScreen();

}

short TransactionsMenueOption()
{
	short Choose = 0;
	cout << "\n  >>>>> Choose Any [1 to 4] ? ";
	cin >> Choose;
	return Choose;
}

//Addddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd



stUser ConvertLinetoRecordUser(string Line, string Seperator = "#//#")
{
	stUser User;
	vector<string> vUserData;
	vUserData = SplitString(Line, Seperator);

	User.Name = vUserData[0];
	User.Password = vUserData[1];
	User.Permissions = std::stoi(vUserData[2]);
	
	return User;
}

vector<stUser> LoadUserDataFromFile(string FileName)
{
	vector<stUser> vUser;

	fstream MyFile;
	MyFile.open(FileName, ios::in); //read Mode

	if (MyFile.is_open())
	{
		string Line; //*
		stUser User;

		while (getline(MyFile, Line))
		{
			User = ConvertLinetoRecordUser( Line);

			vUser.push_back(User);


		}
		MyFile.close();
	}
	return vUser;
}

bool FindUserByUserNameAndPassword(string Username, string Password, stUser & User)
{
	vector<stUser> vUser = LoadUserDataFromFile(File_UserName);

	for (stUser& U : vUser)
	{
		if (U.Name == Username && U.Password == Password)
		{
		
			User = U;
			return true;
			
		}
	}
	return false;
}

bool LoadUserInfo(string Username, string Password)
{
	if (FindUserByUserNameAndPassword(Username, Password, CurrentUser))
		return true;
	else
		return false;
}

int ReadPermissionsToSet()
{
	int Permissions = 0;
	char Answer = 'n';

	cout << "Do You Want To Give Full access? Y/N >> ";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y') {
		return -1; 
	}

	cout << "Do You Want To Give access To :\n";

	cout << "Show Client List? Y/N";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y') {
		Permissions |= enMainMenuePermissions::pListClient; // ✅
	}

	cout << "Add New Client? Y/N";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y') {
		Permissions |= enMainMenuePermissions::pAddNewClient; // ✅
	}

	cout << "Delete Client? Y/N";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y') {
		Permissions |= enMainMenuePermissions::pDeleteClient; // ✅
	}

	cout << "Update Client Info? Y/N";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y') {
		Permissions |= enMainMenuePermissions::pUpdateClientInfo; // ✅
	}

	cout << "Find Client? Y/N";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y') {
		Permissions |= enMainMenuePermissions::pFindClient; // ✅
	}

	cout << "Transactions? Y/N";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y') {
		Permissions |= enMainMenuePermissions::pTransactions; // ✅
	}

	cout << "Manage Users? Y/N";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y') {
		Permissions |= enMainMenuePermissions::pManageUsers; // ✅
	}

	return Permissions;
}

void PrintTotalUser(stUser User)
{
	cout << "\n  |" << left << setw(20) << User.Name;
	cout << "|" << left << setw(20) << User.Password;
	cout << "|" << left << setw(20) << User.Permissions;

}

bool SearchUser(string Username)
{
	vector<stUser> vUser = LoadUserDataFromFile(File_UserName);

	for (stUser& C : vUser)
	{
		if (C.Name == Username)
		{

			return true;

		}
	}
	return false;
}

stUser ReadNewOneUser()
{

	stUser User;
	cout << "  | Enter Name User? ";
	do
	{
		getline(cin >> ws, User.Name);
		if (SearchUser(User.Name))
		{
			cout << "  | Account already exists! Enter another number: ";
		}
	} while (SearchUser(User.Name));

	cout << "  | Enter Password? ";
	cin >> User.Password;
	
	User.Permissions = ReadPermissionsToSet();



	return User;
}

string ConvertRecordUserToLine(stUser User, string Seperator = "#//#")
{
	string strClientRecord = ""; //All String

	strClientRecord += User.Name + Seperator;
	strClientRecord += User.Password + Seperator;
	strClientRecord += to_string(User.Permissions);
	
	return strClientRecord;
}

void AddOneUser()
{
	stUser Add = ReadNewOneUser();
	//Sersh(string AccountNumber, sClient & Client)

	AddDataLineToFile(File_UserName, ConvertRecordUserToLine(Add, "#//#"));
	
}

string ReadUserName()
{
	string UserName = "";
	cout << "\n  | Please enter UserName? ";
	cin >> UserName;
	return UserName;
}
  
bool FindUserByAccountNumber(string UserName, stUser& User, vector <stUser>& vUser)
{

	for (stUser& C : vUser)
	{
		if (C.Name == UserName)
		{
			User = C;
			return true;
		}
	}
	return false;
}

void PrintUserCard(stUser& User)
{

	cout << "\n <------------------------------------------>";
	cout << "\n   >> The following are the client details:";
	cout << "\n <------------------------------------------>";
	cout << "\n  | Accout Name: " << User.Name;
	cout << "\n  | Password : " << User.Password;
	cout << "\n  | Permissions : " << User.Permissions;
	cout << "\n <------------------------------------------>\n";
}

bool MarkUserForDeleteByUserName(string UserName, vector <stUser>& vUser)
{

	for (stUser& c : vUser)
	{
		if (c.Name == UserName)
		{
			c.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

vector <stUser> SaveUsersDataToFile(vector <stUser>& vUser, string FileName)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);

	string DataLine;
	if (MyFile.is_open())
	{
		for (stUser c : vUser)
		{
			if (c.MarkForDelete == false)
			{
				DataLine = ConvertRecordUserToLine(c);
				MyFile << DataLine << endl;
			}

		}
		MyFile.close();
		cout << "\n    *-------------------------*----";
		cout << "\n    | Successful attempt      | :) ";
		cout << "\n    *-------------------------*----";

	}
	return vUser;
}

bool DeleteUser(vector <stUser>& vUser, string UserName)
{
	stUser User;
	char Ask = 'Y';

	if (FindUserByAccountNumber( UserName, User, vUser))
	{
		PrintUserCard(User);
		cout << "  >> Are you sure you want to delete? (Y/N): ";
		cin >> Ask;

		if (Ask == 'Y' || Ask == 'y')
		{
			MarkUserForDeleteByUserName(UserName, vUser);
			SaveUsersDataToFile(vUser, File_UserName);
			return true;
		}
		else
		{
			system("cls");
			cout << "\n <==================*============>";
			cout << "\n  | AOK MR Client   |  :)   ";
			cout << "\n <==================*============>";

		}

	}
	else
	{
		Show_ClientwithAccountNumber(UserName);
		return false;
	}
}

stUser ChangeUserRecord(stUser User, string UserName)
{
	User.Name = UserName;
	cout << "\n <==========================================>\n";
	cout << "  | Enter Update Password: ";
	 cin >> User.Password;
	cout << " <==========================================>\n";
	return User;
}

bool UpdateClientByAccountNumber( string UserName , vector <stUser>& vUser)
{
	stUser User;
	char Ask = 'Y';

	if (FindUserByAccountNumber(UserName, User, vUser))
	{
		PrintUserCard(User);

		cout << "  >> Are you sure you want to Update? (Y/N): ";
		cin >> Ask;

		if (Ask == 'Y' || Ask == 'y')
		{
			for (stUser& c : vUser)
			{
				if (c.Name == UserName)
				{
					system("cls");
					c = ChangeUserRecord( User,  UserName);
					break;
				}
			}

			SaveUsersDataToFile(vUser, File_UserName);

			return true;
		}

		else
		{
			system("cls");
			cout << "\n <==================*============>";
			cout << "\n  |  OK MR Client   |  :)   ";
			cout << "\n <==================*============>";
		}

	}
	else
	{
		Show_ClientwithAccountNumber(UserName);
		return false;
	}
}

bool SearchFor_User(vector<stUser> &vUser , string Username , stUser& User)
{
	

	for (stUser& C : vUser)
	{
		if (C.Name == Username)
		{
			User = C;
			return true;

		}
	}
	return false;
}

void PrintUserSersh(stUser User)
{
	cout << "\n <==========================================>";
	cout << "\n  | The following are the User details:";
	cout << "\n <==========================================>";
	cout << "\n  | Accout Name: " << User.Name;
	cout << "\n  | Password : " << User.Password;
	cout << "\n  | Permissions : " << User.Permissions;
	cout << "\n <==========================================>";
	cout << "\n  | Successful attempt";
	cout << "\n <==========================================>";
}

void FindUserClient(vector <stUser>& vUser, string Username)
{
	stUser User;
	if (SearchFor_User(vUser,Username, User))
	{
		PrintUserSersh( User);
	}
	else
	{
		Show_ClientwithAccountNumber(Username);
	}

}



//user////////////////////////////////////
void ShowListUSERS()
{
	

	vector<stUser> vUser = LoadUserDataFromFile(File_UserName);

	cout << "\n\t\tBalances List [" << vUser.size() << "]";
	cout << "\n  ======================================================================";
	cout << "\n  |" << left << setw(20) << "Account Number";
	cout << "|" << left << setw(20) << "Client Name";
	cout << "|" << left << setw(20) << "Balance  |";
	cout << "\n  ======================================================================";

	for (stUser c : vUser)
	{
		PrintTotalUser(c);
	}
}

void AddNewUSRES()
{
	//vector<stUser> vUser = LoadUserDataFromFile(File_User);

	char Ch = 'Y';

	do
	{
		system("cls");
		cout << "\n <==========================================>";
		cout << "\n  | Enter Data:                            |";
		cout << "\n <==========================================>\n";

		AddOneUser();

		cout << "\n  <==========================================>";
		cout << "\n>> Do you want to add a User? (Y OR N): \n";
		cin >> Ch;
	} while (toupper(Ch) == 'Y');
}

void DeleteUSERS()
{

	cout << "\n <==========================================>";
	cout << "\n  | Delete Client:                         |";
	cout << "\n <==========================================>";

	vector<stUser> vUser = LoadUserDataFromFile(File_UserName);
	string UserName = ReadUserName();
	system("cls");

	DeleteUser(vUser, UserName);
}

void UpdateUSERSInfo()
{

	vector<stUser> vUser = LoadUserDataFromFile(File_UserName);
	cout << "\n <==========================================>";
	cout << "\n  | Update Users:                         |";
	cout << "\n <==========================================>";

	string UserName = ReadUserName();
	system("cls");

	UpdateClientByAccountNumber(UserName,vUser);

}

void FindUsers()
{

	vector<stUser> vUser = LoadUserDataFromFile(File_UserName);

	cout << "\n <==========================================>";
	cout << "\n  |  Find User:                          |";
	cout << "\n <==========================================>";
	string UserName = ReadUserName();
	system("cls");

	FindUserClient(vUser, UserName);

}
////////////////////////////////////////

void GoBackToUserMenue()
{
		cout << "\nPress Any Kay To Go Back To Main Menue...!!";
		system("pause>0");
		system("cls");
	    ShowUserMenue();
}

void PrefroUserMenueOption(enUsersMenue enUsersMenue)
{
	switch (enUsersMenue)
	{
	case eListUsers:
	{
		system("cls");
		ShowListUSERS();
		GoBackToUserMenue();
	}

		break;


	case eAddNewUser:
	{
		system("cls");
		AddNewUSRES();
		GoBackToUserMenue();
	}

		break;


	case eDeleteUser:
	{
		system("cls");
		DeleteUSERS();
		GoBackToUserMenue();
	}
		break;


	case eUpdateUser:
	{
		system("cls");
		UpdateUSERSInfo();
		GoBackToUserMenue();
	}
		break;


	case eFindUser:
	{
		system("cls");
		FindUsers();
		GoBackToUserMenue();
	}
		break;


	case eMainMenue:
	{
		system("cls");
		ShowMainMenue();
		GoBackToUserMenue();
	}
		break;

	default:
		break;
	}

}

short ReadUserMenueOption()
{
	short Choose = 0;
	cout << "\n  >>>>> Choose Any [1 to 6] ? ";
	cin >> Choose;
	return Choose;
}

void ShowUserMenue()
{
	if (!CheckAccessPermission(enMainMenuePermissions::pManageUsers))
	{
		showAccessDeniedMessage();
		return;
	}

	cout << "\n <========================================>";
	cout << "\n  | Manage (Users) Menue Screen          |";
	cout << "\n <========================================>";
	cout << "\n  | [1] List Users.                      |";
	cout << "\n  | [2] Add New User.                    |";
	cout << "\n  | [3] Delete User.                     |";
	cout << "\n  | [4] Update User.                     |";
	cout << "\n  | [5] Find User.                       |";
	cout << "\n  | [6] Main Menue.                      |";
	cout << "\n <========================================>";
	
	PrefroUserMenueOption((enUsersMenue)ReadUserMenueOption());
}

void Logen()
{
	bool LoginFaild = false;
	string Username , Password;

	do
	{
		system("cls");

		cout << "\n <========================================>";
		cout << "\n  | Login Screen                         |";
		cout << "\n <========================================>\n";
		
		if (LoginFaild)
		{
			cout << ">>| Invalid Username or Password, Try Again!\n";
		}

		cout << " >| Enter Username?\n";
		cin >> Username;
		cout << " >| Enter password?\n";
		cin >> Password;
		LoginFaild =!LoadUserInfo(Username, Password);


	} while (LoginFaild);

	system("cls");
	ShowMainMenue();

}
//Endddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd



void TransactionsMenueOption(enTransactionsMenue TransactionsMenue)
{
	switch (TransactionsMenue)
	{
	case eDeposit:
	{

		system("cls");
		Deposit();
		GoBackToTransactionsMenueScreen();
	}
	break;

	case eWithdraw:
	{
		system("cls");
		Withdraw();
		GoBackToTransactionsMenueScreen();
	}
	break;

	case eTotalBalances:
	{
		system("cls");
		TotalBalances();
		GoBackToTransactionsMenueScreen();
	}
	break;

	case eMainMenu:
	{
		system("cls");
		MainMenu();
	}
	break;

	default:
		break;
	}
}

void PrefroMainMenueOption(enMainMenu MainMenue)
{
	switch (MainMenue)
	{
	case enMainMenu::eShowClientList:
	{
		system("cls");
		ShowClientList();
		GoBackToMainMenue();
	}
	break;
	case enMainMenu::eAddNewClient:
	{
		system("cls");
		AddNewClients();
		GoBackToMainMenue();
	}
	break;
	case enMainMenu::eDeleteClient:
	{
		system("cls");
		DeleteClient();
		GoBackToMainMenue();
	}
	break;
	case enMainMenu::eUpdateClientInfo:
	{
		system("cls");
		UpdateClientInfo();
		GoBackToMainMenue();
	}
	break;
	case enMainMenu::eFindClient:
	{
		system("cls");
		FindClient();
		GoBackToMainMenue();
	}
	break;
	case enMainMenu::eTransactions:
	{
		system("cls");
		TransactionsMenueScreen();
	}
	break;
	case enMainMenu::ManageUsers :
	{
		system("cls");
		ShowUserMenue();
	}
	break;
	case enMainMenu::eExit:
	{
		system("cls");
		Logout();
	}
	break;
	default:
		break;
	}
}

void TransactionsMenueScreen()
{
	if (!CheckAccessPermission(enMainMenuePermissions::pTransactions))
	{
		showAccessDeniedMessage();
		return;
	}
	cout << "===========================" << endl;
	cout << " Transactions Menu Screen  " << endl;
	cout << "===========================" << endl;
	cout << "[1] Deposit." << endl;
	cout << "[2] Withdraw." << endl;
	cout << "[3] Total Balances." << endl;
	cout << "[4] Main Menu." << endl;
	cout << "===========================" << endl;
	TransactionsMenueOption((enTransactionsMenue)TransactionsMenueOption());

}

void ShowMainMenue()
{

	cout << "\n <========================================>";
	cout << "\n  | Main Menue Screen                    |";
	cout << "\n <========================================>";
	cout << "\n  | [1] Show Client List.                |";
	cout << "\n  | [2] Add New Client.                  |";
	cout << "\n  | [3] Delete Client.                   |";
	cout << "\n  | [4] Update Client Info.              |";
	cout << "\n  | [5] Find Client.                     |";
	cout << "\n  | [6] Transactions.                    |";
	cout << "\n  | [7] Manage Users.                    |";
	cout << "\n  | [8] Logout.                          |";
	cout << "\n <========================================>";
	PrefroMainMenueOption((enMainMenu)ReadMainMenueOption());


}



int main()
{
	Logen();
	system("pause>0");
	return 0;
}