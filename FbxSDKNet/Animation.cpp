#include "pch.h"
#include "Animation.h"
#include "Node.h"

namespace FbxSDK
{
	int AnimationStack::GetAnimationLayerCount()
	{
		return animStack->GetMemberCount<FbxAnimLayer>();
	}

	AnimationLayer^ AnimationStack::GetAnimationLayer(int layerIndex)
	{
		return gcnew AnimationLayer(animStack->GetMember<FbxAnimLayer>(layerIndex));
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
		return gcnew AnimationCurve(curve);
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