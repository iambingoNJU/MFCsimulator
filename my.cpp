#include "my.h"

// Global object
CMyWinApp theApp;

//IMPLEMENT_DYNAMIC(CMyWinApp, CWinApp)
//IMPLEMENT_DYNAMIC(CMyFrameWnd, CFrameWnd)
IMPLEMENT_DYNCREATE(CMyFrameWnd, CFrameWnd)
IMPLEMENT_DYNCREATE(CMyDoc, CDocument)
IMPLEMENT_DYNCREATE(CMyView, CView)

BOOL CMyWinApp::InitInstance() {
	cout << "CMyWinApp::InitInstance\n";
	m_pMainWnd = new CMyFrameWnd;
	return TRUE;
}

BEGIN_MESSAGE_MAP(CMyWinApp, CWinApp)
ON_COMMAND(CMyWinAppid, 0)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CMyFrameWnd, CFrameWnd)
ON_COMMAND(CMyFrameWndid, 0)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CMyDoc, CDocument)
ON_COMMAND(CMyDocid, 0)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CMyView, CView)
ON_COMMAND(CMyViewid, 0)
END_MESSAGE_MAP()

void printlpEntries(AFX_MSGMAP_ENTRY* lpEntry) {
	struct {
		int classid;
		const char* classname;
	} classinfo[] = {
		{ CCmdTargetid, "CCmdTarget" },
		{ CWinThreadid, "CWinThread" },
		{ CWinAppid, "CWinApp" },
		{ CMyWinAppid, "CMyWinApp" },
		{ CWndid, "CWnd" },
		{ CFrameWndid, "CFrameWnd" },
		{ CMyFrameWndid, "CMyFrameWnd" },
		{ CViewid, "CView" },
		{ CMyViewid, "CMyView" },
		{ CDocumentid, "CDocument" },
		{ CMyDocid, "CMyDoc" },
		{ 0, "" }
	};

	for(int i = 0; classinfo[i].classid != 0; i ++) {
		if(classinfo[i].classid == lpEntry->nID) {
			cout << lpEntry->nID << "  "
				 << classinfo[i].classname << endl;
			break;
		}
	}
}

void MsgMapPrinting(AFX_MSGMAP* pMessageMap) {
	for(; pMessageMap != NULL; pMessageMap = pMessageMap->pBaseMessageMap) {
		printlpEntries(pMessageMap->lpEntries);
	}
}

void PrintAllClasses() {
	CRuntimeClass *pClass;
	for(pClass = CRuntimeClass::pFirstClass; pClass != NULL; pClass = pClass->m_pNextClass) {
		cout << pClass->m_lpszClassName << endl;
		cout << pClass->m_nObjectSize << endl;
		cout << pClass->m_wSchema << endl;
	}
}

//-------------------------------------------
// main
//-------------------------------------------
int main() {
	CWinApp* pApp = AfxGetApp();

	pApp->InitApplication();
	pApp->InitInstance();
	pApp->Run();

	// PrintAllClasses();

/*
	CView* pView = new CView();
	cout << "Result: " << pView->IsKindOf(RUNTIME_CLASS(CWinApp)) << endl;
	cout << "Result: " << pView->IsKindOf(RUNTIME_CLASS(CView)) << endl;
	cout << "Result: " << pView->IsKindOf(RUNTIME_CLASS(CCmdTarget)) << endl;
	cout << "Result: " << pView->IsKindOf(RUNTIME_CLASS(CObject)) << endl;
	cout << "Result: " << pView->IsKindOf(RUNTIME_CLASS(CDocument)) << endl;
	cout << "Result: " << pView->IsKindOf(RUNTIME_CLASS(CMyFrameWnd)) << endl;
	*/

/*
	// Test Dynamic creation
	CRuntimeClass* pClassRef;
	CObject* pOb;
	while(1) {
		if((pClassRef = CRuntimeClass::Load()) == NULL)
			break;

		pOb = pClassRef->CreateObject();
		if(pOb != NULL) pOb->SayHello();
	}
	*/

	CMyDoc* pMyDoc = new CMyDoc();
	CMyView* pMyView = new CMyView();
	CFrameWnd* pMyFrame = (CMyFrameWnd*)pApp->m_pMainWnd;
	pMyFrame->m_pViewActive = pMyView;
	pMyView->m_pDocument = pMyDoc;

	// test message routing
	cout << endl << "pMyFrame received a WM_CREATE, routint path:" << endl;
	AfxWndProc(0, WM_CREATE, 0, 0, pMyFrame);

	cout << endl << "pMyView received a WM_PAINT, routint path:" << endl;
	AfxWndProc(0, WM_PAINT, 0, 0, pMyView);

	cout << endl << "pMyView received a WM_COMMAND, routint path:" << endl;
	AfxWndProc(0, WM_COMMAND, 0, 0, pMyView);

	cout << endl << "pMyFrame received a WM_COMMAND, routint path:" << endl;
	AfxWndProc(0, WM_COMMAND, 0, 0, pMyFrame);


/*
	cout << endl << "CMyView Message Map: " << endl;
	MsgMapPrinting(pMyView->GetMessageMap());

	cout << endl << "CMyDoc Message Map: " << endl;
	MsgMapPrinting(pMyDoc->GetMessageMap());

	cout << endl << "CMyFrame Message Map: " << endl;
	MsgMapPrinting(pMyFrame->GetMessageMap());

	cout << endl << "CMyWinApp Message Map: " << endl;
	MsgMapPrinting(pApp->GetMessageMap());
	*/

	return 0;
}
