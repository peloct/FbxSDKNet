#include "pch.h"
#include "Types.h"
#include <string>

namespace FbxSDK
{
	String^ Vector2::ToString()
	{
		std::string str = "{ " + std::to_string(x) + ", " + std::to_string(y) + " }";
		return gcnew String(str.c_str());
	}

	String^ Vector3::ToString()
	{
		std::string str = "{ " + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + " }";
		return gcnew String(str.c_str());
	}

	String^ Color::ToString()
	{
		std::string str = "{ " + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + ", " + std::to_string(a) + " }";
		return gcnew String(str.c_str());
	}

	String^ FbxSDK::Matrix::ToString()
	{
		return "{ T : " + translation.ToString() + ", R : " + rotation.ToString() + ", S : " + scaling.ToString() + " }";
	}
}