#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

enum enMenu { eShowClientList = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClientInfo = 4, eFindClient = 5, eExit = 6 };
const string FileName = "Clients.txt";
struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};


void ShowMainMenue();
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

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
	sClient Client;
	vector<string> vClientData;
	vClientData = SplitString(Line, Seperator);

	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]); //cast string to double
	return Client;
}

vector<sClient> LoadCleintsDataFromFile(string FileName)
{
	vector<sClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in); //read Mode

	if (MyFile.is_open())
	{
		string Line; //*
		sClient Client;

		while (getline(MyFile, Line))
		{
			Client = ConvertLinetoRecord(Line);

			vClients.push_back(Client);


		}
		MyFile.close();
	}
	return vClients;
}

void PrintClientRecord(sClient Client)
{
	cout << "  * |" << left << setw(20) << Client.AccountNumber;
	cout << "|" << left << setw(15) << Client.PinCode;
	cout << "|" << left << setw(15) << Client.Name;
	cout << "|" << left << setw(15) << Client.Phone;
	cout << "|" << left << setw(14) << Client.AccountBalance << "*";;
	cout << endl;

}

sClient ReadNewClient()
{
	sClient Client;
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

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{
	string strClientRecord = "";
	strClientRecord += Client.AccountNumber + Seperator;
	strClientRecord += Client.PinCode + Seperator;
	strClientRecord += Client.Name + Seperator;
	strClientRecord += Client.Phone + Seperator;
	strClientRecord += to_string(Client.AccountBalance);
	return strClientRecord;
}


bool SershForClient(string AccountNumber, sClient& Client);
sClient ReadNewOneClient()
{

	sClient Client;
	cout << "  | Enter Account Number? ";
	do
	{
		getline(cin >> ws, Client.AccountNumber);
		if (SershForClient(Client.AccountNumber, Client))
		{
	
			cout << "  | Account already exists! Enter another number: ";
		}
	} while (SershForClient(Client.AccountNumber, Client));

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
	sClient Add = ReadNewOneClient();
	//Sersh(string AccountNumber, sClient & Client)

	AddDataLineToFile(FileName, ConvertRecordToLine(Add, "#//#"));
}

void Show_ClientwithAccountNumber(string AccountNumber)
{
	system("cls");
	cout << "\n <=======================================================================>";
	cout << "\n  | Client with Account Number (" << AccountNumber << ") is Not Found!";
	cout << "\n <=======================================================================>";
}

bool FindClientByAccountNumber(string AccountNumber, sClient& Client, vector <sClient>& vClients)
{

	for (sClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

	for (sClient& c : vClients)
	{
		if (c.AccountNumber == AccountNumber)
		{
			c.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

vector <sClient> SaveCleintsDataToFile(vector <sClient>& vClients, string AccountNumber, string FileName)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);

	string DataLine;
	if (MyFile.is_open())
	{
		for (sClient c : vClients)
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

void PrintClientCard(sClient& Client)
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

bool DeleteClients(vector <sClient>& vClients, string AccountNumber)
{
	sClient Client;
	char Ask = 'Y';

	if (FindClientByAccountNumber(AccountNumber, Client, vClients))
	{
		PrintClientCard(Client);
		cout << "  >> Are you sure you want to delete? (Y/N): ";
		cin >> Ask;

		if (Ask == 'Y' || Ask == 'y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveCleintsDataToFile(vClients, AccountNumber, FileName);
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

sClient ChangeClientRecord(sClient Client, string AccountNumber)
{
	Client.AccountNumber == AccountNumber;
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

bool UpdateClientByAccountNumber(vector <sClient>& vClients, string AccountNumber)
{
	sClient Client;
	char Ask = 'Y';

	if (FindClientByAccountNumber(AccountNumber, Client, vClients))
	{
		PrintClientCard(Client);

		cout << "  >> Are you sure you want to delete? (Y/N): ";
		cin >> Ask;

		if (Ask == 'Y' || Ask == 'y')
		{
			for (sClient& c : vClients)
			{
				if (c.AccountNumber == AccountNumber)
				{
					system("cls");
					c = ChangeClientRecord(c, AccountNumber);
					break;
				}
			}

			SaveCleintsDataToFile(vClients, AccountNumber, FileName);

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

bool SershForClient(string AccountNumber, sClient& Client)
{
	vector <sClient> oneClient = LoadCleintsDataFromFile(FileName);

	for (sClient c : oneClient)
	{
		if (c.AccountNumber == AccountNumber)
		{
			Client = c;
			return true;
		}
	}
	return false;
}

void PrintSersh(sClient Client)
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

void FindClient(vector <sClient>& vClients, string AccountNumber)
{
	sClient Client;
	if (SershForClient(AccountNumber, Client))
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


void ShowClientList()
{
	
	vector<sClient> vClient = LoadCleintsDataFromFile(FileName);
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

	for (sClient s : vClient)
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
	
	
	vector<sClient> vClient = LoadCleintsDataFromFile(FileName);
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

	cout << "\n <==========================================>";
	cout << "\n  | Delete Client:                         |";
	cout << "\n <==========================================>";

	vector<sClient> vClient = LoadCleintsDataFromFile(FileName);
	string AccountNumber = ReadClientAccountNumber();
	system("cls");

	DeleteClients(vClient, AccountNumber);
}

void UpdateClientInfo()
{
	
	vector<sClient> vClient = LoadCleintsDataFromFile(FileName);
	cout << "\n <==========================================>";
	cout << "\n  | Update Client:                         |";
	cout << "\n <==========================================>";

	string AccountNumber = ReadClientAccountNumber();
	system("cls");

	UpdateClientByAccountNumber(vClient, AccountNumber);

}

void FindClient()
{
	
	vector<sClient> vClient = LoadCleintsDataFromFile(FileName);
	
	cout << "\n <==========================================>";
	cout << "\n  |  Find Client:                          |";
	cout << "\n <==========================================>";
	string AccountNumber = ReadClientAccountNumber();
	system("cls");

	FindClient(vClient, AccountNumber);

}

void ExitApp()
{
	

	cout << "\n   <==============================>";
	cout << "\n    |  End App :)                |";
	cout << "\n   <==============================>";

}


void GoBackToHome()
{
	cout << "\nPress Any Kay To Go Back To Main Menue...!!";
	system("pause>0");
	system("cls");
	ShowMainMenue();
}
short ReadMainMenueOption()
{
	short Choose =0;
	cout << "\n  >>>>> Choose Any [1 to 6] ? ";
	cin >> Choose;
	return Choose;
}
void PrefroMainMenueOption(enMenu MainMenue)
{
	switch (MainMenue)
	{
	case eShowClientList:
	{
		system("cls");
		ShowClientList();
		GoBackToHome();
	}
		break;
	case eAddNewClient:
	{
		system("cls");
		AddNewClients();
		GoBackToHome();
	}
		break;
	case eDeleteClient:
	{
		system("cls");
		DeleteClient();
		GoBackToHome();
	}
		break;
	case eUpdateClientInfo:
	{
		system("cls");
		UpdateClientInfo();
		GoBackToHome();
	}
		break;
	case eFindClient:
	{
		system("cls");
		FindClient();	
		GoBackToHome();
	}
		break;
	case eExit:
	{
		system("cls");
		ExitApp();
	}
		break;
	default:
		break;
	}
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
	cout << "\n  | [6] Exit.                            |";
	cout << "\n <========================================>";
	PrefroMainMenueOption((enMenu)ReadMainMenueOption());


}

int main()
{
	ShowMainMenue();
	system("pause>0");
	return 0;
}