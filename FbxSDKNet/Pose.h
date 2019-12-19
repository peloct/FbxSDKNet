#pragma once
#include <fbxsdk.h>
#include "Types.h"
#include "Object.h"

namespace FbxSDK
{
	ref class Node;
	ref class Scene;

	public ref class Pose : Object
	{
	private:
		FbxPose* pose;
		Pose(Scene^ scene, FbxPose* pose) : Object(scene, pose), pose(pose) {}

	internal:
		static Pose^ GetPose(Scene^ scene, FbxPose* pose);

	public:
		int Find(Node^ node);
		bool IsBindPose();
		bool IsLocalMatrix(int nodeIndex);
		Matrix GetMatrix(int nodeIndex);
	};
}