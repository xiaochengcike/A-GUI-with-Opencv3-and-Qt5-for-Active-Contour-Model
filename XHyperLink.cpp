#include "stdafx.h"
#include "XHyperLink.h"
#include "atlconv.h" // for Unicode conversion

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TOOLTIP_ID 1

#ifndef IDC_HAND
#define IDC_HAND MAKEINTRESOURCE(32649) // From WINUSER.H
#endif

UINT WM_XHYPERLINK_CLICKED = ::RegisterWindowMessage(_T("WM_XHYPERLINK_CLICKED"));

BEGIN_MESSAGE_MAP(CXHyperLink, CStatic)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_CONTROL_REFLECT(STN_CLICKED, OnClicked)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

CXHyperLink::CXHyperLink()
{
	m_hLinkCursor  = NULL; // No cursor as yet
	m_crLinkColour  = RGB(0, 0, 238); // Blue
	m_crVisitedColour = RGB(85, 26, 139);
	m_crHoverColour  = RGB(255, 0, 0);
	m_bOverControl  = FALSE;
	m_bVisited  = FALSE;
	m_nUnderline  = ulHover;
	m_bAdjustToFit = TRUE;
	m_strURL = _T("");
	m_nTimerID  = 100;
	m_bNotifyParent = FALSE;
	m_bIsURLEnabled = TRUE;
	m_bToolTip = TRUE;
	m_crBackground = (UINT)-1;
	m_bAlwaysOpenNew = FALSE;
}

CXHyperLink::~CXHyperLink()
{
	TRACE(_T("in CXHyperLink::~CXHyperLink\n"));

	if (m_hLinkCursor)
		DestroyCursor(m_hLinkCursor);
	m_hLinkCursor = NULL;
	m_UnderlineFont.DeleteObject();
	if (m_Brush.GetSafeHandle())
		m_Brush.DeleteObject();
}

BOOL CXHyperLink::DestroyWindow()
{
	KillTimer(m_nTimerID);
	return CStatic::DestroyWindow();
}

BOOL CXHyperLink::PreTranslateMessage(MSG* pMsg)
{
	m_ToolTip.RelayEvent(pMsg);
	return CStatic::PreTranslateMessage(pMsg);
}

void CXHyperLink::PreSubclassWindow()
{
	DWORD dwStyle = GetStyle();
	::SetWindowLong(GetSafeHwnd(), GWL_STYLE, dwStyle | SS_NOTIFY);

	if (m_strURL.IsEmpty())
		GetWindowText(m_strURL);

	CString strWndText;
	GetWindowText(strWndText);
	if (strWndText.IsEmpty())
	{
		ASSERT(!m_strURL.IsEmpty());
		SetWindowText(m_strURL);
	}

	CFont* pFont = GetFont();
	if (!pFont)
	{
		HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
		if (hFont == NULL)
			hFont = (HFONT)GetStockObject(ANSI_VAR_FONT);
		if (hFont)
			pFont = CFont::FromHandle(hFont);
	}
	ASSERT(pFont->GetSafeHandle());

	// Create the underline font
	LOGFONT lf;
	pFont->GetLogFont(&lf);
	m_StdFont.CreateFontIndirect(&lf);
	lf.lfUnderline = (BYTE)TRUE;
	m_UnderlineFont.CreateFontIndirect(&lf);

	PositionWindow();
	SetDefaultCursor();
	SetUnderline();

	// Create the tooltip
	if (m_bToolTip)
	{
		CRect rect;
		GetClientRect(rect);
		m_ToolTip.Create(this);
		m_ToolTip.AddTool(this, m_strURL, rect, TOOLTIP_ID);
	}

	CStatic::PreSubclassWindow();
}

void CXHyperLink::OnClicked()
{
	m_bOverControl = FALSE;
	int result = HINSTANCE_ERROR + 1;
	if (m_bIsURLEnabled)
	{
		result = (int)GotoURL(m_strURL, SW_SHOW, m_bAlwaysOpenNew);
	}

	m_bVisited = (result > HINSTANCE_ERROR);
	if (!m_bVisited)
	{
		MessageBeep(MB_ICONEXCLAMATION);
		ReportError(result);
	}
	else
	{
		SetVisited();
	}

	NotifyParent();
}

#ifdef _DEBUG
HBRUSH CXHyperLink::CtlColor(CDC* pDC, UINT nCtlColor)
#else
HBRUSH CXHyperLink::CtlColor(CDC* pDC, UINT /*nCtlColor*/)
#endif
{
	ASSERT(nCtlColor == CTLCOLOR_STATIC);

	if (m_bOverControl)
		pDC->SetTextColor(m_crHoverColour);
	else if (m_bVisited)
		pDC->SetTextColor(m_crVisitedColour);
	else
		pDC->SetTextColor(m_crLinkColour);

	// transparent text.
	pDC->SetBkMode(TRANSPARENT);

	if (m_Brush.GetSafeHandle())
	{
		pDC->SetBkColor(m_crBackground);
		return (HBRUSH)m_Brush;
	}
	else
	{
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	}
}

void CXHyperLink::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!m_bOverControl)
	{
		m_bOverControl = TRUE;

		if (m_nUnderline == ulHover)
			SetFont(&m_UnderlineFont);
		Invalidate();

		SetTimer(m_nTimerID, 100, NULL);
	}
	CStatic::OnMouseMove(nFlags, point);
}

void CXHyperLink::OnTimer(UINT_PTR nIDEvent)
{
	CPoint p(GetMessagePos());
	ScreenToClient(&p);

	CRect rect;
	GetClientRect(rect);
	if (!rect.PtInRect(p))
	{
		m_bOverControl = FALSE;
		KillTimer(m_nTimerID);

		if (m_nUnderline != ulAlways)
			SetFont(&m_StdFont);
		rect.bottom += 10;
		InvalidateRect(rect);
	}

	CStatic::OnTimer(nIDEvent);
}

BOOL CXHyperLink::OnSetCursor(CWnd* /*pWnd*/, UINT /*nHitTest*/, UINT /*message*/)
{
	if (m_hLinkCursor)
	{
		::SetCursor(m_hLinkCursor);
		return TRUE;
	}
	return FALSE;
}

BOOL CXHyperLink::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(rect);
	if (m_crBackground != (UINT)-1)
		pDC->FillSolidRect(rect, m_crBackground);
	else
		pDC->FillSolidRect(rect, ::GetSysColor(COLOR_3DFACE));

	return TRUE;
}

void CXHyperLink::SetURL(CString strURL)
{
	m_strURL = strURL;

	if (::IsWindow(GetSafeHwnd()))
	{
		PositionWindow();
		m_ToolTip.UpdateTipText(strURL, this, TOOLTIP_ID);
	}
}

void CXHyperLink::SetColours(COLORREF crLinkColour, COLORREF crVisitedColour, COLORREF crHoverColour /* = -1 */)
{
	m_crLinkColour = crLinkColour;
	m_crVisitedColour = crVisitedColour;

	if (crHoverColour == -1)
		m_crHoverColour = ::GetSysColor(COLOR_HIGHLIGHT);
	else
		m_crHoverColour = crHoverColour;

	if (::IsWindow(m_hWnd))
	{
		Invalidate();
	}
}

void CXHyperLink::SetBackgroundColour(COLORREF crBackground)
{
	m_crBackground = crBackground;
	if (m_Brush.GetSafeHandle())
		m_Brush.DeleteObject();
	m_Brush.CreateSolidBrush(m_crBackground);
}

void CXHyperLink::SetVisited(BOOL bVisited /* = TRUE */)
{
	m_bVisited = bVisited;

	if (::IsWindow(GetSafeHwnd()))
		Invalidate();
}

void CXHyperLink::SetLinkCursor(HCURSOR hCursor)
{
	m_hLinkCursor = hCursor;
	if (m_hLinkCursor == NULL)
		SetDefaultCursor();
}

void CXHyperLink::SetUnderline(int nUnderline /*=ulHover*/)
{
	if (m_nUnderline == nUnderline)
		return;

	if (::IsWindow(GetSafeHwnd()))
	{
		if (nUnderline == ulAlways)
			SetFont(&m_UnderlineFont);
		else
			SetFont(&m_StdFont);

		Invalidate();
	}

	m_nUnderline = nUnderline;
}

void CXHyperLink::SetAutoSize(BOOL bAutoSize /* = TRUE */)
{
	m_bAdjustToFit = bAutoSize;

	if (::IsWindow(GetSafeHwnd()))
		PositionWindow();
}

void CXHyperLink::SetWindowText(LPCTSTR lpszString)
{
	ASSERT(lpszString);
	if (!lpszString)
		return;
	CStatic::SetWindowText(_T(""));
	RedrawWindow();
	CStatic::SetWindowText(lpszString);
	PositionWindow();
}

void CXHyperLink::PositionWindow()
{
	if (!::IsWindow(GetSafeHwnd()) || !m_bAdjustToFit)
		return;

	CRect WndRect, ClientRect;
	GetWindowRect(WndRect);
	GetClientRect(ClientRect);

	ClientToScreen(ClientRect);

	CWnd* pParent = GetParent();
	if (pParent)
	{
		pParent->ScreenToClient(WndRect);
		pParent->ScreenToClient(ClientRect);
	}

	CString strWndText;
	GetWindowText(strWndText);

	CDC* pDC = GetDC();
	CFont* pOldFont = pDC->SelectObject(&m_UnderlineFont);
	CSize Extent = pDC->GetTextExtent(strWndText);
	pDC->SelectObject(pOldFont);
	ReleaseDC(pDC);

	Extent.cx += WndRect.Width() - ClientRect.Width();
	Extent.cy += WndRect.Height() - ClientRect.Height();

	DWORD dwStyle = GetStyle();

	if (dwStyle & SS_CENTERIMAGE)
		WndRect.DeflateRect(0, (WndRect.Height() - Extent.cy) / 2);
	else
		WndRect.bottom = WndRect.top + Extent.cy;

	if (dwStyle & SS_CENTER)
		WndRect.DeflateRect((WndRect.Width() - Extent.cx) / 2, 0);
	else if (dwStyle & SS_RIGHT)
		WndRect.left = WndRect.right - Extent.cx;
	else
		WndRect.right = WndRect.left + Extent.cx;

	SetWindowPos(NULL, WndRect.left, WndRect.top, WndRect.Width(), WndRect.Height(), SWP_NOZORDER);
}

void CXHyperLink::SetDefaultCursor()
{
	if (m_hLinkCursor == NULL)
	{
		TRACE(_T("loading from IDC_HAND\n"));
		m_hLinkCursor = AfxGetApp()->LoadStandardCursor(IDC_HAND);

		if (m_hLinkCursor == NULL)
		{
			TRACE(_T("loading from winhlp32\n"));

			// Get the windows directory
			CString strWndDir;
			GetWindowsDirectory(strWndDir.GetBuffer(MAX_PATH), MAX_PATH);
			strWndDir.ReleaseBuffer();

			strWndDir += _T("\\winhlp32.exe");

			HMODULE hModule = LoadLibrary(strWndDir);
			if (hModule)
			{
				HCURSOR hHandCursor = ::LoadCursor(hModule, MAKEINTRESOURCE(106));
				if (hHandCursor)
				{
					m_hLinkCursor = CopyCursor(hHandCursor);
				}
				FreeLibrary(hModule);
			}
		}
	}
}

LONG CXHyperLink::GetRegKey(HKEY key, LPCTSTR subkey, LPTSTR retdata)
{
	HKEY hkey;
	LONG retval = RegOpenKeyEx(key, subkey, 0, KEY_QUERY_VALUE, &hkey);

	if (retval == ERROR_SUCCESS)
	{
		long datasize = MAX_PATH;
		TCHAR data[MAX_PATH];
		RegQueryValue(hkey, NULL, data, &datasize);
		_tcscpy_s(retdata, MAX_PATH + 1, data);

		RegCloseKey(hkey);
	}

	return retval;
}

void CXHyperLink::ReportError(int nError)
{
#ifdef XHYPERLINK_REPORT_ERROR

	CString str;
	switch (nError)
	{
	case 0:?? ??? ??? ??? ??? ??? ??? ?str = "The operating system is out\nof memory or resources."; break;
	case SE_ERR_PNF:?? ??? ??? ??? ?str = "The specified path was not found."; break;
	case SE_ERR_FNF:?? ??? ??? ??? ?str = "The specified file was not found."; break;
	case ERROR_BAD_FORMAT:?? ??? ??? ?str = "The .EXE file is invalid\n(non-Win32 .EXE or error in .EXE image)."; break;
	case SE_ERR_ACCESSDENIED:?? ??? ?str = "The operating system denied\naccess to the specified file."; break;
	case SE_ERR_ASSOCINCOMPLETE:?? ?str = "The filename association is\nincomplete or invalid."; break;
	case SE_ERR_DDEBUSY:?? ??? ??? ?str = "The DDE transaction could not\nbe completed because other DDE transactions\nwere being processed."; break;
	case SE_ERR_DDEFAIL:?? ??? ??? ?str = "The DDE transaction failed."; break;
	case SE_ERR_DDETIMEOUT:?? ??? ??? ?str = "The DDE transaction could not\nbe completed because the request timed out."; break;
	case SE_ERR_DLLNOTFOUND:?? ??? ?str = "The specified dynamic-link library was not found."; break;
	case SE_ERR_NOASSOC:?? ??? ??? ?str = "There is no application associated\nwith the given filename extension."; break;
	case SE_ERR_OOM:?? ??? ??? ??? ?str = "There was not enough memory to complete the operation."; break;
	case SE_ERR_SHARE:?? ??? ??? ??? ?str = "A sharing violation occurred. ";
	default:?? ??? ??? ??? ??? ??? ?str.Format(_T("Unknown Error (%d) occurred."), nError); break;
	}
	str = "Unable to open hyperlink:\n\n" + str;
	AfxMessageBox(str, MB_ICONEXCLAMATION | MB_OK);

#else

	UNUSED_ALWAYS(nError);

	#endif?? ?// XHYPERLINK_REPORT_ERROR
}

void CXHyperLink::NotifyParent()
{
	if (m_bNotifyParent)
	{
		CWnd *pParent = GetParent();
		if (pParent && ::IsWindow(pParent->m_hWnd))
		{
			pParent->SendMessage(WM_XHYPERLINK_CLICKED, GetDlgCtrlID());
		}
	}
}

HINSTANCE CXHyperLink::GotoURL(LPCTSTR url, int showcmd, BOOL bAlwaysOpenNew /*= FALSE*/)
{
	if (!url || url[0] == _T('\0'))
		return (HINSTANCE)HINSTANCE_ERROR + 1;

	TCHAR key[MAX_PATH * 2];

	TCHAR *verb = _T("open");
	if (bAlwaysOpenNew)
		verb = _T("new");
	HINSTANCE result = ShellExecute(NULL, verb, url, NULL, NULL, showcmd);

	if ((UINT)result <= HINSTANCE_ERROR)
	{
		if (GetRegKey(HKEY_CLASSES_ROOT, _T(".htm"), key) == ERROR_SUCCESS)
		{
			_tcscat_s(key, _T("\\shell\\open\\command"));

			if (GetRegKey(HKEY_CLASSES_ROOT, key, key) == ERROR_SUCCESS)
			{
				TCHAR *pos;
				pos = _tcsstr(key, _T("\"%1\""));
				if (pos == NULL)
				{
					pos = _tcsstr(key, _T("%1"));
					if (pos == NULL)
						pos = key + _tcslen(key) - 1;
					else
						*pos = _T('\0');
				}
				else
				{
					*pos = _T('\0');
				}

				_tcscat(pos, _T(" "));
				_tcscat(pos, url);

				USES_CONVERSION;
				result = (HINSTANCE)WinExec(T2A(key), showcmd);
			}
		}
	}

	return result;
}