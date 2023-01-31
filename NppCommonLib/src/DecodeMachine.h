#pragma once
#include <string>
#include <functional>
#include <vector>
using std::string;
#include <regex>

#include "MappingMachine.h"

typedef std::function<string(int)> DecodeFunction;

class DecodingData {
public:
	string mPattern = "";

	std::vector<DecodeFunction>& mCallBacks;

	DecodingData(string patt, std::vector<DecodeFunction>& cbs) 
	: mCallBacks(cbs), mPattern(patt) {
	}

	void addCallback(DecodeFunction cb) {
		mCallBacks.push_back(cb);
	}
};

class DecodeMachine {
	MappingMachine mMapMachine;
	std::vector<DecodingData&> mItems;

public:
	DecodeMachine();
	~DecodeMachine();

	bool addPattern(string patt, std::vector<DecodeFunction>& cbs);
	bool addPattern(DecodingData& item);

	string decode(string str);
};