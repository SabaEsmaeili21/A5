#include <iostream>
#include "Report.hpp"

using namespace std;

ReportView Report::ToReportView() const{
    return ReportView{senderUsername_, reportedUsername_, reason_};
}