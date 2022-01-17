#include "DeltaShadow.SetupForm.h"
#include "DeltaShadow.Program.h"
#include "Properties/Resources.Designer.h"

using namespace SdlDotNet::Input;

namespace DeltaShadow
{

	SetupForm::SetupForm()
	{
		InitializeComponent();
		ShowKempstonSettings();
		FullScreenChecked->Checked = Program::prev_full_screen_mode;
	}

	void SetupForm::Timer_Tick(const std::shared_ptr<void> &sender, const std::shared_ptr<EventArgs> &e)
	{
		if (Program::full_screen_mode)
		{
			this->Close();
		}

		TimerCntr = (TimerCntr + 1) & 0x07;
		Joysticks::Initialize();

		if (Joysticks::NumberOfJoysticks == 0)
		{
			if (JoyButtons->Enabled)
			{
				JoyButtons->Text = L"No joysticks found";
				JoyButtons->Enabled = false;
				all_redefine = false;
				ShowKempstonSettings();
			}
		}
		else
		{
			if (!JoyButtons->Enabled)
			{
				JoyButtons->Text = L"Kempston redefine";
				JoyButtons->Enabled = true;
			}

			if (now_redefine)
			{
				std::wstring s = L"press button";
				if ((TimerCntr & 0x04) == 0)
				{
					s = L"";
				}
				current_redefine->Text = s;

				Joysticks::OpenJoystick(0);
				std::shared_ptr<Joystick> j = std::make_shared<Joystick>(0);
				std::int32_t i = std::stoi(current_redefine->Name[6] + L"");
				if (Program::kempston_ax_h == 0 || Program::kempston_ax_h == 1)
				{
					std::shared_ptr<joy_button> b = std::make_shared<joy_button>();
					b->isAxis = true;
					b->isButton = false;
					b->AxisNum = 0;
					b->AxisDirection = Program::kempston_ax_h;
					if (all_redefine && auto_num != 0 && FindSameButton(b, false) != -1)
					{
						return;
					}
					std::int32_t same = FindSameButton(b, true);
					if (same != -1)
					{
						Program::kempston_buttons[same]->isAxis = false;
						Program::kempston_buttons[same]->isButton = false;
					}
					Program::kempston_buttons[i] = b;
					ShowKempstonSettings();
					Program::SaveSettings();
				}
				if (Program::kempston_ax_v == 0 || Program::kempston_ax_v == 1)
				{
					std::shared_ptr<joy_button> b = std::make_shared<joy_button>();
					b->isAxis = true;
					b->isButton = false;
					b->AxisNum = 1;
					b->AxisDirection = Program::kempston_ax_v;
					if (all_redefine && auto_num != 0 && FindSameButton(b, false) != -1)
					{
						return;
					}
					std::int32_t same = FindSameButton(b, true);
					if (same != -1)
					{
						Program::kempston_buttons[same]->isAxis = false;
						Program::kempston_buttons[same]->isButton = false;
					}
					Program::kempston_buttons[i] = b;
					ShowKempstonSettings();
					Program::SaveSettings();
				}
				for (std::int32_t k = 0; k < j->NumberOfButtons; k++)
				{
					if (Program::kempston_btns[k] == ButtonKeyState::Pressed)
					{
						std::shared_ptr<joy_button> b = std::make_shared<joy_button>();
						b->isAxis = false;
						b->isButton = true;
						b->ButtonNum = k;
						if (all_redefine && auto_num != 0 && FindSameButton(b, false) != -1)
						{
							return;
						}
						std::int32_t same = FindSameButton(b, true);
						if (same != -1)
						{
							Program::kempston_buttons[same]->isAxis = false;
							Program::kempston_buttons[same]->isButton = false;
						}
						Program::kempston_buttons[i] = b;
						ShowKempstonSettings();
						Program::SaveSettings();
						break;
					}
				}
			}
		}
	}

	void SetupForm::OKButton_Click(const std::shared_ptr<void> &sender, const std::shared_ptr<EventArgs> &e)
	{
		this->Close();
	}

	void SetupForm::AntialiasChecked_CheckedChanged(const std::shared_ptr<void> &sender, const std::shared_ptr<EventArgs> &e)
	{
		Program::InitVideo();
		Program::SaveSettings();
	}

	void SetupForm::FullScreenChecked_CheckedChanged(const std::shared_ptr<void> &sender, const std::shared_ptr<EventArgs> &e)
	{
		Program::prev_full_screen_mode = FullScreenChecked->Checked;
	}

	void SetupForm::SetupForm_KeyDown(const std::shared_ptr<void> &sender, const std::shared_ptr<KeyEventArgs> &e)
	{
		if (e->KeyCode == Keys::F1)
		{
			this->Close();
		}
	}

	void SetupForm::RedefineButton(const std::shared_ptr<void> &sender, const std::shared_ptr<EventArgs> &e)
	{
		//this.TopMost = false;
		if (!now_redefine)
		{
			now_redefine = true;
			current_redefine = std::static_pointer_cast<Button>(sender);
			for (std::int32_t i = 0; i < 8; i++)
			{
				(std::static_pointer_cast<Button>(this->getControls()->Find(L"Button" + std::to_wstring(i), true)[0]))->Enabled = false;
				(std::static_pointer_cast<Label>(this->getControls()->Find(L"Label" + std::to_wstring(i), true)[0]))->Enabled = false;
			}
			(std::static_pointer_cast<Button>(sender))->Enabled = true;
			(std::static_pointer_cast<Label>(this->getControls()->Find(L"Label" + (std::static_pointer_cast<Button>(sender))->Name[6], true)[0]))->Enabled = true;
			RedefineAll->Enabled = false;
		}
		else
		{
			all_redefine = false;
			ShowKempstonSettings();
		}
	}

	void SetupForm::ShowKempstonSettings()
	{
		now_redefine = false;
		for (std::int32_t i = 0; i < 8; i++)
		{
			std::shared_ptr<Button> b = std::static_pointer_cast<Button>(this->getControls()->Find(L"Button" + std::to_wstring(i), true)[0]);
			b->Enabled = !all_redefine;
			(std::static_pointer_cast<Label>(this->getControls()->Find(L"Label" + std::to_wstring(i), true)[0]))->Enabled = !all_redefine;
			std::vector<std::shared_ptr<joy_button>> j = Program::kempston_buttons;
			std::wstring s = L"none";
			if (j[i]->isAxis)
			{
				s = L"Axis";
				if (j[i]->AxisNum == 0)
				{
					s += L"X ";
				}
				else
				{
					s += L"Y ";
				}
				if (j[i]->AxisDirection == 0)
				{
					s += L"-";
				}
				else
				{
					s += L"+";
				}
			}
			if (j[i]->isButton)
			{
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
				s = L"Button " + j[i]->ButtonNum.ToString();
			}
			b->Text = s;
		}
		RedefineAll->Enabled = !all_redefine;

		if (all_redefine)
		{
			auto_num++;
			if (auto_num < 8)
			{
				current_redefine = std::static_pointer_cast<Button>(this->getControls()->Find(L"Button" + std::to_wstring(auto_num), true)[0]);
			}
			else
			{
				all_redefine = false;
				ShowKempstonSettings();
			}
		}
	}

	void SetupForm::RedefineAll_Click(const std::shared_ptr<void> &sender, const std::shared_ptr<EventArgs> &e)
	{
		all_redefine = true;
		current_redefine = Button0;
		auto_num = 0;
	}

	void SetupForm::Timer3_Tick(const std::shared_ptr<void> &sender, const std::shared_ptr<EventArgs> &e)
	{
		if (!all_redefine)
		{
			return;
		}

		if (!now_redefine)
		{
			RedefineButton(current_redefine, std::make_shared<EventArgs>());
		}
	}

	std::int32_t SetupForm::FindSameButton(const std::shared_ptr<joy_button> &b, bool in_all)
	{
		std::int32_t n = 8;
		if (!in_all)
		{
			n = auto_num;
		}
		std::vector<std::shared_ptr<joy_button>> j = Program::kempston_buttons;
		for (std::int32_t i = 0; i < n; i++)
		{
			if (CompareButtons(b, j[i]))
			{
				return i;
			}
		}
		return -1;
	}

	bool SetupForm::CompareButtons(const std::shared_ptr<joy_button> &i, const std::shared_ptr<joy_button> &j)
	{
		if (i->isAxis && j->isAxis && i->AxisNum == j->AxisNum && i->AxisDirection == j->AxisDirection)
		{
			return true;
		}
		if (i->isButton && j->isButton && i->ButtonNum == j->ButtonNum)
		{
			return true;
		}

		return false;
	}

	void SetupForm::SetupForm_FormClosed(const std::shared_ptr<void> &sender, const std::shared_ptr<FormClosedEventArgs> &e)
	{
		Program::full_screen_mode = Program::prev_full_screen_mode;
		Program::StartKempston();
		Program::InitVideo();
	}

	void SetupForm::Dispose(bool disposing)
	{
		if (disposing && (components != nullptr))
		{
			components->Dispose();
		}
		System::Windows::Forms::Form::Dispose(disposing);
	}

	void SetupForm::InitializeComponent()
	{
		this->components = std::make_shared<System::ComponentModel::Container>();
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
		std::shared_ptr<System::ComponentModel::ComponentResourceManager> resources = std::make_shared<System::ComponentModel::ComponentResourceManager>(typeof(SetupForm));
		this->Timer = std::make_shared<System::Windows::Forms::Timer>(this->components);
		this->JoyButtons = std::make_shared<System::Windows::Forms::GroupBox>();
		this->RedefineAll = std::make_shared<System::Windows::Forms::Button>();
		this->Button7 = std::make_shared<System::Windows::Forms::Button>();
		this->Label7 = std::make_shared<System::Windows::Forms::Label>();
		this->Button6 = std::make_shared<System::Windows::Forms::Button>();
		this->Label4 = std::make_shared<System::Windows::Forms::Label>();
		this->Label6 = std::make_shared<System::Windows::Forms::Label>();
		this->Button4 = std::make_shared<System::Windows::Forms::Button>();
		this->Button5 = std::make_shared<System::Windows::Forms::Button>();
		this->Label5 = std::make_shared<System::Windows::Forms::Label>();
		this->Button3 = std::make_shared<System::Windows::Forms::Button>();
		this->Label3 = std::make_shared<System::Windows::Forms::Label>();
		this->Button2 = std::make_shared<System::Windows::Forms::Button>();
		this->Label2 = std::make_shared<System::Windows::Forms::Label>();
		this->Button1 = std::make_shared<System::Windows::Forms::Button>();
		this->Label1 = std::make_shared<System::Windows::Forms::Label>();
		this->Button0 = std::make_shared<System::Windows::Forms::Button>();
		this->Label0 = std::make_shared<System::Windows::Forms::Label>();
		this->groupBox1 = std::make_shared<System::Windows::Forms::GroupBox>();
		this->FullScreenChecked = std::make_shared<System::Windows::Forms::CheckBox>();
		this->OKButton = std::make_shared<System::Windows::Forms::Button>();
		this->Timer3 = std::make_shared<System::Windows::Forms::Timer>(this->components);
		this->setupFormBindingSource = std::make_shared<System::Windows::Forms::BindingSource>(this->components);
		this->JoyButtons->SuspendLayout();
		this->groupBox1->SuspendLayout();
		(std::static_pointer_cast<System::ComponentModel::ISupportInitialize>(this->setupFormBindingSource))->BeginInit();
		this->SuspendLayout();
		// 
		// Timer
		// 
		this->Timer->Enabled = true;
		this->Timer->Tick += std::make_shared<System::EventHandler>(this->Timer_Tick);
		// 
		// JoyButtons
		// 
		this->JoyButtons->BackColor = System::Drawing::Color::Transparent;
		this->JoyButtons->Controls->Add(this->RedefineAll);
		this->JoyButtons->Controls->Add(this->Button7);
		this->JoyButtons->Controls->Add(this->Label7);
		this->JoyButtons->Controls->Add(this->Button6);
		this->JoyButtons->Controls->Add(this->Label4);
		this->JoyButtons->Controls->Add(this->Label6);
		this->JoyButtons->Controls->Add(this->Button4);
		this->JoyButtons->Controls->Add(this->Button5);
		this->JoyButtons->Controls->Add(this->Label5);
		this->JoyButtons->Controls->Add(this->Button3);
		this->JoyButtons->Controls->Add(this->Label3);
		this->JoyButtons->Controls->Add(this->Button2);
		this->JoyButtons->Controls->Add(this->Label2);
		this->JoyButtons->Controls->Add(this->Button1);
		this->JoyButtons->Controls->Add(this->Label1);
		this->JoyButtons->Controls->Add(this->Button0);
		this->JoyButtons->Controls->Add(this->Label0);
		this->JoyButtons->ForeColor = System::Drawing::SystemColors::ControlText;
		this->JoyButtons->Location = System::Drawing::Point(13, 99);
		this->JoyButtons->Name = L"JoyButtons";
		this->JoyButtons->Size = System::Drawing::Size(309, 195);
		this->JoyButtons->TabIndex = 4;
		this->JoyButtons->TabStop = false;
		this->JoyButtons->Text = L"Kempston redefine";
		// 
		// RedefineAll
		// 
		this->RedefineAll->FlatStyle = System::Windows::Forms::FlatStyle::System;
		this->RedefineAll->Location = System::Drawing::Point(107, 19);
		this->RedefineAll->Name = L"RedefineAll";
		this->RedefineAll->Size = System::Drawing::Size(87, 23);
		this->RedefineAll->TabIndex = 0;
		this->RedefineAll->Text = L"Redefine all";
		this->RedefineAll->UseVisualStyleBackColor = true;
		this->RedefineAll->Click += std::make_shared<System::EventHandler>(this->RedefineAll_Click);
		// 
		// Button7
		// 
		this->Button7->FlatStyle = System::Windows::Forms::FlatStyle::System;
		this->Button7->Location = System::Drawing::Point(210, 155);
		this->Button7->Name = L"Button7";
		this->Button7->Size = System::Drawing::Size(87, 23);
		this->Button7->TabIndex = 34;
		this->Button7->Text = L"none";
		this->Button7->UseVisualStyleBackColor = true;
		this->Button7->Click += std::make_shared<System::EventHandler>(this->RedefineButton);
		// 
		// Label7
		// 
		this->Label7->AutoSize = true;
		this->Label7->BackColor = System::Drawing::Color::Transparent;
		this->Label7->Font = std::make_shared<System::Drawing::Font>(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, (static_cast<std::uint8_t>(204)));
		this->Label7->Location = System::Drawing::Point(166, 155);
		this->Label7->Name = L"Label7";
		this->Label7->Size = System::Drawing::Size(34, 13);
		this->Label7->TabIndex = 33;
		this->Label7->Text = L"Start";
		// 
		// Button6
		// 
		this->Button6->FlatStyle = System::Windows::Forms::FlatStyle::System;
		this->Button6->Location = System::Drawing::Point(210, 126);
		this->Button6->Name = L"Button6";
		this->Button6->Size = System::Drawing::Size(87, 23);
		this->Button6->TabIndex = 32;
		this->Button6->Text = L"none";
		this->Button6->UseVisualStyleBackColor = true;
		this->Button6->Click += std::make_shared<System::EventHandler>(this->RedefineButton);
		// 
		// Label4
		// 
		this->Label4->AutoSize = true;
		this->Label4->BackColor = System::Drawing::Color::Transparent;
		this->Label4->Font = std::make_shared<System::Drawing::Font>(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, (static_cast<std::uint8_t>(204)));
		this->Label4->Location = System::Drawing::Point(166, 68);
		this->Label4->Name = L"Label4";
		this->Label4->Size = System::Drawing::Size(28, 13);
		this->Label4->TabIndex = 27;
		this->Label4->Text = L"Fire";
		// 
		// Label6
		// 
		this->Label6->AutoSize = true;
		this->Label6->BackColor = System::Drawing::Color::Transparent;
		this->Label6->Font = std::make_shared<System::Drawing::Font>(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, (static_cast<std::uint8_t>(204)));
		this->Label6->Location = System::Drawing::Point(166, 126);
		this->Label6->Name = L"Label6";
		this->Label6->Size = System::Drawing::Size(43, 13);
		this->Label6->TabIndex = 31;
		this->Label6->Text = L"Select";
		// 
		// Button4
		// 
		this->Button4->FlatStyle = System::Windows::Forms::FlatStyle::System;
		this->Button4->Location = System::Drawing::Point(210, 68);
		this->Button4->Name = L"Button4";
		this->Button4->Size = System::Drawing::Size(87, 23);
		this->Button4->TabIndex = 28;
		this->Button4->Text = L"none";
		this->Button4->UseVisualStyleBackColor = true;
		this->Button4->Click += std::make_shared<System::EventHandler>(this->RedefineButton);
		// 
		// Button5
		// 
		this->Button5->FlatStyle = System::Windows::Forms::FlatStyle::System;
		this->Button5->Location = System::Drawing::Point(210, 97);
		this->Button5->Name = L"Button5";
		this->Button5->Size = System::Drawing::Size(87, 23);
		this->Button5->TabIndex = 30;
		this->Button5->Text = L"none";
		this->Button5->UseVisualStyleBackColor = true;
		this->Button5->Click += std::make_shared<System::EventHandler>(this->RedefineButton);
		// 
		// Label5
		// 
		this->Label5->AutoSize = true;
		this->Label5->BackColor = System::Drawing::Color::Transparent;
		this->Label5->Font = std::make_shared<System::Drawing::Font>(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, (static_cast<std::uint8_t>(204)));
		this->Label5->Location = System::Drawing::Point(166, 97);
		this->Label5->Name = L"Label5";
		this->Label5->Size = System::Drawing::Size(36, 13);
		this->Label5->TabIndex = 29;
		this->Label5->Text = L"Jump";
		// 
		// Button3
		// 
		this->Button3->FlatStyle = System::Windows::Forms::FlatStyle::System;
		this->Button3->Location = System::Drawing::Point(53, 155);
		this->Button3->Name = L"Button3";
		this->Button3->Size = System::Drawing::Size(87, 23);
		this->Button3->TabIndex = 26;
		this->Button3->Text = L"none";
		this->Button3->UseVisualStyleBackColor = true;
		this->Button3->Click += std::make_shared<System::EventHandler>(this->RedefineButton);
		// 
		// Label3
		// 
		this->Label3->AutoSize = true;
		this->Label3->BackColor = System::Drawing::Color::Transparent;
		this->Label3->Font = std::make_shared<System::Drawing::Font>(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, (static_cast<std::uint8_t>(204)));
		this->Label3->Location = System::Drawing::Point(8, 155);
		this->Label3->Name = L"Label3";
		this->Label3->Size = System::Drawing::Size(37, 13);
		this->Label3->TabIndex = 25;
		this->Label3->Text = L"Right";
		// 
		// Button2
		// 
		this->Button2->FlatStyle = System::Windows::Forms::FlatStyle::System;
		this->Button2->Location = System::Drawing::Point(53, 126);
		this->Button2->Name = L"Button2";
		this->Button2->Size = System::Drawing::Size(87, 23);
		this->Button2->TabIndex = 24;
		this->Button2->Text = L"none";
		this->Button2->UseVisualStyleBackColor = true;
		this->Button2->Click += std::make_shared<System::EventHandler>(this->RedefineButton);
		// 
		// Label2
		// 
		this->Label2->AutoSize = true;
		this->Label2->BackColor = System::Drawing::Color::Transparent;
		this->Label2->Font = std::make_shared<System::Drawing::Font>(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, (static_cast<std::uint8_t>(204)));
		this->Label2->Location = System::Drawing::Point(8, 126);
		this->Label2->Name = L"Label2";
		this->Label2->Size = System::Drawing::Size(29, 13);
		this->Label2->TabIndex = 23;
		this->Label2->Text = L"Left";
		// 
		// Button1
		// 
		this->Button1->FlatStyle = System::Windows::Forms::FlatStyle::System;
		this->Button1->Location = System::Drawing::Point(53, 97);
		this->Button1->Name = L"Button1";
		this->Button1->Size = System::Drawing::Size(87, 23);
		this->Button1->TabIndex = 22;
		this->Button1->Text = L"none";
		this->Button1->UseVisualStyleBackColor = true;
		this->Button1->Click += std::make_shared<System::EventHandler>(this->RedefineButton);
		// 
		// Label1
		// 
		this->Label1->AutoSize = true;
		this->Label1->BackColor = System::Drawing::Color::Transparent;
		this->Label1->Font = std::make_shared<System::Drawing::Font>(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, (static_cast<std::uint8_t>(204)));
		this->Label1->Location = System::Drawing::Point(8, 97);
		this->Label1->Name = L"Label1";
		this->Label1->Size = System::Drawing::Size(39, 13);
		this->Label1->TabIndex = 21;
		this->Label1->Text = L"Down";
		// 
		// Button0
		// 
		this->Button0->FlatStyle = System::Windows::Forms::FlatStyle::System;
		this->Button0->ForeColor = System::Drawing::SystemColors::ControlText;
		this->Button0->Location = System::Drawing::Point(53, 68);
		this->Button0->Name = L"Button0";
		this->Button0->Size = System::Drawing::Size(87, 23);
		this->Button0->TabIndex = 20;
		this->Button0->Text = L"none";
		this->Button0->UseVisualStyleBackColor = true;
		this->Button0->Click += std::make_shared<System::EventHandler>(this->RedefineButton);
		// 
		// Label0
		// 
		this->Label0->AutoSize = true;
		this->Label0->BackColor = System::Drawing::Color::Transparent;
		this->Label0->Font = std::make_shared<System::Drawing::Font>(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, (static_cast<std::uint8_t>(204)));
		this->Label0->Location = System::Drawing::Point(8, 68);
		this->Label0->Name = L"Label0";
		this->Label0->Size = System::Drawing::Size(23, 13);
		this->Label0->TabIndex = 19;
		this->Label0->Text = L"Up";
		// 
		// groupBox1
		// 
		this->groupBox1->BackColor = System::Drawing::Color::Transparent;
		this->groupBox1->Controls->Add(this->FullScreenChecked);
		this->groupBox1->Location = System::Drawing::Point(13, 12);
		this->groupBox1->Name = L"groupBox1";
		this->groupBox1->Size = System::Drawing::Size(309, 68);
		this->groupBox1->TabIndex = 5;
		this->groupBox1->TabStop = false;
		this->groupBox1->Text = L"Graphics settings";
		// 
		// FullScreenChecked
		// 
		this->FullScreenChecked->AutoSize = true;
		this->FullScreenChecked->Location = System::Drawing::Point(11, 28);
		this->FullScreenChecked->Name = L"FullScreenChecked";
		this->FullScreenChecked->Size = System::Drawing::Size(88, 17);
		this->FullScreenChecked->TabIndex = 1;
		this->FullScreenChecked->Text = L"Full screen";
		this->FullScreenChecked->UseVisualStyleBackColor = true;
		this->FullScreenChecked->CheckedChanged += std::make_shared<System::EventHandler>(this->FullScreenChecked_CheckedChanged);
		// 
		// OKButton
		// 
		this->OKButton->Location = System::Drawing::Point(117, 300);
		this->OKButton->Name = L"OKButton";
		this->OKButton->Size = System::Drawing::Size(94, 23);
		this->OKButton->TabIndex = 6;
		this->OKButton->Text = L"OK";
		this->OKButton->UseVisualStyleBackColor = true;
		this->OKButton->Click += std::make_shared<System::EventHandler>(this->OKButton_Click);
		// 
		// Timer3
		// 
		this->Timer3->Enabled = true;
		this->Timer3->Tick += std::make_shared<System::EventHandler>(this->Timer3_Tick);
		// 
		// setupFormBindingSource
		// 
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
		this->setupFormBindingSource->DataSource = typeof(DeltaShadow::SetupForm);
		// 
		// SetupForm
		// 
		this->setAutoScaleDimensions(System::Drawing::SizeF(7.0F, 13.0F));
		this->setAutoScaleMode(System::Windows::Forms::AutoScaleMode::Font);
		this->setBackgroundImage(::DeltaShadow::Properties->Resources::getMetall());
		this->setClientSize(System::Drawing::Size(334, 338));
		this->getControls()->Add(this->OKButton);
		this->getControls()->Add(this->groupBox1);
		this->getControls()->Add(this->JoyButtons);
		this->setFont(std::make_shared<System::Drawing::Font>(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, (static_cast<std::uint8_t>(204))));
		this->setFormBorderStyle(System::Windows::Forms::FormBorderStyle::FixedToolWindow);
		this->setIcon((std::static_pointer_cast<System::Drawing::Icon>(resources->GetObject(L"$this.Icon"))));
		this->setKeyPreview(true);
		this->setName(L"SetupForm");
		this->setText(L"Setup");
		this->setTopMost(true);
		this->FormClosed->addListener(L"this.SetupForm_FormClosed", [&] (Object sender, System::Windows::Forms::FormClosedEventArgs e) {this->SetupForm_FormClosed(sender, e);});
		this->KeyDown->addListener(L"this.SetupForm_KeyDown", [&] (Object sender, System::Windows::Forms::KeyEventArgs e) {this->SetupForm_KeyDown(sender, e);});
		this->JoyButtons->ResumeLayout(false);
		this->JoyButtons->PerformLayout();
		this->groupBox1->ResumeLayout(false);
		this->groupBox1->PerformLayout();
		(std::static_pointer_cast<System::ComponentModel::ISupportInitialize>(this->setupFormBindingSource))->EndInit();
		this->ResumeLayout(false);

	}
}
