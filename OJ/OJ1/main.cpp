#include <iostream>
#include "merchandise.h"
#include "merchandise_list.h"
#include "user.h"
using namespace std;




int main(){
    Merchandise mer_pen = Merchandise("pen", 2); 
    Merchandise mer_apple = Merchandise("apple", 3);
    cout<<mer_pen.GetMerchandiseName()<<endl; //返回商品名
    cout<<mer_pen.GetMerchandisePrice()<<endl; //返回商品价格
    
    MerchandiseList merchandise_list; // 创建一个merchandise_list对象
    merchandise_list.AddRecord(&mer_pen, 8);
    merchandise_list.ModifyRecord(&mer_pen, 7);
    cout<<merchandise_list.FindRecord(&mer_pen)<<endl;
    cout<<merchandise_list.DeleteRecord(&mer_pen)<<endl;
    cout<<merchandise_list.DeleteRecord(&mer_apple)<<endl;
    
    User user_Tom = User("Tom"); // 创建一个User对象,用户名为Tom
    user_Tom.BrowseMerchandise(&mer_pen); // 浏览商品pen一次
    user_Tom.GetBrowseHistory(); // 返回用户Tom的浏览记录
    user_Tom.BuyMerchandise(&mer_apple, 6); // 购买6个apple
    user_Tom.GetBuyHistory(); // 返回用户Tom的购买记录
    user_Tom.BuyMerchandise(&mer_apple, 2); // 再次购买2个苹果
    user_Tom.GetBuyHistory(); // 返回再次购买后的购买记录
    return 0;
}