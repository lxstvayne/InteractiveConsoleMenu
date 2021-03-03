// Created by LXSTVAYNE, NjRat


#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <iomanip>
#include <conio.h>
#include <Windows.h>
#include <functional>


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

    static void print_other(const std::function<void()>& f) {
        system("cls");
        f();
        std::cout << std::endl << "Нажмите любую клавишу, чтобы вернуться" << std::endl;
        _getch();
    }


public:

    explicit Menu(std::string name = "") {
        this->name = std::move(name);
    }

    Menu(std::vector<std::string> v, std::vector<std::function<void()>> functions, std::string name = "") {
        this->menu = std::move(v);
        this->name = std::move(name);
        this->functions = std::move(functions);
    }


    void add_row(const std::string& s, const std::function<void()>& f) {
        this->menu.push_back(s);
        this->functions.push_back(f);
    }


    static void set_colors(char bg_color = '0', char text_color = '7') {
        /*
            Blue 1
            LightGreen "A"
            LightAqua "B"
            Aqua 3
            LightRed "C"
            Red 4
            LightPurple "D"
            Purple 5
            LightYellow "E"
            Yellow 6
            BrightWhite "F"
            White 7
            Gray 8
            LightBlue 9
            Black 0
        */

        std::string option = "COLOR ";
        option += bg_color;
        option += text_color;
        const char* opt = option.c_str();
        system(opt);
    }


    void run() {

        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);
        setlocale(0, "");


        const int NUM_MENU_ITEMS = this->menu.size() + 1; // showMenu + 1

        int activeMenuItem = 0;
        if (!this->name.empty())
            activeMenuItem = 2;

        int start_index = 0;
        if (!this->name.empty())
            start_index = 2;

        int ch = 0;
        bool exit = false;

        while (!exit)
        {
            show();
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
