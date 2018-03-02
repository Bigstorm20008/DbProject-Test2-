#pragma once

#include <Windows.h>
#include <tchar.h>

#include "Constants.h"

class EditControlTemplate
{
public:
	EditControlTemplate(HWND parent, int editXPos, int editYPos, int editWidth, int editHeight, UINT editStyle);
	~EditControlTemplate();

	
	void createDescriptionForEdit(TCHAR* descriptionText);
	void setFontForEdit(HFONT hFont);
	TCHAR* getTextFromEdit();
	void setFocusOnEdit();
	HWND getEditHandle() const;
	void setNewTextForEdit(TCHAR* newText);
private:
	LONG_PTR m_oldEditProc;
	static LRESULT CALLBACK EditProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	UINT m_btnIdentifier;

	void createEditControl(HWND parent, int editXPos, int editYPos, int editWidth, int editHeight, UINT editStyle);
protected:
	LRESULT RealEditProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	HWND m_EdithWnd;
	HWND m_parentOfEdit;
	TCHAR* m_textInEdit;
};

