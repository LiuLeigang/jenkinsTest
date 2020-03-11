// Windows_Demo5.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include<string>
#include<iostream>
#include<process.h>
#include<windows.h>
using namespace std;
//声明3个事件句柄
HANDLE  hev1, hev2, hev3;

//线程绑定的函数返回值和参数是确定的，而且一定要__stdcall
DWORD WINAPI threadFunA(LPVOID lpParamter)
{
	for (int i = 0; i < 10; i++) {
		WaitForSingleObject(hev1, INFINITE);//等待事件1
		cout << "A" << endl;
		SetEvent(hev2);//触发事件2
	}
	return 0L;
}

DWORD WINAPI threadFunB(LPVOID lpParamter)
{
	for (int i = 0; i < 10; i++) {
		WaitForSingleObject(hev2, INFINITE);//等待事件2
		cout << "B" << endl;
		SetEvent(hev3);//触发事件3
	}
	return 0L;
}

DWORD WINAPI threadFunC(LPVOID lpParamter)
{
	for (int i = 0; i < 10; i++) {
		WaitForSingleObject(hev3, INFINITE);//等待事件3
		cout << "C" << endl;
		SetEvent(hev1);//触发事件1
	}
	return 0L;
}


int main()
{
	hev1 = CreateEvent(NULL, FALSE, FALSE, NULL);
	hev2 = CreateEvent(NULL, FALSE, FALSE, NULL);
	hev3 = CreateEvent(NULL, FALSE, FALSE, NULL);
	SetEvent(hev1);//触发事件1，从A开始打印

	HANDLE hth1, hth2, hth3;
	//创建线程
	hth1 = CreateThread(NULL, 0, threadFunA, NULL, 0, NULL);
	hth2 = CreateThread(NULL, 0, threadFunB, NULL, 0, NULL);
	hth3 = CreateThread(NULL, 0, threadFunC, NULL, 0, NULL);

	//等待子线程结束
	WaitForSingleObject(hth1, INFINITE);
	WaitForSingleObject(hth2, INFINITE);
	WaitForSingleObject(hth3, INFINITE);

	//一定要记得关闭线程句柄
	CloseHandle(hth1);
	CloseHandle(hth2);
	CloseHandle(hth3);

	//删除事件
	CloseHandle(hev1);
	CloseHandle(hev2);
	CloseHandle(hev3);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
