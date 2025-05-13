/*
* WinAPI声明
*
* Author: Maple
* date: 2021-7-13 Create
* Copyright winmoes.com
*/

#pragma once
#include <string>
#include <comdef.h>
#include <gdiplus.h>
#include <vector>

#include <gdiplus.h>
using namespace Gdiplus;

Image* gifImage = nullptr;
UINT currentFrame = 0;
int* frameDelays = nullptr;
UINT frameCount = 0;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_TIMER:
            if (wParam == 1) {
                // Advance to the next frame of the GIF
                currentFrame = (currentFrame + 1) % frameCount;
                gifImage->SelectActiveFrame(&frameDimension, currentFrame);
                InvalidateRect(hwnd, NULL, TRUE);
            }
            break;

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            Graphics g(hdc);

            // Draw the current GIF frame
            if (gifImage) {
                g.DrawImage(gifImage, 0, 0, 1920, 1080);  // Adjust size as needed
            }
            EndPaint(hwnd, &ps);
            break;
        }

        // Handle other window messages as needed
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


/*调试输出
* Debug output
*/
extern void Log(std::wstring log);
extern void Log(int log);

/*获取当前dll所在目录
* Get current directory
*/
extern std::wstring GetCurDllDir();

/*判断文件是否存在
* file exist
*/
extern bool FileIsExist(std::wstring FilePath);

/*获取窗口标题*/
extern std::wstring GetWindowTitle(HWND hWnd);

/*获取窗口类名*/
extern std::wstring GetWindowClassName(HWND hWnd);

/*读取配置文件内容
* Read config file
*/
extern std::wstring GetIniString(std::wstring FilePath, std::wstring AppName, std::wstring KeyName);

/*枚举某目录下指定文件*/
extern void EnumFiles(std::wstring path, std::wstring append, std::vector<std::wstring>& fileList);

/*取文件名*/
extern std::wstring GetFileName(std::wstring path);

/*取文件尺寸*/
extern size_t GetFileSize(std::wstring path);

/*GDI Bitmap*/
class BitmapGDI
{
public:
	BitmapGDI(std::wstring path);
	~BitmapGDI();

	HDC pMem = 0;
	HBITMAP pBmp = 0;
	SIZE Size{};
	Gdiplus::Bitmap* src = 0;
};