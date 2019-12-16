#pragma once
#include <fbxsdk.h>
#include "Types.h"

namespace FbxSDK
{
	ref class Node;

	public ref class Pose
	{
	private:
		FbxPose* pose;

	internal:
		Pose(FbxPose* pose) : pose(pose) {}
		
	public:
		int Find(Node^ node);
		bool IsBindPose();
		bool IsLocalMatrix(int nodeIndex);
		Matrix GetMatrix(int nodeIndex);
	};
}