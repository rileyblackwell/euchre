#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include "Player.h"

using namespace std;


class SimplePlayer: public Player {
 public:
  SimplePlayer() : name("default_simple_player") {}
  
  SimplePlayer(const string &player_name) : name(player_name) {}  
  
  //EFFECTS returns player's name
  const string & get_name() const override {return name;}

  //REQUIRES player has less than MAX_HAND_SIZE cards
  //EFFECTS  adds Card c to Player's hand
  void add_card(const Card &c) override {
    assert(MAX_HAND_SIZE > static_cast<int>(hand.size()));
    hand.push_back(c);
  }

  //REQUIRES round is 1 or 2
  //MODIFIES order_up_suit
  //EFFECTS If Player wishes to order up a trump suit then return true and
  //  change order_up_suit to desired suit.  If Player wishes to pass, then do
  //  not modify order_up_suit and return false.
  bool make_trump(const Card &upcard, bool is_dealer,
                  int round, string &order_up_suit) const override {
    assert(round == 1 || round == 2);
    if (round == 1) {
      int trump_face_cards = 0;
      for (int i = 0; i < MAX_HAND_SIZE; ++i) {
        Card card = hand[i];
        if (card.is_trump(upcard.get_suit()) && card.is_face()) {
          trump_face_cards += 1;
        }
      }
      if (trump_face_cards >= 2) {
        order_up_suit = upcard.get_suit();
        return true;
      } 
      return false;
    }

    // round == 2
    if (is_dealer) {
      order_up_suit = Suit_next(upcard.get_suit());
      return true;
    }
    int trump_face_cards = 0;
    for (int i = 0; i < MAX_HAND_SIZE; ++i) {
      Card card = hand[i];
      if (card.is_trump(Suit_next(upcard.get_suit())) && card.is_face()) {
        trump_face_cards += 1;
      }
    }
    if (trump_face_cards >= 1) {
      order_up_suit = Suit_next(upcard.get_suit());
      return true;
    }
    return false;
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Player adds one card to hand and removes one card from hand.
  void add_and_discard(const Card &upcard) override {
    assert(!hand.empty());
    Card min_card = upcard;
    for (int i = 0; i < MAX_HAND_SIZE; ++i) {
      Card card = hand[i];
      if (card < min_card) {
        Card temp_min_card = card;
        hand[i] = min_card;
        min_card = temp_min_card;  
      }
    }
  }

  //REQUIRES Player has at least one card, trump is a valid suit
  //EFFECTS  Leads one Card from Player's hand according to their strategy
  //  "Lead" means to play the first Card in a trick.  The card
  //  is removed the player's hand.
  Card lead_card(const string &trump) override {
    assert(!hand.empty());
    assert(trump == Card::SUIT_SPADES || trump == Card::SUIT_HEARTS 
           || trump == Card::SUIT_CLUBS || trump == Card::SUIT_DIAMONDS);
    // Returns min non-trump card from hand
    Card min_card = hand[0];
    int min_index = 0;
    for (int i = 0; i < MAX_HAND_SIZE; ++i) { 
      Card card = hand[i];
      if (card < min_card) {
        min_card = card;
        min_index = i;
      }
    }  
    if (!min_card.is_trump(trump)) {
      const int end_index = static_cast<int>(hand.size() - 1); 
      hand[min_index] = hand[end_index];
      hand.pop_back();
      return min_card;  
    }
    // Returns max trump card if entire hand is trump cards.
    Card max_card = hand[0];
    int max_index = 0;
    for (int i = 0; i < MAX_HAND_SIZE; ++i) {
      Card card = hand[i];
      if (card > max_card) {
        max_card = card;
        max_index = i;
      }
    } 
    const int end_index = static_cast<int>(hand.size() - 1); 
    hand[max_index] = hand[end_index];
    hand.pop_back();
    return max_card;    
  }

  //REQUIRES Player has at least one card, trump is a valid suit
  //EFFECTS  Plays one Card from Player's hand according to their strategy.
  //  The card is removed from the player's hand.
  Card play_card(const Card &led_card, const string &trump) override {
    assert(false);
  }

  private:
    string name;
    vector<Card> hand;
};

class HumanPlayer: public Player {
 public:
  HumanPlayer() : name("default_human_player") {}
  
  HumanPlayer(const string &player_name) : name(player_name) {}  
  
  //EFFECTS returns player's name
  const string & get_name() const override {return name;}

  //REQUIRES player has less than MAX_HAND_SIZE cards
  //EFFECTS  adds Card c to Player's hand
  void add_card(const Card &c) override {
    assert(false);
  }

  //REQUIRES round is 1 or 2
  //MODIFIES order_up_suit
  //EFFECTS If Player wishes to order up a trump suit then return true and
  //  change order_up_suit to desired suit.  If Player wishes to pass, then do
  //  not modify order_up_suit and return false.
  bool make_trump(const Card &upcard, bool is_dealer,
                          int round, string &order_up_suit) const override {
    assert(false);
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Player adds one card to hand and removes one card from hand.
  void add_and_discard(const Card &upcard) override {
    assert(false);
  }

  //REQUIRES Player has at least one card, trump is a valid suit
  //EFFECTS  Leads one Card from Player's hand according to their strategy
  //  "Lead" means to play the first Card in a trick.  The card
  //  is removed the player's hand.
  Card lead_card(const string &trump) override {
    assert(false);
  }

  //REQUIRES Player has at least one card, trump is a valid suit
  //EFFECTS  Plays one Card from Player's hand according to their strategy.
  //  The card is removed from the player's hand.
  Card play_card(const Card &led_card, const string &trump) override {
    assert(false);
  }

  private:
    string name;
    vector<Card> hand;
};

//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each Player* after the game is over
Player * Player_factory(const string &name, const string &strategy) {
  if (strategy == "Simple") {
    return new SimplePlayer(name);
  } else if (strategy == "Human") {
    return new HumanPlayer(name);
  }
  assert(false);
  return nullptr;
}

//EFFECTS: Prints player's name to os
ostream & operator<<(ostream &os, const Player &p) {
  os << p.get_name();
  return os;
}