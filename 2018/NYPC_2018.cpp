#include < iostream >
#include < string >
#include < vector >
#include < algorithm >
 
using namespace std;
 
// 팀별 선수 수
const int n = 4;
const int score[] = { 10, 8, 6, 5, 4, 3, 2, 1 };
 
// 선수 클래스
class CPlayer
{
public:
    CPlayer(bool t = true, int ra = 0, double rec = 0, int s = 0)
    {
        team = t;
        rank = ra;
        record = rec;
        score = s;
    }
    ~CPlayer() {}
 
public:
    bool team; // red : true, blue : false
    int rank;
    double record;
    int score;
};
 
// 게임 클래스
class CGame
{
public:
    CGame(bool t = true, bool win = true) :players(n * 2)
    {
        type = t;
        winner = win;
        redScore = blueScore = 0;
    }
    ~CGame() {}
 
public:
    bool type;// item:true, speed:false
    bool winner;// red : true, blue : false
    vector<CPlayer> players;
    int redScore, blueScore;
 
    static bool sortRank(const CPlayer& p1, const CPlayer& p2)
    {
        return p1.record < p2.record;
    }
    void update()
    {
        //먼저 기록 정렬
        std::sort(players.begin(), players.end(), sortRank);
 
        int order = 0;
        double bestRec = 0;
 
        vector<CPlayer>::iterator itr;
        for (itr = players.begin(); itr != players.end(); ++itr)
        {
            // 1등 기록 
            if (order == 0)
                bestRec = itr->record;
 
            // 1등기록과 10초이상 차이나면 0점
            if (itr->record >= bestRec + 10.0)
                itr->score = 0;
            else
                itr->score = score[order];
 
            // 팀별 점수 합산
            if (itr->team)
                redScore += itr->score;
            else
                blueScore += itr->score;
 
            order++;
            itr->rank = order;
 
            //cout << itr->team << " " << itr->rank << " " << itr->record << " " << itr->score << endl;            
        }
 
    }
    string getWinner()
    {
        string winner;
        // item
        if (type == true)
        {
            if (players.at(0).team == true)
                winner = "red";
            else
                winner = "blue";
        }
        else // speed
        {
            if (redScore == blueScore)
            {
                if (players.at(0).team)
                    winner = "red";
                else
                    winner = "blue";
            }
            else if (redScore > blueScore)
                winner = "red";
            else
                winner = "blue";
        }
        return winner;
    }
    static double getTimeRecord(const string& strRec, char c)
    {
        string str;
        double fRec = 0;
        int token = strRec.find(c);
        str = strRec.substr(0, token);
        fRec = atof(str.c_str());
        str = strRec.substr(++token, strRec.length());
        fRec = (fRec*60.0 + atof(str.c_str()));
 
        return fRec;
    }
};
 
 
int main()
{
    // 테스트 케이스의 수
    int t = 0;
    cin >> t;
 
    // 게임 기록 입력
    vector<CGame> game(t);
    for (int i = 0; i < t; i++)
    {
        string type;
        cin >> type;
 
        // 게임종류
        if (type == "item")
            game.at(i).type = true;
        else
            game.at(i).type = false;
 
        // 팀종류, 선수기록 저장
        for (int k = 0; k < n * 2; k++)
        {
            string team, rec;
            cin >> team >> rec;
 
            game.at(i).players.at(k).record = CGame::getTimeRecord(rec, ':');
 
            if (team == "red")
                game.at(i).players.at(k).team = true; // red            
            else
                game.at(i).players.at(k).team = false; // red
        }
    }
 
    // 게임 결과 출력
    vector<CGame>::iterator itr;
    for (itr = game.begin(); itr != game.end(); ++itr)
    {
        // 게임결과 입력값 정렬, 점수 및 순위 계산
        itr->update();
        cout << itr->getWinner() << endl;
    }
 
    return 0;
}