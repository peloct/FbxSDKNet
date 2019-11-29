#pragma once

using namespace System;
using namespace System::Diagnostics;
using namespace System::Runtime::InteropServices;

#ifdef _DEBUG
#define DebugLine(str) System::Diagnostics::Debug::WriteLine(str)
#else
#define DebugLine(str)
#endif  // DEBUG

namespace FbxSDK
{
	static const char* StringToCStr(String^ str)
	{
		IntPtr strPtr = Marshal::StringToHGlobalAnsi(str);
		char* cStr = (char*)strPtr.ToPointer();
		return cStr;
	}
}