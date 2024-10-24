#pragma once
#include "pEntity.h"
namespace p {
	class Resource:public Entity
	{
	public:
		Resource(enums::eResourceType type);
		virtual ~Resource();

		virtual HRESULT Load(const std::wstring& path) = 0;//bool이랑 같음
		const std::wstring& GetPath() { return mPath; }
		void SetPath(const std::wstring& path) { mPath = path; }
	private:
		std::wstring mPath;
		const enums::eResourceType mType;

	};
	//리소스는 상속해서 써야함 추상클래스로 선언
	//메모리 할당 불가능
}


