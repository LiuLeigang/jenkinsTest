// Windows_Demo4.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <windows.h>   
using namespace std;

 //定义一个临界区
CRITICAL_SECTION g_cs;
DWORD WINAPI Fun(LPVOID lpParamter)
{
	for (int i = 0; i < 10; i++)
	{
		// 小粒度 对资源变化的部分加锁，充分利用多线程
		//请求一个互斥量锁
		EnterCriticalSection(&g_cs);//进入临界区，如果有其他线程则等待
		cout << "Thread::" << i << endl;
		//释放互斥量锁
		LeaveCriticalSection(&g_cs);//退出临界区，其他线程可以进来了
	}
	return 0L;
}

int main()
{
	//初始化临界区
	InitializeCriticalSection(&g_cs);
	// 创建一个子线程
	HANDLE hThread = CreateThread(NULL, 0, Fun, NULL, 0, NULL);

	// 主线程的执行路径
	for (int i = 0; i < 10; i++)
	{
		//请求获得一个互斥量锁
		EnterCriticalSection(&g_cs);//进入临界区，如果有其他线程则等待
		cout << "Main Thread::" << i << endl;
		//释放互斥量锁
		//释放互斥量锁
		LeaveCriticalSection(&g_cs);//退出临界区，其他线程可以进来了
	}

	WaitForSingleObject(hThread, INFINITE);
	return 0;
}

