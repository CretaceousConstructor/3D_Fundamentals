/******************************************************************************************
*	Chili DirectX Framework Version 16.10.01											  *
*	Graphics.cpp																		  *
*	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#include "MainWindow.h"
#include "Graphics.h"
#include "DXErr.h"
#include "ChiliException.h"
#include <assert.h>
#include <string>
#include <array>
#include <functional>

// Ignore the intellisense error "cannot open source file" for .shh files.
// They will be created during the build sequence before the preprocessor runs.
namespace FramebufferShaders
{
#include "FramebufferPS.shh"
#include "FramebufferVS.shh"
}

#pragma comment( lib,"d3d11.lib" )

using Microsoft::WRL::ComPtr;

Graphics::Graphics(HWNDKey& key)
	:
	sysBuffer(ScreenWidth, ScreenHeight)
{
	assert(key.hWnd != nullptr);

	//////////////////////////////////////////////////////
	// create device and swap chain/get render target view
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferCount = 1;
	sd.BufferDesc.Width = Graphics::ScreenWidth;
	sd.BufferDesc.Height = Graphics::ScreenHeight;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 1;
	sd.BufferDesc.RefreshRate.Denominator = 60;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = key.hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	D3D_FEATURE_LEVEL	featureLevelsRequested = D3D_FEATURE_LEVEL_9_1;
	UINT				numLevelsRequested = 1;
	D3D_FEATURE_LEVEL	featureLevelsSupported;
	HRESULT				hr;
	UINT				createFlags = 0u;
#ifdef _DEBUG
#ifdef USE_DIRECT3D_DEBUG_RUNTIME
	createFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
#endif

	// create device and front/back buffers
	if (FAILED(hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		createFlags,
		&featureLevelsRequested,
		numLevelsRequested,
		D3D11_SDK_VERSION,
		&sd,
		&pSwapChain,
		&pDevice,
		&featureLevelsSupported,
		&pImmediateContext)))
	{
		throw CHILI_GFX_EXCEPTION(hr, L"Creating device and swap chain");
	}

	// get handle to backbuffer
	ComPtr<ID3D11Resource> pBackBuffer;
	if (FAILED(hr = pSwapChain->GetBuffer(
		0,
		__uuidof(ID3D11Texture2D),
		(LPVOID*)&pBackBuffer)))
	{
		throw CHILI_GFX_EXCEPTION(hr, L"Getting back buffer");
	}

	// create a view on backbuffer that we can render to
	if (FAILED(hr = pDevice->CreateRenderTargetView(
		pBackBuffer.Get(),
		nullptr,
		&pRenderTargetView)))
	{
		throw CHILI_GFX_EXCEPTION(hr, L"Creating render target view on backbuffer");
	}


	// set backbuffer as the render target using created view
	pImmediateContext->OMSetRenderTargets(1, pRenderTargetView.GetAddressOf(), nullptr);


	// set viewport dimensions
	D3D11_VIEWPORT vp;
	vp.Width = float(Graphics::ScreenWidth);
	vp.Height = float(Graphics::ScreenHeight);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	pImmediateContext->RSSetViewports(1, &vp);


	///////////////////////////////////////
	// create texture for cpu render target
	D3D11_TEXTURE2D_DESC sysTexDesc;
	sysTexDesc.Width = Graphics::ScreenWidth;
	sysTexDesc.Height = Graphics::ScreenHeight;
	sysTexDesc.MipLevels = 1;
	sysTexDesc.ArraySize = 1;
	sysTexDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sysTexDesc.SampleDesc.Count = 1;
	sysTexDesc.SampleDesc.Quality = 0;
	sysTexDesc.Usage = D3D11_USAGE_DYNAMIC;
	sysTexDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	sysTexDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	sysTexDesc.MiscFlags = 0;
	// create the texture
	if (FAILED(hr = pDevice->CreateTexture2D(&sysTexDesc, nullptr, &pSysBufferTexture)))
	{
		throw CHILI_GFX_EXCEPTION(hr, L"Creating sysbuffer texture");
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = sysTexDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	// create the resource view on the texture
	if (FAILED(hr = pDevice->CreateShaderResourceView(pSysBufferTexture.Get(),
		&srvDesc, &pSysBufferTextureView)))
	{
		throw CHILI_GFX_EXCEPTION(hr, L"Creating view on sysBuffer texture");
	}


	////////////////////////////////////////////////
	// create pixel shader for framebuffer
	// Ignore the intellisense error "namespace has no member"
	if (FAILED(hr = pDevice->CreatePixelShader(
		FramebufferShaders::FramebufferPSBytecode,
		sizeof(FramebufferShaders::FramebufferPSBytecode),
		nullptr,
		&pPixelShader)))
	{
		throw CHILI_GFX_EXCEPTION(hr, L"Creating pixel shader");
	}


	/////////////////////////////////////////////////
	// create vertex shader for framebuffer
	// Ignore the intellisense error "namespace has no member"
	if (FAILED(hr = pDevice->CreateVertexShader(
		FramebufferShaders::FramebufferVSBytecode,
		sizeof(FramebufferShaders::FramebufferVSBytecode),
		nullptr,
		&pVertexShader)))
	{
		throw CHILI_GFX_EXCEPTION(hr, L"Creating vertex shader");
	}


	//////////////////////////////////////////////////////////////
	// create and fill vertex buffer with quad for rendering frame
	const FSQVertex vertices[] =
	{
		{ -1.0f,1.0f,0.5f,0.0f,0.0f },
		{ 1.0f,1.0f,0.5f,1.0f,0.0f },
		{ 1.0f,-1.0f,0.5f,1.0f,1.0f },
		{ -1.0f,1.0f,0.5f,0.0f,0.0f },
		{ 1.0f,-1.0f,0.5f,1.0f,1.0f },
		{ -1.0f,-1.0f,0.5f,0.0f,1.0f },
	};
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(FSQVertex) * 6;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0u;
	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = vertices;
	if (FAILED(hr = pDevice->CreateBuffer(&bd, &initData, &pVertexBuffer)))
	{
		throw CHILI_GFX_EXCEPTION(hr, L"Creating vertex buffer");
	}


	//////////////////////////////////////////
	// create input layout for fullscreen quad
	const D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 }
	};

	// Ignore the intellisense error "namespace has no member"
	if (FAILED(hr = pDevice->CreateInputLayout(ied, 2,
		FramebufferShaders::FramebufferVSBytecode,
		sizeof(FramebufferShaders::FramebufferVSBytecode),
		&pInputLayout)))
	{
		throw CHILI_GFX_EXCEPTION(hr, L"Creating input layout");
	}


	////////////////////////////////////////////////////
	// Create sampler state for fullscreen textured quad
	D3D11_SAMPLER_DESC sampDesc = {};
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	if (FAILED(hr = pDevice->CreateSamplerState(&sampDesc, &pSamplerState)))
	{
		throw CHILI_GFX_EXCEPTION(hr, L"Creating sampler state");
	}
}

Graphics::~Graphics()
{
	// clear the state of the device context before destruction
	if (pImmediateContext) pImmediateContext->ClearState();
}

void Graphics::EndFrame()
{
	HRESULT hr;

	// lock and map the adapter memory for copying over the sysbuffer
	if (FAILED(hr = pImmediateContext->Map(pSysBufferTexture.Get(), 0u,
		D3D11_MAP_WRITE_DISCARD, 0u, &mappedSysBufferTexture)))
	{
		throw CHILI_GFX_EXCEPTION(hr, L"Mapping sysbuffer");
	}
	// perform the copy line-by-line
	sysBuffer.Present(mappedSysBufferTexture.RowPitch,
		reinterpret_cast<BYTE*>(mappedSysBufferTexture.pData));
	// release the adapter memory
	pImmediateContext->Unmap(pSysBufferTexture.Get(), 0u);

	// render offscreen scene texture to back buffer
	pImmediateContext->IASetInputLayout(pInputLayout.Get());
	pImmediateContext->VSSetShader(pVertexShader.Get(), nullptr, 0u);
	pImmediateContext->PSSetShader(pPixelShader.Get(), nullptr, 0u);
	pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	const UINT stride = sizeof(FSQVertex);
	const UINT offset = 0u;
	pImmediateContext->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);
	pImmediateContext->PSSetShaderResources(0u, 1u, pSysBufferTextureView.GetAddressOf());
	pImmediateContext->PSSetSamplers(0u, 1u, pSamplerState.GetAddressOf());
	pImmediateContext->Draw(6u, 0u);

	// flip back/front buffers
	if (FAILED(hr = pSwapChain->Present(1u, 0u)))
	{
		throw CHILI_GFX_EXCEPTION(hr, L"Presenting back buffer");
	}
}

void Graphics::BeginFrame()
{
	sysBuffer.Clear(Colors::Red);
	pzBuffer.Clear();
}


//////////////////////////////////////////////////
//           Graphics Exception
Graphics::Exception::Exception(HRESULT hr, const std::wstring& note, const wchar_t* file, unsigned int line)
	:
	ChiliException(file, line, note),
	hr(hr)
{}

std::wstring Graphics::Exception::GetFullMessage() const
{
	const std::wstring empty = L"";
	const std::wstring errorName = GetErrorName();
	const std::wstring errorDesc = GetErrorDescription();
	const std::wstring& note = GetNote();
	const std::wstring location = GetLocation();
	return    (!errorName.empty() ? std::wstring(L"Error: ") + errorName + L"\n"
		: empty)
		+ (!errorDesc.empty() ? std::wstring(L"Description: ") + errorDesc + L"\n"
			: empty)
		+ (!note.empty() ? std::wstring(L"Note: ") + note + L"\n"
			: empty)
		+ (!location.empty() ? std::wstring(L"Location: ") + location
			: empty);
}

std::wstring Graphics::Exception::GetErrorName() const
{
	return DXGetErrorString(hr);
}

std::wstring Graphics::Exception::GetErrorDescription() const
{
	std::array<wchar_t, 512> wideDescription;
	DXGetErrorDescription(hr, wideDescription.data(), wideDescription.size());
	return wideDescription.data();
}

std::wstring Graphics::Exception::GetExceptionType() const
{
	return L"Chili Graphics Exception";
}

void Graphics::DrawLine(float x1, float y1, float x2, float y2, Color c)
{
	const float dx = x2 - x1;
	const float dy = y2 - y1;

	if (dy == 0.0f && dx == 0.0f)
	{
		PutPixel(int(x1), int(y1), c);
	}
	else if (abs(dy) > abs(dx))
	{
		if (dy < 0.0f)
		{
			std::swap(x1, x2);
			std::swap(y1, y2);
		}

		const float m = dx / dy;
		float y = y1;
		int lastIntY;
		for (float x = x1; y < y2; y += 1.0f, x += m)
		{
			lastIntY = int(y);
			PutPixel(int(x), lastIntY, c);
		}
		if (int(y2) > lastIntY)
		{
			PutPixel(int(x2), int(y2), c);
		}
	}
	else
	{
		if (dx < 0.0f)
		{
			std::swap(x1, x2);
			std::swap(y1, y2);
		}

		const float m = dy / dx;
		float x = x1;
		int lastIntX;
		for (float y = y1; x < x2; x += 1.0f, y += m)
		{
			lastIntX = int(x);
			PutPixel(lastIntX, int(y), c);
		}
		if (int(x2) > lastIntX)
		{
			PutPixel(int(x2), int(y2), c);
		}
	}







}



void Graphics::DrawTriangle(Triangle& tr)
{

	//sort them so that v0 at top,v2 at the bottom 
	const int* pI0 = &tr.index[0];
	const int* pI1 = &tr.index[1];
	const int* pI2 = &tr.index[2];
	//sort
	if (tr.vertexs[*pI0].p.y > tr.vertexs[*pI1].p.y)  std::swap(pI0, pI1);
	if (tr.vertexs[*pI0].p.y > tr.vertexs[*pI2].p.y)  std::swap(pI0, pI2);
	if (tr.vertexs[*pI1].p.y > tr.vertexs[*pI2].p.y)  std::swap(pI1, pI2);


	if (tr.vertexs[*pI0].p.y == tr.vertexs[*pI1].p.y)  //flat top tri 
	{
		if (tr.vertexs[*pI0].p.x > tr.vertexs[*pI1].p.x) {
			std::swap(pI0, pI1);
		}

		DrawFlatTopTriangle(tr, tr.vertexs[*pI0], tr.vertexs[*pI1], tr.vertexs[*pI2]);
	}

	else if (tr.vertexs[*pI1].p.y == tr.vertexs[*pI2].p.y)  //flat bottom tri 
	{
		if (tr.vertexs[*pI1].p.x > tr.vertexs[*pI2].p.x) {
			std::swap(pI1, pI2);
		}

		DrawFlatBottomTriangle(tr, tr.vertexs[*pI0], tr.vertexs[*pI1], tr.vertexs[*pI2]);
	}

	else { //general tir

		const float alpha = (tr.vertexs[*pI1].p.y - tr.vertexs[*pI0].p.y) / (tr.vertexs[*pI2].p.y - tr.vertexs[*pI0].p.y);

		Vertex vi = tr.vertexs[*pI0] + (tr.vertexs[*pI2] - tr.vertexs[*pI0]) * alpha;
		
		if (vi.p.x > tr.vertexs[*pI1].p.x) //major right
		{
			//counterclockwise order
				//          v0
				//         /  \ 
				//        /    \
				//       v1----v2

			DrawFlatBottomTriangle(tr, tr.vertexs[*pI0],  tr.vertexs[*pI1] , vi);
			//clockwise order
				// v0--------v1
				//   \      /
				// v' \    / v''
				//      v2

			DrawFlatTopTriangle(tr,tr.vertexs[*pI1], vi, tr.vertexs[*pI2]);
		}
		else//major left
		{
			//counterclockwise order
				//          v0
				//         /  \ 
				//        /    \
				//       v1----v2

			DrawFlatBottomTriangle(tr, tr.vertexs[*pI0], vi, tr.vertexs[*pI1]);
			//clockwise order
				// v0--------v1
				//   \      /
				// v' \    / v''
				//      v2

			DrawFlatTopTriangle(tr, vi, tr.vertexs[*pI1], tr.vertexs[*pI2]);
		}
	}



}

void Graphics::DrawFlatTopTriangle(Triangle& tr, Vertex& v0, Vertex& v1, Vertex& v2) {



	// v0--------v1
	//   \      /
	// v' \    / v''
	//      v2
	// z negtive

	if (v2.p.y < 0.f || v1.p.x < 0.f || v0.p.y >= float(Graphics::ScreenHeight)) return;

	//run over rise ,avoid vertical fuck up
	float m0 = (v2.p.x - v0.p.x) / (v2.p.y - v0.p.y);
	float m1 = (v2.p.x - v1.p.x) / (v2.p.y - v1.p.y);


	//scanline start and end
	const int yStart = std::max((int)ceil(v0.p.y - 0.5f), 0);
	const int yEnd = std::min((int)ceil(v2.p.y - 0.5f), (int)(Graphics::ScreenHeight)); //exclusive this last one

	for (int y = yStart; y < yEnd; y++)
	{
		const float px0 = m0 * (float(y) + 0.5f - v0.p.y) + v0.p.x;
		const float px1 = m1 * (float(y) + 0.5f - v1.p.y) + v1.p.x;
		const int xStart = std::max((int)ceil(px0 - 0.5f), 0);
		const int xEnd = std::min((int)ceil(px1 - 0.5f), (int)(Graphics::ScreenWidth));//exclusive

		for (int x = xStart; x < xEnd; x++) {
			float alpha = (float(y) + 0.5f - v0.p.y) / (v2.p.y - v0.p.y);
			Vertex vPrime = v0 + (v2 - v0) * alpha;
			Vertex vPrimePrime = v1 + (v2 - v1) * alpha;
			float beta = (float(x) + 0.5f - vPrime.p.x) / (vPrimePrime.p.x - vPrime.p.x);
			Vertex finalPoint = vPrime + (vPrimePrime - vPrime) * beta;
			float recipicalOfz = finalPoint.p.w;
			float z = 1.f / recipicalOfz;

			if (recipicalOfz > pzBuffer.At(x, y)) {
				pzBuffer.Store(x, y, z);
				PutPixel(x, y, GetColorFromTexture(finalPoint.uvCoordinate * z, *tr.surf));
			}
			
		}
	}
}

void Graphics::DrawFlatBottomTriangle(Triangle& tr, Vertex& v0, Vertex& v1, Vertex& v2)
{
	//          v0
    //         /  \ 
    //        /    \
	//       v1----v2


	if (v2.p.y < 0.f || v2.p.x < 0.f || v0.p.y >= float(Graphics::ScreenHeight)) return;

	float m0 = (v0.p.x - v1.p.x) / (v0.p.y - v1.p.y);
	float m1 = (v0.p.x - v2.p.x) / (v0.p.y - v2.p.y);





	int yStart = std::max((int)ceil(v0.p.y - 0.5f), 0);
	int yEnd = std::min((int)ceil(v1.p.y - 0.5f), (int)(Graphics::ScreenHeight)); //exclusive

	for (int y = yStart; y < yEnd; y++) {


		const float px0 = m0 * (float(y) + 0.5f - v0.p.y) + v0.p.x;
		const float px1 = m1 * (float(y) + 0.5f - v0.p.y) + v0.p.x;
		const int xStart = std::max((int)ceil(px0 - 0.5f), 0);
		const int xEnd = std::min((int)ceil(px1 - 0.5f), (int)(Graphics::ScreenWidth));





		for (int x = xStart; x < xEnd; x++) {
			//          v0
			//         /  \ 
			//    v'  /    \ v''
			//       v1----v2

			float alpha = (float(y) + 0.5f - v0.p.y) / (v1.p.y - v0.p.y);

			Vertex vPrime = v0 + (v1 - v0) * alpha;
			Vertex vPrimePrime = v0 + (v2 - v0) * alpha;

			float beta = (float(x) + 0.5f - vPrime.p.x) / (vPrimePrime.p.x - vPrime.p.x);
			Vertex finalPoint = vPrime + (vPrimePrime - vPrime) * beta;


			float recipicalOfz = finalPoint.p.w;
			float z = 1.f / recipicalOfz;

			if (recipicalOfz > pzBuffer.At(x, y) ) {
				pzBuffer.Store(x, y, z);
			
				PutPixel(x, y, GetColorFromTexture(finalPoint.uvCoordinate * z, *tr.surf));
			}

		}

	}
}



Color Graphics::GetColorFromTexture(Vec2 uv, const texture& tex)
{

	const int w = tex.GetWidth();
	const int h = tex.GetHeight();
	const float u = uv.x;
	const float v = uv.y;

	int x = (int)(w * (u / 1.f));
	int y = (int)(h * (v / 1.f));

	return tex.GetColor(x, y);
}




