#pragma once
#include "OdDbEntity.h"

typedef OdSmartPtr<class OdDbPolyline> OdDbPolylinePtr;
class OdDbPolyline :
    public OdDbEntity
{
	OD_RTTI_DECLARE(OdDbPolyline, OdDbEntity);
public:
	OdDbPolyline();
	virtual ~OdDbPolyline() = default;
	void addVertex(const OdGePoint3d& vertex, double bulge = 0);
	OdGePoint3d getVertexAt(int index) const;
	double getBulgeAt(int index) const;
	int numVertices() const;
	// Inherited via OdDbEntity
	OdBaseObjectPtr Clone() override;
	OdResult draw() const override;
	OdGeExtents3d boundingBox() const override;
	OdResult worldDraw() const override;

	// Inherited via OdDbObject
	virtual json toJson() const override;
	virtual void fromJson(const json& j) override;
private:
	std::vector<std::pair<OdGePoint3d, double>> m_vertices;
};

OD_RTTI_DEFINE(OdDbPolyline, OdDbEntity)