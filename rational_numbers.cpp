#include <iostream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;

class Rational {
public:
    Rational() = default;

    Rational(int inNum):numerator_(inNum),denominator_(1){
    }

    Rational(int in_numerator, int in_denomenator):numerator_(in_numerator),denominator_(in_denomenator){
        Normalize();
    }
    
    int Numerator() const {
        return numerator_;
    }

    int Denominator() const {
        return denominator_;
    }

    Rational& operator+=(Rational right) {
        // Результат операции сохраняется в текущем экземпляре класса
        numerator_ = numerator_* right.Denominator() + right.Numerator() * denominator_;
        denominator_ = denominator_* right.Denominator();
        Normalize();
        // return *this позволяет вернуть ссылку на текущий объект
        return *this;
    }

    Rational& operator-=(Rational right) {
        // Результат операции сохраняется в текущем экземпляре класса
        numerator_ = numerator_* right.Denominator() - right.Numerator() * denominator_;
        denominator_ = denominator_* right.Denominator();
        Normalize();
        // return *this позволяет вернуть ссылку на текущий объект
        return *this;
    }
    
    Rational& operator*=(Rational right) {
        // Результат операции сохраняется в текущем экземпляре класса
        numerator_ = numerator_*right.Numerator();
        denominator_ = denominator_* right.Denominator();
        Normalize();
        // return *this позволяет вернуть ссылку на текущий объект
        return *this;
    }
    
    Rational& operator/=(Rational right) {
        // Результат операции сохраняется в текущем экземпляре класса
        numerator_ = numerator_*right.Denominator();
        denominator_ = denominator_* right.Numerator();
        Normalize();
        // return *this позволяет вернуть ссылку на текущий объект
        return *this;
    }

private:
    int numerator_ = 0;
    int denominator_ = 1;
    int gcd(int a, int b){       
        int c;
        while (b) {
            c = a % b;
            a = b;
            b = c;        
        }
    return abs(a);
    }

    void Normalize(){
        int gcd_num_denum = gcd(numerator_, denominator_);
        numerator_ = numerator_/gcd_num_denum;
        denominator_ = denominator_/gcd_num_denum;
        if(denominator_ < 0){
            denominator_ = -1*denominator_;
            numerator_ = -1*numerator_; 
        }
    }
};

// вывод
ostream& operator<<(ostream& output, Rational fraction) {
    output << fraction.Numerator() << "/"s << fraction.Denominator();
    return output;
}

// ввод
istream& operator>>(istream& input, Rational& fraction) {
    int num, denom;
    char slash; // переменная для считывания запятой
    input >> num >> slash >> denom;
    fraction = Rational{num, denom};
    return input;
} 
//+ binary operation
Rational operator+(Rational left, Rational right) {
    return left += right;
}
//- binary operation
Rational operator-(Rational left, Rational right) {
    return left -= right;
}

//* binary operation
Rational operator*(Rational left, Rational right) {
    return left *= right;
}

// / binary operation
Rational operator/(Rational left, Rational right) {
    return left /= right;
}

//+ unary operation
Rational operator+(Rational in_operand) {
    return in_operand;
}

//- unary operation
Rational operator-(Rational in_operand) {
    return {-in_operand.Numerator(),in_operand.Denominator()};
}
// == operation
bool operator==(Rational left, Rational right) {
    return left.Numerator() == right.Numerator() && 
           left.Denominator() == right.Denominator();
} 
// != operation
bool operator!=(Rational left, Rational right) {
    return !(left == right);
} 
// < operation
bool operator<(Rational left, Rational right) {
    if(left.Denominator() == right.Denominator()){
        return (left.Numerator() < right.Numerator());
    }else{
        return (left.Numerator()*right.Denominator() < right.Numerator()*left.Denominator());
    }
} 
// > operation
bool operator>(Rational left, Rational right) {
    if(left.Denominator() == right.Denominator()){
        return (left.Numerator() > right.Numerator());
    }else{
        return (left.Numerator()*right.Denominator() > right.Numerator()*left.Denominator());
    }
} 
// <= operation
bool operator<=(Rational left, Rational right) {
    if(left.Denominator() == right.Denominator()){
        return (left.Numerator() <= right.Numerator());
    }else{
        return (left.Numerator()*right.Denominator() <= right.Numerator()*left.Denominator());
    }
} 
// >= operation
bool operator>=(Rational left, Rational right) {
    if(left.Denominator() == right.Denominator()){
        return (left.Numerator() >= right.Numerator());
    }else{
        return (left.Numerator()*right.Denominator() >= right.Numerator()*left.Denominator());
    }
} 

void AssertImpl(bool value, const string& expr_str, const string& file, const string& func, unsigned line,
                const string& hint) {
    if (!value) {
        cerr << file << "("s << line << "): "s << func << ": "s;
        cerr << "Assert("s << expr_str << ") failed."s;
        if (!hint.empty()) {
            cerr << " Hint: "s << hint;
        }
        cerr << endl;
        abort();
    }
} 

#define ASSERT_HINT(expr, hint) AssertImpl((expr), #expr, __FILE__, __FUNCTION__, __LINE__, (hint))

template <typename T, typename U>
void AssertEqualImpl(const T& t, const U& u, const string& t_str, const string& u_str, const string& file,
                     const string& func, unsigned line, const string& hint) {
    if (t != u) {
        cerr << boolalpha;
        cerr << file << "("s << line << "): "s << func << ": "s;
        cerr << "ASSERT_EQUAL("s << t_str << ", "s << u_str << ") failed: "s;
        cerr << t << " != "s << u << "."s;
        if (!hint.empty()) {
            cerr << " Hint: "s << hint;
        }
        cerr << endl;
        abort();
    }
} 

#define ASSERT_EQUAL(a, b) AssertEqualImpl((a), (b), #a, #b, __FILE__, __FUNCTION__, __LINE__, ""s)
#define ASSERT_EQUAL_HINT(a, b, hint) AssertEqualImpl((a), (b), #a, #b, __FILE__, __FUNCTION__, __LINE__, (hint))

template <typename TestFunc>
void RunTestImpl(const TestFunc& func, const string& test_name) {
    func();
    cerr << test_name << " OK"s << endl;
}

#define RUN_TEST(func) RunTestImpl(func, #func) 

void TestMyInput() {
    istringstream input;
    input.str("1/3"s);

    Rational fract;
    input >> fract;
    ASSERT_EQUAL(fract.Numerator(), 1);
    ASSERT_EQUAL(fract.Denominator(), 3);
    
    input.clear();
    input.str("4/8"s);
    input >> fract;
    ASSERT_EQUAL_HINT(fract.Numerator(), 1,"error in fraction reduction");
    ASSERT_EQUAL_HINT(fract.Denominator(), 2,"error in fraction reduction");

    input.clear();
    input.str("4/-8"s);
    input >> fract;
    ASSERT_EQUAL_HINT(fract.Numerator(), -1,"error with sign processing");
    ASSERT_EQUAL_HINT(fract.Denominator(), 2,"error with sign processing");

    input.clear();
    input.str("18/9"s);
    input >> fract;
    ASSERT_EQUAL_HINT(fract.Numerator(), 2,"error when numerator is greater then denominator");
    ASSERT_EQUAL_HINT(fract.Denominator(), 1,"error when numerator is greater then denominator");
}

void TestMyOutput() {
    Rational fract = Rational{1,3};
    ostringstream output;
    output << fract;
    ASSERT_EQUAL_HINT(output.str(), "1/3","problem with output");

    output.str("");
    output.clear();
    output.str().clear();
    fract = Rational{45,15};
    output << fract;
    ASSERT_EQUAL_HINT(output.str(), "3/1","problem with output");

    output.str("");
    output.clear();
    output.str().clear();
    fract = Rational{4,-8};
    output << fract;
    ASSERT_EQUAL_HINT(output.str(), "-1/2","problem with output");

}

void TestAdition(){
    Rational fract = Rational{1,3} + Rational{2,3};
    ASSERT_EQUAL(fract.Numerator(), 1);
    ASSERT_EQUAL(fract.Denominator(), 1);

    fract = Rational{1,5} + Rational{2,3};
    ASSERT_EQUAL(fract.Numerator(), 13);
    ASSERT_EQUAL(fract.Denominator(), 15);
    
    fract = Rational{-1,4} + Rational{2,3};
    ASSERT_EQUAL(fract.Numerator(), 5);
    ASSERT_EQUAL(fract.Denominator(), 12);

    fract = Rational{-3,4} + Rational{2,3};
    ASSERT_EQUAL(fract.Numerator(), -1);
    ASSERT_EQUAL(fract.Denominator(), 12);

    fract = Rational{1,4} + Rational{-2,3};
    ASSERT_EQUAL(fract.Numerator(), -5);
    ASSERT_EQUAL(fract.Denominator(), 12);

    fract = Rational{1,4} + Rational{-1,4};
    ASSERT_EQUAL(fract.Numerator(), 0);
    ASSERT_EQUAL(fract.Denominator(), 1);


    fract = Rational{156,396} + Rational{-339,1289};
    ASSERT_EQUAL(fract.Numerator(), 5570);
    ASSERT_EQUAL(fract.Denominator(), 42537);

}

void TestSubtraction(){
    Rational fract = Rational{1,3} - Rational{2,3};
    ASSERT_EQUAL(fract.Numerator(), -1);
    ASSERT_EQUAL(fract.Denominator(), 3);

    fract = Rational{1,5} - Rational{2,3};
    ASSERT_EQUAL(fract.Numerator(), -7);
    ASSERT_EQUAL(fract.Denominator(), 15);
    
    fract = Rational{-1,4} - Rational{2,3};
    ASSERT_EQUAL(fract.Numerator(), -11);
    ASSERT_EQUAL(fract.Denominator(), 12);

    fract = Rational{-3,4} - Rational{2,3};
    ASSERT_EQUAL(fract.Numerator(), -17);
    ASSERT_EQUAL(fract.Denominator(), 12);

    fract = Rational{1,4} - Rational{-2,3};
    ASSERT_EQUAL(fract.Numerator(), 11);
    ASSERT_EQUAL(fract.Denominator(), 12);

    fract = Rational{1,4} - Rational{1,4};
    ASSERT_EQUAL(fract.Numerator(), 0);
    ASSERT_EQUAL(fract.Denominator(), 1);


    fract = Rational{156,396} - Rational{339,1289};
    ASSERT_EQUAL(fract.Numerator(), 5570);
    ASSERT_EQUAL(fract.Denominator(), 42537);

}

void TestUnaryPlus(){
    Rational fract = +Rational{1,3};
    ASSERT_EQUAL(fract.Numerator(), 1);
    ASSERT_EQUAL(fract.Denominator(), 3);
}

void TestUnaryMinus(){
    Rational fract = -Rational{1,3};
    ASSERT_EQUAL(fract.Numerator(), -1);
    ASSERT_EQUAL(fract.Denominator(), 3);
}

void TestAdditionAssignment(){
    Rational fract = Rational{1,3};
    fract += Rational{2,3};
    ASSERT_EQUAL(fract.Numerator(), 1);
    ASSERT_EQUAL(fract.Denominator(), 1);

    fract = Rational{1,5};
    fract += Rational{2,3};
    ASSERT_EQUAL(fract.Numerator(), 13);
    ASSERT_EQUAL(fract.Denominator(), 15);
    
    fract = Rational{-1,4};
    fract += Rational{2,3};
    ASSERT_EQUAL(fract.Numerator(), 5);
    ASSERT_EQUAL(fract.Denominator(), 12);

    fract = Rational{-3,4};
    fract += Rational{2,3};
    ASSERT_EQUAL(fract.Numerator(), -1);
    ASSERT_EQUAL(fract.Denominator(), 12);

    fract = Rational{1,4};
    fract += Rational{-2,3};
    ASSERT_EQUAL(fract.Numerator(), -5);
    ASSERT_EQUAL(fract.Denominator(), 12);

    fract = Rational{1,4};
    fract += Rational{-1,4};
    ASSERT_EQUAL(fract.Numerator(), 0);
    ASSERT_EQUAL(fract.Denominator(), 1);


    fract = Rational{156,396};
    fract += Rational{-339,1289};
    ASSERT_EQUAL(fract.Numerator(), 5570);
    ASSERT_EQUAL(fract.Denominator(), 42537);
}

void TestSubtractionAssignment(){
    Rational fract = Rational{1,3};
    fract -= Rational{2,3};
    ASSERT_EQUAL(fract.Numerator(), -1);
    ASSERT_EQUAL(fract.Denominator(), 3);

    fract = Rational{1,5};
    fract -= Rational{2,3};
    ASSERT_EQUAL(fract.Numerator(), -7);
    ASSERT_EQUAL(fract.Denominator(), 15);
    
    fract = Rational{-1,4};
    fract -= Rational{2,3};
    ASSERT_EQUAL(fract.Numerator(), -11);
    ASSERT_EQUAL(fract.Denominator(), 12);

    fract = Rational{-3,4};
    fract -= Rational{2,3};
    ASSERT_EQUAL(fract.Numerator(), -17);
    ASSERT_EQUAL(fract.Denominator(), 12);

    fract = Rational{1,4};
    fract -= Rational{-2,3};
    ASSERT_EQUAL(fract.Numerator(), 11);
    ASSERT_EQUAL(fract.Denominator(), 12);

    fract = Rational{1,4};
    fract -= Rational{1,4};
    ASSERT_EQUAL(fract.Numerator(), 0);
    ASSERT_EQUAL(fract.Denominator(), 1);


    fract = Rational{156,396};
    fract -= Rational{339,1289};
    ASSERT_EQUAL(fract.Numerator(), 5570);
    ASSERT_EQUAL(fract.Denominator(), 42537);
}

void TestMultiplicationAssignment(){
    Rational fract = Rational{1,3};
    fract *= Rational{2,3};
    ASSERT_EQUAL(fract.Numerator(), 2);
    ASSERT_EQUAL(fract.Denominator(), 9);

    fract = Rational{0,5};
    fract *= Rational{2,3};
    ASSERT_EQUAL(fract.Numerator(), 0);
    ASSERT_EQUAL(fract.Denominator(), 1);

    fract = Rational{-5,4};
    fract *= Rational{2,3};
    ASSERT_EQUAL(fract.Numerator(), -5);
    ASSERT_EQUAL(fract.Denominator(), 6);
    
    fract = Rational{-156,396};
    fract *= Rational{339,1289};
    ASSERT_EQUAL(fract.Numerator(), -1469);
    ASSERT_EQUAL(fract.Denominator(), 14179);

}

void TestDevisionAssignment(){
    Rational fract = Rational{1,3};
    fract /= Rational{2,3};
    ASSERT_EQUAL(fract.Numerator(), 1);
    ASSERT_EQUAL(fract.Denominator(), 2);

    fract = Rational{0,5};
    fract /= Rational{2,3};
    ASSERT_EQUAL(fract.Numerator(), 0);
    ASSERT_EQUAL(fract.Denominator(), 1);

    fract = Rational{-5,4};
    fract /= Rational{2,3};
    ASSERT_EQUAL(fract.Numerator(), -15);
    ASSERT_EQUAL(fract.Denominator(), 8);
    
}

void TestEqual(){
    Rational fract = Rational{1,3};
    ASSERT_EQUAL((fract == Rational{1,3}),true);

    ASSERT_EQUAL((fract == Rational{2,3}),false);
}

void TestNotEqual(){
    Rational fract = Rational{1,3};
    ASSERT_EQUAL((fract != Rational{1,3}),false);

    ASSERT_EQUAL((fract != Rational{2,3}),true);
}

void TestGreater(){
    Rational fract = Rational{2,3};
    ASSERT_EQUAL((fract > Rational{1,3}),true);

    ASSERT_EQUAL((fract > Rational{2,3}),false);

    ASSERT_EQUAL((fract > Rational{1,4}),true);

    ASSERT_EQUAL((fract > Rational{3,4}),false);

    ASSERT_EQUAL((fract > 0),true);
}

void TestLess(){
    Rational fract = Rational{2,3};
    ASSERT_EQUAL((fract < Rational{1,3}),false);

    ASSERT_EQUAL((fract < Rational{2,3}),false);

    ASSERT_EQUAL((fract < Rational{1,4}),false);

    ASSERT_EQUAL((fract < Rational{3,4}),true);

    ASSERT_EQUAL((fract < 0),false);
}

void TestGreaterOrEqual(){
    Rational fract = Rational{2,3};
    ASSERT_EQUAL((fract >= Rational{1,3}),true);

    ASSERT_EQUAL((fract >= Rational{2,3}),true);

    ASSERT_EQUAL((fract >= Rational{1,4}),true);

    ASSERT_EQUAL((fract >= Rational{3,4}),false);

    ASSERT_EQUAL((fract >= 0),true);

    ASSERT_EQUAL((fract >= -1),true);
}

void TestLessOrEqual(){
        Rational fract = Rational{2,3};
    ASSERT_EQUAL((fract <= Rational{1,3}),false);

    ASSERT_EQUAL((fract <= Rational{2,3}),true);

    ASSERT_EQUAL((fract <= Rational{1,4}),false);

    ASSERT_EQUAL((fract <= Rational{3,4}),true);

    ASSERT_EQUAL((fract <= 0),false);
    ASSERT_EQUAL((fract <= -1),false);
}

void TestRational() {
    RUN_TEST(TestMyInput);    
    RUN_TEST(TestMyOutput);
    RUN_TEST(TestAdition);
    RUN_TEST(TestUnaryPlus);
    RUN_TEST(TestUnaryMinus);
    RUN_TEST(TestAdditionAssignment);
    RUN_TEST(TestSubtractionAssignment);
    RUN_TEST(TestMultiplicationAssignment);
    RUN_TEST(TestDevisionAssignment);
    RUN_TEST(TestEqual);
    RUN_TEST(TestNotEqual);
    RUN_TEST(TestGreater);
    RUN_TEST(TestLess);
    RUN_TEST(TestGreaterOrEqual);
    RUN_TEST(TestLessOrEqual);
}
int main() {
    TestRational();
    cout << "Rational testing finished"s << endl;
    Rational zero;     // Дробь 0/1 = 0
    const Rational seven(7); // Дробь 7/1 = 7
    const Rational one_third(1, 3); // Дробь 1/3
    vector<Rational> numbers;
    numbers.push_back(Rational{7, 8});
    // Следующие 2 строки эквивалентны - добавляют в numbers дробь 3/1
    numbers.push_back(Rational{3});
    numbers.push_back(3);
    Rational sum = Rational{1,6} + one_third;
    // Выведет 1/2
    cout << sum;
} 