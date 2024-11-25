#pragma once
#include "OdDbEntity.h"

typedef OdSmartPtr<class OdDbLine> OdDbLinePtr;
class OdDbLine : public OdDbEntity
{
	OD_RTTI_DECLARE(OdDbLine, OdDbEntity)
public:
	OdDbLine();
	virtual ~OdDbLine() = default;
#pragma region Properties
	OdGePoint3d getStartPnt() const { return m_startPnt; }
	void setStartPnt(OdGePoint3d startPnt)
	{
		m_startPnt = startPnt;
		setPosition(startPnt.CenterTo(m_endPnt));
	}
	OdGePoint3d getEndPnt() const { return m_endPnt; }
	void setEndPnt(OdGePoint3d endPnt)
	{
		m_endPnt = endPnt;
		setPosition(m_startPnt.CenterTo(endPnt));
		m_extents = OdGeExtents3d(m_startPnt, m_endPnt);
	}
#pragma endregion

	// Inherited via OdDbEntity
	OdBaseObjectPtr Clone() override;
	virtual OdResult draw() const;
	OdGeExtents3d boundingBox() const override;
	OdResult worldDraw() const override;

	// Inherited via OdDbObject
	virtual json toJson() const override;
	virtual void fromJson(const json& j) override;
private:
	OdGePoint3d m_startPnt;
	OdGePoint3d m_endPnt;
};

OD_RTTI_DEFINE(OdDbLine, OdDbEntity)
