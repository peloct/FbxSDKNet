#include "pch.h"
#include "Object.h"

namespace FbxSDK
{
	String^ Object::GetName()
	{
		return gcnew String(object->GetName());
	}
}
