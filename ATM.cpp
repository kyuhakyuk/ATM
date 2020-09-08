/*
 * ATM Ver 0.5
*/

#include <iostream>

using namespace std;
const int NAME_LEN = 10;

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
    Account(int accId, int balance, char *name);
    Account(const Account &copy);
    ~Account();
    void Deposit(int money);
    bool Withdraw(int money);
    void ShowInfo() const;
    int GetID() const;
};

Account::Account(int accId, int balance, char *name) : accId(accId), balance(balance)
{
    cusName = new char[strlen(name) + 1];
    stpcpy(cusName, name);
}

Account::Account(const Account &copy) : accId(copy.accId), balance(copy.balance)
{
    cusName = new char[strlen(copy.cusName) + 1];
    stpcpy(cusName, copy.cusName);
}

Account::~Account()
{
    delete[] cusName;
    cout << "Called Destructor " << this << endl;
}

void Account::Deposit(int money)
{
    balance += money;
}

bool Account::Withdraw(int money)
{
    if (balance < money)
    {
        return false;
    }

    balance -= money;
    return true;
}

void Account::ShowInfo() const
{
    cout << "AccId: " << accId << endl;
    cout << "Name: " << cusName << endl;
    cout << "Balance: " << balance << endl;
}

int Account::GetID() const
{
    return accId;
}

class AccountHandler
{
private:
    Account *accArr[100];
    int accNum;

public:
    AccountHandler();
    void ShowMenu() const;
    void MakeAccount();
    void Deposit();
    void Withdraw();
    void ShowAccInfo() const;
    int FindAccountByID(int) const;
    ~AccountHandler();
};

AccountHandler::AccountHandler()
{
    accNum = 0;
}

AccountHandler::~AccountHandler()
{
    for (int i = 0; i <= accNum; i++)
    {
        delete accArr[i];
    }
}

void AccountHandler::ShowMenu() const
{
    cout << "-----Menu-----" << endl;
    cout << "1. Make an account" << endl;
    cout << "2. Deposit" << endl;
    cout << "3. Withdraw" << endl;
    cout << "4. Account information" << endl;
    cout << "5. End transaction" << endl;
}

void AccountHandler::MakeAccount()
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

void AccountHandler::Deposit()
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

void AccountHandler::Withdraw()
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

void AccountHandler::ShowAccInfo() const
{
    for (int i = 0; i < accNum; i++)
    {
        accArr[i]->ShowInfo();
    }
}

int AccountHandler::FindAccountByID(int id) const
{
    for (int i = 0; i < accNum; i++)
    {
        if (accArr[i]->GetID() == id)
            return i;
    }

    return -1;
}

int main(void)
{
    int choise;
    AccountHandler manager;

    while (choise != EXIT)
    {
        manager.ShowMenu();
        cout << "Choise: ";
        cin >> choise;

        switch (choise)
        {
        case MAKE:
            manager.MakeAccount();
            break;
        case DEPOSIT:
            manager.Deposit();
            break;
        case WITHDRAW:
            manager.Withdraw();
            break;
        case INQUIRE:
            manager.ShowAccInfo();
            break;
        case EXIT:
            break;
        default:
            cout << "INVALID SELECTION.." << endl;
        }
    }

    return 0;
}