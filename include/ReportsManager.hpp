#ifndef __REPORTSMANAGER_HPP__
#define __REPORTSMANAGER_HPP__

#include <iostream>
#include <map>
#include "Report.hpp"
#include "ReportView.hpp"

class ReportsManager{
    public:
    ReportsManager() = default;
    void AddReport(std::string senderUsername, std::string reportedUsername, std::string reason);
    std::map<int, ReportView> GetReports() const;
    private:
    std::map<int, Report> reports_;
};
#endif