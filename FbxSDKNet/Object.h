#pragma once

#include<fbxsdk.h>

using namespace System;

namespace FbxSDK
{
	public ref class Object
	{
	private:
		FbxObject* object;

	protected:
		Object(FbxObject* object) : object(object) {}

	public:
		String^ GetName();

		bool operator==(const Object^ other)
		{
			return object->operator==(*other->object);
		}
	};
}