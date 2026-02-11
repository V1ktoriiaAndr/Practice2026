#pragma once

#include <cmath>

namespace Lab5 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1000, 700);
			this->Name = L"MyForm";
			this->Text = L"Lab 5 - Hermite Curve";
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
			this->ResumeLayout(false);
		}
#pragma endregion

		void DrawDandelion(Graphics^ g, Pen^ p, float x, float y, float l, float a, int k)
		{
			if (k < 0) return;

			float xe = x + l * std::cos(a);
			float ye = y - l * std::sin(a);

			g->DrawLine(p, x, y, xe, ye);

			if (k > 0)
			{
				float nl = l * 0.6f;
				DrawDandelion(g, p, xe, ye, nl, a + 0.8f, k - 1);
				DrawDandelion(g, p, xe, ye, nl, a + 0.3f, k - 1);
				DrawDandelion(g, p, xe, ye, nl, a - 0.3f, k - 1);
				DrawDandelion(g, p, xe, ye, nl, a - 0.8f, k - 1);
			}
		}

		System::Void MyForm_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
		{
			Graphics^ g = e->Graphics;
			g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;

			Pen^ ph = gcnew Pen(Color::Orange, 4.0f);

			float x1 = 150.0f, y1 = 550.0f;
			float x2 = 800.0f, y2 = 250.0f;
			float vx1 = 300.0f, vy1 = -700.0f;
			float vx2 = 300.0f, vy2 = -700.0f;

			float ox = x1;
			float oy = y1;

			for (float t = 0.0f; t <= 1.01f; t += 0.005f)
			{
				float t2 = t * t;
				float t3 = t2 * t;

				float h00 = 2 * t3 - 3 * t2 + 1;
				float h01 = -2 * t3 + 3 * t2;
				float h10 = t3 - 2 * t2 + t;
				float h11 = t3 - t2;

				float nx = h00 * x1 + h10 * vx1 + h01 * x2 + h11 * vx2;
				float ny = h00 * y1 + h10 * vy1 + h01 * y2 + h11 * vy2;

				g->DrawLine(ph, ox, oy, nx, ny);
				ox = nx;
				oy = ny;
			}

			Pen^ pf = gcnew Pen(Color::Green, 1.0f);
			DrawDandelion(g, pf, 900.0f, 650.0f, 120.0f, 1.57f, 4);
		}
	};
}