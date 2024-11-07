#pragma once
#include <wx/wx.h>
#include <wx/spinctrl.h>
class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
	
private:
	void OnPlanButtonClick(wxCommandEvent& evt);
	void OnCancelButtonClick(wxCommandEvent& evt);
	void OnCommentChange(wxCommandEvent& evt);
	void OnSpin1Change(wxSpinEvent& evt);
	void OnSpin2Change(wxSpinEvent& evt);
	void OnSpin3Change(wxSpinEvent& evt);
	void OnTimeImplChoise1Change(wxCommandEvent& evt);
	void OnTimeImplChoise2Change(wxCommandEvent& evt);
	void OnTimeImplChoise3Change(wxCommandEvent& evt);
	void OnChoiseModeChange(wxCommandEvent& evt);
	wxDECLARE_EVENT_TABLE();

	
	
};

