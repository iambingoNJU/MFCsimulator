#include "my.h"

extern CMyWinApp theApp;

static char szCObject[] = "CObject";
struct CRuntimeClass CObject::classCObject = 
	{ szCObject, sizeof(CObject), 0xffff, NULL, NULL, NULL };
static AFX_CLASSINIT _init_CObject(&CObject::classCObject);

CRuntimeClass* CRuntimeClass::pFirstClass = NULL;

AFX_CLASSINIT::AFX_CLASSINIT(CRuntimeClass* pNewClass) {
	pNewClass->m_pNextClass = CRuntimeClass::pFirstClass;
	CRuntimeClass::pFirstClass = pNewClass;
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

BOOL CFrameWnd::Create() {
	cout << "CFrameWnd::Create\n";
	CreateEx();
	return TRUE;
}

BOOL CFrameWnd::PreCreateWindow() {
	cout << "CFrameWnd::PreCreateWindow\n";
	return TRUE;
}

IMPLEMENT_DYNAMIC(CCmdTarget, CObject)
IMPLEMENT_DYNAMIC(CWinThread, CCmdTarget)
IMPLEMENT_DYNAMIC(CWinApp, CWinThread)
IMPLEMENT_DYNAMIC(CWnd, CCmdTarget)
IMPLEMENT_DYNAMIC(CFrameWnd, CWnd)
IMPLEMENT_DYNAMIC(CDocument, CCmdTarget)
IMPLEMENT_DYNAMIC(CView, CWnd)

// global function
CWinApp* AfxGetApp() {
	return theApp.m_pCurrentWinApp;
}
