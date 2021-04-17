#pragma once


class HijriDate {
public:
  wxString day;
  wxString month;
  wxString year;
};

class CalendarApi {
public:
  HijriDate getHijriDate();
private:
  HijriDate getHijriDateFromApi();  
};
