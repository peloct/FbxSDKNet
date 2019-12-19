#pragma once

#include <fbxsdk.h>
#include "Object.h"

namespace FbxSDK
{
	ref class Node;
	ref class NodeAttribute;

	public enum class NodeAttributeType
	{
		Unknown,
		Null,
		Marker,
		Skeleton,
		Mesh,
		Nurbs,
		Patch,
		Camera,
		CameraStereo,
		CameraSwitcher,
		Light,
		OpticalReference,
		OpticalMarker,
		NurbsCurve,
		TrimNurbsSurface,
		Boundary,
		NurbsSurface,
		Shape,
		LODGroup,
		SubDiv,
		CachedEffect,
		Line
	};

	NodeAttributeType ConvertAttributeType(FbxNodeAttribute::EType attributeType);
	NodeAttribute^ ConvertNodeAttribute(Node^ node, FbxNodeAttribute* attribute);

	public ref class NodeAttribute : Object
	{
	private:
		Node^ node;
		FbxNodeAttribute* attribute;

	protected:
		NodeAttribute(Node^ node, FbxNodeAttribute* attribute);

	public:
		NodeAttributeType GetAttributeType() { return ConvertAttributeType(attribute->GetAttributeType()); }
		Node^ GetNode() { return node; }
	};
}