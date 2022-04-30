#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<string>
#include<fstream>
#include<iomanip>

using namespace std;

const int N = 10;
const int X_POS = 13;
const char SPACE = ' ';
const char E_BUTTON = 'E';
const char P_BUTTON = 'P';
const char S_BUTTON = 'S';
const string PATH_MAP = "map.txt";
const string PATH_SETTING = "setting.txt";
const string PATH_DATA = "data.txt";
const string DECK = "D";
const string HIT = "X";
const string MISS = "@";
const string HEADER = " ABCDEFGHIJ";
const string SINGLE_FIELD = ":";
const string INPUT_LINE = ">>>";

enum Button
{
	RIGTH = 100,
	LEFT = 97,
	UP = 119,
	DOWN = 115,
	ROTATION = 114,
	ENTER = 13
};

enum ConsoleColor
{
	BLACK = 0,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	LIGHT_GRAY = 7,
	DARK_GRAY = 8,
	LIGHT_RED = 12,
	YELLOW = 14,
	WHITE = 15
};

enum SaveExitMenu
{
	EXIT = 1,
	PAUSE,
	SAVE_AND_EXIT,
};

struct Hit
{
	int x;
	int y;
	bool key = false;
};

void clearKeyboardBuffer()
{
	while (_kbhit())
	{
		_getch();
	}
}

void errorInput()
{
	cout << "\n\nОшибка ввода. Попробуйте еще раз\n\n";
	Sleep(1000);
	system("cls");
}

void setColor(unsigned foreground, unsigned background)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((background << 4) | foreground));
}

void startMessage(ofstream &fout)
{
	bool exit_cicle = true;
	char ch;
	while (exit_cicle)
	{
		cout << "1 - продолжить\n";
		cout << "2 - начать новую игру\n";
		cout << "\n>>>";

		ch = _getch();
		switch (ch)
		{
		case '1':
			exit_cicle = false;
			clearKeyboardBuffer();
			break;
		case '2':
			exit_cicle = false;
			fout.open(PATH_MAP);
			fout.clear();
			fout.close();
			clearKeyboardBuffer();
			break;
		default:
			errorInput();
			break;
		}
	}
	clearKeyboardBuffer();
	system("cls");
}

void saveExitMessage()
{
	cout << endl;
	cout << "Ctrl + P - остановка программы\n";
	cout << "Ctrl + E - выход из программы\n";
	cout << "Ctrl + S - запись и выход из программы\n";
}

void registerHotKeyInGame()
{
	RegisterHotKey(0, EXIT, MOD_CONTROL, E_BUTTON);
	RegisterHotKey(0, PAUSE, MOD_CONTROL, P_BUTTON);
	RegisterHotKey(0, SAVE_AND_EXIT, MOD_CONTROL, S_BUTTON);
}

void unregisterHotKeyInGame()
{
	UnregisterHotKey(0, EXIT);
	UnregisterHotKey(0, PAUSE);
	UnregisterHotKey(0, SAVE_AND_EXIT);
}

void _msg(MSG &msg)
{
	while (PeekMessage(&msg, 0, 0, 0, 0x0001))
	{
		switch (msg.message)
		{
		case WM_HOTKEY:
			if (msg.wParam == EXIT)
			{
				setColor(WHITE, BLACK);
				cout << "Завершение работы программы...\n";
				Sleep(3000);
				system("cls");
				ofstream fout;
				fout.open(PATH_MAP, ios_base::out);
				fout.clear();
				fout.close();
				_exit(0);
			}
			else if (msg.wParam == PAUSE)
			{
				setColor(WHITE, BLACK);
				system("pause");
				setColor(CYAN, BLACK);
			}
			else if (msg.wParam == SAVE_AND_EXIT)
			{
				setColor(WHITE, BLACK);
				cout << "Сохранение данных и завершение работы программы...\n";
				Sleep(3000);
				system("cls");
				_exit(0);
			}
		}
	}
}

void gameMode(bool &game_mode)
{
	bool exit_cicle = true;
	char ch;
	string str;
	while (exit_cicle)
	{
		cout << "Режим игры:\n\n";
		cout << "1 - Человек - компьютер\n";
		cout << "2 - Компьютер - компьютер\n";
		cout << "\n>>>";

		ch = _getch();
		switch (ch)
		{
		case '1':
			str = "человек - компьютер\n";
			exit_cicle = false;
			game_mode = true;
			clearKeyboardBuffer();
			break;
		case '2':
			str = "компьютер - компьютер\n";
			exit_cicle = false;
			game_mode = false;
			clearKeyboardBuffer();
			break;
		default:
			errorInput();
			break;
		}
	}
	clearKeyboardBuffer();
	system("cls");
}

void placementOfShips(bool &placement_of_ships)
{
	string str;
	char ch;
	bool exit_cicle = true;
	while (exit_cicle)
	{
		cout << "Расстановка кораблей:\n\n";
		cout << "1 - Вручную\n";
		cout << "2 - Компьютер расставляет за игрока\n";
		cout << "\n>>>";

		ch = _getch();
		switch (ch)
		{
		case '1':
			str = "вручную\n";
			exit_cicle = false;
			placement_of_ships = true;
			clearKeyboardBuffer();
			break;
		case '2':
			str = "компьютер расставляет за игрока\n";
			exit_cicle = false;
			placement_of_ships = false;
			clearKeyboardBuffer();
			break;
		default:
			errorInput();
			break;
		}
	}
	clearKeyboardBuffer();
	system("cls");
}

void computerGameMode(bool &computer_game_mode)
{
	string str;
	bool exit_cicle = true;
	char ch;
	while (exit_cicle)
	{
		cout << "Режим игры компьютера:\n\n";
		cout << "1 - Случайный выстрел\n";
		cout << "2 - Интеллектуальная игра\n";
		cout << "\n>>>";

		ch = _getch();
		switch (ch)
		{
		case '1':
			str = "случайный выстрел\n";
			exit_cicle = false;
			computer_game_mode = true;
			clearKeyboardBuffer();
			break;
		case '2':
			str = "интеллектуальная игра\n";
			exit_cicle = false;
			computer_game_mode = false;
			clearKeyboardBuffer();
			break;
		default:
			errorInput();
			break;
		}
	}
	clearKeyboardBuffer();
	system("cls");
}

void settingGameModes(bool &game_mode, bool &placement_of_ships, bool &computer_game_mode)
{
	string str_1, str_2, str_3;
	if (game_mode)
	{
		str_1 = "человек - компьютер\n";
	}
	else
	{
		str_1 = "компьютер - компьютер\n";
	}
	cout << "Режим игры: " << str_1 << endl;
	if (placement_of_ships)
	{
		str_2 = "вручную\n";
	}
	else
	{
		str_2 = "компьютер расставляет за игрока\n";
	}
	cout << "Расстановка кораблей: " << str_2 << endl;
	if (computer_game_mode)
	{
		str_3 = "случайный выстрел\n";
	}
	else
	{
		str_3 = "интеллектуальная игра\n";
	}
	cout << "Режим игры компьютера: " << str_3 << endl;
	cout << "\t\tЗагрузка игры... " << endl;

	Sleep(5000);
	system("cls");
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
		cout << DECK;
		shipXY(x, y, dir);
	}
}

bool shipInMap(int x, int y, int dir, int size_ship)
{
	bool in_map = 1;
	//проверка нахождения корабля в пределах карты
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

bool setShip(int map[N][N], int x, int y, int dir, int size_ship, int &ships_id)
{
	int temp_x = x;
	int temp_y = y;
	bool setting_is_possible = 1;

	//проверка возможности постановки корабля
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

	//если есть возможность поставить корабль, ставим
	if (setting_is_possible == 1)
	{
		x = temp_x;
		y = temp_y;

		for (int i = 0; i < size_ship; i++)
		{
			map[x][y] = ships_id;

			shipXY(x, y, dir);
		}
		ships_id++;
	}
	return setting_is_possible;
}

void mapShow(int map[N][N], int x_pos, int y_pos, bool all_decks_show, bool flag = false)
{
	setColor(WHITE, BLACK);
	cout << HEADER << endl;
	setColor(DARK_GRAY, BLACK);
	for (int i = 0; i < N; i++)
	{
		if (flag)
		{
			cursorMove(X_POS, ++y_pos);
		}
		setColor(WHITE, BLACK);
		cout << i;
		setColor(DARK_GRAY, BLACK);
		for (int j = 0; j < N; j++)
		{
			if (flag)
			{
				if (map[j][i] == -1)
				{
					setColor(WHITE, BLACK);
					cout << MISS;
					setColor(DARK_GRAY, BLACK);
				}
				else if (map[j][i] == -2)
				{
					setColor(RED, BLACK);
					cout << HIT;
					setColor(DARK_GRAY, BLACK);
				}
				else if (map[j][i] >= 1 && all_decks_show == true)
				{
					setColor(GREEN, BLACK);
					cout << DECK;
					setColor(DARK_GRAY, BLACK);
				}
				else
				{
					cout << SINGLE_FIELD;
				}
			}
			else
			{
				if (map[j][i] == 0)
				{
					cout << SINGLE_FIELD;
				}
				else if (map[j][i] >= 1)
				{
					setColor(GREEN, BLACK);
					cout << DECK;
					setColor(DARK_GRAY, BLACK);
				}
				else if (map[j][i] == -1)
				{
					setColor(WHITE, BLACK);
					cout << MISS;
					setColor(DARK_GRAY, BLACK);
				}
				else if (map[j][i] == -2)
				{
					setColor(RED, BLACK);
					cout << HIT;
					setColor(DARK_GRAY, BLACK);
				}
			}
		}
		cout << endl;
	}
	saveExitMessage();
	setColor(YELLOW, BLACK);
	cout << endl << INPUT_LINE;
	setColor(CYAN, BLACK);
}

void setManualShips(int map[N][N], int dir, int x, int y, int size_ship, int ships[N], int y_pos, int &ships_id, bool all_decks_show)
{
	int button;
	int i = 0;
	while (i < N)
	{
		mapShow(map, X_POS, y_pos, all_decks_show);
		shipShow(x, y, dir, size_ship);

		int temp_x = x;
		int temp_y = y;
		int temp_dir = dir;

		button = _getch();

		//изменить координаты или напрвление
		switch (button)
		{
		case RIGTH://d вправо
			x++;
			break;
		case DOWN://s вниз
			y++;
			break;
		case LEFT://a влево
			x--;
			break;
		case UP://w вверх
			y--;
			break;
		case ROTATION://r поворот
			dir = !dir;
			break;
		case ENTER://enter установка корабля
			if (setShip(map, x, y, dir, size_ship, ships_id))
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
		system("cls");
	}
}

void setRandomShips(int map[N][N], int size_ship, int ship_id)
{
	int x, y;
	int dir = 0;
	int count_ship = 0;

	while (count_ship < 1)
	{
		//первичная позиция
		x = rand() % N;
		y = rand() % N;

		int temp_x = x;
		int temp_y = y;

		//генерация направления
		dir = rand() % 4;

		bool setting_is_possible = 1;
		//проверка возможности постановки корабля
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

		//если есть возможность поставить корабль, ставим
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

void setMissField(int map[N][N], int &length_ship, int &x, int &y, bool direction_ship)
{
	if (direction_ship)
	{
		for (int i = -1; i <= length_ship; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (y + i < 0 || x + j < 0 || y + i >= N || x + j >= N)
				{
					continue;
				}
				else if (y + i != y || x + j != x)
				{
					if (map[y + i][x + j] != -2)
					{
						map[y + i][x + j] = -1;
					}
				}
			}
		}
	}
	else
	{
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j <= length_ship; j++)
			{
				if (y + i < 0 || x + j < 0 || y + i >= N || x + j >= N)
				{
					continue;
				}
				else if (y + i != y || x + j != x)
				{
					if (map[y + i][x + j] != -2)
					{
						map[y + i][x + j] = -1;
					}
				}
			}
		}
	}
}

bool directionShip(int map[N][N], int &x, int &y)
{
	int temp_x = x;
	int temp_y = y;
	int count = 0;
	bool direction = true;

	do
	{
		temp_x--;
		if (map[y][temp_x] == -2 && temp_x >= 0)
		{
			count++;
		}
	} while (map[y][temp_x] == -2 && temp_x >= 0);

	if (count > 0)
	{
		x = ++temp_x;
		direction = false;
	}
	else
	{
		temp_x = x;
		if (map[y][++temp_x] == -2 && temp_x < N)
		{
			direction = false;
		}
	}

	if (direction)
	{
		count = 0;
		do
		{
			temp_y--;
			if (map[temp_y][x] == -2 && temp_y >= 0)
			{
				count++;
			}
		} while (map[temp_y][x] == -2 && temp_y >= 0);

		if (count > 0)
		{
			y = ++temp_y;
		}
	}

	return direction;
}

void fillingFieldsAroundShip(int map[N][N], int &id, int &x, int &y)
{
	int length_ship = 1;
	bool direction_ship = true; // горизонтальное расположение корабля
	switch (id)
	{
	case 1:
		length_ship = 4;
		direction_ship = directionShip(map, x, y);
		setMissField(map, length_ship, x, y, direction_ship);
		break;
	case 2:
	case 3:
		length_ship = 3;
		direction_ship = directionShip(map, x, y);;
		setMissField(map, length_ship, x, y, direction_ship);
		break;
	case 4:
	case 5:
	case 6:
		length_ship = 2;
		direction_ship = directionShip(map, x, y);;
		setMissField(map, length_ship, x, y, direction_ship);
		break;
	case 7:
	case 8:
	case 9:
	case 10:
		setMissField(map, length_ship, x, y, direction_ship);
		break;
	}
}

void resultShooting(int map[N][N], int result_shooting[N], Hit &h, int &x, int &y, bool &hit, bool &mode_shooting)
{
	if (map[y][x] == 0)
	{
		map[y][x] = -1; // промах
		hit = false;
		Sleep(500);
		cout << "Промах";
	}
	else if (map[y][x] >= 1)
	{
		int id = map[y][x];
		int result = map[y][x] - 1;
		map[y][x] = -2; // попадание
		hit = true;

		result_shooting[result]--;
		if (result_shooting[result] == 0)
		{
			mode_shooting = false;
			h.key = false;
			Sleep(500);
			cout << "Убит";
			fillingFieldsAroundShip(map, id, x, y);
		}
		else
		{
			mode_shooting = true;
			h.x = x;
			h.y = y;
			Sleep(500);
			cout << "Ранен";
		}
	}
	else
	{
		Sleep(500);
		cout << "По этой координате уже стреляли!";
		hit = true;
	}
}

void strategyBot(int map[N][N], Hit &h, int &x, int &y)
{
	int temp_x = x;
	int temp_y = y;

	if (h.key == false)
	{
		do
		{
			temp_x--;
		} while (map[y][temp_x] == -2 && temp_x >= 0);

		if (map[y][temp_x] >= 0 && temp_x >= 0)
		{
			x = temp_x;
			return;
		}
		else
		{
			do
			{
				temp_x++;
			} while (map[y][temp_x] == -2 && temp_x < N);

			if (map[y][temp_x] >= 0 && temp_x < N)
			{
				x = temp_x;
				return;
			}
		}
	}

	h.key = true;
	if (h.key == true)
	{
		do
		{
			temp_y--;
		} while (map[temp_y][x] == -2 && temp_y >= 0);

		if (map[temp_y][x] >= 0 && temp_y >= 0)
		{
			y = temp_y;
			return;
		}
		else
		{
			do
			{
				temp_y++;
			} while (map[temp_y][x] == -2 && temp_y < N);

			if (map[temp_y][x] >= 0 && temp_y < N)
			{
				y = temp_y;
				return;
			}
		}
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
		return;
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
		return;
	}
	else
	{
		do
		{
			temp_x += N / 2.5;
			if (temp_x >= N)
			{
				temp_x -= (N - 1);
				if (temp_y < N - 1)
				{
					temp_y++;
				}
				else
				{
					do
					{
						temp_x = rand() % N;
						temp_y = rand() % N;
					} while (map[temp_y][temp_x] < 0);
				}
			}
		} while (map[temp_y][temp_x] < 0);
		x = temp_x;
		y = temp_y;
	}
}

void shooting(int map[N][N], int result_shooting[N], Hit &h, MSG &msg, bool &hit, bool &computer_game_mode, bool &mode_shooting, bool shooting_bot = true)
{
	_msg(msg);
	if (shooting_bot)
	{
		int x;
		int y;
		if (mode_shooting)
		{
			x = h.x;
			y = h.y;
			strategyBot(map, h, x, y);
			cout << static_cast<char>(y + 97) << x << endl;
			resultShooting(map, result_shooting, h, x, y, hit, mode_shooting);
			return;
		}
		else if (computer_game_mode)
		{
			do
			{
				x = rand() % N;
				y = rand() % N;
			} while (map[y][x] < 0);
			cout << static_cast<char>(y + 97) << x << endl;
			resultShooting(map, result_shooting, h, x, y, hit, mode_shooting);
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
				cout << static_cast<char>(y + 97) << x << endl;
				resultShooting(map, result_shooting, h, x, y, hit, mode_shooting);
				return;
			}
			else
			{
				x = N / 3;
				y = 0;
				strategyBot_2(map, x, y);
				cout << static_cast<char>(y + 97) << x << endl;
				resultShooting(map, result_shooting, h, x, y, hit, mode_shooting);
				return;
			}
		}
	}
	else
	{
		string str_error = "Ошибка ввода. Повторите попытку!\n";
		string coordinate_entry_line;
		getline(cin, coordinate_entry_line);
		int x = -100;
		int y = -100;
		coordinate_entry_line.erase(remove(coordinate_entry_line.begin(), coordinate_entry_line.end(), SPACE), coordinate_entry_line.end());
		if (coordinate_entry_line.length() != 2)
		{
			cout << str_error;
			Sleep(1000);
			hit = true;
			return;
		}

		int temp_y = 0;
		for (char i = 'a'; i <= 'j'; i++, temp_y++)
		{
			if (coordinate_entry_line[0] == i)
			{
				y = temp_y;
				break;
			}
		}

		if (y == -100)
		{
			temp_y = 0;
			for (char i = 'A'; i <= 'J'; i++, temp_y++)
			{
				if (coordinate_entry_line[0] == i)
				{
					y = temp_y;
					break;
				}
			}
		}

		int temp_x = 0;
		for (char i = '0'; i <= '9'; i++, temp_x++)
		{
			if (coordinate_entry_line[1] == i)
			{
				x = temp_x;
				break;
			}
		}

		if (x == -100 || y == -100)
		{
			cout << str_error;
			Sleep(1000);
			hit = true;
			return;
		}
		else
		{
			resultShooting(map, result_shooting, h, x, y, hit, mode_shooting);
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

void saveInFileMap(int map_1[N][N], int map_2[N][N], ofstream &fout)
{
	fout.open(PATH_MAP, ios_base::out);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			fout << setw(2) << map_1[j][i] << " ";
		}
		fout << "\n";
	}

	fout << "\n";
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			fout << setw(2) << map_2[j][i] << " ";
		}
		fout << "\n";
	}
	fout.close();
}

void readFileMap(int map_1[N][N], int map_2[N][N], ifstream &fin)
{
	fin.open(PATH_MAP, ios_base::in);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			fin >> setw(2) >> map_1[j][i];
		}
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			fin >> setw(2) >> map_2[j][i];
		}
	}
	fin.close();
}

bool isEmptyFileMap(ifstream &fin)
{
	bool file_empty = false;
	long file_size;
	fin.open(PATH_MAP, ios_base::in);
	fin.seekg(0, ios_base::end);
	file_size = fin.tellg();
	if (file_size == 0)
	{
		file_empty = true;
	}
	fin.close();
	return file_empty;
}

void saveInFileSetting(bool &game_mode, bool &computer_game_mode, ofstream &fout)
{
	fout.open(PATH_SETTING, ios_base::out);
	fout << game_mode << computer_game_mode;
	fout.close();
}

void readFileSetting(bool &game_mode, bool &computer_game_mode, ifstream &fin)
{
	fin.open(PATH_SETTING, ios_base::in);
	fin >> game_mode >> computer_game_mode;
	fin.close();
}

void saveInFileData(Hit &h_1, Hit &h_2, int result_shooting_1[N], int result_shooting_2[N], bool &hit, bool &mode_shooting_1, bool &mode_shooting_2, int &move, ofstream &fout)
{
	fout.open(PATH_DATA, ios_base::out);
	fout << h_1.key << h_1.x << h_1.y << h_2.key << h_2.x << h_2.y << "\n";
	for (int i = 0; i < N; i++)
	{
		fout << result_shooting_1[i];
	}
	fout << "\n";
	for (int i = 0; i < N; i++)
	{
		fout << result_shooting_2[i];
	}
	fout << "\n";
	fout << hit << "\n";
	fout << mode_shooting_1 << mode_shooting_2 << "\n";
	fout << move;
	fout.close();
}

void readFileData(Hit &h_1, Hit &h_2, int result_shooting_1[N], int result_shooting_2[N], bool &hit, bool &mode_shooting_1, bool &mode_shooting_2, int &move, ifstream &fin)
{
	fin.open(PATH_DATA, ios_base::in);
	fin >> h_1.key >> h_1.x >> h_1.y >> h_2.key >> h_2.x >> h_2.y;
	for (int i = 0; i < N; i++)
	{
		fin >> result_shooting_1[i];
	}
	for (int i = 0; i < N; i++)
	{
		fin >> result_shooting_2[i];
	}
	fin >> hit;
	fin >> mode_shooting_1 >> mode_shooting_2;
	fin >> move;
	fin.close();
}

int main()
{
	ofstream fout;
	ifstream fin;

	bool game_mode{ true };          // режимы игры: человек - компьютер(true), компьютер - компьютер(false)
	bool placement_of_ships{ true }; // расстановка кораблей: вручную(true), компьютер расставляет за игрока(false)
	bool computer_game_mode{ true }; // режим игры компьютера: случайный выстрел(true), интеллектуальная игра(false)

	srand((unsigned int)time(NULL));
	SetConsoleOutputCP(1251);
	registerHotKeyInGame();

	int map_1[N][N]{};
	int map_2[N][N]{};
	int ships[N]{ 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
	int dir{};
	int y_pos{};
	int x{}, y{};
	int size_ship{ ships[0] };
	int ships_id{ 1 };
	bool all_decks_show{ false };

	MSG msg;
	Hit h_1{ 0, 0 };
	Hit h_2{ 0, 0 };
	string end_game;
	int result_shooting_1[N]{ 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
	int result_shooting_2[N]{ 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
	bool game_over{ true };
	bool hit{ true };
	bool mode_shooting_1{ false };
	bool mode_shooting_2{ false };
	int move{};
	bool _move{ false };

	if (!isEmptyFileMap(fin))
	{
		setColor(LIGHT_GRAY, BLACK);
		startMessage(fout);
	}

	if (isEmptyFileMap(fin))
	{
		setColor(LIGHT_GRAY, BLACK);
		gameMode(game_mode);
		placementOfShips(placement_of_ships);
		computerGameMode(computer_game_mode);
		settingGameModes(game_mode, placement_of_ships, computer_game_mode);
		saveInFileSetting(game_mode, computer_game_mode, fout);
		if (placement_of_ships)
		{
			setManualShips(map_1, dir, x, y, size_ship, ships, y_pos, ships_id, all_decks_show);
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
	}
	else
	{
		readFileSetting(game_mode, computer_game_mode, fin);
		readFileMap(map_1, map_2, fin);
		readFileData(h_1, h_2, result_shooting_1, result_shooting_2, hit, mode_shooting_1, mode_shooting_2, move, fin);
		_move = true;
	}

	while (game_over)
	{
		if (game_mode)
		{
			do
			{
				if (move == 2 && _move == true)
				{
					system("pause");
					break;
				}
				mapShow(map_1, X_POS, y_pos, all_decks_show);
				cursorMove(X_POS, y_pos);
				mapShow(map_2, X_POS, y_pos, all_decks_show, true);
				saveInFileMap(map_1, map_2, fout);
				shooting(map_2, result_shooting_2, h_2, msg, hit, computer_game_mode, mode_shooting_1, false);
				move = 2;
				_move = false;
				saveInFileMap(map_1, map_2, fout);
				saveInFileData(h_1, h_2, result_shooting_1, result_shooting_2, hit, mode_shooting_1, mode_shooting_2, move, fout);
				game_over = gameOver(result_shooting_2);
				if (!game_over)
				{
					break;
				}
				Sleep(1000);
				system("cls");
			} while (hit);
			if (!game_over)
			{
				end_game = { "Вы победили!" };
				break;
			}
			do
			{
				mapShow(map_1, X_POS, y_pos, all_decks_show);
				cursorMove(X_POS, y_pos);
				mapShow(map_2, X_POS, y_pos, all_decks_show, true);
				saveInFileMap(map_1, map_2, fout);
				shooting(map_1, result_shooting_1, h_1, msg, hit, computer_game_mode, mode_shooting_2);
				move = 1;
				_move = false;
				saveInFileMap(map_1, map_2, fout);
				saveInFileData(h_1, h_2, result_shooting_1, result_shooting_2, hit, mode_shooting_1, mode_shooting_2, move, fout);
				game_over = gameOver(result_shooting_1);
				if (!game_over)
				{
					break;
				}
				cout << endl;
				Sleep(1000);
				system("cls");
			} while (hit);
			if (!game_over)
			{
				end_game = { "Вы проиграли!" };
				break;
			}
		}
		else
		{
			do
			{
				if (move == 2 && _move == true)
				{
					break;
				}
				move = 1;
				_move = false;
				mapShow(map_1, X_POS, y_pos, all_decks_show);
				cursorMove(X_POS, y_pos);
				mapShow(map_2, X_POS, y_pos, all_decks_show, true);
				saveInFileMap(map_1, map_2, fout);
				shooting(map_2, result_shooting_2, h_2, msg, hit, computer_game_mode, mode_shooting_1);
				saveInFileMap(map_1, map_2, fout);
				saveInFileData(h_1, h_2, result_shooting_1, result_shooting_2, hit, mode_shooting_1, mode_shooting_2, move, fout);
				Sleep(1000);
				game_over = gameOver(result_shooting_2);
				if (!game_over)
				{
					break;
				}
				Sleep(1000);
				system("cls");
			} while (hit);
			if (!game_over)
			{
				end_game = { "Бот №1 победил!" };
				break;
			}
			do
			{
				move = 2;
				_move = false;
				mapShow(map_1, X_POS, y_pos, all_decks_show);
				cursorMove(X_POS, y_pos);
				mapShow(map_2, X_POS, y_pos, all_decks_show, true);
				saveInFileMap(map_1, map_2, fout);
				shooting(map_1, result_shooting_1, h_1, msg, hit, computer_game_mode, mode_shooting_2);
				saveInFileMap(map_1, map_2, fout);
				saveInFileData(h_1, h_2, result_shooting_1, result_shooting_2, hit, mode_shooting_1, mode_shooting_2, move, fout);
				Sleep(1000);
				game_over = gameOver(result_shooting_1);
				if (!game_over)
				{
					break;
				}
				Sleep(1000);
				system("cls");
			} while (hit);
			if (!game_over)
			{
				end_game = { "Бот №2 победил!" };
				break;
			}
		}
	}

	system("cls");
	all_decks_show = true;
	mapShow(map_1, X_POS, y_pos, all_decks_show);
	cursorMove(X_POS, y_pos);
	mapShow(map_2, X_POS, y_pos, all_decks_show, true);
	setColor(LIGHT_RED, BLACK);
	cout << end_game << endl;
	setColor(WHITE, BLACK);
	fout.open(PATH_MAP, ios_base::out);
	fout.clear();
	fout.close();
	unregisterHotKeyInGame();

	return 0;
}