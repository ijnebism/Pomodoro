#pragma once
#include <windows.h>

class Tray {
public:
	Tray(HWND hwnd);
	~Tray();
	bool closeApplicationReq() const { return closeApplication; };

private:
	HWND createTrayWindow();
	static LRESULT CALLBACK TrayProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	static inline bool closeApplication = false;
	static inline HWND globalHwnd = nullptr;

	NOTIFYICONDATAW nid;
	HWND trayHwnd;
};