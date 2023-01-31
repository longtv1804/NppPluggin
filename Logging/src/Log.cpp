#define _CRT_SECURE_NO_WARNINGS

#include "Log.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include <time.h>
using std::ofstream;

namespace LOGGING {
	Log Log::mIns;

	Log::Log() {
		mDebugLevel = LOW;

		char NPath[MAX_PATH];
		GetCurrentDirectoryA(MAX_PATH, NPath);
		mLogPath = std::string(NPath) + "\\runtime.log";

		writeLine(DEBUG, "=== start NPP Pluggin ===");
	}

	Log::~Log() {
	}

	string Log::getTimeStamp()
	{
		time_t t = time(0);
		struct tm* _t;
		char timeCString[25] = { 0, };
		
		_t = localtime(&t);
		strftime(timeCString, 25, "%Y.%d.%m %H:%M:%S", _t);
		return string(timeCString);
	}

	void Log::writeLine (eLoggLevel lv, string str) {
		if (lv >= mDebugLevel) {
			ofstream file;
			file.open(mLogPath, std::ios::app); // std::ios::app is the open mode "append" meaning

			if (file.is_open()) {
				file << str + "\n";
			}
			file.close();
		}
	}

	void Log::setDebugLevel(eDebugLevel lv) {
		mIns.mDebugLevel = lv;
	}
	void Log::e(string str) {
		mIns.writeLine(ERR, str);
	}
	void Log::d(string str) {
		mIns.writeLine(DEBUG, str);
	}
	void Log::i(string str) {
		mIns.writeLine(INFO, str);
	}
};