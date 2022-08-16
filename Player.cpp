#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <algorithm>
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
      for (int i = 0; i < static_cast<int>(hand.size()); ++i) {
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
    for (int i = 0; i < static_cast<int>(hand.size()); ++i) {
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
    for (int i = 0; i < static_cast<int>(hand.size()); ++i) {
      Card card = hand[i];
      if (Card_less(card, min_card, upcard.get_suit())) {
        Card temp_min_card = card;
        hand[i] = min_card;
        min_card = temp_min_card;  
      }
    }
  }

  static bool is_hand_all_trump(const vector<Card> &hand, const string &trump) {
    for (int i = 0; i < static_cast<int>(hand.size()); ++i) {
      Card card = hand[i];
      if (!card.is_trump(trump)) {
        return false;
      }  
    }
    return true;  
  }
  
  //REQUIRES Player has at least one card, trump is a valid suit
  //EFFECTS  Leads one Card from Player's hand according to their strategy
  //  "Lead" means to play the first Card in a trick.  The card
  //  is removed the player's hand.
  Card lead_card(const string &trump) override {
    check_suit_is_valid(trump);
    assert(!hand.empty());
    
    if (!is_hand_all_trump(hand, trump)) { 
      Card max_card = hand[0]; 
      int max_index = 0;
      for (int i = 0; i < static_cast<int>(hand.size()); ++i) { 
        Card card = hand[i];
        if (!card.is_trump(trump)) {
          // If the starting max_card is a trump card then a non-trump card
          // will be assigned as the max_card.
          if (max_card.is_trump(trump)) {
            max_card = card;
            max_index = i;
          } 
          if (max_card < card) {
            max_card = card;
            max_index = i;  
          }  
        }
      }
      // Returns and removes max non-trump card from hand.
      hand[max_index] = hand[hand.size() - 1];
      hand.pop_back();
      return max_card;  
    }

    // If entire hand is trump cards.
    Card max_trump_card = hand[0];
    int max_trump_index = 0;
    for (int i = 0; i < static_cast<int>(hand.size()); ++i) {
      Card card = hand[i];
      if (Card_less(max_trump_card, card, trump)) {
        max_trump_card = card;
        max_trump_index = i;
      }
    } 
    // Returns and removes max trump card from hand.
    hand[max_trump_index] = hand[hand.size() - 1];
    hand.pop_back();
    return max_trump_card;    
  }

  // EFFECTS Returns true if card is the led suit.
  static bool is_led_suit(const Card &card, const Card &led_card, const string &trump) {
    return card.get_suit(trump) == led_card.get_suit(trump);
  }
  
  // EFFECTS Returns the index in hand of a card that can follow suit.
  // If no card can follow suit returns -1.
  static int get_led_suit_index(const vector<Card> &hand, const Card &led_card, 
                          const string &trump) {
    for (int i = 0; i < static_cast<int>(hand.size()); ++i) {
      Card card = hand[i];
      if (is_led_suit(card, led_card, trump)) {
        return i;
      }
    }
    return -1;                            
  }
  
  //REQUIRES Player has at least one card, trump is a valid suit
  //EFFECTS  Plays one Card from Player's hand according to their strategy.
  //  The card is removed from the player's hand.
  Card play_card(const Card &led_card, const string &trump) override {
    check_suit_is_valid(trump);
    assert(!hand.empty());
    
    const int led_suit_index = get_led_suit_index(hand, led_card, trump);
    if (!(led_suit_index == -1)) {
      Card max_card = hand[led_suit_index]; 
      int max_index = led_suit_index;
      for (int i = 0; i < static_cast<int>(hand.size()); ++i) {
        Card card = hand[i];
        if (is_led_suit(card, led_card, trump)) {
          if (Card_less(max_card, card, trump)) {
            max_card = card;
            max_index = i;
          }
        }
      }
      // Returns the max card in hand that follows suit.
      hand[max_index] = hand[hand.size() - 1];
      hand.pop_back();
      return max_card; 
    }

    Card min_card = hand[0];
    int min_index = 0;
    for (int i = 0; i < static_cast<int>(hand.size()); ++i) {
      Card card = hand[i];
      if (Card_less(card, min_card, led_card, trump)) {
        min_card = card;
        min_index = i;
      }
    }
    // Returns the min card in hand if suit can't be followed.
    hand[min_index] = hand[hand.size() - 1];
    hand.pop_back();
    return min_card;
  }
  
  static void check_suit_is_valid(const string &suit) {
    assert(suit == Card::SUIT_SPADES || suit == Card::SUIT_HEARTS || suit == Card::SUIT_CLUBS || suit == Card::SUIT_DIAMONDS);
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
    assert(MAX_HAND_SIZE > static_cast<int>(hand.size()));
    hand.push_back(c);
    // Sorts hand after adding a card.
    sort(hand.begin(), hand.end());
  }

  //REQUIRES round is 1 or 2
  //MODIFIES order_up_suit
  //EFFECTS If Player wishes to order up a trump suit then return true and
  //  change order_up_suit to desired suit.  If Player wishes to pass, then do
  //  not modify order_up_suit and return false.
  bool make_trump(const Card &upcard, bool is_dealer,
                  int round, string &order_up_suit) const override {
    assert(round == 1 || round == 2);
    
    print_hand(hand, get_name());
    string suit;
    cout << "Human player " << get_name() << ", please enter a suit, or \"pass\":" << endl;
    cin >> suit;
    
    if (suit == "pass") {
      return false;
    }
    order_up_suit = suit;
    return true; 
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Player adds one card to hand and removes one card from hand.
  void add_and_discard(const Card &upcard) override {
    assert(!hand.empty());
    
    print_hand(hand, get_name());
    string card;
    cout << "Discard upcard: [-1] " << endl << "Human player" << get_name() 
         << ", please select a card to discard:" << endl;
    cin >> card;
    const int card_num = stoi(card);
    
    if (card_num != -1) {
      hand[card_num] = upcard;
      // Sorts hand after adding a card.
      sort(hand.begin(), hand.end());
    } 
  }

  //REQUIRES Player has at least one card, trump is a valid suit
  //EFFECTS  Leads one Card from Player's hand according to their strategy
  //  "Lead" means to play the first Card in a trick.  The card
  //  is removed the player's hand.
  Card lead_card(const string &trump) override {
    check_suit_is_valid(trump);
    assert(!hand.empty());
    
    print_hand(hand, get_name());
    string card;
    cout << "Human player " << get_name() << ", please select a card:" << endl;
    cin >> card;
    const int card_num = stoi(card);
    
    Card play_card = hand[card_num];
    hand[card_num] = hand[hand.size() - 1];
    hand.pop_back();
    // Sorts hand after removing a card.
    sort(hand.begin(), hand.end()); 
    return play_card;
  }

  //REQUIRES Player has at least one card, trump is a valid suit
  //EFFECTS  Plays one Card from Player's hand according to their strategy.
  //  The card is removed from the player's hand.
  Card play_card(const Card &led_card, const string &trump) override {
    check_suit_is_valid(trump);
    assert(!hand.empty());
    
    print_hand(hand, get_name());
    string card;
    cout << "Human player " << get_name() << ", please select a card:" << endl;
    cin >> card;
    const int card_num = stoi(card);
    
    Card play_card = hand[card_num];
    hand[card_num] = hand[hand.size() - 1];
    hand.pop_back();
    // Sorts hand after removing a card.
    sort(hand.begin(), hand.end()); 
    return play_card;
  }

  static void print_hand(const vector<Card> &hand, const string &name) {
    for (int i = 0; i < static_cast<int>(hand.size()); ++i) {
      cout << "Human player " << name << "'s hand: [" << i << "] " << hand[i] << endl;  
    }  
  }

  static void check_suit_is_valid(const string &suit) {
    assert(suit == Card::SUIT_SPADES || suit == Card::SUIT_HEARTS || suit == Card::SUIT_CLUBS || suit == Card::SUIT_DIAMONDS);
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

