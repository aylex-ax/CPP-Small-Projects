
#include <iostream>
using namespace std;

enum enQuestionLivel { EasyLenel = 1, MedLenel = 2, HardLenel = 3 , MixLenel= 5 };
enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, Mix = 5 };





int RandomNumber(int From, int To)
{
	//Seeds the random number generator in C++, called only once
	// #include <cstdlib>
   //srand((unsigned)time(NULL));

	int rendNum = rand() % (To - From + 1) + From;

	return rendNum;
}

short ReadHowManyQuestions()
{
	short NumberOfQuestions;
	do
	{
		
		cout << "How Many Questions Do you Want to ansewr?";
		cin >> NumberOfQuestions;

	} while (NumberOfQuestions <1 || NumberOfQuestions >10);

	return NumberOfQuestions;

}

enQuestionLivel ReadQuestionLivel()
{
	short QuestionLivel;

	do
	{
		cout << "Enter Question Level { (1)Easy (2)Med (3)Hard (5)Mix }";
		cin >> QuestionLivel;

	} while (QuestionLivel < 1 || QuestionLivel >4);

	return (enQuestionLivel)QuestionLivel;
}

enOperationType ReadOpType()
{
	short OpType;

	do
	{
		cout << "Enter ReadOpType  1{+}  2{-}  3{*}  4{/}  5{Mix}";
		cin >> OpType;

	} while (OpType < 1 || OpType >5);

	return (enOperationType)OpType;
}

struct stQuestion
{
	int Num1 = 0;
	int Num2 = 0;
	enQuestionLivel  QuestionLivel;
	enOperationType  OpType;
	int correctAnswer = 0;
	int PlayerAnswer = 0;
	bool AnswerResult = false;

};

struct stQuizz
{
	stQuestion QuestionList[100];
	short NumberOfQuestion;
	enQuestionLivel  QuestionLivel;
	enOperationType  OpType;
	short NumberOfWrongAnswers = 0;
	short NumberOfRightAnswers = 0;
	bool isPass = false;
};

enOperationType GenerateOperationType()
{
	int Op = RandomNumber(1, 4);
	
	return (enOperationType)Op;
}

int SimpleCalculator(int Number1, int Number2, enOperationType	OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return Number1 + Number2;
	case enOperationType::Sub:
		return Number1 - Number2;
	case enOperationType::Mult:
		return Number1 * Number2;
	case enOperationType::Div:
		return Number1 / Number2;
	default:
		return Number1 + Number2;
	}
}

stQuestion GenerateQuestion(enQuestionLivel QuestionLivel , enOperationType OperationType)
{
	stQuestion Question;

	if (QuestionLivel ==enQuestionLivel::MixLenel)
	{
		QuestionLivel = (enQuestionLivel)RandomNumber(1, 3);
	}

	if (OperationType == enOperationType::Mix)
	{
		OperationType = GenerateOperationType();
	}

	Question.OpType = OperationType;

	switch (QuestionLivel)
	{
	case enQuestionLivel::EasyLenel:
		Question.Num1 = RandomNumber(1, 10);
		Question.Num2 = RandomNumber(1, 10);

		Question.correctAnswer = SimpleCalculator(Question.Num1, Question.Num2, Question.OpType);
		Question.QuestionLivel = QuestionLivel;
			
		return Question;

	case  enQuestionLivel::MedLenel:
		Question.Num1 = RandomNumber(10, 50);
		Question.Num2 = RandomNumber(10, 50);

		Question.correctAnswer = SimpleCalculator(Question.Num1, Question.Num2, Question.OpType);
		Question.QuestionLivel = QuestionLivel;

		return Question;


	case  enQuestionLivel::HardLenel:
		Question.Num1 = RandomNumber(50, 100);
		Question.Num2 = RandomNumber(50, 100);

		Question.correctAnswer = SimpleCalculator(Question.Num1, Question.Num2, Question.OpType);
		Question.QuestionLivel = QuestionLivel;

		return Question;

	}
	return Question;


}

string GetOpTypeSymbol(enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return  "+";
	case enOperationType::Sub:
		return  "-";
	case enOperationType::Mult:
		return  "*";
	case enOperationType::Div:
		return  "/";
	default:
		return  "Mix";
	}


}

void GenerateQuizzQuestion(stQuizz& Quizz)
{
	for (short Question = 0;  Question < Quizz.NumberOfQuestion;  Question++)
	{
		Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionLivel, Quizz.OpType);
	}

}



void PrintTheQuestion(stQuizz& Quizz,short QuestiOnNumber)
{
	cout << "\n";
	cout << "Question [" << QuestiOnNumber + 1 << "/" << Quizz.NumberOfQuestion << "]\n\n";
	cout << Quizz.QuestionList[QuestiOnNumber].Num1 << endl;
	cout << Quizz.QuestionList[QuestiOnNumber].Num2 << " ";
	cout << GetOpTypeSymbol(Quizz.QuestionList[QuestiOnNumber].OpType);
	cout << "\n------------" << endl;
}
 
int ReadQuesttionAnswer()
{
	int Answer = 0;
		cin >> Answer;
		return Answer;
}

void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestiOnNumber)
{
	if (Quizz.QuestionList[QuestiOnNumber].PlayerAnswer != Quizz.QuestionList[QuestiOnNumber].correctAnswer)
	{
		Quizz.QuestionList[QuestiOnNumber].AnswerResult = false;
		Quizz.NumberOfWrongAnswers++;

		cout << "Worng Answer :(\n";
		cout << "The right answer is:";
		cout << Quizz.QuestionList[QuestiOnNumber].correctAnswer;
		cout << endl;
	}
	 
	else
	{
		Quizz.QuestionList[QuestiOnNumber].AnswerResult = true;
		Quizz.NumberOfRightAnswers++;

		cout << "Right Answer :)\n";
	}
}

string GetQuestionLevelText(enQuestionLivel QuestionLivel)
{
	string arrQuestionLevelText[4] = { "Easy" , "Med" , "Hard" , "Mix" };
	return arrQuestionLevelText[QuestionLivel - 1];

}


void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
	for (int QuestionOnNumber  = 0; QuestionOnNumber < Quizz.NumberOfQuestion; QuestionOnNumber++)
	{

		PrintTheQuestion(Quizz, QuestionOnNumber);
		Quizz.QuestionList[QuestionOnNumber].PlayerAnswer = ReadQuesttionAnswer();

		CorrectTheQuestionAnswer(Quizz , QuestionOnNumber);


	}
	Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);

}

string GetFinalResultsText(bool Pass)
{
	if (Pass)
		return "PASS :)";
	else
	{
		return "Fail :(";
	}
}

void PrintQuizzResults(stQuizz Quizz)
{
	cout << "\n\n\n\n\n------------------------------\n\n";
	cout << "Final Resuls is " << GetFinalResultsText(Quizz.isPass);
	cout << "\n------------------------------\n\n";

	cout << "Number Of Question: " << Quizz.NumberOfQuestion << endl;
	cout << "Question Level: " << GetQuestionLevelText(Quizz.QuestionLivel) << endl;
	cout << "OpType: "<< GetOpTypeSymbol(Quizz.OpType) << endl;
	cout << "Number Of Right Answers: " << Quizz.NumberOfRightAnswers << endl;
	cout << "Number Of Wrong Answers: " << Quizz.NumberOfWrongAnswers << endl;
	cout << "\n------------------------------\n\n";
}


void PlayMathGame()
{
	stQuizz Quizz;
	Quizz.NumberOfQuestion = ReadHowManyQuestions();
	Quizz.QuestionLivel = ReadQuestionLivel();
	Quizz.OpType = ReadOpType();

	GenerateQuizzQuestion(Quizz);
	AskAndCorrectQuestionListAnswers(Quizz);
	PrintQuizzResults(Quizz);

}




void ResetScreen()
{
	system("cls");
	system("color 0F");

}

void StartGame()
{
	char PlayAgain= 'Y';

	do
	{
		ResetScreen();
		PlayMathGame();

		cout << endl << "Do You went to again?  (Y/N)";
		cin >> PlayAgain;



	} while (PlayAgain == 'Y' || PlayAgain == 'y');




}





int main()
{
	srand((unsigned)time(NULL));
	
	StartGame();

	return 0;
}




