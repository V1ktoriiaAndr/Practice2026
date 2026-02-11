#pragma once
#include "DbManager.h"

namespace Project {
    using namespace System;
    using namespace System::Windows::Forms;

    public ref class LoginForm : public Form {
    public:
        LoginForm(void) { InitializeComponent(); }
    private:
        Button^ btnLogin;
        TextBox^ txtUser;
        TextBox^ txtPass;

        void InitializeComponent(void) {
            this->txtUser = gcnew TextBox();
            this->txtPass = gcnew TextBox();
            this->btnLogin = gcnew Button();

            this->txtUser->Location = System::Drawing::Point(50, 50);
            this->txtPass->Location = System::Drawing::Point(50, 80);
            this->txtPass->PasswordChar = '*';
            this->btnLogin->Location = System::Drawing::Point(50, 120);
            this->btnLogin->Text = "Login";
            this->btnLogin->Click += gcnew EventHandler(this, &LoginForm::OnLogin);

            this->Controls->Add(txtUser);
            this->Controls->Add(txtPass);
            this->Controls->Add(btnLogin);
            this->Size = System::Drawing::Size(300, 250);
        }

        void OnLogin(Object^ sender, EventArgs^ e) {
            DbManager^ db = gcnew DbManager();
            if (db->Login(txtUser->Text, txtPass->Text)) {
                this->DialogResult = System::Windows::Forms::DialogResult::OK;
            }
            else {
                MessageBox::Show("Access Denied");
            }
        }
    };
}