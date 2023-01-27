//
// Created by 谷岩 on 2022/12/23.
//
#include "data_list.h"
#include "menu.h"
#include "option.h"
#include "book.h"
#include "stdbool.h"
#include "stdlib.h"
#include "catagory_management.h"
#include "data_io.h"

//主菜单的选择函数 run就是运行的意思
void run(){
    int option= main_menu();
    switch (option) {
        case 1:
            catagory_options();
            break;
        case 2:
            add_book_menu();
            add_book_operation();
            break;
        case 3:
            delete_book_menu();
            delete_book_operation();
            break;
        case 4:
            book_search();
            break;
        case 5:
            book_borrow();
            break;
        case 6:
            book_return();
            break;
        case 7:
            data_export();
            exit(0);
    }
}

//分类菜单的选择函数
void catagory_options(){
    bool is_done=false;
    while (!is_done){
        int option=catagory_menu();
        switch (option) {
            case 1:
                catagory_search();
                break;
            case 2:
                catagory_add();
                break;
            case 3:
                catagory_del();
                break;
            case 4:
                catagory_modify();
                break;
            case 5:
                is_done=true;
                break;
        }
    }
}