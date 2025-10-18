#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

enum enMainMenuChoice {QuickWithdraw = 1, NormalWithdraw = 2, Deposit = 3, CheckBalance = 4, Logout = 5};
enum enQuickWithdraw {Twenty = 1, Fifty = 2, Hundred = 3, TwoHundred = 4, FourHundreds = 5, SixHundreds = 6, EightHundreds = 7, Thousand = 8, Exit = 9 };

struct stClientDetails {
    string accNumber;
    string pinCode;
    string holderName;
    string phone;
    double balance;
    bool markForDelete = false;
};

void performMainMenu(enMainMenuChoice choice,stClientDetails &c,vector<stClientDetails> &vClients);
void mainMenu(stClientDetails &c,vector<stClientDetails> &vClients);
void login();
string readAccountNumber() {
    string acc;
    cout << "Enter the account number : ";
    getline(cin,acc);
    return acc;
}

string readPinCode() {
    string pin;
    cout << "Enter the pin code : ";
    getline(cin,pin);
    return pin;
}

short readMainMenuChoice() {
    short num;
    do {
        cout << "Choose What do you want to do ? [1 to 5]\n";
        cin >> num;
    }while (num < 1 || num > 5);
    return num;
}

vector<string> split(string s , string delim) {
    vector<string> words;
    short pos = 0;
    string subWord = "";
    while ((pos = s.find(delim)) != std::string::npos) {
        subWord = s.substr(0,pos);
        if (subWord != "")
            words.push_back(subWord);
        s.erase(0,pos + delim.length());
    }
    if (s != "")
        words.push_back(s);
    return words;
}

stClientDetails converClientLineToRecord(string line,string delim = "#//#") {
    stClientDetails client;
    vector<string> vString = split(line, delim);
    client.accNumber = vString[0];
    client.pinCode = vString[1];
    client.holderName = vString[2];
    client.phone = vString[3];
    client.balance = stod(vString[4]);
    return client;
}

vector<stClientDetails> loadClientsDataFromFile(string fileName) {
    vector<stClientDetails> clients;
    stClientDetails client;
    ifstream file;
    string line;
    file.open(fileName);
    if (file.is_open()) {
        while (getline(file,line)) {
            client = converClientLineToRecord(line);
            clients.push_back(client);
        }
    }
    else {
        cout << "\nError : File not found!\n";
    }
    return clients;
}

bool findClientByAccountNumber(string accountNumber, stClientDetails &client, vector<stClientDetails> &vClients) {
    for (stClientDetails &c : vClients) {
        if (c.accNumber == accountNumber) {
            client = c;
            return true;
        }
    }
    return false;
}

short readQuickWithdrawChoice() {
    short choice;
    cout << "Choose What to do you want ? [ 1 to 9 ]\n";
    cin >> choice;
    return choice;
}

string convertClientRecordToLine(stClientDetails client , string delim = "#//#") {
    string line = "";
    line += client.accNumber + delim;
    line += client.pinCode + delim;
    line += client.holderName + delim;
    line += client.phone + delim;
    line += to_string(client.balance);

    return line;
}

vector<stClientDetails> SaveCleintsDataToFile(string fileName, vector<stClientDetails> &vClients) {
    fstream myFile;
    myFile.open(fileName,ios::out);
    string line;
    if (myFile.is_open()) {
        for (stClientDetails &c : vClients) {
            if (c.markForDelete == false) {
                line = convertClientRecordToLine(c);
                myFile << line << endl;
            }
        }
        myFile.close();
    }
    return vClients;
}

void printClientRecord(stClientDetails Client) {
    cout << "| " << setw(15) << left << Client.accNumber;
    cout << "| " << setw(10) << left << Client.pinCode;
    cout << "| " << setw(40) << left << Client.holderName;
    cout << "| " << setw(12) << left << Client.phone;
    cout << "| " << setw(12) << left << Client.balance << endl;
}

stClientDetails changeClientRecord(string accNumber) {
    stClientDetails client;
    client.accNumber = accNumber;
    cin.ignore();
    cout << "Enter Pincode :";
    getline(cin,client.pinCode);;
    cout << "Enter a name : ";
    getline(cin,client.holderName);
    cout << "Enter a Phone Number : ";
    getline(cin,client.phone);
    cout << "Enter a balance : ";
    cin >> client.balance;

    return client;
}

void updateClientRecord(stClientDetails updatedClient, vector<stClientDetails> &vClients) {
    for (stClientDetails &client : vClients) {
        if (client.accNumber == updatedClient.accNumber) {
            client = updatedClient;
            break;
        }
    }
}


void performQuickWithdraw(enQuickWithdraw choice,stClientDetails &c,vector<stClientDetails> &vClients) {
    switch (choice) {
        case enQuickWithdraw::Twenty:
            if (c.balance >= 20)
            c.balance -= 20;
            else
                cout << "Your balance is lower than balance you want to withdraw!\n";
            break;
        case enQuickWithdraw::Fifty:
            if (c.balance >= 50)
            c.balance -= 50;
            else
                cout << "Your balance is lower than balance you want to withdraw!\n";
            break;
        case enQuickWithdraw::Hundred:
            if (c.balance >= 100)
            c.balance -= 100;
            else
                cout << "Your balance is lower than balance you want to withdraw!\n";
            break;
        case enQuickWithdraw::TwoHundred:
            if (c.balance >= 200)
            c.balance -= 200;
            else
                cout << "Your balance is lower than balance you want to withdraw!\n";
            break;
        case enQuickWithdraw::FourHundreds:
            if (c.balance >= 400)
            c.balance -= 400;
            else
                cout << "Your balance is lower than balance you want to withdraw!\n";
            break;
        case enQuickWithdraw::SixHundreds:
            if (c.balance >= 600)
            c.balance -= 600;
            else
                cout << "Your balance is lower than balance you want to withdraw!\n";
            break;
        case enQuickWithdraw::EightHundreds:
            if (c.balance >= 800)
            c.balance -= 800;
            else
                cout << "Your balance is lower than balance you want to withdraw!\n";
            break;
        case enQuickWithdraw::Thousand:
            if (c.balance >= 1000)
            c.balance -= 1000;
            else
                cout << "Your balance is lower than balance you want to withdraw!\n";
            break;
        default:
            mainMenu(c,vClients);
    }
    cout << "Your Balance is : " << c.balance << "$" << endl;
    updateClientRecord(c,vClients);
    SaveCleintsDataToFile("Clients.txt",vClients);
}

void quickWithdraw(stClientDetails &c,vector<stClientDetails> &vClients) {
    short choice;
    cout << "==============================\n";
    cout << "[ 1 ] 20$ \t [ 2 ] 50$\n";
    cout << "[ 3 ] 100$ \t [ 4 ] 200$\n";
    cout << "[ 5 ] 400$ \t [ 6 ] 600$\n";
    cout << "[ 7 ] 800$ \t [ 8 ] 1000$\n";
    cout << "[ 9 ] Exit\n";
    cout << "==============================\n";
    cout << "Your balance is " << c.balance <<"$\n";
    choice = readQuickWithdrawChoice();
    performQuickWithdraw(enQuickWithdraw(choice),c,vClients);
}

double readBalance() {
    double balance;
    cout << "Enter a balance : ";
    cin >> balance;
    return balance;
}

void deposit(double balance,stClientDetails &c,vector<stClientDetails> &vClients) {
    if (balance < 1)
        cout << "You can't deposit balance <= 0\n";
    else {
        c.balance += balance;
        updateClientRecord(c,vClients);
        SaveCleintsDataToFile("Clients.txt",vClients);
    }
    cout << "Your balance is : " << c.balance << endl;
}

void normalWithdraw(stClientDetails &c, vector<stClientDetails> &vClients) {
    int balance;
    cout << "Enter a balance to withdraw [ balance % 5 = 0 ] : ";
    cin >> balance;
    if (balance > c.balance)
        cout << "You cant withdraw because it is sufficient. \n";
    while (balance % 5 != 0) {
        cout << "Enter a balance to withdraw [ balance % 5 = 0 ] : ";
        cin >> balance;
    }
    c.balance -= balance;
    updateClientRecord(c,vClients);
    SaveCleintsDataToFile("Clients.txt",vClients);
    cout << "Your Balance is : " << c.balance;
}

void performMainMenu(enMainMenuChoice choice,stClientDetails &c,vector<stClientDetails> &vClients) {
    switch (choice) {
        case enMainMenuChoice::QuickWithdraw:
            quickWithdraw(c,vClients);
            system("pause");
            mainMenu(c,vClients);
            break;
        case enMainMenuChoice::NormalWithdraw:
            normalWithdraw(c,vClients);
            system("pause");
            mainMenu(c,vClients);
            break;
        case enMainMenuChoice::Deposit:
            deposit(readBalance(),c,vClients);
            system("pause");
            mainMenu(c,vClients);
            break;
        case enMainMenuChoice::CheckBalance:
            cout << "Your balance is : " << c.balance << "$";
            system("pause");
            mainMenu(c,vClients);
            break;
        case enMainMenuChoice::Logout:
            login();
            cin.ignore();
    }
}

void mainMenu(stClientDetails &c,vector<stClientDetails> &vClients) {
    cout << "==================================\n";
    cout << "\tATM Main Menu Screen\n";
    cout << "==================================\n";
    cout << "[ 1 ] Quick Withdraw.\n";
    cout << "[ 2 ] Normal Withdraw.\n";
    cout << "[ 3 ] Deposit.\n";
    cout << "[ 4 ] Check Balance.\n";
    cout << "[ 5 ] Logout.\n";
    cout << "==================================\n";
    performMainMenu((enMainMenuChoice)readMainMenuChoice(),c,vClients);

}

void login() {
    bool check;
    stClientDetails c;
    vector<stClientDetails> vClients = loadClientsDataFromFile("Clients.txt");
    string accountNumber;
    string pin;
    cout << "--------------------------------\n";
    cout << "\tLogin Screen\n";
    cout << "--------------------------------\n";
    do {
        cin.ignore();
        accountNumber = readAccountNumber();
        pin = readPinCode();

        check = findClientByAccountNumber(accountNumber, c, vClients) && c.pinCode == pin;

        if (!check)
            cout << "Invalid account number or pin code, please try again:\n";
    } while (!check);
    mainMenu(c,vClients);
}

int main() {
    login();
    return 0;
}