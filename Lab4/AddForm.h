#pragma once

#using <System.dll>
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>

#include "DbManager.h"

namespace Project {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class AddForm : public Form {
    public:
        AddForm(void) {
            InitializeComponent();
        }

    protected:
        ~AddForm() {
            if (components) delete components;
        }

    private:
        Label^ lblName, ^ lblCpu, ^ lblClock, ^ lblRam, ^ lblHdd, ^ lblVideo, ^ lblSound;
        TextBox^ txtName, ^ txtCpu, ^ txtClock, ^ txtRam, ^ txtHdd, ^ txtVideo, ^ txtSound;
        Button^ btnSave;
        System::ComponentModel::IContainer^ components;

        void InitializeComponent(void) {
            this->lblName = gcnew Label();
            this->lblCpu = gcnew Label();
            this->lblClock = gcnew Label();
            this->lblRam = gcnew Label();
            this->lblHdd = gcnew Label();
            this->lblVideo = gcnew Label();
            this->lblSound = gcnew Label();

            this->txtName = gcnew TextBox();
            this->txtCpu = gcnew TextBox();
            this->txtClock = gcnew TextBox();
            this->txtRam = gcnew TextBox();
            this->txtHdd = gcnew TextBox();
            this->txtVideo = gcnew TextBox();
            this->txtSound = gcnew TextBox();

            this->btnSave = gcnew Button();

            this->lblName->Text = "PC Name:";
            this->lblName->Location = Point(20, 20);
            this->txtName->Location = Point(150, 20);
            this->txtName->Size = Drawing::Size(200, 20);

            this->lblCpu->Text = "CPU Type:";
            this->lblCpu->Location = Point(20, 60);
            this->txtCpu->Location = Point(150, 60);
            this->txtCpu->Size = Drawing::Size(200, 20);

            this->lblClock->Text = "Clock Speed (GHz):";
            this->lblClock->Location = Point(20, 100);
            this->txtClock->Location = Point(150, 100);
            this->txtClock->Size = Drawing::Size(200, 20);

            this->lblRam->Text = "RAM Size (GB):";
            this->lblRam->Location = Point(20, 140);
            this->txtRam->Location = Point(150, 140);
            this->txtRam->Size = Drawing::Size(200, 20);

            this->lblHdd->Text = "HDD Size (GB):";
            this->lblHdd->Location = Point(20, 180);
            this->txtHdd->Location = Point(150, 180);
            this->txtHdd->Size = Drawing::Size(200, 20);

            this->lblVideo->Text = "Video Card:";
            this->lblVideo->Location = Point(20, 220);
            this->txtVideo->Location = Point(150, 220);
            this->txtVideo->Size = Drawing::Size(200, 20);

            this->lblSound->Text = "Sound Card:";
            this->lblSound->Location = Point(20, 260);
            this->txtSound->Location = Point(150, 260);
            this->txtSound->Size = Drawing::Size(200, 20);

            this->btnSave->Text = "Save Computer";
            this->btnSave->Location = Point(150, 310);
            this->btnSave->Size = Drawing::Size(120, 40);
            this->btnSave->Click += gcnew EventHandler(this, &AddForm::btnSave_Click);

            this->ClientSize = Drawing::Size(400, 400);
            this->Controls->Add(this->lblName);
            this->Controls->Add(this->txtName);
            this->Controls->Add(this->lblCpu);
            this->Controls->Add(this->txtCpu);
            this->Controls->Add(this->lblClock);
            this->Controls->Add(this->txtClock);
            this->Controls->Add(this->lblRam);
            this->Controls->Add(this->txtRam);
            this->Controls->Add(this->lblHdd);
            this->Controls->Add(this->txtHdd);
            this->Controls->Add(this->lblVideo);
            this->Controls->Add(this->txtVideo);
            this->Controls->Add(this->lblSound);
            this->Controls->Add(this->txtSound);
            this->Controls->Add(this->btnSave);

            this->Text = "Add Computer Entry";
            this->StartPosition = FormStartPosition::CenterParent;
        }

        void btnSave_Click(Object^ sender, EventArgs^ e) {
            try {
                DbManager^ db = gcnew DbManager();
                db->Add(
                    txtName->Text,
                    txtCpu->Text,
                    Convert::ToDouble(txtClock->Text),
                    Convert::ToInt32(txtRam->Text),
                    Convert::ToInt32(txtHdd->Text),
                    txtVideo->Text,
                    txtSound->Text
                );
                this->DialogResult = System::Windows::Forms::DialogResult::OK;
                this->Close();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Format Error: Please check numeric fields.");
            }
        }
    };
}