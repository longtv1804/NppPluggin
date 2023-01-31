#pragma once
#include <string>
#include <regex>
#include <vector>
#include <map>
#include <functional>
using std::string;

/*
 * including information of added pattern.
 */
class PatternInfor {
public:
	string mPattern;
	uint32_t mId;
	uint8_t mMappingSize;
	std::function<string(std::vector<string>)> mCallback;

	PatternInfor();
	~PatternInfor();
	PatternInfor(const string pattern, const uint32_t id, const uint8_t size, 
				 const std::function<string(std::vector<string>)> cb);
};

/*
 * using matching multi patterns to find out given string matches with which pattern.
 */
class MappingMachine {
private:
	uint32_t mTopId;
	std::map<uint32_t, PatternInfor*> mMappingInfos;	// <int, int> ~ <index, id>

	bool mNeedInitilize;
	std::regex *mRg;
	std::smatch mSm;

	bool initMappingMachine();

public:
	MappingMachine();
	~MappingMachine();

	bool addPattern(const string patt, const std::function<string(std::vector<string>)> cb);
	bool addPattern(const string patt);

	// return id of first matched pattern
	int match(string str);

	// search multily matched pattern.
	int search(string str);

	PatternInfor* getMatchedInfor();
	PatternInfor* getPatternInfor(const uint32_t id);
};
