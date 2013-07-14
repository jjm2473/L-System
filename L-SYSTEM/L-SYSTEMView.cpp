
// L-SYSTEMView.cpp : CLSYSTEMView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "L-SYSTEM.h"
#endif

#include "L-SYSTEMDoc.h"
#include "L-SYSTEMView.h"
#define M_PI       3.14159265358979323846

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLSYSTEMView

IMPLEMENT_DYNCREATE(CLSYSTEMView, CView)

BEGIN_MESSAGE_MAP(CLSYSTEMView, CView)
	//ON_WM_CONTEXTMENU()
	//ON_WM_RBUTTONUP()
	ON_COMMAND(ID_FILE_NEW, &CLSYSTEMView::OnFileNew)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_32773, &CLSYSTEMView::OnResetOffset)
	ON_COMMAND(ID_32775, &CLSYSTEMView::OnExportImage)
	ON_COMMAND(ID_32776, &CLSYSTEMView::OnSetColor)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()

// CLSYSTEMView 构造/析构

CLSYSTEMView::CLSYSTEMView():initStr("---L"),iterStr("L=L++L----L++L"),
	itDeep(5),angle(30.0*acos(-1.0)/180.0),stepLen(3),width(1),
	angofs(0.0),lenmut(1.0),widofs(0),mouse(0,0),offset(300,400),fcolor(0),mdown(false)
{
	// TODO: 在此处添加构造代码
	PI2=M_PI*2.0;
	pen=new CPen(PS_SOLID,1,fcolor);
	brush=new CBrush(fcolor);
	map.insert(std::pair<char,CString> ('#',""));
}

CLSYSTEMView::~CLSYSTEMView()
{
	pen->DeleteObject();
	brush->DeleteObject();
}

BOOL CLSYSTEMView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}




void CLSYSTEMView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CLSYSTEMView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CLSYSTEMView 诊断

#ifdef _DEBUG
void CLSYSTEMView::AssertValid() const
{
	CView::AssertValid();
}

void CLSYSTEMView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLSYSTEMDoc* CLSYSTEMView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLSYSTEMDoc)));
	return (CLSYSTEMDoc*)m_pDocument;
}
#endif //_DEBUG

class CCreatDlg : public CDialog
{
public:
	CCreatDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	CString initStr;
	CString iterStr;
	int itDeep;
	double angle;
	int stepLen;
	int width;
	double angofs;
	double lenmut;
	int widofs;
};
CCreatDlg::CCreatDlg():CDialog(CCreatDlg::IDD)
	, initStr(_T(""))
	, iterStr(_T(""))
	, itDeep(1)
	, angle(0)
	, stepLen(0)
	, width(1)
	, angofs(0.0)
	, lenmut(1.0)
	, widofs(0)
{

}
void CCreatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, initStr);
	DDX_Text(pDX, IDC_EDIT2, iterStr);
	DDX_Text(pDX, IDC_EDIT3, itDeep);
	DDX_Text(pDX, IDC_EDIT4, angle);
	DDX_Text(pDX, IDC_EDIT5, stepLen);
	DDX_Text(pDX, IDC_EDIT6, width);
	DDX_Text(pDX, IDC_EDIT7, angofs);
	DDX_Text(pDX, IDC_EDIT8, lenmut);
	DDX_Text(pDX, IDC_EDIT9, widofs);
}

BEGIN_MESSAGE_MAP(CCreatDlg, CDialog)
END_MESSAGE_MAP()

// CLSYSTEMView 绘制

void CLSYSTEMView::OnDraw(CDC* pDC)
{
	CLSYSTEMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此处为本机数据添加绘制代码
	oldpen=cdc->SelectObject(pen);
	oldbrush=cdc->SelectObject(brush);
	DrawNode(node('#',offset.x,offset.y,0,acos(-1.0)/2.0,width,false,(double)stepLen,angle));
	cdc->SelectObject(oldbrush);
	cdc->SelectObject(oldpen);
}

// CLSYSTEMView 消息处理程序
void CLSYSTEMView::OnFileNew()
{
	// TODO: 在此添加命令处理程序代码
	CCreatDlg creat;
	char str[128];
	creat.initStr=initStr;
	creat.iterStr=iterStr;
	creat.itDeep=itDeep;
	creat.angle=angle*180.0/M_PI;
	creat.stepLen=stepLen;
	creat.width=width;
	creat.angofs=angofs*180.0/M_PI;
	creat.lenmut=lenmut;
	creat.widofs=widofs;
	while(1)
	{
		if(creat.DoModal()==2)break;
		creat.initStr.Remove(' ');
		if(creat.initStr.IsEmpty())continue;
		creat.iterStr.Remove(' ');
		initStr=creat.initStr;
		iterStr=creat.iterStr;
		itDeep=creat.itDeep;
		angle=creat.angle*M_PI/180.0;
		stepLen=creat.stepLen;
		width=creat.width;
		angofs=creat.angofs*M_PI/180.0;
		lenmut=creat.lenmut;
		widofs=creat.widofs;
		std::strstream iterStr(creat.iterStr.GetBuffer(),std::streamsize(creat.iterStr.GetLength()));
		map.clear();
		//map.insert(std::pair<char,CString> ('#',initStr));
		map['#']=initStr;
		while(!iterStr.eof()){
			iterStr.getline(str,std::streamsize(sizeof(str)));
			for(int i=0;str[i]!='\0';i++)
			{
				if(str[i]=='\r')str[i]='\0';
			}
			if(str[0]!=0)map[str[0]]=CString(str+2);
		}

		this->Invalidate();
		/*
		//clear screen
		
		this->UpdateWindow();

		//Creat graphic
		oldpen=cdc->SelectObject(pen);
		DrawNode(node('#',offset.x,offset.y,0,acos(-1.0)/2.0));
		cdc->SelectObject(oldpen);
		*/
		break;
	}
}
char *CLSYSTEMView::DrawStr(char *s,node &n)
{
	bool po;
	CPen *tmpn=new CPen(PS_SOLID,n.w,fcolor);
	CPen *tmpo;
	(cdc->SelectObject(tmpn))->DeleteObject();
	tmpo=tmpn;
	while(*s!=0)
	{
		switch(*s)
		{
		case '+':
		case '-':
			po=*s=='+'?true:false;
			if(po^n.isrev)n.a+=n.ap;
			else n.a-=n.ap;
			if(n.a>PI2)n.a-=PI2;
			else if(n.a<0.0)n.a+=PI2;
			break;
		case '|':
			n.a=-n.a;
			n.a+=PI2;
			break;
		case '&':
			n.isrev=!n.isrev;
			break;
		case '#':
		case '!':
			if(*s=='#')n.w+=widofs;
			else {
				n.w-=widofs;
				if(n.w<0.0)n.w=_chgsign(n.w);
			}
			tmpn=new CPen(PS_SOLID,n.w,fcolor);
			(cdc->SelectObject(tmpn))->DeleteObject();
			delete tmpo;
			tmpo=tmpn;
			break;
		case '<':
			n.len/=lenmut;
			break;
		case '>':
			n.len*=lenmut;
			break;
		case '(':
			n.ap-=angofs;
			break;
		case ')':
			n.ap+=angofs;
			break;
		case '[':
			s=DrawStr(s+1,node(n));
			tmpn=new CPen(PS_SOLID,n.w,fcolor);
			(cdc->SelectObject(tmpn))->DeleteObject();
			delete tmpo;
			tmpo=tmpn;
			break;
		case ']':
			goto eow;
			break;
		case '@':
			cdc->Ellipse(n.x-n.w-0.5,n.y-n.w-0.5,n.x+n.w+0.5,n.y+n.w+0.5);
			break;
		default:
			if(n.l==itDeep)
			{
				if(*s>='A'&&*s<='Z')cdc->MoveTo(n.x,n.y);
				n.x+=cos(n.a)*n.len;
				n.y-=sin(n.a)*n.len;
				if(*s>='A'&&*s<='Z'){cdc->LineTo(n.x,n.y);}
			}else{
				n.key=*s;
				n.l+=1;
				DrawNode(n);
				n.l-=1;
			}
		}
		++s;
	}
	eow:
	tmpo->DeleteObject();
	delete tmpo;
	return s;
}
void CLSYSTEMView::DrawNode(node &n)
{
	if(n.l>itDeep)return;
	std::map<char,CString>::iterator it;
	if((it=map.find(n.key))==map.end())
	{
		char str[2]=" ";
		str[0]=n.key;
		map.insert(std::pair<char,CString>(n.key,str));
		DrawStr(str,n);
	}else{
		DrawStr(it._Ptr->_Myval.second.GetBuffer(),n);
	}
}


void CLSYSTEMView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	mouse=point;
	//
	mdown=true;
	CView::OnLButtonDown(nFlags, point);
}


void CLSYSTEMView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(mdown){
		offset+=(point-mouse);
		this->Invalidate();
		mdown=false;
	}
	/*
	oldpen=cdc->SelectObject(pen);
	DrawNode(node('#',offset.x,offset.y,0,acos(-1.0)/2.0));
	cdc->SelectObject(oldpen);*/
	CView::OnLButtonUp(nFlags, point);
}


void CLSYSTEMView::OnResetOffset()
{
	// TODO: 在此添加命令处理程序代码
	offset.x=300;
	offset.y=400;
	this->Invalidate();
	this->UpdateWindow();
	/*
	oldpen=cdc->SelectObject(pen);
	DrawNode(node('#',offset.x,offset.y,0,acos(-1.0)/2.0));
	cdc->SelectObject(oldpen);*/
}


void CLSYSTEMView::OnExportImage()
{
	// TODO: 在此添加命令处理程序代码
	CImage image;
	CBitmap *bm=cdc->GetCurrentBitmap();
	image.Attach((HBITMAP)bm->GetSafeHandle());
	CFileDialog exportdlg(false,"bmp","*.bmp",NULL,"位图文件(*.bmp)|*.bmp|JPEG 图像文件|*.jpg|GIF 图像文件|*.gif|PNG 图像文件|*.png|");
	if(exportdlg.DoModal()==IDOK)
	{
		CString path=exportdlg.GetPathName();
		image.Save(path);
	}
}


void CLSYSTEMView::OnSetColor()
{
	// TODO: 在此添加命令处理程序代码
	CColorDialog colordlg(fcolor);
	if(colordlg.DoModal()==IDOK){
		fcolor=colordlg.GetColor();
		pen->DeleteObject();
		delete pen;
		pen=new CPen(PS_SOLID,1,fcolor);
		brush->DeleteObject();
		delete brush;
		brush=new CBrush(fcolor);
		this->Invalidate();
		this->UpdateWindow();
		/*oldpen=cdc->SelectObject(pen);
		DrawNode(node('#',offset.x,offset.y,0,acos(-1.0)/2.0));
		cdc->SelectObject(oldpen);*/
	}
}


int CLSYSTEMView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	cdc=new CClientDC(this);
	return 0;
}

