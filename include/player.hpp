#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

class Player{
    private:
        std::string name;
        unsigned int age;
        /// TODO: Cards
        /// TODO: Sign
    public:
        Player(const std::string& p_name, const unsigned int& age);

        void setPlayerName(const std::string& p_name);

        void setPlayerAge(const unsigned int& p_age);

        std::string getPlayerName() const;

        unsigned int getPlayerAge() const;
};

#endif
