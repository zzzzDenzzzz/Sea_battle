#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<string>

using namespace std;

const int N = 10;
const int x_pos = 13;
const string DECK = "D";
const string HIT = "X";
const string MISS = "@";
const string HEADER = " ABCDEFGHIJ";
const string SINGLE_FIELD = { ":" };
int ships_id = 1;

enum Button
{
	RIGTH = 100,
	LEFT = 97,
	UP = 119,
	DOWN = 115,
	ROTATION = 114,
	ENTER = 13
};

void errorInput()
{
	::cout << "\n\n������ �����. ���������� ��� ���\n\n";
	Sleep(1000);
	::system("cls");
}

void gameMode(bool &game_mode)
{
	bool exit_cicle = true;
	char ch;
	string str;
	while (exit_cicle)
	{
		::cout << "����� ����:\n\n";
		::cout << "1 - ������� - ���������\n";
		::cout << "2 - ��������� - ���������\n";
		::cout << "\n>>>";

		ch = _getch();
		switch (ch)
		{
		case '1':
			str = "������� - ���������\n";
			exit_cicle = false;
			game_mode = true;
			break;
		case '2':
			str = "��������� - ���������\n";
			exit_cicle = false;
			game_mode = false;
			break;
		default:
			errorInput();
			break;
		}
	}

	::system("cls");
}

void placementOfShips(bool &placement_of_ships)
{
	string str;
	char ch;
	bool exit_cicle = true;
	while (exit_cicle)
	{
		::cout << "����������� ��������:\n\n";
		::cout << "1 - �������\n";
		::cout << "2 - ��������� ����������� �� ������\n";
		::cout << "\n>>>";

		ch = _getch();
		switch (ch)
		{
		case '1':
			str = "�������\n";
			exit_cicle = false;
			placement_of_ships = true;
			break;
		case '2':
			str = "��������� ����������� �� ������\n";
			exit_cicle = false;
			placement_of_ships = false;
			break;
		default:
			errorInput();
			break;
		}
	}

	::system("cls");
}

void computerGameMode(bool &computer_game_mode)
{
	string str;
	bool exit_cicle = true;
	char ch;
	while (exit_cicle)
	{
		::cout << "����� ���� ����������:\n\n";
		::cout << "1 - ��������� �������\n";
		::cout << "2 - ���������������� ����\n";
		::cout << "\n>>>";

		ch = _getch();
		switch (ch)
		{
		case '1':
			str = "��������� �������\n";
			exit_cicle = false;
			computer_game_mode = true;
			break;
		case '2':
			str = "���������������� ����\n";
			exit_cicle = false;
			computer_game_mode = false;
			break;
		default:
			errorInput();
			break;
		}
	}

	::system("cls");
}

void settingGameModes(bool &game_mode, bool &placement_of_ships, bool &computer_game_mode)
{
	string str_1, str_2, str_3;
	if (game_mode)
	{
		str_1 = "������� - ���������\n";
	}
	else
	{
		str_1 = "��������� - ���������\n";
	}
	::cout << "����� ����: " << str_1 << endl;
	if (placement_of_ships)
	{
		str_2 = "�������\n";
	}
	else
	{
		str_2 = "��������� ����������� �� ������\n";
	}
	::cout << "����������� ��������: " << str_2 << endl;
	if (computer_game_mode)
	{
		str_3 = "��������� �������\n";
	}
	else
	{
		str_3 = "���������������� ����\n";
	}
	::cout << "����� ���� ����������: " << str_3 << endl;
	::cout << "\t\t�������� ����... " << endl;

	Sleep(5000);
	::system("cls");
}

void gotoXY(short x, short y)
{
	COORD c{ x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void cursorMove(int x_pos, int y_pos)
{
	COORD scrn;
	HANDLE h_output = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = x_pos;
	scrn.Y = y_pos;
	SetConsoleCursorPosition(h_output, scrn);
}

void shipXY(int &x, int &y, int &dir)
{
	switch (dir)
	{
	case 0:
		x++;
		break;
	case 1:
		y++;
		break;
	case 2:
		x--;
		break;
	case 3:
		y--;
		break;
	}
}

void shipShow(int x, int y, int dir, int size_ship)
{
	for (int i = 0; i < size_ship; i++)
	{
		gotoXY(x + 1, y + 1);
		::cout << DECK;
		shipXY(x, y, dir);
	}
}

bool shipInMap(int x, int y, int dir, int size_ship)
{
	bool in_map = 1;
	//�������� ���������� ������� � �������� �����
	for (int i = 0; i < size_ship; i++)
	{
		if (x < 0 || y < 0 || x >= N || y >= N)
		{
			in_map = 0;
			break;
		}

		shipXY(x, y, dir);
	}
	return in_map;
}

bool setShip(int map[N][N], int x, int y, int dir, int size_ship)
{
	int temp_x = x;
	int temp_y = y;
	bool setting_is_possible = 1;
	//�������� ����������� ���������� �������
	for (int i = 0; i < size_ship; i++)
	{
		if (x < 0 || y < 0 || x >= N || y >= N)
		{
			setting_is_possible = 0;
			break;
		}

		if (map[x][y] >= 1)
		{
			setting_is_possible = 0;
			break;
		}
		if (y < N - 1)
		{
			if (map[x][y + 1] >= 1)
			{
				setting_is_possible = 0;
				break;
			}
		}
		if (y > 0)
		{
			if (map[x][y - 1] >= 1)
			{
				setting_is_possible = 0;
				break;
			}
		}
		if (x < N - 1)
		{
			if (map[x + 1][y] >= 1)
			{
				setting_is_possible = 0;
				break;
			}
		}
		if (x < N - 1 && y < N - 1)
		{
			if (map[x + 1][y + 1] >= 1)
			{
				setting_is_possible = 0;
				break;
			}
		}
		if (x < N - 1 && y > 0)
		{
			if (map[x + 1][y - 1] >= 1)
			{
				setting_is_possible = 0;
				break;
			}
		}
		if (x > 0)
		{
			if (map[x - 1][y] >= 1)
			{
				setting_is_possible = 0;
				break;
			}
		}
		if (x > 0 && y < N - 1)
		{
			if (map[x - 1][y + 1] >= 1)
			{
				setting_is_possible = 0;
				break;
			}
		}
		if (x > 0 && y > 0)
		{
			if (map[x - 1][y - 1] >= 1)
			{
				setting_is_possible = 0;
				break;
			}
		}

		shipXY(x, y, dir);
	}

	//���� ���� ����������� ��������� �������, ������
	if (setting_is_possible == 1)
	{
		x = temp_x;
		y = temp_y;

		for (int i = 0; i < size_ship; i++)
		{
			map[x][y] = ships_id;

			shipXY(x, y, dir);
		}
		//if (ships_id < N)
		//{
		//	_ships[ships_id] = size_ship;
		//}
		//_ships[ships_id] = size_ship;
		ships_id++;
	}
	return setting_is_possible;
}

void mapShow(int map[N][N], int x_pos, int y_pos, bool flag = false)
{
	::cout << HEADER <<  endl;
	for (int i = 0; i < N; i++)
	{
		if (flag)
		{
			cursorMove(x_pos, ++y_pos);
		}
		::cout << i;
		for (int j = 0; j < N; j++)
		{
			if (flag)
			{
				if (map[j][i] == -1)
				{
					::cout << MISS;
				}
				else if (map[j][i] == -2)
				{
					::cout << HIT;
					//::cout << map[j][i];
				}
				//else if (map[j][i] >= 1)
				//{
				//	::cout << map[j][i];
				//}
				else
				{
					::cout << SINGLE_FIELD;
				}
			}
			else
			{
				if (map[j][i] == 0)
				{
					::cout << SINGLE_FIELD;
				}
				else if (map[j][i] >= 1)
				{
					::cout << DECK;
				}
				else if (map[j][i] == -1)
				{
					::cout << MISS;
				}
				else if (map[j][i] == -2)
				{
					::cout << HIT;
				}
			}
		}
		::cout << endl;
	}
	::cout << endl;
}

void setManualShips(int map[N][N], int dir, int x, int y, int size_ship, int ships[N], int y_pos)
{
	int button;
	int i = 0;
	while (i < N)
	{
		mapShow(map, x_pos, y_pos);
		shipShow(x, y, dir, size_ship);

		int temp_x = x;
		int temp_y = y;
		int temp_dir = dir;

		button = _getch();

		//�������� ���������� ��� ����������
		switch (button)
		{
		case RIGTH://d ������
			x++;
			break;
		case DOWN://s ����
			y++;
			break;
		case LEFT://a �����
			x--;
			break;
		case UP://w �����
			y--;
			break;
		case ROTATION://r �������
			dir = !dir;
			break;
		case ENTER://enter ��������� �������
			if (setShip(map, x, y, dir, size_ship))
			{
				x = 0;
				y = 0;
				dir = 0;
				i++;
				size_ship = ships[i];
				break;
			}
			break;
		}
		if (!shipInMap(x, y, dir, size_ship))
		{
			x = temp_x;
			y = temp_y;
			dir = temp_dir;
		}
		::system("cls");
	}
}

void setRandomShips(int map[N][N], int size_ship, int ship_id)
{
	int x, y;
	int dir = 0;
	int count_ship = 0;

	while (count_ship < 1)
	{
		//��������� �������
		x = rand() % N;
		y = rand() % N;

		int temp_x = x;
		int temp_y = y;

		//��������� �����������
		dir = rand() % 4;

		bool setting_is_possible = 1;
		//�������� ����������� ���������� �������
		for (int i = 0; i < size_ship; i++)
		{
			if (x < 0 || y < 0 || x >= N || y >= N)
			{
				setting_is_possible = 0;
				break;
			}

			if (map[x][y] >= 1 || map[x][y + 1] >= 1 || map[x][y - 1] >= 1 ||
				map[x + 1][y] >= 1 || map[x + 1][y + 1] >= 1 || map[x + 1][y - 1] >= 1 ||
				map[x - 1][y] >= 1 || map[x - 1][y + 1] >= 1 || map[x - 1][y - 1] >= 1)
			{
				setting_is_possible = 0;
				break;
			}

			shipXY(x, y, dir);
		}

		//���� ���� ����������� ��������� �������, ������
		if (setting_is_possible == 1)
		{
			x = temp_x;
			y = temp_y;

			for (int i = 0; i < size_ship; i++)
			{
				map[x][y] = ship_id;

				shipXY(x, y, dir);
			}
			count_ship++;
		}
	}
}

void resultShooting(int map[N][N], int result_shooting[N], int x, int y, bool &hit)
{
	if (map[y][x] == 0)
	{
		map[y][x] = -1; // ������
		hit = false;
		Sleep(500);
		::cout << "������";
	}
	else if (map[y][x] >= 1)
	{
		int result = map[y][x] - 1;
		map[y][x] = -2; // ���������
		hit = true;

		result_shooting[result]--;
		if (result_shooting[result] == 0)
		{
			Sleep(500);
			::cout << "����";
		}
		else
		{
			Sleep(500);
			::cout << "�����";
		}
	}
	else
	{
		Sleep(500);
		::cout << "�� ���� ���������� ��� ��������!";
		hit = true;
	}
}

void strategyBot_1(int map[N][N], int &x, int &y)
{
	int temp_x = x;
	int temp_y = y;
	if (map[temp_y][temp_x] >= 0)
	{
		x = temp_x;
		y = temp_y;
	}
	else
	{
		do
		{
			++temp_x;
			++temp_y;
			if (temp_x == N || temp_y == N)
			{
				temp_x = 0;
				temp_y = N - 1;
				if (map[temp_y][temp_x] >= 0)
				{
					break;
				}
				do
				{
					++temp_x;
					--temp_y;
					if (temp_x == N || temp_y < 0)
					{
						do
						{
							temp_x = rand() % N;
							temp_y = rand() % N;
						} while (map[temp_y][temp_x] < 0);
					}
				} while (map[temp_y][temp_x] < 0);
			}
		} while (map[temp_y][temp_x] < 0);
		x = temp_x;
		y = temp_y;
	}
}

void strategyBot_2(int map[N][N], int &x, int &y)
{
	int temp_x = x;
	int temp_y = y;
	if (map[temp_y][temp_x] >= 0)
	{
		x = temp_x;
		y = temp_y;
	}
	else
	{
		do
		{
			++temp_x;
			if (temp_x == N || temp_y == N)
			{
				temp_x = N / 2 - 1;
				temp_y = N - 1;
				if (map[temp_y][temp_x] >= 0)
				{
					break;
				}
				do
				{
					--temp_y;
					if (temp_x == N || temp_y < 0)
					{
						do
						{
							temp_x = rand() % N;
							temp_y = rand() % N;
						} while (map[temp_y][temp_x] < 0);
					}
				} while (map[temp_y][temp_x] < 0);
			}
		} while (map[temp_y][temp_x] < 0);
		x = temp_x;
		y = temp_y;
	}
}

void shooting(int map[N][N], int result_shooting[N], string str, bool &hit, bool &computer_game_mode,  bool shooting_bot = true)
{
	if (shooting_bot)
	{
		int x;
		int y;
		if (computer_game_mode)
		{
			do
			{
				x = rand() % N;
				y = rand() % N;
			} while (map[y][x] < 0);

			resultShooting(map, result_shooting, x, y, hit);
			return;
		}
		else
		{
			bool strategy = rand() % 2;
			if (strategy)
			{
				x = 0;
				y = 0;
				strategyBot_1(map, x, y);
				resultShooting(map, result_shooting, x, y, hit);
				return;
			}
			else
			{
				x = 0;
				y = N / 2 - 1;
				strategyBot_2(map, x, y);
				resultShooting(map, result_shooting, x, y, hit);
				return;
			}
		}
	}
	else
	{
		string str_error = "������ �����. ��������� �������!\n";
		char c = ' ';
		int x = -100;
		int y = -100;
		str.erase(remove(str.begin(), str.end(), c), str.end());
		if (str.length() != 2)
		{
			std::cout << str_error;
			Sleep(1000);
			return;
		}

		int temp_y = 0;
		for (char i = 'a'; i <= 'j'; i++, temp_y++)
		{
			if (str[0] == i)
			{
				y = temp_y;
				break;
			}
		}

		if (y == -10)
		{
			temp_y = 0;
			for (char i = 'A'; i <= 'J'; i++, temp_y++)
			{
				if (str[0] == i)
				{
					y = temp_y;
					break;
				}
			}
		}

		int temp_x = 0;
		for (char i = '0'; i <= '9'; i++, temp_x++)
		{
			if (str[1] == i)
			{
				x = temp_x;
				break;
			}
		}

		if (x == -100 || y == -100)
		{
			std::cout << str_error;
			Sleep(1000);
			return;
		}
		else
		{
			resultShooting(map, result_shooting, x, y, hit);
		}
	}
}

bool gameOver(int result_shuting[N])
{
	for (int i = 0; i < N; i++)
	{
		if (result_shuting[i] > 0)
		{
			return true;
		}
	}
	return false;
}

int main()
{
	bool game_mode{ true };          // ������ ����: ������� - ���������(true), ��������� - ���������(false)
	bool placement_of_ships{ true }; // ����������� ��������: �������(true), ��������� ����������� �� ������(false)
	bool computer_game_mode{ true }; // ����� ���� ����������: ��������� �������(true), ���������������� ����(false)

	srand((unsigned int)time(NULL));
	SetConsoleOutputCP(1251);
	gameMode(game_mode);
	placementOfShips(placement_of_ships);
	computerGameMode(computer_game_mode);
	settingGameModes(game_mode, placement_of_ships, computer_game_mode);

	int map_1[N][N]{};
	int map_2[N][N]{};
	int ships[N]{ 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
	int dir{};
	int y_pos{};
	int x{}, y{};
	int size_ship{ ships[0] };
	bool hit{ true };

	if (placement_of_ships)
	{
		setManualShips(map_1, dir, x, y, size_ship, ships, y_pos);
		ships_id = 1;
		for (int i = 0; i < N; i++)
		{
			setRandomShips(map_2, ships[i], ships_id + i);
		}
	}
	else
	{
		for (int i = 0; i < N; i++)
		{
			setRandomShips(map_1, ships[i], ships_id + i);
		}
		ships_id = 1;
		for (int i = 0; i < N; i++)
		{
			setRandomShips(map_2, ships[i], ships_id + i);
		}
	}

	string coordinate_entry_line;
	int result_shooting_1[N]{ 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
	int result_shooting_2[N]{ 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
	bool game_over = true;

	while (game_over)
	{
		if (game_mode)
		{
			do
			{
				mapShow(map_1, x_pos, y_pos);
				cursorMove(x_pos, y_pos);
				mapShow(map_2, x_pos, y_pos, true);
				::cout << ">>>";
				getline(cin, coordinate_entry_line);
				shooting(map_2, result_shooting_2, coordinate_entry_line, hit, computer_game_mode, false);
				game_over = gameOver(result_shooting_2);
				if (!game_over)
				{
					break;
				}
				Sleep(1000);
				::system("cls");
			} while (hit);
			if (!game_over)
			{
				break;
			}
			do
			{
				mapShow(map_1, x_pos, y_pos);
				cursorMove(x_pos, y_pos);
				mapShow(map_2, x_pos, y_pos, true);
				::cout << ">>>";
				::cout << endl;
				shooting(map_1, result_shooting_1, coordinate_entry_line, hit, computer_game_mode);
				game_over = gameOver(result_shooting_1);
				if (!game_over)
				{
					break;
				}
				::cout << endl;
				Sleep(1000);
				::system("cls");
			} while (hit);
			if (!game_over)
			{
				break;
			}
		}
		else
		{
			do
			{
				mapShow(map_1, x_pos, y_pos);
				cursorMove(x_pos, y_pos);
				mapShow(map_2, x_pos, y_pos, true);
				Sleep(1000);
				shooting(map_2, result_shooting_2, coordinate_entry_line, hit, computer_game_mode);
				game_over = gameOver(result_shooting_2);
				if (!game_over)
				{
					break;
				}
				Sleep(1000);
				::system("cls");
			} while (hit);
			if (!game_over)
			{
				break;
			}
			do
			{
				mapShow(map_1, x_pos, y_pos);
				cursorMove(x_pos, y_pos);
				mapShow(map_2, x_pos, y_pos, true);
				Sleep(1000);
				shooting(map_1, result_shooting_1, coordinate_entry_line, hit, computer_game_mode);
				game_over = gameOver(result_shooting_1);
				if (!game_over)
				{
					break;
				}
				Sleep(1000);
				::system("cls");
			} while (hit);
			if (!game_over)
			{
				break;
			}
		}
	}

	::system("cls");
	mapShow(map_1, x_pos, y_pos);
	cursorMove(x_pos, y_pos);
	mapShow(map_2, x_pos, y_pos, true);

	return 0;
}