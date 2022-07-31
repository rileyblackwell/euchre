#include <iostream>
#include <cassert>
#include <array>
#include "Pack.h"

using namespace std;

// EFFECTS: Initializes the Pack to be in the following standard order:
//          the cards of the lowest suit arranged from lowest rank to
//          highest rank, followed by the cards of the next lowest suit
//          in order from lowest to highest rank, and so on.
// NOTE: The standard order is the same as that in pack.in.
// NOTE: Do NOT use pack.in in your implementation of this function
Pack::Pack() {
  next = 0;
  int k = 0;
  for (int i = 0; i < NUM_SUITS; ++i) {
    for (int j = 0; j < NUM_RANKS; ++j) {
      Card card(RANK_NAMES_BY_WEIGHT[j], SUIT_NAMES_BY_WEIGHT[i]);
      if (card.get_rank() == Card::RANK_NINE || card.get_rank() == Card::RANK_TEN 
          || card.is_face()) {
            cards[k++] = card;
      }  
    }
  }  
}

// REQUIRES: pack_input contains a representation of a Pack in the
//           format required by the project specification
// MODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
Pack::Pack(istream& pack_input) {
  next = 0;
  string rank;
  string suit;
  string of;
  for (int i = 0; i < PACK_SIZE; ++i) {
    pack_input >> rank >> of >> suit;
    Card card(rank, suit);
    cards[i] = card;
  }
}

// REQUIRES: cards remain in the Pack
// EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one() {
  assert(!(Pack::empty()));
  return cards[next++];
}

// EFFECTS: Resets next index to first card in the Pack
void Pack::reset() {
  next = 0;
}

// EFFECTS: Shuffles the Pack and resets the next index. This
//          performs an in shuffle seven times. See
//          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle() {
  array<Card, PACK_SIZE> temp_cards;
  const int half_pack_size = PACK_SIZE / 2;
  for (int i = 0; i < 7; ++i) {
    for (int j = 0; j < half_pack_size; ++j) {
      temp_cards[j * 2] = cards[half_pack_size + j];
      temp_cards[j * 2 + 1] = cards[j];
    }
    cards = temp_cards; 
  }  
  Pack::reset();
}

// EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const {
  return next == PACK_SIZE;
}
