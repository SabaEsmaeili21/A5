#ifndef __IDGENERATOR_HPP__
#define __IDGENERATOR_HPP__

class IdGenerator{
    public:
    static int GenerateInvitationId();
    static int GenerateMatchId();
    static int GenerateReportId();
    private:
    static int nextInvitationId;
    static int nextMatchId;
    static int nextReportId;
};
#endif