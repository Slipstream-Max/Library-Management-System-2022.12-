//
// Created by 谷岩 on 2022/12/27.
//
#include <stdlib.h>
#include "stdio.h"
#include "catagory_management.h"
#include "data_list.h"
#include "string.h"

//分类查找
void catagory_search(){
    printf("请输入要查询的分类。\n");
    fflush(stdout);
    fflush(stdin);
    char word[5];
    int is_done=NON;
    while (!is_done){
        scanf("%s",&word);
        fflush(stdin);
        if(strcmp(word,"#")==0){
            //全列出 属于分类查找的一个小功能
            full_display();
            continue_question(&is_done);
            continue;
        }
        if(strcmp(word,"*")== 0){
            for (int i = 0; i < cat_length; ++i) {
                if(book_catagory[i].is_exist==YES){
                    printf("分类号为：%d ",i);
                    printf("有%d种书 ",book_catagory[i].size);
                    if(strcmp(book_catagory[i].catagory_name,"-1")!= 0){
                        printf("分类名为：%s",book_catagory[i].catagory_name);
                    }
                    printf("。\n");
                    fflush(stdout);
                }
            }
        }
        else{
            int cat_num= atoi(word);
            if(book_catagory[cat_num].is_exist==YES){
                fflush(stdout);
                printf("分类存在 分类号为：%d 有%d种书",cat_num,book_catagory[cat_num].size);
                if(strcmp(book_catagory[cat_num].catagory_name,"-1")!= 0){
                    printf("分类名为：%s",book_catagory[cat_num].catagory_name);
                }
                printf("。\n");
                struct Book_Node *point=book_catagory[cat_num].head;
                while (point!=NULL){
                    if(point->able==YES){
                        printf("书号为%d，书名为：%s，书总量为%d，现有库存为%d，借阅量为%d\n",
                               point->book_number,point->bookname,point->total_storage,point->storage_now,point->borrow_number);
                    }
                    point=point->next;
                }
                fflush(stdout);
            }
            else{
                fflush(stdout);
                printf("分类不存在！\n");
            }
        }
        continue_question(&is_done);
    }
}

//添加分类
void catagory_add(){
    printf("请输入要增加的分类。\n");
    fflush(stdout);
    int cat_num;
    int is_done=NON;
    while (!is_done){
        scanf("%d",&cat_num);
        fflush(stdin);
        if(book_catagory[cat_num].is_exist==YES) {
            printf("分类 %d 已存在。\n",cat_num);
            fflush(stdout);
            continue_question(&is_done);
            fflush(stdout);
            continue;
        }
        //转换状态
        book_catagory[cat_num].is_exist=YES;
        printf("分类 %d 添加成功。\n",cat_num);
        fflush(stdout);
        continue_question(&is_done);
        fflush(stdout);
    }

}

//删除分类
void catagory_del() {
    printf("请输入要删除的分类。\n");
    fflush(stdout);
    int cat_num;
    int is_done=NON;
    while (!is_done){
        scanf("%d",&cat_num);
        fflush(stdin);
        if(book_catagory[cat_num].is_exist==NON){
            printf("分类不存在。\n");
            continue_question(&is_done);
            continue;
        }

        if(book_catagory[cat_num].size!=0){
            printf("有 %d 种图书，不能删除。\n",book_catagory[cat_num].size);
            continue_question(&is_done);
            continue;
        }
        book_catagory[cat_num].is_exist=NON;
        printf("删除分类成功。\n");
        continue_question(&is_done);
    }
}

//修改分类
void catagory_modify(){
    printf("请输入要修改的分类。\n");
    fflush(stdout);
    int cat_num;
    int is_done=NON;
    while (!is_done){
        scanf("%d",&cat_num);
        fflush(stdin);
        printf("您要修改的%d分类，",cat_num);
        if(strcmp(book_catagory[cat_num].catagory_name,"-1")!= 0){
            printf("分类名为：%s",book_catagory[cat_num].catagory_name);
        } else{
            printf("分类名未命名");
        }
        printf("。\n");
        printf("请输入分类名称。\n");
        fflush(stdout);
        char cat_name[30];
        scanf("%s",cat_name);
        fflush(stdin);
        strcpy(book_catagory[cat_num].catagory_name,cat_name);
        printf("重命名成功。分类%d名称为%s。\n",cat_num,book_catagory[cat_num].catagory_name);
        continue_question(&is_done);
    }
}

//全展示 按照分类书籍 分类书籍 展示图书馆所有分类和书籍
// 直观的感受海量数据（爽）
void full_display(){
    struct Book_Node *point;
    for (int i = 0; i < cat_length; ++i) {
        if(book_catagory[i].is_exist==YES){
            printf("分类%d 名称为%s ，有%d种书籍\n",i,book_catagory[i].catagory_name,book_catagory[i].size);
            point=book_catagory[i].head;
            while (point!=NULL){
                if(point->able==YES){
                    printf("书号为%d，书名为：%s，书总量为%d，现有库存为%d，借阅量为%d\n",
                           point->book_number,point->bookname,point->total_storage,point->storage_now,point->borrow_number);
                }
                point=point->next;
            }
            printf("\n");
        }
    }
}