#include <GlobalDefines.hpp>
#include <utility/GameUtility.hpp>

#include <source_engine/index.hpp>

#include <string>

namespace SteveBase::Utility {
	using namespace SourceEngine::Virtual;

    std::string m_hackDllDirectory;
	std::string m_hackConfigLocation;
	bool m_cheatRunning;

	/*
	vector<string> playerSoundList {
		text("anarchist)(balkan)(fbihrt)(gign"),
		text("gsg9)(idf)(leet)(phoenix"),
		text("pirate)(professional)(sas)(seal"),
		text("separatist)(swat"),
	};
	*/

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
    /*
	void GameUtility::MsgTemplate(string name, string msg) {
#if !SIMULATOR
		auto mod = SystemUtility::SafeGetModuleHandle(text("tier0.dll"));
		((MsgFn)GetProcAddress(mod, name.data()))(msg.c_str());
#endif
	}
	void GameUtility::Msg(string msg) {
		MsgTemplate(text("Msg"), msg);
	}
	void GameUtility::Warning(string msg) {
		MsgTemplate(text("Warning"), msg);
	}
	void GameUtility::Log(string msg) {
		MsgTemplate(text("Log"), msg);
	}
	
#pragma warning(push)
#pragma warning(disable: 4244) // precision loss
	string GameUtility::SecondsToHMSString(time_t delta) {
		auto str = string("");

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

	void GameUtility::PlayRandomReadySound() {
		GetInterface(ISurface)->PlaySound(
			ggformat_to_string(
				text("player/vo/{0}/inposition0{1}.wav"),
				playerSoundList[rand() % playerSoundList.size()],
				rand() % 3 + 1 // [1, 3)
			)
		);
	}
	*/
}