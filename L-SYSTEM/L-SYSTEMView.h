
// L-SYSTEMView.h : CLSYSTEMView ��Ľӿ�
//

#pragma once
#include <map>
#include <strstream>
#include <queue>
#include <float.h>
#include <math.h>

class CLSYSTEMView : public CView
{
protected: // �������л�����
	CLSYSTEMView();
	DECLARE_DYNCREATE(CLSYSTEMView)
public:
	class node
	{
	public:
		char key;	//������ĸ
		double x,y;	//��ǰλ��xy
		int	l;		//��ǰ���
		long double a;//��ǰ�Ƕ�
		double w;	//�߿�
		bool isrev;	//�Ƿ񽻻�+-
		double len;	//����
		long double ap;//������
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
// ����
public:
	CLSYSTEMDoc* GetDocument() const;

// ����
public:
	char* DrawStr(char *s,node &n);
	void DrawNode(node &n);
// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CLSYSTEMView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // L-SYSTEMView.cpp �еĵ��԰汾
inline CLSYSTEMDoc* CLSYSTEMView::GetDocument() const
   { return reinterpret_cast<CLSYSTEMDoc*>(m_pDocument); }
#endif

