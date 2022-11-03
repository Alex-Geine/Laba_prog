
// Laba_progDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "Laba_prog.h"
#include "Laba_progDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CLabaprogDlg



CLabaprogDlg::CLabaprogDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LABA_PROG_DIALOG, pParent)
	, Phase(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLabaprogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Phase);
}

BEGIN_MESSAGE_MAP(CLabaprogDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CLabaprogDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Обработчики сообщений CLabaprogDlg

BOOL CLabaprogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	Graph_Sign.Create(GetDlgItem(IDC_SIGN)->GetSafeHwnd());
	Graph_ACH.Create(GetDlgItem(IDC_ACH)->GetSafeHwnd());
	Graph_FCH.Create(GetDlgItem(IDC_FCH)->GetSafeHwnd());
		
	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CLabaprogDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CLabaprogDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CLabaprogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//Создает сигнал и отсчеты
//fd - частота дискретизации
//f -  частота сигнала
//phase - начальная фаза
//K - множитель амплитуды
//SignR - реальная часть сигнала
//SignI - мнимая
void CreateSign(double* SignR, double * SignI, double* keys, int N, double fd, double f, double phase, double K) {
	for (int i = 0; i < N; i++) {
		SignR[i] = K * sin(2 * Pi * f * (i / fd) + phase);
		SignI[i] = 0;
		keys[i] = i / fd;
	}
}

//кнопка, которая измеряет сигналы
void CLabaprogDlg::OnBnClickedOk()
{
	UpdateData(true);

	Graph_Sign.DrawW();
	Graph_ACH.DrawW();
	Graph_FCH.DrawW();
	
	

	//Проверка корректности работы этой херни
	int N = 256;
	double fd = 100;

	Signal_Analise Data(1);

	double
		* Sign1, //первый сигнал Re
		* Sign2, //второй сигнал Re
		* Sign1Im, //первый сигнал Im
		* Sign2Im, //второй сигнал Im
		* keys1, //ключи(хз зачем но путь будут)
		* keys2;
	Sign1 = new double[N];
	Sign2 = new double[N];
	Sign1Im = new double[N];
	Sign2Im = new double[N];
	keys1 = new double[N];
	keys2 = new double[N];

	CreateSign(Sign1, Sign1Im, keys1, N, fd, 1, 0, 1); //входной сигнал
	CreateSign(Sign2, Sign1Im, keys2, N, fd, 1, 1, 2); //выходной сигнал

	Data.FFT(Sign1, Sign1Im, N, log2(N), -1); // прямое фурье
	Data.FFT(Sign2, Sign2Im, N, log2(N), -1); // прямое фурье
	Data.FCH_Find(Sign1, Sign1Im, Sign2, Sign2Im, N);// находим ФЧХ для данной частоты

	Phase = Data.GetLastFCH();

	UpdateData(false);

}
