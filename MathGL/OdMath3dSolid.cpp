#include "pch.h"
#include "OdMath3dSolid.h"
#include <opencascade/TopoDS_Wire.hxx>
#include <opencascade/TopoDS_Shape.hxx>
#include <opencascade/gp_Pnt.hxx>
#include <opencascade/BRepPrimAPI_MakeBox.hxx>
#include <opencascade/BRepMesh_IncrementalMesh.hxx>
#include <opencascade/TopExp_Explorer.hxx>
#include <opencascade/Poly_Triangulation.hxx>
#include <opencascade/BRep_Tool.hxx>
#include <opencascade/TopoDS.hxx>
#include <opencascade/gp_Pln.hxx>
#include <opencascade/BRepBuilderAPI_MakeWire.hxx>
#include <opencascade/BRepBuilderAPI_MakeEdge.hxx>
#include <opencascade/BRepBuilderAPI_MakeFace.hxx>
#include <opencascade/BRepPrimAPI_MakePrism.hxx>
#include <opencascade/BRepOffsetAPI_MakePipeShell.hxx>
#include <opencascade/BRepOffsetAPI_MakePipe.hxx>
#include <opencascade/BRepBuilderAPI_MakeShape.hxx>
#include <opencascade/BRepCheck_Analyzer.hxx>
#include "OdDrawingManager.h"
#include <MathLog.h>


OdMath3dSolid::OdMath3dSolid()
{
	setType(SolidType::Box);
    calculateVolume();
    calculateSurfaceArea();
}

OdBaseObjectPtr OdMath3dSolid::Clone()
{
    OdMath3dSolidPtr pSolid = OdMath3dSolid::createObject();

    pSolid->setScale(getScale());
    pSolid->setTransform(getTransform());
    pSolid->setName(getName());
    pSolid->setMaterial(getMaterial());
    pSolid->m_shape = m_shape;

    OdGeExtents3d newExtents;
    const auto& originalPoints = getExtents().getPoints();
    const auto& originalFaces = getExtents().getFaces();
	pSolid->getExtents().SetMinPnt(getExtents().GetMinPnt());
	pSolid->getExtents().SetMaxPnt(getExtents().GetMaxPnt());
    for (const auto& point : originalPoints) {
		pSolid->getExtents().appendPoint(point);
    }
    for (const auto& face : originalFaces) {
		std::vector<int> newFace;
		for (int idx : face) {
			newFace.push_back(idx);
		}
        pSolid->getExtents().appendFace(newFace);
    }

    return pSolid;
}


OdResult OdMath3dSolid::calculateVolume()
{
    return OdResult();
}

OdResult OdMath3dSolid::calculateSurfaceArea()
{
    return OdResult();
}

OdResult OdMath3dSolid::createBox(double x, double y, double z)
{
    try {
        TopoDS_Shape box = BRepPrimAPI_MakeBox(x, y, z).Shape();
        extractGeometry(box);
    }
    catch (const Standard_Failure& e) {
        std::cerr << "Error: " << e.GetMessageString() << std::endl;
        return OdResult::eInvalidDrawing;
    }
    return OdResult::eOk;
}

OdResult OdMath3dSolid::createExtrudeSolid(unsigned int entityId, double height, OdGeVector3d aXis)
{
	OdDbEntity* entity = static_cast<OdDbEntity*>(OdDrawingManager::R()->getEntityById(entityId).get());
	if (entity == nullptr) {
		return OdResult::eInvalidInput;
	}
	std::vector<OdGePoint3d> pnts = entity->getExtents().getPoints();
    try {
        if (pnts.size() < 3) {
            return OdResult::eInvalidInput;
        }
        if (pnts.front() != pnts.back()) {
            pnts.push_back(pnts.front());
        }

        // Create edges from points
        BRepBuilderAPI_MakeWire wireBuilder;
        for (size_t i = 0; i < pnts.size() - 1; ++i) {
            TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(
                gp_Pnt(pnts[i].x, pnts[i].y, pnts[i].z),
                gp_Pnt(pnts[i + 1].x, pnts[i + 1].y, pnts[i + 1].z)
            );
            wireBuilder.Add(edge);
			MathLog::LogFunction("Added edge to wire.", pnts[i], pnts[i + 1]);
        }

        if (!wireBuilder.IsDone()) {
            return OdResult::eInvalidInput;
        }

        TopoDS_Wire wire = wireBuilder.Wire();

        TopoDS_Face face = BRepBuilderAPI_MakeFace(wire);

        gp_Vec extrusionDir(aXis.x, aXis.y, aXis.z);
        extrusionDir.Normalize();
        extrusionDir.Multiply(height);

        TopoDS_Shape solid = BRepPrimAPI_MakePrism(face, extrusionDir);

        this->m_shape = solid;
        extractGeometry(solid);
        return OdResult::eOk;
    }
    catch (const Standard_Failure& e) {
        std::cerr << "Exception: " << e.GetMessageString() << std::endl;
        return OdResult::eInvalidDrawing;
    }
    catch (...) {
        std::cerr << "Unknown exception occurred during extrusion." << std::endl;
        return OdResult::eInvalidDrawing;
    }
}

OdResult OdMath3dSolid::createSweepSolid(unsigned int orgId, unsigned int pathId)
{
    try {
        // Step 1: Retrieve and validate the profile
        OdDbEntity* orgEntity = static_cast<OdDbEntity*>(OdDrawingManager::R()->getEntityById(orgId).get());
        if (!orgEntity) {
            return OdResult::eInvalidInput;
        }

        std::vector<OdGePoint3d> orgPoints = orgEntity->getExtents().getPoints();
        if (orgPoints.size() < 3) {
            return OdResult::eInvalidInput;
        }

        // Step 2: Retrieve and validate the path
        OdDbEntity* pathEntity = static_cast<OdDbEntity*>(OdDrawingManager::R()->getEntityById(pathId).get());
        if (!pathEntity) {
            return OdResult::eInvalidInput;
        }

        std::vector<OdGePoint3d> pathPoints = pathEntity->getExtents().getPoints();
        if (pathPoints.size() < 2) {
            return OdResult::eInvalidInput;
        }

        OdGeVector3d pathDir = pathPoints[1] - pathPoints[0];
        if (pathDir.Length() < 1e-9) {
            return OdResult::eInvalidInput;
        }
        pathDir = pathDir.normalize();
		OdGeVector3d globalUp = OdGeVector3d::kZAxis;

        if (fabs(pathDir.dotProduct(globalUp)) > 0.9999) {
            globalUp = OdGeVector3d::kXAxis;
        }

        OdGeVector3d yAxis = globalUp.crossProduct(pathDir).normalize();
        OdGeVector3d zAxis = pathDir.crossProduct(yAxis).normalize();


        OdGePoint3d origin = pathPoints[0];
        //OdGeMatrix3d transformToPathPlane;
        //transformToPathPlane.setCoordSystem(origin, pathDir, yAxis, zAxis);
        OdGeMatrix3d transformToPathPlane = OdGeMatrix3d::translation(pathPoints[0] - orgEntity->getExtents().getCenter());

        OdGeVector3d oldNormal(0, 0, 1);
        Quaternion3d rotQ;
        rotQ.setToRotateVectorToVector(oldNormal, pathDir, pathPoints[0]);
        for (auto& pt : orgPoints) {
            OdGePoint3d p(pt.x, pt.y, pt.z);
            p = rotQ * p.transformBy(transformToPathPlane);
            pt.x = p.x;
            pt.y = p.y;
            pt.z = p.z;
        }

        OdGeVector3d newDir = (orgPoints[0] - orgPoints[1]).crossProduct(orgPoints[0] - orgPoints[2]).normalize();

        // Ensure profile is planar
        gp_Pln profilePlane(gp_Pnt(orgPoints[0].x, orgPoints[0].y, orgPoints[0].z), gp_Dir(newDir.x, newDir.y, newDir.z));
        for (const auto& pt : orgPoints) {
            if (!profilePlane.Contains(gp_Pnt(pt.x, pt.y, pt.z), 1e-6)) {
                return OdResult::eInvalidInput;
            }
        }

        // Ensure the profile is closed
        if (orgPoints.front() != orgPoints.back()) {
            orgPoints.push_back(orgPoints.front());
        }

        // Create a profile wire
        BRepBuilderAPI_MakeWire profileWireBuilder;
        for (size_t i = 0; i < orgPoints.size() - 1; ++i) {
            profileWireBuilder.Add(BRepBuilderAPI_MakeEdge(
                gp_Pnt(orgPoints[i].x, orgPoints[i].y, orgPoints[i].z),
                gp_Pnt(orgPoints[i + 1].x, orgPoints[i + 1].y, orgPoints[i + 1].z)
            ));
        }

        if (!profileWireBuilder.IsDone()) {
            return OdResult::eInvalidInput;
        }

        TopoDS_Wire profileWire = profileWireBuilder.Wire();
        if (!BRepCheck_Analyzer(profileWire).IsValid()) {
            return OdResult::eInvalidInput;
        }

        // Create a path wire
        BRepBuilderAPI_MakeWire pathWireBuilder;
        for (size_t i = 0; i < pathPoints.size() - 1; ++i) {
            pathWireBuilder.Add(BRepBuilderAPI_MakeEdge(
                gp_Pnt(pathPoints[i].x, pathPoints[i].y, pathPoints[i].z),
                gp_Pnt(pathPoints[i + 1].x, pathPoints[i + 1].y, pathPoints[i + 1].z)
            ));
        }

        if (!pathWireBuilder.IsDone()) {
            return OdResult::eInvalidInput;
        }

        TopoDS_Wire pathWire = pathWireBuilder.Wire();
        if (!BRepCheck_Analyzer(pathWire).IsValid()) {
            return OdResult::eInvalidInput;
        }

        // Step 3: Sweep the profile along the path using Frenet trihedron (SetMode(true))
        BRepOffsetAPI_MakePipeShell pipeShell(pathWire);
        pipeShell.Add(profileWire, true);
		pipeShell.SetMode(true);
        pipeShell.Build();

        if (!pipeShell.IsDone()) {
            return OdResult::eInvalidDrawing;
        }

        pipeShell.MakeSolid();
        TopoDS_Shape sweptSolid = pipeShell.Shape();
        this->m_shape = sweptSolid;
        extractGeometry(sweptSolid);

        return OdResult::eOk;
    }
    catch (const Standard_Failure& e) {
        std::cerr << "Exception: " << e.GetMessageString() << std::endl;
        return OdResult::eInvalidDrawing;
    }
    catch (...) {
        std::cerr << "Unknown exception occurred during sweep solid creation." << std::endl;
        return OdResult::eInvalidDrawing;
    }
}

void OdMath3dSolid::extractGeometry(const TopoDS_Shape& shape)
{
    BRepMesh_IncrementalMesh mesh(shape, 0.1);
    getExtents().reset();
    for (TopExp_Explorer aFaceIter(shape, TopAbs_FACE); aFaceIter.More(); aFaceIter.Next()) {
        const TopoDS_Face& aFace = TopoDS::Face(aFaceIter.Current());
        std::vector<int> faceStorage;
        int oldSize = getExtents().pntSize();
        TopLoc_Location aLoc;
        const Handle(Poly_Triangulation)& aPolyTri = BRep_Tool::Triangulation(aFace, aLoc);
        if (aPolyTri.IsNull()) { continue; }

        for (int aTriIter = 1; aTriIter <= aPolyTri->NbTriangles(); ++aTriIter) {
            const Poly_Triangle& aTri = aPolyTri->Triangle(aTriIter);
            gp_Pnt aTriNodes[3] = {
                aPolyTri->Node(aTri(1)),
                aPolyTri->Node(aTri(2)),
                aPolyTri->Node(aTri(3))
            };

            for (int aNodeIter = 0; aNodeIter < 3; ++aNodeIter) {
                const gp_Pnt& aNode = aTriNodes[aNodeIter];
				OdGePoint3d transformPnt = OdGePoint3d(aNode.X(), aNode.Y(), aNode.Z());
                getExtents().appendPoint_s(transformPnt);
                faceStorage.push_back(oldSize++);
            }
        }
        getExtents().appendFace(faceStorage);
    }
}

OdResult OdMath3dSolid::draw() 
{
    glBegin(GL_TRIANGLES);
    glLoadName(id());
    for (const auto& face : getExtents().getFaces()) {
        for (int idx : face) {
            OdGePoint3d point = getExtents().getPoint(idx);
            OdGePoint3d transformPnt = point * m_scale * m_transform;
            OdGePoint3d transformPntRot = point.rotateBy(m_rotation);
            glVertex3d(point.x, point.y, point.z);
        }
    }
    glEnd();
    return OdResult::eOk;
}