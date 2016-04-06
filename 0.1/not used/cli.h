
#pragma once

/****************************************************
command line handler

*****************************************************/
#include<iostream>
#include<map>
#include<string>
#include"Vec3.h"

class cli
{
public:
	cli();
	~cli();
	void run(int argc, char **argv);
	void init();

private:
	std::map<int, Vec3F> map;

	/*打印分隔线*/
	void printLine();

	/*选择向量列表中的num个元素*/
	void choose(int num, int * list);

	/*新建向量*/
	void newVec();

	/*检查状态，判断向量列表中是否存在 num 个向量
	* 如果数量不够，则新建 num - 当前数量 个向量*/
	void checkState(int num);

	/*打印提示信息*/
	void showList();

	/*打印当前向量列表中的所有向量*/
	void printMap();

	/*初始化*/


	/*读取一个命令*/
	void readCommand();

	/*解析一个命令*/
	void parseCommand(int argc, char **argv);

	/*程序结束的标志*/
	bool isFinished;

	/*当前命令*/
	int command;
};
