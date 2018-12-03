#include<iostream>
#include<ncurses.h>

using namespace std;


void debugPrint(char *str){
    static int i;
    mvprintw(i++,10,str);
    refresh();
}
void normalPrint(char *str){
  static int j;
  mvprintw(j++,0,str);
  refresh();
}
int main(){
    initscr();
    normalPrint("blah");
    normalPrint("blah");

    debugPrint("Alpha");
    debugPrint("Bravo");
    normalPrint("blah");

    debugPrint("Charlie");

    getch();
    endwin();
}
