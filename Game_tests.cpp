#include "Game.h"
#include "unit_test_framework.h"
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;


TEST(test_game_ctor) {
    Pack pack;
    vector<Player*> players;
    Game game(players, pack);

    ASSERT_EQUAL(game.get_score_team_0(), 0);
    ASSERT_EQUAL(game.get_score_team_1(), 0);
    ASSERT_EQUAL(game.get_dealer(), 0);
}

TEST(test_game_default_ctor) {
    Game game;
    ASSERT_EQUAL(game.get_score_team_0(), 0);
    ASSERT_EQUAL(game.get_score_team_1(), 0);
    ASSERT_EQUAL(game.get_dealer(), 0);
}
 

TEST_MAIN()