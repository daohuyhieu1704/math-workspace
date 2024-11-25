#include "pch.h"
#include "OdSelectionPrompt.h"
#include "MathViewport.h"
#include "OdDrawingManager.h"
#include "OdPointPrompt.h"

OD_RTTI_DEFINE(OdSelectionPrompt, AbstractSelectionPrompt)
OD_RTTI_SINGLETON_DEFINE(OdSelectionPrompt)

OdSelectionPrompt::OdSelectionPrompt()
{
}

OdResult OdSelectionPrompt::pickObjects(int x, int y)
{
    GLuint selectBuf[512];
    GLint hits, viewport[4];
    double windowWidth = MathViewport::R()->win_width;
    double windowHeight = MathViewport::R()->win_height;
    glGetIntegerv(GL_VIEWPORT, viewport);

    glSelectBuffer(512, selectBuf);
    glRenderMode(GL_SELECT);

    glInitNames();
    glPushName(0); // Ensure m_name stack is not empty

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    gluPickMatrix(x, viewport[3] - y, 5.0, 5.0, viewport);
    gluPerspective(45.0, windowWidth / windowHeight, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    MathViewport::R()->setCamera();

    // Render entities with names
    OdDrawingManager::R()->renderAll();

    glPopName(); // Pop the initial m_name off the stack

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    hits = glRenderMode(GL_RENDER);

    // Clear selection status of all entities
    const auto& entities = OdDrawingManager::R()->getEntities();
    for (auto& obj : entities) {
        OdDbEntity* entity = static_cast<OdDbEntity*>(obj.get());
        if (entity) {
            entity->setSelected(false);
        }
    }

    if (hits > 0)
    {
        GLuint* ptr = selectBuf;
        for (int i = 0; i < hits; ++i)
        {
            GLuint numNames = *ptr++;
            GLuint minZ = *ptr++;
            GLuint maxZ = *ptr++;
            GLuint m_name = 0;
            if (numNames > 0)
            {
                m_name = *ptr;
                ptr += numNames;
            }
            else
            {
                continue;
            }

            for (const OdBaseObjectPtr& obj : entities)
            {
                OdDbEntity* entity = static_cast<OdDbEntity*>(obj.get());
                if (entity && entity->id() == m_name)
                {
                    entity->setSelected(true);
                    OdDrawingManager::R()->m_json = entity->toJson();
                    break;
                }
            }
        }
    }

    glutPostRedisplay();
    return OdResult::eOk;
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
	return OdBaseObjectPtr();
}
