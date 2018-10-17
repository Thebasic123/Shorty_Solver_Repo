#include "Helper.hpp"

//calculate the number of combinations give n and k
unsigned long long
calculate_num_combos(unsigned long long n, unsigned long long k) {
    if (k > n) {
        return 0;
    }
    unsigned long long r = 1;
    for (unsigned long long d = 1; d <= k; ++d) {
        r *= n--;
        r /= d;
    }
    return r;
}

void find_combo(std::vector<std::vector<int>>& result,std::vector<int>& combo,
	const std::vector<int>& remaining_cards,int offset,int k){
	if(k==0){
		result.push_back(combo);
		return;
	}
	for(int i=offset;i<=(int)remaining_cards.size()-k;++i){
		combo.push_back(remaining_cards[i]);
		find_combo(result,combo,remaining_cards,i+1,k-1);
		combo.pop_back();
	}
}

//get a vector of known cards and number of elements k
//return a vector of vectors of cards
std::vector<std::vector<int>> get_combos(const std::vector<int>& known_cards,int k){
	//get remaining cards
	std::vector<int> remaining_cards;
	std::set<int> s(known_cards.begin(),known_cards.end());
	for(int i=0;i<36;i++){
		//if i is not in set,then added element into reminding cards
		if(!s.count(i)){
			remaining_cards.push_back(i);
		}
	}
	//find all combos
	std::vector<std::vector<int>> result;
	//if not enough cards to form k element combo, return empyt vector
	if(remaining_cards.size() < (unsigned int)k){
		return result;
	}
	//pre reserve space for huge vector
	long long int pre_size = calculate_num_combos(remaining_cards.size(),k);
	result.reserve(pre_size);
	std::vector<int> curr_combo;
	find_combo(result,curr_combo,remaining_cards,0,k);
	return result;
}

//covert string representation to card index from 0-35
int covert_card_str_to_card_index(const std::string& card_str){
	// if string is not the correct length,
	//return invalid index
	if(card_str.length()!= 2){
		return -1;
	}
	int suit_index = -1;
	int rank_index = -1;
	//find suit
	if(card_str[1]=='c'){
		suit_index = 0;
	}else if(card_str[1]=='d'){
		suit_index = 1;
	}else if(card_str[1]=='h'){
		suit_index = 2;
	}else if(card_str[1]=='s'){
		suit_index = 3;
	}
	//find rank
	if(card_str[0]=='6'){
		rank_index = 0;
	}else if(card_str[0]=='7'){
		rank_index = 1;
	}else if(card_str[0]=='8'){
		rank_index = 2;
	}else if(card_str[0]=='9'){
		rank_index = 3;
	}else if(card_str[0]=='T'){
		rank_index = 4;
	}else if(card_str[0]=='J'){
		rank_index = 5;
	}else if(card_str[0]=='Q'){
		rank_index = 6;
	}else if(card_str[0]=='K'){
		rank_index = 7;
	}else if(card_str[0]=='A'){
		rank_index = 8;
	}

	//if card_str is invalid, return -1 for index
	if(suit_index == -1 || rank_index == -1){
		return -1;
	}
	int result = 9*suit_index + rank_index;
	return result;
}

//covert card index from 0-35 to string representation 
std::string covert_card_index_to_card_str(const int card_index){
	//make sure index is valid
	if(card_index > 35 || card_index < 0){
		return "NA";
	}
	int suit_index = card_index / 9;
	int rank_index = card_index % 9;
	std::string result;
	char first = 0;
	char second = 0;
	if(rank_index==0){
		first = '6';
	}else if(rank_index==1){
		first = '7';
	}else if(rank_index==2){
		first = '8';
	}else if(rank_index==3){
		first = '9';
	}else if(rank_index==4){
		first = 'T';
	}else if(rank_index==5){
		first = 'J';
	}else if(rank_index==6){
		first = 'Q';
	}else if(rank_index==7){
		first = 'K';
	}else if(rank_index==8){
		first = 'A';
	}
	result.push_back(first);
	if(suit_index==0){
		second = 'c';
	}else if(suit_index==1){
		second = 'd';
	}else if(suit_index==2){
		second = 'h';
	}else if(suit_index==3){
		second = 's';
	}
	result.push_back(second);
	return result;
}

//vector version of conversion
std::vector<int> covert_card_str_to_card_index_vector(const std::vector<std::string>& card_strs){
	std::vector<int> result;
	for(auto const& card_str:card_strs){
		result.push_back(covert_card_str_to_card_index(card_str));
	}
	return result;
}
std::vector<std::string> covert_card_index_to_card_str_vector(const std::vector<int>& card_indices){
	std::vector<std::string> result;
	for(auto const& card_index:card_indices){
		result.push_back((covert_card_index_to_card_str(card_index)));
	}
	return result;
}

//calculate equity of hands
std::vector<double> get_hands_equity
	(const std::vector<std::vector<int>>& hole_cards,
		const std::vector<int>& board,const std::vector<int>& deadCards){

	//vector of winning and drawing times of each hand
	std::vector<std::vector<int>> outputs(hole_cards.size(),std::vector<int>(2,0));
	std::vector<double> result(hole_cards.size(),0);
	//get a vector to count the winning times of each hand
	//since sometime hands can have same hand strength and all win
	//we use float to count the total number of winnings
	std::vector<float> winning_counts(hole_cards.size(),0);
	//add all known cards together
	std::vector<int> known_cards = board;
	known_cards.insert(known_cards.end(),deadCards.begin(),deadCards.end());
	//create a vector of Hand objects for hand strength
	std::vector<Hand> input_hands;
	//add cards in hand into known_cards vector
	for(const auto& hole_card : hole_cards){
		known_cards.insert(known_cards.end(),hole_card.begin(),hole_card.end());
		input_hands.push_back(Hand(hole_card));
	}
	//if board is not empty,add board cards to hands
	if(board.size() != 0){
		for(unsigned int i=0;i<input_hands.size();i++){
			input_hands[i].add_cards(board);
		}
	}
	std::vector<std::vector<int>> board_combos = get_combos(known_cards,5-board.size());
	unsigned int num_combos = board_combos.size();
	//find best hand for each combo
	//and update winning_counts
	for(const auto& board_combo : board_combos){
		//update hand strength
		std::vector<unsigned int> hand_strength_vec(input_hands.size(),0);
		for(unsigned int i=0;i<input_hands.size();i++){
			input_hands[i].add_cards(board_combo);
			hand_strength_vec[i] = input_hands[i].get_hand_strength();
			input_hands[i].remove_cards(board_combo);
		}
		std::vector<int> max_element_indices;
		unsigned int curr_max = 0;
		for(unsigned int i=0;i<hand_strength_vec.size();i++){
			if(curr_max==hand_strength_vec[i]){
				max_element_indices.push_back(i);
			}else if(curr_max < hand_strength_vec[i]){
				max_element_indices.clear();
				max_element_indices.push_back(i);
				curr_max = hand_strength_vec[i];
			}else{
				//if curr_max is larger than i hand strength do nothing
			}
		}
		//increment output vector
		if(max_element_indices.size()==1){
			outputs[max_element_indices[0]][0]++;
		}else{
			for(unsigned int i=0;i<max_element_indices.size();i++){
				outputs[max_element_indices[i]][1]++;
			}
		}

		//increment winning counts properly 
		float increment = (float)1/(float)max_element_indices.size();
		for(unsigned int i=0;i<max_element_indices.size();i++){
			winning_counts[max_element_indices[i]] += increment;
		}
	}
	for(unsigned int i=0;i<winning_counts.size();i++){
		result[i] = winning_counts[i]/(double)num_combos;
	}
	//print out outputs vector
	for(unsigned int i=0;i<hole_cards.size();i++){
		std::cout<<"Hand "<<i<<" wins:"<<outputs[i][0]<<" times"
		<<" and draws"<<outputs[i][1]<<" times"<<std::endl;
	}
	return result;
}
std::vector<std::string> splitString(const std::string& inputStr,const std::string& delimiter=" "){
    std::vector<std::string> result;
    if(inputStr.length()==0){
        return result;
    }
    size_t pos = 0;
    std::string token;
    std::string s = inputStr;
    while((pos = s.find(delimiter))!= std::string::npos){
        token = s.substr(0,pos);
        result.push_back(token);
        s.erase(0,pos+delimiter.length());
    }
    return result;
}    