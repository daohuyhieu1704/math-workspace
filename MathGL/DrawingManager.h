#pragma once
#include <windows.h>
#include "DisposableWrapper.h"
#include "OdDrawingManager.h"
#include <nlohmann/json.hpp>
#include "Entity.h"

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
		property String^ EntityJson
		{
			String^ get()
			{
				return gcnew String(GetImpObj()->m_json.c_str());
			}
		}
		property String^ CurrentFilePath
		{
			String^ get()
			{
				return gcnew String(OdDrawingManager::R()->GetCurrentFilePath().c_str());
			}
		}

		property unsigned int CurrentSessionId
		{
			unsigned int get();
		}

		IntPtr InitializeWindow(IntPtr parentHandle);
		Entity^ getEntityById(unsigned int id);
		void removeEntity(unsigned int id);
		int ProcessGLUTEvents();
		int exitGLUT();
		void TLViewport();
		void TMViewport();
		void TRViewport();
		void MLViewport();
		void TMMViewport();
		void BMMViewport();
		void MRViewport();
		void BLViewport();
		void BMViewport();
		void BRViewport();
		List<String^>^ GetAllEntityJsons();
		void createSession(String^ fileName);
		void changeSession(unsigned int sessionId);
	private:
		OdDrawingManager* GetImpObj()
		{
			return static_cast<OdDrawingManager*>(DisposableWrapper::GetImpObj());
		}
	};
}
