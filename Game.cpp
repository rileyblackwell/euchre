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

// EFFECTS: Intializes dealer, maker, hand to 0. 
Game::Game() : dealer(0), maker(0), hand(0) {}

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

int Game::get_maker() const {
    return maker;
}

bool Game::win_game(const int points_to_win, const int score_team_0, const int score_team_1) const {
    if (score_team_0 >= points_to_win) {
        cout << *players[0] << " and " << *players[2] << " win!" << endl;
        return true;
    } else if (score_team_1 >= points_to_win) {
        cout << *players[1] << " and " << *players[3] << " win!" << endl;
        return true; 
    }  
    return false;
}

// MODIFIES: Pack.
// EFFECTS: Pack is shuffled if shuffle_on == true.
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

string Game::make_trump(const Card &upcard) {
    int eldest = dealer;
    bool is_dealer = false;
    int round = 1;
    string order_up_suit;
    for (int i = 0; i < 7; ++i) {
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
            if (round == 1) {
                players[dealer]->add_and_discard(upcard);
            }
            maker = eldest;
            cout << *players[maker] << " orders up " << order_up_suit << endl << endl;
            return order_up_suit;    
        }
        cout << *players[eldest] << " passes" << endl;
    }
    // Screw the dealer.  Dealer must order up suit if all other players pass in round 2.
    players[dealer]->make_trump(upcard, true, 2, order_up_suit);
    maker = dealer;
    cout << *players[maker] << " orders up " << order_up_suit << endl << endl;
    return order_up_suit;
}

Card Game::lead_trick(const string &trump, const int trick_winner) const {
    Card led_card = players[trick_winner]->lead_card(trump);
    cout << led_card << " led by " << *players[trick_winner] << endl;
    return led_card; 
}

int Game::play_trick(const Card &led_card, int leader, const string &trump) {
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

void Game::score_trick(const int trick_winner) {
    if (trick_winner == 0 || trick_winner == 2) {
        trick_score[0]++;
    } else {
        trick_score[1]++;
    }
}

int Game::win_hand() {
    if (trick_score[0] >= 3) {
        return 0;
    }
    return 1;
}

void Game::score_hand(const int maker_team, const int hand_winner) {
    cout << *players[hand_winner] << " and " << *players[hand_winner + 2] << " win the hand" << endl;  
    score[hand_winner]++; 
    if (hand_winner == maker_team && trick_score[hand_winner] == 5) {   
        cout << "march!" << endl;
        score[hand_winner]++;      
    }
    if (hand_winner != maker_team) {
        cout << "euchred!" << endl;
        score[hand_winner]++; 
    }  
    cout << *players[0] << " and " << *players[2] << " have " << get_score_team_0()
         << " points" << endl << *players[1] << " and " << *players[3] << " have " 
         << get_score_team_1() << " points" << endl << endl;
    trick_score[0] = 0;
    trick_score[1] = 0;
    move_to_left(dealer);
    hand++;   
}
    
      

 
     

