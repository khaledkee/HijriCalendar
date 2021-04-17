#pragma once
class MainFrame : public wxFrame
{
public:
  MainFrame();
private:
  wxTimer *dayTimer;
  wxPoint m_delta;
  void createGUI();
  void setStartPosition();
  void createDayTimer();
  void dayTimerEvent(wxTimerEvent& event);
  // drag frame
  void OnLeftDown(wxMouseEvent& evt);
  void OnLeftUp(wxMouseEvent& evt);
  void OnMouseMove(wxMouseEvent& evt);
};
enum
{
  ID_Hello = 1
};