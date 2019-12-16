#include "pch.h"
#include "Material.h"
#include "TextureInfo.h"

namespace FbxSDK
{
	array<TextureInfo^>^ Material::GetTextureInfo(TextureChannel textureChannel)
	{
		FbxProperty prop;

		switch (textureChannel)
		{
		case FbxSDK::TextureChannel::Diffuse:
			prop = material->FindProperty(FbxSurfaceMaterial::sDiffuse);
			break;
		case FbxSDK::TextureChannel::DiffuseFactor:
			prop = material->FindProperty(FbxSurfaceMaterial::sDiffuseFactor);
			break;
		case FbxSDK::TextureChannel::Emissive:
			prop = material->FindProperty(FbxSurfaceMaterial::sEmissive);
			break;
		case FbxSDK::TextureChannel::EmissiveFactor:
			prop = material->FindProperty(FbxSurfaceMaterial::sEmissiveFactor);
			break;
		case FbxSDK::TextureChannel::Ambient:
			prop = material->FindProperty(FbxSurfaceMaterial::sAmbient);
			break;
		case FbxSDK::TextureChannel::AmbientFactor:
			prop = material->FindProperty(FbxSurfaceMaterial::sAmbientFactor);
			break;
		case FbxSDK::TextureChannel::Specular:
			prop = material->FindProperty(FbxSurfaceMaterial::sSpecular);
			break;
		case FbxSDK::TextureChannel::SpecularFactor:
			prop = material->FindProperty(FbxSurfaceMaterial::sSpecularFactor);
			break;
		case FbxSDK::TextureChannel::Shininess:
			prop = material->FindProperty(FbxSurfaceMaterial::sShininess);
			break;
		case FbxSDK::TextureChannel::Bump:
			prop = material->FindProperty(FbxSurfaceMaterial::sBump);
			break;
		case FbxSDK::TextureChannel::NormalMap:
			prop = material->FindProperty(FbxSurfaceMaterial::sNormalMap);
			break;
		case FbxSDK::TextureChannel::TransparentColor:
			prop = material->FindProperty(FbxSurfaceMaterial::sTransparentColor);
			break;
		case FbxSDK::TextureChannel::TransparencyFactor:
			prop = material->FindProperty(FbxSurfaceMaterial::sTransparencyFactor);
			break;
		case FbxSDK::TextureChannel::Reflection:
			prop = material->FindProperty(FbxSurfaceMaterial::sReflection);
			break;
		case FbxSDK::TextureChannel::ReflectionFactor:
			prop = material->FindProperty(FbxSurfaceMaterial::sReflectionFactor);
			break;
		default:
			break;
		}

		if (prop.IsValid())
		{
			int textureCount = prop.GetSrcObjectCount<FbxTexture>();
			array<TextureInfo^>^ ret = gcnew array<TextureInfo^>(textureCount);
			for (int i = 0; i < textureCount; ++i)
				ret[i] = gcnew TextureInfo(prop.GetSrcObject<FbxTexture>(i));
			return ret;
		}
		else
		{
			return gcnew array<TextureInfo^>(0);
		}
	}
}
