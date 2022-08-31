#include <iostream>
#include <queue>

const int N = 55;
int cost[4][N][N];

int mp[N][N];

struct nod{
	int x,y,dir;
	nod(int dir,int x,int y):x(x),y(y),dir(dir){}

};

int X0,Y0,X1,Y1,Dir,n,m;

int dx[]={-1,0,1,0};
int dy[]={0,1,0,-1};

//syxz

bool inmp(int x,int y){
	return x>0&&x<=n&&y>0&&y<=m;
}

bool inrob(int x,int y){
	return x>0&&x<n&&y>0&&y<m;
}

bool check(int x,int y){
	for(int i = 0;i <= 1; ++i){
		for(int j = 0; j <= 1; ++j){
			int nx = x + i, ny = j + y;
			if(inmp(nx,ny)){
				if(mp[nx][ny])return false;
			}
		}
	}
	return true;
}

void bfs(){
	std::queue<nod>q;
	q.emplace(Dir,X0,Y0);
	cost[Dir][X0][Y0] = 0;
	while(!q.empty()){
		auto now = q.front();
		q.pop();
		int x = now.x,y = now.y,dir = now.dir;
		int lefDir = (dir + 3) % 4;
		int rigDir = (dir + 1) % 4;
		// std::cerr<<x<<' '<<y<<' '<<dir<<std::endl;
		if(x==X1&&y==Y1){
			std::cout<<cost[dir][x][y]<<std::endl;
			return;
		}
		if(cost[lefDir][x][y]==-1){
			q.emplace(lefDir,x,y);
			cost[lefDir][x][y]=cost[dir][x][y]+1;
		}
		if(cost[rigDir][x][y]==-1){
			q.emplace(rigDir,x,y);
			cost[rigDir][x][y]=cost[dir][x][y]+1;
		}
		for(int stp = 1;stp <= 3;++stp){
			int nx = x + stp * dx[dir],ny = y + stp * dy[dir];
			if(inrob(nx,ny)){
				if(check(nx,ny)){
					if(cost[dir][nx][ny]==-1){
						cost[dir][nx][ny]=cost[dir][x][y]+1;
						q.emplace(dir,nx,ny);
					}else break;
				}else break;
			}else break;
		}
	}
	std::cout<<-1<<std::endl;
}

int main(){
	std::cin>>n>>m;
	memset(cost,-1,sizeof cost);
	for(int i = 1; i <= n; ++i){
		for(int j = 1; j <= m;++j){
			std::cin>>mp[i][j];
		}
	}
	char d;
	std::cin >> X0 >> Y0 >> X1 >> Y1 >> d;
	if(d=='N')Dir = 0;
	if(d=='E')Dir = 1;
	if(d=='S')Dir = 2;
	if(d=='W')Dir = 3;
	bfs();
}