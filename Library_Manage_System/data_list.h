//
// Created by 谷岩 on 2022/12/22.
//

#ifndef LIBRARY_MANAGE_SYSTEM_DATA_LIST_H
#define LIBRARY_MANAGE_SYSTEM_DATA_LIST_H
#define NON 0 //不存在该分类
#define YES 1 //存在该分类
//图书结点
struct Book_Node{
    int able;
    int book_number;
    char bookname[100];
    int total_storage;
    int storage_now;
    int borrow_number;
    struct Book_Node *next;
};
//分类结点
struct catagory{
    int is_exist;
    int size;
    char catagory_name[30];
    struct Book_Node *head;
};

extern struct catagory book_catagory[101];
void add_book_operation();
void add_book_to_library(int catagory_number,int book_number,char *book_name,int book_storage);
void delete_book_operation();
void continue_question(int *is_done);
void catagory_init();
int duplicate_checking(int catagory_num, int book_num,int storage_num);
#endif //LIBRARY_MANAGE_SYSTEM_DATA_LIST_H
