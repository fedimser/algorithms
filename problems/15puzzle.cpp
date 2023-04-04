// Classic 15 Puzzle, Example of applying A* algorithm.
// Problem: https://vjudge.net/problem/UVA-10181/origin
// Algorithm: https://en.wikipedia.org/wiki/A*_search_algorithm
#include <bits/stdc++.h> // (c) Dmytro Fedoriaka, 2023.
using namespace std;
vector<int>ReadVec(int n){vector<int>a(n);for(int i=0;i<n;i++)cin>>a[i];return a;} 
  
class Board{
 private:
  uint64_t board_; 
  int8_t x0_, y0_;

  Board(uint64_t code, int8_t x0, int8_t y0) {
    board_ = code;
    x0_=x0;
    y0_=y0;

    if (x0_ == -1) {
      for(int i=0;i<16;i++) {
        if(GetTile(i)==0) {
          x0_=i%4;
          y0_=i/4;
          break;
        }
      }
    } 
  } 

 public: 
  static Board FromCode(uint64_t code) {
    return Board(code, -1, -1);
  }

  static Board FromVector(vector<int> tiles) {
    assert(tiles.size() == 16);
    uint64_t code = 0;
    for(int i=0;i<16;i++) {
      assert(0<=tiles[i] && tiles[i]<16);
      code += (((uint64_t)tiles[i])<<(4*i));
    }
    return Board::FromCode(code);
  }

  inline uint64_t GetTile(int id) const {
    return (board_>>(4*id)) & 0b1111;
  }

  inline uint64_t GetTile(int x, int y) const{
    return GetTile(4*y+x);
  }

  bool IsSolvable() {
    int c = 0;
    for(int i=0;i<16;i++) {
      for(int j=i+1;j<16;j++) {
        if (GetTile(i)<GetTile(j))c++;
      }
    }
    return (c+x0_+y0_)%2==1;
  }

  Board MoveEmptyTile(int dx, int dy) const {
    int idx1 = 4*y0_+x0_;
    assert(GetTile(idx1) == 0);
    int idx2 = 4*(y0_+dy) + (x0_+dx);
    uint64_t tile_id = GetTile(idx2);
    return Board(board_ - (tile_id<<(4*idx2)) + (tile_id<<(4*idx1)), x0_+dx, y0_+dy);
  }

  vector<pair<char, Board>> PossibleMoves() const {
    vector<pair<char, Board>> ans;
    if (y0_>0) ans.push_back({'U', MoveEmptyTile(0, -1)});
    if (y0_<3) ans.push_back({'D', MoveEmptyTile(0, +1)});
    if (x0_>0) ans.push_back({'L', MoveEmptyTile(-1, 0)});
    if (x0_<3) ans.push_back({'R', MoveEmptyTile(+1, 0)});
    return ans;
  }

  inline uint64_t GetCode() const {
    return board_;
  }

  // The A* heuristic.
  int h() const {
    int ans=0;
    int cx,cy;
    for(int x=0;x<4;x++) {
      for(int y=0;y<4;y++) {
        int tile = GetTile(x,y);
        if(tile!=0){
          tile--;cx=tile%4;cy=tile/4;
          ans+=abs(cx-x)+abs(cy-y);
        }
      }
    }
    return ans;
  }
}; 

Board SOLVED_BOARD = Board::FromVector({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0});
int LIMIT = 50;

struct AStarData {
  uint64_t prev;
  char move;
  int16_t cost_d;
  int16_t cost_dh; // d+h
};

struct Solver {
  priority_queue<pair<int16_t, uint64_t> > pq;
  unordered_map<uint64_t, AStarData> d;

  string Solve(Board board) {
    if (board.h() == 0) {
      return "";
    }
    
    int16_t init_cost_dh = board.h();
    pq.push({-init_cost_dh, board.GetCode()});
    d[board.GetCode()] = {0, '*', 0, init_cost_dh};

    while(!pq.empty()) {
      int16_t cur_cost_dh = -pq.top().first;
      uint64_t cur_code = pq.top().second;
      Board cur_board = Board::FromCode(cur_code);
      pq.pop();
      int16_t cur_cost_d = d[cur_code].cost_d;

      if(d[cur_code].cost_dh != cur_cost_dh) {
        // outdated entry, no need to explore it.
        continue;
      }

      if (cur_cost_d >= LIMIT) continue;
      
      for(const auto i: cur_board.PossibleMoves()) {
        Board next_board = i.second;
        uint64_t next_board_code = next_board.GetCode();
        int h = next_board.h(); 
        int16_t next_cost_d = cur_cost_d + 1;
        int16_t next_cost_dh = next_cost_d + h;

        // If already in queue with same or better cost, don't put it there again.
        auto it = d.find(next_board_code);
        if (it != d.end() && it->second.cost_dh <= next_cost_dh) {
          continue;
        }  
        
        pq.push(make_pair(-next_cost_dh, next_board_code));
        d[next_board_code] = {cur_code, i.first, next_cost_d, next_cost_dh};
        if (h == 0) {
          assert(next_board_code == SOLVED_BOARD.GetCode());
          goto SOLVED;
        }
      }
    }
    assert(false); // If reached, means no solution found.

SOLVED: 
    string seq = "";
    uint64_t cur = SOLVED_BOARD.GetCode();
    while(cur != board.GetCode()) {
      assert(d.find(cur)!=d.end());
      seq += d[cur].move;
      cur = d[cur].prev;
    }

    reverse(seq.begin(), seq.end());
    return seq;
  }

};

void solve() {
  Board board = Board::FromVector(ReadVec(16));
  if (!board.IsSolvable()) {
    cout << "This puzzle is not solvable." << endl;
  } else {
    cout << Solver().Solve(board) << endl;
  }
}  
 
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); 
  
  int casesNum=1;
  cin>>casesNum;
  for(int caseId = 1; caseId<=casesNum; caseId++) {
  	solve();	
  }
    
  return 0;
}