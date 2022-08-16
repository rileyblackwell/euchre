#include <iostream>
#include <fstream>
#include "Game.h"
#include "Player.h"
#include "Pack.h"
#include "Card.h"

using namespace std;


static bool is_simple_or_human_player(const string &player_type) {
    if (player_type != "Simple" && player_type != "Human") {
        return false;
    }
    return true;
}

// EFFECTS: Returns true if there is an error, returns false if there is not.
static bool is_arg_error(int argc, char *argv[]) {
    const string shuffle = argv[2];
    if (argc != 12 || (stoi(argv[3]) < 0 || stoi(argv[3]) > 100)
        || (shuffle != "shuffle" && shuffle != "noshuffle")) {
        return true;
    }
    
    for (int i = 5; i < 12; i += 2) {
        if (!is_simple_or_human_player(argv[i])) {
            return true;    
        }
    }
    return false;
}

static void print_args(int argc, char *argv[]) {
    for (int i = 0; i < argc; ++i) {
        cout << argv[i] << " ";
    }
    cout << endl;
}

static void run_simulation(vector<Player*> &players, Pack &pack, 
                           const string &shuffle, const int points_to_win) {
    bool shuffle_on = true;
    if (shuffle  == "noshuffle") {
        shuffle_on = false;
    }
    
    Game game(players, pack);
    
    while (!game.win_game(points_to_win, game.get_score_team_0(), game.get_score_team_1())) {
        game.shuffle(shuffle_on);
        Card upcard = game.deal();
        string trump_suit = game.make_trump(upcard);
        
        int trick_winner = game.get_dealer() + 1;
        // Player 0 == 0 || Player 0 == 4.
        if (trick_winner == 4) {
            trick_winner = 0;
        }
        // Plays 1 hand.  Eldest hand leads the first trick.
        for (int i = 0; i < 5; ++i) {
            Card led_card = game.lead_trick(trump_suit, trick_winner);
            trick_winner = game.play_trick(led_card, trick_winner, trump_suit);
            game.score_trick(trick_winner);
        }
        game.score_hand(game.get_making_team(), game.get_team_of_winning_hand());   
    }       
}


int main(int argc, char *argv[]) {
    if (is_arg_error(argc, argv)) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
        << "NAME4 TYPE4" << endl;
        return 1;
    }
    print_args(argc, argv);

    ifstream pack_input(argv[1]);
    if (!pack_input.is_open()) { 
        cout << "Error opening " << argv[1] << endl;
        return 1;
    }
    Pack pack(pack_input);
    
    vector<Player*> players;
    // Player_factory creates each player in dynamic memory.
    players.push_back(Player_factory(argv[4], argv[5]));
    players.push_back(Player_factory(argv[6], argv[7]));
    players.push_back(Player_factory(argv[8], argv[9]));
    players.push_back(Player_factory(argv[10], argv[11]));
    
    const string shuffle = argv[2];
    const int points_to_win = stoi(argv[3]); 
    run_simulation(players, pack, shuffle, points_to_win);

    // Delete each player that was created with dynamic memory in the Player_factory.    
    for (int i = 0; i < int(players.size()); ++i) {
        delete players[i];
    }   
    
    return 0;
}