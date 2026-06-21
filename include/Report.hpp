#ifndef __REPORT_HPP__
#define __REPORT_HPP__
#include <iostream>
#include "Player.hpp"
#include "ReportView.hpp"

class Report{
    public:
    Report(std::string senderUsername, std::string reportedUsername, std::string reason)
    : senderUsername_(senderUsername), reportedUsername_(reportedUsername), reason_(reason){}
    ReportView ToReportView() const;

    std::string ReportedUsername() const;
    
    private:
    std::string senderUsername_;
    std::string reportedUsername_;
    std::string reason_;
};
#endif