//
// Created by 谷岩 on 2022/12/22.
//
#include <malloc.h>
#include "string.h"
#include "data_list.h"
#include "catagory_management.h"
#include "menu.h"
#include "stdio.h"
#define NON 0 //不存在该分类
#define YES 1 //存在该分类

struct catagory book_catagory[cat_length];

//入库图书的模块
void add_book_operation() {
    int is_done=NON;
    while (!is_done){
        int catagory_number,book_number,book_storage;
        char book_name[100];

        scanf("%d %d %s %d",&catagory_number,&book_number,book_name,&book_storage);
        fflush(stdin);
        if(book_catagory[catagory_number].size>=1){
            //查重
            int res=duplicate_checking(catagory_number,book_number,book_storage);
            if(res==YES){
                printf("书号重复，已增加库存。\n");
                fflush(stdout);
                continue_question(&is_done);
                continue;
            }
        }
        add_book_to_library(catagory_number,book_number,book_name,book_storage);
        printf("添加成功!书在%d分类，书号是%d，书名是%s，有%d本。\n",catagory_number,book_number,book_name,book_storage);
        continue_question(&is_done);
    }
}

//真正执行入库图书操作
void add_book_to_library(int catagory_number,int book_number,char *book_name,int book_storage) {

    if(book_catagory[catagory_number].is_exist==NON){
        book_catagory[catagory_number].is_exist=YES;
    }
    //链表指向之前存的书
    struct Book_Node *New_Book; //动态申请一个内存空间成为图书
    New_Book=(struct Book_Node*) malloc(sizeof(struct Book_Node));
    New_Book->next=book_catagory[catagory_number].head;
    //初始化为可访问
    New_Book->able=YES;
    //书名字
    strcpy(New_Book->bookname,book_name);
    //书号
    New_Book->book_number=book_number;
    //设置书的存量
    New_Book->total_storage=book_storage;
    New_Book->storage_now=book_storage;
    New_Book->borrow_number=0;
    //头指针指向最后存的书
    book_catagory[catagory_number].head=New_Book;
    book_catagory[catagory_number].size+=1; //数量增加
}

//初始化分类链表
void catagory_init(){
    for (int i = 0; i < cat_length; ++i) {
        book_catagory[i].is_exist=NON;
        book_catagory[i].size=0;
        strcpy(book_catagory[i].catagory_name,"-1");
        book_catagory[i].head=NULL;
    }
}

//查重
int duplicate_checking(int catagory_num, int book_num,int storage_num) {
    struct Book_Node *point=book_catagory[catagory_num].head;
    while(point!=NULL){
        if(point->book_number==book_num){
            point->total_storage+=storage_num;
            point->storage_now+=storage_num;
            return YES;
        }
        point=point->next;
    }
    return NON;
}

//是否循环的函数 复用率很高
void continue_question(int *is_done){
    printf("是否输入完毕？1退出 0继续\n");
    fflush(stdout);
    scanf("%d",is_done);
    fflush(stdin);
    if(*is_done==YES){
        printf("退出中......\n");
        fflush(stdout);
    }
    else{
        printf("继续\n");
        fflush(stdout);
    }
}

//图书出库
void delete_book_operation(){
    int catagory_num,book_num;
    int isDone=NON;
    while (!isDone){
        scanf("%d %d",&catagory_num,&book_num);
        struct Book_Node *point=book_catagory[catagory_num].head;
        int find=NON;
        while(point!=NULL){
            if(point->book_number==book_num){
                find=YES;
                break;
            }
            point=point->next;
        }

        if (find == NON){
            printf("查无此书，出库失败\n");
            continue_question(&isDone);
            continue;
        }

        if(point->borrow_number!=0){
            printf("借阅数为 %d 不能出库。\n",point->borrow_number);
            fflush(stdout);
            continue_question(&isDone);
            continue;
        }
        //正常处理
        point->able=NON;
        book_catagory[catagory_num].size-=1;
        printf("出库成功。\n");
        continue_question(&isDone);
    }
}