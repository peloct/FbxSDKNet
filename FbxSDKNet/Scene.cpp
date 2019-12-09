#include "pch.h"
#include "Scene.h"
#include "Manager.h"
#include "Utils.h"
#include "Node.h"
#include "Animation.h"
#include "AnimationEvaluator.h"

using namespace FbxSDK;

Scene::!Scene()
{
	if (!sceneReference->isDisposed)
		sceneReference->Destroy();

	DebugLine("Scene Disposed");
	manager = nullptr;
}

Node^ Scene::GetRootNode()
{
	return gcnew Node(sceneReference->scene->GetRootNode());
}

int Scene::GetAnimStackCount()
{
	return sceneReference->scene->GetSrcObjectCount<FbxAnimStack>();
}

AnimationStack^ Scene::GetAnimStack(int index)
{
	return gcnew AnimationStack(sceneReference->scene->GetSrcObject<FbxAnimStack>());
}

AnimationEvaluator^ Scene::GetAnimEvaluator()
{
	return gcnew AnimationEvaluator(sceneReference->scene->GetAnimationEvaluator());
}
