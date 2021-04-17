#include <wx/wxprec.h>
#include <wx/url.h>
#include <wx/datetime.h>
#include <wx/sstream.h>
#include "CalendarApi.h"
#include "json.hpp"
#include <string>
#include <iomanip>
#include <ctime>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

using json = nlohmann::json;

HijriDate CalendarApi::getHijriDate() {
  if (!wxApp::IsMainLoopRunning()) {
    return HijriDate{ "", "", "" };
  }
  return CalendarApi::getHijriDateFromApi();
}

HijriDate CalendarApi::getHijriDateFromApi() {
  const wxString domain = _T("http://api.aladhan.com");
  const wxString uri = _T("/v1/gToH?date=");

  const wxString timeStr = wxDateTime::Today().Format("%d-%m-%Y");

  wxURL url(domain + uri + wxString(timeStr));
  HijriDate result{ "01", "", "1440" };

  if (url.GetError() == wxURL_NOERR) { // read response
    wxInputStream *httpStream = url.GetInputStream();
    wxString resStr = _T("");
    wxStringOutputStream outStream(&resStr);
    httpStream->Read(outStream);

    // deserialize hijri date
    auto response = json::parse(resStr);
    auto hijriDate = response["data"]["hijri"];
    // wxMessageBox(hijriDate.dump(4));
    result.day = wxString(hijriDate["day"].get<std::string>());
    result.month = wxString(hijriDate["month"]["ar"].get<std::string>());
    result.year = wxString(hijriDate["year"].get<std::string>());

    // release memory
    wxDELETE(httpStream);
  }
  else {
    wxMessageBox(_T("Unable to connect!"));
  }

  return result;
}