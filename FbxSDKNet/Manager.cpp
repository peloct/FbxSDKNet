#include "pch.h"
#include "Manager.h"
#include "Scene.h"
#include "Utils.h"

using namespace FbxSDK;
using namespace System::IO;

Manager^ Manager::Create()
{
	FbxManager* fbxManager = FbxManager::Create();
	FbxIOSettings* pIOsettings = FbxIOSettings::Create(fbxManager, IOSROOT);
	fbxManager->SetIOSettings(pIOsettings);

	Manager^ nFbxManager = gcnew Manager(fbxManager);
	return nFbxManager;
}

Manager::!Manager()
{
	for (int i = 0; i < sceneReferenceList->Count; ++i)
		if (!sceneReferenceList[i]->isDisposed)
			sceneReferenceList[i]->Destroy();

	DebugLine("Manager Disposed");
	
	fbxManager->Destroy();
}

String^ Manager::GetVersion()
{
	return GetVersion(true);
}

String^ Manager::GetVersion(bool pFull)
{
	String^ clistr = gcnew String(fbxManager->GetVersion(pFull));
	return clistr;
}

SceneReference^ Manager::AddSceneReference(FbxScene* scene)
{
	for (int i = 0; i < sceneReferenceList->Count; ++i)
	{
		if (sceneReferenceList[i]->isDisposed)
		{
			sceneReferenceList[i]->SetScene(scene);
			return sceneReferenceList[i];
		}
	}

	SceneReference^ newSceneRefer = gcnew SceneReference();
	newSceneRefer->SetScene(scene);
	sceneReferenceList->Add(newSceneRefer);
	return newSceneRefer;
}

Scene^ Manager::CreateSceneFromFile(String^ path)
{
	String^ fileName = Path::GetFileNameWithoutExtension(path);
	FbxImporter* importer = FbxImporter::Create(fbxManager, "Importer");
	
	bool isSuccess = importer->Initialize(StringToCStr(path), -1, fbxManager->GetIOSettings());

	if (!isSuccess)
	{
		importer->Destroy();
		return nullptr;
	}

	FbxScene* fbxScene = FbxScene::Create(fbxManager, StringToCStr(fileName));
	isSuccess = importer->Import(fbxScene);

	if (!isSuccess)
	{
		fbxScene->Destroy();
		importer->Destroy();
		return nullptr;
	}

	importer->Destroy();

	return gcnew Scene(this, AddSceneReference(fbxScene));
}

Scene^ Manager::CreateScene(String^ name)
{
	FbxScene* fbxScene = FbxScene::Create(fbxManager, StringToCStr(name));
	return gcnew Scene(this, AddSceneReference(fbxScene));
}