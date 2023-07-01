//
// Created by 谷岩 on 2022/12/21.
//
#include "option.h"
#include "data_list.h"
#include "data_io.h"
int main() {
    catagory_init();//初始化分类
    data_import();  //导入数据
    while (1){
        run(); //运行界面
    }
}
