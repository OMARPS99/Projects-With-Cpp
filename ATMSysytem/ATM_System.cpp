#pragma warning(disable : 4996)

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include<iomanip>
#include <ctime>
#include <limits>

using namespace std;

void Login ();
void OperationCenter ();

//      Begin Data Type           //

enum eAppOption { eQuickWithdraw = 1, eNormalWithdraw = 2, eDeposit = 3, eCheckBalance = 4, eShowClientData = 5,
eAccountTransactions = 6, eLogOut = 7};

struct stClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    short OperationsNumber;
};

struct stTransactions
{
    string AccountNumber;
    string MovementType;
    int Amount;
    double Balance;
    string Date;
    string Time;
};

//      End Data Type             //

/* ------------------------------ */

//     Begin Global Variables     //

const string ClientsFile = "ClientsAccount.txt";
const string TransactionsFile = "Transactions.txt";

// Total Number Transactions To be Saved For Each Client
const short  MaxTransactions = 10;

// Number of Transactions To be Deleted When The Maximum Limit Is Reached
const short  DeletedTransactions = 5;

const string Delim = "#//#";
stClient ClientSession; 

//      End Global Variables      //

/* ------------------------------ */

//     Begin Print functions      //

void ShowMainMenu() {

    system("cls");
    cout << "=================================\n";
    cout << "\tATM Main Menu Screen\n";
    cout << "=================================\n";
    cout << "\t[1] Quick Withdraw.\n";
    cout << "\t[2] Normal Withdraw.\n";
    cout << "\t[3] Deposit.\n";
    cout << "\t[4] Check Balance.\n";
    cout << "\t[5] Show my information.\n";
    cout << "\t[6] Account transactions.\n";
    cout << "\t[7] Logout.\n";
    cout << "=================================\n";
}

void ShowBar ( string MessageBar ) {
    cout << "=================================\n";
    cout << "\t" << MessageBar << endl;
    cout << "=================================\n";
}

void ShowQuickWithdraw () {
    cout << "=================================\n";
    cout << "\t   QuickWithdraw \n";
    cout << "=================================\n";
    cout << "\t[1] 20\t\t[2] 50\n\t[3] 100\t\t[4] 200\n\t[5] 400\t\t[6] 600\n\t[7] 800\t\t[8] 1000\n\t[9] exit\n";
    cout << "=================================\n";
}

void ShowClientData () {
    
    cout << "\nThe Following are the client's details:\n";
    cout << "---------------------------------\n";
    cout << "Account Number  : " << ClientSession.AccountNumber << endl;
    cout << "Pin Code        : " << ClientSession.PinCode << endl;
    cout << "Name            : " << ClientSession.Name << endl;
    cout << "Phone           : " << ClientSession.Phone << endl;
    cout << "Account Balance : " << ClientSession.AccountBalance << endl;
    cout << "Number of recent Transactions : " << ClientSession.OperationsNumber << endl;
    cout << "---------------------------------\n\n";
}

void ShowClientTransactions ( vector <stTransactions> Transactions ) {

    short Counter = 1;
    cout << "\t\t\t\tYour Account Transactions.";
    cout << "\n________________________________________________________________________________________________________________\n\n";
    cout << "        | " << left << setw(15) << "Type";
    cout << "| " << left << setw(12) << "Amount";
    cout << "| " << left << setw(15) << "Balance before";
    cout << "| " << left << setw(15) << "Balance after";
    cout << "| " << left << setw(15) << "Transaction date";
    cout << "| " << left << setw(15) << "Transaction time";
    cout << "\n________________________________________________________________________________________________________________\n\n";

    for (stTransactions Trans : Transactions)
    {
        if ( Trans.AccountNumber == ClientSession.AccountNumber) {

            cout << "| " << left << setw(6)  << Counter;
            cout << "| " << left << setw(15) << Trans.MovementType;
            cout << "| " << left << setw(12) << Trans.Amount;
            cout << "| " << left << setw(15) << Trans.Balance;
            cout << "| " << left << setw(15) << Trans.Balance + Trans.Amount;
            cout << "| " << left << setw(16) << Trans.Date;
            cout << "| " << left << setw(15) << Trans.Time;
            cout << "\n";
            Counter++;
        }
    }
    cout << "\n________________________________________________________________________________________________________________\n\n";

    cout << 
    "\nThe last transactions made in your account,\n" <<
    "please note that the maximum number of saved transactions is : [" << 
    MaxTransactions << 
    "]\nWhen the limit is reached, the last [" <<
    DeletedTransactions << 
    "] transactions will be deleted in order of seniority\n";

    cout << "\n________________________________________________________________________________________________________________\n\n";
}

//      End Print functions       //

/* ------------------------------ */

//Begin Tools For Client function//

vector <string> SplitString ( string str ) {

    vector <string> vWord;
    short pos = 0;
    string sWord = "\0";
    
    while ((pos = str.find(Delim)) != std::string::npos) {

        sWord = str.substr(0, pos);
        if (sWord != "") {
            vWord.push_back(sWord);
        }
        str.erase(0, pos + Delim.length()); 
    }

    if (str != "") {
        vWord.push_back(str);
    }
    return vWord;
}

string ConvertRecordToLineForClient ( stClient ClientData ) {

    string stClientRecord = "\0";

    stClientRecord  += 
    ClientData.AccountNumber            + Delim +
    ClientData.PinCode                  + Delim +
    ClientData.Name                     + Delim +
    ClientData.Phone                    + Delim +
    to_string(ClientData.AccountBalance)+ Delim +
    to_string(ClientData.OperationsNumber);

    return stClientRecord ;
}

stClient ConvertLineToStructForClient ( string LineRecord ) {

    stClient Client;
    vector <string> vClientData = SplitString(LineRecord);

    Client.AccountNumber =       vClientData[0];
    Client.PinCode =             vClientData[1];
    Client.Name =                vClientData[2];
    Client.Phone =               vClientData[3];
    Client.AccountBalance =      stod(vClientData[4]);
    Client.OperationsNumber = stod(vClientData[5]);

    return Client;
}

vector <stClient> LoadClientsDataFromFile () {

    vector <stClient> vClients;
    fstream MyFile;

    MyFile.open(ClientsFile, ios::in);

    if (MyFile.is_open()) { 

        string Line = "\0";
        stClient Client; 

        while (getline(MyFile, Line)) {
            
            Client = ConvertLineToStructForClient(Line);
		    vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;
}

void IncreaseNumberOperations ( vector <stClient>& vClients, short NumberAdditions ) {

    fstream MyFile;

    MyFile.open(ClientsFile, ios::out);

    for (stClient& Client : vClients)
    {
        if (Client.AccountNumber == ClientSession.AccountNumber){

            Client.OperationsNumber        += NumberAdditions;
            ClientSession.OperationsNumber += NumberAdditions;

            MyFile << ConvertRecordToLineForClient(Client) << endl;
        }
        else{
            MyFile << ConvertRecordToLineForClient(Client) << endl;
        }
    }  
    MyFile.close();
}

bool SearchClientToLogIn ( string AccountNumber, string  PinCode) {

    vector <stClient> vClients  = LoadClientsDataFromFile();
    
    for (stClient& Client : vClients)
    {
        if (Client.AccountNumber == AccountNumber && Client.PinCode == PinCode)
        {
            ClientSession = Client;
            return false;
        }
    }
    return true;
}

// End Tools For Client function //

/* ------------------------------ */

//Begin Tools For Transactions function//

string GetSystemDateToLine () {

    time_t t = time(0);   // get time now
    tm* now = localtime(&t);

    string Date = "\0";

    Date += 
    to_string(now->tm_year + 1900) + "/" + to_string(now->tm_mon + 1) + "/" + to_string(now->tm_mday)
    + Delim +
    to_string(now->tm_hour) + ":" + to_string(now->tm_min) + ":" + to_string(now->tm_sec);

    return Date;
}

string DetermineTypeOfMovement ( int AmountMoney ) {

    return (AmountMoney < 0) ? "Withdraw" : "Deposit";
}

stTransactions ConvertLineToStructForMovementInformation( string LineRecord ) {

    stTransactions TransactionsClient;
    vector <string> vTransactionsClient = SplitString(LineRecord);

    TransactionsClient.AccountNumber   = vTransactionsClient[0];
    TransactionsClient.MovementType    = vTransactionsClient[1];
    TransactionsClient.Amount          = stoi(vTransactionsClient[2]);
    TransactionsClient.Balance         = stod(vTransactionsClient[3]);
    TransactionsClient.Date            = vTransactionsClient[4];
    TransactionsClient.Time            = vTransactionsClient[5];

    return TransactionsClient;
}

string ConvertMovementInformationToLine ( int AmountMoney, double AccountBalance ) {

    string TransactionsToLine = "\0";
    TransactionsToLine  += 
    ClientSession.AccountNumber         + Delim +
    DetermineTypeOfMovement(AmountMoney)+ Delim +
    to_string(AmountMoney)              + Delim +
    to_string(AccountBalance)           + Delim +
    GetSystemDateToLine();

    return TransactionsToLine ;
}

string ConvertRecordToLineForTransactions ( stTransactions TransactionsData ) {

    string TransactionsToLine = "\0";
    TransactionsToLine  += 
    TransactionsData.AccountNumber      + Delim +
    TransactionsData.MovementType       + Delim +
    to_string(TransactionsData.Amount)  + Delim +
    to_string(TransactionsData.Balance) + Delim +
    TransactionsData.Date               + Delim +
    TransactionsData.Time;

    return TransactionsToLine ;
}

vector <stTransactions> LoadTransactionsDataFromFile () {

    vector <stTransactions> vTransactionsData;
    fstream MyFile;

    MyFile.open(TransactionsFile, ios::in);

    if (MyFile.is_open()) { 

        string Line = "\0";
        stTransactions TransactionsData; 

        while (getline(MyFile, Line)) {

            TransactionsData = ConvertLineToStructForMovementInformation(Line);
		    vTransactionsData.push_back(TransactionsData);
        }
        MyFile.close();
    }
    return vTransactionsData;
}

void DeleteTransactionsFromFileAutomatically () {

    vector <stTransactions> vTransactionsData = LoadTransactionsDataFromFile ();
    fstream MyFile;

    short Counter = 0;
    MyFile.open(TransactionsFile, ios::out);

    for (stTransactions& Trans : vTransactionsData)
    {
        if (Trans.AccountNumber == ClientSession.AccountNumber) {

            if (Counter > DeletedTransactions && Counter <= MaxTransactions ) {
                MyFile << ConvertRecordToLineForTransactions(Trans) << endl;
                Counter++;
            }
            else {
                Counter++;
            }
        }
        else {
            MyFile << ConvertRecordToLineForTransactions(Trans) << endl;
        }
    } 
        
    MyFile.close();
}

void UploadAccountTransactionsToFile ( vector <stClient>& vClients, int AmountMoney, double AccountBalance ) {

    if ( ClientSession.OperationsNumber >= MaxTransactions ) {
        DeleteTransactionsFromFileAutomatically();
        IncreaseNumberOperations (vClients, (DeletedTransactions * -1));
    }
    else {
        IncreaseNumberOperations (vClients, 1);
    }

    fstream MyFile;
    MyFile.open(TransactionsFile, ios::out | ios::app);

    if (MyFile.is_open()) {

        MyFile << ConvertMovementInformationToLine(AmountMoney, AccountBalance) << endl;
        MyFile.close();
    }
}

//      End Tools For Transactions function        //

/* ------------------------------ */

//      Begin Get function        //

string GetString (string Message) {

    string ClientAccountNumber = "\0"; 
    cout << Message;
    getline(cin >> ws, ClientAccountNumber);

    return ClientAccountNumber;
}

int GetNumber (string Message, int Min = 0, int Max = 10000) {

    int Number = 0;
    cout << Message;
    cin >> Number;
    
    while (Number < Min || Number > Max || cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << Message;
        cin >> Number;
    } 
     
    return Number;
}

char GetChar (string Message) {

    char Char = 'Y'; 
    
    do
    {
        cout << Message;
        cin >> Char;
    } while (toupper(Char) != 'Y' || toupper(Char) != 'N');
    
    
    return Char;
}

//      End Get function          //


// Begin Deposit And Withdraw functions   //

void ShowBalance () {

    cout << "Your Balance is " << ClientSession.AccountBalance << endl;
}

void DepositAndWithdraw ( vector <stClient>& vClients, int AmountMoney) {

    fstream MyFile;

    MyFile.open( ClientsFile, ios::out );
    
    for (stClient& Client : vClients)
    {
        if ( Client.AccountNumber == ClientSession.AccountNumber ) {
            UploadAccountTransactionsToFile( vClients, AmountMoney, Client.AccountBalance );
            Client.AccountBalance += AmountMoney;
            ClientSession.AccountBalance += AmountMoney;
            MyFile << ConvertRecordToLineForClient(Client) << endl;
            cout << "Done Successfully, New Balance is " << Client.AccountBalance << endl;
        }
        else {
            MyFile << ConvertRecordToLineForClient(Client) << endl;
        }
    }
    MyFile.close();
}

void QuickWithdraw( vector <stClient>& vClients ) {
    
    short WithdrawalAmounts[] = {0, 20, 50, 100, 200, 400, 600, 800, 1000, 0};

    ShowBalance();
    short ChooseNumber = GetNumber("Choose what to withdraw from [1] to [8] ? ", 1, 9);

    if (WithdrawalAmounts[ChooseNumber] > ClientSession.AccountBalance) {
        system("cls");
        cout << "\nThe amount exceeds your Balance, Make another choice.\n\n";
        if (toupper(GetChar("Do you want try again ? Y/N")) == 'Y')
            return QuickWithdraw(vClients);
        else
            return;
    }
    else if (ChooseNumber != 9 && toupper(GetChar("Are you sure want perform this transaction ? Y/N ? ")) == 'Y') {
        DepositAndWithdraw(vClients, (WithdrawalAmounts[ChooseNumber] * -1));
        return;
    }
    else {
        cout << "\n\nThe operation has been cancelled!" << endl;
        return;
    }
}

void NormalWithdraw ( vector <stClient>& vClients ) {

    ShowBalance();
    int Amount = GetNumber("Enter an amount Multiple of 5's ? ");

    if (Amount % 5 != 0 && Amount > ClientSession.AccountBalance) {
        cout << "\nInvalid entry Please enter an amount that is a multiple of 5 and fits the amount of cash in the account.\n\n";
        if (toupper(GetChar("Do you want try again ? Y/N")) == 'Y')
            return NormalWithdraw(vClients);
        else
            return;
    }
    else if (toupper(GetChar("Are you sure want perform this transaction ? Y/N ? ")) == 'Y') {
        DepositAndWithdraw(vClients, (Amount * -1));
        return;
    }
    else {
        cout << "\n\nThe operation has been cancelled!" << endl;
        return;
    }
}

void Deposit ( vector <stClient>& vClients ) {

    ShowBalance();
    int Amount = GetNumber("Enter a Positive Deposit amount ? ");

    if (Amount % 5 != 0 || Amount < 0) {
        cout << "\nInvalid entry Please enter an amount that is a multiple of 5 and a positive number.\n\n";
        if (toupper(GetChar("Do you want try again ? Y/N")) == 'Y')
            return Deposit(vClients);
        else
            return;
    }
    else if (toupper(GetChar("Are you sure want perform this transaction ? Y/N ? ")) == 'Y') {
        DepositAndWithdraw(vClients, Amount);
        return;
    }
    else {
        cout << "\n\nThe operation has been cancelled!" << endl;
        return;
    }
}

// End Deposit And Withdraw functions     //

/* ------------------------------ */

// Begin OperationCenter functions//

void OperationCenter() {

    system("cls");
    ShowMainMenu();

    vector <stClient>       vClients     = LoadClientsDataFromFile();
    vector <stTransactions> Transactions = LoadTransactionsDataFromFile();

    switch ( GetNumber ("Choose what do you to do? [1 To 7]? ", 1, 7) )
    {
        case eAppOption::eQuickWithdraw :
            system("cls");
            ShowQuickWithdraw();
            QuickWithdraw(vClients);
            system("pause");
            return OperationCenter();
        case eAppOption::eNormalWithdraw :
            system("cls");            
            ShowBar("Normal Withdraw");
            NormalWithdraw(vClients);
            system("pause");
            return OperationCenter();
        case eAppOption::eDeposit :
            system("cls");            
            ShowBar("Deposit");
            Deposit(vClients);
            system("pause");
            return OperationCenter();
        case eAppOption::eCheckBalance :
            system("cls");            
            ShowBar("Check Balance");
            ShowBalance();
            system("pause");
            return OperationCenter();
        case eAppOption::eShowClientData :
            system("cls");            
            ShowClientData();
            system("pause");
            return OperationCenter();   
        case eAppOption::eAccountTransactions :
            system("cls");            
            ShowClientTransactions(Transactions);
            system("pause");
            return OperationCenter(); 
        case eAppOption::eLogOut :
            return Login();
    }
}

// End OperationCenter functions //

/* ------------------------------ */

// Begin Login functions    //

void Login () {

    system("cls");
    ShowBar("Login Screen");
    string AccountNumber = "\0", PinCode = "\0";

    AccountNumber = GetString("Enter Account Number? ");
    PinCode = GetString("Enter Pin Code? ");

    if (SearchClientToLogIn(AccountNumber, PinCode)) {
        cout << "Invalid Account Number/Pin Code!\n";
        system("pause");
        return Login();
    }
    else {
        return OperationCenter();
    }
}

// End Login functions    //

int main() {

    Login();

    return 0;
}
