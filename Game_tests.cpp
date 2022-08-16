#include "Player.h"
#include "Pack.h"
#include "Card.h"
#include "Game.h"
#include "unit_test_framework.h"
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;


TEST(test_game_ctor) {
    ifstream pack_input("pack.in");
    if (!pack_input.is_open()) {
        cout << "error opening pack" << endl;
    }
    Pack pack(pack_input);
    vector<Player*> players;
    Game game(players, pack);

    ASSERT_EQUAL(game.get_score_team_0(), 0);
    ASSERT_EQUAL(game.get_score_team_1(), 0);
    ASSERT_EQUAL(game.get_dealer(), 0);
}


TEST_MAIN()