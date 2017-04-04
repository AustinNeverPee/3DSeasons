// WalkCamera.h: interface for the WalkCamera class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WALKCAMERA_H__2882EBBF_ABBA_4459_8C01_FF37943A1B84__INCLUDED_)
#define AFX_WALKCAMERA_H__2882EBBF_ABBA_4459_8C01_FF37943A1B84__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define dTheta  0.02
#define dAlpha 0.01
#define dStep 2
#define D 1


class WalkCamera	//	���������
{
public:
	WalkCamera(float eyex, float eyey, float eyez);
	virtual ~WalkCamera();

	void Backward();

	void Forward();

	void Down();

	void Up();

	void Right();

	void Left();

	void Look();		//		

protected:
	float m_fEye[3];	//	�����λ��
		
	float m_fAlpha;		//	����ĸ�����
	float m_fTheta;		//	�����ƫ����
};

#endif // !defined(AFX_WALKCAMERA_H__2882EBBF_ABBA_4459_8C01_FF37943A1B84__INCLUDED_)
