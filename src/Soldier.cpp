#include "Soldier.hpp"

Soldier::Soldier(const std::string p_name, const unsigned int score) : Card(p_name)
{
  this->setCardScore(score);
  this->setCardDescription("This Card will add " + std::to_string(score) + " points!");
  /// FIXME: Set a better description
}

void Soldier::use(std::unordered_set<Card *> &hand_cards, std::unordered_set<Card *> &player_cards, Player &player, IO_Interface &terminal_handler)
{
  int score = 0;
  for (Card *card : player_cards)
  {
    if (card->getCardType() == "Soldier")
    {
      Soldier *soldier = dynamic_cast<Soldier *>(card);
      score += soldier->getCardScore();
    }
  }
  player.setPlayerScore(score);
}

std::string Soldier::getCardType() const { return "Soldier"; }

void Soldier::setCardScore(const unsigned int &p_score)
{
  if (p_score >= 1)
    this->score = p_score;
  else
    this->score = 1;
}

unsigned int Soldier::getCardScore() const { return this->score; }
