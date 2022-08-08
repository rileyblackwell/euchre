#include "Player.h"
#include "unit_test_framework.h"
#include <sstream>
#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

// Add more tests here
// TEST(test_player_factory) {
  
     
// }

TEST(test_print_player_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ostringstream ss_output;
    ss_output << *alice;
    ASSERT_EQUAL(ss_output.str(), "Alice");

    delete alice;   
}

// TEST(test_player_add_card) {
//     Player * alice = Player_factory("Alice", "Simple");
//     alice->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));

//     delete alice;
// }

TEST(test_player_make_trump) {
    Player * alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
    alice->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    alice->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    string order_up_suit = " ";
    
    ASSERT_TRUE(alice->make_trump(Card(Card::RANK_KING, Card::SUIT_HEARTS), false, 1, order_up_suit));
    ASSERT_EQUAL(order_up_suit, Card::SUIT_HEARTS);
    
    order_up_suit = " ";
    ASSERT_FALSE(alice->make_trump(Card(Card::RANK_NINE, Card::SUIT_SPADES), true, 1, order_up_suit));
    ASSERT_EQUAL(order_up_suit, " ");
    
    order_up_suit = " ";
    ASSERT_TRUE(alice->make_trump(Card(Card::RANK_KING, Card::SUIT_HEARTS), false, 2, order_up_suit));
    ASSERT_EQUAL(order_up_suit, Card::SUIT_DIAMONDS);
    
    delete alice; 
}

TEST(test_player_make_trump_is_dealer) {
    Player * alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    alice->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    alice->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
    alice->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    string order_up_suit = " ";

    // Tests screw the dealer
    ASSERT_TRUE(alice->make_trump(Card(Card::RANK_KING, Card::SUIT_HEARTS), true, 2, order_up_suit));
    ASSERT_EQUAL(order_up_suit, Card::SUIT_DIAMONDS);

    order_up_suit = " ";
    ASSERT_FALSE(alice->make_trump(Card(Card::RANK_KING, Card::SUIT_HEARTS), false, 2, order_up_suit));
    ASSERT_EQUAL(order_up_suit, " "); 

    delete alice;    
}    

// TEST(test_player_add_and_discard) {
//     Player * alice = Player_factory("Alice", "Simple");
//     alice->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
//     alice->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
//     alice->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
//     alice->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
//     alice->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));

//     alice->add_and_discard(Card(Card::RANK_KING, Card::SUIT_HEARTS));

//     delete alice;       
// }
 


TEST_MAIN()
