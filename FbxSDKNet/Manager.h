#pragma once

#include <fbxsdk.h>

using namespace std;
using namespace System;
using namespace System::Collections::Generic;

namespace FbxSDK
{
	ref class Scene;

	private ref class SceneReference
	{
	public:
		FbxScene* scene;
		bool isDisposed;

		SceneReference() {}

		void Destroy()
		{
			if (isDisposed)
				return;

			isDisposed = true;
			scene->Destroy();
		}

		void SetScene(FbxScene* scene)
		{
			this->scene = scene;
			isDisposed = false;
		}
	};

	public ref class Manager
	{
	private:
		FbxManager* manager;
		FbxGeometryConverter* converter;

		List<SceneReference^>^ sceneReferenceList;

		Manager(FbxManager* manager)
		{
			this->manager = manager;
			converter = new FbxGeometryConverter(manager);
			sceneReferenceList = gcnew List<SceneReference^>();
		}

		~Manager() {}
		!Manager();

		SceneReference^ AddSceneReference(FbxScene* fbxNetScene);

	public:
		static Manager^ Create();

		String^ GetVersion();
		String^ GetVersion(bool pFull);

		Scene^ CreateSceneFromFile(String^ path);
	};
}
