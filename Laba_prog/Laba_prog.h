
// Laba_prog.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CLabaprogApp:
// Сведения о реализации этого класса: Laba_prog.cpp
//

class CLabaprogApp : public CWinApp
{
public:
	CLabaprogApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CLabaprogApp theApp;
