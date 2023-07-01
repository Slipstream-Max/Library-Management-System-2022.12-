//
// Created by 谷岩 on 2022/12/28.
//
#include <malloc.h>
#include <stdio.h>
#include "catagory_management.h"
#include "string.h"
#include "data_io.h"
#include "data_list.h"

void data_import() {
    //指向文件
    FILE *fp = fopen("./data/data_load.txt", "r+，ccs=UTF-8");
    if(!fp){
        perror("file open failed");
        return;
    }
    char buf[BUFSIZ]={0};
    fgets(buf,BUFSIZ,fp); //首行去掉

    //导入分类
    while (strncmp(buf,"分类号 书号 书名 书籍数量 库存量 借阅量\n", BUFSIZ)!=0){
        fgets(buf,BUFSIZ,fp);
        if(strncmp(buf,"分类号 书号 书名 书籍数量 库存量 借阅量\n", BUFSIZ)!=0){
            catagory_import(buf);
        }
    }
    //导入图书
    while(!feof(fp)){
        fgets(buf, BUFSIZ, fp);
        book_import(buf);
    }
    printf("图书导入成功！\n");
    fclose(fp);
}

void data_export() {
    FILE *fp = fopen("./data/data_save.txt", "w+，ccs=UTF-8");
    if(!fp){
        perror("file open failed");
        return;
    }
    fprintf(fp,"分类号 分类名\n");
    catagory_export(fp);
    fprintf(fp,"分类号 书号 书名 书籍数量 库存量 借阅量\n");
    book_export(fp);
    fclose(fp);
    printf("保存成功！\n");
}

void catagory_import(char *buf){
    int catagory_number;
    char catagory_name[30];
    sscanf(buf,"%d %s",&catagory_number,catagory_name);
    book_catagory[catagory_number].is_exist=YES;
    strcpy(book_catagory[catagory_number].catagory_name,catagory_name);
}

void book_import(char *buf){
    int catagory_number,book_number,total_storage,storage_now,borrow_number;
    char book_name[100];
    //给所有元素赋值
    sscanf(buf,"%d %d %s %d %d %d",&catagory_number,&book_number,book_name,&total_storage,&storage_now,&borrow_number);
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
    New_Book->total_storage=total_storage;
    New_Book->storage_now=storage_now;
    New_Book->borrow_number=borrow_number;
    //头指针指向最后存的书
    book_catagory[catagory_number].head=New_Book;
    book_catagory[catagory_number].size+=1; //数量增加
}

void catagory_export(FILE *fp){
    for (int i = 1; i < 101; ++i) {
        if(book_catagory[i].is_exist==YES){
            fprintf(fp,"%d %s\n",i,book_catagory[i].catagory_name);
        }
    }
}

void book_export(FILE *fp){
    for (int i = 1; i < cat_length; ++i) {
        struct Book_Node *point;
        if(book_catagory[i].is_exist==YES){
            point=book_catagory[i].head;
            while (point!=NULL){
                if(point->able==YES){
                    fprintf(fp,"%d %d %s %d %d %d\n",i,point->book_number,point->bookname,
                            point->total_storage,point->storage_now,point->borrow_number);
                }
                point=point->next;
            }
        }
    }
    long pos = ftell(fp);
    // 将文件指针倒回到文件末尾
    fseek(fp, -1, SEEK_END);
    // 覆盖原有的换行符
    fputc(EOF, fp);
    // 将文件指针倒回到文件末尾
    fseek(fp, pos, SEEK_SET);
}