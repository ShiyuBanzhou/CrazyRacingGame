//ͷ�ļ�
#pragma comment(lib,"Winmm.lib")
#include <graphics.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

//�궨��
#define LENGTH 2					//��ͼƬ���鳤��
#define WIDTH 1280					//��Ϸ���ڿ��(x)
#define HEIGHT 960					//��Ϸ���ڸ߶�(y)
#define SIZE 200					//���ĳߴ�
#define SIZE_OBSTACLE 128			//�ϰ���ĳߴ�
#define SIZE_NUM 20					//���ֵĳߴ�
#define SIZE_ROCKET 100				//����ĳߴ�
#define PI 3.14159265359			//��

//״̬ȫ�ֱ���					
bool isMenu = false;				//�Ƿ�㿪���˵�
bool onFire = false;				//�Ƿ�������
bool isUp = false;					//�Ƿ��Ѱ��¹����ϵİ���
bool isDown = false;				//�Ƿ��Ѱ��¹����µİ���
bool isHit = false;					//�Ƿ��ѷ�����ײ
bool first_play;					//�Ƿ��һ������

//ͼƬȫ�ֱ���
IMAGE frontCover;					//��Ϸ����ͼƬ
IMAGE grass;						//�ݵ�ͼƬ
IMAGE car_Audi[LENGTH];				//�µϳ�ͼƬ
IMAGE car_Bmw[LENGTH];				//����ͼƬ
IMAGE car_Mercedes[LENGTH];			//���۳�ͼƬ
IMAGE car_black[LENGTH];			//�ڳ�ͼƬ
IMAGE garage;						//����ͼƬ
IMAGE map_1;						//��ͼͼƬ
IMAGE map_2;
IMAGE car_circle[LENGTH];			//��ת������ͼƬ
IMAGE rock[LENGTH];					//�ϰ���ʯͷͼƬ
IMAGE rocket_img[LENGTH];			//���ͼƬ
IMAGE number[10];					//����ʱ���������ͼƬ
IMAGE show;							//��Ϣ��
IMAGE bomb[LENGTH];					//��ըͼƬ
IMAGE life;							//����ֵͼƬ
IMAGE success;						//�ɹ�ͼƬ
IMAGE black;						//��ɫ����ͼ
IMAGE star_black;					//����
IMAGE star_yellow;					//����
IMAGE terminalPoint;				//�յ�ͼƬ
IMAGE gameOver;						//gameoverͼƬ
IMAGE gameWin;						//gamewinͼƬ
IMAGE bomb_car[LENGTH];				//������ըͼƬ
IMAGE site;							//����ͼƬ
IMAGE temp;							//��ʱ�洢��Ϸ��Ϣ
IMAGE add_life;						//��������ֵͼƬ
IMAGE add_rocket;					//���ӵ�ҩͼƬ

//��Ϣȫ�ֱ���
ExMessage m;						//������Ϣ��������꣩

//����ȫ�ֱ���
double Forward = 0;					//��������
double Rota = 360;					//���ٶ�(ת���ٶ�)

//�û���Ϣ
char* name;							//�û�����
char* password;						//�û�����

//��ͼ���ص���Ϣ����
int map_information[WIDTH][HEIGHT];

//�յ��ʼy����
int end_y = -100;

//��һ�÷���ȫ�ֱ���
long score = 0;

//�����ٶ�ȫ�ֱ���
int speed_show = 30;
const int speed_min = 20;			//�ٶ���Сֵ
const int speed_max = 98;			//�ٶ����ֵ
long distance = 0;					//·��

//������ǵ�����
const int first_star = 500;			//һ�Ƿ�������
const int second_star = 2000;		//���Ƿ�������
const int third_star = 5000;		//���Ƿ�������

//ʱ��ȫ�ֱ���
time_t game_sum = 0;				//��Ϸ��ʱ��
time_t game_begin = 0;				//��Ϸ��ʼʱ��
time_t game_progress = 0;			//��Ϸ����ʱ��
time_t menu_begin = 0;				//��ʼ����˵���ʱ��
time_t menu_progress = 0;			//�˵�����ʱ��
time_t menu_sum = 0;				//�˵���ʱ��
time_t fire_last = 0;				//����ϴη���ʱ��
time_t fire_now = 0;				//������ڷ���ʱ��
time_t control_up_last = 0;			//�ϴ����Ͽ���ʱ��
time_t control_down_last = 0;		//�ϴ����¿���ʱ��	

//ģʽһ��ͼ�ɹ������ϰ���ĺ�����
int map_obstacle[3] = {
	//һ��
	230,
	//����
	530,
	//����
	900,
};

//�ṹ��
//������ť�Ľṹ��
typedef struct button
{
	int x;
	int y;
	int width;
	int height;
	COLORREF color;
	const char* buttonText;
}Button;

//�������Ľṹ��
typedef struct car
{
	int x;							//����(x, y)���꣬�Լ��ٶ�
	int y;
	int speed;
	time_t last;					//�ϴ���ײ��ʱ��
	bool life;						//�Ƿ���
}Car;

//�����ϰ���Ľṹ��
typedef struct obstacle {
	int x;
	int y;
	int speed;
	time_t last;					//�ϴ�ʱ��
	bool status;
}Obstacle;

//������ͼ�Ľṹ��
typedef struct map {
	int x;
	int y;
	int speed;
}Map;

//��������Ľṹ��
typedef struct rocket {
	int x;
	int y;
	int speed;
	bool status;					//�����״̬��trueΪ���ã�falseΪ������
}Rocket;

//�������а�����
typedef struct node {
	int no;
	char name[50];
	int score;
	struct node* next;
}TOPNODE;

//��������
int main(void);																//������
Button* createButton(int x, int y, int width, int height, COLORREF color,
	const char* buttonText);												//��ť����Ĵ���
void drawButton(Button* button, bool title);								//���ư�ť( title ���ڵ�������)
Car* createCar(int x, int y, int speed, bool life, time_t last);			//������Ĵ���
void loadImage();															//����ͼƬ
bool mouseDetect(Button* button, ExMessage m);								//�ж�������¼��Ƿ����ڰ�ť�߿�Χ��
void drawFrontCover();														//������Ϸ�����Լ����������水ť����¼�
int drawCarSelection();														//����ѡ������
void controlCar();															//��������
int pointTsm(int x, int y, int wide, int high);								//Խ����
void edgeDetection(Car* car);												//��Ե���
bool canCircle(Car* car);													//�ж��Ƿ������ת
void onUp(Car* car);
void onDown(Car* car);
void onLeft(Car* car);
void onRight(Car* car);
void mode_1();																//ģʽһ
Obstacle* createObstacle(int x, int y, int speed, bool status,
	time_t last);															//�ϰ�����Ĵ���
Map* createMap(int x, int y, int speed);									//��ͼ����Ĵ���
Rocket* createRocket(int x, int y, int speed, bool status);					//�������Ĵ���
void pauseInterface();														//��ͣ����
char* login_name();															//�����û�����
bool haveSpace(char* input);												//����û������Ƿ��пո�
char* login_password();														//�����û�����
void checkUsers(char* name);												//����û��Ƿ����
void PutNumber(long x, long y, long number, int TextSize = 10,
	int TextProportion = 2, int TextInterval = 0,
	COLORREF tc = 0x000000, LPCTSTR font = "����");							//��long�������ֳ����ڻ�����
void winInterface();														//��ʤ����
void loseInterface();														//ʧ�ܽ���
TOPNODE* loadNode();														//��ȡ���а�
void showNode();															//չʾ���а�
void changeNode(TOPNODE* h);												//�ı����а�����
TOPNODE* reNode(TOPNODE* h);												//�ع����а�˳��
void rewriteNode(TOPNODE* h);												//��д���а�
void node_main();															//���а�����������

int main(void)
{
	loadImage();										//����ͼƬ
	initgraph(WIDTH, HEIGHT);							//��ʼ����Ϸ����(1280 * 960)
	drawFrontCover();
	system("pause");
	closegraph();
}

//��ť����Ĵ���
Button* createButton(int x, int y, int width, int height, COLORREF color, const char* buttonText) {
	Button* button = (Button*)malloc(sizeof(Button) * 1);

	button->x = x;
	button->y = y;
	button->width = width;
	button->height = height;
	button->color = color;
	button->buttonText = buttonText;

	return button;
}

//���ư�ť( title ���ڵ�������)
void drawButton(Button* button, bool title) {
	int width, height;									//���ڼ������־�����ʾ�������߿�Ŀ���ߵı���
	setlinecolor(WHITE);								//���ð�ť�߿�������ɫ
	setbkmode(TRANSPARENT);								//�������ֱ���͸��
	settextcolor(button->color);						//����������ɫ

	//�ַ��������Ƿ����ڱ��⣬��ѡ��ͬ����������
	if (title == true) {
		settextstyle(120, 0, "����", 5, 0, 10, true, true, false);
		setlinestyle(PS_DASHDOT, 10);
	}
	else {
		settextstyle(50, 0, "����");
		setlinestyle(PS_SOLID, 10);
	}

	//���ư�ť
	roundrect(button->x, button->y,
		button->x + button->width, button->y + button->height, 30, 30);		//����Բ�Ǿ��α߿�
	width = button->width / 2 - textwidth(button->buttonText) / 2;			//���־���߿�ľ���
	height = button->height / 2 - textheight(button->buttonText) / 2;		//���־��ϱ߿�ĸ߶�
	outtextxy(button->x + width, button->y + height, button->buttonText);	//�����������

	return;
}

//�ж�������¼��Ƿ����ڰ�ť�߿�Χ��
bool mouseDetect(Button* button, ExMessage m) {
	if (m.x >= button->x
		&& m.x <= (button->x + button->width)
		&& m.y >= button->y
		&& m.y <= (button->y + button->height))
		return true;
	else
		return false;
}

//������Ϸ�����Լ����������水ť����¼�
void drawFrontCover() {
	Button* title, * start, * instruction, * quit;									//���尴ť�ṹ��ָ��
	//loadimage(&frontCover, (".\\image\\����.jpg"), NULL);
	putimage(0, 0, &frontCover);													//���ַ��汳��ͼ
	score = 0;
	//������ť����
	title = createButton(350, 50, 580, 150, RGB(237, 255, 83), "������Ϸ");			//�������
	start = createButton(500, 300, 280, 80, BLACK, "��ʼ��Ϸ");						//��ʼ����
	instruction = createButton(500, 430, 280, 80, RGB(51, 235, 149), "�淨����");	//���ܶ���
	quit = createButton(500, 560, 280, 80, RGB(3, 0, 255), "�˳���Ϸ");				//�˳�����

	//���ư�ť
	drawButton(title, true);			//�������ⰴť	
	drawButton(start, false);			//��������ʼ��Ϸ����ť
	drawButton(instruction, false);		//�������淨���ܡ���ť
	drawButton(quit, false);			//�������˳���Ϸ"��ť

	//�û���Ϣ����
	name = login_name();
	checkUsers(name);

	//��������
	//ѭ������
	//PlaySound(".\\sound\\bk.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	mciSendString("open .\\sound\\bk.mp3 alias bkmusic", NULL, 0, NULL);
	mciSendString("play bkmusic repeat from 0", NULL, 0, NULL);
	//��������ڷ��水ť�ĵ���¼�
	while (true) {
		m = getmessage(EX_MOUSE);		//��ȡ�����Ϣ
		switch (m.message) {
		case WM_LBUTTONDOWN:
			//����Ƿ��¡���ʼ��Ϸ����ť
			if (mouseDetect(start, m)) {
				printf("��ʼ��Ϸ");
				cleardevice();
				//controlCar();
				mode_1();
			}
			//����Ƿ��¡��淨���ܡ���ť
			if (mouseDetect(instruction, m)) {
				MessageBox(NULL,
					"�û�����ͨ��'W','S','A','D' �� �� �� �� �� �����ֱ����������ǰ������\n���ո�����䵼�����Ӵ�ʯͷ��ɴ���ʯͷ������100��\nȥ��ս���߷ְɣ���ʿ��",
					"�淨����", MB_ICONEXCLAMATION | MB_SETFOREGROUND);
			}
			//����Ƿ��¡��˳���Ϸ����ť
			if (mouseDetect(quit, m)) {
				exit(-1);
			}
		}
	}
}

//����ͼƬ
void loadImage() {
	//����ͼƬ
	loadimage(&frontCover, (".\\image\\����.jpg"), NULL);

	//����ͼƬ
	loadimage(&garage, ".\\image\\����.jpg", WIDTH, HEIGHT);

	//�µϳ�ͼƬ
	loadimage(&car_Audi[0], ".\\image\\�µ�A4L1.png", SIZE, SIZE);
	loadimage(&car_Audi[1], ".\\image\\�µ�A4L2.png", SIZE, SIZE);

	//����ͼƬ
	loadimage(&car_Bmw[0], ".\\image\\����X31.png", SIZE, SIZE);
	loadimage(&car_Bmw[1], ".\\image\\����X32.png", SIZE, SIZE);

	//���۳�ͼƬ
	loadimage(&car_Mercedes[0], ".\\image\\����E��1.png", SIZE, SIZE);
	loadimage(&car_Mercedes[1], ".\\image\\����E��2.png", SIZE, SIZE);

	//�ڳ�ͼƬ
	loadimage(&car_black[0], ".\\image\\car_black1.png", NULL);
	loadimage(&car_black[1], ".\\image\\car_black2.png", NULL);

	//��ͼͼƬ
	loadimage(&map_1, ".\\image\\map1.png", NULL);
	loadimage(&map_2, ".\\image\\��ͼ1.png", NULL);

	//�ϰ���ʯͷͼƬ
	loadimage(&rock[0], ".\\image\\ʯͷ1.png", SIZE_OBSTACLE, SIZE_OBSTACLE);
	loadimage(&rock[1], ".\\image\\ʯͷ2.png", SIZE_OBSTACLE, SIZE_OBSTACLE);

	//���ͼƬ
	loadimage(&rocket_img[0], ".\\image\\���1.png", SIZE_ROCKET, SIZE_ROCKET);
	loadimage(&rocket_img[1], ".\\image\\���2.png", SIZE_ROCKET, SIZE_ROCKET);

	//����ͼƬ0~9
	loadimage(&number[0], ".\\image\\0.jpg", SIZE_NUM, SIZE_NUM);
	loadimage(&number[1], ".\\image\\1.jpg", SIZE_NUM, SIZE_NUM);
	loadimage(&number[2], ".\\image\\2.jpg", SIZE_NUM, SIZE_NUM);
	loadimage(&number[3], ".\\image\\3.jpg", SIZE_NUM, SIZE_NUM);
	loadimage(&number[4], ".\\image\\4.jpg", SIZE_NUM, SIZE_NUM);
	loadimage(&number[5], ".\\image\\5.jpg", SIZE_NUM, SIZE_NUM);
	loadimage(&number[6], ".\\image\\6.jpg", SIZE_NUM, SIZE_NUM);
	loadimage(&number[7], ".\\image\\7.jpg", SIZE_NUM, SIZE_NUM);
	loadimage(&number[8], ".\\image\\8.jpg", SIZE_NUM, SIZE_NUM);
	loadimage(&number[9], ".\\image\\9.jpg", SIZE_NUM, SIZE_NUM);

	//��Ϣ��ͼƬ
	loadimage(&show, ".\\image\\show.png", NULL);

	//��ըͼƬ
	loadimage(&bomb[0], ".\\image\\��ը1.png", SIZE_OBSTACLE, SIZE_OBSTACLE);
	loadimage(&bomb[1], ".\\image\\��ը2.png", SIZE_OBSTACLE, SIZE_OBSTACLE);

	//������ըͼƬ
	loadimage(&bomb_car[0], ".\\image\\��ը1.png", SIZE, SIZE);
	loadimage(&bomb_car[1], ".\\image\\��ը2.png", SIZE, SIZE);

	//����ֵͼƬ
	loadimage(&life, ".\\image\\life.bmp", NULL);

	//����ɹ�ͼƬ
	loadimage(&success, ".\\image\\flag.jpg", NULL);

	//��ɫ����ͼƬ
	loadimage(&black, ".\\image\\black.png", NULL);

	//����ͼƬ
	loadimage(&star_black, ".\\image\\star1.bmp", NULL);

	//����ͼƬ
	loadimage(&star_yellow, ".\\image\\star2.bmp", NULL);

	//�յ�ͼƬ
	loadimage(&terminalPoint, ".\\image\\�յ�.png", NULL);

	//gamewinͼƬ
	loadimage(&gameWin, ".\\image\\gamewin.bmp", NULL);

	//gameoverͼƬ
	loadimage(&gameOver, ".\\image\\gameover.bmp", WIDTH, HEIGHT);

	//����ͼƬ
	loadimage(&site, ".\\image\\site.jpg", NULL);

	//��������ֵͼƬ
	loadimage(&add_life, ".\\image\\������ֵ.png", NULL);

	//���ӵ�ҩͼƬ
	loadimage(&add_rocket, ".\\image\\�ӵ�ҩ��.png", NULL);
}

//������Ĵ���
Car* createCar(int x, int y, int speed, bool life, time_t last) {
	Car* car = (Car*)malloc(sizeof(Car) * 1);

	car->x = x;
	car->y = y;
	car->speed = speed;
	car->life = life;
	car->last = last;

	return car;
}

//�ϰ�����Ĵ���
Obstacle* createObstacle(int x, int y, int speed, bool status, time_t last) {
	Obstacle* obstacle = (Obstacle*)malloc(sizeof(Obstacle) * 1);

	obstacle->x = x;
	obstacle->y = y;
	obstacle->speed = speed;
	obstacle->status = status;
	obstacle->last = last;

	return obstacle;
}

//��ͼ����Ĵ���
Map* createMap(int x, int y, int speed) {
	Map* map = (Map*)malloc(sizeof(Map) * 1);

	map->x = x;
	map->y = y;
	map->speed = speed;

	return map;
}

//�������Ĵ���
Rocket* createRocket(int x, int y, int speed, bool status) {
	Rocket* rocket = (Rocket*)malloc(sizeof(Rocket) * 1);

	rocket->x = x;
	rocket->y = y;
	rocket->speed = speed;
	rocket->status = status;

	return rocket;
}

//����û������Ƿ��пո�
bool haveSpace(char* input) {
	bool isSpace = false;
	//�����ַ�������
	for (int i = 0; i < strlen(input); i++) {
		if (input[i] == ' ') {
			isSpace = true;
		}
	}

	return isSpace;
}

//�����û�����
char* login_name() {
	char* name;
	char title[30] = "��ӭ���棡������Ϸ�ĵ�½����";		//��ʾ�����ı���
	char clue[40] = "�����������û���(���ܺ��пո�)";		//��ʾ����������
	//��̬�������ֿռ�
	name = (char*)malloc(sizeof(char) * 50);
	while (1) {
		InputBox(name, 20, clue, title);

		//����û������뺬�пո�
		if (haveSpace(name))
		{
			/*
			����������������:
			MB_ICONQUESTION	��ʾ Warning Message ͼ��
			MB_SETFOREGROUND  ��־ȷ����Ϣ���Ϊǰ̨���ڡ�
			*/
			//����������ʾ���������
			MessageBox(NULL,
				"����ȷ�����û���",
				"����ȷ�����û���", MB_ICONEXCLAMATION | MB_SETFOREGROUND);
			continue;
		}

		//����û�δ����
		if (*name == '\0')
		{
			MessageBox(NULL,
				"��δ�����û���",
				"��δ�����û���", MB_ICONEXCLAMATION | MB_SETFOREGROUND);
			continue;
		}
		break;
	}

	return name;
}

//�����û�����
char* login_password() {
	char* password;
	char title[30] = "��¼����";							//��ʾ�����ı���
	char clue[40] = "��������������(���ܺ��пո�)";		//��ʾ����������
	//���붯̬����ռ�
	password = (char*)malloc(sizeof(char) * 50);
	while (1) {
		InputBox(password, 20, clue, title);

		//����û������뺬�пո�
		if (haveSpace(password))
		{
			/*
			����������������:
			MB_ICONQUESTION	��ʾ Warning Message ͼ��
			MB_SETFOREGROUND  ��־ȷ����Ϣ���Ϊǰ̨���ڡ�
			*/
			//����������ʾ���������
			MessageBox(NULL,
				"����ȷ��������",
				"����ȷ��������", MB_ICONEXCLAMATION | MB_SETFOREGROUND);
			continue;
		}

		//����û�δ����
		if (*password == '\0')
		{
			MessageBox(NULL,
				"��δ��������",
				"��δ��������", MB_ICONEXCLAMATION | MB_SETFOREGROUND);
			continue;
		}
		break;
	}

	return password;
}

// ����û��Ƿ����
void checkUsers(char* name)
{
	FILE* fp;
	errno_t err;													//int�ض��壬���ں���Ĵ������
	//fopen_s�ķ���ֵ����Ӧ�Ĵ�����룬�������Ų�����(���ļ��ɹ�����0��ʧ�ܷ��ط�0)
	err = fopen_s(&fp, ".\\users.txt", "a+");						//��users�ļ�����ִ�ж�д����

	//����ļ���дû�д���
	if (err == 0) {
		//���ļ�ָ�������ļ���ʼλ�ã���ƫ����Ϊ0
		fseek(fp, 0, SEEK_SET);
		char check_password[50];
		// ����û������Ƿ��е�ǰ�û������û�У�����û����һ�ӭ������У���������û������һ�ӭ�û�����
		int flag;
		//���ļ�ָ�벻���ļ���βʱ������ѭ��
		while (!(feof(fp)))
		{
			char check_name[50];
			fscanf(fp, "%s", check_name);
			fscanf(fp, "%s", check_password);
			if (!(strcmp(check_name, name)))
			{
				flag = 1;

				break;		// һ�������б���������˳�ѭ������ֹflag��ˢ��
			}
			else
				flag = 0;
		}

		//�����ҵ�һ��������Ϸ
		if (flag == 0)
		{
			first_play = true;
			password = login_password();
			fprintf(fp, "%s %s\n", name, password);
			char string[70];
			sprintf_s(string, "�û�:%s ��ӭ���棡", name);
			MessageBox(NULL,
				"��ӭ������CrazzyHe�ĵ�һ����Ϸ\n��׼������ս���������Ϸ����\n���������ĵڶ�����Ŀ���и���ϸ����Ϸ�淨����Ŷ��",
				string, MB_SETFOREGROUND);

		}

		//�������Ƿǵ�һ��������Ϸ
		else
		{
			first_play = false;
			int flag = 0;	//�����������������
			while (1)
			{
				password = login_password();

				// �������������ȷ
				if (!(strcmp(password, check_password)))
				{
					char string[70];
					sprintf_s(string, "�û�:%s ��ӭ����", name);
					MessageBox(NULL,
						"��ӭ������׼����ˢ�¼�¼����",
						string, MB_SETFOREGROUND);
					break;
				}

				// ��������������
				else
				{
					if (flag == 0)
					{
						MessageBox(NULL,
							"��������㻹��1�λ���������������\n������򽫹ر�",
							"�������", MB_SETFOREGROUND);
						flag = 1;
						continue;
					}
					else
					{
						MessageBox(NULL,
							"������󣬳���ر�",
							"�������", MB_SETFOREGROUND);
						exit(-1);
					}
				}
			}
		}
	}
	//���д���ļ�����
	else if (err != 0) {
		MessageBox(NULL, "�ļ���������",
			"�ļ�������������users.txt�ļ�������", MB_SETFOREGROUND);
		exit(-1);
	}
	//�ر��ļ�ָ�룬�������������������ļ���
	fclose(fp);
}

//����ѡ������
int drawCarSelection() {
	Button* chose_Audi, * chose_Bmw, * chose_Mercedes, * success;
	int selection;
	bool choice_car = false;

	//��ͼ
	putimage(0, 0, &garage);
	putimage(170, 220, &car_Audi[0], NOTSRCERASE);
	putimage(170, 220, &car_Audi[1], SRCINVERT);
	putimage(540, 220, &car_Bmw[0], NOTSRCERASE);
	putimage(540, 220, &car_Bmw[1], SRCINVERT);
	putimage(910, 220, &car_Mercedes[0], NOTSRCERASE);
	putimage(910, 220, &car_Mercedes[1], SRCINVERT);
	outtextxy(450, HEIGHT / 2 + 250, "��ѡ����������");

	//��ť�ṹ���ʼ��
	chose_Audi = createButton(150, 470, SIZE + 20, SIZE - 100, RGB(255, 165, 165), "ѡ��µ�");
	chose_Bmw = createButton(520, 470, SIZE + 20, SIZE - 100, RGB(255, 165, 165), "ѡ����");
	chose_Mercedes = createButton(890, 470, SIZE + 20, SIZE - 100, RGB(255, 165, 165), "ѡ�񱼳�");
	success = createButton(520, 700, SIZE + 20, SIZE - 100, RGB(255, 165, 165), "ѡ���ɹ�");

	//���ư�ť�ṹ��
	drawButton(chose_Audi, false);
	drawButton(chose_Bmw, false);
	drawButton(chose_Mercedes, false);

	//����¼�ѭ��
	while (true) {
		m = getmessage(EX_MOUSE);	//��ȡ�����Ϣ
		switch (m.message) {
		case WM_LBUTTONDOWN:
			//����Ƿ��¶�Ӧ��ѡ����ť

			//ѡ��µϳ�
			if (mouseDetect(chose_Audi, m)) {
				cleardevice();
				putimage(0, 0, &garage);
				putimage(520, 400, &car_Audi[0], NOTSRCERASE);
				putimage(520, 400, &car_Audi[1], SRCINVERT);
				//���δ���ѡ���ɹ���Ч
				PlaySound(".\\sound\\light.wav", NULL, SND_ASYNC | SND_FILENAME);
				selection = 1;
				choice_car = true;
				break;
			}

			//ѡ����
			if (mouseDetect(chose_Bmw, m)) {
				cleardevice();
				putimage(0, 0, &garage);
				putimage(520, 400, &car_Bmw[0], NOTSRCERASE);
				putimage(520, 400, &car_Bmw[1], SRCINVERT);
				PlaySound(".\\sound\\light.wav", NULL, SND_ASYNC | SND_FILENAME);
				selection = 2;
				choice_car = true;
				break;
			}

			//ѡ�񱼳۳�
			if (mouseDetect(chose_Mercedes, m)) {
				cleardevice();
				putimage(0, 0, &garage);
				putimage(520, 400, &car_Mercedes[0], NOTSRCERASE);
				putimage(520, 400, &car_Mercedes[1], SRCINVERT);
				PlaySound(".\\sound\\light.wav", NULL, SND_ASYNC | SND_FILENAME);
				selection = 3;
				choice_car = true;
				break;
			}
		}
		if (choice_car == true) {
			break;
		}
	}
	drawButton(success, false);
	Sleep(3000);
	return selection;
}

//��long�������ֳ����ڻ�����
void PutNumber(
	long x,															//���λ��
	long y,
	long number,													//��Ҫת��������
	int TextSize,													//���ֵĳߴ�
	int TextProportion,												//���ֵĸ߿��
	int TextInterval,												//����֮��ļ��
	COLORREF tc,													//������ɫ(Ĭ��Ϊ��)
	LPCTSTR font													//��������
)
{
	int max;
	long int one_data;												//��ǰλ����

	//������������
	settextcolor(tc);												//����������ɫ
	setbkmode(TRANSPARENT);											//�������ֱ���Ϊ͸��ɫ
	settextstyle(TextSize * TextProportion, TextSize, font);		//�����������ֵĴ�С
	if (TextInterval == 0)											//������Ϊ0�����Զ��������
		TextInterval = TextSize;
	for (max = 0; max < 10; max++)									//�������λ��max
		if (number / pow(10, max) < 10)
			break;
	while (number >= 0) {											//��λ�������
		if (max < 0 || x > getwidth())								//���λ��С��0����x��������߽�
			return;
		one_data = number / (long)pow(10, max);
		outtextxy(x, y, (char)(one_data + 48));
		number -= one_data * (long)pow(10, max);
		--max;
		x += TextInterval;
	}
}

//��ʤ����
void winInterface() {
	char* show_score;
	Button* returnMain, * quit;
	show_score = (char*)malloc(sizeof(char) * 100);
	sprintf(show_score, "%ld", score);
	MessageBox(NULL,
		show_score,
		"��ϲ����ʤ�����ķ���Ϊ��", MB_ICONEXCLAMATION | MB_SETFOREGROUND);
	putimage(0, 200, &success);
	settextcolor(WHITE);
	settextstyle(50, 0, "����");
	mciSendString("close all", NULL, 0, NULL);
	mciSendString("open .\\sound\\gamewin.mp3 alias gamewinmusic", NULL, 0, NULL);
	mciSendString("open .\\sound\\light.mp3 alias lightmusic", NULL, 0, NULL);
	mciSendString("play gamewinmusic from 0", NULL, 0, NULL);
	BeginBatchDraw();
	//��̬ʤ������չʾ
	for (int i = -1280; i <= 0; i++) {
		putimage(i, 200 + success.getheight(), &black);
		outtextxy(i + 20, 250 + success.getheight(), "��ң�");
		outtextxy(i + 200, 250 + success.getheight(), name);
		//�����ź���
		putimage(i + 1280 - star_black.getwidth(),
			200 + 2 * success.getheight() - star_black.getheight(),
			&star_black);
		//�ڶ��ź���
		putimage(i + 1280 - star_black.getwidth() * 2,
			200 + 2 * success.getheight() - star_black.getheight(),
			&star_black);
		//��һ�ź���
		putimage(i + 1280 - star_black.getwidth() * 3,
			200 + 2 * success.getheight() - star_black.getheight(),
			&star_black);
		FlushBatchDraw();
	}
	EndBatchDraw();
	Sleep(1000);
	//��һ�Ż���
	if (first_star <= score) {
		mciSendString("play lightmusic from 0", NULL, 0, NULL);
		putimage(1280 - star_yellow.getwidth() * 3,
			200 + 2 * success.getheight() - star_yellow.getheight(),
			&star_yellow);
		Sleep(1000);
	}
	//�ڶ��Ż���
	if (second_star <= score) {
		mciSendString("play lightmusic from 0", NULL, 0, NULL);
		putimage(1280 - star_yellow.getwidth() * 2,
			200 + 2 * success.getheight() - star_yellow.getheight(),
			&star_yellow);
		Sleep(1000);
	}
	//�����Ż���
	if (third_star <= score) {
		mciSendString("play lightmusic from 0", NULL, 0, NULL);
		putimage(1280 - star_yellow.getwidth(),
			200 + 2 * success.getheight() - star_yellow.getheight(),
			&star_yellow);
		Sleep(1000);
	}
	node_main();
	//������ť����
	returnMain = createButton(0, 800, 200, 100, BLACK, "������");
	quit = createButton(1080, 800, 200, 100, BLACK, "�˳���Ϸ");

	//���ư�ť
	drawButton(returnMain, false);
	drawButton(quit, false);
	FlushBatchDraw();

	//�����������ͣҳ�水ť�ĵ���¼�
	while (true) {
		m = getmessage(EX_MOUSE);											//��ȡ�����Ϣ
		switch (m.message)
		{
		case WM_LBUTTONDOWN:
			//����Ƿ��¡����������桱��ť
			if (mouseDetect(returnMain, m)) {
				cleardevice();
				drawFrontCover();
			}
			//����Ƿ��¡��˳���Ϸ����ť
			if (mouseDetect(quit, m)) {
				exit(-1);
			}
		}
	}
}

//��ȡ���а�
TOPNODE* loadNode() {
	TOPNODE* h, * r;
	TOPNODE* p;
	FILE* top;
	errno_t err;													//int�ض��壬���ں���Ĵ������
	h = NULL;
	r = NULL;
	//fopen_s�ķ���ֵ����Ӧ�Ĵ�����룬�������Ų�����(���ļ��ɹ�����0��ʧ�ܷ��ط�0)
	err = fopen_s(&top, ".\\tops.txt", "r");						//��tops�ļ�����ִ�ж�д����
	//����ļ���дû�д���
	if (err == 0) {
		//���ļ�ָ�������ļ���ʼλ�ã���ƫ����Ϊ0
		fseek(top, 0L, SEEK_SET);
		for (int i = 0; i < 10; i++) {
			p = (TOPNODE*)malloc(sizeof(TOPNODE) * 1);
			fscanf_s(top, "%d", &p->no);
			fscanf_s(top, "%s", p->name, _countof(p->name));
			fscanf_s(top, "%d", &p->score);
			//β�巨������������ȡ���а���Ϣ
			p->next = NULL;
			if (h == NULL) {
				h = p;
				r = p;
			}
			else {
				r->next = p;
				r = p;
			}
		}
	}
	//�����ȡ���а��ļ�����
	else if (err != 0) {
		MessageBox(NULL, "�ļ���������",
			"�ļ�������������tops.txt�ļ�������", MB_SETFOREGROUND);
		exit(-1);
	}
	fclose(top);
	//����������ʵ�ֵĲ��ԣ��书����������ʵ��
	//���Դ��룺
	/*
	TOPNODE* q = h;
	while (q != NULL) {
		printf("%d %s %d \n", q->no, q->name, q->score);
		q = q->next;
	}
	*/
	return h;
}

// չʾ���а�
void showNode()
{

	char tops[500] = "No\tName\t\tPlayer's Best Score\n";					//�洢���а�ǰʮ����
	TOPNODE* h;
	TOPNODE* q;
	h = loadNode();
	q = h;
	for (int i = 0; i < 10; i++)
	{
		char top[40];
		sprintf_s(top, "%d\t%s\t\t%d\n", q->no, q->name, q->score);
		strcat_s(tops, top);
		q = q->next;
	}
	MessageBox(NULL, tops,
		"********************���а�����***********************", MB_SETFOREGROUND);
}

//��д���а�
void rewriteNode(TOPNODE* h) {
	/*
	�ڵ��øú���֮ǰӦȷ��tops.txt�ļ��Ѵ��ڹر�״̬����ָ������
	���򣬿��ܻ����stream.valid()�����⣬topsָ�붪ʧ
	*/
	bool is_top;
	int temp_no;
	int temp_score;
	char temp_name[50];
	TOPNODE* p;
	FILE* tops;
	errno_t err;
	p = (TOPNODE*)malloc(sizeof(TOPNODE) * 1);
	p = h;
	is_top = false;
	err = fopen_s(&tops, ".\\tops.txt", "w");
	fseek(tops, 0L, SEEK_SET);
	while (p != NULL) {
		fprintf_s(tops, "%d %s %d\n", p->no, p->name, p->score);
		p = p->next;
	}
	fclose(tops);
	err = fopen_s(&tops, ".\\tops.txt", "r");
	fseek(tops, 0L, SEEK_SET);
	for (int i = 0; i < 10; i++)
	{
		fscanf_s(tops, "%d", &temp_no);
		fscanf_s(tops, "%s", temp_name, _countof(temp_name));
		fscanf_s(tops, "%d", &temp_score);
		if (strcmp(name, temp_name) == 0)
		{
			is_top = true;
			break;
		}
	}
	//����ϰ�
	if (is_top == true)
	{
		MessageBox(NULL, "��ϲ�ϰ񣬽���ǰʮ��",
			"===============��ϲ�ϰ񣡣�����===============", MB_SETFOREGROUND);
	}
	else
	{
		MessageBox(NULL, "��ϲͨ�أ����������ź�����û�ܵ������а��ٽ����������ͣ�",
			"===============��ϲͨ�أ�������===============", MB_SETFOREGROUND);
	}
	fclose(tops);
}

//�ع����а�˳��
TOPNODE* reNode(TOPNODE* h) {
	TOPNODE* p, * f;
	TOPNODE temp;
	int i = 1;
	p = (TOPNODE*)malloc(sizeof(TOPNODE) * 1);
	p = h;
	//��������
	while (p->next != NULL) {
		f = (TOPNODE*)malloc(sizeof(TOPNODE) * 1);
		f = p->next;
		while (f != NULL) {
			if (p->score < f->score) {
				temp = *p;
				*p = *f;
				*f = temp;
				temp.next = p->next;
				p->next = f->next;
				f->next = temp.next;
			}
			f = f->next;
		}
		p = p->next;
	}
	p = h;
	while (p != NULL)
	{
		p->no = i;
		p = p->next;
		i++;
	}
	//�ֶ�����tops.txt�ڲ����а���������֤���������ѿ�����������
	/*
	p = h;
	while (p != NULL) {
		printf("%d %s %d\n", p->no, p->name, p->score);
		p = p->next;
	}
	*/
	return h;
}

// �ı����а�����
void changeNode(TOPNODE* h)
{
	TOPNODE* p, * f;
	int flag;
	// �����
	char temp_name[50];
	// ������
	int temp_no;
	int temp_score;
	//Ϊ����ڵ�p��̬��������ռ�
	p = (TOPNODE*)malloc(sizeof(TOPNODE) * 1);
	flag = 0;
	// �Ƿ����б���Ҽ��
	FILE* tops;
	errno_t err;
	err = fopen_s(&tops, ".\\tops.txt", "r");
	//���ļ�ָ�������ļ�ͷ��
	fseek(tops, 0L, SEEK_SET);
	if (err == 0) {
		while (!(feof(tops))) {
			fscanf_s(tops, "%d", &temp_no);
			fscanf_s(tops, "%s", temp_name, _countof(temp_name));
			fscanf_s(tops, "%d", &temp_score);
			if (strcmp(temp_name, name) == 0) {
				flag = 1;													//�û��Ѵ���
				break;
			}
		}
		//�������Ѿ�����
		if (flag == 1) {
			if (score > temp_score) {
				p = h;
				while (p != NULL) {
					if (strcmp(temp_name, p->name) == 0) {
						p->score = score;
						break;
					}
					p = p->next;
				}
				fclose(tops);
				h = reNode(h);
				rewriteNode(h);
				MessageBox(NULL, "��ϲ��ˢ���˸�����ʷ��¼��������",
					"===============��ϲ�Ƽ�¼��������===============", MB_SETFOREGROUND);
			}
			else {
				MessageBox(NULL, "��ϲͨ�أ����������ź�����û��ˢ�¸�����ʷ��¼���ٽ����������ͣ�",
					"===============��ϲͨ�أ�������===============", MB_SETFOREGROUND);
			}
		}
		else if (flag == 0) {
			fclose(tops);
			p = h;
			while (p->next != NULL) {
				p = p->next;
			}
			TOPNODE* f;
			f = (TOPNODE*)malloc(sizeof(TOPNODE) * 1);
			memset(f->name, 0, 50);
			strcat(f->name, name);
			f->score = score;
			f->next = NULL;
			p->next = f;
			MessageBox(NULL, "��ϲͨ�أ����������ź�����֮ǰ��û�е������а�!",
				"===============��ϲͨ�أ�������===============", MB_SETFOREGROUND);
			h = reNode(h);
			rewriteNode(h);
		}
	}
	return;
}

// ���а�����������
void node_main()
{
	TOPNODE* h = NULL;
	h = loadNode();
	h = reNode(h);
	changeNode(h);
	showNode();
}

//��ͣ����
void pauseInterface() {
	Button* goOn, * site, * quit;
	ExMessage m;
	bool play = false;
	menu_begin = time(NULL);
	isMenu = true;
	setbkmode(TRANSPARENT);													//�������ֱ���͸��
	settextcolor(BLACK);													//����������ɫ
	settextstyle(100, 0, "����");

	//������ť����
	goOn = createButton(440, 360, 400, 100, BLACK, "������Ϸ");
	//site = createButton(440, 520, 400, 100, BLACK, "��Ϸ����");
	quit = createButton(440, 680, 400, 100, BLACK, "�˳���Ϸ");
	roundrect(340, 160, 940, 800, 30, 30);
	outtextxy(540, 200, "��ͣ");

	//���ư�ť
	drawButton(goOn, false);
	//drawButton(site, false);
	drawButton(quit, false);
	FlushBatchDraw();

	//�����������ͣҳ�水ť�ĵ���¼�
	while (!play) {
		m = getmessage(EX_MOUSE);											//��ȡ�����Ϣ
		switch (m.message)
		{
		case WM_LBUTTONDOWN:
			//����Ƿ��¡���ʼ��Ϸ����ť
			if (mouseDetect(goOn, m)) {
				cleardevice();
				play = true;
				menu_progress = time(NULL);
				menu_sum += (menu_progress - menu_begin);
				break;
			}
			/*
			//����Ƿ��¡����á���ť
			if (mouseDetect(site, m)) {
			}
			*/
			//����Ƿ��¡��˳���Ϸ����ť
			if (mouseDetect(quit, m)) {
				exit(-1);
			}
		}
	}
}

//ʧ�ܽ���
void loseInterface() {
	EndBatchDraw();
	Button* returnMain, * quit;
	MessageBox(NULL,
		"��������Ѫ���Ѻľ�����л�������棬��ӭ���ٴ���ս",
		"ʧ��", MB_SETFOREGROUND);
	mciSendString("close all", NULL, 0, NULL);
	mciSendString("open .\\sound\\gameover.mp3 alias gameovermusic", NULL, 0, NULL);
	mciSendString("play gameovermusic from 0", NULL, 0, NULL);
	//������ť����
	returnMain = createButton(0, 800, 200, 100, BLACK, "������");
	quit = createButton(1080, 800, 200, 100, BLACK, "�˳���Ϸ");
	cleardevice();
	//���ư�ť
	putimage(0, 0, &gameOver);
	drawButton(returnMain, false);
	drawButton(quit, false);
	//�����������ͣҳ�水ť�ĵ���¼�
	while (true) {
		m = getmessage(EX_MOUSE);											//��ȡ�����Ϣ
		switch (m.message)
		{
		case WM_LBUTTONDOWN:
			//����Ƿ��¡����������桱��ť
			if (mouseDetect(returnMain, m)) {
				cleardevice();
				drawFrontCover();
			}
			//����Ƿ��¡��˳���Ϸ����ť
			if (mouseDetect(quit, m)) {
				exit(-1);
			}
		}
	}
}

//ģʽһ
void mode_1() {
	Car* car;
	Map* map;
	Obstacle** obstacle;
	Rocket** rocket;
	int selection;
	int life_leave;															//����ֵʣ������
	int rocket_leave;														//����ֵʣ������
	IMAGE img_1, img_2;
	//�����ϰ���ָ������
	obstacle = (Obstacle**)malloc(sizeof(Obstacle) * 3);
	//�������ָ������
	rocket = (Rocket**)malloc(sizeof(Rocket) * 3);
	map = createMap(0, -(960 * 9), 1);										//������ͼ����
	car = createCar(640, 750, 2, true, 0);									//������������
	selection = drawCarSelection();
	//��ͣ���ű�������
	//PlaySound(NULL, NULL, SND_FILENAME | SND_PURGE);
	mciSendString("stop bkmusic", NULL, 0, NULL);
	//���ֳ�ʼ����
	mciSendString("open .\\sound\\game.mp3 alias gamemusic", NULL, 0, NULL);
	mciSendString("open .\\sound\\fire.mp3 alias firemusic", NULL, 0, NULL);
	mciSendString("open .\\sound\\crash.mp3 alias crashmusic", NULL, 0, NULL);
	mciSendString("open .\\sound\\explode.mp3 alias explodemusic", NULL, 0, NULL);
	//ѭ��������Ϸ����
	mciSendString("play gamemusic repeat from 0", NULL, 0, NULL);
	//�������ѡ��ѡ�񣬽���ͼƬ��ʼ��
	switch (selection) {
		//ѡ��µϳ�
	case 1:
		img_1 = car_Audi[0];
		img_2 = car_Audi[1];
		break;

		//ѡ����
	case 2:
		img_1 = car_Bmw[0];
		img_2 = car_Bmw[1];
		break;

		//ѡ�񱼳۳�
	case 3:
		img_1 = car_Mercedes[0];
		img_2 = car_Mercedes[1];
		break;
	}

	//��ʼ��Ѫ����Ϣ
	life_leave = 3;

	//��ʼ��Ѫ����Ϣ
	rocket_leave = 3;

	//��ʼ���ϰ�����Ϣ
	for (int i = 0; i < 3; i++) {
		obstacle[i] = createObstacle(map_obstacle[rand() % 3], -(rand() % (100)), (rand() % 1) + 1, true, 0);
	}

	//��ʼ�������Ϣ
	for (int i = 0; i < 3; i++) {
		rocket[i] = createRocket(0, 0, 1, true);
	}
	cleardevice();
	game_begin = time(NULL);												//��Ϸ��ʼʱ��

	//��ͼ��ͼ
	putimage(map->x, map->y, &map_2);

	//��ҿ��Ƴ�����ʼλ����ʾ
	putimage(car->x, car->y, &img_1, NOTSRCERASE);
	putimage(car->x, car->y, &img_2, SRCINVERT);
	BeginBatchDraw();

	//ģʽһ��ѭ��
	while (true) {
		game_progress = time(NULL);											//��Ϸ����ʱ��
		game_sum = game_progress - game_begin;								//��Ϸ��ʱ��

		//���ͼƬ���ص���ͷ����������ͼ
		if (map->y == 0) {
			map->x = 0;
			map->y = -(960 * 9);
		}

		//��Ϸ����ʱ��3s���ٲ����ϰ����������������ϰ���
		if (game_sum - menu_sum >= 3) {
			for (int i = 0; i < 3; i++) {
				obstacle[i]->y += obstacle[i]->speed;
			}
		}

		//��ͼ�ƶ�
		map->y += map->speed;

		//�������ƶ�
		//������ �� �� W ʱ
		if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W')) {
			if (0 <= car->y) {
				car->y -= car->speed;

				//�����ٶȸı���
				if (!isUp) {
					isUp = true;
					control_up_last = game_sum - menu_sum;
				}

				//�ٶȼ��1s������
				if (speed_show <= speed_max && game_sum - menu_sum - control_up_last >= 1) {
					isUp = false;
					speed_show += 1;
				}
			}
		}

		//�������ƶ�
		//������ �� �� S ʱ
		if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S')) {
			if (car->y <= 760) {
				car->y += car->speed;

				//�����ٶȸı���
				if (!isDown) {
					isDown = true;
					control_down_last = game_sum - menu_sum;
				}

				//�ٶȼ��3s������
				if (speed_show >= speed_min && game_sum - menu_sum - control_down_last >= 3) {
					isDown = false;
					speed_show -= 1;
				}
			}
		}

		//�������ƶ�
		//������ �� �� A ʱ
		if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A')) {
			if (150 <= car->x) {
				car->x -= car->speed;
			}
		}

		//�������ƶ�
		//������ �� �� D ʱ
		if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D')) {
			if (car->x <= 930) {
				car->x += car->speed;
			}
		}

		//������
		//��һ�η�����
		if (!onFire) {
			fire_last = time(NULL);
			onFire = true;

			//�����¿ո��ʱ
			if (GetAsyncKeyState(VK_SPACE)) {
				mciSendString("play firemusic from 0", NULL, 0, NULL);
				for (int i = 0; i < 3; i++) {
					//����ϰ���״̬Ϊ��
					if (rocket[i]->status == true) {
						rocket[i]->x = car->x + (SIZE / 2);
						rocket[i]->y = car->y;
						rocket[i]->status = false;
						rocket_leave -= 1;
						break;
					}
				}
			}
		}

		//�ǵ�һ�η�����
		else {
			//�������η�����
			fire_now = time(NULL);

			//���¿ո���ҷ�����1s�����ϣ��ſ��Է�����
			if (GetAsyncKeyState(VK_SPACE) && (fire_now - fire_last) >= 2) {
				mciSendString("play firemusic from 0", NULL, 0, NULL);
				for (int i = 0; i < 3; i++) {
					if (rocket[i]->status == true) {
						rocket[i]->x = car->x + (SIZE / 2);
						rocket[i]->y = car->y;
						rocket[i]->status = false;
						rocket_leave -= 1;
						break;
					}
				}
				fire_last = fire_now;
			}
		}

		//���ϰ������곬����Χ�����ʼ����λ��
		for (int i = 0; i < 3; i++) {
			if (obstacle[i]->y >= 960) {
				obstacle[i]->status = true;
				obstacle[i]->y = -(rand() % 960);
				obstacle[i]->x = map_obstacle[rand() % 3];
				obstacle[i]->speed = (rand() % 1) + 1;
			}
		}

		//�ı���λ�ã����ж����Ƿ񳬳���Χ������������Χ���������״̬Ϊ�ɷ���
		for (int i = 0; i < 3; i++) {
			if (rocket[i]->status == false) {
				if (rocket[i]->y <= 0) {
					rocket[i]->status = true;
					rocket_leave += 1;
					continue;
				}
				rocket[i]->y -= rocket[i]->speed;
			}
		}

		//�������ϰ������ײ���
		for (int i = 0; i < 3; i++) {
			//������ײ״̬
			if (isHit == true && game_sum - menu_sum >= 0 && game_sum - menu_sum - car->last > 1) {
				isHit = false;
			}
			//����ͼƬ�н���ʱif�жϳ���

			if (obstacle[i]->status == true
				&& abs((obstacle[i]->x + SIZE_OBSTACLE) / 2 - (car->x + SIZE) / 2) <= abs(SIZE_OBSTACLE - SIZE)
				&& abs((obstacle[i]->y + SIZE_OBSTACLE) / 2 - (car->y + SIZE) / 2) <= abs(SIZE_OBSTACLE - SIZE)
				) {
				//�������ֵ����
				if (life_leave == 0) {
					Sleep(1000);
					loseInterface();
				}

				//���ϴ���ײ���1s���ϲŻ�۳�����ֵ�����������ײ��Ѫ����������
				if (!isHit) {
					mciSendString("play crashmusic from 0", NULL, 0, NULL);
					life_leave -= 1;
					car->last = game_sum - menu_sum;
					isHit = true;
				}
			}
		}

		//������ϰ������ײ���
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				//����ͼƬ�н���ʱif�жϳ���
				if (rocket[j]->status == false
					&& rocket[j]->x >= obstacle[i]->x
					&& rocket[j]->x <= (obstacle[i]->x + SIZE_OBSTACLE)
					&& rocket[j]->y <= (obstacle[i]->y + (SIZE_OBSTACLE / 2))
					&& rocket[j]->y >= obstacle[i]->y
					|| (rocket[j]->status == false
						&& (rocket[j]->x + SIZE_ROCKET) <= (obstacle[i]->x + SIZE_OBSTACLE)
						&& (rocket[j]->x + SIZE_ROCKET) >= obstacle[i]->x
						&& (rocket[j]->y + SIZE_ROCKET) <= (obstacle[i]->y + (SIZE_OBSTACLE / 2))
						&& (rocket[j]->y + SIZE_ROCKET) >= obstacle[i]->y)
					) {
					mciSendString("play explodemusic from 0", NULL, 0, NULL);
					rocket[j]->status = true;
					rocket_leave += 1;
					rocket[j]->y = 2000;
					obstacle[i]->status = false;
					obstacle[i]->last = game_sum - menu_sum;
					score += 100;
				}
			}
		}
		//������ͼ
		cleardevice();

		//��ͼ��ͼ
		putimage(map->x, map->y, &map_2);

		//�����ϰ���ͼƬ��ͼ�ص�
		if (game_sum - menu_sum >= 3) {
			for (int i = 0; i < 3; i++) {
				for (int j = i + 1; j < 3; j++) {
					//����ͼƬ�н���ʱif�жϳ���
					if (obstacle[j]->x <= obstacle[i]->x
						&& obstacle[j]->x <= (obstacle[i]->x + SIZE_OBSTACLE)
						&& obstacle[j]->y <= (obstacle[i]->y + SIZE_OBSTACLE)
						&& obstacle[j]->y >= obstacle[i]->y
						|| ((obstacle[j]->x + SIZE_OBSTACLE) <= (obstacle[i]->x + SIZE_OBSTACLE)
							&& (obstacle[j]->x + SIZE_OBSTACLE) >= obstacle[i]->x
							&& (obstacle[j]->y + SIZE_OBSTACLE) <= (obstacle[i]->y + SIZE_OBSTACLE)
							&& (obstacle[j]->y + SIZE_OBSTACLE) >= obstacle[i]->y)
						) {
						obstacle[j]->y = -(rand() % 960);
					}
				}
			}
		}

		//�����ϰ���ͼƬ
		if (game_sum - menu_sum >= 3) {
			for (int i = 0; i < 3; i++) {
				//����ϰ���״̬Ϊ�棬��ͼʯͷ
				if (obstacle[i]->status == true) {
					putimage(obstacle[i]->x, obstacle[i]->y, &rock[0], NOTSRCERASE);
					putimage(obstacle[i]->x, obstacle[i]->y, &rock[1], SRCINVERT);
				}
				else {
					//��ը�������1s
					if (game_sum - menu_sum >= 3 && game_sum - menu_sum - obstacle[i]->last >= 1) {
						obstacle[i]->status = true;
						obstacle[i]->x = map_obstacle[rand() % 3];
						obstacle[i]->speed = (rand() % 1) + 1;
						obstacle[i]->y = -(rand() % 960);
					}
					else {
						putimage(obstacle[i]->x, obstacle[i]->y, &bomb[0], NOTSRCERASE);
						putimage(obstacle[i]->x, obstacle[i]->y, &bomb[1], SRCINVERT);
					}
				}
			}
		}

		//���û��ͼƬ
		for (int i = 0; i < 3; i++) {
			//������״̬Ϊ��,��ͼ���
			if (rocket[i]->status == false) {
				putimage(rocket[i]->x, rocket[i]->y, &rocket_img[0], NOTSRCERASE);
				putimage(rocket[i]->x, rocket[i]->y, &rocket_img[1], SRCINVERT);
			}
		}

		//չʾ��Ϣ��
		putimage(0, 0, &show);

		//ʱ����ʾ
		putimage(110, 37, &number[9 - ((game_sum - menu_sum) / 10)]);	//ʱ����ͼʮλ
		putimage(135, 37, &number[9 - ((game_sum - menu_sum) % 10)]);	//ʱ����ͼ��λ

		//�����ٶ���ʾ
		putimage(110, 15, &number[speed_show / 10]);					//�ٶ���ͼʮλ
		putimage(135, 15, &number[speed_show % 10]);					//�ٶ���ͼ��λ

		//·����ʾ
		distance = speed_show * (game_sum - menu_sum);
		PutNumber(110, 60, distance, 10, 2, 0, WHITE, "����");

		//����ͼƬ��ʾ
		putimage(car->x, car->y, &img_1, NOTSRCERASE);
		putimage(car->x, car->y, &img_2, SRCINVERT);

		//����ֵ��Ϣ��ʾ
		settextstyle(16, 0, ("Consolas"));
		settextcolor(BLACK);
		outtextxy(0, 160, "����ֵ��");
		rectangle(0, 200, (3 * life.getwidth() + 20), 200 + life.getheight() + 10);
		for (int i = 0; i < life_leave; i++) {
			putimage((i * life.getwidth() + 10), 205, &life);
		}

		//��ҩ����Ϣ��ʾ
		settextstyle(16, 0, ("Consolas"));
		settextcolor(BLACK);
		outtextxy(0, 340, "��ҩ����");
		rectangle(0, 380, (3 * life.getwidth() + 20), 380 + life.getheight() + 10);
		for (int i = 0; i < rocket_leave; i++) {
			putimage((i * life.getwidth() + 10), 385, &life);
		}

		//����ʱ����Ϣ��ʾ
		if (isHit == true && game_sum - menu_sum >= 0 && game_sum - menu_sum - car->last < 1) {
			outtextxy(100, 160, "�ܱ���״̬");
		}

		//������Ϣ��ʾ
		outtextxy(0, 250, "��÷�����");
		PutNumber(0, 280, score);
		FlushBatchDraw();

		//����ESC��������ͣ����
		if (GetAsyncKeyState(VK_ESCAPE)) {
			getimage(&temp, 0, 0, WIDTH, HEIGHT);
			mciSendString("pause gamemusic", NULL, 0, NULL);
			//��ͣ������ʾ
			pauseInterface();
			mciSendString("resume gamemusic", NULL, 0, NULL);
		}

		//ʱ�������ͨ���յ㻭�����
		if (game_sum - menu_sum >= 98) {
			break;
		}
	}
	EndBatchDraw();
	BeginBatchDraw();

	//ͨ���յ��߻������
	while (true) {
		cleardevice();
		//���ͼƬ���ص���ͷ����������ͼ
		if (map->y == 0) {
			map->x = 0;
			map->y = -(960 * 9);
		}

		//��ͼ�ƶ�
		map->y += map->speed;

		//���������ڵ�ͼ����
		if (car->x != WIDTH / 2 - 100 && car->y != HEIGHT / 2) {
			if (car->x <= WIDTH / 2 - 100) {
				car->x += car->speed;
			}
			if (car->x >= WIDTH / 2 - 100) {
				car->x -= car->speed;
			}
			if (car->y <= HEIGHT / 2) {
				car->y += car->speed;
			}
			if (car->y >= HEIGHT / 2) {
				car->y -= car->speed;
			}
		}
		//��������ڵ�ͼ���룬������յ�
		else {
			end_y += map->speed;
		}
		//��ͼͼƬ��ʾ
		putimage(map->x, map->y, &map_2);

		//չʾ��Ϣ��
		putimage(0, 0, &show);

		//ʱ����ʾ
		putimage(110, 37, &number[9 - ((game_sum - menu_sum) / 10)]);	//ʱ����ͼʮλ
		putimage(135, 37, &number[9 - ((game_sum - menu_sum) % 10)]);	//ʱ����ͼ��λ

		//�����ٶ���ʾ
		putimage(110, 15, &number[speed_show / 10]);					//�ٶ���ͼʮλ
		putimage(135, 15, &number[speed_show % 10]);					//�ٶ���ͼ��λ

		//·����ʾ
		distance = speed_show * (game_sum - menu_sum);
		PutNumber(110, 60, distance, 10, 2, 0, WHITE, "����");

		//�յ�ͼƬ��ʾ
		putimage(150, end_y, &terminalPoint);

		//����ͼƬ��ʾ
		putimage(car->x, car->y, &img_1, NOTSRCERASE);
		putimage(car->x, car->y, &img_2, SRCINVERT);

		//����ֵ��Ϣ��ʾ
		settextstyle(16, 0, ("Consolas"));
		settextcolor(BLACK);
		outtextxy(0, 160, "����ֵ��");
		rectangle(0, 200, (3 * life.getwidth() + 20), 200 + life.getheight() + 10);
		for (int i = 0; i < life_leave; i++) {
			putimage((i * life.getwidth() + 10), 205, &life);
		}

		//����ʱ����Ϣ��ʾ
		if (game_sum - menu_sum >= 0 && game_sum - menu_sum - car->last <= 1) {
			outtextxy(100, 160, "�ܱ���״̬");
		}

		//������Ϣ��ʾ
		outtextxy(0, 250, "��÷�����");
		PutNumber(0, 280, score);

		//�������ͨ���յ��ߣ����ֽ������
		if (car->y + SIZE == end_y) {
			break;
		}

		FlushBatchDraw();
	}
	EndBatchDraw();
	winInterface();		//ʤ������
}

void PutImgWithout(IMAGE& obj, int px, int py, COLORREF withouter = WHITE, DWORD* pbWnd = GetImageBuffer(), int wX = getwidth(), int wY = getheight(), DWORD bitsub = 0x00FFFFFF)
{
	DWORD* pbImg = GetImageBuffer(&obj);
	int iX = obj.getwidth();
	int iY = obj.getheight();
	for (int i1 = 0; i1 < iX; i1++)
	{
		for (int i2 = 0; i2 < iY; i2++)
		{
			// ����Ƿ�Խ��
			if (pointTsm(i1 + px, i2 + py, wX, wY) == -1)continue;

			// ����Ƿ�Ҫ�ų�����ɫ
			if ((pbImg[pointTsm(i1, i2, iX, iY)] & bitsub) == BGR(withouter))continue;

			// �����Դ�
			pbWnd[pointTsm(i1 + px, i2 + py, wX, wY)] = pbImg[pointTsm(i1, i2, iX, iY)];
		}
	}
}

void onUp(Car* car) {
	car->y -= car->speed * (int)round(sin(Forward + PI / 2));
	car->x -= car->speed * (int)round(cos(Forward + PI / 2));
}

void onDown(Car* car) {
	car->y += car->speed * (int)round(sin(Forward + PI / 2));
	car->x += car->speed * (int)round(cos(Forward + PI / 2));
}

void onLeft(Car* car) {
	if (canCircle(car)) {
		Forward -= PI / Rota;
		//car->x += (int)round(cos(Forward - PI / 2));
		//car->y += (int)round(sin(Forward - PI / 2));
	}
}

void onRight(Car* car) {
	if (canCircle(car)) {
		Forward += PI / Rota;
		//car->x += (int)round(cos(Forward + PI / 2));
		//car->y += (int)round(sin(Forward + PI / 2));
	}
}

//�ж��Ƿ������ת
bool canCircle(Car* car) {
	//ָ�򻺳�����ָ�����
	DWORD* map;						//����DWORD����ָ��(typedef unsigned int DWORD;)
	DWORD temp;
	int temp_x, temp_y;				//������ʱ�洢������x �� yֵ
	int iX, iY;						//������ʱ�洢�Ƿ������תʱ�������ж�x�� yֵ
	map = GetImageBuffer(&map_1);
	temp_x = car->x;
	temp_y = car->y;
	rotateimage(&car_circle[0], &car_black[0], -Forward, WHITE, true, false);
	rotateimage(&car_circle[1], &car_black[1], -Forward, WHITE, true, false);
	iX = car_circle[0].getwidth();
	iY = car_circle[0].getheight();
	for (int i = 0; i < iX; i++) {
		for (int j = 0; j < iY; j++) {
			temp = map[pointTsm((int)ceil(i + car->x), (int)ceil(j + car->y), WIDTH, HEIGHT)] & 0x00FFFFF;
			if (temp == BGR(RGB(215, 113, 53))
				|| temp == BGR(RGB(250, 250, 250))
				|| temp == BGR(RGB(79, 146, 202))) {
				return false;
			}
		}
	}

	return true;
}

//��Ե���
void edgeDetection(Car* car) {
	DWORD temp;
	//ָ�򻺳�����ָ�����
	DWORD* map;											//����DWORD����ָ��(typedef unsigned int DWORD;)
	map = GetImageBuffer(&map_1);						//��ȡ��ͼ����ʾ������ָ��
	int iX = car_black[0].getwidth();					//����ͼƬ���
	int iY = car_black[0].getheight();					//����ͼƬ�߶�

	//�������ص���ɫ�ж������Ƿ�Ӵ���Ե
	for (int i = 0; i < iX; i++)
	{
		for (int j = 0; j < iY; j++)
		{
			temp = map[pointTsm((int)ceil(i + car->x), (int)ceil(j + car->y), WIDTH, HEIGHT)] & 0x00FFFFFF;
			if (temp == BGR(RGB(215, 113, 53))
				|| temp == BGR(RGB(250, 250, 250))
				|| temp == BGR(RGB(79, 146, 202))) {
				car->speed = 1;
			}
			else {
				car->speed = 1;
			}
		}
	}
}

//Խ����
int pointTsm(int x, int y, int wide, int high)
{
	if (x < 0) return x = 0;
	if (x >= wide) return x = wide;
	if (y < 0) return y = 0;
	if (y >= high) return y = high;

	return wide * y + x;
}

//��������
void controlCar() {
	Car* car;
	IMAGE img_1, img_2;
	img_1 = car_black[0];
	img_2 = car_black[1];
	car = createCar(1000, 750, 1, true, 0);
	putimage(car->x, car->y, &img_1, NOTSRCERASE);
	putimage(car->x, car->y, &img_2, SRCINVERT);
	BeginBatchDraw();									//�ڴ滺�壬���⻭��˺��
	while (true) {
		//�������ƶ�
		if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W')) {
			onUp(car);
		}

		//�������ƶ�
		if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S')) {
			onDown(car);
		}

		//�������ƶ�
		if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A')) {
			onLeft(car);
			rotateimage(&img_1, &car_black[0], -Forward);
			rotateimage(&img_2, &car_black[1], -Forward, WHITE);
		}

		//�������ƶ�
		if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D')) {
			onRight(car);
			rotateimage(&img_1, &car_black[0], -Forward);
			rotateimage(&img_2, &car_black[1], -Forward, WHITE);
		}
		cleardevice();
		putimage(0, 0, &map_1);
		edgeDetection(car);
		//putimage(car->x, car->y, &car_black[0], NOTSRCERASE);
		//putimage(car->x, car->y, &car_black[1], SRCINVERT);
		putimage(car->x, car->y, &img_1, NOTSRCERASE);
		putimage(car->x, car->y, &img_2, SRCINVERT);
		FlushBatchDraw();								//�����廭���ͷŵ���ʾ����
	}

	EndBatchDraw();										//��������
}
//�״γ�����ͼƬָ�����ʽ������������ɫ������ͼƬ��Ϣ��ȡ��������ջ���������
/*
void getMapInformation(IMAGE map_1);					//�洢��ͼ��Ϣ
//�洢��ͼ��Ϣ
void getMapInformation(IMAGE map_1) {
	int temp[WIDTH * HEIGHT];
	int count = 0;
	map = GetImageBuffer(&map_1);
	for (int i = 0; i < WIDTH*HEIGHT; i++) {
		if (map[i] == BGR(RGB(250, 250, 250)) || map[i] == BGR(RGB(215, 113, 53)) || map[i] == BGR(RGB(79, 146, 202))) {
			temp[i] = 1;
			printf("1");
		}
		else {
			temp[i] = 0;
			printf("0");
		}
	}
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			map_information[i][j] = temp[count++];
		}
	}
	//
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			if (getpixel(i, j) == RGB(255, 255, 255) || getpixel(i, j) == RGB(215, 113, 53) || getpixel(i, j) == RGB(79, 146, 202)) {
				map_information[i][j] = 1;
			}
		}
	}
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			printf("%d",map_information[i][j]);
		}
		printf("\n");
	}
}
*/
