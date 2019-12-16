#include "pch.h"
#include "TextureInfo.h"

namespace FbxSDK
{
	TextureInfo::TextureInfo(FbxTexture* texture) : Object(texture)
	{
		FbxLayeredTexture* layeredTexture = FbxCast<FbxLayeredTexture>(texture);
		if (!layeredTexture)
		{
			this->layeredTexture = nullptr;
			this->texture = texture;
		}
		else
		{
			this->layeredTexture = layeredTexture;
			this->texture = nullptr;
		}
	}

	bool TextureInfo::IsLayeredTexture()
	{
		return layeredTexture != nullptr;
	}

	int TextureInfo::GetChildCount()
	{
		return layeredTexture->GetSrcObjectCount<FbxTexture>();
	}

	bool TextureInfo::GetChildTexture(int index, TextureInfo^% texutreInfo, TextureBlendMode& blendMode, double& alpha)
	{
		FbxTexture* texture = layeredTexture->GetSrcObject<FbxTexture>(index);

		texutreInfo = nullptr;
		blendMode = TextureBlendMode::Translucent;
		alpha = 0.0;

		if (!texture)
			return false;

		FbxLayeredTexture::EBlendMode tmpBlendMode;
		if (layeredTexture->GetTextureBlendMode(index, tmpBlendMode))
			blendMode = static_cast<TextureBlendMode>(static_cast<int>(tmpBlendMode));
		else
			return false;

		if (!layeredTexture->GetTextureAlpha(index, alpha))
			return false;

		texutreInfo = gcnew TextureInfo(texture);
		return true;
	}

	bool TextureInfo::IsFileTexture()
	{
		return FbxCast<FbxFileTexture>(texture) != nullptr;
	}

	String^ TextureInfo::GetFileName()
	{
		return gcnew String(FbxCast<FbxFileTexture>(texture)->GetFileName());
	}

	TextureMaterialUse TextureInfo::GetMaterialUse()
	{
		return static_cast<TextureMaterialUse>(static_cast<int>(FbxCast<FbxFileTexture>(texture)->GetMaterialUse()));
	}

	double TextureInfo::GetScaleU()
	{
		return texture->GetScaleU();
	}

	double TextureInfo::GetScaleV()
	{
		return texture->GetScaleV();
	}

	double TextureInfo::GetTranslationU()
	{
		return texture->GetTranslationU();
	}

	double TextureInfo::GetTranslationV()
	{
		return texture->GetTranslationV();
	}

	bool TextureInfo::GetSwapUV()
	{
		return texture->GetSwapUV();
	}

	double TextureInfo::GetRotationU()
	{
		return texture->GetRotationU();
	}

	double TextureInfo::GetRotationV()
	{
		return texture->GetRotationV();
	}

	double TextureInfo::GetRotationW()
	{
		return texture->GetRotationW();
	}

	TextureAlphaSource TextureInfo::GetAlphaSource()
	{
		return static_cast<TextureAlphaSource>(static_cast<int>(texture->GetAlphaSource()));
	}

	double TextureInfo::GetCroppingLeft()
	{
		return texture->GetCroppingLeft();
	}

	double TextureInfo::GetCroppingTop()
	{
		return texture->GetCroppingTop();
	}

	double TextureInfo::GetCroppingRight()
	{
		return texture->GetCroppingRight();
	}

	double TextureInfo::GetCroppingBottom()
	{
		return texture->GetCroppingBottom();
	}

	TextureMappingType TextureInfo::GetMappingType()
	{
		return static_cast<TextureMappingType>(static_cast<int>(texture->GetMappingType()));
	}

	int TextureInfo::GetPlanarMappingNormal()
	{
		return texture->GetPlanarMappingNormal();
	}

	double TextureInfo::GetDefaultAlpha()
	{
		return texture->GetDefaultAlpha();
	}

	TextureUse TextureInfo::GetTextureUse()
	{
		return static_cast<TextureUse>(static_cast<int>(texture->GetTextureUse()));
	}
}