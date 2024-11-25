#include "pch.h"
#include <opencascade/BRepGProp.hxx>
#include <opencascade/GProp_GProps.hxx>
#include <opencascade/BRepPrimAPI_MakeBox.hxx>
#include <opencascade/BRepMesh_IncrementalMesh.hxx>
#include <opencascade/Poly_Triangulation.hxx>
#include <opencascade/TopExp_Explorer.hxx>
#include <opencascade/Poly_Connect.hxx>
#include <opencascade/TopoDS.hxx>
#include <opencascade/TopoDS_Face.hxx>
#include "OdDb3dSolid.h"

OdDb3dSolid::OdDb3dSolid() : m_volume(0.0), m_surfaceArea(0.0), m_name("Unnamed") {}

OdBaseObjectPtr OdDb3dSolid::Clone()
{
	OdDb3dSolidPtr pSolid = OdDb3dSolid::createObject();
	pSolid->setName(m_name);
	pSolid->setMaterial(m_material);
	return pSolid;
}

OdResult OdDb3dSolid::draw() const
{
	return OdResult::eNotImplementedYet;
}

OdGeExtents3d OdDb3dSolid::boundingBox() const
{
	return getExtents();
}

OdResult OdDb3dSolid::worldDraw() const
{
	return OdResult();
}

json OdDb3dSolid::toJson() const
{
	json j = OdDbEntity::toJson();
	j["name"] = m_name;
	j["material"] = m_material;
	return j;
}

void OdDb3dSolid::fromJson(const json& j)
{
	OdDbEntity::fromJson(j);
	m_name = j["name"].get<std::string>();
	m_material = j["material"].get<std::string>();
}

OdResult OdDb3dSolid::calculateVolume()
{
	return OdResult::eNotImplementedYet;
}

OdResult OdDb3dSolid::calculateSurfaceArea()
{
	return OdResult::eNotImplementedYet;
}
