#include "pch.h"
#include "Animation.h"
#include "Node.h"
#include "Scene.h"

namespace FbxSDK
{
	AnimationStack^ AnimationStack::GetAnimStack(Scene^ scene, FbxAnimStack* animStack)
	{
		if (animStack == nullptr)
			return nullptr;

		AnimationStack^ ret = static_cast<AnimationStack^>(scene->FindObject(animStack));
		if (ret)
			return ret;
		else
			return gcnew AnimationStack(scene, animStack);
	}

	int AnimationStack::GetAnimationLayerCount()
	{
		return animStack->GetMemberCount<FbxAnimLayer>();
	}

	AnimationLayer^ AnimationStack::GetAnimationLayer(int layerIndex)
	{
		return AnimationLayer::GetAnimLayer(this, animStack->GetMember<FbxAnimLayer>(layerIndex));
	}

	AnimationLayer::AnimationLayer(AnimationStack^ owner, FbxAnimLayer* layer) : Object(owner->GetScene(), layer), layer(layer) {}

	AnimationLayer^ AnimationLayer::GetAnimLayer(AnimationStack^ owner, FbxAnimLayer* layer)
	{
		if (layer == nullptr)
			return nullptr;

		AnimationLayer^ ret = static_cast<AnimationLayer^>(owner->GetScene()->FindObject(layer));
		if (ret)
			return ret;
		else
			return gcnew AnimationLayer(owner, layer);
	}

	AnimationCurve^ AnimationLayer::GetAnimationCurve(Node^ node, AnimationCurveChannel curveChannel)
	{
		FbxNode* fNode = node->node;
		FbxAnimCurve* curve = nullptr;

		switch (curveChannel)
		{
		case AnimationCurveChannel::TranslationX:
			curve = fNode->LclTranslation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_X);
			break;
		case AnimationCurveChannel::TranslationY:
			curve = fNode->LclTranslation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_Y);
			break;
		case AnimationCurveChannel::TranslationZ:
			curve = fNode->LclTranslation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_Z);
			break;
		case AnimationCurveChannel::RotationX:
			curve = fNode->LclRotation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_X);
			break;
		case AnimationCurveChannel::RotationY:
			curve = fNode->LclRotation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_Y);
			break;
		case AnimationCurveChannel::RotationZ:
			curve = fNode->LclRotation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_Z);
			break;
		case AnimationCurveChannel::ScalingX:
			curve = fNode->LclScaling.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_X);
			break;
		case AnimationCurveChannel::ScalingY:
			curve = fNode->LclScaling.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_Y);
			break;
		case AnimationCurveChannel::ScalingZ:
			curve = fNode->LclScaling.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_Z);
			break;
		case AnimationCurveChannel::AttributeColorRed:
			if (fNode->GetNodeAttribute())
			{
				FbxNodeAttribute* attribute = fNode->GetNodeAttribute();
				curve = attribute->Color.GetCurve(layer, FBXSDK_CURVENODE_COLOR_RED);
			}
			break;
		case AnimationCurveChannel::AttributeColorGreen:
			if (fNode->GetNodeAttribute())
			{
				FbxNodeAttribute* attribute = fNode->GetNodeAttribute();
				curve = attribute->Color.GetCurve(layer, FBXSDK_CURVENODE_COLOR_GREEN);
			}
			break;
		case AnimationCurveChannel::AttributeColorBlue:
			if (fNode->GetNodeAttribute())
			{
				FbxNodeAttribute* attribute = fNode->GetNodeAttribute();
				curve = attribute->Color.GetCurve(layer, FBXSDK_CURVENODE_COLOR_BLUE);
			}
			break;
		case AnimationCurveChannel::LightIntensity:
		{
			FbxLight* light = fNode->GetLight();
			if (light)
				curve = light->Intensity.GetCurve(layer);
		}
		break;
		case AnimationCurveChannel::LightOuterAngle:
		{
			FbxLight* light = fNode->GetLight();
			if (light)
				curve = light->OuterAngle.GetCurve(layer);
		}
		break;
		case AnimationCurveChannel::LightFog:
		{
			FbxLight* light = fNode->GetLight();
			if (light)
				curve = light->Fog.GetCurve(layer);
		}
		break;
		case AnimationCurveChannel::CameraFieldOfViewX:
		{
			FbxCamera* camera = fNode->GetCamera();
			if (camera)
				curve = camera->FieldOfViewX.GetCurve(layer);
		}
		break;
		case AnimationCurveChannel::CameraFieldOfViewY:
		{
			FbxCamera* camera = fNode->GetCamera();
			if (camera)
				curve = camera->FieldOfViewY.GetCurve(layer);
		}
		break;
		case AnimationCurveChannel::CameraOpticalCenterX:
		{
			FbxCamera* camera = fNode->GetCamera();
			if (camera)
				curve = camera->OpticalCenterX.GetCurve(layer);
		}
		break;
		case AnimationCurveChannel::CameraOpticalCenterY:
		{
			FbxCamera* camera = fNode->GetCamera();
			if (camera)
				curve = camera->OpticalCenterY.GetCurve(layer);
		}
		break;
		case AnimationCurveChannel::CameraRoll:
		{
			FbxCamera* camera = fNode->GetCamera();
			if (camera)
				curve = camera->Roll.GetCurve(layer);
		}
		break;
		default:
			break;
		}

		if (!curve)
			return nullptr;

		curve->KeyGet(0);
		curve->KeyGetCount();
		curve->KeyGetTime(0);
		curve->KeyGetValue(0);
		curve->KeyGetInterpolation(0);
		return AnimationCurve::GetAnimCurve(this, curve);
	}

	AnimationCurve::AnimationCurve(AnimationLayer^ owner, FbxAnimCurve* curve) : Object(owner->GetScene(), curve), curve(curve) {}

	AnimationCurve^ AnimationCurve::GetAnimCurve(AnimationLayer^ owner, FbxAnimCurve* curve)
	{
		if (curve == nullptr)
			return nullptr;

		AnimationCurve^ ret = static_cast<AnimationCurve^>(owner->GetScene()->FindObject(curve));
		if (ret)
			return ret;
		else
			return gcnew AnimationCurve(owner, curve);
	}

	int AnimationCurve::GetKeyCount()
	{
		return curve->KeyGetCount();
	}

	Time AnimationCurve::GetKeyTime(int index)
	{
		return Time(curve->KeyGetTime(index));
	}

	double AnimationCurve::GetKeyValue(int index)
	{
		return curve->KeyGetValue(index);
	}

	AnimationInterpolationType AnimationCurve::GetKeyInterpolation(int index)
	{
		return static_cast<AnimationInterpolationType>(static_cast<int>(curve->KeyGetInterpolation(index)));
	}
}