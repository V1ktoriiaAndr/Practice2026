#include "LoginForm.h"
#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main() {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    Project::LoginForm^ login = gcnew Project::LoginForm();
    if (login->ShowDialog() == DialogResult::OK) {
        Application::Run(gcnew Project::MainForm());
    }
    return 0;
}