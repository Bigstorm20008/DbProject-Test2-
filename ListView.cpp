#include "ListView.h"


ListView::ListView(HWND parent, int xPos, int yPos, int listWidth, int listHeight)
{
	m_numCols = 0;
	m_listParent = parent;
	
	InitCommonControls();

	//Create control ListView
	m_listWnd = CreateWindow(WC_LISTVIEW,
		                     NULL,
						     WS_CHILD | LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL |WS_BORDER,
		                     xPos, yPos,
							 listWidth, listHeight,
		                     parent,
						     (HMENU)NULL,   //defined in Constants.h
		                     reinterpret_cast<HINSTANCE>(GetWindowLong(NULL, GWLP_HINSTANCE)),
		                     NULL);
	//Extended style for ListView
	ListView_SetExtendedListViewStyleEx(m_listWnd, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE| LVS_EX_DOUBLEBUFFER);
	ShowWindow(m_listWnd, SW_NORMAL);
}


ListView::~ListView()
{

}

HWND ListView::getHandleOfList() const
{
	return m_listWnd;
}


void ListView::DestroyListView()
{
	DestroyWindow(m_listWnd);  

}

TCHAR* ListView::getColumnName(int subItem)
{	
	const size_t columnTextLenght = 30;
	TCHAR szText[columnTextLenght];
	LVCOLUMN lvcolumn;
	lvcolumn.mask = LVCF_TEXT;                //column contains text and defined width of column	    
	lvcolumn.cchTextMax = columnTextLenght;
	lvcolumn.pszText = szText;
	//maximum characters in columnname
	ListView_GetColumn(m_listWnd, subItem, &lvcolumn);
	return lvcolumn.pszText;
}

void ListView::fillList(std::vector<std::vector<SqlBinding*>*>* m_queryResult)
{
	ListView_DeleteAllItems(m_listWnd);
	deleteAllColumn();
	m_numCols = m_queryResult->at(0)->size();
	LVCOLUMN lvc;
	lvc.mask = LVCF_TEXT | LVCF_WIDTH;  //column contains text and defined width of column
	lvc.cx = 500 / m_numCols;      //width of column = width of listview / count of columns
	lvc.cchTextMax = 30;
	int index = 0;
	for (auto& elem : *m_queryResult)
	{
		for (auto& elemRow : *elem)
		{
			lvc.pszText = elemRow->getColumnName();   //save column name to lvc.pszText
			ListView_InsertColumn(m_listWnd, index++, &lvc);  //insert column in listview and increase counter of column
		}
		break;
	}

	LVITEM lvi;
	lvi.mask = LVIF_TEXT;
	lvi.cchTextMax = 30;
	lvi.iItem = 0;
	lvi.iSubItem = 0;
	lvi.pszText = TEXT("");

	for (auto& elem : *m_queryResult)
	{
		ListView_InsertItem(m_listWnd, &lvi);
		for (auto& elemRow : *elem)
		{
			lvi.pszText = elemRow->getDescription();
			ListView_SetItemText(m_listWnd, lvi.iItem, lvi.iSubItem, lvi.pszText);
			++lvi.iSubItem;
		}
		++lvi.iItem;
		lvi.iSubItem = 0;
	}	
	//ShowWindow(m_listWnd, SW_NORMAL);
}

void ListView::deleteAllColumn()
{
	for (int i = m_numCols - 1; i >= 0; i--)
	{
		ListView_DeleteColumn(m_listWnd, i);
	}
}

void ListView::clear()
{
	ListView_DeleteAllItems(m_listWnd);
	deleteAllColumn();
}

