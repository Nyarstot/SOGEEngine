#include "sogepch.hpp"
#include "SOGE/Graphics/DebugSystem/GraphicsThrowMacroses.hpp"
#include "SOGE/Graphics/DebugSystem/WindowThrowMacroses.hpp"

namespace soge
{
	DXGIInfoManager* DXGIInfoManager::sInstance = nullptr;
	DXGIInfoManager* DXGIInfoManager::GetInstance()
	{
		if (sInstance == nullptr) {
			sInstance = new DXGIInfoManager();
			sInstance->Set();
		}

		return sInstance;
	}

    DXGIInfoManager::DXGIInfoManager()
    {
		// define function signature of DXGIGetDebugInterface
		typedef HRESULT(WINAPI* DXGIGetDebugInterface)(REFIID, void**);

		// load the dll that contains the function DXGIGetDebugInterface
		const auto hModDxgiDebug = LoadLibraryEx(L"dxgidebug.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
		if (hModDxgiDebug == nullptr)
		{
			throw CHWND_LAST_EXCEPT();
		}

		// get address of DXGIGetDebugInterface in dll
		const auto DxgiGetDebugInterface = reinterpret_cast<DXGIGetDebugInterface>(
			reinterpret_cast<void*>(GetProcAddress(hModDxgiDebug, "DXGIGetDebugInterface"))
			);
		if (DxgiGetDebugInterface == nullptr)
		{
			throw CHWND_LAST_EXCEPT();
		}

		HRESULT hr;
		GFX_THROW_NOINFO(DxgiGetDebugInterface(__uuidof(IDXGIInfoQueue), &pDxgiInfoQueue));
    }

    void DXGIInfoManager::Set() noexcept
    {
		// set the index (next) so that the next all to GetMessages()
		// will only get errors generated after this call
		next = pDxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
    }

    std::vector<std::string> DXGIInfoManager::GetMessages() const
    {
		std::vector<std::string> messages;
		const auto end = pDxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
		for (auto i = next; i < end; i++)
		{
			HRESULT hr;
			SIZE_T messageLength = 0;
			// get the size of message i in bytes
			GFX_THROW_NOINFO(pDxgiInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, nullptr, &messageLength));
			// allocate memory for message
			auto bytes = std::make_unique<byte[]>(messageLength);
			auto pMessage = reinterpret_cast<DXGI_INFO_QUEUE_MESSAGE*>(bytes.get());
			// get the message and push its description into the vector
			GFX_THROW_NOINFO(pDxgiInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, pMessage, &messageLength));
			messages.emplace_back(pMessage->pDescription);
		}

		return messages;
    }

}