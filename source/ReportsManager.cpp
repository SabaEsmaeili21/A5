#include "iostream"
#include "ReportsManager.hpp"
#include "IdGenerator.hpp"
#include "Exception.hpp"
using namespace std;

void ReportsManager::AddReport(std::string senderUsername, std::string reportedUsername, std::string reason){
    int id = IdGenerator::GenerateReportId();
    reports_.emplace(id, Report(senderUsername, reportedUsername, reason));
}

std::map<int, ReportView> ReportsManager::GetReports() const{
    std::map<int, ReportView> reports;
    for(const auto& [id, report] : reports_){

        reports.emplace(id, report.ToReportView());
    }
    if(reports.empty())
        throw Empty();
    return reports;
}

const Report& ReportsManager::FindReport(int id) const{
    if(reports_.find(id) == reports_.end())
        throw NotFound();
    return reports_.at(id);
}

void ReportsManager::Delete(int id){
    if(reports_.find(id) == reports_.end())
        throw NotFound();
    reports_.erase(id); 
}