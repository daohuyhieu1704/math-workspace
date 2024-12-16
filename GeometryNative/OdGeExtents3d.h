#pragma once
#include "OdGePoint3d.h"
#include <vector>

namespace GeometryNative
{
#define INVALIDEXTENTS 1e20
    class OdGeExtents3d
    {
    private:
        OdGePoint3d m_min = OdGePoint3d(FLT_MAX, FLT_MAX, FLT_MAX);
        OdGePoint3d m_max = OdGePoint3d(FLT_MIN, FLT_MIN, FLT_MIN);
		std::vector<OdGePoint3d> m_points;
        std::vector<std::vector<int>> m_faces;
    public:
		void appendPoint(const OdGePoint3d& point);
        static const OdGeExtents3d kInvalid;
        OdGeExtents3d();
        OdGeExtents3d(OdGePoint3d minPnt, OdGePoint3d maxPnt)
            : m_min(minPnt), m_max(maxPnt) {}

        ~OdGeExtents3d() {}
        const OdGePoint3d& operator[] (int iIndex) const {
            return iIndex == 0 ? m_min : m_max;
        }
        OdGePoint3d& operator[] (int iIndex) {
            return iIndex == 0 ? m_min : m_max;
        }
        OdGePoint3d getPoint(int index)
		{
			return m_points[index];
        }
        std::vector<OdGePoint3d> getPoints()
        {
            std::vector<OdGePoint3d> retVal;
            for (OdGePoint3d pnt : m_points)
            {
                retVal.push_back(pnt);
            }
            return retVal;
        }
        std::vector<std::vector<int>> getFaces()
		{
            std::vector<std::vector<int>> retVal;
            for (std::vector<int> face : m_faces)
            {
				std::vector<int> faceCopy;
                for (int idx : face)
                {
                    faceCopy.push_back(idx);
                }
				retVal.push_back(faceCopy);
            }
			return retVal;
		}
#pragma region Properties

        OdGePoint3d GetMinPnt() const { return m_min; }
        void SetMinPnt(OdGePoint3d minPnt) { m_min = minPnt; }

        OdGePoint3d GetMaxPnt() const { return m_max; }
        void SetMaxPnt(OdGePoint3d maxPnt) { m_max = maxPnt; }
        void set(
            const OdGePoint3d& min,
            const OdGePoint3d& max);
        OdGeExtents3d& appendPoint_s(OdGePoint3d point);
        inline bool isValidExtents() const
        {
            return ((m_max.x >= m_min.x) && (m_max.y >= m_min.y) && (m_max.z >= m_min.z));
        }
        void expandBy(
            const OdGeVector3d& vect);
		void appendFace(
			const std::vector<int>& face);
#pragma endregion
		double getRadius() const;
        OdGePoint3d getCenter() const;
        void reset();
        int pntSize() const;
    };
}
