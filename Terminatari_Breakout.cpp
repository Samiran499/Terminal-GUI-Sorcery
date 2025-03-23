#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>

int max_x = 0;
int max_y = 0;

struct ball
{
    int x = max_x/4, y = max_y/2, dx = 1, dy = 1;
};

struct slider
{
    int x = max_x/2, dx = 10;
    char figs[50] =   "0000000000000000000000000000000000000000000000000";
    char spaces[50] = "                                                 ";
};

struct figures
{
    const char nescafe[25][174] = {
        "                                                                                                                                                      @@@@@@@                ",
        "                                                                                                                                                     @@@@@@@@                ",
        "                                                                                                                                                    @@@@@@@@@                ",
        "                                                                                                                                                    @@@@@@@@@                ",
        "                                                                                                                                                   @@@@@@@@@                 ",
        "         @@@@@@@              @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@         @@@@@@@@@              ",
        "         @@@@@@@@@            @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@         @@@@@@@@                ",
        "         @@@@@@@@@@@          @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@          @@@@@@@@                   ",
        "         @@@@@@@@@@@@         @@@@@@                                                                                                                                         ",
        "         @@@@@@@@@@@@@        @@@@@@                               @@@@                   @@@                                                                                ",
        "         @@@@@@@@@@@@@@       @@@@@@    @@@@@@@@@@@@@@@@@     @@@@@@@@@@@@@@       @@@@@@@@@@@@@@         @@@@@@@@          @@@@@@@@@@@@@@@@@   @@@@@@@@@@@@@@@@@            ",
        "         @@@@@@ @@@@@@@@      @@@@@@    @@@@@@@@@@@@@@@@@   @@@@@@@@@@@@@@@@      @@@@@@@@@@@@@@@        @@@@@@@@@@         @@@@@@@@@@@@@@@@@   @@@@@@@@@@@@@@@@@            ",
        "         @@@@@@  @@@@@@@@     @@@@@@    @@@@@@              @@@@@@         @     @@@@@@@                @@@@@@@@@@@@        @@@@@@              @@@@@@                       ",
        "         @@@@@@   @@@@@@@@    @@@@@@    @@@@@@             @@@@@@@               @@@@@@                @@@@@@ @@@@@@@       @@@@@@              @@@@@@                       ",
        "         @@@@@@    @@@@@@@@   @@@@@@    @@@@@@              @@@@@@@@@           @@@@@@@                @@@@@   @@@@@@       @@@@@@              @@@@@@                       ",
        "         @@@@@@     @@@@@@@   @@@@@@    @@@@@@@@@@@@@@@     @@@@@@@@@@@@@@      @@@@@@@               @@@@@@   @@@@@@@      @@@@@@@@@@@@@@@@    @@@@@@@@@@@@@@@              ",
        "         @@@@@@      @@@@@@@@ @@@@@@    @@@@@@@@@@@@@@@      @@@@@@@@@@@@@@@    @@@@@@@               @@@@@     @@@@@@      @@@@@@@@@@@@@@@@    @@@@@@@@@@@@@@@              ",
        "         @@@@@@       @@@@@@@ @@@@@@    @@@@@@                   @@@@@@@@@@@@   @@@@@@@              @@@@@@     @@@@@@@     @@@@@@              @@@@@@                       ",
        "         @@@@@@        @@@@@@@@@@@@@    @@@@@@                        @@@@@@@@  @@@@@@@              @@@@@@@@@@@@@@@@@@@    @@@@@@              @@@@@@                       ",
        "         @@@@@@         @@@@@@@@@@@@    @@@@@@@                        @@@@@@@   @@@@@@@            @@@@@@@@@@@@@@@@@@@@    @@@@@@              @@@@@@                       ",
        "         @@@@@@          @@@@@@@@@@@    @@@@@@@@@@  @@@@@   @@@@@@@  @@@@@@@@    @@@@@@@@@@  @@@@   @@@@@         @@@@@@    @@@@@@              @@@@@@@@@@  @@@@@   @ @      ",
        "         @@@@@@           @@@@@@@@@@     @@@@@@@@@@@@@@@@   @@@@@@@@@@@@@@@@      @@@@@@@@@@@@@@@  @@@@@@         @@@@@@@   @@@@@@               @@@@@@@@@@@@@@@@    @@@     ",
        "         @@@@@@              @@@@@@@        @@@@@@@@@@@@@    @@@@@@@@@@@@@           @@@@@@@@@@@@  @@@@@@         @@@@@@@    @@@@@                  @@@@@@@@@@@@@            ",
    };
    const int points = 1564;
};

bool collision(ball& myBall)
{   
    int& y = myBall.y;
    int& x = myBall.x;
    int& dy = myBall.dy;
    int& dx = myBall.dx;

    char obj1 = mvinch(y + dy, x) & A_CHARTEXT;
    char obj2 = mvinch(y + dy, x + dx) & A_CHARTEXT;
    char obj3 = mvinch(y, x + dx) & A_CHARTEXT;
    if(obj1 == '@' && obj3 == '@')
    {
        mvprintw(y + dy, x + dx, " ");
        mvprintw(y, x + dx, " ");
        mvprintw(y + dy, x, " ");
        dx *= -1;
        dy *= -1;
        return true;
    }
    else if(obj1 == '@')
    {
        mvprintw(y + dy, x, " ");
        dy *= -1;
        return true;
    }
    else if(obj3 == '@')
    {
        mvprintw(y, x + dx, " ");
        dx *= -1;
        return true;
    }
    else if (obj2 == '@')
    {
        mvprintw(y + dy, x + dx, " ");
        mvprintw(y, x + dx, " ");
        mvprintw(y + dy, x, " ");
        dx *= -1;
        dy *= -1;
        return true;
    }
    else return false;
}

int main()
{
    initscr();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);

    getmaxyx(stdscr, max_y, max_x);
    
    if (max_x < 180 || max_y < 50) {
        endwin();
        printf("Window too small!\nResize to play\n");
        return 1;
    }

    ball myBall;
    slider mySlider;

    figures myFigures;

    for (int i = 0; i < 25; i++) {
        mvprintw(i, max_x/2-87, "%s", myFigures.nescafe[i]);
    }
    refresh();

    while(true)
    {
        mvprintw(myBall.y, myBall.x, "o");
        mvprintw(max_y - 2, mySlider.x, "%s", mySlider.figs);
        refresh();

        if(!collision(myBall)) // If no collision move ball
        {
            myBall.x += myBall.dx;
            myBall.y += myBall.dy;
        }

        char input = getch();
      
        if(input == 'p' || input == 'P') // For pausing
        {
            while(true)
            {
                mvprintw(myBall.y, myBall.x, "PAUSED!");
                refresh();
                usleep(1000);
                mvprintw(myBall.y, myBall.x, "       ");
                if(getch() == 'p' || getch() == 'P') break;
            }
        }
        else if(input == 'd' || input == 'D')
        {
            if(mySlider.x < max_x - 60)
            {
                mySlider.x += mySlider.dx;
            }
            mvprintw(max_y - 2, mySlider.x - mySlider.dx, "%s", mySlider.spaces);
        }
        else if(input == 'a' || input == 'A')
        {
            if(mySlider.x >= 10)
            {
                mySlider.x -= mySlider.dx;
            }
            mvprintw(max_y - 2, mySlider.x + mySlider.dx, "%s", mySlider.spaces);
        }
        else if(input == 'q' || input == 'Q') break;
        if(myBall.y > max_y - 1) break;

        usleep(40000);
        mvprintw(myBall.y - myBall.dy, myBall.x - myBall.dx, " ");
        if((myBall.x >= mySlider.x && myBall.x < mySlider.x + 50) && myBall.y > max_y - 4) myBall.dy *= -1;
        if(myBall.x <= 0 || myBall.x >= max_x - 1) myBall.dx *= -1;
        if(myBall.y <= 0) myBall.dy *= -1;
        refresh();
    }

    endwin();
    return 0;
}
