#include "Log.h"
#include <iostream>
#include <fstream>
#include <windows.h>
using std::ofstream;

namespace LOGGING {
	Log Log::mIns;

	Log::Log() {
		mDebugLevel = LOW;

		char NPath[MAX_PATH];
		GetCurrentDirectoryA(MAX_PATH, NPath);
		mLogPath = std::string(NPath) + "runtime.log";
	}
	Log::~Log() {
	}

	void Log::write(eDebugLevel lv, string str) {
		if (lv >= mDebugLevel) {
			ofstream file;
			file.open(mLogPath);

			if (file.is_open()) {
				file << str;
			}
			file.close();
		}
	}

	void Log::setDebugLevel(eDebugLevel lv) {
		mIns.mDebugLevel = lv;
	}
	void Log::e(string str) {
		mIns.write(HIGH, str);
	}
	void Log::d(string str) {
		mIns.write(MID, str);
	}
	void Log::i(string str) {
		mIns.write(LOW, str);
	}
};