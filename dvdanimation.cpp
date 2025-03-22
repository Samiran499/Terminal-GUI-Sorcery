#include <ncurses.h>
#include <cstdlib>
#include <unistd.h>
#include <ctime>

struct dvd
{
    int x, y, dx = 2, dy = 1;
    const char fig[10][48] = {
        "      @@@@@@@@@@@@@@@@       @@@@@@@@@@@       ",
        "     @@@@@@@@@@@@@@@@@     @@@@@@@@@@@@@@@@@   ",
        "     @@@@     @@@@@@@@@   @@@@ @@@@     @@@@@  ",
        "     @@@@     @@@@@@@@@@@@@@@  @@@@     @@@@@  ",
        "    @@@@    @@@@@   @@@@@@@   @@@@    @@@@@    ",
        "    @@@@@@@@@@@      @@@@     @@@@@@@@@@@      ",
        "                     @@@                       ",
        "              @@@@@@@@@@@@@@@@@                ",
        "   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@     ",
        "   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@      "
    };

};

int main()
{
    initscr();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);

    dvd myDvd;
    
    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);

    myDvd.x = 0;
    myDvd.y = 0;

    while(true)
    {
        clear();
        for(int i = 0; i < 10; i++)
        {
            mvprintw(myDvd.y+i, myDvd.x, "%s", myDvd.fig[i]);
        }

        refresh();

        myDvd.x += myDvd.dx;
        myDvd.y += myDvd.dy;

        if(myDvd.x <= 0 || myDvd.x >= max_x - 48) myDvd.dx *= -1;
        if(myDvd.y <= 0 || myDvd.y >= max_y - 10) myDvd.dy *= -1;

        if(getch() == 'q') break;
        usleep(50000);
    }

    endwin();
    return 0;
}
