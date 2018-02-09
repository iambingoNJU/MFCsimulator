#include <iostream>
using namespace std;

#define BOOL int
#define TRUE 1

class CObject {
public:
	CObject() { cout << "CObject Constructor \n"; }
	~CObject() { cout << "CObject Destructor \n"; }
};


class CCmdTarget : public CObject {
public:
	CCmdTarget() { cout << "CCmdTarget Constructor \n"; }
	~CCmdTarget() { cout << "CCmdTarget Destructor \n"; }
};


class CWinThread : public CCmdTarget {
public:
	CWinThread() { cout << "CWinThread Constructor \n"; }
	~CWinThread() { cout << "CWinThread Destructor \n"; }

	virtual BOOL InitInstance() {
		cout << "CWinThread::InitInstance\n";
		return TRUE;
	}

	virtual int Run() {
		cout << "CWinThread::Run\n";
		return 1;
	}
};

class CDocument : public CCmdTarget {
public:
	CDocument() { cout << "CDocument Constructor \n"; }
	~CDocument() { cout << "CDocument Destructor \n"; }
};


class CWnd : public CCmdTarget {
public:
	CWnd() { cout << "CWnd Constructor \n"; }
	~CWnd() { cout << "CWnd Destructor \n"; }
	virtual BOOL Create();
	BOOL CreateEx();
	virtual BOOL PreCreateWindow();
};

class CWinApp : public CWinThread {
public:
	CWinApp* m_pCurrentWinApp;
	CWnd* m_pMainWnd;

public:
	CWinApp() { m_pCurrentWinApp = this;  cout << "CWinApp Constructor \n"; }
	~CWinApp() { cout << "CWinApp Destructor \n"; }

	virtual BOOL InitApplication() {
		cout << "CWinApp::InitApplication\n";
		return TRUE;
	}

	virtual BOOL InitInstance() {
		cout << "CWinApp::InitInstance\n";
		return TRUE;
	}

	virtual int Run() {
		cout << "CWinApp:Run\n";
		return CWinThread::Run();
	}
};



class CFrameWnd : public CWnd {
public:
	CFrameWnd() { cout << "CFrameWnd Constructor \n"; }
	~CFrameWnd() { cout << "CFrameWnd Destructor \n"; }
	BOOL Create();
	virtual BOOL PreCreateWindow();
};


class CView : public CWnd {
public:
	CView() { cout << "CView Constructor \n"; }
	~CView() { cout << "CView Destructor \n"; }
};


// Global function

CWinApp* AfxGetApp();
