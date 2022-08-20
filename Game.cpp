#include <iostream>
#include <cassert>
#include <vector>
#include <array>
#include <string>
#include "Game.h"

using namespace std;
    

static void move_to_left(int &player) {
    player++;
    if (player == 4) {
        player = 0;
    }
}

static void is_valid_suit(const string &suit) {
    assert(suit == Card::SUIT_SPADES || suit == Card::SUIT_HEARTS || suit == Card::SUIT_CLUBS || suit == Card::SUIT_DIAMONDS);
}

static void is_valid_player(const int player) {
    assert(0 <= player && player < 4);
}

// EFFECTS: Intializes dealer, maker, hand to 0.
// Intializes score and trick_score to 0.  
Game::Game() : dealer(0), maker(0), hand(0) {
    score[0] = 0;
    score[1] = 0;
    trick_score[0] = 0;
    trick_score[1] = 0;    
}

// REQUIRES: game_players is a vector of Player*.  game_pack contains a valid Euchre deck.
// EFFECTS: Intializes dealer, maker, hand to 0.  Intializes the players of the game.  
// Intializes pack of cards. Intializes score and trick_score to 0. 
Game::Game(vector<Player*> &game_players, Pack &game_pack) 
    : dealer(0), maker(0), hand(0), players(game_players), pack(game_pack) {
    score[0] = 0;
    score[1] = 0;
    trick_score[0] = 0;
    trick_score[1] = 0;
}

// EFFECTS: Returns the score for the team player 0 and player 2.
int Game::get_score_team_0() const {
    return score[0];
}

// EFFECTS: Returns the score for the team player 1 and player 3.
int Game::get_score_team_1() const {
    return score[1];
}

// EFFECTS: Returns the current dealer.
int Game::get_dealer() const {
    return dealer;
}

// REQUIRES: points_to_win > 0
// EFFECTS: returns true if a team has won the game, otherwise returns false. 
bool Game::win_game(const int points_to_win, const int score_team_0, const int score_team_1) const {
    assert(points_to_win > 0);
    if (score_team_0 >= points_to_win) {
        cout << *players[0] << " and " << *players[2] << " win!" << endl;
        return true;
    } else if (score_team_1 >= points_to_win) {
        cout << *players[1] << " and " << *players[3] << " win!" << endl;
        return true; 
    }  
    return false;
}

// EFFECTS: If shuffle_on == true then pack is shuffled, otherwise
// pack is reset without shuffling.
void Game::shuffle(const bool shuffle_on) {
    if (shuffle_on) {
        pack.shuffle();
    } else {
        pack.reset();
    }  
}

// EFFECTS: Deals 5 cards to each player.  Returns the upcard.
Card Game::deal() {
    int eldest = dealer;
    for (int i = 0; i < 8; ++i) {
        move_to_left(eldest);   
        players[eldest]->add_card(pack.deal_one());
        players[eldest]->add_card(pack.deal_one());
        
        // Deals a third card every other batch.
        if (i == 0 || i == 2 || i == 5 || i == 7) {  
            players[eldest]->add_card(pack.deal_one());
        } 
    }
    Card upcard = pack.deal_one();
    cout << "Hand " << hand << endl << *players[dealer] << " deals" << endl
         << upcard << " turned up" << endl;
    return upcard;     
}

// MODIFIES: The player who orders up suit becomes the maker.
// EFFECTS: Returns the suit that is ordered up.  If suit is ordered up
// in round 1 then the dealer is given the option to pick up the upcard.
string Game::make_trump(const Card &upcard) {
    int eldest = dealer;
    bool is_dealer = false;
    int round = 1;
    string order_up_suit;
    for (int i = 0; i < 8; ++i) {
        // Defines variables for round 2 of making.
        if (i == 4) {
            is_dealer = false;
            round = 2;
        }
        move_to_left(eldest);
        if (eldest == 0) {
            is_dealer = true;
        }
        if (players[eldest]->make_trump(upcard, is_dealer, round, order_up_suit)) {
            maker = eldest;
            cout << *players[maker] << " orders up " << order_up_suit << endl;
            if (round == 1) {
                players[dealer]->add_and_discard(upcard);
            }
            cout << endl;
            return order_up_suit;    
        }
        cout << *players[eldest] << " passes" << endl;
    }
    return order_up_suit;
}

// REQUIRES: 0 <= trick_winner && trick_winner < 4.  trump is a valid suit.
// EFFECTS: Player who won the previous trick leads the next trick. 
// Returns the led_card.
Card Game::lead_trick(const string &trump, const int trick_winner) const {
    is_valid_player(trick_winner);
    is_valid_suit(trump);
    Card led_card = players[trick_winner]->lead_card(trump);
    cout << led_card << " led by " << *players[trick_winner] << endl;
    return led_card; 
}

// REQUIRES: 0 <= leader && leader < 4.  trump is a valid suit.
// EFFECTS: Returns the player who wins the trick.
int Game::play_trick(const Card &led_card, int leader, const string &trump) const {
    is_valid_player(leader);
    is_valid_suit(trump);
    Card max_card = led_card;
    int max_player = leader; 
    for (int i = 0; i < 3; ++i) {
        move_to_left(leader);
        Card card = players[leader]->play_card(led_card, trump);
        cout << card << " played by " << *players[leader] << endl;
        if (Card_less(max_card, card, led_card, trump)) {
            max_card = card;
            max_player = leader;
        }
    }
    cout << *players[max_player] << " takes the trick" << endl << endl;
    return max_player;   
}

// REQUIRES: 0 <= trick_winner && trick_winner < 4.
// MODIFIES: trick_score.
// EFFECTS: Records 1 point for the team that won the trick.
void Game::score_trick(const int trick_winner) {
    is_valid_player(trick_winner);
    if (trick_winner == 0 || trick_winner == 2) {
        trick_score[0]++;
    } else {
        trick_score[1]++;
    }
}

// EFFECTS: Returns the team that ordered up.
int Game::get_making_team() const {
    if (maker == 0 || maker == 2) {
        return 0;
    } 
    return 1; 
}

// EFFECTS: Returns the team who won the hand.
int Game::get_team_of_winning_hand() const {
    if (trick_score[0] >= 3) {
        return 0;
    }
    return 1;
}

// REQUIRES: maker_team == 0 || maker_team == 1 
// && hand_winner_team == 0 || hand_winner_team == 1.
// MODIFIES: score, trick_score, dealer, hand.
// EFFECTS: Records 1 point for the team that won a hand and an extra point 
// if the winning team had march or euchred. Resets trick_score to 0 for both teams.  
// Moves the dealer 1 to the left. Increments hand by 1.
void Game::score_hand(const int maker_team, const int hand_winner_team) {
    assert((maker_team == 0 || maker_team == 1) && (hand_winner_team == 0 || hand_winner_team == 1));
    cout << *players[hand_winner_team] << " and " << *players[hand_winner_team + 2] << " win the hand" << endl;  
    score[hand_winner_team]++; 
    if (hand_winner_team == maker_team && trick_score[hand_winner_team] == 5) {   
        cout << "march!" << endl;
        score[hand_winner_team]++;      
    }
    if (hand_winner_team != maker_team) {
        cout << "euchred!" << endl;
        score[hand_winner_team]++; 
    }  
    cout << *players[0] << " and " << *players[2] << " have " << get_score_team_0()
         << " points" << endl << *players[1] << " and " << *players[3] << " have " 
         << get_score_team_1() << " points" << endl << endl;
    trick_score[0] = 0;
    trick_score[1] = 0;
    move_to_left(dealer);
    hand++;   
}
    
      

 
     

