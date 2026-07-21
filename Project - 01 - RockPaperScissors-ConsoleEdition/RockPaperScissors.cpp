#include <iostream>
using namespace std;

enum enGameChoice { Stone =1 , Paper =2,  Scissor =3};
enum enWinner { Player = 1, computer = 2, Draw = 3 };


struct stRoundinfo 
{
	short RoundNumber =0;
	enGameChoice PleyerChoice ;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName;
};


struct stGameResults
{
	int GameRounds = 0;
	short Player1WinTime = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string WinnerName = "";
		
};


int RandomNumber(int From, int To)
{
	int rendNum = rand() % (To - From + 1) + From;

	return rendNum;
}

short ReadHowManyRounds()
{

	short GameRound=1;

	do
	{
		cout << " How Many Rounds (1) to (10)?";
		cin >> GameRound;

	} while (GameRound <1  ||  GameRound > 10 );

	return GameRound;

}


enGameChoice Choice_Player()
{
	short Choice;

	do
	{

		cout << "\nEnter Choice: (( [1] Stone  ))     ((  [2]Paper  ))     (( [3]Scissor )) ? ";
		cin >> Choice;
		


	} while (Choice <1 || Choice > 3);
	

	return (enGameChoice)Choice;
}
enGameChoice Choice_Computer()
{
	

	return (enGameChoice)RandomNumber(1, 3);

}


enWinner WhoWonTheRound(stRoundinfo RoundInfo)
{
	if (RoundInfo.PleyerChoice == RoundInfo.ComputerChoice )
	{
		return enWinner::Draw;
	}

	switch (RoundInfo.PleyerChoice)
	{
	case enGameChoice::Stone:
		 if (RoundInfo.ComputerChoice==enGameChoice::Paper)
		{
			 return enWinner::computer;
		}
		break;

	case enGameChoice::Paper:
		if (RoundInfo.ComputerChoice == enGameChoice::Scissor)
		{
			return enWinner::computer;
		}
		break;

	case enGameChoice::Scissor:
		if (RoundInfo.ComputerChoice == enGameChoice::Stone)
		{
			return enWinner::computer;
		}
		break;

	}

	return enWinner::Player;

}

string WinnerName(enWinner winner)
{
	string arrWinnerName[3] = { "MR Player", "Mr Computer","It's a Draw" };
	return arrWinnerName[winner - 1];

}

string ChoiceName(enGameChoice choice)
{
	string arrNameChoice[3]{ "ston" ,"Paper","scissors" };
	return arrNameChoice[choice - 1];
}

void PrintRoundGame(stRoundinfo Roundinfo)
{
	cout << "**************************[  Round (" << Roundinfo.RoundNumber << ")  ]********************************** \n";
	cout << "PleyerChoice: " << ChoiceName(Roundinfo.PleyerChoice) << endl;
	cout << "ComputerChoice: " << ChoiceName(Roundinfo.ComputerChoice) << endl;
	cout << "Round Winner: " << Roundinfo.WinnerName << endl;
	cout << "***********************************************"<< endl;

}

enWinner WhoWonTheGame(short Player, short Computer)
{
	if (Player < Computer)
		return enWinner::computer;

	else if (Computer > Player)
		return enWinner::Player;

	else
		return enWinner::Draw;
}

stGameResults FillGameResults(int GameRounds , short Player1WinTimes, short ComputerWinTimes, short DrawTimes)
{
	stGameResults GameResults;

	GameResults.GameRounds= GameRounds;
	GameResults.Player1WinTime= Player1WinTimes;
	GameResults.ComputerWinTimes= ComputerWinTimes;
	GameResults.DrawTimes = DrawTimes;
	GameResults.GameWinner= WhoWonTheGame(Player1WinTimes, ComputerWinTimes);
	GameResults.WinnerName= WinnerName(GameResults.GameWinner);
	
	return GameResults;
}

stGameResults PlayGame( short HowManyRounds)
{
	stRoundinfo RoundInfo;

	short  Player1WinTime = 0, ComputerWinTimes = 0, DrawTimes = 0;

	for (short GameRound = 1 ; GameRound <= HowManyRounds; GameRound++)
	{

		cout << "\nRound [" << GameRound << "] begins:\n";

		RoundInfo.RoundNumber = GameRound;
		RoundInfo.PleyerChoice = Choice_Player();
		RoundInfo.ComputerChoice = Choice_Computer();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		if (RoundInfo.Winner == enWinner::Player)
		{
			Player1WinTime++;
		}
		else if (RoundInfo.Winner == enWinner::computer)
		{
			ComputerWinTimes++;
		}
		if (RoundInfo.Winner == enWinner::Draw)
		{
			DrawTimes++;
		}

		PrintRoundGame(RoundInfo);

	}


	return FillGameResults(HowManyRounds, Player1WinTime, ComputerWinTimes, DrawTimes);

}



void ShowGameOverScreen()
{

	cout << "\n\n****************************************************\n";
	cout << "**********    G-A-M-E    E-N-D-E   *****************\n";
	cout << "****************************************************\n";

}
void showFinalGame(stGameResults GameResults)
{

	cout << "**\n";
	cout << "GameRounds :" << GameResults.GameRounds << endl;
	cout << "MR Player :" << GameResults.Player1WinTime << endl;
	cout << "MR Computer :" << GameResults.ComputerWinTimes << endl;
	cout << "Draw Times :" << GameResults.DrawTimes << endl;
	cout << "Game Winner :" << GameResults.GameWinner << endl;
	cout << "Winner Name :" << GameResults.WinnerName << endl;

}


void StartGame()
{
	char PlayAgain = 'y';

	do
	{
		stGameResults GameResults = PlayGame(ReadHowManyRounds());
		void ShowGameOverScreen();
		showFinalGame(GameResults);

		cout << "Do you want to play again? Y/N? ";
		cin >> PlayAgain;
	} while (PlayAgain == 'y' || PlayAgain == 'Y' );
	


}






int main()
{
	srand((unsigned)time(NULL));
	
	StartGame();

	return 0;
}
