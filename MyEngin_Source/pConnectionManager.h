#pragma once
#include "CommonInclude.h"
#include <curl/curl.h>

namespace p {
	class ConnectionManager
	{
	public:
		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Destroy();

		static void SaveScore(int score);
		static int GetHighScore();
		static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userData);
	
	private:
		static CURL* curl;
		static CURLcode res;
		static std::string response;
		static int HighScore;
	};
}


