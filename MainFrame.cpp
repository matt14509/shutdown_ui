#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <string>
#include <wx/chartype.h>

//#define DEBUG


using namespace std;
enum id {
	BUTTON_ID_PLAN = 2,
	COMMENT_ID = 3,
	spin_ID_1 = 4,
	spin_ID_2 = 5,
	spin_ID_3 = 6,
	time_impl_choise1_ID = 7,
	time_impl_choise2_ID = 8,
	time_impl_choise3_ID = 9,
	BUTTON_ID_CANCEL = 10,
	CHOISE_MODE_ID = 11,
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_BUTTON(BUTTON_ID_PLAN, MainFrame::OnPlanButtonClick)
EVT_BUTTON(BUTTON_ID_CANCEL, MainFrame::OnCancelButtonClick)
EVT_TEXT(COMMENT_ID, MainFrame::OnCommentChange)
EVT_SPINCTRL(spin_ID_1, MainFrame::OnSpin1Change)
EVT_SPINCTRL(spin_ID_2, MainFrame::OnSpin2Change)
EVT_SPINCTRL(spin_ID_3, MainFrame::OnSpin3Change)
EVT_CHOICE(time_impl_choise1_ID, MainFrame::OnTimeImplChoise1Change)
EVT_CHOICE(time_impl_choise2_ID, MainFrame::OnTimeImplChoise2Change)
EVT_CHOICE(time_impl_choise3_ID, MainFrame::OnTimeImplChoise3Change)
EVT_CHOICE(CHOISE_MODE_ID, MainFrame::OnChoiseModeChange)
wxEND_EVENT_TABLE()


int Spin1Num = 0;
int TimeImplChoise1 = -1;
int Spin2Num = 0;
int TimeImplChoise2 = -1;
int Spin3Num = 0;
int TimeImplChoise3 = -1;
int ModeChoise = -1;
string comment = "Запланировано с shutdown_gui";



MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY,title){
	wxPanel* panel = new wxPanel(this); /*костыль для правельного отображения*/


	wxStaticText* staticText1 = new wxStaticText(panel, wxID_ANY, "Через:", wxPoint(0, 0));
	wxStaticText* staticText2 = new wxStaticText(panel, wxID_ANY, "Выберите действие:", wxPoint(200, 0));

	wxArrayString mode;
	mode.Add("Завершение работы");
	mode.Add("Гибернация");
	mode.Add("Перезагрузка");
	wxChoice* mode_choise = new wxChoice(panel, CHOISE_MODE_ID, wxPoint(210, 20), wxSize(190, -1), mode);

	wxArrayString time_impl;
	time_impl.Add("часов");
	time_impl.Add("минут");
	time_impl.Add("секунд");
	wxChoice* time_impl_choise1 = new wxChoice(panel, time_impl_choise1_ID, wxPoint(100, 20), wxSize(100, -1), time_impl);
	wxChoice* time_impl_choise2 = new wxChoice(panel, time_impl_choise2_ID, wxPoint(100, 50), wxSize(100, -1), time_impl);
	wxChoice* time_impl_choise3 = new wxChoice(panel, time_impl_choise3_ID, wxPoint(100, 80), wxSize(100, -1), time_impl);

	wxSpinCtrl* spin1 = new wxSpinCtrl(panel, spin_ID_1, " ", wxPoint(0, 20), wxSize(100, -1));		spin1->SetRange(0, 100000);
	wxSpinCtrl* spin2 = new wxSpinCtrl(panel, spin_ID_2, " ", wxPoint(0, 50), wxSize(100, -1));		spin2->SetRange(0, 100000);
	wxSpinCtrl* spin3 = new wxSpinCtrl(panel, spin_ID_3, " ", wxPoint(0, 80), wxSize(100, -1));		spin3->SetRange(0, 100000);

	wxStaticText* staticText3 = new wxStaticText(panel, wxID_ANY, "Введите комментарий:", wxPoint(0, 130));

	wxTextCtrl* comment = new wxTextCtrl(panel, COMMENT_ID, "Запланировано с shutdown_gui",wxPoint(0,150),wxSize(200,-1));

	wxButton* plan_button = new wxButton(panel, BUTTON_ID_PLAN, "Запланировать", wxPoint(300, 250), wxSize(100, 35));
	wxButton* cancel_button = new wxButton(panel, BUTTON_ID_CANCEL, "Отмена плана", wxPoint(0, 250), wxSize(100, 35));


	CreateStatusBar();
}


void MainFrame::OnPlanButtonClick(wxCommandEvent& evt)
{
	if (ModeChoise != -1 && (Spin1Num || Spin2Num || Spin3Num) != 0 && (TimeImplChoise1 || TimeImplChoise2 || TimeImplChoise3) != -1)
	{
		int number_of_seconds = 0;
		switch (TimeImplChoise1)
		{
		case 0:
			number_of_seconds += Spin1Num * 3600;
			break;
		case 1:
			number_of_seconds += Spin1Num * 60;
			break;
		case 2:
			number_of_seconds += Spin1Num;
			break;
		}
		switch (TimeImplChoise2)
		{
		case 0:
			number_of_seconds += Spin2Num * 3600;
			break;
		case 1:
			number_of_seconds += Spin2Num * 60;
			break;
		case 2:
			number_of_seconds += Spin2Num;
			break;
		}
		switch (TimeImplChoise3)
		{
		case 0:
			number_of_seconds += Spin3Num * 3600;
			break;
		case 1:
			number_of_seconds += Spin3Num * 60;
			break;
		case 2:
			number_of_seconds += Spin3Num;
			break;
		}

		string number_of_seconds_string = to_string(number_of_seconds);
		string ModeChose_string;
		switch (ModeChoise)
		{
		case 0:
			ModeChose_string = "/s";
		case 1:
			ModeChose_string = "/h";
		case 2:
			ModeChose_string = "/r";
		}
		std::string command = "shutdown /t " + std::to_string(number_of_seconds) + " " + ModeChose_string + " /c \"" + comment + "\"";
#ifdef DEBUG
		wxString command_wx(command);
		wxLogStatus(command_wx);
#endif // DEBUG
		system(command.c_str());



		wxLogStatus("План поставлен");
	}
	else
	{
		wxLogStatus("Не удалось составить план");
	}
}
void MainFrame::OnCancelButtonClick(wxCommandEvent& evt)
{
	system("shutdown /a");
	wxLogStatus("Выполнение отменено");
}

void MainFrame::OnCommentChange(wxCommandEvent& evt)
{
	comment = std::string(evt.GetString().mb_str());
#ifdef DEBUG
	wxString test(comment);
	wxLogStatus(test);
#endif // DEBUG
}


void MainFrame::OnSpin1Change(wxSpinEvent& evt)
{
	Spin1Num = evt.GetInt();
#ifdef DEBUG
	wxString mystring;
	mystring << Spin1Num;
	wxLogStatus(mystring);
#endif // DEBUG
}
void MainFrame::OnTimeImplChoise1Change(wxCommandEvent& evt)
{

	TimeImplChoise1 = evt.GetSelection();
#ifdef DEBUG
	wxString mystring;
	mystring << TimeImplChoise1;
	wxLogStatus(mystring);
#endif // DEBUG
}


void MainFrame::OnSpin2Change(wxSpinEvent& evt)
{
	Spin2Num = evt.GetInt();
#ifdef DEBUG
	wxString mystring;
	mystring << Spin2Num;
	wxLogStatus(mystring);
#endif // DEBUG
}
void MainFrame::OnTimeImplChoise2Change(wxCommandEvent& evt)
{
	TimeImplChoise2= evt.GetSelection();
#ifdef DEBUG
	wxString mystring;
	mystring << TimeImplChoise2;
	wxLogStatus(mystring);
#endif // DEBUG
}


void MainFrame::OnSpin3Change(wxSpinEvent& evt)
{
	Spin3Num = evt.GetInt();
#ifdef DEBUG
	wxString mystring;
	mystring << Spin3Num;
	wxLogStatus(mystring);
#endif // DEBUG
}

void MainFrame::OnTimeImplChoise3Change(wxCommandEvent& evt)
{
	TimeImplChoise3 = evt.GetSelection();
#ifdef DEBUG
	wxString mystring;
	mystring << TimeImplChoise3;
	wxLogStatus(mystring);
#endif // DEBUG
}

void MainFrame::OnChoiseModeChange(wxCommandEvent& evt)
{
	ModeChoise = evt.GetSelection();
#ifdef DEBUG
	wxString mystring;
	mystring << ModeChoise;
	wxLogStatus(mystring);
#endif // DEBUG
}