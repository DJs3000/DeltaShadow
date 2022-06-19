#pragma once

#include "Program2.h"
#include <string>
#include <vector>
#include <memory>

using namespace SdlDotNet::Input;

namespace DeltaShadow
{
	class SetupForm : public System::Windows::Forms::Form
	{
	private:
		bool now_redefine = false;
		std::shared_ptr<Button> current_redefine;

	public:
		SetupForm();

	private:
		std::int32_t TimerCntr = 0;
		void Timer_Tick(const std::shared_ptr<void> &sender, const std::shared_ptr<EventArgs> &e);

		void OKButton_Click(const std::shared_ptr<void> &sender, const std::shared_ptr<EventArgs> &e);

		void AntialiasChecked_CheckedChanged(const std::shared_ptr<void> &sender, const std::shared_ptr<EventArgs> &e);

		void FullScreenChecked_CheckedChanged(const std::shared_ptr<void> &sender, const std::shared_ptr<EventArgs> &e);

		void SetupForm_KeyDown(const std::shared_ptr<void> &sender, const std::shared_ptr<KeyEventArgs> &e);

		void RedefineButton(const std::shared_ptr<void> &sender, const std::shared_ptr<EventArgs> &e);

		void ShowKempstonSettings();

		bool all_redefine = false;
		std::int32_t auto_num = 0;

		void RedefineAll_Click(const std::shared_ptr<void> &sender, const std::shared_ptr<EventArgs> &e);

		void Timer3_Tick(const std::shared_ptr<void> &sender, const std::shared_ptr<EventArgs> &e);

		//если нет такой-же кнопки, то возвращает -1
		std::int32_t FindSameButton(const std::shared_ptr<joy_button> &b, bool in_all);

		bool CompareButtons(const std::shared_ptr<joy_button> &i, const std::shared_ptr<joy_button> &j);

		void SetupForm_FormClosed(const std::shared_ptr<void> &sender, const std::shared_ptr<FormClosedEventArgs> &e);


		/// <summary>
		/// Required designer variable.
		/// </summary>
		std::shared_ptr<System::ComponentModel::IContainer> components = nullptr;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
	protected:
		void Dispose(bool disposing) override;

//		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
	private:
		void InitializeComponent();

//		#endregion
		std::shared_ptr<System::Windows::Forms::BindingSource> setupFormBindingSource;
		std::shared_ptr<System::Windows::Forms::Timer> Timer;
		std::shared_ptr<System::Windows::Forms::GroupBox> JoyButtons;
		std::shared_ptr<System::Windows::Forms::Button> Button7;
		std::shared_ptr<System::Windows::Forms::Label> Label7;
		std::shared_ptr<System::Windows::Forms::Button> Button6;
		std::shared_ptr<System::Windows::Forms::Label> Label6;
		std::shared_ptr<System::Windows::Forms::Button> Button5;
		std::shared_ptr<System::Windows::Forms::Label> Label5;
		std::shared_ptr<System::Windows::Forms::Button> Button4;
		std::shared_ptr<System::Windows::Forms::Label> Label4;
		std::shared_ptr<System::Windows::Forms::Button> Button3;
		std::shared_ptr<System::Windows::Forms::Label> Label3;
		std::shared_ptr<System::Windows::Forms::Button> Button2;
		std::shared_ptr<System::Windows::Forms::Label> Label2;
		std::shared_ptr<System::Windows::Forms::Button> Button1;
		std::shared_ptr<System::Windows::Forms::Label> Label1;
		std::shared_ptr<System::Windows::Forms::Button> Button0;
		std::shared_ptr<System::Windows::Forms::Label> Label0;
		std::shared_ptr<System::Windows::Forms::GroupBox> groupBox1;
		std::shared_ptr<System::Windows::Forms::Button> OKButton;
		std::shared_ptr<System::Windows::Forms::Button> RedefineAll;
		std::shared_ptr<System::Windows::Forms::Timer> Timer3;
		std::shared_ptr<System::Windows::Forms::CheckBox> FullScreenChecked;

protected:
		std::shared_ptr<SetupForm> shared_from_this()
		{
			return std::static_pointer_cast<SetupForm>(System::Windows::Forms::Form::shared_from_this());
		}
	};
}
