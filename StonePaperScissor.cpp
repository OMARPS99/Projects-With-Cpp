#include <iostream>
#include <ctime>
using namespace std;

enum enGameTool { Stone = 1, Paper = 2, Scissor = 3};

string StTypesEnum (enGameTool Number) {

    if (Number == enGameTool::Stone) {
        return "Stone";
    }
    else if (Number == enGameTool::Paper) {
        return "Paper";
    }
    else {
        return "Scissor";
    }
}

short ReadGameRoundsAndChoiceUser (string Message, short From, short To) {

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

bool PlayLogic (enGameTool ChoiceComputer, enGameTool ChoiceUser ) {

    if (enGameTool::Paper == ChoiceComputer && enGameTool::Stone == ChoiceUser) {

        return true;
    }
    else if (enGameTool::Scissor == ChoiceComputer && enGameTool::Paper == ChoiceUser) {

        return true;
    }
    else if (enGameTool::Stone == ChoiceComputer && enGameTool::Scissor == ChoiceUser) {

        return true;
    }
    else {
         

        return false;
    }

}

short PrintResultGame (enGameTool ChoiceComputer, enGameTool ChoiceUser, short Counter) {

    cout << "________Round [" << Counter << "]____________\n\n";
    cout << "Player1 Choice: " << StTypesEnum(ChoiceUser) << endl;
    cout << "Computer Choice: " << StTypesEnum(ChoiceComputer) << endl;

    if (ChoiceComputer == ChoiceUser) {
        // Yellow
        cout << "Round Winner: " << "[No Winner]\n";
        system("color 6F");
        return 0;
    }
    else if (PlayLogic(ChoiceComputer, ChoiceUser)) {
        // Red
        cout << "Round Winner: " << "[Computer]\n\a";
        system("color 4F");
        return 1;
    }
    else {
        // Green
        cout << "Round Winner: " << "[Player1]\n";
        system("color 2F");
        return 2;
    }
    
}

void CounterResult (short Result, short& Player1Won, short& ComputerWon, short& Draw) {

    if (Result == 0) {
        Draw++;
    }
    else if (Result == 1) {
        ComputerWon++;
    }
    else {
        Player1Won++;
    }

}

void PrintFinalResult (short GameRounds, short CounterPlayer1, short CounterComputer, short CounterDraw) {

    string MsgResultWinner = "\0";

    if (CounterPlayer1 < CounterComputer) {
        MsgResultWinner = "Computer";
    }
    else if (CounterPlayer1 == CounterComputer) {
        MsgResultWinner = "No Winner";
    }
    else {
        MsgResultWinner = "Player1";
    }

    cout << "\t\t\t\t\t\t\t___________________________________________\n";
    cout << "\t\t\t\t\t\t\t           +++ G A M E - O V E R +++        \n";
    cout << "\t\t\t\t\t\t\t___________________________________________\n";
    cout << "\t\t\t\t\t\t\t______________[Game Results]_______________\n";
    cout << "\t\t\t\t\t\t\tGame Rounds        : " << GameRounds << endl;
    cout << "\t\t\t\t\t\t\tPlayer1 won times  : " << CounterPlayer1 << endl;
    cout << "\t\t\t\t\t\t\tComputer won times : " << CounterComputer << endl;
    cout << "\t\t\t\t\t\t\tDraw times         : " << CounterDraw << endl;
    cout << "\t\t\t\t\t\t\tFinal Winner       : " << MsgResultWinner << endl;
    cout << "\t\t\t\t\t\t\t___________________________________________\n";


}

void PlayStarted (short GameRounds, short& CounterPlayer1, short& CounterComputer, short& CounterDraw) {

    for (size_t i = 1; i <= GameRounds; i++)
    {
        cout << "Round [" << i << "] begins:\n\n";
        enGameTool ChoiceUser = (enGameTool) ReadGameRoundsAndChoiceUser("Your Choice: [1]:Stone, [2]:Paper, [3]:Scissors ?", 1, 3);
        enGameTool ChoiceComputer = (enGameTool) RandomNumber(1, 3);
        CounterResult(PrintResultGame(ChoiceComputer, ChoiceUser, i), CounterPlayer1, CounterComputer, CounterDraw);
        cout << "______________________________\n\n";
    }
}

int main() {

    srand((unsigned)time(0));
    char PlayAgain = '\0';
    do
    {
        short GameRounds = ReadGameRoundsAndChoiceUser("\nHow Many Rounds 1 to 10 ?", 1, 10);

        short CounterPlayer1 = 0, CounterComputer = 0, CounterDraw = 0;

        PlayStarted(GameRounds, CounterPlayer1, CounterComputer, CounterDraw);
        PrintFinalResult(GameRounds, CounterPlayer1, CounterComputer, CounterDraw);

        cout << "Do you want to play again? Y/N? ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
    
    

    return 0;
}