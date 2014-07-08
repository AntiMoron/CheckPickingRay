#pragma once
#include<D3D11.h>
#include<D3DX11.h>

class SystemVars
{
private:
	SystemVars();
	~SystemVars();
	static SystemVars* instance;
	UINT screenWidth, screenHeight;
public:
	UINT GetScreenWidth();
	UINT GetScreenHeight();
	void SetScreenWidth(UINT _);
	void SetScreenHeight(UINT _);
	static SystemVars& GetInstance();
};

#define SET_HEIGHT(x)  SystemVars::GetInstance().SetScreenHeight(x);
#define SET_WIDTH(x) SystemVars::GetInstance().SetScreenWidth(x);
#define SCREENHEIGHT (SystemVars::GetInstance().GetScreenHeight())
#define SCREENWIDTH (SystemVars::GetInstance().GetScreenWidth())

#define SAFE_CREATE(varPtr,varType) do{varPtr = nullptr;\
	varPtr = new varType; }while (0)
#define SAFE_DELETE(varPtr) do{if(varPtr){delete varPtr;varPtr = nullptr;}}while(0)

#define SAFE_CREATE_MULTI(varPtr,varType,count) do{varPtr = nullptr;\
	varPtr = new varType[count]; \
}while (0)

#define SAFE_DELETE_MULTI(varPtr) do{if(varPtr){delete [] varPtr;\
	varPtr = nullptr;\
}\
}while (0)

#define CREATE_VERTEX_SHADER(x) do{\
	x = NULL; \
	x = new VertexShaderClass;\
}while (0)

#define CREATE_PIXEL_SHADER(x) do{\
	x = NULL; \
	x = new PixelShaderClass;\
}while (0)

#define DELETESHADER(x) \
do{\
if (x)\
{\
	x->ShutDown(); \
	x = NULL; \
}\
} while (0)

#define SAFE_RELEASE(x) do{ if((x) != nullptr){(x)->Release(); (x) = nullptr;} } while (0)

#define MSG_RETURN(var,errormsg)	if(FAILED(var)){\
	MessageBoxA(NULL, errormsg, "error", MB_OK); \
	return E_FAIL; \
}


#define TOWIDE(src,des) do{\
	DWORD dwNum = MultiByteToWideChar(CP_ACP, 0, src, -1, NULL, 0); \
	MultiByteToWideChar(CP_ACP, 0, src, -1, des, dwNum); \
} while (0)

#define TOMULTIBYTE(src,des) do{\
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, src, -1, NULL, 0, NULL, FALSE); \
	WideCharToMultiByte(CP_OEMCP, NULL, src, -1, des, dwNum, NULL, FALSE); \
}while (0)
