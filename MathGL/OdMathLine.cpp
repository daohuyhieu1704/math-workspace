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

OdResult OdMathLine::draw() const
{
	try
	{
		glDisable(GL_LIGHTING);
		glBegin(GL_LINES);
		glVertex2f(getStartPnt().x, getStartPnt().y);
		glVertex2f(getEndPnt().x, getEndPnt().y);
		glEnd();
		glEnable(GL_LIGHTING);
		return OdResult::eOk;
	}
	catch (const std::exception&)
	{
		return OdResult::eInvalidDrawing;
	}
}
