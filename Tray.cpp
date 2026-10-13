#include "Tray.hpp"
#include "resource.h"

Tray::Tray(HWND hwnd) {
	HWND trayHwnd = createTrayWindow();

	globalHwnd = hwnd;

	NOTIFYICONDATAW nid{};

	nid.cbSize = sizeof(nid);
	nid.hWnd = trayHwnd;
	nid.uID = 101;

	nid.uCallbackMessage = WM_APP + 1;
	nid.hIcon = LoadIcon(GetModuleHandleW(nullptr), MAKEINTRESOURCE(IDI_ICON1));
	wcscpy_s(nid.szTip, L"Pomodoro");
	nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;

	Shell_NotifyIcon(NIM_ADD, &nid);

	this->nid = nid;
	this->trayHwnd = trayHwnd;
}

HWND Tray::createTrayWindow() {
	WNDCLASSW wc{};
	wc.lpfnWndProc = TrayProc;
	wc.hInstance = GetModuleHandleW(nullptr);
	wc.lpszClassName = L"PomodoroTray";
	RegisterClassW(&wc);

	return CreateWindowExW(0, L"PomodoroTray", L"", 0,
		0, 0, 0, 0,
		HWND_MESSAGE,
		nullptr, wc.hInstance, nullptr);
}

LRESULT CALLBACK Tray::TrayProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_APP + 1) {
		if (lParam == WM_LBUTTONUP) {
			ShowWindow(globalHwnd, SW_SHOW);
		}
		else if (lParam == WM_RBUTTONUP) {
			HMENU menu = CreatePopupMenu();
			AppendMenuW(menu, MF_STRING, 1, L"Hide");
			AppendMenuW(menu, MF_STRING, 2, L"Close");

			POINT point;
			GetCursorPos(&point);

			SetForegroundWindow(hwnd);

			int cmd = TrackPopupMenu(menu, TPM_RETURNCMD | TPM_NONOTIFY, point.x, point.y, 0, hwnd, nullptr);

			if (cmd == 1) {
				ShowWindow(globalHwnd, SW_HIDE);
			}
			else if (cmd == 2) {
				closeApplication = true;
			}

			DestroyMenu(menu);
		}
		return 0;
	}
	return DefWindowProcW(hwnd, msg, wParam, lParam);
}

Tray::~Tray() {
	Shell_NotifyIcon(NIM_DELETE, &nid);
}