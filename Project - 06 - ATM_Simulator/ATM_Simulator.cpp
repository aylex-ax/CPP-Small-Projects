#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

enum enMainMenu_ATM { eQuickWithdraw = 1, eNormalWithdraw = 2, eDeposit = 3, eCheckBalance = 4, eLogout = 5};


const string File_Clients = "Clients.txt";

struct stClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};

stClient CurrentClient;



void Logen_ATM();
void ShowMainMenue_ATM();
void QuickWithdraw_ATM();


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

stClient ConvertLinetoRecord_ATM(string Line, string Seperator = "#//#")
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

vector<stClient> LoadClientDataFromFile_ATM(string FileName)
{
	vector<stClient> vClient;

	fstream MyFile;
	MyFile.open(FileName, ios::in); //read Mode

	if (MyFile.is_open())
	{
		string Line; //*
		stClient Client;

		while (getline(MyFile, Line))
		{
			Client = ConvertLinetoRecord_ATM(Line);

			vClient.push_back(Client);


		}
		MyFile.close();
	}
	return vClient;
}

bool FindClientByUserNameAndPassword_ATM(string Username, string Password, stClient& Client)
{
	vector<stClient> vClient = LoadClientDataFromFile_ATM(File_Clients);

	for (stClient& C : vClient)
	{
		if (C.AccountNumber == Username && C.PinCode == Password)
		{

			Client = C;
			return true;

		}
	}
	return false;
}

bool LoadClientInfo_ATM(string Username, string Password)
{
	if (FindClientByUserNameAndPassword_ATM(Username, Password, CurrentClient))
		return true;
	else
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

void UpdateClientByAccountNumber_ATM()
{
	vector<stClient> vClient = LoadClientDataFromFile_ATM(File_Clients);
	stClient Client;
	char Ask = 'Y';

	if (FindClientByUserNameAndPassword_ATM(CurrentClient.Name, CurrentClient.PinCode, Client))
	{

	
			for (stClient& c : vClient)
			{
				if (c.AccountNumber == CurrentClient.AccountNumber)
				{
					system("cls");
					c = CurrentClient;
					break;
				}
			}

			SaveCleintsDataToFile(vClient, File_Clients);


	}

}

void UpdateCurrentClientNOM_ATM()
{
	stClient Client;
	FindClientByUserNameAndPassword_ATM(CurrentClient.Name, CurrentClient.PinCode, Client);
	Client = CurrentClient;
}

bool IsWithdrawAmountValid_ATM(int &amount)
{

	while (amount % 5 != 0 || amount > CurrentClient.AccountBalance)
	{
		system("cls");
		cout << "\n        >>  [ Invalid Operation ]  <<";
		cout << "\n  *--------------------------------------------";
		cout << "\n  | You own: " << fixed << setprecision(2) << CurrentClient.AccountBalance;
		cout << "\n  *--------------------------------------------";

		if (amount > CurrentClient.AccountBalance)
		{
			cout << "\n  | There is not that much money! :(";
		}

		if (amount % 5 != 0)
		{
			cout << "  \n|>> Invalid amount! It must be a multiple of 5: ";
		}


		int Chos = 1;
		cout << "\n  *------------------------------------------*";
		cout << "\n  | Enter a valid and continued   |--->[1]   |";
		cout << "\n  |                               |[OR]      |";
		cout << "\n  | Go TO MaIN Menu               |--->[Any] |";
		cout << "\n  *------------------------------------------*";
		cout << "\n  ENTER? ";
		cin >> Chos;
		if (Chos == 1)
		{
			cout << "\n  | Enter a valid ?";
			cin >> amount;
			return true;
		}
		else
		{
			system("cls");
			QuickWithdraw_ATM();
			return false;
		}

	}
	return true;
}

void WithdrawMoney(int amount)
{
	char Ask = 'y';

	if (CurrentClient.AccountBalance >= amount)
	{

		
			cout << "  >> Are you sure about the operation? (Y/N): ";
			cin >> Ask;
			Ask = tolower(Ask);

			if (Ask == 'y')
			{
				CurrentClient.AccountBalance -= amount;
				UpdateClientByAccountNumber_ATM();
				cout << "\n  | Your Mony Balance: " << CurrentClient.AccountBalance;
				return;
			}

			else
			{
				system("cls");
				cout << "\n <==================*============>";
				cout << "\n  |  OK MR Client   |  :)   ";
				cout << "\n <==================*============>";
				return;
			}

	} 
	else
	{

		if (!IsWithdrawAmountValid_ATM(amount)) return;
	}

}

void NormalWithdrawMoney()
{
	int amount;
	cout << "\n   | Enter Number Mony? ";
	cin >> amount;

	if (!IsWithdrawAmountValid_ATM(amount)) return;

		    char Ask = 'y';
			cout << "  >> Are you sure about the operation? (Y/N): ";
			cin >> Ask;
			Ask = tolower(Ask);

			if (Ask == 'y')
			{
				CurrentClient.AccountBalance -= amount;
				UpdateClientByAccountNumber_ATM();
				cout << "\n  | Your Money Balance: " << fixed << setprecision(2) << CurrentClient.AccountBalance;
				return;
			}

			else
			{
				system("cls");
				cout << "\n <==================*============>";
				cout << "\n  |  OK MR Client   |  :)   ";
				cout << "\n <==================*============>";
				return;
			}


	

}






////////////////////////////////////////////////////
// Start
void NormalWithdraw_ATM()
{
	cout << "\n <=*==============================================*=>";
	cout << "\n   | Normal Withdraw :                            |";
	cout << "\n <=*==============================================*=>";
	cout << "\n   | Your Money Balance: [ " << fixed << setprecision(2) << CurrentClient.AccountBalance << " ] :)";
	NormalWithdrawMoney();
}

void QuickWithdraw_ATM()
{
	short NumMony =0;
	cout << "\n <=*==============================================*=>";
	cout << "\n   | Quick Withdraw :                             |";
	cout << "\n <=*==============================================*=>";
	cout << "\n   |..............................................|";
	cout << "\n   |.. [1] 100$      [2] 200$        [3] 500$   ..|";
	cout << "\n   |..                                          ..|";
	cout << "\n   |.. [4] 1,000$    [5] 5,000$      [6] Other  ..|";
	cout << "\n   |..............................................|";
	cout << "\n   | Your Money Balance: " << fixed << setprecision(2) << CurrentClient.AccountBalance<< " :)";
	cout << "\n <=*==============================================*=>";
	cout << "\n  >> ENTER NUMBER ? ";
	cin >> NumMony;

	char Ask = 'y';
	
	switch (NumMony)
	{
	case 1: WithdrawMoney(100); break;
	case 2: WithdrawMoney(200); break;
	case 3: WithdrawMoney(500); break;
	case 4: WithdrawMoney(1000); break;
	case 5: WithdrawMoney(5000); break;
	case 6:NormalWithdrawMoney( ); break;
	default:
		cout << "\nInvalid choice. Please try again.";
		break;
	}



}

void Deposit()
{
	double NumMoney;
	cout << "\n <=*========================================>";
	cout << "\n   | Deposit Your Balanc BRO IS:  " << CurrentClient.AccountBalance << "$  :)";
	cout << "\n <=*========================================>";
	cout << "\n   | Entrr Number Money? ";
		cin >> NumMoney;

		while (NumMoney <= 0)
		{
			cout << "\n   |";
			cout << "\n   | ERROR: Please enter a valid amount greater than 0";
			cout << "\n   | Entrr Number Money? ";
			cin >> NumMoney;
		}



		char Ask = 'y';
		cout << "   >> Are you sure about the operation? (Y/N): ";
		cin >> Ask;
		Ask = tolower(Ask);

		if (Ask == 'y')
		{
			CurrentClient.AccountBalance += NumMoney;
			UpdateClientByAccountNumber_ATM();
			cout << "\n  | Your Money Balance: " << fixed << setprecision(2) << CurrentClient.AccountBalance;
			return;
		}

		else
		{
			system("cls");
			cout << "\n <==================*============>";
			cout << "\n  |  OK MR Client   |  :)   ";
			cout << "\n <==================*============>";
			return;
		}


}

void CheckBalanc_ATM()
{

	cout << "\n <=*========================================>";
	cout << "\n   | Your Balanc BRO IS:  " << CurrentClient.AccountBalance << "$  :)";
	cout << "\n <=*========================================>";

}
////////////////////////////////////////////////////






void GoBackToMenueScreen_ATM()
{
	cout << "\nPress Any Kay To Go Back To Main Menue...!!";
	system("pause>0");
	system("cls");
	ShowMainMenue_ATM();

}

void PrefroMainMenueOption_ATM(enMainMenu_ATM MainMenue)
{
	switch (MainMenue)
	{
	case eQuickWithdraw:
	{
		system("cls");
		QuickWithdraw_ATM();
		GoBackToMenueScreen_ATM();
	}
		break;
	case eNormalWithdraw:
	{
		system("cls");
		NormalWithdraw_ATM();
		GoBackToMenueScreen_ATM();
	}
		break;
	case eDeposit:
	{
		system("cls");
		Deposit();
		GoBackToMenueScreen_ATM();
	}
		break;
	case eCheckBalance:
	{
		system("cls");
		CheckBalanc_ATM();
		GoBackToMenueScreen_ATM();
	}
		break;
	case eLogout:
	{
		system("cls");
		Logen_ATM();
	}
		break;
	default:
		break;
	}
}

short ReadMainMenueOption_ATM()
{
	short Choose = 0;
	cout << "\n  >>>>> Choose Any [1 to 5] ? ";
	cin >> Choose;
	return Choose;
}

void ShowMainMenue_ATM()
{

	cout << "\n   |--->  [ Welcom "<< CurrentClient.Name <<" ]  <---| ";
	cout << "\n <=*====================================*=>";
	cout << "\n   |   >>>  ATM main menu screen  <<<   |";
	cout << "\n <=*====================================*=>";
	cout << "\n   | [1] Quick Withdraw                 |";
	cout << "\n   | [2] Normal Withdraw.               |";
	cout << "\n   | [3] Deposit.                       |";
	cout << "\n   | [4] Check Balance.                 |";
	cout << "\n   | [5] Logout.                        |";
	cout << "\n <=*====================================*=>";
	
	PrefroMainMenueOption_ATM((enMainMenu_ATM)ReadMainMenueOption_ATM());


}

void Logen_ATM()
{
	bool LoginFaild = false;
	string Username, Password;

	do
	{
		system("cls");

		cout << "\n <=*=========================*=>";
		cout << "\n   |>    Login Screen ATM   <|";
		cout << "\n <=*=========================*=>\n";

		if (LoginFaild)
		{
			cout << ">>| Hello Bro >> Enter !!!\n";
		}

		cout << " >| Enter Username?\n";
		cin >> Username;
		cout << " >| Enter password?\n";
		cin >> Password;
		LoginFaild = !LoadClientInfo_ATM(Username, Password);


	} while (LoginFaild);

	system("cls");
	ShowMainMenue_ATM();

}

int main()
{
	Logen_ATM();
	system("pause>0");
	return 0;
}