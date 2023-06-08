#include<iostream>
#include<fstream>
#include<map>
#include<cstdlib>
#include<vector>
using namespace std;

#define MIN_BALANCE 500
class InsufficientBalance{};
//_-_-_-_-_-_-_-_-_-_-_-_-CLASS DEFINITION OF ACCOUNT-_-_-_-_-_-_-_-_-_-_-_-_
class Account{
    private:
        string name;
        float balance;
        static long NextAvailableAccountNumber;
    public:
        long accountNumber;
        Account(){}
        Account(string name,float balance);
        long getAccountNum(){
            return accountNumber;
        }
        string getName(){
            return name;
        }
        float getBalance(){
            return balance;
        }
        void setName(const string& newName)
        {
            name = newName;
        }

        void setBalance(float newBalance)
        {
            balance = newBalance;
        }

        void Deposit(float amount);
        void Withdraw(float amount);
        static void SetLastAccountNumber(long accountNumber);
        static long getLastAccountNumber();
        friend ofstream & operator<<(ofstream &ofs,Account &account);
        friend ifstream & operator>>(ofstream &ifs,Account &account);
        friend ostream & operator<<(ostream &os,Account &account);
};
long Account::NextAvailableAccountNumber=0;

//_-_-_-_-_-_-_-_-_-_-_-_-CLASS DEFINTION OF BANK-_-_-_-_-_-_-_-_-_-_-_-_
class Bank{
    private:
        map<long,Account> account_map;
    public:
        Bank();
        Account open_account(string name,float balance);
        Account BalanceEnquiry(long accountNumber);
        Account Deposit(long accountNumber,float amount);
        Account Withdraw(long accountNumber,float amount);
        Account modify_account(long accountNumber,string& name);
        float CalculateLoanAmount(long accountNumber,float monthly_income);
        void CloseAccount(long accountNumber);
        void ListAllAccounts();
        ~Bank();
};

int main()
{
    Bank sbi;
    Account account;

    string name;
    long accountNumber;
    float balance;
    float amount;
    int choice;

    system("cls");
    do{
        cout<<"\n\t\t\t__________________________________";
        cout<<"\n\t\t\t|_-_-_-_-_Banking System_-_-_-_-_|\n";
        cout<<"\t\t\t| 1.Open New Account             |";
        cout<<"\n\t\t\t| 2.Balance Enquiry              |"
            <<"\n\t\t\t| 3.Deposit Balance              |"
            <<"\n\t\t\t| 4.Withdraw Balance             |"
            <<"\n\t\t\t| 5.Modify Account Details       |"
            <<"\n\t\t\t| 6.List All Accounts            |"
            <<"\n\t\t\t| 7.Close an Account             |"
            <<"\n\t\t\t| 8.Max Loan Amount              |"
            <<"\n\t\t\t| 9.Exit                         |"
            <<"\n\t\t\t|_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|";
        
        cout<<"\nEnter choice:";
        cin>>choice;

        switch (choice)
        {
            case 1:
                cout<<"Enter Name of Account holder:";
                cin.ignore();
                getline(cin, name);
                cout<<"Enter initial Balance:";
                cin>>balance;
                account=sbi.open_account(name,balance);
                cout<<endl<<"Congratulation for New Account";
                cout<<account;
                break;
            case 2:
                cout<<"Enter Account Number:";
                cin>>accountNumber;
                account=sbi.BalanceEnquiry(accountNumber);
                cout<<endl<<"Details of This Account"<<endl;
                cout<<account;
                break;
            case 3:
                cout<<"Enter Account Number:";
                cin>>accountNumber;
                cout<<"Enter amount to be deposited:";
                cin>>amount;
                account=sbi.Deposit(accountNumber,amount);
                cout<<endl<<"Amount has been successfully deposited to the account"<<endl;
                cout<<account;
                break;
            case 4:
                cout<<"Enter Account Number:";
                cin>>accountNumber;
                cout<<"Enter amount you wish to withdraw:";
                cin>>amount;
                account=sbi.Withdraw(accountNumber,amount);
                cout<<endl<<"Amount has been successfully withdrawn";
                cout<<account;
                break;
            case 5:
                cout<<"Enter Account Number:";
                cin>>accountNumber;
                cout<<"Enter new name:";
                cin.ignore();
                getline(cin, name);
                account=sbi.modify_account(accountNumber,name);
                cout<<endl<<"Account holder name is modified successfully";
                cout<<account;
                break;
            case 6:
                sbi.ListAllAccounts();
                break;
            case 7:
                cout<<"Enter account Number:";
                cin>>accountNumber;
                sbi.CloseAccount(accountNumber);
                cout<<endl<<"Thanks for being part of our bank";
                break;
            case 8:
                float monthly_income;
                cout<<"Enter account Number:";
                cin>>accountNumber;
                cout<<"Enter your monthly income:";
                cin>>monthly_income;
                cout<<"Max amount of loan that can be granted:";
                cout<<sbi.CalculateLoanAmount(accountNumber,monthly_income);
                break;
            case 9:
                cout<<"Thanks for using our Banking System";
                break;
            default:
                cout<<"You've entered Wrong choice";
                break;
        }
    }while(choice!=9);
    return 0;
}

//_-_-_-_-_-_-_-_-_-_-_-_-MEMBER FUNCTIONS OF CLASS ACCOUNT-_-_-_-_-_-_-_-_-_-_-_-_
Account::Account(string name,float balance){
    NextAvailableAccountNumber++;
    accountNumber=NextAvailableAccountNumber;
    this->name=name;
    this->balance=balance;
}
void Account::Deposit(float amount){
    balance+=amount;
}
void Account::Withdraw(float amount){
    if(balance-amount<MIN_BALANCE)
        throw InsufficientBalance();
    balance-=amount;
}
void Account::SetLastAccountNumber(long accountNumber){
    NextAvailableAccountNumber=accountNumber;
}
long Account::getLastAccountNumber(){
    return NextAvailableAccountNumber;
}
ofstream & operator<<(ofstream &ofs,Account &account){
    ofs<<account.accountNumber<<endl;
    ofs<<account.name<<endl;
    ofs<<account.balance<<endl;
    return ofs;
}
ifstream& operator>>(ifstream& ifs, Account& account)
{
    ifs >> account.accountNumber;
    string name;
    float balance;
    ifs.ignore(); // Skip the newline character after accountNumber
    getline(ifs, name);
    ifs >> balance;

    account.setName(name);
    account.setBalance(balance);

    return ifs;
}
ostream & operator<<(ostream &os,Account &account){
    os<<"Name:"<<account.getName()<<endl;
    os<<"Account Number:"<<account.getAccountNum()<<endl;
    os<<"Balance:"<<account.getBalance()<<endl;
    return os;
}

//_-_-_-_-_-_-_-_-_-_-_-_-MEMBER FUNCTIONS OF CLASS BANK-_-_-_-_-_-_-_-_-_-_-_-_
Bank::Bank(){
    Account account;
    ifstream infile;
    infile.open("Bank.data");
    if(!infile){
        cout<<"Error in Opening!File not found";
        return;
    }
    while(!infile.eof()){
        infile>>account;
        account_map.insert(pair<long,Account>(account.getAccountNum(),account));
    }
    Account::SetLastAccountNumber(account.getAccountNum());
    infile.close();
}

Account Bank::open_account(string name,float balance){
    ofstream outfile;
    Account account(name,balance);
    account_map.insert(pair<long,Account>(account.getAccountNum(),account));
    
    outfile.open("Bank.data", ios::trunc);
    
    map<long,Account>::iterator itr;
    for(itr=account_map.begin();itr!=account_map.end();itr++)
    {
        outfile<<itr->second;
    }
    outfile.close();
    return account;
}
Account Bank::BalanceEnquiry(long accountNumber){
    map<long,Account>::iterator itr=account_map.find(accountNumber);
    return itr->second;
}
Account Bank::Deposit(long accountNumber,float amount)
{
    map<long,Account>::iterator itr=account_map.find(accountNumber);
    itr->second.Deposit(amount);
    return itr->second;
}
Account Bank::Withdraw(long accountNumber,float amount)
{
    map<long,Account>::iterator itr=account_map.find(accountNumber);
    itr->second.Withdraw(amount);
    return itr->second;
}
Account Bank::modify_account(long accountNumber,string& newName)
{
    map<long, Account>::iterator itr = account_map.find(accountNumber);
    if (itr != account_map.end()) {
        itr->second.setName(newName);
        cout << "Account holder name modified successfully." << endl;
    }
    else {
        cout << "Account not found. Unable to modify account holder name." << endl;
    }
    cout<<endl;
    return itr->second;
}
float Bank::CalculateLoanAmount(long accountNumber,float monthly_income){
    const float minMonthlyIncome = 2000.0;
    const float minAccountBalance = 1000.0;
    const float maxLoanPercentage = 2.5; 
    map<long,Account>::iterator itr=account_map.find(accountNumber);
    float Balance=itr->second.getBalance();
    // Check eligibility
    if (monthly_income >= minMonthlyIncome && Balance >= minAccountBalance) {
        // Calculate loan amount
        float maxLoanAmount = monthly_income * maxLoanPercentage;
        return maxLoanAmount;
    }
    else {
        // Not eligible for a loan
        return 0.0;
    }
}
void Bank::CloseAccount(long accountNumber)
{
    map<long,Account>::iterator itr=account_map.find(accountNumber);
    cout<<"Account Deleted"<<itr->second;
    account_map.erase(accountNumber);
}
void Bank::ListAllAccounts()
{
    map<long,Account>::iterator itr;
    for(itr=account_map.begin();itr!=account_map.end();itr++)
    {
    cout<<"Account "<<itr->first<<endl<<itr->second<<endl;
    }
}
Bank::~Bank()
{
    ofstream outfile;
    outfile.open("Bank.data", ios::trunc);
    
    map<long,Account>::iterator itr;
    for(itr=account_map.begin();itr!=account_map.end();itr++)
    {
        outfile<<itr->second;
    }
    outfile.close();
}