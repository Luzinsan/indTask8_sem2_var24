/*
Массив записей с именем ZNAK, содержит сведения о знакомых:
{
Фамилия Имя;
Знак Зодиака;
День рождения (массив из трёх чисел)
}.
Написать программу, обеспечивающую ввод с клавиатуры данных в массив ZNAK
и вывод на экран информации о человеке, чья фамилия введена с клавиатуры.
Если такого нет, выдать на дисплей соответствующее сообщение.
*/


#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "stdbool.h"

typedef struct
{
	char z_surnameName[2][20];
	char z_zodiacSign[10];
	int z_birthday[3];
}ZNAK;



void getInt(int* choice, int a, int b)
{
	for (bool flag = scanf("%d", choice);
		flag == 0 || *choice < a || *choice > b;)
	{
		printf("\n\tОшибка! Попробуйте ещё раз.\n\t\t\t");
		if (flag == 0) scanf("%*s");
		flag = scanf("%d", choice);
	}
	getchar();
}

void printPerson(const ZNAK* person, const size_t size)
{
	printf("\n\t__________________________________________________"
		   "\n\t|%10s|%-10s|%12s|  %02d.%02d.%4d |"
		   "\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~",
		   person->z_surnameName[0], person->z_surnameName[1],
		   person->z_zodiacSign, person->z_birthday[0],
		   person->z_birthday[1], person->z_birthday[2]);
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	size_t size = 10;
	ZNAK Familiar[50];

	char s_name[10][2][10] = { {"Акира\0", "Куросава\0"}, {"Рико\0", "Такахаси\0"}, {"Акихиро\0", "Ямада\0"}, {"Иоширо\0", "Саито\0"}, {"Кайоши\0", "Накамура\0"},
							{"Нэо\0", "Иноэ\0"},   {"Масаши\0", "Мори\0"}, {"Сасаки\0", "Хайсэ\0"}, {"Рюк\0", "Обата\0"},    {"Юри\0", "Кацуки\0"} };
	char s_zodiacSign[10][8] = { "Овен\0","Козерог\0","Весы\0","Водолей\0","Лев\0","Дева\0","Рыбы\0","Стрелец\0","Рак\0","Телец\0" };
	int s_birthday[10][3] = { {5,4,1992},{6,1,2001},{11,10,1999},{8,2,2002},{23,7,1995},{13,9,1996},{4,3,2003},{2,4,1994},{16,7,2000},{15,5,1987} };

	for (int i = 0; i < size; i++)
	{
		strcpy((Familiar + i)->z_surnameName[0], s_name[i][0]);
		strcpy((Familiar + i)->z_surnameName[1], s_name[i][1]);
		strcpy((Familiar + i)->z_zodiacSign, s_zodiacSign[i]);
		for (int f = 0; f < 3; f++)
			(Familiar + i)->z_birthday[f] = s_birthday[i][f];
	}

	printf("\n\tВ базе хранятся имена и фамилии, знаки зодиака и дни рождения."
		"\n\t1) Вывести информацию о человеке по указанной фамилии;"
		"\n\t2) Просмотреть весь список;"
		"\n\t3) Добавить новую запись.");
		

	int choice = 0;
	while (1)
	{
		printf("\n\n\tВаш выбор №");

		getInt(&choice, 1, 3);

		while (1)
		{
			bool flag;
			switch (choice)
			{
			case 1://Вывести информацию о человеке по указанной фамилии
				printf("\n\tВведите фамилию: ");
				char name[20];
				gets(name);
				flag = true;

				for (int i = 0; i < size; i++)
					if (!strcmp((Familiar + i)->z_surnameName[1], name))
					{
						printf("\n\t__________________________________________________"
							   "\n\t|       Имя|Фамилия   |Знак зодиака|Дата рождения|");
						printPerson(Familiar + i, size);
						flag = false; break;
					}

				if (flag)
				{
					printf("\n\tДанной фамилии нет в базе данных.\n"
						"\n\t1) Попробовать ещё раз;"
						"\n\t2) Выбрать другую опцию."
					    "\n\tВаш выбор: ");
					getInt(&choice, 1, 2);
					if (choice == 1) continue;
					else break;
				}
				else break;

			case 2://просмотреть весь список
				printf("\n\t__________________________________________________"
					   "\n\t|       Имя|Фамилия   |Знак зодиака|Дата рождения|");
				for (int i = 0; i < size; i++)
					printPerson(Familiar+i, size);
					
				break;

			case 3://добавить новую запись в базу

				printf("\n\tФамилия: ");
				gets((Familiar + size)->z_surnameName[1]);
				printf("\n\tИмя: ");
				gets((Familiar + size)->z_surnameName[0]);
				printf("\n\tЗнак зодиака: ");
				gets((Familiar + size)->z_zodiacSign);

				printf("\n\tДень рождения: ");
				getInt(&((Familiar+size)->z_birthday[0]), 1,31);
				printf("\n\tМесяц рождения: ");
				getInt(&((Familiar + size)->z_birthday[1]), 1, 12);
				printf("\n\tГод рождения: ");
				getInt(&((Familiar + size)->z_birthday[2]), 1900, 2021);

				printf("\n\tЗапись успешно введена.");
				size++;
				break;

			default:
				printf("\n\tОшибка! Что-то пошло не так...");
			}
			break;
		}
		printf("\n\tЖелаете продолжить? (Да/Нет) ");
		char answer[256];
		while (gets(answer) && strcmp(answer, "Да") && strcmp(answer, "Нет"))
			printf("\n\tОшибка! Введите корректный ответ.\n\t\t\t");

		if (!strcmp(answer, "Да")) continue; else break;
	}

	getch();
	return 0;
}

