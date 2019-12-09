#pragma once
#include <fbxsdk.h>
#include "Types.h"
#include "Object.h"

namespace FbxSDK
{
	ref class Node;

	public ref class AnimationEvaluator : Object
	{
	private:
		FbxAnimEvaluator* evaluator;

	internal:
		AnimationEvaluator(FbxAnimEvaluator* evaluator) : Object(evaluator), evaluator(evaluator) {}

	public:
		Matrix GetNodeGlobalTransform(Node^ node, long long time);
		Matrix GetNodeLocalTransform(Node^ node, long long  time);
	};
}