#include "Soldier.hpp"

Soldier::Soldier(const std::string p_name, const unsigned int score) : Card(p_name) {
    this->setCardScore(score);
}

void Soldier::use(std::shared_ptr<Player> player, IO_Interface &terminal_handler) {
    int score = 0;
    for (const auto &card : player->getCard(false)) {
        if (card->getCardType() == "Soldier") {
            std::shared_ptr<Soldier> soldier = std::dynamic_pointer_cast<Soldier>(card);
            if (soldier) {
                score += soldier->getCardScore();
            }
        }
    }
    player->setPlayerScore(score);
}

std::string Soldier::getCardType() const {
    return "Soldier";
}

void Soldier::setCardScore(const unsigned int &p_score) {
    if (p_score >= 1) {
        this->score = p_score;
    } else {
        this->score = 1;
    }
}

unsigned int Soldier::getCardScore() const {
    return this->score;
}