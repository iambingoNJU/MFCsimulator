#include "my.h"

extern CMyWinApp theApp;
extern void printlpEntries(AFX_MSGMAP_ENTRY* lpEntry);

static char szCObject[] = "CObject";
struct CRuntimeClass CObject::classCObject = 
	{ szCObject, sizeof(CObject), 0xffff, NULL, NULL, NULL };
static AFX_CLASSINIT _init_CObject(&CObject::classCObject);

CRuntimeClass* CRuntimeClass::pFirstClass = NULL;

AFX_CLASSINIT::AFX_CLASSINIT(CRuntimeClass* pNewClass) {
	pNewClass->m_pNextClass = CRuntimeClass::pFirstClass;
	CRuntimeClass::pFirstClass = pNewClass;
}

CObject* CRuntimeClass::CreateObject() {
	if(m_pfnCreateObject == NULL) {
		cout << "Error: Trying to create object which is not "
			 << "DECLARE_DYNCREATE \nor DECLARE_SERIAL;"
			 << m_lpszClassName << endl;
		return NULL;
	}
	CObject* pObject = NULL;
	pObject = (*m_pfnCreateObject)();

	return pObject;
}

CRuntimeClass* PASCAL CRuntimeClass::Load() {
	char szClassName[64];
	CRuntimeClass* pClass;
	cout << "enter a class name... ";
	cin >> szClassName;

	for(pClass = pFirstClass; pClass != NULL; pClass = pClass->m_pNextClass) {
		if(strcmp(szClassName, pClass->m_lpszClassName) == 0)
			return pClass;
	}

	cout << "Error: Class not found: " << szClassName << endl;
	return NULL;
}

CRuntimeClass* CObject::GetRuntimeClass() const {
	return &CObject::classCObject;
}

BOOL CObject::IsKindOf(const CRuntimeClass* pClass) const {
	CRuntimeClass* pClassThis = GetRuntimeClass();
	while(pClassThis != NULL) {
		if(pClassThis == pClass) return TRUE;
		pClassThis = pClassThis->m_pBaseClass;
	}
	return FALSE;
}


BOOL CCmdTarget::OnCmdMsg(UINT nID, int nCode) {
	AFX_MSGMAP* pMessageMap;
	for(pMessageMap = GetMessageMap(); pMessageMap != NULL;
		pMessageMap = pMessageMap->pBaseMessageMap) {
		printlpEntries(pMessageMap->lpEntries);
	}

	return FALSE;
}

BOOL CWnd::Create() {
	cout << "CWnd::Create\n";
	return TRUE;
}

BOOL CWnd::CreateEx() {
	cout << "CWnd::CreateEx\n";
	PreCreateWindow();
	return TRUE;
}

BOOL CWnd::PreCreateWindow() {
	cout << "CWnd::PreCreateWindow\n";
	return TRUE;
}

LRESULT CWnd::WindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam) {
	AFX_MSGMAP* pMessageMap;
	AFX_MSGMAP_ENTRY* lpEntry;

	if(nMsg == WM_COMMAND) {
		if(OnCommand(wParam, lParam)) {
			return 1L;
		} else {
			return (LRESULT)DefWindowProc(nMsg, wParam, lParam);
		}
	}

	for(pMessageMap = GetMessageMap(); pMessageMap != NULL;
		pMessageMap = pMessageMap->pBaseMessageMap) {
		lpEntry = pMessageMap->lpEntries;
		printlpEntries(lpEntry);
	}

	return 0;
}

LRESULT CWnd::DefWindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam) {
	return TRUE;
}

BOOL CWnd::OnCommand(WPARAM wParam, LPARAM lParam) {
	return OnCmdMsg(0, 0);
}

BOOL CFrameWnd::Create() {
	cout << "CFrameWnd::Create\n";
	CreateEx();
	return TRUE;
}

BOOL CFrameWnd::PreCreateWindow() {
	cout << "CFrameWnd::PreCreateWindow\n";
	return TRUE;
}

BOOL CFrameWnd::OnCommand(WPARAM wParam, LPARAM lParam) {
	return CWnd::OnCommand(wParam, lParam);
}

CView* CFrameWnd::GetActiveView() const {
	return m_pViewActive;
}

BOOL CFrameWnd::OnCmdMsg(UINT nID, int nCode) {
	CView* pView = GetActiveView();
	if(pView->OnCmdMsg(nID, nCode))
		return TRUE;

	if(CWnd::OnCmdMsg(nID, nCode))
		return TRUE;

	CWinApp* pApp = AfxGetApp();
	if(pApp->OnCmdMsg(nID, nCode))
		return TRUE;

	return FALSE;
}

BOOL CDocument::OnCmdMsg(UINT nID, int nCode) {
	if(CCmdTarget::OnCmdMsg(nID, nCode))
		return TRUE;

	return FALSE;
}

BOOL CView::OnCmdMsg(UINT nID, int nCode) {
	if(CWnd::OnCmdMsg(nID, nCode))
		return TRUE;
	
	return m_pDocument->OnCmdMsg(nID, nCode);
}

IMPLEMENT_DYNAMIC(CCmdTarget, CObject)
IMPLEMENT_DYNAMIC(CWinThread, CCmdTarget)
IMPLEMENT_DYNAMIC(CWinApp, CWinThread)
//IMPLEMENT_DYNAMIC(CWnd, CCmdTarget)
//IMPLEMENT_DYNAMIC(CFrameWnd, CWnd)
IMPLEMENT_DYNCREATE(CWnd, CCmdTarget)
IMPLEMENT_DYNCREATE(CFrameWnd, CWnd)
IMPLEMENT_DYNAMIC(CDocument, CCmdTarget)
IMPLEMENT_DYNAMIC(CView, CWnd)

// global function
CWinApp* AfxGetApp() {
	return theApp.m_pCurrentWinApp;
}

LRESULT AfxWndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam, CWnd* pWnd) {
	return AfxCallWndProc(pWnd, hWnd, nMsg, wParam, lParam);
}

LRESULT AfxCallWndProc(CWnd* pWnd, HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam) {
	return pWnd->WindowProc(nMsg, wParam, lParam);
}


AFX_MSGMAP* CCmdTarget::GetMessageMap() const {
	return &CCmdTarget::messageMap;
}

AFX_MSGMAP CCmdTarget::messageMap = {
	NULL,
	&CCmdTarget::_messageEntries[0]
};

AFX_MSGMAP_ENTRY CCmdTarget::_messageEntries[] = {
	{ 0, 0, CCmdTargetid, 0, AfxSig_end, 0 }
};

BEGIN_MESSAGE_MAP(CWnd, CCmdTarget)
ON_COMMAND(CWndid, 0)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CFrameWnd, CWnd)
ON_COMMAND(CFrameWndid, 0)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CDocument, CCmdTarget)
ON_COMMAND(CDocumentid, 0)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CView, CWnd)
ON_COMMAND(CViewid, 0)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CWinApp, CCmdTarget)
ON_COMMAND(CWinAppid, 0)
END_MESSAGE_MAP()

