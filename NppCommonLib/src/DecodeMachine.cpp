#include "DecodeMachine.h"

DecodeMachine::DecodeMachine() {

}
DecodeMachine::~DecodeMachine() {

}

bool DecodeMachine::addPattern(string patt, std::vector<DecodeFunction>& cbs)
{
	DecodingData data(patt, cbs);
	mItems.push_back(data);
}

bool DecodeMachine::addPattern(DecodingData& item)
{
	
}


string DecodeMachine::decode(string str) {

}