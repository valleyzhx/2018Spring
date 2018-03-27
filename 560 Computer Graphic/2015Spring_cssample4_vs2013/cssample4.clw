; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCssample4View
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "cssample4.h"
LastPage=0

ClassCount=5
Class1=CCssample4App
Class2=CCssample4Doc
Class3=CCssample4View
Class4=CMainFrame

ResourceCount=2
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Resource2=IDD_ABOUTBOX

[CLS:CCssample4App]
Type=0
HeaderFile=cssample4.h
ImplementationFile=cssample4.cpp
Filter=N

[CLS:CCssample4Doc]
Type=0
HeaderFile=cssample4Doc.h
ImplementationFile=cssample4Doc.cpp
Filter=N

[CLS:CCssample4View]
Type=0
HeaderFile=cssample4View.h
ImplementationFile=cssample4View.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=ID_VIEW_WIREFRAME


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=ID_VIEW_POS_INCZ




[CLS:CAboutDlg]
Type=0
HeaderFile=cssample4.cpp
ImplementationFile=cssample4.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_VIEW_TEXTURE_ENABLE
Command2=ID_VIEW_TEXTURE_DISABLE
CommandCount=2

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
Command9=ID_VIEW_WIREFRAME
Command10=ID_VIEW_FILLED
CommandCount=10

