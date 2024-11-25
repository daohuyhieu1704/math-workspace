#include "pch.h"
#include "OdDbPolyline.h"

OdDbPolyline::OdDbPolyline()
{
}

void OdDbPolyline::addVertex(const OdGePoint3d& vertex, double bulge)
{
    m_vertices.emplace_back(vertex, bulge);
}

OdGePoint3d OdDbPolyline::getVertexAt(int index) const {
	if (index < 0 || index >= static_cast<int>(m_vertices.size())) {
		throw std::out_of_range("Index is out of range");
	}
	return m_vertices[index].first;
}

double OdDbPolyline::getBulgeAt(int index) const {
	if (index < 0 || index >= static_cast<int>(m_vertices.size())) {
		throw std::out_of_range("Index is out of range");
	}
	return m_vertices[index].second;
}

int OdDbPolyline::numVertices() const {
	return static_cast<int>(m_vertices.size());
}

OdBaseObjectPtr OdDbPolyline::Clone() {
	OdDbPolylinePtr pClone = OdDbPolyline::createObject();
	for (const auto& vertex : m_vertices) {
		pClone->addVertex(vertex.first, vertex.second);
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

json OdDbPolyline::toJson() const
{
	json j = OdDbEntity::toJson();
	json vertices = json::array();
	for (const auto& vertex : m_vertices) {
		json vertexJson = {
			{"x", std::get<0>(vertex).x},
			{"y", std::get<0>(vertex).y},
			{"z", std::get<0>(vertex).z},
			{"bulge", std::get<1>(vertex)}
		};
		vertices.push_back(vertexJson);
	}
	j["vertices"] = vertices;
	return j;
}

void OdDbPolyline::fromJson(const json& j)
{
	OdDbEntity::fromJson(j);
	if (j.contains("vertices")) {
		m_vertices.clear();
		for (const auto& vertex : j.at("vertices")) {
			OdGePoint3d vertex2d(
				vertex.at("x").get<double>(),
				vertex.at("y").get<double>(),
				vertex.at("z").get<double>()
			);
			double bulge = vertex.at("bulge").get<double>();
			m_vertices.push_back(std::make_pair(vertex2d, bulge));
		}
	}
}
