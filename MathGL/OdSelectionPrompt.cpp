#include "pch.h"
#include "OdSelectionPrompt.h"
#include "MathViewport.h"
#include "OdDrawingManager.h"

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
    glPushName(0); // Ensure name stack is not empty

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

    glPopName(); // Pop the initial name off the stack

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
            GLuint name = 0;
            if (numNames > 0)
            {
                name = *ptr;
                ptr += numNames;
            }
            else
            {
                continue;
            }

            for (const OdBaseObjectPtr& obj : entities)
            {
                OdDbEntity* entity = static_cast<OdDbEntity*>(obj.get());
                if (entity && entity->id() == name)
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

OdBaseObjectPtr OdSelectionPrompt::Clone()
{
	return OdBaseObjectPtr();
}
