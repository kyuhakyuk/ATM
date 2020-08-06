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

class Account
{
private:
    int accId;
    int balance;
    char *cusName;

public:
    Account(int accId, int balance, char *name) : accId(accId), balance(balance)
    {
        cusName = new char[strlen(name) + 1];
        stpcpy(cusName, name);
    }

    Account(const Account &copy) : accId(copy.accId), balance(copy.balance)
    {
        cusName = new char[strlen(copy.cusName) + 1];
        stpcpy(cusName, copy.cusName);
    }

    ~Account()
    {
        delete[] cusName;
        cout << "Called Destructor " << this << endl;
    }

    void Deposit(int money)
    {
        balance += money;
    }

    bool Withdraw(int money)
    {
        if (balance < money)
        {
            return false;
        }

        balance -= money;
        return true;
    }

    void ShowInfo() const
    {
        cout << "AccId: " << accId << endl;
        cout << "Name: " << cusName << endl;
        cout << "Balance: " << balance << endl;
    }

    int GetID() const
    {
        return accId;
    }
};

Account *accArr[100];
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

    accArr[accNum] = new Account(id, deposit, name);
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

        accArr[idx]->Deposit(money);
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

        if (!accArr[idx]->Withdraw(money))
        {
            cout << "Not enough balance" << endl;
        }
        else
        {
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
        accArr[i]->ShowInfo();
    }
}

int FindAccountByID(int id)
{
    for (int i = 0; i < accNum; i++)
    {
        if (accArr[i]->GetID() == id)
            return i;
    }

    return -1;
}