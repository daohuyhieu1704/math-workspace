#pragma once
#include <windows.h>
#include "DisposableWrapper.h"
#include "OdDrawingManager.h"
#include <nlohmann/json.hpp>

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Text::Json;
using namespace System::Text::Json::Nodes;

namespace MathGL {
	public ref class DrawingManager : DisposableWrapper
	{
		static DrawingManager^ m_instance;
		DrawingManager()
			: DisposableWrapper(IntPtr(OdDrawingManager::R().get()), true)
		{
		}

        JsonNode^ ConvertToJsonNode(const nlohmann::json& json) {
			Nullable<JsonNodeOptions> options{};
			auto node = gcnew JsonObject(options);
			for (auto& [key, value] : json.items())
			{
				if (value.is_object())
				{
					node->AsObject()->Add(gcnew String(key.c_str()), ConvertToJsonNode(value));
				}
				else if (value.is_array())
				{
					auto array = gcnew JsonArray();
					for (auto& item : value)
					{
						array->Add(ConvertToJsonNode(item));
					}
					node->AsObject()->Add(gcnew String(key.c_str()), array);
				}
				else if (value.is_number_integer())
				{
					node->AsObject()->Add(gcnew String(key.c_str()), value.get<int>());
				}
				else if (value.is_number_float())
				{
					node->AsObject()->Add(gcnew String(key.c_str()), value.get<float>());
				}
				else if (value.is_string())
				{
					node->AsObject()->Add(gcnew String(key.c_str()), gcnew String(value.get<std::string>().c_str()));
				}
				else if (value.is_boolean())
				{
					node->AsObject()->Add(gcnew String(key.c_str()), value.get<bool>());
				}
			}
			return node;
        }
	public:
		delegate IntPtr InitializeWindowDelegate(IntPtr parentHandle);
		property static DrawingManager^ Instance
		{
			DrawingManager^ get()
			{
				if (m_instance == nullptr)
					m_instance = gcnew DrawingManager();
				return m_instance;
			}
		}
		property JsonObject^ Entities
		{
			JsonObject^ get()
			{
				auto entities = GetImpObj()->getEntities();
				Nullable<JsonNodeOptions> options{};
				auto json = gcnew JsonObject(options);
				for (int i = 0; i < entities.size(); i++)
				{
					json->Add(i.ToString(), ConvertToJsonNode(GetImpObj()->m_json));
				}
				return json;
			}
		}

		IntPtr InitializeWindow(IntPtr parentHandle);
		int ProcessGLUTEvents();
	private:
		OdDrawingManager* GetImpObj()
		{
			return static_cast<OdDrawingManager*>(DisposableWrapper::GetImpObj());
		}
	};
}
