#include "Music.h"
#include "string.h"
#include <algorithm>

vector<string> split(const string& str, const string& delim) {
	vector<string> res;
	if("" == str) return res;
	char *strs = new char[str.length() + 1] ; 
	strcpy(strs, str.c_str()); 
	char *d = new char[delim.length() + 1];
	strcpy(d, delim.c_str());
 
	char *p = strtok(strs, d);
	while(p) {
		string s = p; 
		res.push_back(s); 
		p = strtok(NULL, d);
	}
	return res;
}

class MusicBoard{
    vector<Music> musics;
public:
    MusicBoard(){}
    MusicBoard(vector<string> music_list){
        for(int i=0;i<music_list.size();i++){
            vector<string> tmp = split(music_list[i], "|");
            Music m(tmp[0], tmp[1], stoi(tmp[2]), tmp[3], tmp[4]);
            musics.push_back(m);
        }
    }
    bool addMusic(Music& music){
        for(int i=0;i<musics.size();i++){
            if(musics[i].getName() == music.getName() && musics[i].getSinger() == music.getSinger()){
                return false;
            }
        }
        musics.push_back(music);
        return true;
    }
    void sortMusic(string label){
        if(label == "commentCount"){
            sort(musics.begin(), musics.end(), [](Music a, Music b)->bool{return a.getCount()>b.getCount();});
        }else if(label == "releaseDate"){
            sort(musics.begin(), musics.end(), [](Music a, Music b)->bool{return a.dateLessthan(b);});
        }
    }
    Music getByIndex(int index){
        return musics[index];
    }
    MusicBoard filter(string nation){
        MusicBoard res;
        copy_if(musics.begin(), musics.end(), back_inserter(res.musics), [&](Music &a)->bool{return a.getNation()==nation;});
        return res;
    }
};