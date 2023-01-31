#pragma once
#include <string>
using std::string;

namespace LOGGING {
	enum eDebugLevel {
		HIGH, MID, LOW
	};

	enum eLoggLevel {
		INFO, DEBUG, ERR
	};

	class Log {
	private:
		eDebugLevel mDebugLevel;
		string mLogPath;
		static Log mIns;

		Log();
		void writeLine (eLoggLevel lv, string str);
		string getTimeStamp();

	public:
		~Log();
		static void setDebugLevel(eDebugLevel lv);
		static void e(string str);
		static void d(string str);
		static void i(string str);
	};
}