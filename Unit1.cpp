#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include <memory>
#include <string>
#include <stdexcept>
#include <cctype>
#include <System.SysUtils.hpp>

#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;

// ================= Утиліти локалі =================
static double ParseFloatAny(const UnicodeString& s)
{
    try {
        return StrToFloat(s); // системна локаль (кома/крапка як у Windows)
    } catch (...) {
        TFormatSettings fs = TFormatSettings::Create();
        fs.DecimalSeparator = '.';
        TReplaceFlags fl; fl << rfReplaceAll;
        UnicodeString norm = StringReplace(s, L",", L".", fl);
        return StrToFloat(norm, fs);
    }
}

static std::string NormalizeExpr(const UnicodeString& expr)
{
    TReplaceFlags fl; fl << rfReplaceAll;
    UnicodeString norm = StringReplace(expr, L",", L".", fl);
    return std::string(AnsiString(norm).c_str());
}

// ================= Класи вузлів дерева =================
struct Telement {
protected:
    Telement *left, *right;
    Telement(Telement* l, Telement* r) : left(l), right(r) {}
public:
    virtual ~Telement() { delete left; delete right; }
    virtual double rezult() const = 0;
};

struct Number : Telement {
    double f;
    explicit Number(double F) : Telement(nullptr,nullptr), f(F) {}
    double rezult() const override { return f; }
};

struct Plus : Telement {
    Plus(Telement* l, Telement* r) : Telement(l,r) {}
    double rezult() const override { return left->rezult() + right->rezult(); }
};

struct Mult : Telement {
    Mult(Telement* l, Telement* r) : Telement(l,r) {}
    double rezult() const override { return left->rezult() * right->rezult(); }
};

// ================= Рекурсивний парсер =================
struct Parser {
    const std::string s;
    size_t i = 0;
    double xval;

    Parser(std::string src, double x) : s(std::move(src)), xval(x) {}

    void skip() { while (i < s.size() && std::isspace(static_cast<unsigned char>(s[i]))) ++i; }

    bool eat(char c) {
        skip();
        if (i < s.size() && s[i] == c) { ++i; return true; }
        return false;
    }

    std::unique_ptr<Telement> parse() {
        auto node = parseExpr();
        skip();
        if (i != s.size()) throw std::runtime_error("Непередбачені символи у кінці виразу");
        return node;
    }

    std::unique_ptr<Telement> parseExpr() {
        auto node = parseTerm();
        while (true) {
            if (eat('+')) {
                auto rhs = parseTerm();
                node = std::make_unique<Plus>(node.release(), rhs.release());
            } else break;
        }
        return node;
    }

    std::unique_ptr<Telement> parseTerm() {
        auto node = parseFactor();
        while (true) {
            if (eat('*')) {
                auto rhs = parseFactor();
                node = std::make_unique<Mult>(node.release(), rhs.release());
            } else break;
        }
        return node;
    }

    std::unique_ptr<Telement> parseFactor() {
        skip();
        if (eat('(')) {
            auto node = parseExpr();
            if (!eat(')')) throw std::runtime_error("Відсутня дужка ')'");
            return node;
        }
        if (i < s.size() && (std::isdigit(static_cast<unsigned char>(s[i])) || s[i] == '.')) {
            size_t j = i; bool dot = false;
            while (j < s.size() &&
                   (std::isdigit(static_cast<unsigned char>(s[j])) || (!dot && s[j] == '.'))) {
                if (s[j] == '.') dot = true;
                ++j;
            }
            double val = std::stod(s.substr(i, j - i));
            i = j;
            return std::make_unique<Number>(val);
        }
        if (i < s.size() && (s[i] == 'x' || s[i] == 'X')) {
            ++i;
            return std::make_unique<Number>(xval);
        }
        throw std::runtime_error("Помилка: очікувалось число, x або '('");
    }
}; // ВАЖЛИВО: крапка з комою після struct Parser

// ================= Реалізація форми =================
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
    // Програмно ставимо всі підписи (щоб не залежати від кодування .dfm)
    Caption = L"Обчислення виразу";
    Label1->Caption = L"Вираз 1";
    Label2->Caption = L"Вираз 2 (f(x))";
    Label3->Caption = L"x =";
    Label4->Caption = L"Результат 1";
    Label5->Caption = L"Результат 2";
    Label6->Caption = L"Точність (знаків після коми)";
    Button1->Caption = L"Обчислити";
    Button2->Caption = L"Вихід";

    if (Edit1->Text.IsEmpty()) Edit1->Text = L"x*2 + 3*(x+4)";
    if (Edit3->Text.IsEmpty()) Edit3->Text = L"1,0";

    if (ComboBox1->Items->Count == 0) {
        for (int i = 0; i <= 6; ++i) ComboBox1->Items->Add(IntToStr(i));
    }
    if (ComboBox1->Text.IsEmpty()) ComboBox1->Text = L"2";
}

UnicodeString TForm1::EvalExpr(const UnicodeString& expr, double x, int dec)
{
    std::string src = NormalizeExpr(expr);
    Parser p(src, x);
    auto root = p.parse();
    const double val = root->rezult();
    return FloatToStrF(val, ffFixed, 25, dec);
}

void __fastcall TForm1::Button1Click(TObject *Sender)
{
    try {
        const int dec = StrToIntDef(ComboBox1->Text, 2);
        const double x = ParseFloatAny(Edit3->Text);
        Edit4->Text = Edit1->Text.IsEmpty() ? L"" : EvalExpr(Edit1->Text, x, dec);
        Edit5->Text = Edit2->Text.IsEmpty() ? L"" : EvalExpr(Edit2->Text, x, dec);
    }
    catch (const std::exception& e) {
        ShowMessage(UnicodeString(L"Помилка розбору/обчислення: ") + e.what());
    }
    catch (const Exception& e) {
        ShowMessage(L"Помилка: " + e.Message);
    }
}

void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
    Button1Click(Button1);
}

void __fastcall TForm1::Button2Click(TObject *Sender)
{
    Close();
}
