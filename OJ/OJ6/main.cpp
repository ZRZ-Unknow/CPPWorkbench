#include "Music.h"
#include "MusicBoard.h"



int main(){
    string music001 = "Crow|Vae|64970|2021-05-07|China";
    string music002 = "You Belong With Me|Taylor Swift|2809|2009-04-18|America";
    vector<string> musicList;
    musicList.push_back(music001);
    musicList.push_back(music002);
    MusicBoard board1(musicList);
    
    MusicBoard board2;
    Music music1("Crow","Vae",64970,"2021-05-07","China");
    Music music2("You Belong With Me","Taylor Swift",2809,"2009-04-18","America");
    Music music3("Rice Field","Jay Chou",47516,"2008-10-15","China");
    //在榜单中添加音乐
    board2.addMusic(music1);
    board2.addMusic(music2);
    board2.addMusic(music3);
    //按音乐评论人数排序,排序后,榜单board2中榜首为music1
    board2.sortMusic("commentCount");
    //获取排序后,榜单中索引为1的音乐
    cout<<board2.getByIndex(1)<<endl;
    board2.sortMusic("releaseDate");
    cout<<board2.getByIndex(0)<<endl;

    MusicBoard board3;
    board3.addMusic(music1);
    board3.addMusic(music2);
    board3.addMusic(music3);
    MusicBoard board4 = board3.filter("China");
    cout<<board4.getByIndex(0)<<endl;
    return 0;
}