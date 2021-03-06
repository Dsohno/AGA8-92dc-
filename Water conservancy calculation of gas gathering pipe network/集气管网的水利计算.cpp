// 集气管网的水利计算.cpp: 定义控制台应用程序的入口点。
//使用动态数组well和newwell时为何会引发异常？？

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <stdio.h>

using namespace std;

typedef struct WellheadParameter {
	double Flow=0;
	double PipeLong=0;
	double Pipe_flow= 0;
	double Pressure = 0;

}WP;

//前苏联公式中的系数选择
#define Cs 0.3930
#define Ψ 1
#define E 0.925
#define A 1

void GetInput(ifstream& input, int& arry_size, WP *well, double& pr, double& r, double& z, double& t, int& outlet, double& pmax, double& pmin);
//获取测试输入
void GetInput(int& arry_size, WP *well, double& pr, double& r, double& z, double& t, int& outlet, double& pmax, double& pmin);
//获取输入
double Calculate_Qi(const WP *well, int GSP, const double Q1);
//顺时针计算第i个节点的气体流量

double Calculate_Qi(const WP *well, const int outlet, const int GSP, const double Q1, int arry_size);
//逆时针计算第i个节点的气体流量

void Sortwell(const WP *well, WP *newwell, const int GSp, const int arry_size, int& newoutlet);
//重新排序井口节点

double Calculate_Q1(const WP *well, const int outlet, const int arry_size);
//迭代计算Q1的值

double Calculate_fx(const WP *well, const int outlet, const int arry_size, double Q1);
//计算fx的值

void Input_S_P_Flow(double Q1, WP *well, const int arry_size, const int outlet, const double pr, const double r, const double t, const double z, const double pmax, const double pmin);
//输出各分气点的位置并计算管道的直径
//前提条件：各管段的管径都相等



int main()
{
	int arry_size = 0, outlet=0;
	double pr = 0,  //相对密度
		r = 0,		//阻力系数
		z = 1,      // 压缩因子
		t = 273,    //温度k
		pmax=0,     //最大压力pa
		pmin=0;     //最小压力Pa

	WP well[100];   //井口流量和井间距离
	//well = new WP[arry_size];
	double Q1 = 0, Qn = 0;
	int GSP=0; //分气点位置,表示well数组移动的方向和距离，若为1，则表示顺时针方向移动了一个数字。
	WP newwell[100];
	//newwell = new WP[arry_size];

	char y = 'y';
	while (y != 'N' && y != 'n')
	{
		cout << "是否启用测试用例（Y/N）";
		char a='y';
		cin >> a;
		if (a == 'y' || a == 'Y')
		{
			ifstream input;
			input.open("text.txt");
			if (input.fail())
				cout << "测试用例打开失败";
			GetInput(input,arry_size, well, pr, r, z, t, outlet,pmax,pmin);
		}
		else
			GetInput(arry_size, well,pr,r,z,t,outlet,pmax,pmin);
		//计算初始点
		while (!(Q1 > 0 && Qn > 0))
		{
			Sortwell(well, newwell, GSP, arry_size, outlet);
			Q1 = Calculate_Q1(newwell, outlet, arry_size);
			Qn = newwell[0].Flow - Q1;
			if (Q1 > 0 && Qn > 0)
				break;
			if (GSP == 0)
			{
				if (Qn < 0)
					GSP = arry_size - 1;
				if (Q1 < 0)
					GSP++;
			}
			else if (GSP != 0)
			{
				if (Q1 < 0)
					GSP++;
				if (Qn < 0)
					GSP--;
			}
		}
		cout <<"分气点位置为："<<GSP+1<<endl;
		Input_S_P_Flow(Q1, well, arry_size,outlet,pr,r,t,z,pmax,pmin);
		cout << "继续下一次运算（Y/N）";
		cin >> y;
	}
	//delete[] well;
	//delete[] newwell;
    return 0;
}

void GetInput(ifstream& input, int& arry_size, WP *well, double& pr, double& r, double& z, double& t, int& outlet, double& pmax, double& pmin)
{
	input >> arry_size;
	input >> outlet;
	outlet -= 1;
	input >> pr;
	input >> r;
	input >> z;
	input >> t;
	input >> pmax;
	input >> pmin;
	pmax *= 1000000;
	pmin *= 1000000;
	for (int i = 0; i < arry_size; i++)
	{
		if (i != outlet)
		{
			input >> well[i].Flow;
			input >> well[i].PipeLong;
		}
		else
		input >> well[i].PipeLong;
		//化单位
		well[i].PipeLong *= 1000;
		well[i].Flow =well[i].Flow * 10000/(24*6);
	}
}


void GetInput(int& arry_size, WP *well, double& pr, double& r, double& z, double& t, int& outlet, double& pmax, double& pmin)
{
	cout << "输入节点数量：";
	cin >> arry_size;
	cout << "出气口次序：";
	cin >> outlet;
	outlet -= 1;
	cout << "相对密度：";
	cin >> pr;
	cout << "摩擦阻力系数λ：";
	cin >> r;
	cout << "压缩因子Z：";
	cin >> z;
	cout << "温度（K）：";
	cin >> t;
	cout << "管网最高压力（MPa）：";
	cin >> pmax;
	cout << "管网最低压力（MPa）：";
	cin >> pmin;
	pmax *= 1000000;
	pmin *= 1000000;
	cout << "井口产量的单位为：0.00001*Nm³/d，井间距的单位为：Km";
	for (int i = 0; i < arry_size; i++)
	{
		if (i != outlet - 1)
		{
			cout << "第"<<i+1<<"个井口的参数产量为：";
			cin >> well[i].Flow;
		}
		cout << "第" << i + 1 << "个井口的参数井间距为：";
		cin >> well[i].PipeLong;

		//化单位
		well[i].PipeLong *= 1000;
		well[i].Flow *= 1.157;
	}
}

//重新排序进口个节点
void Sortwell(const WP *well, WP *newwell, const int GSP, const int arry_size, int& outlet)
{
	for (int i = 0; i < arry_size; i++)
	{
		if ((i + GSP) < arry_size)
			newwell[i] = well[i + GSP];
		else
			newwell[i] = well[i + GSP - arry_size];
	}
	if(GSP<outlet)
		outlet -= GSP;
	else if(GSP>outlet)
		outlet=10-(GSP-outlet);
}


//顺时针计算第i个节点的气体流量
double Calculate_Qi(const WP *well, int GSP, const double Q1)
{
	double Qi = Q1;
	for (int i=0; i < GSP; i++)
		Qi += well[i+1].Flow;
	//cout <<GSP <<"   Qi: " << Qi << endl;
	return Qi;
}

//逆时针计算第i个节点的气体流量
double Calculate_Qi(const WP *well, int GSP, const double Qn, int arry_size)
{
	double Qi = Qn;
	int j = 0;
	for (j = arry_size-1; j > GSP; j--)
		Qi += well[j].Flow;
	//cout << GSP << "   Qi: " << Qi << endl;
	return Qi;
}

//迭代计算Q1的值
double Calculate_Q1(const WP *well,const int outlet,const int arry_size)
{
	double Q1=0,Q2=50;
	while (Q1 - Q2 > 0.0000001 || Q2 - Q1 > 0.0000001)
	{
		double fx = Calculate_fx(well, outlet, arry_size, 0.5*(Q1 + Q2)),
			fx1 = Calculate_fx(well, outlet, arry_size, Q1),
			fx2 = Calculate_fx(well, outlet, arry_size, Q2);
		if (fx1 < 0&& fx2>0)
		{
			if (fx < 0)
				Q1 = 0.5*(Q1 + Q2);
			else if (fx > 0)
				Q2 = 0.5*(Q1 + Q2);
			else
				return 0.5*(Q1 + Q2);
		}
		if (fx1 > 0 && fx2 < 0)
		{
			if (fx < 0)
				Q2 = 0.5*(Q1 + Q2);
			else if (fx > 0)
				Q1 = 0.5*(Q1 + Q2);
			else
				return 0.5*(Q1 + Q2);
		}
		if (fx1 > 0 && fx2 > 0)
			Q1 -= 0.01;
		if (fx1 == 0)
			return Q1;
		if (fx2 == 0)
			return Q2;
	}
	return Q1;
}

//计算fx的值
double Calculate_fx(const WP *well, const int outlet, const int arry_size, double Q1)
{
	double fx = 0,fx1=0,fx2=0,Qi=0;
	for (int i = 0; i < outlet; i++)
	{
		Qi = Calculate_Qi(well, i, Q1);
		fx1 += Qi * Qi*well[i].PipeLong;
	}
	for (int j = arry_size-1; j > outlet-1; j--)
	{
		Qi = Calculate_Qi(well, j, well[0].Flow - Q1, arry_size);
		fx2 += Qi * Qi*well[j].PipeLong;
	}
	fx = fx1 - fx2;
	return fx;
}

void Input_S_P_Flow(double Q1, WP *well, const int arry_size, const int outlet, const double pr, const double r, const double t, const double z, const double pmax, const double pmin)
{
	well[0].Pressure = pmax;
	well[outlet].Pressure = pmin;
	//计算各节点流量
	double D_first = 0; //计算管径的公式的分子
	for (int i = 0; i < arry_size; i++)
	{
		if (i <= outlet)
		{
			well[i].Pipe_flow = Calculate_Qi(well, i, Q1);
			cout<<"第" << i+1 << "个节点管段的流量为（m*m*m/s）：" << well[i].Pipe_flow << endl;
			D_first += well[i].Pipe_flow * well[i].Pipe_flow*well[i].PipeLong;

		}
		if (i > outlet)
		{
			well[i].Pipe_flow = Calculate_Qi(well, i, well[0].Flow - Q1, arry_size);
			cout << "第" << i+1 << "个节点管段的流量为（m*m*m/s）：" << well[i].Pipe_flow<< endl;

		}
	}
	//计算出气点的流量
	for (int i = 0; i < arry_size; i++)
		if(i!=outlet)
		well[outlet].Flow += well[i].Flow;
	cout << "出气点的流量为（m*m*m/s）：" << well[outlet].Flow<<endl;


	//计算管径
	double Bs = 0;
	Bs = z * pr*t / pow(Cs*A*Ψ*E, 2);
	double D = 0;//直径
	D = pow(D_first*Bs / (pmax*pmax - pmin * pmin), 1 / 5.2);
	cout << "管径为（m）：" << D << endl;

	//计算各节点压力
	for (int i = 1; i < arry_size-1; i++)
	{
		double first = well[i - 1].Pressure*well[i - 1].Pressure;
		double second = Bs * well[i - 1].Pipe_flow*well[i - 1].Pipe_flow*well[i - 1].PipeLong / pow(D, 5.2);
		well[i].Pressure = pow(first-second, 0.5);
		cout << "第" << i << "个节点的压力为（pa）：" << well[i].Pressure<<endl;
	}
}


