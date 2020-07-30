/*
 * ATM Ver 0.1 
*/

#include <iostream>

using namespace std;
const int NAME_LEN = 10;

void ShowMenu();
void MakeAccount();
void Deposit();
void Withdraw();
void ShowAccInfo();
int FindAccountByID(int); // helper function to find index of a specific account by its id

enum
{
    MAKE = 1,
    DEPOSIT,
    WITHDRAW,
    INQUIRE,
    EXIT
};

typedef struct
{
    int accId;
    int balance;
    char name[NAME_LEN];
} Account;

Account accArr[100];
int accNum = 0;

int main(void)
{
    int choise;

    while (choise != EXIT)
    {
        ShowMenu();
        cout << "Choise: ";
        cin >> choise;

        switch (choise)
        {
        case MAKE:
            MakeAccount();
            break;
        case DEPOSIT:
            Deposit();
            break;
        case WITHDRAW:
            Withdraw();
            break;
        case INQUIRE:
            ShowAccInfo();
            break;
        case EXIT:
            break;
        default:
            cout << "INVALID SELECTION.." << endl;
        }
    }

    return 0;
}

void ShowMenu()
{
    cout << "-----Menu-----" << endl;
    cout << "1. Make an account" << endl;
    cout << "2. Deposit" << endl;
    cout << "3. Withdraw" << endl;
    cout << "4. Account information" << endl;
    cout << "5. End transaction" << endl;
}

void MakeAccount()
{
    int id;
    char name[NAME_LEN];
    int deposit;

    cout << "Open an account" << endl;
    cout << "Account ID: ";
    cin >> id;
    cout << "Name: ";
    cin >> name;
    cout << "Deposit: ";
    cin >> deposit;
    cout << endl;

    accArr[accNum].accId = id;
    strcpy(accArr[accNum].name, name);
    accArr[accNum].balance = deposit;
    accNum += 1;
}

void Deposit()
{
    int id;
    int money;

    cout << "Deposit" << endl;
    cout << "Account ID: ";
    cin >> id;

    int idx = FindAccountByID(id);

    if (idx == -1)
        cout << "Invalid Account ID" << endl;
    else
    {
        cout << "Amount to deposit: ";
        cin >> money;

        accArr[idx].balance += money;
        cout << "Transaction has been made." << endl;
    }
}

void Withdraw()
{
    int id;
    int money;

    cout << "Withdrawal" << endl;
    cout << "Account ID: ";
    cin >> id;

    int idx = FindAccountByID(id);

    if (idx != -1)
    {
        cout << "Amount to withdraw: ";
        cin >> money;

        if (accArr[idx].balance < money)
        {
            cout << "Not enough balance" << endl;
        }
        else
        {
            accArr[idx].balance -= money;
            cout << "Transaction has been made." << endl;
        }
    }
    else
    {
        cout << "Invalid Account ID" << endl;
    }
}

void ShowAccInfo()
{
    for (int i = 0; i < accNum; i++)
    {
        cout << "AccId: " << accArr[i].accId << endl;
        cout << "Name: " << accArr[i].name << endl;
        cout << "Balance: " << accArr[i].balance << endl;
    }
}

int FindAccountByID(int id)
{
    for (int i = 0; i < accNum; i++)
    {
        if (accArr[i].accId == id)
            return i;
    }

    return -1;
}