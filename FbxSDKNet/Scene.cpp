#include "pch.h"
#include "Scene.h"
#include "Manager.h"
#include "Node.h"
#include "Utils.h"

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
	return gcnew Node(nullptr, sceneReference->scene->GetRootNode());
}
