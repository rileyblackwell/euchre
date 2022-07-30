#include <iostream>
#include <string>
#include <cassert>
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
static void check_rank_is_valid(const string &rank) {
    assert(rank == "Two" || rank == "Three" || rank == "Four" || rank == "Five"
           || rank == "Six" || rank == "Seven" || rank == "Eight" || rank == "Nine"  
           || rank == "Ten" || rank == "Jack" || rank == "Queen" || rank == "King"
           || rank == "Ace");
}

static void check_suit_is_valid(const string &suit) {
    assert(suit == "Spades" || suit == "Hearts" || suit == "Clubs" || suit == "Diamonds");
}

//EFFECTS Initializes Card to the Two of Spades
Card::Card() : rank(RANK_TWO), suit(SUIT_SPADES) {}

//REQUIRES rank is one of "Two", "Three", "Four", "Five", "Six", "Seven",
//  "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"
//  suit is one of "Spades", "Hearts", "Clubs", "Diamonds"
//EFFECTS Initializes Card to specified rank and suit
Card::Card(const string &rank_in, const string &suit_in) 
   : rank(rank_in), suit(suit_in) {
    check_rank_is_valid(Card::get_rank());
    check_suit_is_valid(Card::get_suit());
}

//EFFECTS Returns the rank
string Card::get_rank() const {return rank;}

//EFFECTS Returns the suit.  Does not consider trump.
string Card::get_suit() const {return suit;}

//REQUIRES trump is a valid suit
//EFFECTS Returns the suit
//HINT: the left bower is the trump suit!
string Card::get_suit(const string &trump) const {
    check_suit_is_valid(trump);
    if (Card::is_left_bower(trump)) {
        return Suit_next(Card::get_suit());
    } 
    return Card::get_suit();       
}

//EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
bool Card::is_face() const {
    return Card::get_rank() == Card::RANK_JACK || Card::get_rank() == Card::RANK_QUEEN
           || Card::get_rank() == Card::RANK_KING || Card::get_rank() == Card::RANK_ACE;                 
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the trump suit
bool Card::is_right_bower(const string &trump) const {
    check_suit_is_valid(trump);
    if (Card::get_suit() == trump) {
        return Card::get_rank() == Card::RANK_JACK; 
    }
    return false;  
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the next suit
bool Card::is_left_bower(const string &trump) const {
    check_suit_is_valid(trump);
    if (Suit_next(Card::get_suit()) == trump) {
        return Card::get_rank() == Card::RANK_JACK;    
    }
    return false;          
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if the card is a trump card.  All cards of the trump
// suit are trump cards.  The left bower is also a trump card.
bool Card::is_trump(const string &trump) const {
    check_suit_is_valid(trump);
    return Card::get_suit(trump) == trump; 
}

//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card &lhs, const Card &rhs) {
    for (int i = 0; i < NUM_RANKS; ++i) {
        // Decides ties in rank by using suit.
        if (RANK_NAMES_BY_WEIGHT[i] == lhs.get_rank() && RANK_NAMES_BY_WEIGHT[i] == rhs.get_rank()) { 
            for (int j = 0; j < NUM_SUITS; ++j) {
                if (SUIT_NAMES_BY_WEIGHT[j] == lhs.get_suit() && SUIT_NAMES_BY_WEIGHT[j] == rhs.get_suit()) {
                    return false;
                }
                if (SUIT_NAMES_BY_WEIGHT[j] == lhs.get_suit()) {
                    return true;    
                }else if (SUIT_NAMES_BY_WEIGHT[j] == rhs.get_suit()) {
                    return false;
                }
            }
        }
        if (RANK_NAMES_BY_WEIGHT[i] == lhs.get_rank()) {
            return true;
        }else if (RANK_NAMES_BY_WEIGHT[i] == rhs.get_rank()) {
            return false;
        }  
    }
    return false;    
}

//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator<=(const Card &lhs, const Card &rhs) {
    return lhs < rhs || lhs == rhs;        
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs) {
    return !(lhs <= rhs);    
}

//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator>=(const Card &lhs, const Card &rhs) {
    return !(lhs < rhs);    
}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs) {
    return lhs.get_rank() == rhs.get_rank() && lhs.get_suit() == rhs.get_suit();              
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs) {
    return !(lhs == rhs);    
}

//REQUIRES suit is a valid suit
//EFFECTS returns the next suit, which is the suit of the same color
string Suit_next(const string &suit) {
    check_suit_is_valid(suit);
    if (suit == Card::SUIT_SPADES) {
        return Card::SUIT_CLUBS;
    }else if (suit ==  Card::SUIT_CLUBS) {
        return Card::SUIT_SPADES;    
    }else if (suit == Card::SUIT_DIAMONDS) {
        return Card::SUIT_HEARTS;
    } 
    // suit == Card::SUIT_HEARTS
    return Card::SUIT_DIAMONDS;
}

//EFFECTS Prints Card to stream, for example "Two of Spades"
ostream & operator<<(ostream &os, const Card &card) {
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}

// EFFECTS Returns true if a or b is a bower.
static bool is_bower(const Card &a, const Card &b, const string &trump) {
    return a.is_right_bower(trump) || a.is_left_bower(trump) || b.is_right_bower(trump) || b.is_left_bower(trump);                       
}

// EFFECTS Returns true if a is less than b.
static bool compare_with_bowers(const Card &a, const Card &b, const string &trump) {
    if (b.is_right_bower(trump) || (b.is_left_bower(trump) && !(a.is_right_bower(trump)))) {
        return true;
    }
    return false;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const string &trump) {
    check_suit_is_valid(trump);
    // Check if 2 cards are the same card.
    if (a == b) {
        return false;
    }
    
    if (a.is_trump(trump) && b.is_trump(trump)) {
        if (is_bower(a, b, trump)) {
            return compare_with_bowers(a, b, trump);
        }
        return a < b;     
    }
    if (a.is_trump(trump)) {
        return false;
    }else if (b.is_trump(trump)) {
        return true;
    }
    return a < b;    
}

// EFFECTS Returns true if card is the led suit.
static bool is_led(const Card &card, const Card &led_card, const string &trump) {
    return card.get_suit(trump) == led_card.get_suit(trump);
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const string &trump) {
    check_suit_is_valid(trump);
    // Check if 2 cards are the same card.
    if (a == b) {
        return false;
    }

    if (trump == led_card.get_suit(trump) || a.is_trump(trump) || b.is_trump(trump)) {
        return Card_less(a, b, trump);
    }

    if (is_led(a, led_card, trump) && is_led(b, led_card, trump)) {
        return a < b;
    }else if (is_led(a, led_card, trump)) {
        return false;
    }else if (is_led(b, led_card, trump)) {
        return true;
    }
    return a < b;
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
