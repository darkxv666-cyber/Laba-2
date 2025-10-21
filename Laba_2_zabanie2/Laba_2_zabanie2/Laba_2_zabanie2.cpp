#include <iostream>
#include <cmath>
#include <locale> // Для работы с локалью

using namespace std;

class Fraction {
private:
    int numerator;   // числитель
    int denominator; // знаменатель

    static int quantity; // счетчик экземпляров дробей

public:
    // Конструктор
    Fraction(int num = 0, int denom = 1) : numerator(num), denominator(denom) {
        if (denominator == 0) {
            cerr << "Ошибка: знаменатель не может быть равен нулю." << endl;
            denominator = 1;
        }
        reduce();
        quantity++;
    }

    ~Fraction() {
        quantity--;
    }

    void reduce() {
        int gcd_value = gcd(abs(numerator), abs(denominator));
        numerator /= gcd_value;
        denominator /= gcd_value;
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

    static int gcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    Fraction operator+(const Fraction& other) const {
        return Fraction(numerator * other.denominator + other.numerator * denominator,
            denominator * other.denominator);
    }

    Fraction operator-(const Fraction& other) const {
        return Fraction(numerator * other.denominator - other.numerator * denominator,
            denominator * other.denominator);
    }

    Fraction operator*(const Fraction& other) const {
        return Fraction(numerator * other.numerator, denominator * other.denominator);
    }

    Fraction operator/(const Fraction& other) const {
        return Fraction(numerator * other.denominator, denominator * other.numerator);
    }

    friend ostream& operator<<(ostream& os, const Fraction& frac) {
        os << frac.numerator << "/" << frac.denominator;
        return os;
    }

    static void printAsFraction(double decimal_fraction) {
        int denominator = 1;
        while (decimal_fraction != floor(decimal_fraction)) {
            decimal_fraction *= 10;
            denominator *= 10;
        }
        int numerator = static_cast<int>(decimal_fraction);
        Fraction frac(numerator, denominator);
        cout << frac << endl;
    }

    static int getInstanceCount() {
        return quantity;
    }
};

int Fraction::quantity = 0;

int main() {

    setlocale(LC_ALL, "Russian");

    int num1, denom1, num2, denom2;

    cout << "Введите числитель первой дроби: ";
    cin >> num1;
    cout << "Введите знаменатель первой дроби: ";
    cin >> denom1;
    Fraction frac1(num1, denom1);

    cout << "Введите числитель второй дроби: ";
    cin >> num2;
    cout << "Введите знаменатель второй дроби: ";
    cin >> denom2;
    Fraction frac2(num2, denom2);

    cout << "Дробь 1: " << frac1 << endl;
    cout << "Дробь 2: " << frac2 << endl;

    Fraction result_add = frac1 + frac2;
    Fraction result_sub = frac1 - frac2;
    Fraction result_mul = frac1 * frac2;
    Fraction result_div = frac1 / frac2;

    cout << "Результат сложения: " << result_add << endl;
    cout << "Результат вычитания: " << result_sub << endl;
    cout << "Результат умножения: " << result_mul << endl;
    cout << "Результат деления: " << result_div << endl;

    double decimal_fraction;
    cout << "Введите десятичную дробь: ";
    cin >> decimal_fraction;

    cout << "Представление " << decimal_fraction << " как обыкновенной дроби: ";
    Fraction::printAsFraction(decimal_fraction);

    cout << "Количество созданных дробей: " << Fraction::getInstanceCount() << endl;

    return 0;
}
