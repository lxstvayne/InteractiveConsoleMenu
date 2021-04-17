// Created by LXSTVAYNE, NjRat


#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <iomanip>
#include <conio.h>
#include <Windows.h>
#include <functional>

enum Colors : char {
    BLUE = '1',
    LIGHT_GREEN = 'A',
    LIGHT_AQUA = 'B',
    AQUA = '3',
    LIGHT_RED = 'C',
    RED = '4',
    LIGHT_PURPLE = 'D',
    PURPLE = '5',
    LIGHT_YELLOW = 'E',
    YELLOW = '6',
    BRIGHT_WHITE = 'F',
    WHITE = '7',
    GRAY = '8',
    LIGHT_BLUE = '9',
    BLACK = '0'
};


class Menu
{
private:
    std::vector<std::string> menu;
    std::string name;
    std::vector<std::function<void()>> functions;

    static void gotoxy(int xpos, int ypos)
    {
        COORD scrn;
        HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
        scrn.X = xpos; scrn.Y = ypos;
        SetConsoleCursorPosition(hOuput, scrn);
    }

    void show() {

        system("cls");

        if (!this->name.empty())
        {
            std::cout << this->name << std::endl;
            std::cout << std::endl;
        }

        for (const auto& el : this->menu)
            std::cout << el << std::endl;

        std::cout << " Выход" << std::endl;
    }

    void print_other(const std::function<void()>& f) {
        system("cls");
        f();
        std::cout << std::endl << "Нажмите любую клавишу, чтобы вернуться" << std::endl;
        _getch();
        show();
    }


public:

    explicit Menu(std::string title = "") {
        this->name = std::move(title);
    }

    Menu(std::vector<std::string> v, std::vector<std::function<void()>> functions, std::string title = "") {
        this->menu = std::move(v);
        this->name = std::move(title);
        this->functions = std::move(functions);
    }


    void add_row(const std::string& s, const std::function<void()>& f) {
        this->menu.push_back(s);
        this->functions.push_back(f);
    }


    static void set_colors(char BG_COLOR = Colors::BLACK, char FONT_COLOR = Colors::BRIGHT_WHITE) {
        std::string option = "COLOR ";
        option += BG_COLOR;
        option += FONT_COLOR;
        const char* opt = option.c_str();
        system(opt);
    }


    void run() {

        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);


        const int NUM_MENU_ITEMS = this->menu.size() + 1; // showMenu + 1

        int activeMenuItem = 0;
        if (!this->name.empty())
            activeMenuItem = 2;

        int start_index = 0;
        if (!this->name.empty())
            start_index = 2;

        int ch = 0;
        bool exit = false;

        show();

        while (!exit)
        {
            gotoxy(0, activeMenuItem);

			ch = _getch();


            if (ch == 224)
                ch = _getch();

            switch (ch)
            {
            case 27: exit = true; break; //

            case 72: activeMenuItem--; break;

            case 80: activeMenuItem++; break;

            case 13:
                if (activeMenuItem == this->menu.size() + start_index)
                {
                    system("cls");
                    exit = true;
                    break;
                }
                else if (start_index < activeMenuItem < this->menu.size() + start_index)
                {
                    print_other(this->functions[activeMenuItem - start_index]);
                    break;
                }

            default: break;

            }

            if (activeMenuItem < 0 + start_index)
                activeMenuItem = 0 + start_index;


            if (activeMenuItem > NUM_MENU_ITEMS - 1 + start_index)
                activeMenuItem = NUM_MENU_ITEMS - 1 + start_index;

        }
    }

};
