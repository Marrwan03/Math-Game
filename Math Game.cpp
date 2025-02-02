#include <iostream>
#include<string>
#include<cmath>
#include<cstdlib>
using namespace std;
enum enQuestionLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };
enum enOperstiontype { Add = 1, sub = 2, Mul = 3, Div = 4, Mixop = 5 };
int RandomNumber(int From, int To) {
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}
string GetQuestionLevelText(enQuestionLevel QuestionLevel)
{
    string ArrQuestionLevel[4] = { "EasyLevel", "MedLevel", "HardLevel", "Mix" };
    return ArrQuestionLevel[QuestionLevel - 1];
}
string GetoperationtypeSymbol(enOperstiontype Operstiontype)
{
    switch (Operstiontype)
    {
    case enOperstiontype::Add:
        return "+";
    case enOperstiontype::sub:
        return "-";
    case enOperstiontype::Mul:
        return "*";
    case enOperstiontype::Div:
        return "/";
    default:
        return "Mix";
    }
}
struct StQuestion {
    int number1;
    int number2;
    enOperstiontype Operstiontype;
    enQuestionLevel QuestionLevel;
    int PlayerAnswer;
    int CorrectAnswer;
    bool AnswerResult;
};
struct StQuizz
{
    StQuestion QuestionList[100];
    int NumberOfQuestions;
    enOperstiontype Optype;
    enQuestionLevel QuestionLevel;
    short NumberOfRightAnswer=0;
    short NumberOfWrongAnswer=0;
    bool IsPass;
};
enQuestionLevel ReadQuestionLevel()
{
    short QuestionLevel;
    do {
        cout << "Enter Question Level [1] EasyLevel, [2] MedLevel, {3] HardLevel, [4] Mix ?" << endl;
        cin >> QuestionLevel;
    } while (QuestionLevel < 1 || QuestionLevel > 4);
    return (enQuestionLevel)QuestionLevel;
}
enOperstiontype ReadOperstiontype()
{
    short Operstiontype;
    do {
        cout << "enter Operstiontype  [1] Add, [2] Sub, {3] Mul, [4] Div [5] Mix ?" << endl;
        cin >> Operstiontype;
    } while (Operstiontype < 1, Operstiontype > 5);
    return (enOperstiontype)Operstiontype;
}
short ReadHowMany()
{
    short NumberOfQuestion;
    do {
        cout << "How Many Question do you want to answer ?" << endl;
        cin >> NumberOfQuestion;
    } while (NumberOfQuestion < 1 || NumberOfQuestion > 10);
    return NumberOfQuestion;
}
int CalCuletarSimply(int number1, int number2, enOperstiontype Operstiontype)
{
    switch (Operstiontype)
    {
    case enOperstiontype::Add:
        return number1 + number2;
    case enOperstiontype::sub:
        return number1 - number2;
    case enOperstiontype::Mul:
        return number1 * number2;
    case enOperstiontype::Div:
        return number1 / number2;
    default:
        return number1 + number2;
    }
}
int ReadPlayerAnswer()
{
    int Answer;
    cin >> Answer;
    return Answer;
}
StQuestion MakeQuestion(enQuestionLevel QuestionLevel, enOperstiontype Operstiontype)
{
    StQuestion Question;
    if (QuestionLevel == enQuestionLevel::Mix)
    {
        QuestionLevel = (enQuestionLevel)RandomNumber(1, 3);
    }
    if (Operstiontype == enOperstiontype::Mixop)
    {
        Operstiontype = (enOperstiontype)RandomNumber(1, 4);
    }
    Question.Operstiontype = Operstiontype;
    switch (QuestionLevel)
    {
    case enQuestionLevel::EasyLevel:
        Question.number1 = RandomNumber(1, 10);
        Question.number2 = RandomNumber(1, 10);
        Question.CorrectAnswer = CalCuletarSimply(Question.number1, Question.number2, Question.Operstiontype);
        Question.QuestionLevel = QuestionLevel;
        return Question;

    case enQuestionLevel::MedLevel:
        Question.number1 = RandomNumber(20, 40);
        Question.number2 = RandomNumber(20, 40);
        Question.CorrectAnswer = CalCuletarSimply(Question.number1, Question.number2, Question.Operstiontype);
        Question.QuestionLevel = QuestionLevel;
        return Question;

    case enQuestionLevel::HardLevel:
        Question.number1 = RandomNumber(50, 100);
        Question.number2 = RandomNumber(50, 100);
        Question.CorrectAnswer = CalCuletarSimply(Question.number1, Question.number2, Question.Operstiontype);
        Question.QuestionLevel = QuestionLevel;
        return Question;
    }
    return Question;
}
void MakeQuestions(StQuizz& Quizz)
{
    for (int i = 0; i < Quizz.NumberOfQuestions; i++) {
        Quizz.QuestionList[i] = MakeQuestion(Quizz.QuestionLevel, Quizz.Optype);
    }
}
void PrintQuestion(StQuizz& Quizz, short QuestionNumber)
{
    cout << "\n-------------------------" << endl;
    cout << "Question [ " << QuestionNumber + 1 << " / " << Quizz.NumberOfQuestions << " ]" << endl;
    cout << Quizz.QuestionList[QuestionNumber].number1 << endl;
    cout << Quizz.QuestionList[QuestionNumber].number2 << " ";
    cout << GetoperationtypeSymbol(Quizz.QuestionList[QuestionNumber].Operstiontype) << endl;
    cout << "-------------------------" << endl;
}
void CorrectAnswer(StQuizz& Quizz, short QuestionNumber)
{
    if (Quizz.QuestionList[QuestionNumber].PlayerAnswer !=
        Quizz.QuestionList[QuestionNumber].CorrectAnswer)
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = false;

        cout << "\nWrong Answer :-(" << endl;
        cout << "The right answer is: " << Quizz.QuestionList[QuestionNumber].CorrectAnswer << endl;
        Quizz.NumberOfWrongAnswer++;
        cout << "\a";
    }
    else
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = true;
        cout << "\nright answer :-) " << endl;
        Quizz.NumberOfRightAnswer++;
    }
}
void AskAndCorrectAnswer(StQuizz& Quizz)
{
    for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
    {
        PrintQuestion(Quizz, QuestionNumber);
        Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadPlayerAnswer();
        CorrectAnswer(Quizz, QuestionNumber);
    }
    Quizz.IsPass = Quizz.NumberOfRightAnswer >= Quizz.NumberOfWrongAnswer;
}
string GetFinalReslut(bool Pass)
{
    if (Pass)
        return "Pass :-)";
    else
        return "Fail :-(";
}
void PrintFinalReslut(StQuizz Quizz)
{
    cout << "-------------------------" << endl;
    cout << "Final Reslut is: " << GetFinalReslut(Quizz.IsPass) << endl;
    cout << "-------------------------" << endl << endl;
    cout << "Number Of Questions : " << Quizz.NumberOfQuestions << endl;
    cout << "Question Level      : " << GetQuestionLevelText(Quizz.QuestionLevel) << endl;
    cout << "Operstion type      : " << GetoperationtypeSymbol(Quizz.Optype) << endl;
    cout << "NumberOfRightAnswer : " << Quizz.NumberOfRightAnswer << endl;
    cout << "NumberOfWrongAnswer : " << Quizz.NumberOfWrongAnswer << endl;
    cout << "--------------------------------------------------" << endl;
}
void PlayMathGame()
{
    StQuizz Quizz;
    Quizz.NumberOfQuestions = ReadHowMany();
    Quizz.QuestionLevel = ReadQuestionLevel();
    Quizz.Optype = ReadOperstiontype();
    MakeQuestions(Quizz);
    AskAndCorrectAnswer(Quizz);
    PrintFinalReslut(Quizz);
}

void StarMathGame()
{
    char PlayAgain = 'Y';
    do {

        PlayMathGame();
        cout << "Do you want PlayAgain? Y/N? " << endl;
        cin >> PlayAgain;
    } while (PlayAgain == 'y' || PlayAgain == 'Y');
}
int main()
{
    srand((unsigned)time(NULL));
    StarMathGame();

    return 0;
}
