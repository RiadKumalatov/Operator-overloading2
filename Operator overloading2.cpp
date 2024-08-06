#include <iostream>
#include <stdexcept> 

class Fraction
{
private:
    int numerator_;
    int denominator_;

    // Ïðèâàòíûé ìåòîä äëÿ óïðîùåíèÿ äðîáè (åñëè íóæíî)
    void reduce()
    {
        int gcd = compute_gcd(numerator_, denominator_);
        numerator_ /= gcd;
        denominator_ /= gcd;
    }

    // Ôóíêöèÿ äëÿ âû÷èñëåíèÿ ÍÎÄ (íàèáîëüøåãî îáùåãî äåëèòåëÿ)
    int compute_gcd(int a, int b) const
    {
        while (b != 0)
        {
            int t = b;
            b = a % b;
            a = t;
        }
        return a;
    }

public:
    Fraction(int numerator = 0, int denominator = 1)
    {
        if (denominator == 0) {
            throw std::invalid_argument("Denominator cannot be zero");
        }
        numerator_ = numerator;
        denominator_ = denominator;
        reduce();
    }

    bool operator==(const Fraction& other) const
    {
        return numerator_ * other.denominator_ == other.numerator_ * denominator_;
    }

    bool operator!=(const Fraction& other) const
    {
        return !(*this == other);
    }

    bool operator<(const Fraction& other) const
    {
        return numerator_ * other.denominator_ < other.numerator_ * denominator_;
    }

    bool operator<=(const Fraction& other) const
    {
        return *this < other || *this == other;
    }

    bool operator>(const Fraction& other) const
    {
        return !(*this <= other);
    }

    bool operator>=(const Fraction& other) const
    {
        return !(*this < other);
    }

    Fraction operator+(const Fraction& other) const
    {
        int num = numerator_ * other.denominator_ + other.numerator_ * denominator_;
        int denom = denominator_ * other.denominator_;
        return Fraction(num, denom);
    }

    Fraction operator-(const Fraction& other) const
    {
        int num = numerator_ * other.denominator_ - other.numerator_ * denominator_;
        int denom = denominator_ * other.denominator_;
        return Fraction(num, denom);
    }

    Fraction operator*(const Fraction& other) const
    {
        return Fraction(numerator_ * other.numerator_, denominator_ * other.denominator_);
    }

    Fraction operator/(const Fraction& other) const
    {
        if (other.numerator_ == 0) {
            throw std::invalid_argument("Cannot divide by zero");
        }
        return Fraction(numerator_ * other.denominator_, denominator_ * other.numerator_);
    }

    Fraction operator-() const
    {
        return Fraction(-numerator_, denominator_);
    }

    Fraction& operator++()
    {
        numerator_ += denominator_;
        reduce();
        return *this;
    }

    Fraction operator++(int)
    {
        Fraction temp(*this);
        numerator_ += denominator_;
        reduce();
        return temp;
    }

    Fraction& operator--()
    {
        numerator_ -= denominator_;
        reduce();
        return *this;
    }

    Fraction operator--(int)
    {
        Fraction temp(*this);
        numerator_ -= denominator_;
        reduce();
        return temp;
    }

    friend std::ostream& operator<<(std::ostream& os, const Fraction& frac)
    {
        os << frac.numerator_ << '/' << frac.denominator_;
        return os;
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
    int num1, denom1, num2, denom2;

    std::cout << "Ââåäèòå ÷èñëèòåëü äðîáè 1: ";
    std::cin >> num1;
    std::cout << "Ââåäèòå çíàìåíàòåëü äðîáè 1: ";
    std::cin >> denom1;

    std::cout << "Ââåäèòå ÷èñëèòåëü äðîáè 2: ";
    std::cin >> num2;
    std::cout << "Ââåäèòå çíàìåíàòåëü äðîáè 2: ";
    std::cin >> denom2;

    Fraction f1(num1, denom1);
    Fraction f2(num2, denom2);

    std::cout << f1 << " + " << f2 << " = " << (f1 + f2) << '\n';
    std::cout << f1 << " - " << f2 << " = " << (f1 - f2) << '\n';
    std::cout << f1 << " * " << f2 << " = " << (f1 * f2) << '\n';
    std::cout << f1 << " / " << f2 << " = " << (f1 / f2) << '\n';

    std::cout << "++" << f1 << " * " << f2 << " = " << (++f1 * f2) << '\n';
    std::cout << "Çíà÷åíèå äðîáè 1 = " << f1 << '\n';

    std::cout << f1 << "-- * " << f2 << " = " << (f1-- * f2) << '\n';
    std::cout << "Çíà÷åíèå äðîáè 1 = " << f1 << '\n';

    std::cout << "--" << f1 << " * " << f2 << " = " << (--f1 * f2) << '\n';
    std::cout << "Çíà÷åíèå äðîáè 1 = " << f1 << '\n';

    std::cout << f1 << "++ * " << f2 << " = " << (f1++ * f2) << '\n';
    std::cout << "Çíà÷åíèå äðîáè 1 = " << f1 << '\n';

    return 0;
}
