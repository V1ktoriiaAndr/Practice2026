#pragma once

#using <System.dll>
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>
#include "DbManager.h"

namespace Project {
    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class EditForm : public Form {
    private:
        int recordId;
        TextBox^ txtName, ^ txtCpu, ^ txtClock, ^ txtRam, ^ txtHdd, ^ txtVideo, ^ txtSound;
        Button^ btnUpdate;
        System::ComponentModel::IContainer^ components;

    public:
        EditForm(int id, String^ n, String^ c, double s, int r, int h, String^ v, String^ sc) {
            InitializeComponent();
            recordId = id;
            txtName->Text = n;
            txtCpu->Text = c;
            txtClock->Text = s.ToString();
            txtRam->Text = r.ToString();
            txtHdd->Text = h.ToString();
            txtVideo->Text = v;
            txtSound->Text = sc;
        }

    private:
        void InitializeComponent(void) {
            this->Size = Drawing::Size(400, 450);
            this->Text = "Edit Record";
            this->StartPosition = FormStartPosition::CenterParent;

            int y = 20;
            txtName = CreateField("Name:", y); y += 45;
            txtCpu = CreateField("CPU:", y); y += 45;
            txtClock = CreateField("GHz:", y); y += 45;
            txtRam = CreateField("RAM:", y); y += 45;
            txtHdd = CreateField("HDD:", y); y += 45;
            txtVideo = CreateField("Video:", y); y += 45;
            txtSound = CreateField("Sound:", y); y += 45;

            btnUpdate = gcnew Button();
            btnUpdate->Text = "Update Data";
            btnUpdate->Location = Point(130, y + 10);
            btnUpdate->Size = Drawing::Size(120, 35);
            btnUpdate->Click += gcnew EventHandler(this, &EditForm::OnUpdate);
            this->Controls->Add(btnUpdate);
        }

        TextBox^ CreateField(String^ label, int y) {
            Label^ l = gcnew Label();
            l->Text = label;
            l->Location = Point(30, y);
            this->Controls->Add(l);

            TextBox^ t = gcnew TextBox();
            t->Location = Point(150, y);
            t->Width = 180;
            this->Controls->Add(t);
            return t;
        }

        void OnUpdate(Object^ sender, EventArgs^ e) {
            try {
                DbManager^ db = gcnew DbManager();
                db->Update(recordId, txtName->Text, txtCpu->Text,
                    Convert::ToDouble(txtClock->Text),
                    Convert::ToInt32(txtRam->Text),
                    Convert::ToInt32(txtHdd->Text),
                    txtVideo->Text, txtSound->Text);
                this->DialogResult = System::Windows::Forms::DialogResult::OK;
                this->Close();
            }
            catch (Exception^) { MessageBox::Show("Error in data format"); }
        }
    };
}