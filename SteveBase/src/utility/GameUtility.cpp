#include <GlobalDefines.hpp>
#include <utility/GameUtility.hpp>

#include <source_engine/index.hpp>

#include <string>

namespace SteveBase::Utility {
	using namespace SourceEngine::Virtual;

    std::string m_hackDllDirectory;
	std::string m_hackConfigLocation;
	bool m_cheatRunning;

	void GameUtility::SetCheatRunning(bool running) {
		m_cheatRunning = running;
	}

	bool GameUtility::GetCheatRunning() {
		return m_cheatRunning;
	}

	void GameUtility::SetHackDirectory(std::string modPath) {
		m_hackDllDirectory = modPath;
	}

	std::string GameUtility::GetHackDirectory() {
		return m_hackDllDirectory;
	}

	void GameUtility::SetHackConfigLocation(std::string location) {
		m_hackConfigLocation = location;
	}

	std::string GameUtility::GetHackConfigLocation() {
		return m_hackConfigLocation;
	}

#if 0
#pragma warning(push)
#pragma warning(disable: 4244) // precision loss
	std::string GameUtility::SecondsToHMSString(time_t delta) {
		auto str = std::string("");

		if (delta >= 3600) { // hours
			int hrs = delta / 3600; // integer division returns quotient!! Unlike floating number division!!

			str += ggformat_to_string(text("{0} hour{1}"), hrs, hrs > 1 ? "s" : "");
			delta %= 3600; // the remaining seconds are remainer of delta divided by seconds of 1 hour
		}
		if (delta >= 60) { // minutes
			if (str.length() != 0) {
				str += ", ";
			}
			int min = delta / 60;
			str += ggformat_to_string(text("{0} minute{1}"), min, min > 1 ? "s" : "");
			delta %= 60;
		}

		if (delta >= 0) { // seconds
			if (str.length() != 0) {
				str += ", ";
			}
			int sec = delta;
			str += ggformat_to_string(text("{0} second{1}"), sec, sec > 1 ? "s" : "");
		}

		return str;
	}
#pragma warning(pop)
#endif
}