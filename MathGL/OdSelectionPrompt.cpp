#include "pch.h"
#include "OdSelectionPrompt.h"
#include "MathViewport.h"
#include "OdDrawingManager.h"
#include "OdPointPrompt.h"
#include "OdSelectionManager.h"
#include <MathLog.h>

OD_RTTI_DEFINE(OdSelectionPrompt, AbstractSelectionPrompt)

bool OdSelectionPrompt::m_endPicked = false;
int OdSelectionPrompt::m_totalPick = 0;
std::vector<OdDbObjectId> OdSelectionPrompt::m_ents;
OdDbObjectId OdSelectionPrompt::m_ent;

OdSelectionPrompt::OdSelectionPrompt()
{
}

OdResult OdSelectionPrompt::pickObjects(int x, int y) {
    GLint viewport[4];
    GLdouble modelview[16], projection[16];
    GLdouble rayStartX, rayStartY, rayStartZ;
    GLdouble rayEndX, rayEndY, rayEndZ;

    glGetIntegerv(GL_VIEWPORT, viewport);
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);

    GLfloat winX = static_cast<float>(x);
    GLfloat winY = static_cast<float>(viewport[3] - y);

    gluUnProject(winX, winY, 0.0, modelview, projection, viewport, &rayStartX, &rayStartY, &rayStartZ);
    gluUnProject(winX, winY, 1.0, modelview, projection, viewport, &rayEndX, &rayEndY, &rayEndZ);

    GLdouble rayDirX = rayEndX - rayStartX;
    GLdouble rayDirY = rayEndY - rayStartY;
    GLdouble rayDirZ = rayEndZ - rayStartZ;
    GLdouble rayDirLength = std::sqrt(rayDirX * rayDirX + rayDirY * rayDirY + rayDirZ * rayDirZ);

    rayDirX /= rayDirLength;
    rayDirY /= rayDirLength;
    rayDirZ /= rayDirLength;

    const auto& entities = OdDrawingManager::R()->getEntities();
    GLdouble closestDistance = std::numeric_limits<GLdouble>::max();
    OdDbObjectId selectedEntityId = OdDbObjectId::kNull;

    for (auto& entity : entities) {
        GLdouble intersectionDistance = std::numeric_limits<GLdouble>::max();
        if (static_cast<OdDbEntity*>(entity.get())->intersectWithRay(
            rayStartX, rayStartY, rayStartZ,
            rayDirX, rayDirY, rayDirZ,
            intersectionDistance)) {
            if (intersectionDistance < closestDistance) {
                closestDistance = intersectionDistance;
                selectedEntityId = entity->getObjectId();
				// MathLog::LogFunction("Selected entity: " + std::to_string(selectedEntityId.GetObjectId()));
            }
        }
    }

    for (auto& entity : entities) {
        if (entity->getObjectId() == selectedEntityId)
        {
            static_cast<OdDbEntity*>(entity.get())->setSelected(true);
            std::string jsonString = static_cast<OdDbEntity*>(entity.get())->toJson().dump();
            OdDrawingManager::R()->m_json = jsonString;
            // MathLog::LogFunction("Append entity: " + std::to_string(selectedEntityId.GetObjectId()));
        }
    }
    AppendId(selectedEntityId);

    glutPostRedisplay();
    return OdResult::eOk;
}


OdDbObjectId OdSelectionPrompt::getObjectId()
{
    return OdDbObjectId();
}

void OdSelectionPrompt::resetWorldMouse(int x, int y)
{
    GLint viewport[4];
    GLdouble modelview[16], projection[16];
    GLdouble posX, posY, posZ;

    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    GLdouble rayStartX, rayStartY, rayStartZ;
    GLdouble rayEndX, rayEndY, rayEndZ;

    GLfloat winX = (float)x;
    GLfloat winY = (float)(viewport[3] - y);

    gluUnProject(winX, winY, 0.0, modelview, projection, viewport, &rayStartX, &rayStartY, &rayStartZ);
    gluUnProject(winX, winY, 1.0, modelview, projection, viewport, &rayEndX, &rayEndY, &rayEndZ);

    GLdouble dirX = rayEndX - rayStartX;
    GLdouble dirY = rayEndY - rayStartY;
    GLdouble dirZ = rayEndZ - rayStartZ;

    if (dirZ != 0.0)
    {
        double t = -rayStartZ / dirZ;
        posX = rayStartX + t * dirX;
        posY = rayStartY + t * dirY;
        posZ = 0.0;
    }
    else
    {
        posX = rayStartX;
        posY = rayStartY;
        posZ = rayStartZ;
    }

    OdPointPrompt::AppendPoint(OdGePoint3d(posX, posY, posZ));
}

OdBaseObjectPtr OdSelectionPrompt::Clone()
{
	OdSelectionPromptPtr clone = OdSelectionPrompt::createObject();
	return clone;
}

void OdSelectionPrompt::Focus()
{
}

void OdSelectionPrompt::AppendId(const OdDbObjectId& id)
{
    m_ents.push_back(id);
	m_ent = id;
    MathLog::LogFunction("Append Id: " + std::to_string(id.GetObjectId()));
    if (m_ents.size() == m_totalPick) OdDrawingManager::R()->TriggerEntityPicked(m_ents);
}


OdDbObjectId OdSelectionPrompt::LastId()
{
	return m_ent;
}

void OdSelectionPrompt::Clear()
{
	m_ents.clear();
	m_ent = OdDbObjectId();
}

void OdSelectionPrompt::TotalPick(int total)
{
	m_totalPick = total;
}

void OdSelectionPrompt::SetEntityPicked(bool picked)
{
	m_endPicked = picked;
}
