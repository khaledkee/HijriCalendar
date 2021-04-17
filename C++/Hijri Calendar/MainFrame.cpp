#include <wx/wxprec.h>
#include "MainFrame.h"
#include "CalendarApi.h"
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#pragma execution_character_set("utf-8")

MainFrame::MainFrame()
  : wxFrame(NULL, wxID_ANY, "Hello World", wxDefaultPosition, wxDefaultSize, wxSTAY_ON_TOP|wxBORDER_SUNKEN)
{
  createGUI();
  setStartPosition();
  createDayTimer();

}

void MainFrame::setStartPosition() {
  int dw, dh;
  wxDisplaySize(&dw, &dh);
  int w, h;
  w = this->GetSize().GetX();
  h = this->GetSize().GetY();
  this->SetPosition(wxPoint(dw - w - 75, dh - h - 75));
}


void MainFrame::createGUI() {
  // CreateStatusBar();
  // SetStatusText("Hijri Calendar by KhaledKEE!");

  // Main Sizer
  wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

  mainSizer->SetSizeHints(this);
  this->SetSizer(mainSizer);
  this->SetAutoLayout(true);

  // Top panel

  // Month panel
  wxPanel *monthPanel = new wxPanel(this, wxID_ANY);
  mainSizer->Add(monthPanel, 1, wxALIGN_CENTER | wxEXPAND, 0);
  monthPanel->SetBackgroundColour(wxColor(195, 4, 16));



  wxBoxSizer * monthSizer = new wxBoxSizer(wxVERTICAL);
  monthPanel->SetSizer(monthSizer);

  wxStaticText *monthText = new wxStaticText(monthPanel, wxID_ANY, wxString(_T("شعـبان")));
  monthText->SetFont(wxFont(22, wxDEFAULT, wxNORMAL, wxNORMAL));
  monthText->SetForegroundColour(wxColor(255, 255, 255));
  monthSizer->Add(monthText, 1, wxALIGN_CENTER | wxALL, 5);

  monthSizer->Fit(monthPanel);

  // day and year panel
  wxPanel *dayYearPanel = new wxPanel(this, wxID_ANY);
  mainSizer->Add(dayYearPanel, 2, wxALIGN_CENTER | wxEXPAND, 0);
  dayYearPanel->SetBackgroundColour(wxColor(247, 247, 247));

  wxBoxSizer * dayYearSizer = new wxBoxSizer(wxVERTICAL);
  dayYearPanel->SetSizer(dayYearSizer);

  wxStaticText *dayText = new wxStaticText(dayYearPanel, wxID_ANY, wxString("18"));
  dayText->SetFont(wxFont(28, wxDEFAULT, wxNORMAL, wxBOLD));
  dayText->SetForegroundColour(wxColor(195, 4, 16));
  dayYearSizer->Add(dayText, 1, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);

  wxStaticText *yearText = new wxStaticText(dayYearPanel, wxID_ANY, wxString(_T("1442هـ")));
  yearText->SetFont(wxFont(16, wxDEFAULT, wxNORMAL, wxBOLD));
  dayYearSizer->Add(yearText, 1, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);


  GetSizer()->Fit(this);
  GetSizer()->SetSizeHints(this);
}


void MainFrame::createDayTimer() {
  const int dayTimerID = wxID_HIGHEST + 1;
  dayTimer = new wxTimer(this, dayTimerID);
  Bind(wxEVT_TIMER, &MainFrame::dayTimerEvent, this, dayTimerID);
  dayTimer->Start(1 * 60 * 60);
}

void MainFrame::dayTimerEvent(wxTimerEvent& event) {

}


void MainFrame::OnLeftDown(wxMouseEvent& evt)
{
  CaptureMouse();
  wxPoint pos = ::wxGetMousePosition();
  wxPoint origin = this->GetPosition();
  int dx = pos.x - origin.x;
  int dy = pos.y - origin.y;
  m_delta = wxPoint(dx, dy);
}

void MainFrame::OnLeftUp(wxMouseEvent& evt)
{
  if (HasCapture())
    ReleaseMouse();
}

void MainFrame::OnMouseMove(wxMouseEvent& evt)
{
  if (evt.Dragging() && evt.LeftIsDown())
  {
    wxPoint pos = ::wxGetMousePosition();
    Move(wxPoint(pos.x - m_delta.x, pos.y - m_delta.y));
  }
}