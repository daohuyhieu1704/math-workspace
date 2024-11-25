#include "pch.h"
#include "OdMath3dSolid.h"
#include <opencascade/BRepPrimAPI_MakeBox.hxx>
#include <opencascade/BRepMesh_IncrementalMesh.hxx>
#include <opencascade/TopExp_Explorer.hxx>
#include <opencascade/Poly_Triangulation.hxx>
#include <opencascade/BRep_Tool.hxx>
#include <opencascade/gp_Pnt.hxx>
#include <opencascade/TopoDS.hxx>


OdMath3dSolid::OdMath3dSolid()
{
	setType(SolidType::Box);
    calculateVolume();
    calculateSurfaceArea();
}

OdBaseObjectPtr OdMath3dSolid::Clone()
{
	OdMath3dSolidPtr pSolid = OdMath3dSolid::createObject();
	pSolid->setName(getName());
	pSolid->setMaterial(getMaterial());
	pSolid->m_shape = m_shape;
	return pSolid;
	return OdBaseObjectPtr();
}

OdResult OdMath3dSolid::calculateVolume()
{
    return OdResult();
}

OdResult OdMath3dSolid::calculateSurfaceArea()
{
    return OdResult();
}

OdResult OdMath3dSolid::drawBox() const
{
    try {
        TopoDS_Shape box = BRepPrimAPI_MakeBox(1.0, 5.0, 1.0).Shape();

        BRepMesh_IncrementalMesh mesh(box, 0.01);

        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_DEPTH_TEST);

        GLfloat light_position[] = { 1.0f, 1.0f, 1.0f, 0.0f };
        GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };

        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

        GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
        GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat mat_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
        GLfloat mat_shininess[] = { 50.0f };

        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

        for (TopExp_Explorer aFaceIter(box, TopAbs_FACE);
            aFaceIter.More(); aFaceIter.Next())
        {
            const TopoDS_Face& aFace = TopoDS::Face(aFaceIter.Current());
            TopLoc_Location aLoc;
            const Handle(Poly_Triangulation)& aPolyTri =
                BRep_Tool::Triangulation(aFace, aLoc);
            if (aPolyTri.IsNull()) { continue; } // error
            for (int aTriIter = 1; aTriIter <= aPolyTri->NbTriangles(); ++aTriIter)
            {
                glBegin(GL_TRIANGLES);
                const Poly_Triangle& aTri = aPolyTri->Triangle(aTriIter);
                gp_Pnt aTriNodes[3] = {
                    aPolyTri->Node(aTri(1)),
                    aPolyTri->Node(aTri(2)),
                    aPolyTri->Node(aTri(3))
                };

                gp_Vec v1(aTriNodes[0], aTriNodes[1]);
                gp_Vec v2(aTriNodes[0], aTriNodes[2]);
                gp_Vec normal = v1.Crossed(v2);
                normal.Normalize();

                glNormal3d(normal.X(), normal.Y(), normal.Z());

                for (int aNodeIter = 0; aNodeIter < 3; ++aNodeIter)
                {
                    const gp_Pnt& aNode = aTriNodes[aNodeIter];
                    glVertex3d(aNode.X(), aNode.Y(), aNode.Z());
                }
                glEnd();
            }

        }
    }
    catch (const Standard_Failure& e) {
        std::cerr << "Error: " << e.GetMessageString() << std::endl;
        return OdResult::eInvalidDrawing;
    }
    return OdResult::eOk;
}

OdResult OdMath3dSolid::draw() const
{
	try {
		switch (getType()) {
		case SolidType::Box:
            return drawBox();
			break;
		case SolidType::Cylinder:
			break;
		case SolidType::Cone:
			break;
		case SolidType::Sphere:
			break;
		case SolidType::Torus:
			break;
		case SolidType::Prism:
			break;
		case SolidType::Pyramid:
			break;
		case SolidType::Extrusion:
			break;
		case SolidType::Revolution:
			break;
		default:
			break;
		}
    }
    catch (const Standard_Failure& e) {
        std::cerr << "Error: " << e.GetMessageString() << std::endl;
        return OdResult::eNotApplicable;
    }
    return OdResult::eOk;
}