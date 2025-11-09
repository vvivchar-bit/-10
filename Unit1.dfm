object Form1: TForm1
  Left = 0
  Top = 0
  BorderIcons = []
  Caption = 'Form1'
  ClientHeight = 458
  ClientWidth = 560
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poScreenCenter
  TextHeight = 15
  object Label1: TLabel
    Left = 16
    Top = 16
    Width = 34
    Height = 15
    Caption = 'Label1'
  end
  object Label2: TLabel
    Left = 16
    Top = 56
    Width = 34
    Height = 15
    Caption = 'Label2'
  end
  object Label3: TLabel
    Left = 16
    Top = 224
    Width = 14
    Height = 15
    Caption = 'x='
  end
  object Label4: TLabel
    Left = 16
    Top = 93
    Width = 34
    Height = 15
    Caption = 'Label4'
  end
  object Label5: TLabel
    Left = 16
    Top = 136
    Width = 34
    Height = 15
    Caption = 'Label5'
  end
  object Label6: TLabel
    Left = 16
    Top = 173
    Width = 34
    Height = 15
    Caption = 'Label6'
    WordWrap = True
  end
  object Edit1: TEdit
    Left = 96
    Top = 8
    Width = 400
    Height = 23
    TabOrder = 0
  end
  object Edit2: TEdit
    Left = 96
    Top = 53
    Width = 400
    Height = 23
    TabOrder = 1
  end
  object Edit3: TEdit
    Left = 96
    Top = 221
    Width = 97
    Height = 23
    TabOrder = 2
  end
  object ComboBox1: TComboBox
    Left = 96
    Top = 173
    Width = 400
    Height = 23
    TabOrder = 3
    OnChange = ComboBox1Change
  end
  object Edit4: TEdit
    Left = 96
    Top = 90
    Width = 400
    Height = 23
    ReadOnly = True
    TabOrder = 4
  end
  object Edit5: TEdit
    Left = 96
    Top = 136
    Width = 400
    Height = 23
    ReadOnly = True
    TabOrder = 5
  end
  object Button1: TButton
    Left = 8
    Top = 276
    Width = 100
    Height = 30
    Caption = 'Button1'
    TabOrder = 6
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 144
    Top = 276
    Width = 100
    Height = 30
    Caption = 'Button2'
    TabOrder = 7
    OnClick = Button2Click
  end
end
