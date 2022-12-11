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
		string p = std::string(NPath) + "\\runtime.log";

		writeLine(HIGH, "=== start NPP Pluggin ===");
		writeLine(HIGH, p);
	}

	Log::~Log() {
	}

	void Log::writeLine (eDebugLevel lv, string str) {
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
		mIns.writeLine(HIGH, str);
	}
	void Log::d(string str) {
		mIns.writeLine(MID, str);
	}
	void Log::i(string str) {
		mIns.writeLine(LOW, str);
	}
};