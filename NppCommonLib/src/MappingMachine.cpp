#pragma once
#include "MappingMachine.h"

#pragma region PatternInfor

PatternInfor::PatternInfor() :
	mPattern(""),
	mId(0),
	mMappingSize(0),
	mCallback(NULL)
{

}

PatternInfor::~PatternInfor()
{

}
PatternInfor::PatternInfor(const string pattern, const uint32_t id, const uint8_t size,
	const std::function<string(std::vector<string>)> cb) :
	mPattern(pattern),
	mId(id),
	mMappingSize(size),
	mCallback(cb)
{

}
#pragma endregion


#pragma region MappingMachine
/*
 *	MappingMachine
 */
MappingMachine::MappingMachine() :
	mTopId(2),
	mNeedInitilize(false),
	mRg(NULL),
	mSm(),
	mMappingInfos() 
{

}

MappingMachine::~MappingMachine() {
	if (mRg) delete mRg;
	if (mMappingInfos.size() > 0) {
		std::map<uint32_t, PatternInfor*>::iterator it = mMappingInfos.begin();
		while (it != mMappingInfos.end()) {
			delete it->second;
			it++;
		}
	}
}

bool MappingMachine::initMappingMachine() {
	if (mRg) delete mRg;

	// obtain multi-pattern
	string multiPatt = "";
	std::map<uint32_t, PatternInfor*>::iterator it = mMappingInfos.begin();
	while (it != mMappingInfos.end()) {
		if (multiPatt.empty() == false) {
			multiPatt += "|";
		}
		multiPatt += "(" + it->second->mPattern + ")";
		it++;
	}

	// make regex
	if (multiPatt.empty() == false) {
		try {
			mRg = new std::regex(".*(" + multiPatt + ").*");
			return true;
		}
		catch (const std::regex_error & e) {
			// ignore
		}
	}
	return false;
}

bool MappingMachine::addPattern(string patt, const std::function<string(std::vector<string>)> cb) {
	try {
		// check valid pattern.
		std::regex rg(patt);
		int size = patt.length();
		int count = 0;
		for (int i = 0; i < size; i++) {
			if (patt[i] == '(' || patt[i] == ')') {
				if (count % 2 == 1 && patt[i] == '(') {
					throw std::exception("pattern error");		// not support this format of pattern: ((...))
				}
				count++;
			}
		}
		if (count % 2 != 0) {
			throw std::exception("pattern error");				// lack one of ')'
		}

		mMappingInfos.insert({mTopId, new PatternInfor(patt, mTopId, count / 2, cb)});
		mTopId += 1 + count / 2;
		return true;
	}
	catch (const std::regex_error& e) {
		
	}
	catch (...) {

	}
	return false;
}

bool MappingMachine::addPattern(const string patt)
{
	return addPattern(patt, NULL);
}

int MappingMachine::match(string str) {
	if (mNeedInitilize == false) {
		mNeedInitilize = initMappingMachine();
		if (mNeedInitilize == false) {
			return -1;
		}
	}

	if (std::regex_match(str, mSm, *mRg)) {
		for (std::map<uint32_t, PatternInfor*>::iterator it = mMappingInfos.begin(); it != mMappingInfos.end(); it++) {
			if (mSm.str(it->first).empty() == false) {
				return it->second->mId;
			}
		}
	}
	return -1;
}

int MappingMachine::search(string str) {

}

PatternInfor* MappingMachine::getPatternInfor(const uint32_t id) {
	if (id > mTopId) return NULL;

	return mMappingInfos[id];
}


#pragma endregion
