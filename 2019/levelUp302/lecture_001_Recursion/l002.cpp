#include <iostream>
#include <vector>

using namespace std;

vector<string> mazepath_HV_01(int sr, int sc, int er, int ec)
{
    if (sr == er && sc == ec)
    {
        vector<string> base;
        base.push_back("");
        return base;
    }
    vector<string> myAns;
    if (sc + 1 <= ec)
    {
        vector<string> Hori = mazepath_HV_01(sr, sc + 1, er, ec);
        for (string s : Hori)
            myAns.push_back("H" + s);
    }

    if (sr + 1 <= er)
    {
        vector<string> Verti = mazepath_HV_01(sr + 1, sc, er, ec);
        for (string s : Verti)
            myAns.push_back("V" + s);
    }
    return myAns;
}

vector<string> mazepath_HVD_01(int sr, int sc, int er, int ec)
{
    if (sr == er && sc == ec)
    {
        vector<string> base;
        base.push_back("");
        return base;
    }
    vector<string> myAns;
    if (sc + 1 <= ec)
    {
        vector<string> Hori = mazepath_HVD_01(sr, sc + 1, er, ec);
        for (string s : Hori)
            myAns.push_back("H" + s);
    }

    if (sc + 1 <= ec && sr + 1 <= er)
    {
        vector<string> Diag = mazepath_HVD_01(sr + 1, sc + 1, er, ec);
        for (string s : Diag)
            myAns.push_back("D" + s);
    }

    if (sr + 1 <= er)
    {
        vector<string> Verti = mazepath_HVD_01(sr + 1, sc, er, ec);
        for (string s : Verti)
            myAns.push_back("V" + s);
    }

    return myAns;
}

vector<string> mazepath_multiHVD_01(int sr, int sc, int er, int ec)
{
    if (sr == er && sc == ec)
    {
        vector<string> base;
        base.push_back("");
        return base;
    }

    vector<string> myAns;
    for (int jump = 1; sc + jump <= ec; jump++)
    {
        vector<string> Hori = mazepath_multiHVD_01(sr, sc + jump, er, ec);
        for (string s : Hori)
            myAns.push_back("H" + to_string(jump) + s);
    }

    for (int jump = 1; sc + jump <= ec && sr + jump <= er; jump++)
    {
        vector<string> Diag = mazepath_multiHVD_01(sr + jump, sc + jump, er, ec);
        for (string s : Diag)
            myAns.push_back("D" + to_string(jump) + s);
    }
    for (int jump = 1; sr + jump <= er; jump++)
    {
        vector<string> Verti = mazepath_multiHVD_01(sr + jump, sc, er, ec);
        for (string s : Verti)
            myAns.push_back("V" + to_string(jump) + s);
    }

    return myAns;
}

int mazepath_HV_02(int sr, int sc, int er, int ec, string ans)
{
    if (sr == er && sc == ec)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;
    if (sc + 1 <= ec)
        count += mazepath_HV_02(sr, sc + 1, er, ec, ans + "H");
    if (sr + 1 <= er)
        count += mazepath_HV_02(sr + 1, sc, er, ec, ans + "V");

    return count;
}

int mazepath_HVD_02(int sr, int sc, int er, int ec, string ans)
{
    if (sr == er && sc == ec)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;
    if (sc + 1 <= ec)
        count += mazepath_HVD_02(sr + 0, sc + 1, er, ec, ans + "H");
    if (sc + 1 <= ec && sr + 1 <= er)
        count += mazepath_HVD_02(sr + 1, sc + 1, er, ec, ans + "D");
    if (sr + 1 <= er)
        count += mazepath_HVD_02(sr + 1, sc + 0, er, ec, ans + "V");

    return count;
}

int mazepath_multiHVD_02(int sr, int sc, int er, int ec, string ans)
{
    if (sr == er && sc == ec)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;
    for (int jump = 1; sc + jump <= ec; jump++)
        count += mazepath_multiHVD_02(sr + jump * 0, sc + jump * 1, er, ec, ans + "H" + to_string(jump));

    for (int jump = 1; sc + jump <= ec && sr + jump <= er; jump++)
        count += mazepath_multiHVD_02(sr + jump * 1, sc + jump * 1, er, ec, ans + "D" + to_string(jump));

    for (int jump = 1; sr + jump <= er; jump++)
        count += mazepath_multiHVD_02(sr + jump, sc, er, ec, ans + "V" + to_string(jump));

    return count;
}

vector<vector<int>> dir = {{0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}};
vector<string> dirN = {"R", "E", "U", "N", "L", "W", "D", "S"};

// vector<vector<int>> dir = {{0, 1}, {1, 0}, {1, 1}};
// vector<string> dirN = {"H", "V", "D"};

bool isValid(int r, int c, vector<vector<int>> &board)
{
    if (r < 0 || c < 0 || r >= board.size() || c >= board[0].size() || board[r][c] == 0 || board[r][c] == 2)
        return false;

    return true;
}

int floodFill(int sr, int sc, int er, int ec, vector<vector<int>> &board, int rad, string ans)
{
    if (sr == er && sc == ec)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;
    board[sr][sc] = 2;

    for (int d = 0; d < dir.size(); d++)
    {
        for (int mag = 1; mag <= rad; mag++)
        {
            int r = sr + mag * dir[d][0];
            int c = sc + mag * dir[d][1];
            if (isValid(r, c, board))
                // count += floodFill(r, c, er, ec, board, rad, ans + dirN[d] + to_string(mag));
                count += floodFill(r, c, er, ec, board, rad, ans + dirN[d]);
        }
    }

    board[sr][sc] = 1;
    return count;
}

//leetcode 200.
int numIslands(vector<vector<char>> &arr)
{
    int count = 0;
    for (int r = 0; r < arr.size(); r++)
    {
        for (int c = 0; c < arr[0].size(); c++)
        {
            if (arr[r][c] == '1')
            {
                count++;
                // floodFill(r, c, arr, 1);
            }
        }
    }

    return count;
}

vector<vector<int>> dir_ = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};
bool isValid_(int r, int c, vector<vector<char>> &board)
{
    if (r < 0 || c < 0 || r >= board.size() || c >= board[0].size() || board[r][c] == '0' || board[r][c] == '2')
        return false;

    return true;
}

int dfs(int sr, int sc, vector<vector<char>> &board, int rad)
{
    int count = 0;
    board[sr][sc] = '2';

    for (int d = 0; d < dir.size(); d++)
    {
        for (int mag = 1; mag <= rad; mag++)
        {
            int r = sr + mag * dir_[d][0];
            int c = sc + mag * dir_[d][1];
            if (isValid_(r, c, board))
                count += dfs(r, c, board, rad);
        }
    }

    // board[sr][sc] = 1;
    return count;
}

void mazePathSet()
{
    int sr = 0, sc = 0, er = 3, ec = 3;
    // vector<string> ans;

    // ans= mazepath_HV_01(sr, sc, er, ec);
    // ans = mazepath_HVD_01(sr, sc, er, ec);
    // ans = mazepath_multiHVD_01(sr, sc, er, ec);

    // cout << mazepath_HV_02(sr, sc, er, ec, "") << endl;
    // cout << mazepath_HVD_02(sr, sc, er, ec, "") << endl;
    // cout << mazepath_multiHVD_02(sr, sc, er, ec, "") << endl;

    vector<vector<int>> board(er + 1, vector<int>(ec + 1, 1));
    // int rad = max(er, ec);
    int rad = 1;
    cout << floodFill(sr, sc, er, ec, board, rad, "") << endl;

    // for (string s : ans)
    // {
    //     cout << s << " ";
    // }
}

vector<vector<int>> subset_(vector<int> &arr, int vidx, vector<int> &list)
{
    if (vidx == arr.size())
    {
        vector<vector<int>> base;
        vector<int> ll(list);
        base.push_back(ll);
        return base;
    }

    vector<vector<int>> ans;

    vector<vector<int>> left = subset_(arr, vidx + 1, list);
    for (vector<int> e : left)
        ans.push_back(e);

    list.push_back(arr[vidx]);
    vector<vector<int>> right = subset_(arr, vidx + 1, list);
    for (auto e : right)
        ans.push_back(e);
    list.pop_back();

    return ans;
}

//leetcode 78
vector<vector<int>> subsets(vector<int> &nums)
{
    vector<int> list;
    return subset_(nums, 0, list);
}

//queenSet.=====================================================

int combinationQueen1D(vector<bool> &boxes, int qpsf, int tnq, int idx, string ans)
{ //qpsf : queen place so far, tnq: total no of queen
    if (qpsf == tnq)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;
    for (int i = idx; i < boxes.size(); i++)
    {
        count += combinationQueen1D(boxes, qpsf + 1, tnq, i + 1, ans + "B" + to_string(i) + "Q" + to_string(qpsf) + " ");
    }
    return count;
}

int permutationQueen1D(vector<bool> &boxes, int qpsf, int tnq, string ans)
{ //qpsf : queen place so far, tnq: total no of queen
    if (qpsf == tnq)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;
    for (int i = 0; i < boxes.size(); i++)
    {
        if (!boxes[i])
        {
            boxes[i] = true;
            count += permutationQueen1D(boxes, qpsf + 1, tnq, ans + "B" + to_string(i) + "Q" + to_string(qpsf) + " ");
            boxes[i] = false;
        }
    }
    return count;
}

int permutationQueen1D_sub(vector<bool> &boxes, int idx, int qpsf, int tnq, string ans)
{ //qpsf : queen place so far, tnq: total no of queen
    if (qpsf == tnq)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;
    if (!boxes[idx])
    {
        boxes[idx] = true;
        count += permutationQueen1D_sub(boxes, 0, qpsf + 1, tnq, ans + "B" + to_string(idx) + "Q" + to_string(qpsf) + " ");
        boxes[idx] = false;
    }
    count += permutationQueen1D_sub(boxes, idx + 1, qpsf, tnq, ans);

    return count;
}

int combinationQueen2D(vector<vector<bool>> &boxes, int qpsf, int tnq, int idx, string ans)
{ //qpsf : queen place so far, tnq: total no of queen
    if (qpsf == tnq)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;
    for (int i = idx; i < boxes.size() * boxes[0].size(); i++)
    {
        int x = i / boxes[0].size();
        int y = i % boxes[0].size();
        count += combinationQueen2D(boxes, qpsf + 1, tnq, i + 1, ans + "(" + to_string(x) + ", " + to_string(y) + ") ");
    }
    return count;
}

int permutationQueen2D(vector<vector<bool>> &boxes, int qpsf, int tnq, string ans) // boolean[][]
{                                                                                  //qpsf : queen place so far, tnq: total no of queen
    if (qpsf == tnq)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;
    for (int i = 0; i < boxes.size() * boxes[0].size(); i++)
    {
        int x = i / boxes[0].size();
        int y = i % boxes[0].size();
        if (!boxes[x][y])
        {
            boxes[x][y] = true;
            count += permutationQueen2D(boxes, qpsf + 1, tnq, ans + "(" + to_string(x) + ", " + to_string(y) + ") ");
            boxes[x][y] = false;
        }
    }
    return count;
}

//Nqueen.==================================================================

bool isSafeToPlaceQueen(vector<vector<bool>> &boxes, int row, int col)
{
    vector<vector<int>> Qdir = {{0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

    for (int d = 0; d < Qdir.size(); d++)
    {
        for (int rad = 1; rad <= boxes.size(); rad++)
        {
            int r = row + rad * Qdir[d][0];
            int c = col + rad * Qdir[d][1];

            if (r >= 0 && c >= 0 && r < boxes.size() && c < boxes.size())
            {
                if (boxes[r][c])
                    return false;
            }
            else
                break;
        }
    }

    return true;
}

int Nqueen_01(vector<vector<bool>> &boxes, int tnq, int idx, string ans)
{ //qpsf : queen place so far, tnq: total no of queen
    if (tnq == 0)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;
    for (int i = idx; i < boxes.size() * boxes[0].size(); i++)
    {
        int x = i / boxes[0].size();
        int y = i % boxes[0].size();
        if (isSafeToPlaceQueen(boxes, x, y))
        {
            boxes[x][y] = true;
            count += Nqueen_01(boxes, tnq - 1, i + 1, ans + "(" + to_string(x) + ", " + to_string(y) + ") ");
            boxes[x][y] = false;
        }
    }
    return count;
}

// for java:
// static boolean[] rowA;
// static boolean[] colA;
// static boolean[] diag;
// static boolean[] adiag;

vector<bool> rowA;
vector<bool> colA;
vector<bool> diag;  // n+m-1 = 7
vector<bool> adiag; // n+m-1 = 7

int Nqueen_02(int n, int m, int tnq, int idx, string ans)
{ //qpsf : queen place so far, tnq: total no of queen
    if (tnq == 0)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;
    for (int i = idx; i < n * m; i++)
    {
        int x = i / m;
        int y = i % m;
        if (!rowA[x] && !colA[y] && !diag[x - y + m - 1] && !adiag[x + y])
        {
            rowA[x] = true;
            colA[y] = true;
            diag[x - y + m - 1] = true;
            adiag[x + y] = true;

            count += Nqueen_02(n, m, tnq - 1, i + 1, ans + "(" + to_string(x) + ", " + to_string(y) + ") ");

            rowA[x] = false;
            colA[y] = false;
            diag[x - y + m - 1] = false;
            adiag[x + y] = false;
        }
    }
    return count;
}

int rowA_ = 0;
int colA_ = 0;
int diag_ = 0;
int adiag_ = 0;

int Nqueen_03(int n, int m, int tnq, int idx, string ans)
{ //qpsf : queen place so far, tnq: total no of queen
    if (tnq == 0)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;
    for (int i = idx; i < n * m; i++)
    {
        int x = i / m;
        int y = i % m;

        if (!(rowA_ & (1 << x)) && !(colA_ & (1 << y)) && !(diag_ & (1 << (x - y + m - 1))) && !(adiag_ & (1 << (x + y))))
        {
            rowA_ ^= (1 << x);
            colA_ ^= (1 << y);
            diag_ ^= (1 << (x - y + m - 1));
            adiag_ ^= (1 << (x + y));

            count += Nqueen_03(n, m, tnq - 1, i + 1, ans + "(" + to_string(x) + ", " + to_string(y) + ") ");

            rowA_ ^= (1 << x);
            colA_ ^= (1 << y);
            diag_ ^= (1 << (x - y + m - 1));
            adiag_ ^= (1 << (x + y));
        }
    }
    return count;
}

int Nqueen_03_sub(int n, int m, int tnq, int idx, string ans)
{ //qpsf : queen place so far, tnq: total no of queen
    if (idx == n * m || tnq == 0)
    {
        if (tnq == 0)
        {
            cout << ans << endl;
            return 1;
        }
        return 0;
    }

    int count = 0;
    int x = idx / m;
    int y = idx % m;

    if (!(rowA_ & (1 << x)) && !(colA_ & (1 << y)) && !(diag_ & (1 << (x - y + m - 1))) && !(adiag_ & (1 << (x + y))))
    {
        rowA_ ^= (1 << x);
        colA_ ^= (1 << y);
        diag_ ^= (1 << (x - y + m - 1));
        adiag_ ^= (1 << (x + y));

        count += Nqueen_03_sub(n, m, tnq - 1, idx + 1, ans + "(" + to_string(x) + ", " + to_string(y) + ") ");

        rowA_ ^= (1 << x);
        colA_ ^= (1 << y);
        diag_ ^= (1 << (x - y + m - 1));
        adiag_ ^= (1 << (x + y));
    }
    count += Nqueen_03_sub(n, m, tnq, idx + 1, ans);

    return count;
}

int Nqueen_04(int n, int m, int tnq, int r, string ans) // n means houses and m means rooms
{                                                       //qpsf : queen place so far, tnq: total no of queen
    if (r == n || tnq == 0)
    {
        if (tnq == 0)
        {
            cout << ans << endl;
            return 1;
        }
        return 0;
    }

    int count = 0;
    for (int i = 0; i < m; i++)
    {
        int x = r;
        int y = i;

        if (!(rowA_ & (1 << x)) && !(colA_ & (1 << y)) && !(diag_ & (1 << (x - y + m - 1))) && !(adiag_ & (1 << (x + y))))
        {
            rowA_ ^= (1 << x);
            colA_ ^= (1 << y);
            diag_ ^= (1 << (x - y + m - 1));
            adiag_ ^= (1 << (x + y));

            count += Nqueen_04(n, m, tnq - 1, r + 1, ans + "(" + to_string(x) + ", " + to_string(y) + ") ");

            rowA_ ^= (1 << x);
            colA_ ^= (1 << y);
            diag_ ^= (1 << (x - y + m - 1));
            adiag_ ^= (1 << (x + y));
        }
    }
    return count;
}

int Nqueen_04_sub(int n, int m, int tnq, int r, string ans) // n means houses and m means rooms
{                                                           //qpsf : queen place so far, tnq: total no of queen
    if (r == n || tnq == 0)
    {
        if (tnq == 0)
        {
            cout << ans << endl;
            return 1;
        }
        return 0;
    }

    int count = 0;
    for (int i = 0; i < m; i++)
    {
        int x = r;
        int y = i;

        if (!(rowA_ & (1 << x)) && !(colA_ & (1 << y)) && !(diag_ & (1 << (x - y + m - 1))) && !(adiag_ & (1 << (x + y))))
        {
            rowA_ ^= (1 << x);
            colA_ ^= (1 << y);
            diag_ ^= (1 << (x - y + m - 1));
            adiag_ ^= (1 << (x + y));

            count += Nqueen_04_sub(n, m, tnq - 1, r + 1, ans + "(" + to_string(x) + ", " + to_string(y) + ") ");

            rowA_ ^= (1 << x);
            colA_ ^= (1 << y);
            diag_ ^= (1 << (x - y + m - 1));
            adiag_ ^= (1 << (x + y));
        }
    }
    count += Nqueen_04_sub(n, m, tnq, r + 1, ans);
    return count;
}


//===================================================================

void queenSet()
{
    vector<bool> boxes(25, false);
    cout << combinationQueen1D(boxes, 0, 3, 0, "");
    // cout << permutationQueen1D(boxes, 0, 3, "");

    // vector<vector<bool>> boxes(5,vector<bool>(5,false));
    // cout << combinationQueen2D(boxes, 0, 3, 0, "");
    // cout << permutationQueen2D(boxes, 0, 3, "");
}

void Nqueen()
{
    // rowA=new boolean[n];

    int n = 10;
    int m = 4;
    rowA.resize(n, false);
    colA.resize(m, false);
    diag.resize(n + m - 1, false);
    adiag.resize(n + m - 1, false);

    vector<vector<bool>> boxes(n, vector<bool>(m, false));
    // cout << Nqueen_01(boxes, n, 0, "") << endl;
    // cout << Nqueen_02(n, m, n, 0, "") << endl;
    // cout << Nqueen_03(n, m, n, 0, "") << endl;
    // cout << Nqueen_04(n, m, 4, 0, "") << endl;
    // cout << Nqueen_03_sub(n, m, 4, 0, "") << endl;
    cout << Nqueen_04_sub(n, m, 4, 0, "") << endl;
}


int main()
{
    // mazePathSet();
    // queenSet();
    Nqueen();

    return 0;
}
