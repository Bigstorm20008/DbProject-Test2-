#pragma once

#include <Windows.h>
#include <commctrl.h>
#include <vector>
#include "SqlBinding.h"

#pragma comment(lib, "ComCtl32.Lib")


//This class create ListView for ClientView and show main information about all client in database
class ListView 
{
private:
	HWND m_listParent;
	
	HWND m_listWnd;  
	int m_numCols;
	TCHAR* getColumnName(int subItem);
	void deleteAllColumn();
public:	
	void clear();
	//void InitListView();                                        
	void DestroyListView();              
	//void setFocusOnItem();
	//void deleteSelectedPerson();
	HWND getHandleOfList() const;
	void fillList(std::vector<std::vector<SqlBinding*>*>* m_queryResult);
	ListView(HWND parent, int xPos, int yPos, int listWidth, int listHeight);
	~ListView();
};

