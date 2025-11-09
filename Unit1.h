#ifndef Unit1H
#define Unit1H

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

class TForm1 : public TForm
{
__published:
    TLabel *Label1;  // Вираз 1
    TLabel *Label2;  // Вираз 2 (f(x))
    TLabel *Label3;  // x =
    TLabel *Label4;  // Результат 1
    TLabel *Label5;  // Результат 2
    TLabel *Label6;  // Точність (знаків після коми)

    TEdit *Edit1;    // вираз 1
    TEdit *Edit2;    // вираз 2
    TEdit *Edit3;    // x
    TEdit *Edit4;    // результат 1
    TEdit *Edit5;    // результат 2

    TComboBox *ComboBox1; // точність
    TButton *Button1;     // Обчислити
    TButton *Button2;     // Вихід

    void __fastcall Button1Click(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall ComboBox1Change(TObject *Sender);

private:
    UnicodeString EvalExpr(const UnicodeString& expr, double x, int dec);

public:
    __fastcall TForm1(TComponent* Owner);
};

extern PACKAGE TForm1 *Form1;

#endif
