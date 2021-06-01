// Created by LXSTVAYNE, NjRat


#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <iomanip>
#include <conio.h>
#include <Windows.h>
#include <functional>

#ifndef MENU_MENU_H
#define MENU_MENU_H

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

class Item {
protected:
    const std::string name;
    const std::function<void()> function;

public:
    const bool pause;

public:
    explicit Item(const std::string& name, const std::function<void()>& function, const bool pause = true)
        : name(name), function(function), pause(pause)
    {
    }

    friend std::ostream& operator<< (std::ostream& os, const Item& item) {
        os << item.name;
        return os;
    }

    Item operator() () {
        function();
        return *this;
    }

    bool is_empty() {
        return bool(function == nullptr);
    }
};

class Cursor {
private:
    const unsigned int anchor;
    unsigned int number;
    std::vector<Item>& items;

public:
    explicit Cursor(const unsigned int number, std::vector<Item>& items)
        : number(number), items(items), anchor(number)
    {
    }

    void operator++ (int) {
        if (items.size() - 1 == number)
            return;

        number++;
    }

    void operator-- (int) {
        if (number == anchor)
            return;

        number--;
    }

    Item& getCurrentItem() {
        return items[number];
    }

    unsigned int getCurrentNumber() {
        return number;
    }
};

class Menu {
private:


    std::vector<Item> items;
    Cursor cursor;
    std::string color_options;

    static void gotoxy(int xpos, int ypos) {
        COORD scrn;
        HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
        scrn.X = xpos; scrn.Y = ypos;
        SetConsoleCursorPosition(hOuput, scrn);
    }

    void draw() {
        system("cls");
        system(color_options.c_str());
        for (const auto& row : this->items) {
            std::cout << row << std::endl;
        }
    }

public:
    explicit Menu()
        : cursor(0, items)
    {
        set_color();
    }
    explicit Menu(const std::string& name)
        : cursor(1, items)
    {
        items.emplace_back(name, nullptr);
        set_color();
    }

    void add_row(const std::string& item_name, const std::function<void()>& function, const bool pause = true) {
        items.emplace_back(Item(item_name, function, pause));
    }

    void set_color(char BG_COLOR = Colors::BLACK, char FONT_COLOR = Colors::BRIGHT_WHITE) {
        color_options = "COLOR ";
        color_options += BG_COLOR;
        color_options += FONT_COLOR;
    }

    void run() {

        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);

        int ch = 0;
        bool exit = false;

        draw();

        while (!exit)
        {
            gotoxy(0, cursor.getCurrentNumber());

            ch = _getch();

            if (ch == 224)
                ch = _getch();

            switch (ch)
            {
            case 27: exit = true; break; //

            case 72: cursor--; break;

            case 80: cursor++; break;

            case 13:
                if (cursor.getCurrentItem().is_empty()) // Кейс когда на кнопку Выход
                {
                    system("cls");
                    exit = true;
                    break;
                }
                else
                {
                    system("cls");
                    cursor.getCurrentItem()();
                    if (cursor.getCurrentItem().pause) {
                        std::cout << std::endl << "Press any key to return" << std::endl;
                        _getch();
                    }
                    draw();
                    break;
                }

            default: break;

            }

        }
    }

};


#endif //MENU_MENU_H

