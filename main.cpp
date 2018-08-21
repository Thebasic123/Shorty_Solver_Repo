#include "Hand.hpp"
#include "Helper.hpp"
#include "Test.hpp"

int main(int argc, char *argv[]){
	//test stright combos
	//test_all_straights();
	// std::vector<unsigned int> test_equity = test_all_five_cards_combos();
	// for(unsigned int i=0;i<test_equity.size();i++){
	// 	std::cout<<test_equity[i]<<std::endl;
	// }

	std::string feature_str(argv[1]);
	if(feature_str=="handequity"){
		int num_hands = atoi(argv[2]);
		bool has_board = false;
		bool has_dead_cards = false;
		if(atoi(argv[3])){
			has_board = true;
		}
		if(atoi(argv[4])){
			has_dead_cards = true;
		}
		//get hold cards set up
		std::vector<std::string> input_cards;
		std::vector<std::vector<int>> hole_cards;
		for(int i=0;i<num_hands;i++){
			int temp_card_index = 5+i;
			std::string temp_cards(argv[temp_card_index]);
			input_cards.push_back(temp_cards.substr(0,2));
			input_cards.push_back(temp_cards.substr(2,2));
			hole_cards.push_back(covert_card_str_to_card_index_vector(input_cards));
			input_cards.clear();
		}
		std::vector<int> board;
		std::vector<int> deadCards;
		if(has_board){
			std::string board_str(argv[4+num_hands+1]);
			for(unsigned int i=0;i<board_str.length();i=i+2){
				board.push_back(covert_card_str_to_card_index(board_str.substr(i,2)));
			}

		}
		if(has_dead_cards){
			int dead_index = 4+num_hands+1;
			if(has_board){
				dead_index++;
			}
			std::string dead_str(argv[dead_index]);
			for(unsigned int i=0;i<dead_str.length();i=i+2){
				deadCards.push_back(covert_card_str_to_card_index(dead_str.substr(i,2)));
			}
		}
		std::vector<double> equity_result;
		equity_result = std::move(get_hands_equity(hole_cards,board,deadCards));
		for(unsigned int i=0;i<equity_result.size();i++){
			std::cout<<equity_result[i]<<std::endl;
		}
	}else if(feature_str=="test7"){
		std::vector<unsigned int> test_equity = test_all_seven_cards_combos();
		for(unsigned int i=0;i<test_equity.size();i++){
			std::cout<<test_equity[i]<<std::endl;
		}
	}else if(feature_str=="test5"){
		std::vector<unsigned int> test_equity = test_all_five_cards_combos();
		for(unsigned int i=0;i<test_equity.size();i++){
			std::cout<<test_equity[i]<<std::endl;
		}
	}
	return 0;
}