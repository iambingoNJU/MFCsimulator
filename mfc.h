#include <iostream>
using namespace std;

#define BOOL int
#define TRUE 1
#define FALSE 0
#define LPCSTR LPSTR
typedef char* LPSTR;
#define UINT int
#define PASCAL 

class CObject;

struct CRuntimeClass {
	// Attributes
	LPCSTR m_lpszClassName;
	int m_nObjectSize;
	UINT m_wSchema;		// schema number of the loaded class
	CObject* (PASCAL *m_pfnCreateObject)();	// NULL => abstract class
	CRuntimeClass* m_pBaseClass;

	CObject* CreateObject();
	static CRuntimeClass* PASCAL Load();

	// CRuntimeClass objects linked together in simple list
	static CRuntimeClass* pFirstClass;		// start of class list
	CRuntimeClass* m_pNextClass;			// linked list of registered classes
};

struct AFX_CLASSINIT {
	AFX_CLASSINIT(CRuntimeClass* pNewClass);
};

#define RUNTIME_CLASS(class_name) \
	(&class_name::class##class_name)

#define DECLARE_DYNAMIC(class_name) \
public: \
	static CRuntimeClass class##class_name; \
	virtual CRuntimeClass* GetRuntimeClass() const;

#define _IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, wSchema, pfnNew) \
	static char _lpsz##class_name[] = #class_name; \
	CRuntimeClass class_name::class##class_name = { \
		_lpsz##class_name, sizeof(class_name), wSchema, pfnNew, \
		RUNTIME_CLASS(base_class_name), NULL }; \
	static AFX_CLASSINIT _init##class_name(RUNTIME_CLASS(class_name)); \
	CRuntimeClass* class_name::GetRuntimeClass() const \
		{ return RUNTIME_CLASS(class_name); }

#define IMPLEMENT_DYNAMIC(class_name, base_class_name) \
	_IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, 0xFFFF, NULL)

#define DECLARE_DYNCREATE(class_name) \
	DECLARE_DYNAMIC(class_name) \
	static CObject* PASCAL CreateObject();

#define IMPLEMENT_DYNCREATE(class_name, base_class_name) \
	CObject* PASCAL class_name::CreateObject() \
		{ return new class_name; } \
	_IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, 0xFFFF, class_name::CreateObject)

class CObject {
public:
	CObject() { cout << "CObject Constructor \n"; }
	~CObject() { cout << "CObject Destructor \n"; }

	virtual CRuntimeClass* GetRuntimeClass() const;

	virtual void SayHello() { cout << "Hello CObject" << endl; }

	BOOL IsKindOf(const CRuntimeClass* pClass) const;

public:
	static CRuntimeClass classCObject;
};


class CCmdTarget : public CObject {
	DECLARE_DYNAMIC(CCmdTarget)
public:
	CCmdTarget() { cout << "CCmdTarget Constructor \n"; }
	~CCmdTarget() { cout << "CCmdTarget Destructor \n"; }
};


class CWinThread : public CCmdTarget {
	DECLARE_DYNAMIC(CWinThread)
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
	DECLARE_DYNAMIC(CDocument)
public:
	CDocument() { cout << "CDocument Constructor \n"; }
	~CDocument() { cout << "CDocument Destructor \n"; }
};


class CWnd : public CCmdTarget {
	//DECLARE_DYNAMIC(CWnd)
	DECLARE_DYNCREATE(CWnd)
public:
	CWnd() { cout << "CWnd Constructor \n"; }
	~CWnd() { cout << "CWnd Destructor \n"; }
	virtual BOOL Create();
	BOOL CreateEx();
	virtual BOOL PreCreateWindow();
	void SayHello() { cout << "Hello CWnd" << endl; }
};

class CWinApp : public CWinThread {
	DECLARE_DYNAMIC(CWinApp)
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
	//DECLARE_DYNAMIC(CFrameWnd)
	DECLARE_DYNCREATE(CFrameWnd)
public:
	CFrameWnd() { cout << "CFrameWnd Constructor \n"; }
	~CFrameWnd() { cout << "CFrameWnd Destructor \n"; }
	BOOL Create();
	virtual BOOL PreCreateWindow();
	void SayHello() { cout << "Hello CFrameWnd" << endl; }
};


class CView : public CWnd {
	DECLARE_DYNAMIC(CView)
public:
	CView() { cout << "CView Constructor \n"; }
	~CView() { cout << "CView Destructor \n"; }
};


// Global function

CWinApp* AfxGetApp();
