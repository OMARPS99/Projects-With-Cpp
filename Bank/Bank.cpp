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
void Transactions ();

//      Begin Data Type           //

enum eAppOption { eShowClientList = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClientInfo = 4,
eFindClient = 5, eTransactionsMenu = 6, eManageUsersMenu = 7, eShowClientsTransactions = 8, eTotalBalancesForAllClients = 9 ,eLogOut = 10};

enum eTransactions { eDeposit = 1, eWithdraw = 2, eTotalBalances = 3, etMainMenu = 4};

enum eManageUsers { eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, emMainMenu = 6};

enum eShowTransaction {esShowClientTransactions = 1, esShowAllClientsTransactions = 2, esDeleteClientTransactions = 3,
 esDeleteAllClientsTransactions = 4, esMainMenu = 5};

struct stClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    short OperationsNumber;
};

struct stUsers
{
    string UserName;
    string Password;
    short Permissions;
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
const string UsersFile = "UsersAccount.txt";
const string TransactionsFile = "Transactions.txt";

// Total Number Transactions To be Saved For Each Client
const short  MaxTransactions = 10;

// Number of Transactions To be Deleted When The Maximum Limit Is Reached
const short  DeletedTransactions = 5;

const string Delim = "#//#";

stUsers UserSession; 

stClient ClientSession;

//      End Global Variables      //

/* ------------------------------ */

//     Begin Print functions      //

void ShowMainMenu() {

    system("cls");
    cout << "=================================\n";
    cout << "\tMain Menu Screen\n";
    cout << "=================================\n";
    cout << "\t[1] show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Manage Users.\n";
    cout << "\t[8] Transaction Records Procedures.\n";
    cout << "\t[9] Total Balances For All Clients.\n";
    cout << "\t[10] Logout.\n";
    cout << "=================================\n";
}

void ShowClientsTransactionsMenu() {

    system("cls");
    cout << "=======================================\n";
    cout << "\tShow Clients Transactions Screen\n";
    cout << "=======================================\n";
    cout << "\t[1] Show Client Transactions.\n";
    cout << "\t[2] Show All Clients Transactions.\n";
    cout << "\t[3] Delete Client Transactions.\n";
    cout << "\t[4] Delete All Clients Transactions.\n";
    cout << "\t[5] Main Menu.\n";
    cout << "=======================================\n";
}

void ShowTransactionsMenu() {

    system("cls");
    cout << "=======================================\n";
    cout << "\tTransactions Menu Screen\n";
    cout << "=======================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] TotalBalances.\n";
    cout << "\t[4] MainMenu.\n";
    cout << "=======================================\n";
}

void ShowManageUsersMenu() {

    system("cls");
    cout << "=======================================\n";
    cout << "\tManage Users Menu Menu Screen\n";
    cout << "=======================================\n";
    cout << "\t[1] List Users.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete user.\n";
    cout << "\t[4] Update User.\n";
    cout << "\t[5] Find User.\n";
    cout << "\t[6] Main Menu.\n";
    cout << "=======================================\n";
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

void ShowUserData ( stUsers User ) {
    
    cout << "\nThe Following are the client details:\n";
    cout << "---------------------------------\n";
    cout << "User Name   : " << User.UserName << endl;
    cout << "Password    : " << User.Password << endl;
    cout << "Permissions : " << User.Permissions << endl;
    cout << "---------------------------------\n\n";
}

void ShowClientTransactions ( vector <stTransactions> vTransactions ) {

    short Counter = 1;
    cout << "\t\t\t\tTransactions for the account number : " << ClientSession.AccountNumber;
    cout << "\n________________________________________________________________________________________________________________\n\n";
    cout << "        | " << left << setw(15) << "Type";
    cout << "| " << left << setw(12) << "Amount";
    cout << "| " << left << setw(15) << "Balance before";
    cout << "| " << left << setw(15) << "Balance after";
    cout << "| " << left << setw(15) << "Transaction date";
    cout << "| " << left << setw(15) << "Transaction time";
    cout << "\n________________________________________________________________________________________________________________\n\n";

    for (stTransactions Trans : vTransactions)
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
}

void ShowAllClientTransactions ( vector <stTransactions> vTransactions ) {

    short Counter = 1;
    cout << "\t\t\t\tTransaction List (" << vTransactions.size() << ")" << " Transaction(s).";
    cout << "\n________________________________________________________________________________________________________________\n\n";
    cout << "        | " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(12) << "Type";
    cout << "| " << left << setw(12) << "Amount";
    cout << "| " << left << setw(15) << "Balance before";
    cout << "| " << left << setw(15) << "Balance after";
    cout << "| " << left << setw(15) << "Transaction date";
    cout << "| " << left << setw(15) << "Transaction time";
    cout << "\n________________________________________________________________________________________________________________\n\n";

    for (stTransactions Trans : vTransactions)
    {

        cout << "| " << left << setw(6)  << Counter;
        cout << "| " << left << setw(15) << Trans.AccountNumber;
        cout << "| " << left << setw(12) << Trans.MovementType;
        cout << "| " << left << setw(12) << Trans.Amount;
        cout << "| " << left << setw(15) << Trans.Balance;
        cout << "| " << left << setw(15) << Trans.Balance + Trans.Amount;
        cout << "| " << left << setw(16) << Trans.Date;
        cout << "| " << left << setw(15) << Trans.Time;
        cout << "\n";
        Counter++;
    }
    cout << "\n________________________________________________________________________________________________________________\n\n";

}

void ShowALLClientsData ( vector <stClient> vClients ) {

    cout << "\t\t\t\tClient List (" << vClients.size() << ")" << " Client(s).";
    cout << "\n__________________________________________________________________________________________________________\n\n";
    cout << "| " << left << setw(15) << "AccountNumber";
    cout << "| " << left << setw(10) << "PinCode";
    cout << "| " << left << setw(30) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Account Balance";
    cout << "| " << left << setw(26) << "Number of recent Transactions";
    cout << "\n__________________________________________________________________________________________________________\n\n";

    for (stClient Client : vClients)
    {
        cout << "| " << left << setw(15) << Client.AccountNumber;
        cout << "| " << left << setw(10) << Client.PinCode;
        cout << "| " << left << setw(30) << Client.Name;
        cout << "| " << left << setw(12) << Client.Phone;
        cout << "| " << left << setw(12) << Client.AccountBalance;
        cout << "| " << left << setw(26) << Client.OperationsNumber;
        cout << "\n";
    }
    cout << "\n__________________________________________________________________________________________________________\n\n";
}

void ShowALLUsersData ( vector <stUsers> vUsers ) {

    cout << "\t\t\t\tUsers List (" << vUsers.size() << ")" << " Client(s).";
    cout << "\n____________________________________________________________________________________________\n\n";
    cout << "| " << left << setw(15) << "User Name";
    cout << "| " << left << setw(10) << "Password";
    cout << "| " << left << setw(5) << "Permissions";
    cout << "\n____________________________________________________________________________________________\n\n";

    for (stUsers User : vUsers)
    {
        cout << "| " << left << setw(15) << User.UserName;
        cout << "| " << left << setw(10) << User.Password;
        cout << "| " << left << setw(5) << User.Permissions;
        cout << "\n";
    }
    cout << "\n___________________________________________________________________________________________\n";
}

void ShowTotalBalancesForAllClients ( vector <stClient> vClients ) {

    double TotalBalance = 0;
    cout << "\t\t\t\tClient List (" << vClients.size() << ")" << " Client(s).";
    cout << "\n____________________________________________________________________________________________\n\n";
    cout << "| " << left << setw(15) << "AccountNumber";
    cout << "| " << left << setw(30) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n____________________________________________________________________________________________\n\n";

    for (stClient Client : vClients)
    {
        cout << "| " << left << setw(15) << Client.AccountNumber;
        cout << "| " << left << setw(30) << Client.Name;
        cout << "| " << left << setw(12) << Client.AccountBalance;
        cout << "\n";
        TotalBalance += Client.AccountBalance;
    }
    cout << "\n___________________________________________________________________________________________\n";
    cout << "\t\t\t\tTotalBalance = $" << TotalBalance << endl;

}

void ShowBar (string MessageBar) {
    cout << "---------------------------------\n";
    cout << "\t" << MessageBar << endl;
    cout << "---------------------------------\n";
}

//      End Print functions       //

/* ------------------------------ */

//      Begin Get function        //

string GetString (string Message) {

    string ClientAccountNumber = "\0"; 
    cout << Message;
    cin >> ClientAccountNumber;

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
    cout << Message;
    cin >> Char;
    return Char;
}

//      End Get function          //

/* ------------------------------ */

//      Begin Tools function      //

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

bool checkDepositAndWithdraw ( double NewBalance ) {
    
    char Y_N = 'Y';

    cout << "Are you sure want perform this transaction ? Y/N ? ";
    cin >> Y_N;

    if (toupper(Y_N) == 'Y')
    {
        cout << "\n\nDone successfully, the current balance is " << NewBalance << endl;
        return true;
    }
    else {
        cout << "\n\nThe operation has been cancelled!" << endl;
        return false;
    }
}

//      End Tools function      //

/* ------------------------------ */

//Begin Tools For Client function//

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

bool SearchForClientAndUploadInfo ( vector <stClient> vClients, string AccountNumber ) {
        
    for (stClient& Client : vClients)
    {
        if (Client.AccountNumber == AccountNumber)
        {
            ClientSession = Client;
            return false;
        }
    }
    return true;
}

void LoginClient ( vector <stClient> vClients ) {

    string AccountNumber = GetString("Please Enter the Account Number Client ? ");

    if (AccountNumber == "exit")
        return OperationCenter();

    if ( !SearchForClientAndUploadInfo( vClients, AccountNumber ) ) {
        return;
    }
    else {
        cout << "\nClient with Account Number (" << AccountNumber << ") Not Found!\nEnter \"exit\" to return to the Main Menu Or Again ";
        return LoginClient(vClients);
    }
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

//  End Tools For Client function  //

/* ------------------------------ */

// Begin Tools For Users function //

string ConvertRecordToLineForUsers ( stUsers UsersData ) {

    string stUsersRecord = "\0";

    stUsersRecord  += UsersData.UserName + Delim + UsersData.Password  + Delim + to_string(UsersData.Permissions);

    return stUsersRecord ;
}

stUsers ConvertLineToStructForUsers ( string LineRecord ) {

    stUsers Users;
    vector <string> vUsersData = SplitString(LineRecord);

    Users.UserName = vUsersData[0];
    Users.Password = vUsersData[1];
    Users.Permissions = stoi(vUsersData[2]);

    return Users;
}

vector <stUsers> LoadUsersDataFromFile () {

    vector <stUsers> vUsers;
    fstream MyFile;

    MyFile.open(UsersFile, ios::in);

    if (MyFile.is_open()) { 

        string Line = "\0";
        stUsers Users; 

        while (getline(MyFile, Line)) {
            
            Users = ConvertLineToStructForUsers(Line);
		    vUsers.push_back(Users);
        }
        MyFile.close();
    }
    return vUsers;
}

bool SearchUserToLogIn ( string UserName, string Password) {
    
    vector <stUsers> vUsers = LoadUsersDataFromFile();

    for (stUsers& User : vUsers)
    {
        if (User.UserName == UserName && User.Password == Password)
        {
            UserSession = User;
            return false;
        }
    }
    return true;
}

bool SearchUser ( vector <stUsers> vUsers, string UserName) {
    
    for (stUsers& User : vUsers)
    {
        if ( User.UserName == UserName )
        {
            ShowUserData(User);
            return false;
        }
    }
    return true;
}

void CheckPermissions ( short OperationNumber ) {

    if ( UserSession.Permissions & OperationNumber )
        return;
    ShowBar("Access Denied,\nYou dont have Permission to do this,\n    Please Contact Your Admin!");
    system("pause");
    return OperationCenter();
}

//  End Tools For Users function   //

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

void DeleteClientTransactions (vector <stTransactions>& vTransactionsData, vector <stClient>& vClients) {

    // Delete Transaction Client From File  
    fstream MyFile1;

    MyFile1.open(TransactionsFile, ios::out);

    for (stTransactions& Trans : vTransactionsData)
    {
        if (Trans.AccountNumber != ClientSession.AccountNumber)
            MyFile1 << ConvertRecordToLineForTransactions(Trans) << endl;
    } 
    MyFile1.close();

    // Edit Number Operations For Client From File
    fstream MyFile2;

    MyFile2.open(ClientsFile, ios::out);

    for (stClient& Client : vClients)
    {
        if (Client.AccountNumber == ClientSession.AccountNumber) {
            Client.OperationsNumber = 0;
            MyFile2 << ConvertRecordToLineForClient(Client) << endl;
        }
        else {
            MyFile2 << ConvertRecordToLineForClient(Client) << endl;
        }
    } 
    MyFile2.close();

    cout << "\nClient transactions deleted successfully.\n" << endl; 

}

void DeleteAllClientsTransactions (vector <stClient>& vClients) {

    char chr = 'N';
    cout << "Are you sure you want to delete all transactions for all Clients? " ;
    cin >> chr;
    if (toupper(chr) == 'Y')
    {  
        // Delete All Information In File 
        fstream MyFile1;
        MyFile1.open(TransactionsFile, ios::out);
        MyFile1.close();

        // Edit All Information In File
        fstream MyFile2;
        MyFile2.open(ClientsFile, ios::out);
        for (stClient& Client : vClients) {
            Client.OperationsNumber = 0;
            MyFile2 << ConvertRecordToLineForClient(Client) << endl;
        } 
        MyFile2.close(); 
        cout << "\n\nAll Transactions have been successfully deleted   ." << endl; 
    }
    else {
        cout << "\nThe process has been cancelled\n";
    }
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

//End Tools For Transactions function//

/* ------------------------------ */

//      Begin Read functions       //

stClient ReadNewClientAndUpdateClient ( vector <stClient> vClients, bool AddNewClient, string AccountNumber = "\0") {

    stClient Client;

    if (AddNewClient)
    {
        cout << "Enter Account Number ? ";
        getline(cin >> ws, Client.AccountNumber);

        Client.OperationsNumber = ClientSession.OperationsNumber = 0;
        
        while (!SearchForClientAndUploadInfo(vClients, Client.AccountNumber))
        {
            cout << "\nClient with (" << Client.AccountNumber << ") already exists Enter another Account Number? ";
            getline(cin >> ws, Client.AccountNumber);
        }
    }
    else {
        Client.AccountNumber = AccountNumber;
        Client.OperationsNumber = ClientSession.OperationsNumber;
    }
    
    cout << "Enter PinCode ? ";
    getline(cin >> ws, Client.PinCode);
    cout << "Enter Name ? ";
    getline(cin, Client.Name);
    cout << "Enter Phone ? ";
    getline(cin, Client.Phone);
    cout << "Enter Account Balance ? ";
    cin >> Client.AccountBalance;

    return Client;
}

stUsers ReadNewUserAndUpdateUsers ( vector <stUsers> vUsers, bool AddNewUsers = true, string UserName = "\0" ) {

    stUsers User;

    if (AddNewUsers)
    {
        cout << "Enter User Name ? ";
        getline(cin >> ws, User.UserName);
        while (!SearchUser(vUsers, User.UserName))
        {
            cout << "User with (" << User.UserName << ") already exists Enter another User Name? ";
            getline(cin >> ws, User.UserName);
        }
    }
    else {
        User.UserName = UserName;
    }
    
    cout << "Enter Password ? ";
    getline(cin >> ws, User.Password);

    if (toupper(GetChar("Do you want to give full access Y/N ? ")) == 'Y') {

        User.Permissions = -1;
    }
    else {
        User.Permissions = 0;
        cout << "\nDo you want to give access to : \n";
        if(toupper(GetChar("\nShow Clint List ? Y/N ? ")) == 'Y')
            User.Permissions += 1;
        if(toupper(GetChar("\nAdd New Clint ? Y/N ? ")) == 'Y')
            User.Permissions += 2;
        if(toupper(GetChar("\nDelete Clint ? Y/N ? ")) == 'Y')
            User.Permissions += 4;
        if(toupper(GetChar("\nUpDate Clint ? Y/N ? ")) == 'Y')
            User.Permissions += 8;
        if(toupper(GetChar("\nFind Clint ? Y/N ? ")) == 'Y')
            User.Permissions += 16;
        if(toupper(GetChar("\nTransactions ? Y/N ? ")) == 'Y')
            User.Permissions += 32;
        if(toupper(GetChar("\nManage Users ? Y/N ? ")) == 'Y')
            User.Permissions += 64;
        if(toupper(GetChar("\n Show Clients Transactions ? Y/N ? ")) == 'Y')
            User.Permissions += 128;
        if(toupper(GetChar("\nTotal Balances For All Clients ? Y/N ? ")) == 'Y')
            User.Permissions += 256;
    }
    return User;
}

//      End Read function          //

/* ------------------------------ */

//      Begin Add functions       //

void AddClientFromFile ( string ClientData ) {

    fstream MyFile;

    MyFile.open(ClientsFile, ios::out | ios::app);

    if (MyFile.is_open()) { 
        MyFile << ClientData << endl;
        MyFile.close();
    }
}

void AddNewClient ( vector <stClient>& vClients ) {

    do
    {
        cout << "Adding New Client:\n\n";

        stClient Client = ReadNewClientAndUpdateClient(vClients, 1);

        AddClientFromFile(ConvertRecordToLineForClient(Client));
        
    } while (toupper(GetChar("\nClient Added Successfully, do you want to add more clients? Y/N ? ")) == 'Y');
}

void AddUserFromFile ( string UserData ) {

    fstream MyFile;

    MyFile.open(UsersFile, ios::out | ios::app);

    if (MyFile.is_open()) { 
        MyFile << UserData << endl;
        MyFile.close();
    }
}

void AddNewUser ( vector <stUsers>& vUsers ) {

    do
    {
        cout << "Adding New User:\n\n";

        stUsers Users = ReadNewUserAndUpdateUsers(vUsers, 1);

        AddUserFromFile(ConvertRecordToLineForUsers(Users));
        
    } while (toupper(GetChar("\nUser Added Successfully, do you want to add more Users? Y/N ? ")) == 'Y');
}

//      End Add functions         //

/* ------------------------------ */

//      Begin Delete functions    //

void DeleteClientFromFile ( vector <stClient>& vClients, string AccountNumber ) {

    fstream MyFile;

    MyFile.open( ClientsFile, ios::out ); 
    
    for (stClient& vClient : vClients)
    {
        if (vClient.AccountNumber != AccountNumber)
            MyFile << ConvertRecordToLineForClient(vClient) << endl;
    } 
    MyFile.close();

    cout << "\n\nClient Deleted Successfully." << endl;
}

void DeleteClient ( vector <stClient>& vClients ) {

    string AccountNumber = GetString("Please Enter the Account Number Client? ");
    
    if (AccountNumber == "exit")
        return;

    if (SearchForClientAndUploadInfo(vClients, AccountNumber)) {
        cout << "\nClient with Account Number (" << AccountNumber << ") Not Found!\nEnter \"exit\" to return to the Main Menu Or Again ";
        return DeleteClient(vClients);
    }

    if ( toupper(GetChar("\nAre you sure you delete this client Y/N ? ")) == 'Y' )
        DeleteClientFromFile(vClients, AccountNumber);
    else 
        cout << "\nOperation cancelled.\n";
}

void DeleteUserFromFile ( vector <stUsers>& vUsers, string UserName ) {

    fstream MyFile;

    MyFile.open( UsersFile, ios::out ); 
    
    for (stUsers& vUser : vUsers)
    {
        if (vUser.UserName != UserName)
            MyFile << ConvertRecordToLineForUsers(vUser) << endl;
    } 
    MyFile.close();

    cout << "\n\nUser Deleted Successfully." << endl;
}

void DeleteUser ( vector <stUsers>& vUsers ) {

    string UserName = GetString("Please Enter User Name? ");
    
    if (UserName == "exit") {
        return;
    }
    else if (UserName == "Admin") {
        system("cls");
        ShowBar("\nYou Cannot Delete This User.");
        return; 
    }
        
    if ( SearchUser( vUsers, UserName ) ) {
        cout << "\nUser with User Name (" << UserName << ") Not Found!\nEnter \"exit\" to return to the Main Menu Or Again ";
        return DeleteUser(vUsers);
    }

    if ( toupper(GetChar("\nAre you sure you delete this User Y/N ? ")) == 'Y' )
        DeleteUserFromFile(vUsers, UserName);
    else 
        cout << "\nOperation cancelled.\n";
}

//      End Delete functions      //

/* ------------------------------ */

//      Begin Update functions    //

void UpdateClientInfo ( vector <stClient>& vClients ) {

    string AccountNumber = GetString("Please Enter the Account Number Client? ");

    if (AccountNumber == "exit")
        return;

    if ( SearchForClientAndUploadInfo( vClients, AccountNumber ) ) {
        cout << "\nClient with Account Number (" << AccountNumber << ") Not Found!\nEnter \"exit\" to return to the Main Menu Or Again ";
        return UpdateClientInfo(vClients);
    }

    fstream MyFile;
    MyFile.open(ClientsFile, ios::out ); 
    
    for (stClient Client : vClients)
    {
        if (Client.AccountNumber == AccountNumber) {
            MyFile << ConvertRecordToLineForClient(ReadNewClientAndUpdateClient(vClients, 0, AccountNumber)) << endl;
        }
        else {
            MyFile << ConvertRecordToLineForClient(Client) << endl;
        }
    }
    MyFile.close();
    cout << "\n\nClient Updated Successfully.\n" << endl;
}

void UpdateUserInfo ( vector <stUsers>& vUsers ) {

    string UserName = GetString("Please Enter the User Name? ");

    if (UserName == "exit") {
        return;
    }
    else if (UserName == "Admin") {
        ShowBar("\nYou Cannot Update Information This User.");
        return; 
    }

    if ( SearchUser( vUsers, UserName ) ) {
            cout << "\nUser with User Name (" << UserName << ") Not Found!\nEnter \"exit\" to return to the Main Menu Or Again ";
            return  UpdateUserInfo(vUsers);
    }

    fstream MyFile;
    MyFile.open(UsersFile, ios::out ); 
    
    for (stUsers User : vUsers)
    {
        if (User.UserName == UserName) {
            MyFile << ConvertRecordToLineForUsers(ReadNewUserAndUpdateUsers(vUsers, 0, UserName)) << endl;
        }
        else {
            MyFile << ConvertRecordToLineForUsers(User) << endl;
        }
    }
    MyFile.close();
    cout << "\n\nClient Updated Successfully.\n" << endl;
}

//      End Update functions      //

/* ------------------------------ */

// Begin Find Client functions    //

void FindClient ( vector <stClient> vClients ) {

    LoginClient(vClients);
    ShowClientData();
}

void FindUser ( vector <stUsers> vUsers ) {

    string UserName = GetString("Please Enter the User Name? ");
        
    if ( SearchUser( vUsers, UserName ) ) {
        cout << "\nUser with (" << UserName << ") Not Found!" << endl;
    }
}

//  End FindClient functions      //

/* ------------------------------ */

// Begin Transactions functions   //

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

void Deposit ( vector <stClient>& vClients ) {
    
    ShowBalance();
    int Amount = GetNumber("Enter a Positive Deposit amount ? ", 1, 10000000);

    if (Amount < 0) {
        cout << "\nInvalid You must enter a positive number.\n\n";
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

void Withdraw ( vector <stClient>& vClients ) {

    ShowBalance();
    int Amount = GetNumber("Enter Withdraw amount money ? ", 1, 10000000);

    if (Amount > ClientSession.AccountBalance) {
        cout << "\nInvalid entry Please enter the amount that fits the amount of cash in the account.\n\n";
        if (toupper(GetChar("Do you want try again ? Y/N")) == 'Y')
            return Withdraw(vClients);
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

void Transactions () {
    
    system("cls");
    vector <stClient> vClients = LoadClientsDataFromFile();

    ShowTransactionsMenu();
    switch ( GetNumber ("Choose what do you to do? [1 To 4]? ", 1, 4 ))
    {
    case eTransactions::eDeposit :
        system("cls");
        ShowBar("Deposit Screen");
        Deposit(vClients);
        system("pause");
        return Transactions();
    case eTransactions::eWithdraw :
        system("cls");
        ShowBar("Withdraw Screen");
        Withdraw(vClients);
        system("pause");
        return Transactions();
    case eTransactions::eTotalBalances :
        system("cls");
        ShowBalance();
        system("pause");
        return Transactions();
    case eTransactions::etMainMenu :
        system("cls");
        break;
    }
}

// End Transactions functions     //

/* ------------------------------ */

// Begin Show Clients Transactions functions   //

void TransactionRecordsProcedures () {

    system("cls");
    ShowClientsTransactionsMenu();
    vector <stClient> vClients =            LoadClientsDataFromFile();
    vector <stTransactions> vTransactions = LoadTransactionsDataFromFile();

    switch ( GetNumber ("Choose what do you to do? [1 To 5]? ", 1, 5) )
    {
    case eShowTransaction::esShowAllClientsTransactions :
        system("cls");
        ShowAllClientTransactions(vTransactions);
        system("pause");
        return TransactionRecordsProcedures();
    case eShowTransaction::esShowClientTransactions :
        system("cls");
        LoginClient(vClients);
        system("cls");
        ShowClientTransactions(vTransactions);
        system("pause");
        return TransactionRecordsProcedures();
    case eShowTransaction::esDeleteAllClientsTransactions :
        system("cls");
        ShowBar("Delete All Clients Transactions");
        DeleteAllClientsTransactions(vClients);
        system("pause");
        return TransactionRecordsProcedures();
    case eShowTransaction::esDeleteClientTransactions :
        system("cls");
        LoginClient(vClients);
        system("cls");
        ShowBar("Delete Client Transactions");
        DeleteClientTransactions(vTransactions, vClients);
        system("pause");
        return TransactionRecordsProcedures();
    case eShowTransaction::esMainMenu :
        system("cls");
        break;
    }
}

// End Show Clients Transactions functions     //

/* ------------------------------ */

// Begin Manage Users functions   //

void ManageUsers () {

    system("cls");
    ShowManageUsersMenu();
    vector <stUsers> vUsers = LoadUsersDataFromFile();
    

    switch ( GetNumber ("Choose what do you to do? [1 To 6]? ", 1, 6) )
    {
    case eManageUsers::eListUsers :
        system("cls");
        ShowALLUsersData(vUsers);
        system("pause");
        return ManageUsers();
    case eManageUsers::eAddNewUser :
        system("cls");
        ShowBar("Add New User Screen");
        AddNewUser(vUsers);
        system("pause");
        return ManageUsers();
    case eManageUsers::eDeleteUser :
        system("cls");
        ShowBar("Delete User Screen");
        DeleteUser(vUsers);
        system("pause");
        return ManageUsers();
    case eManageUsers::eUpdateUser :
        system("cls");
        ShowBar("Update User Screen");
        UpdateUserInfo(vUsers);
        system("pause");
        return ManageUsers();
    case eManageUsers::eFindUser :
        system("cls");
        ShowBar("Find User Screen");
        FindUser(vUsers);
        system("pause");
        return ManageUsers();
    case eManageUsers::emMainMenu :
        system("cls");
        break;
    }
}

// End Manage Users functions //

/* ------------------------------ */

// Begin OperationCenter functions//

void OperationCenter() {

    system("cls");
    ShowMainMenu();
    vector <stClient> vClients = LoadClientsDataFromFile();
    
    switch ( (eAppOption) GetNumber ("Choose what do you to do? [1 To 10]? ", 1, 10) )
    {
        case eAppOption::eShowClientList :
            system("cls");
            CheckPermissions(1); 
            ShowBar("Show Client List");
            ShowALLClientsData(vClients);
            system("pause");
            return OperationCenter();
        case eAppOption::eAddNewClient :
            system("cls");
            CheckPermissions(2);
            ShowBar("Add New Client");
            AddNewClient(vClients);
            system("pause");
            return OperationCenter();
        case eAppOption::eDeleteClient :
            system("cls");
            CheckPermissions(4);
            ShowBar("Delete Client");
            DeleteClient(vClients);
            system("pause");
            return OperationCenter();
        case eAppOption::eUpdateClientInfo :
            system("cls");
            CheckPermissions(8);
            ShowBar("Update Client Info");
            UpdateClientInfo(vClients);
            system("pause");
            return OperationCenter();
        case eAppOption::eFindClient :
            system("cls");
            CheckPermissions(16);
            ShowBar("Find Client");
            FindClient(vClients);
            system("pause");
            return OperationCenter();
        case eAppOption::eTransactionsMenu :
            system("cls");
            CheckPermissions(32);
            LoginClient(vClients);
            Transactions();
            return OperationCenter();
        case eAppOption::eManageUsersMenu :
            system("cls");
            CheckPermissions(64);
            ManageUsers();
            return OperationCenter();
        case eAppOption::eShowClientsTransactions :
            system("cls");
            CheckPermissions(128);
            TransactionRecordsProcedures();
            return OperationCenter();
        case eAppOption::eTotalBalancesForAllClients :
            system("cls");
            CheckPermissions(256);
            ShowTotalBalancesForAllClients(vClients);
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
    string UserName = "\0", Password = "\0";
    UserName = GetString("Enter User Name? ");
    Password = GetString("Enter Password? ");
    if (SearchUserToLogIn(UserName, Password)) {
        cout << "Invalid UserName/Password!\n";
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
