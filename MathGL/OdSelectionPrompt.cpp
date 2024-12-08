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
    if (!OdHostAppService::R()->getCurrentSession())
        return OdResult::eInvalidContext;

    MathViewportPtr vp = MathViewport::R();
    // Ensure camera and projection are set up consistently as in drawScene()
    vp->applyCameraAndProjection();

    // Retrieve the current viewport, modelview, and projection matrices
    GLint viewport[4];
    GLdouble modelview[16], projection[16];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);

    GLfloat winX = static_cast<GLfloat>(x);
    GLfloat winY = static_cast<GLfloat>(viewport[3] - y);

    GLdouble rayStartX, rayStartY, rayStartZ;
    GLdouble rayEndX, rayEndY, rayEndZ;
    // Unproject the mouse position at z=0 (near plane)
    if (gluUnProject(winX, winY, 0.0, modelview, projection, viewport,
        &rayStartX, &rayStartY, &rayStartZ) != GL_TRUE) {
        return OdResult::eInvalidInput;
    }

    // Unproject the mouse position at z=1 (far plane)
    if (gluUnProject(winX, winY, 1.0, modelview, projection, viewport,
        &rayEndX, &rayEndY, &rayEndZ) != GL_TRUE) {
        return OdResult::eInvalidInput;
    }

    // Compute the ray direction
    GLdouble rayDirX = rayEndX - rayStartX;
    GLdouble rayDirY = rayEndY - rayStartY;
    GLdouble rayDirZ = rayEndZ - rayStartZ;
    GLdouble rayDirLength = std::sqrt(rayDirX * rayDirX + rayDirY * rayDirY + rayDirZ * rayDirZ);

    if (rayDirLength < 1e-14) {
        return OdResult::eInvalidInput;
    }

    // Normalize the ray direction
    rayDirX /= rayDirLength;
    rayDirY /= rayDirLength;
    rayDirZ /= rayDirLength;

    const auto& entities = OdHostAppService::R()->getCurrentSession()->getEntities();

    double tolerance = 1;
    GLdouble closestDistanceAlongRay = std::numeric_limits<GLdouble>::max();
    OdDbObjectId selectedEntityId = OdDbObjectId::kNull;

    // Perform intersection tests with each entity
    for (auto& entity : entities) {
        auto pEntity = static_cast<OdDbEntity*>(entity.get());
        auto vertices = pEntity->getExtents().getPoints();
        if (vertices.size() < 2) continue;

        GLdouble entityClosestT = std::numeric_limits<GLdouble>::max();
        bool entityHit = false;

        for (size_t i = 0; i < vertices.size() - 1; ++i) {
            OdGePoint3d A = vertices[i];
            OdGePoint3d B = vertices[i + 1];
            // Vector u = B - A (represents the direction and length of the segment)
            double ux = B.x - A.x;
            double uy = B.y - A.y;
            double uz = B.z - A.z;

            // Vector v = R0 - A (represents the vector from the segment start to the ray origin)
            double vx = rayStartX - A.x;
            double vy = rayStartY - A.y;
            double vz = rayStartZ - A.z;

            // Compute dot products for the required calculations
            double uDotU = ux * ux + uy * uy + uz * uz;               // Dot product of u with itself (length squared of the segment)
            double uDotRd = ux * rayDirX + uy * rayDirY + uz * rayDirZ; // Dot product of u and ray direction
            double vDotU = vx * ux + vy * uy + vz * uz;               // Dot product of v and u
            double vDotRd = vx * rayDirX + vy * rayDirY + vz * rayDirZ; // Dot product of v and ray direction

            // Calculate the denominator for solving s and t
            double denom = uDotU - uDotRd * uDotRd;
            if (fabs(denom) < 1e-14) {
                // If the denominator is very small, the ray and segment are nearly parallel
                // In such cases, skip further calculations for this segment
                continue;
            }

            // Solve for s (closest point on the segment) and t (closest point on the ray)
            double s = (vDotU - vDotRd * uDotRd) / denom;
            double t = (s * uDotRd - vDotRd);

            // Clamp s to the range [0,1] to ensure the closest point lies on the segment
            s = std::max(0.0, std::min(1.0, s));

            // If t is negative, the closest point on the ray is behind the ray's start point, so skip
            if (t < 0) continue;

            // Compute the closest point on the segment: C = A + s * u
            double Cx = A.x + s * ux;
            double Cy = A.y + s * uy;
            double Cz = A.z + s * uz;

            // Compute the closest point on the ray: R = R0 + t * Rd
            double Rx = rayStartX + t * rayDirX;
            double Ry = rayStartY + t * rayDirY;
            double Rz = rayStartZ + t * rayDirZ;

            // Calculate the distance between the closest points on the segment and the ray
            double dx = Cx - Rx;
            double dy = Cy - Ry;
            double dz = Cz - Rz;
            double dist = std::sqrt(dx * dx + dy * dy + dz * dz);

            // If the distance is within the specified tolerance, consider the ray intersecting the segment
            if (dist < tolerance) {
                entityHit = true; // Mark the entity as hit
                if (t < entityClosestT) {
                    entityClosestT = t; // Update the closest intersection along the ray
                }
            }
        }

        // Update the closest entity if this one is closer along the ray
        if (entityHit && entityClosestT < closestDistanceAlongRay) {
            closestDistanceAlongRay = entityClosestT;
            selectedEntityId = pEntity->getObjectId();
        }
    }

    // Deselect all first
    for (auto& entity : entities) {
        static_cast<OdDbEntity*>(entity.get())->setSelected(false);
    }

    // Select the closest entity
    for (auto& entity : entities) {
        if (entity->getObjectId() == selectedEntityId) {
            static_cast<OdDbEntity*>(entity.get())->setSelected(true);
            std::string jsonString = static_cast<OdDbEntity*>(entity.get())->toJson().dump();
            OdDrawingManager::R()->m_json = jsonString;
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
