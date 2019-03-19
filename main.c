#define _XOPEN_SOURCE 600

#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <curses.h>
#include <time.h>

#define GETCH_TOUT	100


void init_ncurses();
void bool_toggle(bool *boolean);

int main(int argc, char **argv)
{
	int maxx, maxy, c, l_count;
	double x;
	long mody = 1, modx = 1;

	bool sine = TRUE;
	bool cosine = FALSE;
	bool tang = /*Kaworu*/ FALSE;
	bool rando = FALSE;


	srand(time(NULL));

	if (argc == 3)
	{
		mody = atol(argv[1]);
		modx = atol(argv[2]);
	}

	init_ncurses();

	maxx = getmaxx(stdscr);
	maxy = getmaxy(stdscr);

	while ((c = getch()) != 'q')
	{
		if (!rando)
			switch (c)
			{
				case KEY_UP:
					mody++;
					break;
				case KEY_DOWN:
					mody--;
					break;
				case KEY_RIGHT:
					modx++;
					break;
				case KEY_LEFT:
					if (modx > 1)
						modx--;
					break;
				case 's':
					bool_toggle(&(sine));
					break;
				case 'c':
					bool_toggle(&(cosine));
					break;
				case 't':
					bool_toggle(&(tang));
					break;
				case 'r':
					rando = TRUE;
					break;
			}
		else{}

		move(0, 0);
		clrtobot();

		for (x = 0; x < maxx; x+=.1)
		{
			if (sine)
				mvaddch(roundf(sin(x+l_count)*mody)+maxy/2, x*modx, 'x'|COLOR_PAIR(rand()%6));
			if (cosine)
				mvaddch(roundf(cos(x+l_count)*mody)+maxy/2, x*modx, 'x'|COLOR_PAIR(rand()%6));
			if (tang)
				mvaddch(roundf(tan(x+l_count)*mody)+maxy/2, x*modx, 'x'|COLOR_PAIR(rand()%6));
		}
		if (sine)
			mvprintw(maxy-1, 0, "sin(x)*%ld / %ld", modx, mody);
		if (cosine)
			mvprintw(maxy-2, 0, "cos(x)*%ld / %ld", modx, mody);
		if (tang)
			mvprintw(maxy-3, 0, "tan(x)*%ld / %ld", modx, mody);
		refresh();
		if (++l_count > maxx)
			l_count = 0;
	}

	endwin();

	return 0;
}


void bool_toggle(bool *boolean)
{
	if (*boolean)
		*boolean = FALSE;
	else
		*boolean = TRUE;

}

void init_ncurses()
{
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	nonl();
	raw();

	start_color();
	use_default_colors();
	init_pair(1,COLOR_CYAN,-1);
	init_pair(2,COLOR_MAGENTA,-1);
	init_pair(3,COLOR_BLUE,-1);
	init_pair(4,COLOR_YELLOW,-1);
	init_pair(5,COLOR_RED,-1);
	init_pair(6,COLOR_GREEN,-1);

	/* Sets the timeout for getch statements */
	timeout(GETCH_TOUT);
}

