#include "IdGenerator.hpp"

int IdGenerator::nextInvitationId = 1;
int IdGenerator::nextMatchId = 1;
int IdGenerator::nextReportId = 1;

int IdGenerator::GenerateInvitationId()
{
    return nextInvitationId++;
}

int IdGenerator::GenerateMatchId()
{
    return nextMatchId++;
}

int IdGenerator::GenerateReportId()
{
    return nextReportId++;
}