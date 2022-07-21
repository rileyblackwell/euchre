#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
// add any necessary #include or using directives here
using namespace std; 

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

// add your code below
//EFFECTS Initializes Card to the Two of Spades
Card::Card() {
    assert(false);
}

//REQUIRES rank is one of "Two", "Three", "Four", "Five", "Six", "Seven",
//  "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"
//  suit is one of "Spades", "Hearts", "Clubs", "Diamonds"
//EFFECTS Initializes Card to specified rank and suit
Card::Card(const string &rank_in, const string &suit_in) {
   assert(false);
}

//EFFECTS Returns the rank
string Card::get_rank() const {
    assert(false);    
}

//EFFECTS Returns the suit.  Does not consider trump.
string Card::get_suit() const {
    assert(false);    
}

//REQUIRES trump is a valid suit
//EFFECTS Returns the suit
//HINT: the left bower is the trump suit!
string Card::get_suit(const string &trump) const {
    assert(false);    
}

//EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
bool Card::is_face() const {
    assert(false);    
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the trump suit
bool Card::is_right_bower(const string &trump) const {
    assert(false);    
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the next suit
bool Card::is_left_bower(const string &trump) const {
    assert(false);    
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if the card is a trump card.  All cards of the trump
// suit are trump cards.  The left bower is also a trump card.
bool Card::is_trump(const string &trump) const {
    assert(false);    
}

//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card &lhs, const Card &rhs) {
    assert(false);    
}

//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator<=(const Card &lhs, const Card &rhs) {
    assert(false);    
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs) {
    assert(false);    
}

//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator>=(const Card &lhs, const Card &rhs) {
    assert(false);    
}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs) {
    assert(false);    
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs) {
    assert(false);    
}

//REQUIRES suit is a valid suit
//EFFECTS returns the next suit, which is the suit of the same color
string Suit_next(const string &suit) {
    assert(false);    
}

//EFFECTS Prints Card to stream, for example "Two of Spades"
ostream & operator<<(ostream &os, const Card &card) {
    assert(false);    
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const string &trump) {
    assert(false);    
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const string &trump) {
    assert(false);    
}

// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec (see the appendices) before implementing
// the following operator overload functions:
//   operator<<
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=
