#include "pch.h"
#include "OdMathLine.h"

OdMathLine::OdMathLine()
{
}

OdMathLine::OdMathLine(OdGePoint3d startPnt, OdGePoint3d endPnt)
{
	setStartPnt(startPnt);
	setEndPnt(endPnt);
}

OdResult OdMathLine::draw() 
{
	try
	{
		OdGePoint3d transformedStart = (getStartPnt() * m_scale) * m_transform;
		OdGePoint3d transformedEnd = (getEndPnt() * m_scale) * m_transform;
		glDisable(GL_LIGHTING);
		getExtents().reset();
		glBegin(GL_LINES);
		glVertex2f(static_cast<GLfloat>(transformedStart.x), static_cast<GLfloat>(transformedStart.y));
		glVertex2f(static_cast<GLfloat>(transformedEnd.x), static_cast<GLfloat>(transformedEnd.y));
		glEnd();
		glEnable(GL_LIGHTING);
		OdGeExtents3d extents = OdGeExtents3d(transformedStart, transformedEnd);
		extents.apppendPoint(transformedStart);
		extents.apppendPoint(transformedEnd);
		extents.appendFace({ 0, 1 });
		return OdResult::eOk;
	}
	catch (const std::exception&)
	{
		return OdResult::eInvalidDrawing;
	}
}

OdBaseObjectPtr OdMathLine::Clone()
{
	OdMathLinePtr clone = OdMathLine::createObject();
	clone->setStartPnt(getStartPnt());
	clone->setEndPnt(getEndPnt());
	return clone;
}
