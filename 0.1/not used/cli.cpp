#include "cli.h"
#include"display.h"

cli::cli()
{
}

void cli::init() {
	command = 0;
	isFinished = false;
}

void cli::run(int argc, char **argv) {
	while (!isFinished) {
		showList();
		readCommand();
		parseCommand(argc,argv);
		printLine();
	}
}

void cli::printLine() {
	for (int i = 0; i < 20; i++) printf("-");
	printf("\n\n");
}
void cli::readCommand() {
	std::cin >> command;
}
void cli::showList() {
	std::cout <<
		"选择要测试的功能：\n" <<
		"1.新建向量\n" <<
		"2.向量加法\n" <<
		"3.向量减法\n" <<
		"4.向量数乘\n" <<
		"5.向量点积\n" <<
		"6.向量叉积\n" <<
		"7.向量求模\n" <<
		"8.向量投影\n" <<
		"0.退出\n\n";
}

void cli::newVec() {
	std::cout << "输入向量的坐标，以空格分隔\n例:x 1 2.4 5\n";
	Vec3F a;
	std::cin >> a;
	map[map.size()] = a;

	std::cout << "向量" << a << "已加入列表\n";
}
void cli::checkState(int num) {
	int curNum = map.size();
	if (curNum < num) {
		std::cout << "向量列表中的个数不足" << num << "个，请新建向量\n";
		for (int i = 0; i < num - curNum; i++)
		newVec();
	}
	printMap();
}
void cli::printMap() {
	std::map<int, Vec3F>::iterator it;
	for (it = map.begin();it != map.end();++it)
		std::cout << "编号: " << it->first << " 值: " << it->second << std::endl;
}

void cli::choose(int num, int *list) {
	std::cout << "请从列表中选择" << num <<"个向量进行运算: " << std::endl;
	int index[3];
	bool hasKey = true;
	do {
		hasKey = true;
		for (int i = 0; i < num; i++) {
			std::cin >> index[i];
		}
		for (int i = 0; i < num; i++) {
			if (map.find(index[i]) == map.end()) hasKey = false;
			else list[i] = index[i];
		}
		if (hasKey == false) {
			std::cout << "输入了不存在的向量编号,请重新输入\n";
		}
	} while (hasKey == false);
	 
}
void cli::parseCommand(int argc, char **argv) {
	double point[100];
	int i;
	Vec3F a;
	switch (command)
	{

	case 1:
	{
		newVec();
	}
	break;
	case 2:
	{
		std::cout << "2.向量加法" << std::endl;
		checkState(2);
		int list[2];
		choose(2, list);
		std::cout << "结果:" << map[list[0]] + map[list[1]] << std::endl;
		memset(point,0,sizeof(point));
		a=map[list[0]] + map[list[1]];
		point[0]=map[list[0]].getX();
		point[1]=map[list[0]].getY();
		point[2]=map[list[0]].getZ();
		point[3]=map[list[1]].getX();
		point[4]=map[list[1]].getY();
		point[5]=map[list[1]].getZ();
		point[6]=a.getX();
		point[7]=a.getY();
		point[8]=a.getZ();
		displaymain(argc,argv,3,point);
	}
	break;
	case 3:
	{
		std::cout << "3.向量减法" << std::endl;
		checkState(2);
		int list[2];
		choose(2, list);
		std::cout << "结果:" << map[list[0]] - map[list[1]] << std::endl;
		memset(point,0,sizeof(point));
		a=map[list[0]] - map[list[1]];
		point[0]=map[list[0]].getX();
		point[1]=map[list[0]].getY();
		point[2]=map[list[0]].getZ();
		point[3]=map[list[1]].getX();
		point[4]=map[list[1]].getY();
		point[5]=map[list[1]].getZ();
		point[6]=a.getX();
		point[7]=a.getY();
		point[8]=a.getZ();
		displaymain(argc,argv,3,point);
	}
	break;
	case 4:
	{
		std::cout << "4.向量数乘" << std::endl;
		checkState(1);
		int list[1];
		choose(1, list);
		std::cout << "输入数字" << std::endl;
		double d;
		std::cin >> d;
		std::cout << "结果:" << map[list[0]] * d << std::endl;
		memset(point,0,sizeof(point));
		a=map[list[0]] * d;
		point[0]=map[list[0]].getX();
		point[1]=map[list[0]].getY();
		point[2]=map[list[0]].getZ();
		point[3]=a.getX();
		point[4]=a.getY();
		point[5]=a.getZ();
		displaymain(argc,argv,2,point);
	}
	break;
	case 5:
	{
		std::cout << "5.向量点积" << std::endl;
		checkState(2);
		int list[2];
		choose(2, list);
		std::cout << "结果:" << innerProduct(map[list[0]],map[list[1]]) << std::endl;
	}
	break;
	case 6:
	{
		std::cout << "6.向量叉积" << std::endl;
		checkState(2);
		int list[2];
		choose(2, list);
		std::cout << "结果:" << crossProduct(map[list[0]], map[list[1]]) << std::endl;
	}
	break;
	case 7:
	{
		std::cout << "7.向量求模" << std::endl;
		checkState(1);
		int list[1];
		choose(1, list);
		std::cout << "结果:" << map[list[0]].length()<< std::endl;
	}
	break;
	case 8:
	{
		std::cout << "8.向量投影" << std::endl;
		checkState(2);
		int list[2];
		choose(2, list);
		std::cout << "结果:" << project(map[list[0]], map[list[1]]) << std::endl;
		a=project(map[list[0]], map[list[1]]);
		point[0]=map[list[0]].getX();
		point[1]=map[list[0]].getY();
		point[2]=map[list[0]].getZ();
		point[3]=map[list[1]].getX();
		point[4]=map[list[1]].getY();
		point[5]=map[list[1]].getZ();
		point[6]=a.getX();
		point[7]=a.getY();
		point[8]=a.getZ();
		displaymain(argc,argv,3,point);
	}
	break;
	case 0:
	{
		isFinished = true;
	}
	break;

	default:
		break;
	}

	if (!isFinished) {
		printf("\n输入回车键以继续...\n");
		getchar();
		getchar();
	}
	
}

cli::~cli()
{
}
