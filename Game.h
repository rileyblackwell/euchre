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

        // REQUIRES: game_players is a vector of Player*.  game_pack contains a valid Euchre deck.
        // EFFECTS: Intializes dealer, maker, hand to 0.  Intializes the players of the game.  
        // Intializes pack of cards. Intializes score and trick_score to 0.
        Game(std::vector<Player*> &game_players, Pack &game_pack);

        // EFFECTS: Returns the score for the team player 0 and player 2.
        int get_score_team_0() const;

        // EFFECTS: Returns the score for the team player 1 and player 3.
        int get_score_team_1() const;

        // EFFECTS: Returns the current dealer.
        int get_dealer() const;
        
        // REQUIRES: points_to_win > 0
        // EFFECTS: returns true if a team has won the game, otherwise returns false. 
        bool win_game(const int points_to_win, const int score_team_0, const int score_team_1) const;

        // MODIFIES: pack. 
        // EFFECTS: If shuffle_on == true then pack is shuffled, otherwise
        // pack is reset without shuffling.
        void shuffle(const bool shuffle_on);
        
        // MODIFIES: pack. 
        // EFFECTS: Deals 5 cards to each player.  Returns the upcard.
        Card deal();

        // MODIFIES: The player who orders up suit becomes the maker.
        // EFFECTS: Returns the suit that is ordered up.  If suit is ordered up
        // in round 1 then the dealer is given the option to pick up the upcard.
        std::string make_trump(const Card &upcard);

        // REQUIRES: 0 <= trick_winner && trick_winner < 4.  trump is a valid suit.
        // EFFECTS: Player who won the previous trick leads the next trick. 
        // Returns the led_card.
        Card lead_trick(const std::string &trump, const int trick_winner) const;
        
        // REQUIRES: 0 <= leader && leader < 4.  trump is a valid suit.
        int play_trick(const Card &led_card, int leader, const std::string &trump) const;

        // REQUIRES: 0 <= trick_winner && trick_winner.
        // MODIFIES: trick_score.
        // EFFECTS: Records the score for the team that won the trick.  
        void score_trick(const int trick_winner);

        // EFFECTS: Returns the team that ordered up.
        int get_making_team() const;
        
        // EFFECTS: Returns the team who won the hand.
        int get_team_of_winning_hand() const;

        void score_hand(const int maker_team, const int hand_winner);
        

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