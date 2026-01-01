#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <signal.h>
void cleanup(int sig) {
    endwin();
    exit(0);
}

int main() {
  // setup ncurses
  signal(SIGINT, cleanup);
  initscr();
  noecho();
  cbreak();
  keypad(stdscr, 1);
  nodelay(stdscr, 1);
  curs_set(0);

  // create windows
  int h, w;
  getmaxyx(stdscr, h, w);
  WINDOW *game = newwin(h, 2*w/3, 0, 0);
  WINDOW *ui = newwin(h, w/3, 0, 2*w/3);

  int x = 0;
  int y = 0;

  while (1) {
    // refresh windows
    wrefresh(game);
    wrefresh(ui);

    // box windows
    box(game, 0, 0);
    box(ui, 0, 0);


    mvwaddch(game,y,2*x,'#');

    int ch = getch();
    if (ch == 27) break;    // escape key
    if (ch == KEY_UP) y--;
    if (ch == KEY_DOWN) y++;
    if (ch == KEY_LEFT) x--;
    if (ch == KEY_RIGHT) x++;
  }

  endwin();

  return 0;
}