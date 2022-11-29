#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include<iomanip>

using namespace std;

void Login ();
void OperationCenter ();

//      Begin Data Type           //

enum eAppOption { eShowClientList = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClientInfo = 4,
eFindClient = 5, eTransactionsMenu = 6, eManageUsersMenu = 7, eLogOut = 8};

enum eTransactions { eDeposit = 1, eWithdraw = 2, eTotalBalances = 3, etMainMenu = 4};

enum eManageUsers { eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, emMainMenu = 6};

struct stClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
};

struct stUsers
{
    string UserName;
    string Password;
    short Permissions;
};

//      End Data Type             //

/* ------------------------------ */

//     Begin Global Variables     //

const string ClientsFileName = "ClientData.txt";
const string UsersFileName = "UsersAccount.txt";
const string Delim = "#//#";
stUsers UserSession; 

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
    cout << "\t[6] Transaction.\n";
    cout << "\t[7] Manage Users.\n";
    cout << "\t[8] Logout.\n";
    cout << "=================================\n";
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

void ShowManageUsersMenu() { /* New */

    system("cls");
    cout << "=======================================\n";
    cout << "\tManage Users Menu Menu Screen\n";
    cout << "=======================================\n";
    cout << "\t[1] List Users.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete user.\n";
    cout << "\t[4] UpDate User.\n";
    cout << "\t[5] Find User.\n";
    cout << "\t[6] Main Menu.\n";
    cout << "=======================================\n";
}

void ShowClientData ( stClient Client ) {
    
    cout << "\nThe Following are the client details:\n";
    cout << "---------------------------------\n";
    cout << "Account Number  : " << Client.AccountNumber << endl;
    cout << "Pin Code        : " << Client.PinCode << endl;
    cout << "Name            : " << Client.Name << endl;
    cout << "Phone           : " << Client.Phone << endl;
    cout << "Account Balance : " << Client.AccountBalance << endl;
    cout << "---------------------------------\n\n";
}

void ShowUserData ( /* New */ stUsers User ) {
    
    cout << "\nThe Following are the client details:\n";
    cout << "---------------------------------\n";
    cout << "User Name   : " << User.UserName << endl;
    cout << "Password    : " << User.Password << endl;
    cout << "Permissions : " << User.Permissions << endl;
    cout << "---------------------------------\n\n";
}

void ShowALLClientsData ( vector <stClient> vClients ) {

    cout << "\t\t\t\tClient List (" << vClients.size() << ")" << " Client(s).";
    cout << "\n____________________________________________________________________________________________\n\n";
    cout << "| " << left << setw(15) << "AccountNumber";
    cout << "| " << left << setw(10) << "PinCode";
    cout << "| " << left << setw(30) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "AccountBalance";
    cout << "\n____________________________________________________________________________________________\n\n";

    for (stClient Client : vClients)
    {
        cout << "| " << left << setw(15) << Client.AccountNumber;
        cout << "| " << left << setw(10) << Client.PinCode;
        cout << "| " << left << setw(30) << Client.Name;
        cout << "| " << left << setw(12) << Client.Phone;
        cout << "| " << left << setw(12) << Client.AccountBalance;
        cout << "\n";
    }
    cout << "\n___________________________________________________________________________________________\n";
}

void ShowALLUsersData ( /* New */ vector <stUsers> vUsers ) {

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

void ShowTotalBalances ( vector <stClient> vClients ) {

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

//      Begin Tools function      //

vector <string> SplitString ( string str, string Delim ) {

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

string ConvertRecordToLineForClient ( stClient ClientData, string Delim ) {

    string stClientRecord = "\0";

    stClientRecord  += 
    ClientData.AccountNumber + Delim +
    ClientData.PinCode       + Delim +
    ClientData.Name          + Delim +
    ClientData.Phone         + Delim +
    to_string(ClientData.AccountBalance);

    return stClientRecord ;
}

stClient ConvertLineToStructForClient ( string LineRecord, string Delim ) {

    stClient Client;
    vector <string> vClientData = SplitString(LineRecord, Delim);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);

    return Client;
}

string ConvertRecordToLineForUsers ( /* New */ stUsers UsersData, string Delim ) {

    string stUsersRecord = "\0";

    stUsersRecord  += UsersData.UserName + Delim + UsersData.Password  + Delim + to_string(UsersData.Permissions);

    return stUsersRecord ;
}

stUsers ConvertLineToStructForUsers ( /* New */ string LineRecord, string Delim ) {

    stUsers Users;
    vector <string> vUsersData = SplitString(LineRecord, Delim);

    Users.UserName = vUsersData[0];
    Users.Password = vUsersData[1];
    Users.Permissions = stoi(vUsersData[2]);

    return Users;
}

vector <stClient> LoadClientsDataFromFile ( string ClientsFileName, string Delim ) {

    vector <stClient> vClients;
    fstream MyFile;

    MyFile.open(ClientsFileName, ios::in);

    if (MyFile.is_open()) { 

        string Line = "\0";
        stClient Client; 

        while (getline(MyFile, Line)) {
            
            Client = ConvertLineToStructForClient(Line, Delim);
		    vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;
}

vector <stUsers> LoadUsersDataFromFile ( /* New */ string UsersFileName, string Delim ) {

    vector <stUsers> vUsers;
    fstream MyFile;

    MyFile.open(UsersFileName, ios::in);

    if (MyFile.is_open()) { 

        string Line = "\0";
        stUsers Users; 

        while (getline(MyFile, Line)) {
            
            Users = ConvertLineToStructForUsers(Line, Delim);
		    vUsers.push_back(Users);
        }
        MyFile.close();
    }
    return vUsers;
}

bool SearchByAccountNumber ( vector <stClient> vClients, string AccountNumber ) {
        
    for (stClient& Client : vClients)
    {
        if (Client.AccountNumber == AccountNumber)
        {
            ShowClientData(Client);
            return false;
        }
    }
    return true;
}

bool SearchUserToLogIn ( /* New */ string UserName, string Password) {
    
    vector <stUsers> vUsers = LoadUsersDataFromFile(UsersFileName, Delim);

    for (stUsers& User : vUsers)
    {
        if (User.UserName == UserName && User.Password == Password)
        {
            UserSession.UserName = User.UserName;
            UserSession.Password = User.Password;
            UserSession.Permissions = User.Permissions;
            return false;
        }
    }
    return true;
}

bool SearchUser ( /* New */ vector <stUsers> vUsers, string UserName) {
    
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

void CheckPermissions ( /* New */ short OperationNumber ) {

    if ( UserSession.Permissions & OperationNumber )
        return;
    ShowBar("Access Denied,\nYou dont have Permission to do this,\n    Please Contact Your Admin!");
    system("pause");
    return OperationCenter();
}

//      End Tools function        //

/* ------------------------------ */

//      Begin Get function        //

string GetString (string Message) {

    string ClientAccountNumber = "\0"; 
    cout << Message;
    cin >> ClientAccountNumber;

    return ClientAccountNumber;
}

short GetNumber (string Message, short Min = 0, short Max = 10000) {

    short Number = 0;
    do
    {
        cout << Message;
        cin >> Number;
    } while (Number < Min || Number > Max);
     
    return Number;
}

char GetChar (string Message) {

    char Char = 'Y'; 
    cout << Message;
    cin >> Char;
    return Char;
}

stClient ReadNewClientAndUpdateClient ( vector <stClient> vClients, bool AddNewClient, string AccountNumber = "0") {

    stClient Client;

    if (AddNewClient)
    {
        cout << "Enter Account Number ? ";
        getline(cin >> ws, Client.AccountNumber);
        while (!SearchByAccountNumber(vClients, Client.AccountNumber))
        {
            cout << "Client with (" << Client.AccountNumber << ") already exists Enter another Account Number? ";
            getline(cin >> ws, Client.AccountNumber);
        }
    }
    else {
        Client.AccountNumber = AccountNumber;
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

stUsers ReadNewUserAndUpdateUsers ( /* New */ vector <stUsers> vUsers, bool AddNewUsers = true, string UserName = "\0" ) {

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
    }
    return User;
}

//      End Get function          //

/* ------------------------------ */

//      Begin Add functions       //

void AddClientFromFile ( string ClientData ) {

    fstream MyFile;

    MyFile.open(ClientsFileName, ios::out | ios::app);

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

        AddClientFromFile(ConvertRecordToLineForClient(Client, "#//#"));
        
    } while (toupper(GetChar("\nClient Added Successfully, do you want to add more clients? Y/N ? ")) == 'Y');
}

void AddUserFromFile ( /* New */ string UserData ) {

    fstream MyFile;

    MyFile.open(UsersFileName, ios::out | ios::app);

    if (MyFile.is_open()) { 
        MyFile << UserData << endl;
        MyFile.close();
    }
}

void AddNewUser ( /* New */ vector <stUsers>& vUsers ) {

    do
    {
        cout << "Adding New User:\n\n";

        stUsers Users = ReadNewUserAndUpdateUsers(vUsers, 1);

        AddUserFromFile(ConvertRecordToLineForUsers(Users, "#//#"));
        
    } while (toupper(GetChar("\nUser Added Successfully, do you want to add more Users? Y/N ? ")) == 'Y');
}

//      End Add functions         //

/* ------------------------------ */

//      Begin Delete functions    //

void DeleteClientFromFile ( vector <stClient>& vClients, string AccountNumber, string Delim ) {

    fstream MyFile;

    MyFile.open( ClientsFileName, ios::out ); 
    
    for (stClient& vClient : vClients)
    {
        if (vClient.AccountNumber != AccountNumber)
            MyFile << ConvertRecordToLineForClient(vClient, Delim) << endl;
    } 
    MyFile.close();

    cout << "\n\nClient Deleted Successfully." << endl;
}

void DeleteClient ( vector <stClient>& vClients ) {

    string AccountNumber = GetString("Please Enter the Account Number Client? ");
    
    if (AccountNumber == "exit")
        return;

    if ( SearchByAccountNumber( vClients, AccountNumber ) ) {
            cout << "\nClient with Account Number (" << AccountNumber << ") Not Found!\n\nEnter exit to return to the Main Menu.\n" << endl;
            return DeleteClient(vClients);
    }

    if ( toupper(GetChar("\nAre you sure you delete this client Y/N ? ")) == 'Y' )
        DeleteClientFromFile(vClients, AccountNumber, Delim);
    else 
        cout << "\nOperation cancelled.\n";
}

void DeleteUserFromFile ( /* New */ vector <stUsers>& vUsers, string UserName, string Delim ) {

    fstream MyFile;

    MyFile.open( UsersFileName, ios::out ); 
    
    for (stUsers& vUser : vUsers)
    {
        if (vUser.UserName != UserName)
            MyFile << ConvertRecordToLineForUsers(vUser, Delim) << endl;
    } 
    MyFile.close();

    cout << "\n\nUser Deleted Successfully." << endl;
}

void DeleteUser ( /* New */ vector <stUsers>& vUsers ) {

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
        cout << "\nClient with Account Number (" << UserName << ") Not Found!\n\nEnter exit to return to the Manage Users Menu.\n" << endl;
        return DeleteUser(vUsers);
    }

    if ( toupper(GetChar("\nAre you sure you delete this User Y/N ? ")) == 'Y' )
        DeleteUserFromFile(vUsers, UserName, Delim);
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

    if ( SearchByAccountNumber( vClients, AccountNumber ) ) {
            cout << "\nClient with Account Number (" << AccountNumber << ") Not Found!\n\nEnter exit to return to the Main Menu.\n" << endl;
            return  UpdateClientInfo(vClients);
    }

    fstream MyFile;
    MyFile.open(ClientsFileName, ios::out ); 
    
    for (stClient Client : vClients)
    {
        if (Client.AccountNumber == AccountNumber) {
            MyFile << ConvertRecordToLineForClient(ReadNewClientAndUpdateClient(vClients, 0, AccountNumber), Delim) << endl;
        }
        else {
            MyFile << ConvertRecordToLineForClient(Client, Delim) << endl;
        }
    }
    MyFile.close();
    cout << "\n\nClient Updated Successfully.\n" << endl;
}

void UpdateUserInfo ( /* New */ vector <stUsers>& vUsers ) {

    string UserName = GetString("Please Enter the User Name? ");

    if (UserName == "exit") {
        return;
    }
    else if (UserName == "Admin") {
        ShowBar("\nYou Cannot UpDate Information This User.");
        return; 
    }

    if ( SearchUser( vUsers, UserName ) ) {
            cout << "\nClient with Account Number (" << UserName << ") Not Found!\n\nEnter exit to return to the Manage Users Menu.\n" << endl;
            return  UpdateUserInfo(vUsers);
    }

    fstream MyFile;
    MyFile.open(UsersFileName, ios::out ); 
    
    for (stUsers User : vUsers)
    {
        if (User.UserName == UserName) {
            MyFile << ConvertRecordToLineForUsers(ReadNewUserAndUpdateUsers(vUsers, 0, UserName), Delim) << endl;
        }
        else {
            MyFile << ConvertRecordToLineForUsers(User, Delim) << endl;
        }
    }
    MyFile.close();
    cout << "\n\nClient Updated Successfully.\n" << endl;
}

//      End Update functions      //

/* ------------------------------ */

// Begin Find Client functions    //

void FindClient ( vector <stClient> vClients ) {

    string AccountNumber = GetString("Please Enter the Account Number Client? ");
        
    if ( SearchByAccountNumber( vClients, AccountNumber ) ) {
        cout << "\nClient with Account Number (" << AccountNumber << ") Not Found!" << endl;
    }
}

void FindUser ( /* New */ vector <stUsers> vUsers ) {

    string UserName = GetString("Please Enter the User Name? ");
        
    if ( SearchUser( vUsers, UserName ) ) {
        cout << "\nUser with (" << UserName << ") Not Found!" << endl;
    }
}

//  End FindClient functions      //

/* ------------------------------ */

// Begin Transactions functions   //

void DepositAndWithdrawTransactions ( vector <stClient>& vClients, string AccountNumber, bool DepositOrWithdraw) {

    double AmountMoney = 0;
    fstream MyFile;

    MyFile.open( ClientsFileName, ios::out ); 
    
    for (stClient& Client : vClients)
    {
        if ( Client.AccountNumber == AccountNumber ) {
            if ( DepositOrWithdraw ) {

                                    /* Withdraw Money */

                AmountMoney = GetNumber("Please Enter Withdraw amount money ? ");

                if ( AmountMoney > Client.AccountBalance ) 
                {
                    cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
                    MyFile.close();
                    return DepositAndWithdrawTransactions ( vClients, AccountNumber, DepositOrWithdraw );
                }
                else if ( checkDepositAndWithdraw( Client.AccountBalance - AmountMoney ) ) {

                    Client.AccountBalance -= AmountMoney;
                    MyFile << ConvertRecordToLineForClient(Client, Delim) << endl;
                }
                else {

                    MyFile << ConvertRecordToLineForClient(Client, Delim) << endl;
                }
            }
            else {
                                    /* Deposit Money */

                AmountMoney = GetNumber("Please Enter Deposit amount money ? ");

                if (checkDepositAndWithdraw( Client.AccountBalance + AmountMoney )) {
                    Client.AccountBalance += AmountMoney;
                    MyFile << ConvertRecordToLineForClient(Client, Delim) << endl;
                }
                else {
                    MyFile << ConvertRecordToLineForClient(Client, Delim) << endl;
                }
            }
        }
        else {
            MyFile << ConvertRecordToLineForClient(Client, Delim) << endl;
        }
    }
    MyFile.close();
}

void DepositScreen ( vector <stClient>& vClients ) {
    
    string AccountNumber = GetString("Please Enter the Account Number Client ? ");

    if (AccountNumber == "exit")
        return;

    if ( !SearchByAccountNumber( vClients, AccountNumber ) ) {
        DepositAndWithdrawTransactions(vClients, AccountNumber, 0);
    }
    else {
        cout << "Client with Account Number (" << AccountNumber << ") Not Found!\n\nEnter exit to return to the Transactions Menu.\n" << endl;
        return  DepositScreen(vClients);
    }
    
}

void WithdrawScreen ( vector <stClient>& vClients ) {
    
    string AccountNumber = GetString("Please Enter the Account Number Client ? ");

    if (AccountNumber == "exit")
    return;

    if ( !SearchByAccountNumber( vClients, AccountNumber ) ) {
        DepositAndWithdrawTransactions(vClients, AccountNumber, 1);
    }
    else {
        cout << "\nClient with Account Number (" << AccountNumber << ") Not Found!\n\nEnter exit to return to the Transactions Menu.\n" << endl;
        return  DepositScreen(vClients);
    }
}

void Transactions ( vector <stClient>& vClients ) {

    system("cls");
    ShowTransactionsMenu();
    vClients = LoadClientsDataFromFile(ClientsFileName, Delim);

    switch ( GetNumber ("Choose what do you to do? [1 To 4]? ", 1, 4 ))
    {
    case eTransactions::eDeposit :
        system("cls");
        ShowBar("Deposit Screen");
        DepositScreen(vClients);
        system("pause");
        return Transactions(vClients);
    case eTransactions::eWithdraw :
        system("cls");
        ShowBar("Withdraw Screen");
        WithdrawScreen(vClients);
        system("pause");
        return Transactions(vClients);
    case eTransactions::eTotalBalances :
        system("cls");
        ShowTotalBalances(vClients);
        system("pause");
        return Transactions(vClients);
    case eTransactions::etMainMenu :
        system("cls");
        break;
    }
}

// End Transactions functions     //

/* ------------------------------ */

// Begin Manage Users functions   //

void ManageUsers () /* New */ {

    system("cls");
    ShowManageUsersMenu();
    vector <stUsers> vUsers = LoadUsersDataFromFile(UsersFileName, Delim);
    

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
    vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName, Delim);
    

    switch ( GetNumber ("Choose what do you to do? [1 To 8]? ", 1, 8) )
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
            Transactions(vClients);
            return OperationCenter();
        case eAppOption::eManageUsersMenu :
            system("cls");
            CheckPermissions(64);
            ManageUsers();
            return OperationCenter();
        case eAppOption::eLogOut :
            return Login();
    }
}

// End OperationCenter functions //

/* ------------------------------ */

// Begin Login functions    //

void Login () /* New */ {

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