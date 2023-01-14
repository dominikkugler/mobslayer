#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
int main() {
	srand(time(0));
	char move, menu, hero = '#', selector;
	int i, j, check, mapSize = 25, iteration_counter = 0;
	char mob = 'X';
	int x1, y1, if_mob = 0, kills = 0;
	int iteration_stop = 0;
	clock_t start, end;
	double elapsed = 0;
	
	char map[mapSize][mapSize];
	
	MENU:
	system("cls"); 
	printf("\n Witaj w grze");
	printf("\n o. Opcje");
	printf("\n m. Dostosuj rozmiar mapy");
	printf("\n s. start gry\n");
	
	do {
		menu = getch();
	} while (menu!='o' && menu!='m' && menu!='s');
	system("cls");
	
	switch(menu) {
		case 'o' : {
			printf("\n Wybierz postac (wpisz numer od 1 do 3 i potwierdz przyciskiem enter):");
			printf("\n 1. @");
			printf("\n 2. # (domyslna)");
			printf("\n 3. $");
			printf("\n 4. powrot do menu\n");
			do {
				selector = getch();
			} while (selector!='1' && selector!='2' && selector!='3' && selector!='4');
			switch(selector) {
				case '1': hero = '@'; break;
				case '2': hero = '#'; break;
				case '3': hero = '$'; break;
				case '4': goto MENU;
			}
			break;
		}
		case 'm' : {
			do {
				printf("\n Dostosuj rozmiar mapy (domyslnie 25)");
				printf("\n Obslugiwane rozmiary to od 10 do 25 : ");
				check = scanf("%d", &mapSize);
				if (check==0) {
					printf(" Blad formatu");
					fflush(stdin);
				} else if (mapSize < 10 || mapSize > 25) {
					printf(" Bledny zakres");
					fflush(stdin);
				}
			} while (check==0 || (mapSize < 10 || mapSize > 25));
			break;
		}
		case 's' : break;
	}
	
	printf("\n Wcisnij dowolny klawisz, aby rozpoczac gre");
	
	int x=1,y=1;
	kills = 0;
	if_mob = 0;
	iteration_counter = 0;
	iteration_stop = 0;
	
	start = clock();
	while(1) {
		
		if (iteration_counter%5 == 0 && if_mob==0) {
			do {
				x1 = rand() % (mapSize-1) + 1;
				y1 = rand() % (mapSize-1) + 1;
				if_mob = 1;
			} while (x1==x && y1==x);
		}
		
		do {
			move = getch();
		} while (move!='w' && move!='s' && move!='a' && move!='d' && move!='q' && move!='m' && move!='h');
		system("cls");
		
		printf("\n Move v1.0");
		printf("\n Co zrobic?");
		printf("\n w. krok do gory");
		printf("\n s. krok w dol");
		printf("\n a. krok w lewo");
		printf("\n d. krok w prawo");
		printf("\n q. wyjscie z gry");
		printf("\n m. powrot do menu\n\n");
		
		switch(move) {
			case 'w' : {
				if (y == 1 || (if_mob==1 && (y-y1 == 1 && x == x1))) {
					iteration_stop = 1;
					break;
				} 
				else {
					y--;
					break;
				}
			}
			case 's' : {
				if (y==(mapSize-1) || (if_mob==1 && (y1-y == 1 && x==x1))) {
					iteration_stop = 1;
					break;
				}
				else {
					y++;
					break;
				}
			}
			case 'a' : {
				if (x==1 || (if_mob==1 && (x-x1==1 && y==y1))) {
					iteration_stop = 1;
					break;
				}
				else {
					x--;
					break;
				}
			}
			case 'd' : {
				if(x==(mapSize-1) || (if_mob==1 && (x1-x==1 && y==y1))) {
					iteration_stop = 1;
					break;
				}
				else {
					x++; 
					break;
				}
			}
			case 'q' : {
				end = clock();
				system("cls");
				printf("\n Dziekuje za gre \n");
				printf(" Ilosc ruchow : %d", iteration_counter);
				printf("\n Ilosc zabitych mobow : %d", kills);
				elapsed = ((double)(end-start))/CLOCKS_PER_SEC;
				printf("\n Calkowity czas rozgrywki : %.1f", elapsed);
				return 0;
				break;
			}
			case 'm' : goto MENU; break;
			case 'h' : {
    			if (if_mob) {
      				if ((abs(y1-y)==1 && abs(x1-x)==0)||(abs(y1-y)==0 && abs(x1-x)==1)) {
        				if_mob = 0;
        				kills++;
					} else iteration_stop = 1; 
    			} else iteration_stop = 1;
    			break;
  			}
		}
		
		for(i=0;i<=mapSize;i++) {
			for(j=0;j<=mapSize;j++) {
				if (i==0 || j==0 || i==mapSize || j==mapSize) {
					if ((i==0 && j==0) || (i==0 && j==mapSize) || (i==mapSize && j==0) || (i==mapSize && j==mapSize)) map[i][j] = '+';
					else if ((i==0 || i==mapSize) && j!=0 && j!=mapSize) map[i][j] = '-';
					else if ((j==0 || j==mapSize) && i!=0 && i!=mapSize) map[i][j] = '|';
				}
				else {
					if (i==y && j==x) map[i][j] = hero;
					else if (i==y1 && j==x1 && if_mob == 1) map[i][j] = mob;
					else map[i][j] = ' ';
				}	
			}
		}
		
		for(i=0;i<=mapSize;i++) {
			printf("\n");
			for(j=0;j<=mapSize;j++) {
				printf("%c", map[i][j]);
			}
		}
		
		printf("\n Pokonane moby: %d", kills);
		
		if (iteration_stop == 0) {
			iteration_counter ++;
		} else if (iteration_stop == 1) {
			iteration_counter - 1;
			iteration_stop = 0; 
			continue;
		}
	
	}
	getchar();
	return 0;
}
