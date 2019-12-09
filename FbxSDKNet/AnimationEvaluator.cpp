#include "pch.h"
#include "AnimationEvaluator.h"
#include "Node.h"
#include "Types.h"

using namespace FbxSDK;

Matrix AnimationEvaluator::GetNodeGlobalTransform(Node^ node, long long time)
{
	FbxAMatrix matrix = evaluator->GetNodeGlobalTransform(node->node, time);
	FbxVector4 t = matrix.GetT();
	FbxVector4 r = matrix.GetR();
	FbxVector4 s = matrix.GetS();
	return Matrix(Vector3(t[0], t[1], t[2]), Vector3(r[0], r[1], r[2]), Vector3(s[0], s[1], s[2]));
}

Matrix AnimationEvaluator::GetNodeLocalTransform(Node^ node, long long time)
{
	FbxAMatrix matrix = evaluator->GetNodeLocalTransform(node->node, time);
	FbxVector4 t = matrix.GetT();
	FbxVector4 r = matrix.GetR();
	FbxVector4 s = matrix.GetS();
	return Matrix(Vector3(t[0], t[1], t[2]), Vector3(r[0], r[1], r[2]), Vector3(s[0], s[1], s[2]));
}
