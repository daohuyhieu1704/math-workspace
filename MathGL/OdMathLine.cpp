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
		glVertex3f(static_cast<GLfloat>(transformedStart.x), static_cast<GLfloat>(transformedStart.y), static_cast<GLfloat>(transformedStart.z));
		glVertex3f(static_cast<GLfloat>(transformedEnd.x), static_cast<GLfloat>(transformedEnd.y), static_cast<GLfloat>(transformedEnd.z));
		glEnd();
		glEnable(GL_LIGHTING);
		getExtents().appendPoint_s(transformedStart);
		getExtents().appendPoint_s(transformedEnd);
		getExtents().appendFace({ 0, 1 });
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
