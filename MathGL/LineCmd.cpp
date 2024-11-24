#include "pch.h"
#include "LineCmd.h"
#include "OdDrawingManager.h"
#include "OdMathLine.h"

OdBaseObjectPtr LineCmd::Clone()
{
	LineCmdPtr pCmd = LineCmd::createObject();
    return pCmd;
}

bool LineCmd::execute()
{
	//OdMathLinePtr line = OdMathLine::createObject();
 //   line->setStartPnt(startPnt);
 //   line->setEndPnt(endPnt);
 //   OdDrawingManager::R()->appendEntity(line);
    return true;
}

bool LineCmd::serialize(const std::vector<std::string>& strData)
{
    try
    {
        if (strData.size() < 3)
        {
            return false;
        }
        std::vector<std::string> point1Coords = CommandPrompt::split(strData[1], ',');
        std::vector<std::string> point2Coords = CommandPrompt::split(strData[2], ',');

        if (point1Coords.size() != 3 || point2Coords.size() != 3)
        {
            return false;
        }

        startPnt =
        {
        std::stof(point1Coords[0]),
        std::stof(point1Coords[1]),
        std::stof(point1Coords[2])
        };

        endPnt =
        {
            std::stof(point2Coords[0]),
            std::stof(point2Coords[1]),
            std::stof(point2Coords[2])
        };

        return true;
    }
	catch (const std::exception&)
	{
		return false;
	}
}
