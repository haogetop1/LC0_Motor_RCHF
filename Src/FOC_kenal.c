#include "main.h"
#include <math.h> 

#define PWM_Period 100
#define _PI 3.14159265359
#define _PI_2 1.57079632679
#define _PI_3 1.0471975512
#define _2PI 6.28318530718
#define _3PI_2 4.71238898038
#define _PI_6 0.52359877559
#define _SQRT3 1.73205080757

float voltage_power;

float _normalizeAngle(float angle)
{
  float a = fmod(angle, _2PI);                     //fmod()ȡ�ຯ��
  return a >= 0 ? a : (a + _2PI);
}

/** @biref FOC���ĺ���,����Ud��Uq�͵�Ƕȣ����PWM
*	@param Ud
*	@param Uq
*	@param ��Ƕ�
*/

void SetPhaseVoltage(float Uq, float Ud, float angle_el)
{
	float Uref;
	float U_alpha,U_beta;
	float T0,T1,T2;
	float Ta,Tb,Tc;
	int sector;
	
	//��park�任
	U_alpha=Ud*cos(angle_el)-Uq*sin(angle_el);            
	U_beta=Ud*sin(angle_el)+Uq*cos(angle_el);
	
	Uref=_sqrt(U_alpha*U_alpha + U_beta*U_beta) / voltage_power;    //����ο���ѹʸ���ķ�ֵ
	
	//�����ε�����Բ(SVPWM���ʧ����ת��ѹʸ����ֵ)����3/3
	if(Uref> 0.577)Uref= 0.577;                     			
	if(Uref<-0.577)Uref=-0.577; 
	
	//�жϲο���ѹʸ������������
	angle_el = _normalizeAngle(angle_el+_PI_2);           //��׼����Ƕ�ֵ��0,2pi������90�Ⱥ��ǲο���ѹʸ����λ��
	sector = (angle_el / _PI_3) + 1; 
	
	T1 = _SQRT3*sin(sector*_PI_3 - angle_el) * Uref;           //�����������ڵ�ѹʸ������ʱ��
	T2 = _SQRT3*sin(angle_el - (sector-1.0)*_PI_3) * Uref;
	T0 = 1 - T1 - T2;                                          //��ʸ������ʱ��
	
	switch(sector)
	{
		case 1:
			Ta = T1 + T2 + T0/2;
			Tb = T2 + T0/2;
			Tc = T0/2;
			break;
		case 2:
			Ta = T1 +  T0/2;
			Tb = T1 + T2 + T0/2;
			Tc = T0/2;
			break;
		case 3:
			Ta = T0/2;
			Tb = T1 + T2 + T0/2;
			Tc = T2 + T0/2;
			break;
		case 4:
			Ta = T0/2;
			Tb = T1+ T0/2;
			Tc = T1 + T2 + T0/2;
			break;
		case 5:
			Ta = T2 + T0/2;
			Tb = T0/2;
			Tc = T1 + T2 + T0/2;
			break;
		case 6:
			Ta = T1 + T2 + T0/2;
			Tb = T0/2;
			Tc = T1 + T0/2;
			break;
		default:  // possible error state
			Ta = 0;
			Tb = 0;
			Tc = 0;
	}
	FL_ATIM_WriteCompareCH1(ATIM,Ta*PWM_Period);
	FL_ATIM_WriteCompareCH2(ATIM,Tb*PWM_Period);
	FL_ATIM_WriteCompareCH3(ATIM,Tc*PWM_Period);
}
