// Windows_Demo3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <iostream>
#include <windows.h>   
using namespace std;

HANDLE hMutex = NULL;//互斥量

DWORD WINAPI Fun(LPVOID lpParamter)
{
	for (int i = 0; i < 10; i++)
	{
		// 小粒度 对资源变化的部分加锁，充分利用多线程
		//请求一个互斥量锁
		WaitForSingleObject(hMutex, INFINITE);
		cout << "Thread::" << i << endl;
		//释放互斥量锁
		ReleaseMutex(hMutex);
	}
	return 0L;
}

int main()
{
	// 创建一个子线程
	HANDLE hThread = CreateThread(NULL, 0, Fun, NULL, 0, NULL);
	// 创建互斥量
	hMutex = CreateMutex(NULL, FALSE, NULL);

	// 主线程的执行路径
	for (int i = 0; i < 10; i++)
	{
		//请求获得一个互斥量锁
		WaitForSingleObject(hMutex, INFINITE);
		cout << "Main Thread::" << i << endl;
		//释放互斥量锁
		ReleaseMutex(hMutex);
	}

	WaitForSingleObject(hThread, INFINITE);
	return 0;
}

