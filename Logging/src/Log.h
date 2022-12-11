#pragma once
#include <string>
using std::string;

namespace LOGGING {
	enum eDebugLevel {
		LOW, MID, HIGH
	};

	class Log {
	private:
		eDebugLevel mDebugLevel;
		string mLogPath;
		static Log mIns;

		Log();
		void writeLine (eDebugLevel lv, string str);
		string getTimeStamp();

	public:
		~Log();
		static void setDebugLevel(eDebugLevel lv);
		static void e(string str);
		static void d(string str);
		static void i(string str);
	};
}