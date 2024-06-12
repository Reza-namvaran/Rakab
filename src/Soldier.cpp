#include "Soldier.hpp"

Soldier::Soldier(const std::string p_name, const std::string p_description) : Card(p_name, p_description) {}

void Soldier::use(std::unordered_set<Card*> players_cards){
  /// TODO: Decide on how to implement this method
}

void Soldier::setCardScore(const unsigned int& p_score){
  if(p_score >= 1)
    this->score = p_score;
  else
    this->score = 1;
}

unsigned int Soldier::getCardScore() const{ return this->score; }
