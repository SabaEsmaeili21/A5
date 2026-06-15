#include <iostream>
#include "Match.hpp"
#include "PlayerSide.hpp"
#include "Exception.hpp"
using namespace std;

void Match::ProcessMove(Move move, string username){
    Round& round = rounds_.at(currentRound_); //without the & only the copy is modified 
    /*You're saying: "Give me an alias to the Round inside the map."
    Not: "Create a new Round object and copy the contents."*/

    if(username == player1Username_){
        if(!CanShoot(move, player1Bullets_))
            throw BadRequest();
        round.RegisterMove(move, PlayerSide::Player1);
    }

    else if(username == player2Username_){
        if(!CanShoot(move, player2Bullets_))
            throw BadRequest();
        round.RegisterMove(move, PlayerSide::Player2);
    }

    if(round.IsComplete())
        ResolveRound();
}

void Match::ResolveRound(){
    Round& round = rounds_.at(currentRound_);

    Move player1Move = round.Player1Move();
    Move player2Move = round.Player2Move();

    if (player1Move == Move::SHOOT)
        player1Bullets_--;

    if (player2Move == Move::SHOOT)
        player2Bullets_--;

    if (player1Move == Move::RELOAD)
        player1Bullets_++;

    if (player2Move == Move::RELOAD)
        player2Bullets_++;

    switch (round.Outcome()) {
        case RoundOutcome::Player1Wins:
            winnerUsername_ = player1Username_;
            isFinished_ = true;
            return;

        case RoundOutcome::Player2Wins:
            winnerUsername_ = player2Username_;
            isFinished_ = true;
            return;

        case RoundOutcome::NoWinner:
            currentRound_++;
            rounds_.emplace(currentRound_, Round{});
            return;
    }
}

bool Match::IsFinished() const{
    return isFinished_;
}

std::string Match::WinnerUsername() const{
    return winnerUsername_;
}

std::string Match::LoserUsername() const{
    if(player1Username_ == winnerUsername_)
        return player2Username_;
    return player1Username_;
}

bool Match::CanShoot(Move move, int bulletCount){
    return !(bulletCount == 0 && move == Move::SHOOT);
}

MatchStatusView Match::MatchStatus(std::string username)const{
    MatchStatusView matchStatus;

    const Round& round = rounds_.at(currentRound_);

    Move player1Move = round.Player1Move();
    Move player2Move = round.Player2Move(); 

    bool isPlayer1 = username == player1Username_;
    Move yourMove = isPlayer1 ? player1Move : player2Move;
    Move opponentMove = isPlayer1 ? player2Move : player1Move;
    int yourBullets = isPlayer1 ? player1Bullets_ : player2Bullets_;

    matchStatus.turnNum = currentRound_;
    matchStatus.yourMove = yourMove;
    matchStatus.opponentHasPlayed = opponentMove != Move::PENDING;
    matchStatus.yourRemainingBullets = yourBullets;
    matchStatus.history = RoundHistory(username);
    return matchStatus;
}

std::vector<std::pair<Move, Move>> Match::RoundHistory(std::string username) const{
    vector<pair<Move, Move>> history;
    for(const auto& [roundNum, round] : rounds_){

        if (roundNum == currentRound_)
            continue;
        Move player1Move = round.Player1Move();
        Move player2Move = round.Player2Move();

        bool isPlayer1 = username == player1Username_;
        Move yourMove = isPlayer1 ? player1Move : player2Move;
        Move opponentMove = isPlayer1 ? player2Move : player1Move;
        history.push_back({opponentMove, yourMove});
    }
    return history;
}