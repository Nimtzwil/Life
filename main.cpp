#include <vector>
#include <string>

#include "libtcod.hpp"

//counts the alive neighbors of a cell
int countNeighbors(std::vector< std::vector<bool> > & current, int x, int y){
    int sum = 0;
//checks all 8 neighbors and returns their sum
    for (int i = x-1; i <= x+1; i++){
        for (int j = y-1; j <= y+1; j++){
            if((current[i][j] == true)&& !((i == x)&&(j == y)))
                sum = sum + 1;
        }
    }
    return sum;
}

//steps to the next time
void update(std::vector< std::vector<bool> > & current, std::vector< std::vector<bool> > & step){
    int neighbors = 0;
//check all relevant cells
    for (unsigned int v = 1; v <= current.size()-2; v++){
        for (unsigned int h = 1; h <= current.size()-2; h++){
//counts the neighbors
            neighbors = countNeighbors(current, v, h);
//determines if the cell lives or dies
            if ((current[v][h])&&((neighbors == 2)||(neighbors == 3)))
                step[v][h] = true;
            else if (!(current[v][h])&&(neighbors == 3))
                step[v][h] = true;
            else
                step[v][h] = false;
        }
    }

//updates the universe
    current = step;
}

//render the game
void render(int & curX, int & curY, std::vector< std::vector<bool> > & current, bool & hide, int & clock){
    TCODConsole::root->clear();
    std::string str = "";
    int count = 0;
//Universe
    for (unsigned int I = 1; I <= current.size()-2; I++){
        for (unsigned int J = 1; J <= current.size()-2; J++){
            if(current[I][J])
                TCODConsole::root->setCharBackground(I-1, J-1, TCODColor::white);
            else
                TCODConsole::root->setCharBackground(I-1, J-1, TCODColor::black);
        }
    }

//cursor
    if (!hide){
        TCODConsole::root->setChar(curX,curY,7);
        TCODConsole::root->setCharForeground(curX,curY,TCODColor::blue);
    }

//vertical lines
    for (unsigned int J = 1; J < current.size()-3; J++){
        TCODConsole::root->setChar(current.size()-2,J,186);
        TCODConsole::root->setCharForeground(current.size()-2, J, TCODColor::red);

        TCODConsole::root->setChar(current.size()+9,J,186);
        TCODConsole::root->setCharForeground(current.size()+9, J, TCODColor::red);
    }

//horizontal lines
    for (unsigned int I = current.size()-1; I <current.size()+9; I++){
        TCODConsole::root->setChar(I,0,205);
        TCODConsole::root->setCharForeground(I, 0, TCODColor::red);

        TCODConsole::root->setChar(I,5,205);
        TCODConsole::root->setCharForeground(I, 5, TCODColor::red);

        TCODConsole::root->setChar(I,current.size()-5,205);
        TCODConsole::root->setCharForeground(I, current.size()-5, TCODColor::red);

        TCODConsole::root->setChar(I,current.size()-3,205);
        TCODConsole::root->setCharForeground(I, current.size()-3, TCODColor::red);
    }

//left connections
    TCODConsole::root->setChar(current.size()-2,0,201);
    TCODConsole::root->setCharForeground(current.size()-2,0, TCODColor::red);

    TCODConsole::root->setChar(current.size()-2,5,204);
    TCODConsole::root->setCharForeground(current.size()-2,5, TCODColor::red);

    TCODConsole::root->setChar(current.size()-2,current.size()-5,204);
    TCODConsole::root->setCharForeground(current.size()-2,current.size()-5, TCODColor::red);

    TCODConsole::root->setChar(current.size()-2,current.size()-3,200);
    TCODConsole::root->setCharForeground(current.size()-2,current.size()-3, TCODColor::red);

//right connections
    TCODConsole::root->setChar(current.size()+9,0,187);
    TCODConsole::root->setCharForeground(current.size()+9,0, TCODColor::red);

    TCODConsole::root->setChar(current.size()+9,5,185);
    TCODConsole::root->setCharForeground(current.size()+9,5, TCODColor::red);

    TCODConsole::root->setChar(current.size()+9,current.size()-5,185);
    TCODConsole::root->setCharForeground(current.size()+9,current.size()-5, TCODColor::red);

    TCODConsole::root->setChar(current.size()+9,current.size()-3,188);
    TCODConsole::root->setCharForeground(current.size()+9,current.size()-3, TCODColor::red);

//Title
    count = 0;
    str = "Conway's";
    for (char c: str){
        TCODConsole::root->setChar(current.size()-1+count,1,c);
        TCODConsole::root->setCharForeground(current.size()-1+count,1, TCODColor::blue);
        count++;
    }

    count = 0;
    str = "  Game";
    for (char c: str){
        TCODConsole::root->setChar(current.size()-1+count,2,c);
        TCODConsole::root->setCharForeground(current.size()-1+count,2, TCODColor::chartreuse);
        count++;
    }

    count = 0;
    str = "    of";
    for (char c: str){
        TCODConsole::root->setChar(current.size()-1+count,3,c);
        TCODConsole::root->setCharForeground(current.size()-1+count,3, TCODColor::chartreuse);
        count++;
    }

    count = 0;
    str = "     Life";
    for (char c: str){
        TCODConsole::root->setChar(current.size()-1+count,4,c);
        TCODConsole::root->setCharForeground(current.size()-1+count,4, TCODColor::chartreuse);
        count++;
    }

//Time
    count = 0;
    str = "Time-";
    for (char c: str){
        TCODConsole::root->setChar(current.size()-1+count,current.size()-4,c);
        TCODConsole::root->setCharForeground(current.size()-1+count,current.size()-4, TCODColor::blue);
        count++;
    }

    str = std::to_string(clock);
    for (char c: str){
        TCODConsole::root->setChar(current.size()-1+count,current.size()-4,c);
        TCODConsole::root->setCharForeground(current.size()-1+count,current.size()-4, TCODColor::chartreuse);
        count++;
    }

//Controls
    count = 0;
    str = " Controls";
    for (char c: str){
        TCODConsole::root->setChar(current.size()-1+count,6,c);
        TCODConsole::root->setCharForeground(current.size()-1+count,6, TCODColor::blue);
        count++;
    }

    count = 0;
    str = "Move-arrow";
    for (char c: str){
        TCODConsole::root->setChar(current.size()-1+count,8,c);
        TCODConsole::root->setCharForeground(current.size()-1+count,8, TCODColor::chartreuse);
        count++;
    }
    count = 0;
    str = "      keys";
    for (char c: str){
        TCODConsole::root->setChar(current.size()-1+count,9,c);
        TCODConsole::root->setCharForeground(current.size()-1+count,9, TCODColor::chartreuse);
        count++;
    }

    count = 0;
    str = " Hide  - h";
    for (char c: str){
        TCODConsole::root->setChar(current.size()-1+count,12,c);
        TCODConsole::root->setCharForeground(current.size()-1+count,12, TCODColor::chartreuse);
        count++;
    }
    count = 0;
    str = "Cursor";
    for (char c: str){
        TCODConsole::root->setChar(current.size()-1+count,13,c);
        TCODConsole::root->setCharForeground(current.size()-1+count,13, TCODColor::chartreuse);
        count++;
    }

    count = 0;
    str = "Flip   - f";
    for (char c: str){
        TCODConsole::root->setChar(current.size()-1+count,16,c);
        TCODConsole::root->setCharForeground(current.size()-1+count,16, TCODColor::chartreuse);
        count++;
    }
    count = 0;
    str = "  Cell";
    for (char c: str){
        TCODConsole::root->setChar(current.size()-1+count,17,c);
        TCODConsole::root->setCharForeground(current.size()-1+count,17, TCODColor::chartreuse);
        count++;
    }

    count = 0;
    str = "Random - r";
    for (char c: str){
        TCODConsole::root->setChar(current.size()-1+count,20,c);
        TCODConsole::root->setCharForeground(current.size()-1+count,20, TCODColor::chartreuse);
        count++;
    }
    count = 0;
    str = " Fill";
    for (char c: str){
        TCODConsole::root->setChar(current.size()-1+count,21,c);
        TCODConsole::root->setCharForeground(current.size()-1+count,21, TCODColor::chartreuse);
        count++;
    }

    count = 0;
    str = "Clear  - c";
    for (char c: str){
        TCODConsole::root->setChar(current.size()-1+count,24,c);
        TCODConsole::root->setCharForeground(current.size()-1+count,24, TCODColor::chartreuse);
        count++;
    }
    count = 0;
    str = " Board";
    for (char c: str){
        TCODConsole::root->setChar(current.size()-1+count,25,c);
        TCODConsole::root->setCharForeground(current.size()-1+count,25, TCODColor::chartreuse);
        count++;
    }

    count = 0;
    str = "Step   - s";
    for (char c: str){
        TCODConsole::root->setChar(current.size()-1+count,28,c);
        TCODConsole::root->setCharForeground(current.size()-1+count,28, TCODColor::chartreuse);
        count++;
    }
    count = 0;
    str = "  Time";
    for (char c: str){
        TCODConsole::root->setChar(current.size()-1+count,29,c);
        TCODConsole::root->setCharForeground(current.size()-1+count,29, TCODColor::chartreuse);
        count++;
    }
}

//main body of game
int main() {
    int width = 60;
    int height = width;
    int cursorX = 0;
    int cursorY = 0;
    std::vector< std::vector<bool> > Universe(height+2, std::vector<bool>(width+2));
    std::vector< std::vector<bool> > Next(height+2, std::vector<bool>(width+2));
    TCODConsole::initRoot(width+12, height, "Life", false);
    TCODRandom rnd = TCODRandom();
    int rndVal = 0;
    bool hidden = false;
    int time = 0;

//render initial state
    render(cursorX,cursorY,Universe,hidden,time);

//keeps game going
    while ( !TCODConsole::isWindowClosed() ) {
        TCOD_key_t key;
//check if key has been pressed
        TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key,NULL);
        switch(key.vk) {
//up
            case TCODK_UP :
                cursorY = (cursorY - 1);
            break;
//down
            case TCODK_DOWN :
                cursorY = (cursorY + 1);
            break;
//left
            case TCODK_LEFT :
                cursorX = (cursorX - 1);
            break;
//right
            case TCODK_RIGHT :
                cursorX = (cursorX + 1);
            break;

//not a special character
            case TCODK_CHAR :
//flip cell
                if(key.c == 'f'){
                    if(Universe[cursorX+1][cursorY+1])
                        Universe[cursorX+1][cursorY+1] = false;
                    else
                        Universe[cursorX+1][cursorY+1] = true;
                    time = 0;
                }
//step time
                else if(key.c == 's'){
                    update(Universe, Next);
                    time++;
                }
//clear Universe
                else if(key.c == 'c'){
                    for (int I = 1; I <= width; I++){
                        for (int J =1; J <=height; J++){
                            Universe[I][J] = false;
                        }
                    }
                    time = 0;
                }
//randomly fill Universe
                else if(key.c == 'r'){
                    for (int I = 1; I <= width; I++){
                        for (int J =1; J <=height; J++){
                            rndVal = rnd.getInt(1,100);
                            if (rndVal>50)
                                Universe[I][J] = false;
                            else
                                Universe[I][J] = true;
                        }
                    }
                    time = 0;
                }
//hide cursor
                else if(key.c == 'h'){
                    if(hidden)
                        hidden = false;
                    else
                        hidden = true;
                }
            break;

//default
            default:break;
        }

//handle cursor wrapping (% was giving issues when going to -1)
        if (cursorY >= height)
            cursorY = cursorY - height;
        else if (cursorY < 0)
            cursorY = cursorY + height;

        if (cursorX >= width)
            cursorX = cursorX - width;
        else if (cursorX < 0)
            cursorX = cursorX + width;

//render current state
        render(cursorX,cursorY,Universe,hidden,time);

//flush the screen buffer
        TCODConsole::flush();
    }

    return 0;
}
