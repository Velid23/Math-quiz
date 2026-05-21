#include <iostream>
#include <cmath>
#include<string>
#include <cstdlib>
#include <ctime>  
#include "myLibrary.h";
using namespace std;

enum QuestionLevel {
	easy = 1, med = 2, hard = 3, levelmix = 4
};
enum OperationType {
	add = 1, sub = 2, mul = 3, diving = 4,operationmix=5

};
enum PassOrNot {
	pass = 1, fall = 2
};
struct GameInfo {
	QuestionLevel level = QuestionLevel::easy;
	OperationType operationtype = OperationType::add;
	int NumberOfQuestions = 0;
	int number1 = 0;
	int number2 = 0;
	int answer = 0;
};
struct GameEnd {
	PassOrNot PassOrFall = PassOrNot::pass;
	int NumberOfRightAnswers = 0;
	int NumberOfWrongAnswers = 0;
};
string PrintLevelName(GameInfo info) {
	string levels[4] = { "easy","mid","hard","mix" };
	return levels[info.level - 1];
}

string PrintOperationType(GameInfo info) {
	string operations[5] = { "+","-","*","/","mix" };
	return operations[info.operationtype - 1];
}



void MixOperation(GameInfo& info) {
	if (info.operationtype == 5) {
		int mix = 0;
		mix= myLibrary::RandomNumberInRange(1, 4);
		switch (mix) {
		case(1):
			info.operationtype = OperationType::add;
			break;
		case(2):
			info.operationtype = OperationType::sub;
			break;
		case(3):
			info.operationtype = OperationType::mul;
			break;
		case(4):
			info.operationtype = OperationType::diving;
			break;
		}
	}
}
void ReadGameStart(GameInfo& info) {
	info.NumberOfQuestions = myLibrary::ReadNumber("How Many Questions do you want to answer ? ");
	info.level = (QuestionLevel)myLibrary::ReadPositiveNumberInRange("Enter Question Level [1] Easy, [2] Med, [3] Hard, [4] Mix ", 1, 4);
	info.operationtype = (OperationType)myLibrary::ReadPositiveNumberInRange("Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ", 1, 5);

}
void Fill2Numbers(GameInfo &info) {
	info.number1 = 0;
	info.number2 = 0;
	switch (info.level) {
	case(QuestionLevel::easy):
		info.number1 = myLibrary::RandomNumberInRange(1, 10);
		info.number2 = myLibrary::RandomNumberInRange(1, 10);
		break;
	case(QuestionLevel::med):
		info.number1 = myLibrary::RandomNumberInRange(10, 100);
		info.number2 = myLibrary::RandomNumberInRange(10, 100);
		break;
	case(QuestionLevel::hard):
		info.number1 = myLibrary::RandomNumberInRange(100, 1000);
		info.number2 = myLibrary::RandomNumberInRange(100, 1000);
		break;
	case(QuestionLevel::levelmix):
		info.number1 =myLibrary::RandomNumberInRange(1, 1000);
		info.number2 =myLibrary::RandomNumberInRange(1, 1000);
		break;
	}

}

bool IsRightAnswer(GameInfo &info) {

	switch (info.operationtype) {
	case(OperationType::add):
		if (info.number1 + info.number2 == info.answer) {
			return 1;
		}
		return 0;
	case(OperationType::sub):
		if (info.number1<=info.number2 && info.answer==0) {
			return 1;
		}
		else if (info.number1 > info.number2 && info.number1-info.number2==info.answer) {
			return 1;
		}
		return 0;
	case(OperationType::mul):
		if (info.number1 * info.number2 == info.answer) {
			return 1;
		}
		return 0;
	case(OperationType::diving):
		if (info.number1 / info.number2 ==info.answer) {
			return 1;
		}
		return 0;
	}

}
int ReturnRightAnswer(GameInfo& info) {

	switch (info.operationtype) {
	case(OperationType::add):
		return info.number1 + info.number2;
		break;
	case(OperationType::sub):
		return info.number1 - info.number2;
		break;
	case(OperationType::mul):
		return info.number1 * info.number2;
		break;
	case(OperationType::diving):
		return info.number1 / info.number2;
		break;
	}
	
}


GameEnd FillGameEndInfo(GameEnd& endinfo,GameInfo& gameinfo, int rightanswers, int wronganswers) {
	endinfo.NumberOfRightAnswers = rightanswers;
	endinfo.NumberOfWrongAnswers = wronganswers;
	if (endinfo.NumberOfRightAnswers > endinfo.NumberOfWrongAnswers) {
		endinfo.PassOrFall = PassOrNot::pass;
		system("color 2F");

	}
	else {
		endinfo.PassOrFall = PassOrNot::fall;
		system("color 4F");

	}
	return endinfo;
}
string PrintPassOrFall(GameEnd info) {
	string passorfail[2] = { "PASS","FAIL" };

	return passorfail[info.PassOrFall - 1];
}
GameEnd IfOperationMix(GameInfo& info, GameEnd& endinfo) {
	int rightanswers = 0, wronganswers = 0;

	for (int i = 1; i <= info.NumberOfQuestions; i++) {
		info.operationtype =(OperationType)myLibrary::RandomNumberInRange(1, 4);
		Fill2Numbers(info);			
		cout << "\n\nQuestion [" << i << "/" << info.NumberOfQuestions << "]\n" << endl;
		cout << info.number1 << endl;
		cout << info.number2 << PrintOperationType(info) << endl;
		cout << "-------------" << endl;
		info.answer = myLibrary::ReadNumber("");
		if (IsRightAnswer(info)) {
			cout << "Right Answer :-)\n\n" << endl;
			rightanswers++;
			system("color 2F");
		}
		else {
			cout << "Wrong Answer" << endl;
			cout << "the right answer is : " << ReturnRightAnswer(info) << "\n\n";
			wronganswers++;
			system("color 4F");

		}
		
	}
	info.operationtype = (OperationType)5;
	return FillGameEndInfo(endinfo, info, rightanswers, wronganswers);
}
GameEnd PrintQuestions(GameInfo &info,GameEnd& endinfo) {
	int rightanswers = 0, wronganswers = 0;

	for (int i = 1; i <= info.NumberOfQuestions; i++) {
		if (info.operationtype == 5) {
			MixOperation(info);
		}
		Fill2Numbers(info);
		cout << "\n\nQuestion [" << i << "/" << info.NumberOfQuestions << "]\n" << endl;
		cout << info.number1 << endl;
		cout << info.number2 << PrintOperationType(info) << endl;
		cout << "-------------" << endl;
		info.answer = myLibrary::ReadNumber("");
		if (IsRightAnswer(info)) {
			cout << "Right Answer :-)\n\n";
			rightanswers++;
			system("color 2F");

		}
		else {
			cout << "Wrong Answer" << endl;
			cout << "the right answer is : " << ReturnRightAnswer(info) << "\n\n";
			wronganswers++;
			system("color 4F");

		}

	}

	return FillGameEndInfo(endinfo,info, rightanswers, wronganswers);
}
void FinalResult(GameEnd endinfo) {
	cout << "--------------------------" << endl;
	cout << "Final Result is : " << PrintPassOrFall(endinfo) << endl;
	cout << "--------------------------" << endl;

}
void PrintGameEnd(GameInfo gameinfo, GameEnd endinfo) {

	cout << "Number Of Questions:    " << gameinfo.NumberOfQuestions << endl;
	cout << "Question Level:         " << PrintLevelName(gameinfo) << endl;
	cout << "OpType:                 " << PrintOperationType(gameinfo) << endl;
	cout << "Number Of Right Answers:" << endinfo.NumberOfRightAnswers << endl;
	cout << "Number Of Wrong Answers:" << endinfo.NumberOfWrongAnswers << endl;
	cout << "---------------------------------------" << endl;

}

bool AskToPlayAgain() {
	char YesNo = 'y';
	cout << "Do you want to play again? Y/N:";
	cin >> YesNo;
	if (YesNo == 'y' || YesNo == 'Y') {
		return 1;
	}
	else {
		return 0;
	}
}
void PlayGame() {
	do{
		system("color 0F");
		system("cls");
		GameInfo gameinfo;
		GameEnd gameend;
		 ReadGameStart(gameinfo);
		 if(gameinfo.operationtype==5){
			 gameend = IfOperationMix(gameinfo, gameend);
		 }
		 else {
			 gameend = PrintQuestions(gameinfo, gameend);
		 }
		FinalResult(gameend);
		PrintGameEnd(gameinfo, gameend);
	} while (AskToPlayAgain());

}

int main() {
	srand((unsigned)time(NULL));

	PlayGame();

	return 0;
}



//teacher abouhadhoud code

//#include <iostream>  
//#include <cstdlib>   
//#include <ctime>     
//using namespace std; 


//enum enQuestionsLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };
//
//enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };
//
//int RandomNumber(int From, int To)
//{
//	return rand() % (To - From + 1) + From;
//}
//
//string GetOpTypeSymbol(enOperationType OpType)
//{
//	switch (OpType)
//	{
//	case enOperationType::Add:
//		return "+";
//	case enOperationType::Sub:
//		return "-";
//	case enOperationType::Mult:
//		return "x";
//	case enOperationType::Div:
//		return "/";
//	default:
//		return "Mix";
//	}
//}
//
//
//enOperationType GetRandomOperationType()
//{
//	return (enOperationType)RandomNumber(1, 4);
//}
// 
//int ReadQuestionNumber() {
//	int number = 0;
//	cout << "how many question do you want to answer";
//	cin >> number;
//	return number;
//}
//int ReadNumberInRange(string message,int from,int to) {
//int number = 0;
//	do {
//	cout << message;
//	cin >> number;
//	} while (number<from||number>to);
//	
//	return number;
//}
//string GetQuestionLevelText(enQuestionsLevel QuestionLevel)
//{
//	string arrQuestionLevelText[4] = { "Easy","Medium","Hard","Mixed" };
//	return arrQuestionLevelText[QuestionLevel - 1];
//}
//
//
//
//void SetScreenColor(bool Right)
//{
//	if (Right)
//		system("color 2F");  
//	else
//	{
//		system("color 4F");  
//		cout << "\a";  
//	}
//}
// 
//int SimpleCalculator(int Number1, int Number2, enOperationType OpType)
//{
//	switch (OpType)
//	{
//	case enOperationType::Add:
//		return Number1 + Number2;
//	case enOperationType::Sub:
//		return Number1 - Number2;
//	case enOperationType::Mult:
//		return Number1 * Number2;
//	case enOperationType::Div:
//		return (Number2 != 0) ? (Number1 / Number2) : 0;   
//	default:
//		return Number1 + Number2;
//	}
//}
//
//
//struct stQuestion
//{
//	int Number1 = 0;
//	int Number2 = 0;
//	enOperationType OperationType=enOperationType::Add;
//	enQuestionsLevel QuestionLevel=enQuestionsLevel::EasyLevel;
//	int CorrectAnswer = 0;
//	int PlayerAnswer = 0;
//	bool AnswerResult = false;
//};
//
//struct stQuizz
//{
//	stQuestion QuestionList[100];
//	short NumberOfQuestions=0;
//	enQuestionsLevel QuestionsLevel=enQuestionsLevel::EasyLevel;
//	enOperationType OpType= enOperationType::Add;
//	short NumberOfWrongAnswers = 0;
//	short NumberOfRightAnswers = 0;
//	bool isPass = false;
//};
//
//
//stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enOperationType OpType)
//{
//	stQuestion Question;
//
//	if (QuestionLevel == enQuestionsLevel::Mix)
//		QuestionLevel = (enQuestionsLevel)RandomNumber(1, 3);
//
//	if (OpType == enOperationType::MixOp)
//		OpType = GetRandomOperationType();
//
//	Question.OperationType = OpType;
//
//	switch (QuestionLevel)
//	{
//	case enQuestionsLevel::EasyLevel:
//		Question.Number1 = RandomNumber(1, 10);
//		Question.Number2 = RandomNumber(1, 10);
//		break;
//	case enQuestionsLevel::MedLevel:
//		Question.Number1 = RandomNumber(10, 50);
//		Question.Number2 = RandomNumber(10, 50);
//		break;
//	case enQuestionsLevel::HardLevel:
//		Question.Number1 = RandomNumber(50, 100);
//		Question.Number2 = RandomNumber(50, 100);
//		break;
//	}
//
//	Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
//	Question.QuestionLevel = QuestionLevel;
//
//	return Question;
//}
//
//
//void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
//{
//	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
//	{
//		cout << "\nQuestion [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]\n";
//		cout << Quizz.QuestionList[QuestionNumber].Number1 << " "
//			<< GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType) << " "
//			<< Quizz.QuestionList[QuestionNumber].Number2 << " = ";
//
//		cin >> Quizz.QuestionList[QuestionNumber].PlayerAnswer;
//
//		if (Quizz.QuestionList[QuestionNumber].PlayerAnswer == Quizz.QuestionList[QuestionNumber].CorrectAnswer)
//		{
//			cout << "Correct!\n";
//			Quizz.NumberOfRightAnswers++;
//		}
//		else
//		{
//			cout << "Wrong! Correct Answer: " << Quizz.QuestionList[QuestionNumber].CorrectAnswer << endl;
//			Quizz.NumberOfWrongAnswers++;
//		}
//	}
//
//	Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
//}
//
//void PlayMathGame()
//{
//	stQuizz Quizz;
//	Quizz.NumberOfQuestions =ReadQuestionNumber(); 
//	Quizz.QuestionsLevel =(enQuestionsLevel) ReadNumberInRange("enter the level you want:",1,4);
//	Quizz.OpType = (enOperationType)ReadNumberInRange("enter the operation you want:", 1, 5);
//
//	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
//	{
//		Quizz.QuestionList[QuestionNumber] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OpType);
//	}
//
//	AskAndCorrectQuestionListAnswers(Quizz);
//
//	cout << "\nQuiz Completed! Right Answers: " << Quizz.NumberOfRightAnswers
//		<< ", Wrong Answers: " << Quizz.NumberOfWrongAnswers << "\n";
//
//	cout << (Quizz.isPass ? "You Passed the Quiz!\n" : "You Failed the Quiz!\n");
//}
//int main()
//{
//	srand((unsigned)time(NULL)); 
//	PlayMathGame(); 
//	return 0; 
//}