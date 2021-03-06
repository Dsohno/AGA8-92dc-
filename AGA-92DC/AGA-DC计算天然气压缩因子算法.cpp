// BWRS计算压缩因子.cpp: 定义控制台应用程序的入口点。
//注意摩尔密度与密度的区别


#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cmath>
#include <conio.h>
#include"CalculationAll.h"

using namespace std;
#define Rm 8.31447


int main()
{
	//获取表中的内容
	ifstream list_10, list_11, list_12;
	double list1_10[58][11] = { 0 }, list1_11[21][21][4] = { 0 }, list1_12[21][8] = { 0 }, pm = 0;
	list_10.open("list1-10.txt");
	list_11.open("list1-11.txt");
	list_12.open("list1-12.txt");
	if (list_10.fail())
		cout << "表1-10打开失败" << endl;
	else
		cout << "表1-10打开成功" << endl;
	if (list_11.fail())
		cout << "表1-11打开失败" << endl;
	else
		cout << "表1-11打开成功" << endl;
	if (list_12.fail())
		cout << "表1-12打开失败" << endl;
	else
		cout << "表1-12打开成功" << endl;

	//获取表1-10，1-11，1-12中的信息
	Get_Input(list_10, list1_10, 0);
	Get_Input(list_11, list1_11, 0.1);
	Get_Input(list_12, list1_12, 'c');





	//获取混合气体的各组分含量并确定混合气体中有几种气体,获取基本参数P,T
	double x_i[21] = { 0 }, p = 0, t = 0;
	int n = 21;
	char a = 'y';
	cout << "是否启用测试用例（Y/N）";
	cin >> a;
	if (a == 'y' || a == 'Y')
	{
		//测试用例
		ifstream text;
		n = 21;
		text.open("text.txt");
		text >> p >> t;
		for (int i = 0; i < 21; i++)
			text >> x_i[i];
	}
	else
		Get_x_i(x_i, n, p, t);
	


	//迭代主体
	char y = 'y';
	while (y == 'Y' || y == 'y')
	{
		//获取混合气体的各组分含量并确定混合气体中有几种气体,获取基本参数P,T
		//Get_x_i(x_i,n,p,t);


		//获取pm2的值
		pm = Calculation_PM2(x_i, list1_12, t, p);

		//进行迭代并进行输出z和ρ的值
		Calculation_PM3(x_i, list1_10, list1_11, list1_12, t, p, pm, n);
		//Calculaton_BY_BOOK(x_i, list1_10, list1_11, list1_12, t, p, 0, pm2, n);
		cout << endl << "是否继续下一次计算（Y/N）";
		cin >> y;
	}
	_getch();
	return 0;
}
