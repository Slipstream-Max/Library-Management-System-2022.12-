//
// Created by 谷岩 on 2022/12/24.
//
#include "stdlib.h"
#include "data_list.h"
#include "stdio.h"
#include "book.h"
#include "string.h"

//书籍查询
void book_search(){
    printf("请输入想要查询的分类号+（书号、书名）\n例如：1 2或者1 三体\n");
    fflush(stdout);
    int is_done=NON;
    while (!is_done){
        int cat_num;
        char search_word[20];
        scanf("%d %s",&cat_num,search_word);
        fflush(stdin);
        if((int)search_word[0]>='0'&&(int)search_word[0]<='9'){
            int book_num= atoi(search_word);
            struct Book_Node *point=book_catagory[cat_num].head;
            while (point!=NULL){
                if(point->book_number==book_num){
                    break;
                }
                point=point->next;
            }
            if(point==NULL){
                printf("未查询到这本书。\n");
                continue_question(&is_done);
                continue;
            }
            printf("找到了。\n分类号：%d 书号：%d 书名：%s\n书籍总量：%d 库存量：%d 借阅量%d\n",
                   cat_num,book_num,point->bookname,point->total_storage,point->storage_now,point->borrow_number);
            continue_question(&is_done);
            continue;
        }

        struct Book_Node *point=book_catagory[cat_num].head;
        while (point!=NULL){
            if(strcmp(point->bookname,search_word)==0){
                break;
            }
            point=point->next;
        }
        if(point==NULL){
            printf("未查询到这本书。\n");
            continue_question(&is_done);
            continue;
        }
        printf("找到了。\n分类号：%d 书号：%d 书名：%s\n书籍总量：%d 库存量：%d 借阅量%d\n",
               cat_num,point->book_number,point->bookname,point->total_storage,point->storage_now,point->borrow_number);
        continue_question(&is_done);
    }
}

//书籍借阅
void book_borrow(){
    printf("请输入想要借阅的书。 分类号+书号\n例如：1 2\n");
    fflush(stdout);
    int is_done=NON;
    while (!is_done){
        int cat_num,book_num;
        scanf("%d %d",&cat_num,&book_num);
        fflush(stdin);
        if(cat_num>100||book_catagory[cat_num].head==NON){
            printf("您访问的分类不存在！");
            continue_question(&is_done);
            continue;
        }
        struct Book_Node *point=book_catagory[cat_num].head;
        while (point!=NULL){
            if(point->book_number==book_num){
                break;
            }
            point=point->next;
        }
        if(point==NULL){
            printf("未查询到这本书。\n");

        }
        if(point->storage_now==0){
            printf("库存不足，无法借阅。\n");
            continue_question(&is_done);
            continue;
        }
        point->borrow_number++;point->storage_now--;
        printf("借阅成功。借阅量为%d，库存为%d\n",point->borrow_number,point->storage_now);
        continue_question(&is_done);
    }
}

//书籍归还
void book_return(){
    printf("请输入想要归还的书。 分类号+书号\n例如：1 2\n");
    fflush(stdout);
    int is_done=NON;
    while (!is_done){
        int cat_num,book_num;
        scanf("%d %d",&cat_num,&book_num);
        fflush(stdin);
        if(cat_num>100||book_catagory[cat_num].head==NON){
            printf("您访问的分类不存在！");
            continue_question(&is_done);
            continue;
        }
        struct Book_Node *point=book_catagory[cat_num].head;
        while (point!=NULL){
            if(point->book_number==book_num){
                break;
            }
            point=point->next;
        }
        if(point==NULL){
            printf("未查询到这本书。\n");

        }
        if(point->borrow_number==0){
            printf("无借阅用户，不能返还。\n");
            continue_question(&is_done);
            continue;
        }
        point->borrow_number--;point->storage_now++;
        printf("返还成功。借阅量为%d，库存为%d\n",point->borrow_number,point->storage_now);
        continue_question(&is_done);
    }
}