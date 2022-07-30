#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>
#include <sstream>
#include <cstring>

using namespace std;

 
TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}

// Add more test cases here
TEST(test_card_default_ctor) {
    Card c;
    ASSERT_EQUAL(Card::RANK_TWO, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, c.get_suit());
}

TEST(test_card_get_rank) {
    Card c(Card::RANK_THREE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_THREE, c.get_rank());
 
}

TEST(test_card_get_suit) {
    Card c(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, c.get_suit());
}

TEST(test_card_get_suit_considers_trump) {
    Card left_bower(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(Card::SUIT_HEARTS, left_bower.get_suit(Card::SUIT_HEARTS));    

    Card trump_card(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::SUIT_HEARTS, trump_card.get_suit(Card::SUIT_HEARTS));

    Card not_trump_card(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, not_trump_card.get_suit(Card::SUIT_HEARTS));   
}

TEST(test_card_is_face) {
    Card face_card(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_TRUE(face_card.is_face());

    Card not_face_card(Card::RANK_THREE, Card::SUIT_HEARTS);
    ASSERT_FALSE(not_face_card.is_face());
}

TEST(test_card_is_right_bower) {
    Card right_bower(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(right_bower.is_right_bower(Card::SUIT_DIAMONDS));

    Card left_bower(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_FALSE(left_bower.is_right_bower(Card::SUIT_DIAMONDS));
}

TEST(test_card_is_left_bower) {
    Card left_bower(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_TRUE(left_bower.is_left_bower(Card::SUIT_DIAMONDS));
    
    Card right_bower(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_FALSE(right_bower.is_left_bower(Card::SUIT_DIAMONDS));   
}

TEST(test_card_is_trump) {
    Card trump_card(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_TRUE(trump_card.is_trump(Card::SUIT_HEARTS));

    Card left_bower(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(left_bower.is_trump(Card::SUIT_HEARTS));
    
    Card not_trump_card(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    ASSERT_FALSE(not_trump_card.is_trump(Card::SUIT_HEARTS));   
}

TEST(test_operator_lower_than) {
    Card min_card(Card::RANK_TWO, Card::SUIT_SPADES);
    
    Card min_rank_card(Card::RANK_TWO, Card::SUIT_HEARTS);
    ASSERT_TRUE(min_card < min_rank_card);
    ASSERT_FALSE(min_rank_card < min_card);

    Card min_suit_card(Card::RANK_THREE, Card::SUIT_SPADES);
    ASSERT_TRUE(min_card < min_suit_card);
    ASSERT_FALSE(min_suit_card < min_card);

    // Tests if 2 cards are the same card
    ASSERT_FALSE(min_card < min_card);
}

TEST(test_operator_lower_than_or_equal_to) {
    Card min_card(Card::RANK_TWO, Card::SUIT_SPADES);

    ASSERT_TRUE(min_card <= min_card);

    Card rank_three_card(Card::RANK_THREE, Card::SUIT_SPADES);
    ASSERT_TRUE(min_card <= rank_three_card);
    ASSERT_FALSE(rank_three_card <= min_card);
}

TEST(test_operator_higher_than) {
    Card min_card(Card::RANK_TWO, Card::SUIT_SPADES);
    
    Card min_rank_card(Card::RANK_TWO, Card::SUIT_HEARTS);
    ASSERT_TRUE(min_rank_card > min_card);
    ASSERT_FALSE(min_card > min_rank_card);
    
    Card min_suit_card(Card::RANK_THREE, Card::SUIT_SPADES);
    ASSERT_TRUE(min_suit_card > min_card);
    ASSERT_FALSE(min_card > min_suit_card);
    
    // Tests if 2 cards are the same card
    ASSERT_FALSE(min_card > min_card);    
}

TEST(test_operator_higher_than_or_equal_to) {
    Card min_card(Card::RANK_TWO, Card::SUIT_SPADES);

    ASSERT_TRUE(min_card >= min_card);

    Card rank_three_card(Card::RANK_THREE, Card::SUIT_SPADES);
    ASSERT_TRUE(rank_three_card >= min_card);
    ASSERT_FALSE(min_card >= rank_three_card);
}

TEST(test_operator_equal_to) {
    Card min_card(Card::RANK_TWO, Card::SUIT_SPADES);

    ASSERT_TRUE(min_card == min_card);

    Card club_card(Card::RANK_TWO, Card::SUIT_CLUBS);
    ASSERT_FALSE(min_card == club_card);

    Card rank_three_card(Card::RANK_THREE, Card::SUIT_SPADES);
    ASSERT_FALSE(min_card == rank_three_card);
}

TEST(test_operator_not_equal_to) {
    Card min_card(Card::RANK_TWO, Card::SUIT_SPADES);

    ASSERT_FALSE(min_card != min_card);

    Card club_card(Card::RANK_TWO, Card::SUIT_CLUBS);
    ASSERT_TRUE(min_card != club_card);

    Card rank_three_card(Card::RANK_THREE, Card::SUIT_SPADES);
    ASSERT_TRUE(min_card != rank_three_card);
}

TEST(test_Suit_next) {
    ASSERT_EQUAL(Card::SUIT_CLUBS, Suit_next(Card::SUIT_SPADES));
    ASSERT_NOT_EQUAL(Card::SUIT_SPADES, Suit_next(Card::SUIT_SPADES));
    ASSERT_NOT_EQUAL(Card::SUIT_HEARTS, Suit_next(Card::SUIT_SPADES));
    ASSERT_NOT_EQUAL(Card::SUIT_DIAMONDS, Suit_next(Card::SUIT_SPADES));  
}

TEST(test_print_card_to_stream) {
    Card min_card(Card::RANK_TWO, Card::SUIT_SPADES);
    ostringstream ss_output;
    string correct_output = "Two of Spades";

    ss_output << min_card;

    ASSERT_EQUAL(ss_output.str(), correct_output);
}

TEST(test_card_less_considers_trump) {
    Card right_bower(Card::RANK_JACK, Card::SUIT_DIAMONDS);    
    Card left_bower(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card trump_card(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card rank_ace_card(Card::RANK_ACE, Card::SUIT_SPADES);
    Card min_card(Card::RANK_TWO, Card::SUIT_SPADES);
    
    ASSERT_TRUE(Card_less(left_bower, right_bower, Card::SUIT_DIAMONDS));
    ASSERT_TRUE(Card_less(trump_card, left_bower, Card::SUIT_DIAMONDS));
    ASSERT_TRUE(Card_less(rank_ace_card, trump_card, Card::SUIT_DIAMONDS));
    ASSERT_TRUE(Card_less(min_card, rank_ace_card, Card::SUIT_DIAMONDS));

    ASSERT_FALSE(Card_less(right_bower, left_bower, Card::SUIT_DIAMONDS));
    ASSERT_FALSE(Card_less(left_bower, trump_card, Card::SUIT_DIAMONDS));
    ASSERT_FALSE(Card_less(trump_card, rank_ace_card, Card::SUIT_DIAMONDS));
    ASSERT_FALSE(Card_less(rank_ace_card, min_card, Card::SUIT_DIAMONDS));
}

TEST(test_card_less_considers_trump_and_led_suit) {
    Card led_card(Card::RANK_FOUR, Card::SUIT_CLUBS);
    Card trump_card(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card rank_ace_card(Card::RANK_ACE, Card::SUIT_SPADES);
    
    // Trump card tests
    Card right_bower(Card::RANK_JACK, Card::SUIT_DIAMONDS);    
    Card left_bower(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_TRUE(Card_less(left_bower, right_bower, led_card, Card::SUIT_DIAMONDS));
    ASSERT_TRUE(Card_less(trump_card, left_bower, led_card, Card::SUIT_DIAMONDS));
    ASSERT_TRUE(Card_less(rank_ace_card, trump_card, led_card, Card::SUIT_DIAMONDS));
    
    ASSERT_FALSE(Card_less(right_bower, left_bower, led_card, Card::SUIT_DIAMONDS));
    ASSERT_FALSE(Card_less(left_bower, trump_card, led_card, Card::SUIT_DIAMONDS));
    ASSERT_FALSE(Card_less(trump_card, rank_ace_card, led_card, Card::SUIT_DIAMONDS));
    
    // Led card tests
    Card max_led_card(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card min_led_card(Card::RANK_TWO, Card::SUIT_CLUBS);
    ASSERT_TRUE(Card_less(max_led_card, trump_card, led_card, Card::SUIT_DIAMONDS));
    ASSERT_TRUE(Card_less(min_led_card, max_led_card, led_card, Card::SUIT_DIAMONDS));
    ASSERT_TRUE(Card_less(rank_ace_card, min_led_card, led_card, Card::SUIT_DIAMONDS));
    
    ASSERT_FALSE(Card_less(trump_card, max_led_card, led_card, Card::SUIT_DIAMONDS));
    ASSERT_FALSE(Card_less(max_led_card, min_led_card, led_card, Card::SUIT_DIAMONDS));
    ASSERT_FALSE(Card_less(min_led_card, rank_ace_card, led_card, Card::SUIT_DIAMONDS));
    
    // Non-trump non-led card test
    Card min_card(Card::RANK_TWO, Card::SUIT_SPADES);
    ASSERT_TRUE(Card_less(min_card, rank_ace_card, led_card, Card::SUIT_DIAMONDS));
    ASSERT_FALSE(Card_less(rank_ace_card, min_card, led_card, Card::SUIT_DIAMONDS));
}


TEST_MAIN()
