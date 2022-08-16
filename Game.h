#ifndef GAME_H
#define GAME_H
/* Game.h
 * Euchre game interface
 */
#include <iostream>
#include <vector>
#include <array>
#include <string>
#include "Player.h"
#include "Pack.h"
#include "Card.h"


class Game {
    public:
        // EFFECTS: Intializes dealer, maker, hand to 0. 
        Game();

        // EFFECTS: Intializes dealer, maker, hand to 0.  Intializes the players of the game.  
        // Intializes pack of cards. Intializes score and trick_score to 0.
        Game(std::vector<Player*> &game_players, Pack &game_pack);

        // EFFECTS: Returns the score for the team player 0 and player 2.
        int get_score_team_0() const;

        // EFFECTS: Returns the score for the team player 1 and player 3.
        int get_score_team_1() const;

        // EFFECTS: Returns the current dealer.
        int get_dealer() const;

        int get_maker() const;
        
        bool win_game(const int points_to_win, const int score_team_0, const int score_team_1) const;

        // MODIFIES: Pack.
        // EFFECTS: Pack is shuffled if shuffle_on == true.
        void shuffle(const bool shuffle_on);
        
        // EFFECTS: Deals 5 cards to each player.  Returns the upcard.
        Card deal();

        std::string make_trump(const Card &upcard);

        Card lead_trick(const std::string &trump, const int trick_winner) const;
        
        int play_trick(const Card &led_card, int leader, const std::string &trump);

        void score_trick(const int trick_winner);

        int win_hand();

        void score_hand(const int maker, const int hand_winner);
        

    private:
        int dealer;
        int maker;
        int hand;
        std::vector<Player*> players;
        Pack pack; 
        std::array<int, 2> score;
        std::array<int, 2> trick_score;         
};

#endif // GAME_H 