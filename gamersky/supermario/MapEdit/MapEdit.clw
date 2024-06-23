; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMapWidthDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MapEdit.h"
LastPage=0

ClassCount=7
Class1=CMapEditApp
Class2=CMapEditDoc
Class3=CMapEditView
Class4=CMainFrame

ResourceCount=6
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Resource3=IDD_OBJECTTYPE
Resource4=IDR_MAINFRAME (English (U.S.))
Class6=CMapWidthDlg
Resource5=IDD_MAPWIDTH
Class7=CObjectTypeDlg
Resource6=IDD_ABOUTBOX (English (U.S.))

[CLS:CMapEditApp]
Type=0
HeaderFile=MapEdit.h
ImplementationFile=MapEdit.cpp
Filter=N

[CLS:CMapEditDoc]
Type=0
HeaderFile=MapEditDoc.h
ImplementationFile=MapEditDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CMapEditDoc

[CLS:CMapEditView]
Type=0
HeaderFile=MapEditView.h
ImplementationFile=MapEditView.cpp
Filter=C
BaseClass=CScrollView
VirtualFilter=VWC
LastObject=CMapEditView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=MapEdit.cpp
ImplementationFile=MapEdit.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command10=ID_EDIT_PASTE
Command11=ID_VIEW_TOOLBAR
Command12=ID_VIEW_STATUS_BAR
Command13=ID_APP_ABOUT
CommandCount=13
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
CommandCount=13
Command4=ID_EDIT_UNDO
Command13=ID_PREV_PANE


[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_BRICK1
Command5=ID_BRICK2
Command6=ID_BRICK3
Command7=ID_GRASS
Command8=ID_CLOUD
Command9=ID_HILL
Command10=ID_MARK
Command11=ID_TUBE
Command12=IDB_BUILDING
Command13=ID_GHOST1
Command14=ID_GHOST2
Command15=ID_GHOST3
Command16=ID_APP_ABOUT
CommandCount=16

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_MAPWIDTH
Command9=ID_APP_ABOUT
CommandCount=9

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_MAPWIDTH]
Type=1
Class=CMapWidthDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_WIDTH,edit,1350631552
Control5=IDC_DARKEN,button,1342242819

[CLS:CMapWidthDlg]
Type=0
HeaderFile=MapWidthDlg.h
ImplementationFile=MapWidthDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CMapWidthDlg
VirtualFilter=dWC

[DLG:IDD_OBJECTTYPE]
Type=1
Class=CObjectTypeDlg
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_COIN,button,1342308361
Control5=IDC_MUSHROOM,button,1342177289
Control6=IDC_HIDDEN,button,1342242819

[CLS:CObjectTypeDlg]
Type=0
HeaderFile=ObjectTypeDlg.h
ImplementationFile=ObjectTypeDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CObjectTypeDlg

