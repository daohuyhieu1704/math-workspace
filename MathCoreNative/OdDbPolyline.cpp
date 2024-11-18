#include "pch.h"
#include "OdDbPolyline.h"

void OdDbPolyline::addVertex(const OdGePoint2d& vertex, double bulge)
{
    m_vertices.emplace_back(vertex, bulge);
}

OdGePoint3d OdDbPolyline::getVertexAt(int index) const
{
    if (index < 0 || index >= static_cast<int>(m_vertices.size())) {
        throw std::out_of_range("Index is out of range");
    }
    const auto& vertex2d = m_vertices[index].first;
    return OdGePoint3d(vertex2d.x, vertex2d.y, 0.0);
}

double OdDbPolyline::getBulgeAt(int index) const
{
    if (index < 0 || index >= static_cast<int>(m_vertices.size())) {
        throw std::out_of_range("Index is out of range");
    }
    return m_vertices[index].second;
}

int OdDbPolyline::numVertices() const
{
    return static_cast<int>(m_vertices.size());
}

OdBaseObjectPtr OdDbPolyline::Clone()
{
	OdDbPolylinePtr pClone = OdDbPolyline::createObject();
	std::vector<std::pair<OdGePoint2d, double>> verticesClone;
	for (const auto& vertex : m_vertices) {
        OdGePoint2d vertexClone = std::get<0>(vertex);
		double bulge = std::get<1>(vertex);
		verticesClone.push_back(std::make_pair(OdGePoint2d(vertexClone.x, vertexClone.y), bulge));
	}
    return pClone;
}

OdResult OdDbPolyline::draw() const
{
    return OdResult::eNotImplementedYet;
}

OdGeExtents3d OdDbPolyline::boundingBox() const
{
	return getExtents();
}

OdResult OdDbPolyline::worldDraw() const
{
    return OdResult::eNotImplementedYet;
}
