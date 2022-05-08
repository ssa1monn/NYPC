#include < iostream >
#include < string >
#include < vector >
#include < algorithm >
 
using namespace std;
 
// ���� ���� ��
const int n = 4;
const int score[] = { 10, 8, 6, 5, 4, 3, 2, 1 };
 
// ���� Ŭ����
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
 
// ���� Ŭ����
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
        //���� ��� ����
        std::sort(players.begin(), players.end(), sortRank);
 
        int order = 0;
        double bestRec = 0;
 
        vector<CPlayer>::iterator itr;
        for (itr = players.begin(); itr != players.end(); ++itr)
        {
            // 1�� ��� 
            if (order == 0)
                bestRec = itr->record;
 
            // 1���ϰ� 10���̻� ���̳��� 0��
            if (itr->record >= bestRec + 10.0)
                itr->score = 0;
            else
                itr->score = score[order];
 
            // ���� ���� �ջ�
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
    // �׽�Ʈ ���̽��� ��
    int t = 0;
    cin >> t;
 
    // ���� ��� �Է�
    vector<CGame> game(t);
    for (int i = 0; i < t; i++)
    {
        string type;
        cin >> type;
 
        // ��������
        if (type == "item")
            game.at(i).type = true;
        else
            game.at(i).type = false;
 
        // ������, ������� ����
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
 
    // ���� ��� ���
    vector<CGame>::iterator itr;
    for (itr = game.begin(); itr != game.end(); ++itr)
    {
        // ���Ӱ�� �Է°� ����, ���� �� ���� ���
        itr->update();
        cout << itr->getWinner() << endl;
    }
 
    return 0;
}