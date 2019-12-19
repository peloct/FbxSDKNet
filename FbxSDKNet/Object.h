#pragma once

#include<fbxsdk.h>

using namespace System;

namespace FbxSDK
{
	ref class Scene;

	public ref class Object
	{
	private:
		Scene^ ownerScene;
		FbxObject* object;

	protected:
		Object(Scene^ owner, FbxObject* object);

	public:
		String^ GetName();
		Scene^ GetScene() { return ownerScene; }
	};
}