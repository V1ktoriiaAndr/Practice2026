#pragma once
#include "EditForm.h"
#include "AddForm.h"
#include "DbManager.h"

namespace Project {
    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class MainForm : public Form {
    public:
        MainForm(void) {
            InitializeComponent();
            LoadData();
        }

    private:
        DataGridView^ dgv;
        Button^ btnRefresh;
        Button^ btnOpenAdd;
        Button^ btnSearch;
        TextBox^ txtSearch;
        Button^ btnDelete;
        Button^ btnEdit;

        void InitializeComponent(void) {
            this->dgv = gcnew DataGridView();
            this->btnRefresh = gcnew Button();
            this->btnOpenAdd = gcnew Button();
            this->btnEdit = gcnew Button();
            this->btnDelete = gcnew Button();
            this->btnSearch = gcnew Button();
            this->txtSearch = gcnew TextBox();

            this->btnOpenAdd->Text = "Add New";
            this->btnOpenAdd->Location = Point(10, 10);
            this->btnOpenAdd->Size = Drawing::Size(100, 30);
            this->btnOpenAdd->Click += gcnew EventHandler(this, &MainForm::OnOpenAdd);

            this->btnEdit->Text = "Edit Record";
            this->btnEdit->Location = Point(115, 10);
            this->btnEdit->Size = Drawing::Size(100, 30);
            this->btnEdit->Click += gcnew EventHandler(this, &MainForm::OnEditClick);

            this->btnDelete->Text = "Delete Selected";
            this->btnDelete->Location = Point(220, 10);
            this->btnDelete->Size = Drawing::Size(110, 30);
            this->btnDelete->BackColor = Color::LightCoral;
            this->btnDelete->Click += gcnew EventHandler(this, &MainForm::OnDeleteClick);

            this->txtSearch->Location = Point(350, 13);
            this->txtSearch->Size = Drawing::Size(160, 25);

            this->btnSearch->Text = "Search";
            this->btnSearch->Location = Point(515, 10);
            this->btnSearch->Size = Drawing::Size(80, 30);
            this->btnSearch->Click += gcnew EventHandler(this, &MainForm::OnSearch);

            this->btnRefresh->Text = "Refresh All";
            this->btnRefresh->Location = Point(670, 10);
            this->btnRefresh->Size = Drawing::Size(100, 30);
            this->btnRefresh->Click += gcnew EventHandler(this, &MainForm::OnRefresh);

            this->dgv->Location = Point(10, 60);
            this->dgv->Size = Drawing::Size(760, 380);
            this->dgv->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            this->dgv->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            this->dgv->ReadOnly = true;

            this->Controls->Add(dgv);
            this->Controls->Add(btnRefresh);
            this->Controls->Add(btnOpenAdd);
            this->Controls->Add(btnEdit);
            this->Controls->Add(btnDelete);
            this->Controls->Add(btnSearch);
            this->Controls->Add(txtSearch);

            this->Text = "Computer Sales Inventory";
            this->Size = Drawing::Size(800, 500);
            this->StartPosition = FormStartPosition::CenterScreen;
        }

        void LoadData() {
            DbManager^ db = gcnew DbManager();
            dgv->DataSource = db->GetAll();
        }

        void OnRefresh(Object^ sender, EventArgs^ e) {
            LoadData();
        }

        void OnOpenAdd(Object^ sender, EventArgs^ e) {
            AddForm^ addForm = gcnew AddForm();
            if (addForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                LoadData();
            }
        }

        void OnSearch(Object^ sender, EventArgs^ e) {
            DbManager^ db = gcnew DbManager();
            dgv->DataSource = db->Search(txtSearch->Text);
        }

        void OnDeleteClick(Object^ sender, EventArgs^ e) {
            if (dgv->SelectedRows->Count > 0) {
                System::Windows::Forms::DialogResult result = MessageBox::Show(
                    "Are you sure you want to delete this computer?",
                    "Confirmation",
                    MessageBoxButtons::YesNo,
                    MessageBoxIcon::Warning
                );

                if (result == System::Windows::Forms::DialogResult::Yes) {
                    try {
                        int id = Convert::ToInt32(dgv->SelectedRows[0]->Cells["id"]->Value);
                        DbManager^ db = gcnew DbManager();
                        db->Delete(id);
                        LoadData();
                    }
                    catch (Exception^ ex) {
                        MessageBox::Show("Error: " + ex->Message);
                    }
                }
            }
            else {
                MessageBox::Show("Please select a full row to delete.");
            }
        }

        void OnEditClick(Object^ sender, EventArgs^ e) {
            if (dgv->SelectedRows->Count > 0) {
                int id = Convert::ToInt32(dgv->SelectedRows[0]->Cells["id"]->Value);
                String^ name = dgv->SelectedRows[0]->Cells["pc_name"]->Value->ToString();
                String^ cpu = dgv->SelectedRows[0]->Cells["cpu_type"]->Value->ToString();
                double speed = Convert::ToDouble(dgv->SelectedRows[0]->Cells["clock_speed"]->Value);
                int ram = Convert::ToInt32(dgv->SelectedRows[0]->Cells["ram_size"]->Value);
                int hdd = Convert::ToInt32(dgv->SelectedRows[0]->Cells["hdd_size"]->Value);
                String^ video = dgv->SelectedRows[0]->Cells["video_card"]->Value->ToString();
                String^ sound = dgv->SelectedRows[0]->Cells["sound_card"]->Value->ToString();

                EditForm^ f = gcnew EditForm(id, name, cpu, speed, ram, hdd, video, sound);
                if (f->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                    LoadData();
                }
            }
            else {
                MessageBox::Show("Please select a row");
            }
        }
    };
}