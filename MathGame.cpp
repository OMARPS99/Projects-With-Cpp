#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;

enum enQuestionsLevel { Easy = 1,  Med = 2,  Hard = 3,  MixLevel = 4 };

enum enQuestionsType    { Add  = 1,  Sub = 2,  Mul = 3,  Div = 4,  MixType = 5 };

struct stQuestionsOperator
{
    short Number1 = 0;
    short Number2 = 0;
    short Result = 0;
    char MathSymbol = '\0';
};

short GetNumber (short From, short To, string Message) {

    short Number;
    do {

        cout << Message << endl;
        cin >> Number;
    } while (Number < From || Number > To);
    return Number;
}

short RandomNumber (short From, short To) {

    return rand()% (To - From + 1) + From;
}

string switchEnumToString (enQuestionsLevel QuestionsLevel, enQuestionsType QuestionsType, bool condition) {

    if (condition) {
        switch (QuestionsLevel)
        {
            case enQuestionsLevel::Easy:
                return "Easy";
            case enQuestionsLevel::Med :
                return "Med";
            case enQuestionsLevel::Hard :
                return "Hard";
            case enQuestionsLevel:: MixLevel:
                return "Mix";
        }
    }
    else {
        switch (QuestionsType)
        {
            case enQuestionsType::Add :
                return "Add";
            case enQuestionsType::Div :
                return "Div";
            case enQuestionsType::Mul :
                return "Mul";
            case enQuestionsType::Sub :
                return "Sub";
            case enQuestionsType::MixType :
                return "Mix";
        }
    }
    return "\0";

}

stQuestionsOperator CalculationProcess (short Number1, short Number2, enQuestionsType QuestionsType) {

    stQuestionsOperator QuestionsOperator;

    switch (QuestionsType)
    {
        case enQuestionsType::Add :
            QuestionsOperator.Number1 = Number1,
            QuestionsOperator.Number2 = Number2,
            QuestionsOperator.MathSymbol = '+',
            QuestionsOperator.Result = Number1 + Number2;
            break;

        case enQuestionsType::Div :
            QuestionsOperator.Number1 = Number1,
            QuestionsOperator.Number2 = Number2,
            QuestionsOperator.MathSymbol = '/',
            QuestionsOperator.Result = (short) round((float) Number1 / (float) Number2);
            break;

        case enQuestionsType::Mul :
            QuestionsOperator.Number1 = Number1,
            QuestionsOperator.Number2 = Number2,
            QuestionsOperator.MathSymbol = '*',
            QuestionsOperator.Result = Number1 * Number2;
            break;

        case enQuestionsType::Sub :
            QuestionsOperator.Number1 = Number1,
            QuestionsOperator.Number2 = Number2,
            QuestionsOperator.MathSymbol = '-',
            QuestionsOperator.Result = Number1 - Number2;
            break;
                 
        case enQuestionsType::MixType :
            return CalculationProcess(Number1, Number2, (enQuestionsType) RandomNumber(1, 4));

    }
    return QuestionsOperator;
}

stQuestionsOperator QuestionsProcess (enQuestionsLevel QuestionsLevel, enQuestionsType QuestionsType) {

        switch (QuestionsLevel)
        {
        case enQuestionsLevel::Easy :
            return CalculationProcess(RandomNumber(1, 10), RandomNumber(1, 10), QuestionsType);

        case enQuestionsLevel::Med :
            return CalculationProcess(RandomNumber(10, 30), RandomNumber(10, 30), QuestionsType);

        case enQuestionsLevel::Hard :
            return CalculationProcess(RandomNumber(20, 50), RandomNumber(20, 50), QuestionsType);

        case enQuestionsLevel::MixLevel :
            return QuestionsProcess((enQuestionsLevel) RandomNumber(1, 3), QuestionsType);

        }
        return CalculationProcess(RandomNumber(1, 50), RandomNumber(1, 50), QuestionsType);
}

void PrintFinalResult (short NumberOfQuestions, short WrongAnswersCounter, short RightAnswersCounter,
enQuestionsLevel QuestionsLevel, enQuestionsType QuestionsType) {

    string StResult = "PASS :-)";
    if (WrongAnswersCounter >  RightAnswersCounter)
        StResult = "Fail :-(";
    
    cout << "________________________________________\n\n";
    cout << "\tFinal Result is " << StResult << "\n";
    cout << "________________________________________\n\n";
    cout << "Number of RightAnswers: " << RightAnswersCounter << "\n";
    cout << "Number of WrongAnswers: " << WrongAnswersCounter << "\n";
    cout << "Number of Questions   : " << NumberOfQuestions << "\n";
    cout << "Questions Level       : " << switchEnumToString(QuestionsLevel, QuestionsType, 1) << "\n";
    cout << "Math Symbol           : " << switchEnumToString(QuestionsLevel, QuestionsType, 0) << "\n";
    cout << "________________________________________\n\n";

    

}

void StartPlay (short NumberOfQuestions, short& WrongAnswersCounter, short& RightAnswersCounter,
 enQuestionsLevel QuestionsLevel, enQuestionsType QuestionsType) {

    short answer = 0;
    for (size_t i = 1; i <= NumberOfQuestions; i++)
    {
        stQuestionsOperator QuestionsOperator = QuestionsProcess(QuestionsLevel, QuestionsType);
        cout << "Questions [" << i << "/" << NumberOfQuestions << "]\n";

        cout << QuestionsOperator.Number1 << endl;
        cout << QuestionsOperator.Number2 << " " << QuestionsOperator.MathSymbol << "\n_________\n";
        cin >> answer;
        if (answer == QuestionsOperator.Result ) {
            cout << "Right Answer :-)\n\n";
            RightAnswersCounter++;

        }
        else {
            cout << "\nWrong Answer :-(\nThe right answer is: " << QuestionsOperator.Result << "\n\n";
            WrongAnswersCounter++;
        }
    }
    PrintFinalResult(NumberOfQuestions, WrongAnswersCounter, RightAnswersCounter, QuestionsLevel, QuestionsType);
}

void ResetScreen() {

    system("cls");
    system("color 0F");
}

int main() {

    srand((unsigned)time(0));
    
    char PlayAgain = '\0';
    do
    {
        ResetScreen();
        short NumberOfQuestions = GetNumber(1, 50, "How Many Questions do you to answer ? ");
        enQuestionsLevel QuestionsLevel = (enQuestionsLevel) GetNumber(1, 4, "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ");
        enQuestionsType QuestionsType = (enQuestionsType) GetNumber(1, 5, "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ");

        short RightAnswersCounter = 0, WrongAnswersCounter = 0;
        StartPlay(NumberOfQuestions, WrongAnswersCounter, RightAnswersCounter, QuestionsLevel, QuestionsType);

        cout << "Do you want to play again Y/N? ";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
    

    return 0;
}