#include <iostream>
#include "CareerTalk.h"
#include "ReservationTable.h"
using namespace std;


int main(){
    CareerTalk tencentTalk("Tencent", 2, 9, 11);// 查询信息
    int day=tencentTalk.GetDay();
    int start_time=tencentTalk.GetStartTime();
    int end_time=tencentTalk.GetEndTime();// 修改宣讲会信息，调整到周四11:00-13:00
    tencentTalk.AdjustInfo(4, 11, 13);// 开放预约通道
    tencentTalk.OpenAccess();// 查询预约通道是否开启
    bool isOpen=tencentTalk.IsOpen();// 给宣讲会打8分和10分
    tencentTalk.Comment(9);
    tencentTalk.Comment(10);// 获取宣讲会均分（预期为9分）
    float avgScore=tencentTalk.GetScore();
    tencentTalk.CloseAccess();
    cout<<day<<" "<<start_time<<" "<<end_time<<" "<<isOpen<<" "<<avgScore<<endl;

    CareerTalk talk1=CareerTalk("Tencent QQ", 1, 8, 10);
    CareerTalk talk2=CareerTalk("Alibaba", 2, 14, 16);
    CareerTalk talk3=CareerTalk("Baidu", 3, 12, 15);
    talk1.OpenAccess();
    talk2.OpenAccess();// 初始化对象
    ReservationTable table;// 预约宣讲会，根据开放预约与否会有不同的结果
    bool addState1=table.AddTalk(&talk1);
    bool addState2=table.AddTalk(&talk2);
    bool addState3=table.AddTalk(&talk3);// 查询周一9:00-10:00的宣讲会信息
    CareerTalk *queryTalk=table.QueryTalk(1, 9);// 查询周一预约了几场宣讲会
    int talkNum=table.TalksInADay(1);// 调整宣讲会时间，如果冲突则自动取消预约被改动的宣讲会，不冲突则将table中的宣讲会信息更新
    talk1.AdjustInfo(4, 15, 17);
    bool adjustState=table.AdjustTalk(&talk1);
    talk1.AdjustInfo(2, 15, 17);
    adjustState=table.AdjustTalk(&talk1);// 取消预约
    bool cancelState=table.CancelTalk(&talk2);
    cout<<addState1<<" "<<addState2<<" "<<addState3<<" "<<talkNum<<" "<<adjustState<<" "<<cancelState<<endl;
    return 0;
}