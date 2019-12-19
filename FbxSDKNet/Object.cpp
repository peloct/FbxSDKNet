#include "pch.h"
#include "Object.h"
#include "Scene.h"

namespace FbxSDK
{
	Object::Object(Scene^ owner, FbxObject* object) : ownerScene(owner), object(object)
	{
		ownerScene->AddObject(object, this);
	}

	String^ Object::GetName()
	{
		return gcnew String(object->GetName());
	}
}
