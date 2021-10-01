#include "framework.h"
#include "ytdlgui.h"

#define BUFFERSIZE 1024

HINSTANCE hMainInst;
int YouTubeDownload(HWND hDlg);
INT_PTR CALLBACK MainDlg(HWND hDlg, UINT msg, WPARAM wPrm, LPARAM lPrm);

int APIENTRY _tWinMain(HINSTANCE hInst, HINSTANCE hPInst, LPTSTR lpCmdLine, int nCmdShow)
{
	hMainInst = hInst;
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_MAIN), NULL, MainDlg);
}

INT_PTR CALLBACK MainWin(HWND hDlg, UINT msg, WPARAM wPrm, LPARAM lPrm)
{
	UNREFERENCED_PARAMETER(lPrm);

	switch (msg) {

	}

	return (INT_PTR)FALSE;
}

// バージョン情報ボックスのメッセージ ハンドラーです。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK MainDlg(HWND hDlg, UINT msg, WPARAM wPrm, LPARAM lPrm)
{
	switch (msg) {
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		switch (LOWORD(wPrm)) {
		case IDOK:
			YouTubeDownload(hDlg);
			break;
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wPrm));
			return (INT_PTR)TRUE;
		}
		break;
	}

	return (INT_PTR)FALSE;
}

int YouTubeDownload(HWND hDlg)
{
	TCHAR buf[BUFFERSIZE];
	TCHAR cmd[BUFFERSIZE];

	GetDlgItemText(hDlg, IDC_URL, buf, BUFFERSIZE);
	StringCchPrintf(cmd, BUFFERSIZE, _T("youtube-dl \"%s\""), buf);
	_tsystem(cmd);
	MessageBox(hDlg, _T("動画のダウンロードが完了しました"), _T("YouTube DL GUI"), 0);

	return 0;
}