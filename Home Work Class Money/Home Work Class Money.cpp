#include <iostream>
#include <iomanip> 
#include <Windows.h>

using namespace std;

class Money
{
private:
    int rub, kop;
public:
    Money();
    Money(int _rub, int _kop);
    void Set_Money(int _rub, int _kop);
    void Print();
    void Convert_Kopecks();
    Money Input_Money();
    Money Addition(int _rub, int _kop);
    Money operator +(const Money &money);
    Money operator -(const Money &money);
    Money Percent(int percent);
    Money operator ++();
};

int main()
{
    Money money, money_2; char menu{};
    int rub{}, kop{}, percent{};
    bool flag = false;
    while (flag == false)
    {
        system("cls");
        cout << "\t\t\t\tMoney editor\n" <<
            "\t\t\Enter P(p) to show your balance\n" <<
            "\t\t\Enter sign (+) to add money to your balance\n" <<
            "\t\tEnter sign (-) to deduct money from your balance\n" <<
            "\t\tEnter the (%) sign to see the percentage of your money on the balance\n" <<
            "\t\tEnter A(a) to add 1 unit to your amount of rubles and kopecks on the balance\n" <<
            "\t\tEnter E(e) to exit the editor\n\n" <<
            "\t\t\tEnter a command to select an action : ";
        cin >> menu;
        switch (menu)
        {
        case 'P':
        case 'p':
            system("cls");
            cout << "Your balance : ";
            money.Print();
            cout << endl;
            system("pause");
            break;
        case '+':
            cout << "\t\tEnter the amount of money you want to add to your balance\n" <<
                "\tThe limit of rubles to add = 100000\n" <<
                "\tThe limit of kopecks to add = 99\n";
            money_2.Input_Money();
            money + money_2;
            cout << "\t\t\tMoney successfully added\n";
            system("pause");
            break;
        case '-':
            system("cls");
            money.Print();
            cout << "\tImportant! The money you want to withdraw" <<
                " must not exceed the amount of your balance\n" <<
                "\tThe limit of rubles to withdraw = 100000\n" <<
                "\tThe limit of kopecks to withdraw = 99\n";
            money_2.Input_Money();
            money - money_2;
            cout << "\t\t\tMoney successfully withdrawn\n";
            system("pause");
            break;
        case '%':
            cout << "Specify the percentage to be calculated" <<
                " from the amount of money on your balance\n" <<
                "Percent : "; cin >> percent;
            while (percent < 1 || percent > 100)
            {
                cout << "Error. Try again\n" <<
                    "Percent : "; cin >> percent;
            }
            money_2 = money.Percent(percent);
            cout << percent << " percent of the amount of money on your balance = ";
            money_2.Print();
            system("pause");
            break;
        case 'A':
        case 'a':
            system("cls");
            ++money;
            cout << "1 unit has been successfully added" <<
                " to the amount of rubles and kopecks on your balance\n";
            system("pause");
            break;
        case 'E':
        case'e':
            cout << "\t\tThe program exits\n";
            system("pause");
            flag = true;
            break;
        default:
            cout << "\t\tMistake. Wrong command\n";
            system("pause");
            break;
        }
    }
    system("pause");
}

Money::Money()
{
    rub = 10000;
    kop = 0;
}

Money::Money(int _rub, int _kop)
{
    if (_rub >= 0) rub = _rub;
    else cout << "Error\n";
    if (_kop >= 0) kop = _kop;
    else cout << "Error\n";
}

void Money::Set_Money(int _rub, int _kop)
{
    if (_rub >= 0) rub = _rub;
    else cout << "Error\n";
    if (_kop >= 0 && kop < 100) kop = _kop;
    else cout << "Error\n";
}

void Money::Print()
{
    cout << rub << " rubles. " << kop << " kopecks.\n";
}

void Money::Convert_Kopecks()
{
    if (kop > 99) {
        ++rub;
        kop %= 100;
    }
}

Money Money::Input_Money()
{
    cout << "\t\tEnter the number of rubles : "; cin >> rub;
    cout << "\t\tEnter the number of kopecks : "; cin >> kop;
    while (rub < 0 || rub > 100000 ||
        kop < 0 || kop > 99)
    {
        cout << "\tInput error. Try again\n";
        cout << "\t\tEnter the number of rubles : "; cin >> rub;
        cout << "\t\tEnter the number of kopecks : "; cin >> kop;
    }
    return Money();
}

Money Money::Addition(int _rub, int _kop)
{
    if (_rub < 0) cout << "Error\n";
    else
    {
        rub += _rub;
    }
    if (_kop < 0) cout << "Error\n";
    else
    {
        kop += _kop;
    }
    Convert_Kopecks();
    return Money();
}

Money Money::operator +(const Money &money)
{
    rub = rub + money.rub;
    kop = kop + money.kop;
    Convert_Kopecks();
    return Money();
}

Money Money::operator - (const Money &money)
{
    if (rub < money.rub) cout << "Error\n";
    else rub = rub - money.rub;
    if (kop < money.kop && rub > 0) {
        --rub;
        kop += 100 - money.kop;
    }
    else if (kop < money.kop && rub == 0) cout << "Error";
    else kop -= money.kop;
    return Money();
}

Money Money::Percent(int percent)
{
    Money tmp;
    tmp.rub = rub * (float)percent / 100;
    tmp.kop = kop * (float)percent / 100;
    if (tmp.rub % percent > 0) tmp.kop += rub % percent;
    tmp.Convert_Kopecks();
    return tmp;
}

Money Money::operator++()
{
    ++rub, ++kop;
    if (kop > 99) {
        ++rub;
        kop %= 100;
    }
    return Money();
}
