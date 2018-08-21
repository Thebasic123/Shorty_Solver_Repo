#ifndef HELPER_H
#define HELPER_H

#include <vector>
#include <set>
#include <iostream>
#include <utility>
#include <string>
#include <cmath>
#include <bitset>
#include <cstdlib>
#include <algorithm>
#include <iterator>
#include "Hand.hpp"

//calculate the number of combinations give n and k
unsigned long long
calculate_num_combos(unsigned long long n, unsigned long long k);

void find_combo(std::vector<std::vector<int>>& result,std::vector<int>& combo,
	const std::vector<int>& remaining_cards,int offset,int k);

//get a vector of known cards and number of elements k
//return a vector of vectors of cards
std::vector<std::vector<int>> get_combos(const std::vector<int>& known_cards,int k);


//covert string representation to card index from 0-35
int covert_card_str_to_card_index(const std::string& card_str);
//covert card index from 0-35 to string representation 
std::string covert_card_index_to_card_str(const int card_index);
//vector version
std::vector<int> covert_card_str_to_card_index_vector(const std::vector<std::string>& card_strs);
std::vector<std::string> covert_card_index_to_card_str_vector(const std::vector<int>& card_indices);
//calculate equity of hands
std::vector<double> get_hands_equity
	(const std::vector<std::vector<int>>& hole_cards,
		const std::vector<int>& board,const std::vector<int>& deadCards);
	
#endif