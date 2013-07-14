
// L-SYSTEMView.h : CLSYSTEMView 类的接口
//

#pragma once
#include <map>
#include <strstream>
#include <queue>
#include <float.h>
#include <math.h>

class CLSYSTEMView : public CView
{
protected: // 仅从序列化创建
	CLSYSTEMView();
	DECLARE_DYNCREATE(CLSYSTEMView)
public:
	class node
	{
	public:
		char key;	//代表字母
		double x,y;	//当前位置xy
		int	l;		//当前深度
		long double a;//当前角度
		double w;	//线宽
		bool isrev;	//是否交换+-
		double len;	//步长
		long double ap;//角增量
		node(){}
		node(char k,double xx,double yy,int ll,long double aa,double ww,
			bool ir,double plen,long double pap):key(k),x(xx),
			y(yy),l(ll),a(aa),w(ww),isrev(ir),len(plen),ap(pap){}
	};
private:
	std::map<char,CString> map;
//	std::queue<node> queue;
	CClientDC *cdc;
	CString initStr;
	CString iterStr;
	int itDeep;
	long double angle;
	long double PI2;
	//int dl;
	int stepLen;
	int width;
	long double angofs;
	double lenmut;
	int widofs;
	CPen *pen;
	CPen *oldpen;
	CBrush *oldbrush;
	CBrush *brush;
 	CPoint mouse;
	CPoint offset;
	COLORREF fcolor;
	COLORREF oldcolor;
	bool mdown;
// 特性
public:
	CLSYSTEMDoc* GetDocument() const;

// 操作
public:
	char* DrawStr(char *s,node &n);
	void DrawNode(node &n);
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CLSYSTEMView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileNew();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnResetOffset();
	afx_msg void OnExportImage();
	afx_msg void OnSetColor();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // L-SYSTEMView.cpp 中的调试版本
inline CLSYSTEMDoc* CLSYSTEMView::GetDocument() const
   { return reinterpret_cast<CLSYSTEMDoc*>(m_pDocument); }
#endif

