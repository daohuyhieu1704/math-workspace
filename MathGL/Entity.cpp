#include "pch.h"
#include "Entity.h"
#include "OdDrawingManager.h"
#include <MathLog.h>
#include <nlohmann/json.hpp>

namespace MathGL
{
    Scale3d Entity::Scale::get()
    {
		OdGeScale3d scale = GetImpObj()->getScale();
		return Scale3d(scale.sx, scale.sy, scale.sz);
    }
    void Entity::Scale::set(Scale3d value)
    {
		OdGeScale3d scale(value.XFactor, value.YFactor, value.ZFactor);
        GetImpObj()->setScale(scale);
    }
    Point3d Entity::Position::get()
    {
		OdGePoint3d position = GetImpObj()->getPosition();
		return Point3d(position.x, position.y, position.z);
    }
    void Entity::Position::set(Point3d value)
    {
		OdGePoint3d position(value.X, value.Y, value.Z);
		GetImpObj()->setPosition(position);
    }
    Vector3d Entity::XDir::get()
    {
		OdGeVector3d xDir = GetImpObj()->getXDir();
		return Vector3d(xDir.x, xDir.y, xDir.z);
    }
    void Entity::XDir::set(Vector3d value)
    {
		OdGeVector3d xDir(value.X, value.Y, value.Z);
		GetImpObj()->setXDir(xDir);
    }
    Vector3d Entity::YDir::get()
    {
        OdGeVector3d yDir = GetImpObj()->getYDir();
        return Vector3d(yDir.x, yDir.y, yDir.z);
    }
    void Entity::YDir::set(Vector3d value)
    {
        OdGeVector3d yDir(value.X, value.Y, value.Z);
        GetImpObj()->setYDir(yDir);
    }
    Vector3d Entity::ZDir::get()
    {
        OdGeVector3d zDir = GetImpObj()->getZDir();
        return Vector3d(zDir.x, zDir.y, zDir.z);
    }
    void Entity::ZDir::set(Vector3d value)
    {
        OdGeVector3d zDir(value.X, value.Y, value.Z);
        GetImpObj()->setZDir(zDir);
    }
    unsigned int Entity::Create(String^ desc)
    {
        std::string descStr = UtilCLI::convertToStdString(desc);
        if (!OdHostAppService::R()->getCurrentSession()) return 0;
        return OdHostAppService::R()->getCurrentSession()->appendEntity(OdObjectFactory::createObject(descStr));
    }
    MathResult Entity::TransformBy(Matrix3d xform)
    {
        OdGeMatrix3d nativeXform = OdGeMatrix3d::kIdentity;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				nativeXform[i][j] = xform.Entries[i, j];
			}
		}
		return MathResult(GetImpObj()->transformBy(nativeXform));
    }
    String^ Entity::ToJson()
    {
		json j = GetImpObj()->toJson();
		return gcnew String(j.dump().c_str());
    }
    unsigned int Entity::FromJson(String^ jsonStr)
    {
        if (!OdHostAppService::R()->getCurrentSession()) return 0;
        try
        {
            std::string strJson = msclr::interop::marshal_as<std::string>(jsonStr);
            json j = json::parse(strJson);
            std::string type = j["type"];
            OdBaseObjectPtr obj = OdObjectFactory::createObject(type);
            if (static_cast<OdDbEntity*>(obj.get()))
            {
                static_cast<OdDbEntity*>(obj.get())->fromJson(j);
            }

            return OdHostAppService::R()->getCurrentSession()->appendEntity(obj->Clone());
        }
		catch (const std::exception& e)
		{
			MathLog::LogFunction("Error in Entity::FromJson: " + std::string(e.what()));
			return 0;
		}
    }
    void Entity::FromJson2(String^ json)
    {
		try
		{
			std::string strJson = UtilCLI::convertToStdString(json);
            nlohmann::json j = json::parse(strJson);
			GetImpObj()->fromJson(j);
		}
		catch (const std::exception& e)
        {
			MathLog::LogFunction("Error in Entity::FromJson2");
        }
    }
    unsigned int Entity::Draw()
    {
        if (!OdHostAppService::R()->getCurrentSession()) return 0;
        return OdHostAppService::R()->getCurrentSession()->appendEntity(GetImpObj()->Clone());
    }

    Matrix3d Entity::Transform::get()
    {
		OdGeMatrix3d transform = GetImpObj()->getTransform();
        Matrix3d retVal = Matrix3d::Identity();
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				retVal.Entries[i, j] = transform[i][j];
			}
		}
		return retVal;
    }
    bool Entity::IsVisible::get()
    {
		return GetImpObj()->isVisible();
    }
    void Entity::IsVisible::set(bool value)
    {
		GetImpObj()->setVisible(value);
    }
    bool Entity::IsSelected::get()
    {
		return GetImpObj()->isSelected();
    }
    void Entity::IsSelected::set(bool value)
    {
		GetImpObj()->setSelected(value);
    }
    Extents3d Entity::Extents::get()
    {
		OdGeExtents3d extents = GetImpObj()->getExtents();
		Point3d minPnt = Point3d(extents.GetMinPnt().x, extents.GetMinPnt().y, extents.GetMinPnt().z);
		Point3d maxPnt = Point3d(extents.GetMaxPnt().x, extents.GetMaxPnt().y, extents.GetMaxPnt().z);
		Extents3d result = Extents3d(minPnt, maxPnt);
		return result;
    }
}
