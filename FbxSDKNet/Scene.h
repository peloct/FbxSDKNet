#pragma once
#include <fbxsdk.h>

using namespace System;

namespace FbxSDK
{
	ref class Manager;
	ref class SceneReference;
	ref class Node;

	public ref class Scene
	{
	private:
		Manager^ manager;
		SceneReference^ sceneReference;

		~Scene() {}
		!Scene();

	internal:
		Scene(Manager^ manager, SceneReference^ sceneReference) : manager(manager), sceneReference(sceneReference) {}

	public:
		Node^ GetRootNode();
	};
}