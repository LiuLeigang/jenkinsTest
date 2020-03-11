// Windows_Demo2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <windows.h>   
using namespace std;

HANDLE hMutex = NULL;//互斥量

DWORD WINAPI Fun(LPVOID lpParamter)
{
	// 大粒度 失去了多线程的意义
	//请求一个互斥量锁
	WaitForSingleObject(hMutex, INFINITE);
	for (int i = 0; i < 10; i++)
		cout << "Thread::" << i << endl;
	//释放互斥量锁
	ReleaseMutex(hMutex);
	return 0L;
}

int main()
{
	// 创建一个子线程
	HANDLE hThread = CreateThread(NULL, 0, Fun, NULL, 0, NULL);
	// 创建互斥量
	hMutex = CreateMutex(NULL, FALSE, NULL);

	// CloseHandle(hThread);
	// 线程的执行路径
	 //请求获得一个互斥量锁
	WaitForSingleObject(hMutex, INFINITE);
	for (int i = 0; i < 10; i++)
		cout << "Main Thread::" << i << endl;
	//释放互斥量锁
	ReleaseMutex(hMutex);

	WaitForSingleObject(hThread, INFINITE);
	return 0;
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
