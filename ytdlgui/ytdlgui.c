#include "framework.h"
#include "ytdlgui.h"

#define BUFFERSIZE 1024

HINSTANCE hMainInst;
int YouTubeDownload(HWND hDlg);
BOOL SelectCookieFile(HWND hDlg);
INT_PTR CALLBACK MainDlg(HWND hDlg, UINT msg, WPARAM wPrm, LPARAM lPrm);

int APIENTRY _tWinMain(HINSTANCE hInst, HINSTANCE hPInst, LPTSTR lpCmdLine, int nCmdShow)
{
	hMainInst = hInst;
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_MAIN), NULL, MainDlg);
}

INT_PTR CALLBACK MainDlg(HWND hDlg, UINT msg, WPARAM wPrm, LPARAM lPrm)
{
	switch (msg) {
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		switch (LOWORD(wPrm)) {
		case IDC_COOKIEREF:
			return SelectCookieFile(hDlg);
		case IDC_COOKIE:
			if (IsDlgButtonChecked(hDlg, IDC_COOKIE) == BST_CHECKED) {
				EnableWindow(GetDlgItem(hDlg, IDC_COOKIEPATH), TRUE);
				EnableWindow(GetDlgItem(hDlg, IDC_COOKIEREF), TRUE);
			} else {
				EnableWindow(GetDlgItem(hDlg, IDC_COOKIEPATH), FALSE);
				EnableWindow(GetDlgItem(hDlg, IDC_COOKIEREF), FALSE);
			}
			return (INT_PTR)TRUE;
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
	TCHAR opt[BUFFERSIZE] = { 0 };
	TCHAR cmd[BUFFERSIZE];

	if (IsDlgButtonChecked(hDlg, IDC_COOKIE) == BST_CHECKED) {
		StringCchCat(opt, BUFFERSIZE, _T("--cookies "));
		GetDlgItemText(hDlg, IDC_COOKIEPATH, buf, BUFFERSIZE);
		StringCchCat(opt, BUFFERSIZE, buf);
	}

	GetDlgItemText(hDlg, IDC_URL, buf, BUFFERSIZE);
	StringCchPrintf(cmd, BUFFERSIZE, _T("youtube-dl %s %s"), opt, buf);
	_tsystem(cmd);
	MessageBox(hDlg, _T("動画のダウンロードが完了しました"), _T("YouTube DL GUI"), 0);

	return 0;
}

BOOL SelectCookieFile(HWND hDlg)
{
	TCHAR buf[BUFFERSIZE] = { 0 };
	OPENFILENAME ofn;

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hDlg;
	ofn.lpstrFilter = _T("Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0");
	ofn.lpstrCustomFilter = NULL;
	ofn.nFilterIndex = 0;
	ofn.lpstrFile = buf;
	ofn.nMaxFile = BUFFERSIZE;
	ofn.lpstrTitle = _T("Cookie ファイルの選択");
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

	if (GetOpenFileName(&ofn) == 0)
		return FALSE;

	SetDlgItemText(hDlg, IDC_COOKIEPATH, buf);
	return TRUE;
}