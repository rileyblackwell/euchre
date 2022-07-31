#include "Pack.h"
#include "unit_test_framework.h"
#include <iostream>
#include <fstream>

using namespace std;


TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_NINE, first.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, first.get_suit());
}

// Add more tests here
TEST(test_pack_ctor) {
    string filename = "pack.in"; 
    ifstream pack_fin;
    pack_fin.open(filename);
    Pack pack(pack_fin);
    
    Card first = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_NINE, first.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, first.get_suit());
}

TEST(test_pack_deal_one) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_NINE, first.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, first.get_suit());

    Card second = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_TEN, second.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, second.get_suit());    
}

TEST(test_pack_reset) {
    Pack pack;
    Card first = pack.deal_one();
    pack.reset();
    Card first_after_reset = pack.deal_one();
    ASSERT_TRUE(first == first_after_reset);    
}

TEST(test_pack_shuffle) {
    Pack pack;
    Card first = pack.deal_one();
    Card second = pack.deal_one();
    Card third = pack.deal_one();
    while (!pack.empty()) {
        pack.deal_one();
    }
    
    pack.shuffle();
    ASSERT_TRUE(!pack.empty());
    
    Card first_shuffled = pack.deal_one();
    Card second_shuffled = pack.deal_one();
    Card third_shuffled = pack.deal_one();  
    ASSERT_TRUE(first != first_shuffled);
    ASSERT_TRUE(second != second_shuffled);
    ASSERT_TRUE(third != third_shuffled);
    // third card in the deck should be the orignal first card for a 7x in shuffle.
    ASSERT_TRUE(third_shuffled == first);
}

TEST(test_pack_empty) {
    Pack pack;
    int i = 0;
    while (i < 24) {
        ASSERT_FALSE(pack.empty());
        pack.deal_one();
        i++;
    }
    ASSERT_TRUE(pack.empty());
}


TEST_MAIN() 