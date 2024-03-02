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
        int gcd_num_denum = gcd(numerator_, in_denomenator);
        numerator_ = numerator_/gcd_num_denum;
        denominator_ = denominator_/gcd_num_denum;
        if(denominator_ < 0){
            denominator_ = -1*denominator_;
            numerator_ = -1*numerator_; 
        }
    }
    
    int Numerator() const {
        return numerator_;
    }

    int Denominator() const {
        return denominator_;
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
    int numerator = left.Numerator() * right.Denominator() + right.Numerator() * left.Denominator();
    int denominator = left.Denominator() * right.Denominator();
    // Создаём и возвращаем дробь с заданным числителем и знаменателем
    return Rational{numerator, denominator};
}
//- binary operation
Rational operator-(Rational left, Rational right) {
    int numerator = left.Numerator() * right.Denominator() - right.Numerator() * left.Denominator();
    int denominator = left.Denominator() * right.Denominator();
    // Создаём и возвращаем дробь с заданным числителем и знаменателем
    return Rational{numerator, denominator};
}

//+ unary operation
Rational operator+(Rational in_operand) {
    return in_operand;
}

//- unary operation
Rational operator-(Rational in_operand) {
    return {-in_operand.Numerator(),in_operand.Denominator()};
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


void TestRational() {
    RUN_TEST(TestMyInput);    
    RUN_TEST(TestMyOutput);
    RUN_TEST(TestAdition);
    RUN_TEST(TestUnaryPlus);
    RUN_TEST(TestUnaryMinus);
 
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