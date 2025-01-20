#include "pConnectionManager.h"
#include <string>

namespace p {
	CURL* p::ConnectionManager::curl = nullptr;
	CURLcode p::ConnectionManager::res = CURLE_OK;
	std::string p::ConnectionManager::response = "0";
	int p::ConnectionManager::HighScore = 0;
	
	void ConnectionManager::Initialize()
	{
		curl = curl_easy_init(); // libcurl 초기화
	}
	void ConnectionManager::Update()
	{
	}
	void ConnectionManager::LateUpdate()
	{
	}
	void ConnectionManager::Destroy()
	{
		curl_easy_cleanup(curl);
	}
	void ConnectionManager::SaveScore(int score)
	{
		if (curl) {
			curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8080/api/score");
			curl_easy_setopt(curl, CURLOPT_POST, 1L); // POST 요청
			
													  
			// Request Body에 데이터 추가
			std::string jsonData = "{\"score\":" + std::to_string(score) + "}";
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());

			res = curl_easy_perform(curl);
			assert(res == CURLE_OK);			
		}
	}
	int ConnectionManager::GetHighScore()
	{
		response.clear();
		if (curl) {
			curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8080/api/score"); // URL 설정
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback); // 응답 처리 콜백
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response); // 응답 데이터 저장

			res = curl_easy_perform(curl); // 요청 실행
			assert(res == CURLE_OK);			
		}

		if (response == "")return 0;
		return stoi(response);
	}

	size_t ConnectionManager::WriteCallback(void * contents, size_t size, size_t nmemb, std::string * userData)
	{
		userData->append((char*)contents, size * nmemb);
		return size * nmemb;
	}
}
