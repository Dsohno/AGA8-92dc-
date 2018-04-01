//AGA8��92DC����ѹ������
//ͷ�ļ�CalculationAll.h
//���һ���޸�ʱ�䣺2018��3��22�գ�
//���ߣ�����
//��ϵ��ʽ��2321084428@qq.com


#include <iostream>
#include <cmath>
#include <fstream>
#include <stdio.h>
#include <iomanip>

using namespace std;
#define Rm 0.00831447


void Get_Input(ifstream& list, double(*list1_10)[11], int n);
//��ȡ��1-10�е�����
void Get_Input(ifstream& list, double(*list1_11)[21][4], int n);
//��ȡ��1-11�е�����
void Get_Input(ifstream& list, double(*list1_12)[8], char n);
//��ȡ��1-12�е�����

void Get_x_i(double *x_i, int& n, double& p, double& t);
//��ȡ�������ĸ���ֺ�����ȷ������������м�������,��ȡ��������P,T

double Calculation_K(const double x_i[], const double(*list1_11)[21][4], const double(*list1_12)[8], int n);
//����������������K������K������

double Sum_First_K(const double x_i[], const double(*list1_12)[8], int n);
//������ʽK�еĵ�һ��ĺ�

double Sum_Second_K(const double x_i[], const double(*list1_11)[21][4], const double(*list1_12)[8], int n);
//������ʽK�еĵڶ���ĺ�

double Calculation_B(const double x_i[], const double(*list1_10)[11], const double(*list1_11)[21][4], const double(*list1_12)[8], double t, int n);
//����ڶ�ά��ϵ��B������B

double Calculation_Bnij(const double(*list1_10)[11], const double(*list1_11)[21][4], const double(*list1_12)[8], int n, int i, int j);
//���㲢����Bnij

double Calculation_Eij(const double(*list1_11)[21][4], const double(*list1_12)[8], int i, int j);
//���㲢����Eij

double Calculation_Gij(const double(*list1_11)[21][4], const double(*list1_12)[8], int i, int j);
//���㲢����Gij

double Calculation_Sum_B_Two(const double x_i[], const double(*list1_10)[11], const double(*list1_11)[21][4], const double(*list1_12)[8], int n, int k);
//���㲢����B�ĵڶ������������

double Calculation_Sum_Cn(const double *x_i, const double(*list1_10)[11], const double(*list1_11)[121][4], const double(*list1_12)[8], double t, int n);
//���㲢����Cn�ĺ�(Z�ĵ�����ϵ��)

double Calculation_Sum_Cn_C(const double *x_i, const double(*list1_10)[11], const double(*list1_11)[21][4], const double(*list1_12)[8], double t, int s, int n);
//���㲢���ص���C��ֵ

double Calculation_Sum_Cn_C_U(const double *x_i, const double(*list1_10)[11], const double(*list1_11)[21][4], const double(*list1_12)[8], int n);
//���㲢����U

double Calculation_Sum_Cn_C_U_First(const double *x_i, const double(*list1_12)[8], int n);
//���㲢����U�ĵ�һ�������

double Calculation_Sum_Cn_C_U_Two(const double *x_i, const double(*list1_11)[21][4], const double(*list1_12)[8], int n);
//���㲢����U�ĵڶ��������


double Calculation_Sum_Cn_C_G(const double *x_i, const double(*list1_10)[11], const double(*list1_11)[21][4], const double(*list1_12)[8], int n);
//���㲢����G

double Calculation_Sum_Cn_C_G_First(const double *x_i, const double(*list1_12)[8], int n);
//���㲢����G��һ�������

double Calculation_Sum_Cn_C_G_Two(const double *x_i, const double(*list1_11)[21][4], const double(*list1_12)[8], int n);
//���㲢����G�ĵڶ��������


double Calculation_Sum_Cn_C_Q(const double *x_i, const double(*list1_12)[8], int n);
//���㲢����Q

double Calculation_Sum_Cn_C_F(const double *x_i, const double(*list1_12)[8], int n);
//���㲢����F


double Calculation_Sum_Cn4(const double *x_i, const double(*list1_10)[11], const double(*list1_11)[21][4], const double(*list1_12)[8], double t, double pm, int n);
//���㲢����cn��������Z�����һ�

double Calculation_Pr(double k, double pm);
//�����r������

double Calculation_Z(const double *x_i, const double(*list1_10)[11], const double(*list1_11)[21][4], const double(*list1_12)[8], double t, double pm, int n);
//���㲢����Z


double Calculation_PM2(double t, double p);
//���㲢����pm2

double Calculation_PM2_M(const double *x_i, const double(*list1_12)[8]);
//���㲢���ػ���������Է�������

double Calculation_P_BY_Z(const double *x_i, const double(*list1_10)[11], const double(*list1_11)[21][4], const double(*list1_12)[8], double t, double pm, int n);
//����Zֵ�ͦ�ֵ������Ӧ��ѹǿ

void Calculation_PM3(const double *x_i, const double(*list1_10)[11], const double(*list1_11)[21][4], const double(*list1_12)[8], double t, double p, double pm2, int n);
//��������ѵ�ֵ0

//void Calculaton_BY_BOOK(const double *x_i, const double(*list1_10)[11], const double(*list1_11)[19][4], const double(*list1_12)[8], double t, double p, double pm1, double pm2, int n);
//����ѣ�


//��ȡ��1-10�е�����
void Get_Input(ifstream& list, double(*list1_10)[11], int n)
{
	for (int i = 0; i < 58; i++)
		for (int j = 0; j < 11; j++)
			list >> list1_10[i][j];
}

//��ȡ��1-11�е�����
void Get_Input(ifstream& list, double(*list1_11)[21][4], int n)
{
	for (int i = 0; i <21; i++)
		for (int j = 0; j < 21; j++)
			for (int k = 0; k < 4; k++)
			{
				if (i < 8)
				{
					list >> list1_11[i][j][k];
				//	if (i > j)
				//		list1_11[i][j][k] = list1_11[j][i][k];
				}
				else
				{
					//if (i > j)
						//list1_11[i][j][k] = list1_11[j][i][k];
					//else
						list1_11[i][j][k] = 1;
				}

			}
}

//��ȡ��1-12�е�����
void Get_Input(ifstream& list, double(*list1_12)[8], char n)
{
	for (int i = 0; i < 21; i++)
		for (int j = 0; j < 8; j++)
			list >> list1_12[i][j];
}

//��ȡ�������ĸ���ֺ�����ȷ������������м�������,��ȡ��������P,T
void Get_x_i(double *x_i, int& n, double& p, double& t)
{
	cout << "����ѹ��P��MPa��:";
	cin >> p;
	cout << "�����¶�T��k��:";
	cin >> t;

	cout << "��û�и���֣������0" << endl
		<< "�������������X��CH4)         :";
	cin >> *(x_i);
	cout << "�������������X��N2��         :";
	cin >> *(x_i + 1);
	cout << "�������������X��CO2��        :";
	cin >> *(x_i + 2);
	cout << "�������������X��C2H6��       :";
	cin >> *(x_i + 3);
	cout << "�������������X��C3H8��       :";
	cin >> *(x_i + 4);
	cout << "�������������X��H2O��        :";
	cin >> *(x_i + 5);
	cout << "�������������X��H2S��        :";
	cin >> *(x_i + 6);
	cout << "�������������X��H2��         :";
	cin >> *(x_i + 7);
	cout << "�������������X��CO��         :";
	cin >> *(x_i + 8);
	cout << "�������������X��O2��         :";
	cin >> *(x_i + 9);
	cout << "�������������X��i-C4H10��    :";
	cin >> *(x_i + 10);
	cout << "�������������X��n-C4H10��    :";
	cin >> *(x_i + 11);
	cout << "�������������X��i-C5H12��    :";
	cin >> *(x_i + 12);
	cout << "�������������X��n-C5H12��    :";
	cin >> *(x_i + 13);
	cout << "�������������X��n-C6H14��    :";
	cin >> *(x_i + 14);
	cout << "�������������X��n-C7H16��    :";
	cin >> *(x_i + 15);
	cout << "�������������X��n-C8H18��    :";
	cin >> *(x_i + 16);
	cout << "�������������X��n-C9H20��    :";
	cin >> *(x_i + 17);
	cout << "�������������X��n-C10H22��   :";
	cin >> *(x_i + 18);
	cout << "�������������X��He��         :";
	cin >> *(x_i + 19);
	cout << "�������������X��Ar��         :";
	cin >> *(x_i + 20);
}

//����������������K������K������
double Calculation_K(const double x_i[], const double(*list1_11)[21][4], const double(*list1_12)[8], int n)
{
	double k_5=0,k_first = 0, k_second = 0;
	k_first = Sum_First_K(x_i, list1_12, n);
	k_second = Sum_Second_K(x_i, list1_11, list1_12, n);
	k_5 = k_first + k_second;
	return pow(k_5,0.6);
}

//������ʽK�еĵ�һ��ĺ�
double Sum_First_K(const double x_i[], const double(*list1_12)[8], int n)
{
	double k_one = 0;
	for (int i = 0; i < n; i++)
		k_one = k_one + x_i[i] * pow(list1_12[i][2], 2.5);
	return pow(k_one, 2);
}

//������ʽK�еĵڶ���ĺ�
double Sum_Second_K(const double x_i[], const double(*list1_11)[21][4], const double(*list1_12)[8], int n)
{
	double k_two = 0,k_two_p=0;
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
		{
			k_two_p = x_i[i] * x_i[j] * (pow(list1_11[i][j][2], 5) - 1)*pow(list1_12[i][2] * list1_12[j][2], 2.5);
			k_two = k_two + k_two_p;
		}
	return k_two * 2;
}

//����ڶ�ά��ϵ��B������B
double Calculation_B(const double x_i[], const double(*list1_10)[11], const double(*list1_11)[21][4], const double(*list1_12)[8], double t, int n)
{
	double an = 0,b=0,tp=0;
	for (int k = 0; k < 18; k++)
	{
		b = Calculation_Sum_B_Two(x_i, list1_10, list1_11, list1_12, n, k);
		tp = pow(t, -list1_10[k][5]);
		an = an + list1_10[k][1] * b *tp;
	} 
	return an;
}

//���㲢����Bnij
double Calculation_Bnij(const double(*list1_10)[11], const double(*list1_11)[21][4], const double(*list1_12)[8], int n, int i, int j)
{
	double  g = 0, b_first = 0, b_second = 0, b_third = 0, b_fourth = 0, b_five = 0,bnij=0;
	g = Calculation_Gij(list1_11, list1_12, i, j);
	b_first = pow((g + 1 - list1_10[n][6]), list1_10[n][6]);
	b_second = pow((list1_12[i][4] * list1_12[j][4] + 1 - list1_10[n][7]), list1_10[n][7]);
	b_third = pow((pow(list1_12[i][5], 0.5)*pow(list1_12[j][5], 0.5) + 1 - list1_10[n][8]), list1_10[n][8]);
	b_fourth = pow((list1_12[i][6] * list1_12[j][6] + 1 - list1_10[n][9]), list1_10[n][9]);
	b_five=pow((list1_12[i][7] * list1_12[j][7] + 1 - list1_10[n][10]), list1_10[n][10]);
	bnij = b_first * b_second * b_third * b_fourth * b_five;
	return bnij;
		
}

//���㲢����Eij
double Calculation_Eij(const double(*list1_11)[21][4], const double(*list1_12)[8], int i, int j)
{
	return list1_11[i][j][0] * pow(list1_12[i][1]*list1_12[j][1], 0.5);
}

//���㲢����Gij
double Calculation_Gij(const double(*list1_11)[21][4], const double(*list1_12)[8], int i, int j)
{
	return 0.5*list1_11[i][j][3] * (list1_12[i][3] + list1_12[j][3]);
}

//���㲢����B�ĵڶ������������
double Calculation_Sum_B_Two(const double x_i[], const double(*list1_10)[11], const double(*list1_11)[21][4], const double(*list1_12)[8], int n, int k)
{
	double b = 0, b_two_e = 0, e=0;
	double b_two1 = 0, bx1 = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			b = Calculation_Bnij(list1_10, list1_11, list1_12, k, i, j);
			e = Calculation_Eij(list1_11, list1_12, i, j);
			b_two_e =pow(e,list1_10[k][5]);
			bx1 = x_i[i] * x_i[j] * pow(list1_12[i][2] * list1_12[j][2], 1.5)*b_two_e;
			b_two1 = b_two1 + b * bx1;
		}
	return b_two1;
}

//���㲢����Cn�ĺ�(Z�ĵ�����ϵ��)
double Calculation_Sum_Cn(const double *x_i, const double(*list1_10)[11], const double(*list1_11)[21][4], const double(*list1_12)[8], double t, int n)
{
	double cn = 0;
	for (int i = 12; i < 18; i++)
		cn = cn + Calculation_Sum_Cn_C(x_i, list1_10, list1_11, list1_12, t, i, n);
	return cn;
}

//���㲢���ص���C��ֵ
double Calculation_Sum_Cn_C(const double *x_i, const double(*list1_10)[11], const double(*list1_11)[21][4], const double(*list1_12)[8], double t, int s, int n)
{
	double c= 0,c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0;
	double g = 0, q = 0, f = 0, u = 0;
	g = Calculation_Sum_Cn_C_G(x_i, list1_10, list1_11, list1_12, n);
	q = Calculation_Sum_Cn_C_Q(x_i, list1_12, n);
	f = Calculation_Sum_Cn_C_F(x_i, list1_12, n);
	u = Calculation_Sum_Cn_C_U(x_i, list1_10, list1_11, list1_12, n);
	c1 = pow((g +1- list1_10[s][6]), list1_10[s][6]);
	c2 = pow((pow(q, 2) + 1 - list1_10[s][7]), list1_10[s][7]);
	c3 = pow((f + 1 - list1_10[s][8]), list1_10[s][8]);
	c4 = pow(u, list1_10[s][5]);
	c5 = pow(t, -list1_10[s][5]);
 	c=list1_10[s][1] * c1 * c2 * c3 * c4 * c5;
	return c;
}

//���㲢����U
double Calculation_Sum_Cn_C_U(const double *x_i, const double(*list1_10)[11], const double(*list1_11)[21][4], const double(*list1_12)[8], int n)
{
	double u_one = 0, u_two = 0,u=0;
	u_one = Calculation_Sum_Cn_C_U_First(x_i, list1_12, n);
	u_two = Calculation_Sum_Cn_C_U_Two(x_i, list1_11, list1_12, n);
	u = u_one + u_two;
	return pow(u,0.2);
}

//���㲢����U�ĵ�һ�������
double Calculation_Sum_Cn_C_U_First(const double *x_i, const double(*list1_12)[8], int n)
{
	double U_first = 0;
	for (int i = 0; i < n; i++)
		U_first = U_first + x_i[i] * pow(list1_12[i][1], 2.5);
	return pow(U_first, 2);
}

//���㲢����U�ĵڶ��������
double Calculation_Sum_Cn_C_U_Two(const double *x_i, const double(*list1_11)[21][4], const double(*list1_12)[8], int n)
{
	double u_two = 0;
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			u_two = u_two + x_i[i] * x_i[j]*(pow(list1_11[i][j][1], 5) - 1)*pow(list1_12[i][1] * list1_12[j][1], 2.5);
	return u_two * 2;
}

//���㲢����G
double Calculation_Sum_Cn_C_G(const double *x_i, const double(*list1_10)[11], const double(*list1_11)[21][4], const double(*list1_12)[8], int n)
{
	return Calculation_Sum_Cn_C_G_First(x_i, list1_12, n) + Calculation_Sum_Cn_C_G_Two(x_i, list1_11, list1_12, n);
}

//���㲢����G��һ�������
double Calculation_Sum_Cn_C_G_First(const double *x_i, const double(*list1_12)[8], int n)
{
	double g_first = 0;
	for (int i = 0; i < n; i++)
		g_first = g_first + x_i[i] * list1_12[i][3];
	return g_first;
}

//���㲢����G�ĵڶ��������
double Calculation_Sum_Cn_C_G_Two(const double *x_i, const double(*list1_11)[21][4], const double(*list1_12)[8], int n)
{
	double g_two = 0;
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			g_two = g_two + x_i[i] * x_i[j] * (list1_11[i][j][3] - 1)*(list1_12[i][3] + list1_12[j][3]);
	return g_two * 2;
}

//���㲢����Q
double Calculation_Sum_Cn_C_Q(const double *x_i, const double(*list1_12)[8], int n)
{
	double q = 0;
	for (int i = 0; i < n; i++)
		q = q + x_i[i] * list1_12[i][4];
	return q;
}

//���㲢����F
double Calculation_Sum_Cn_C_F(const double *x_i, const double(*list1_12)[8], int n)
{
	double f = 0;
	for (int i = 0; i < n; i++)
		f = f + pow(x_i[i], 2)*list1_12[i][5];
	return f;
}

//�����r������
double Calculation_Pr(double k, double pm)
{
	return k * pm;
}

//���㲢����cn��������Z�����һ�
double Calculation_Sum_Cn4(const double *x_i, const double(*list1_10)[11], const double(*list1_11)[21][4], const double(*list1_12)[8], double t, double pr, int n)
{
	double cn = 0, cn4 = 0,cn4_1=0,cn4_2=0,cn4_3=0;
	for (int i = 12; i < 58; i++)
	{
		cn = Calculation_Sum_Cn_C(x_i, list1_10, list1_11, list1_12, t, i, n);
		cn4_1 = list1_10[i][2] - list1_10[i][3] * list1_10[i][4] * pow(pr, list1_10[i][4]);
		cn4_2 = pow(pr, list1_10[i][2]);
		cn4_3 = exp(-list1_10[i][3] * pow(pr, list1_10[i][4]));
		cn4 = cn4 + cn * cn4_1*cn4_2*cn4_3;
		//cout <<endl<< i << "    Cn4:" << cn4;
	}  
	return cn4;
}

//���㲢����Z
double Calculation_Z(const double *x_i, const double(*list1_10)[11], const double(*list1_11)[21][4], const double(*list1_12)[8], double t, double pm, int n)
{
	double z = 0, z1 = 0, z2 = 0, z3 = 0;
	double k = 0, cn = 0, pr = 0;
	z1 = Calculation_B(x_i, list1_10, list1_11, list1_12, t, n)*pm;
	k = Calculation_K(x_i, list1_11, list1_12, n);
	cn = Calculation_Sum_Cn(x_i, list1_10, list1_11, list1_12, t, n);
	pr = Calculation_Pr(k, pm);
	z2 = pr * cn;
	z3=Calculation_Sum_Cn4(x_i, list1_10, list1_11, list1_12, t, pr, n);
	//cout <<endl<< "z1: " << z1 << "    z2: " << z2 << "    z3: " << z3;
	z = 1 + z1 - z2 + z3;
	return z;
}

//���㲢���ػ���������Է�������
double Calculation_PM2_M(const double *x_i, const double(*list1_12)[8])
{
	double m = 0;
	for (int i = 0; i < 21; i++)
		m = m + x_i[i] * list1_12[i][0];
	return m;
}

//���㲢����pm2
double Calculation_PM2(const double *x_i, const double (*list1_12)[8], double t, double p)
{
	return p / (t*Rm);
}

//����Zֵ�ͦ�ֵ������Ӧ��ѹǿ
double Calculation_P_BY_Z(const double *x_i, const double(*list1_10)[11], const double(*list1_11)[21][4], const double(*list1_12)[8], double t, double pm, int n)
{
	double z = 0;
	z = Calculation_Z(x_i, list1_10, list1_11, list1_12, t, pm, n);
	cout<<"           ѹ������Z�� "<<setw(20)<<  z;
	return z * Rm*pm*t;
}

//��������ѵ�ֵ0
void Calculation_PM3(const double *x_i, const double(*list1_10)[11], const double(*list1_11)[21][4], const double(*list1_12)[8], double t, double p, double pm2, int n)
{
	//���ݦѼ���P��ֵ
	cout.setf(std::ios::left);
	double p1=0, z = 0, m=0,pm1=40,p2=0,d=0,pd=0;
	pm2 = 0;
	m = Calculation_PM2_M(x_i, list1_12);
		p1 = Calculation_P_BY_Z(x_i, list1_10, list1_11, list1_12, t, pm1, n)-p;
		p2= Calculation_P_BY_Z(x_i, list1_10, list1_11, list1_12, t, pm2, n) - p;
	while (p1-p2>0.0000001||p2-p1>0.0000001)
	{
		if (p1*p2 > 0)
			pm2 -= 0.5;
		if (p1*p2 < 0)
		{
			d = 0.5*(pm1 + pm2);
			pd = Calculation_P_BY_Z(x_i, list1_10, list1_11, list1_12, t, d, n) - p;
			if (pd > 0)
			{
				pm1 = d;
				p1 = pd;
			}
			if (pd < 0)
			{
				pm2 = d;
				p2 = pd;
			}
			if (pd == 0)
			{
				z = Calculation_Z(x_i, list1_10, list1_11, list1_12, t, pm1, n);
				cout <<endl<< "���������ܶ�Ϊ��" << pm1 * m << endl << "ѹ������Ϊ��" << z;
			}
		} 
		cout << endl << "P1: "<<setw(15) << p1 << " p2: " <<setw(18)<< p2 << "pm1: " << setw(10) << pm1<<"  pm2: "<<pm2;
	}
	z = Calculation_Z(x_i, list1_10, list1_11, list1_12, t, pm1, n);
	cout <<endl<< "���������ܶ�Ϊ��" << pm1*m << endl << "ѹ������Ϊ��" << z;
}


/*void Calculaton_BY_BOOK(const double *x_i, const double(*list1_10)[11], const double(*list1_11)[21][4], const double(*list1_12)[8], double t, double p, double pm1, double pm2, int n)
{
	double cp = 0,p2=0,p1=0,pm3=0;
	cp = Calculation_P_BY_Z(x_i, list1_10, list1_11, list1_12, t, pm2, n);
	p1 = p2;
	p2 = cp;
	while ( p-cp < 0.0000001 || cp - p < 0.0000001)
	{
		pm3 = pm2 - p2 * (pm2 - pm1) / (p2 - p1);
		p1 = p2;
		
		cp= Calculation_P_BY_Z(x_i, list1_10, list1_11, list1_12, t, pm3, n);
		p2 = cp;
	}
}
*/