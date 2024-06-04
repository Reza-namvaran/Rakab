#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>

#include "Card.hpp"

class Player{
    private:
        std::string name;
        unsigned int age;
        std::vector<Card> cards;        
        /// TODO: Sign
    public:
        Player(const std::string& p_name, const unsigned int& age);
                
        /// IMPORTANT: Decide on using full name or first & last name
        
        /// NOTE: Added setters, so players can change their personal info if needed. 
        
        void setPlayerName(const std::string& p_name);

        void setPlayerAge(const unsigned int& p_age);

        std::string getPlayerName() const;

        unsigned int getPlayerAge() const;
};

#endif
