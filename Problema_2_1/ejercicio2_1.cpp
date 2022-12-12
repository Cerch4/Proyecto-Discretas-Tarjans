#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;

typedef pair<int,int> myPair;
class Graph{
    private:
        int V;
        list<myPair> *adj;
        vector<string> keys;
        map<string, pair<int, string>> teselia;
        vector<vector<int>> *adjacentMatrix;
        vector<vector<int>> *prevMatrix;
        map<string, int> Teselia_;
        int k = 0;
    public:
        Graph(int V);
        void addEdge(int u,int v,int w);
        void shortestPath(int src);
        void getAdjacentMatrix();
        void printPath(string , string);
        void mappingTeselia(vector<string> );
        void addWeights(vector<tuple<string, string, int>>);
};
Graph::Graph(int V_){
    V = V_;
    adj = new list<myPair>[V];
    adjacentMatrix = new vector<vector<int>>[V];
    prevMatrix = new vector<vector<int>>[V];
}

void Graph::addEdge(int u,int v,int w){
    adj[u].push_back({v,w});
    adj[v].push_back({u,w});
}

void Graph::mappingTeselia(vector<string> keys_){
    keys = keys_;
    for(int i = 0; i < V; i++){
        Teselia_.insert({keys_[i], i});
    }
}
//Dijkstra
void Graph::shortestPath(int src){

    priority_queue<myPair,vector<myPair>,greater<myPair> > pq;
    vector<int> dist(V,INF);
    vector<int> prev(V);
    dist[src] = 0;
    prev[src] = -1;
    list<myPair>::iterator it;

    pq.push({0,src});

    while(!pq.empty()){
        int u = pq.top().second;
        pq.pop();

        for(it = adj[u].begin();it!=adj[u].end();++it){
            int v = it->first;
            int w = it->second;
            if(dist[v] > dist[u] + w){

                dist[v] = dist[u] + w;
                prev[v] = u;
                pq.push({dist[v],v});
            }
        }
    }
    for(int i=0;i<V;i++){
        cout << i << " - " << dist[i] <<" - prev - "<< prev[i]<< endl;
    }
}

void Graph::getAdjacentMatrix(){

    for(int i = 0; i<V; i++){
        priority_queue<myPair,vector<myPair>,greater<myPair> > pq;
        vector<int> dist(V,INF);
        vector<int> prev(V);
        int src = i;
        dist[src] = 0;
        prev[src] = -1;
        list<myPair>::iterator it;

        pq.push({0,src});

        while(!pq.empty()){
            int u = pq.top().second;
            pq.pop();

            for(it = adj[u].begin();it!=adj[u].end();++it){
                int v = it->first;
                int w = it->second;
                if(dist[v] > dist[u] + w){

                    dist[v] = dist[u] + w;
                    prev[v] = u;
                    pq.push({dist[v],v});
                }
            }
        }
        adjacentMatrix[i].push_back(dist);
        prevMatrix[i].push_back(prev);
    }
}
void Graph::printPath(string u_, string v_){
    int u = Teselia_[u_], v = Teselia_[v_];

    int aux = v;
    vector<int> path;
    while(aux != -1){
        path.push_back(aux);
        auto it = prevMatrix[u][0].begin() + aux;
        aux = *it;
    }
    if(v_=="L1"){
        for(int i = path.size()-1; i>=0; i--){
        cout<<keys[path[i]]<<endl;
        }
    }
    else{
        for(int i = path.size()-1; i>0; i--){
        cout<<keys[path[i]]<<endl;
        }
    }
}

void Graph::addWeights(vector<tuple<string, string, int>> weights){
    for(vector<tuple<string, string, int>>::iterator it = weights.begin(); it != weights.end(); it++){
        string aux1 = get<0>(*it);
        string aux2 = get<1>(*it);
        addEdge(Teselia_[aux1], Teselia_[aux2], get<2>(*it));
    }
}

int main(){
    vector<string> keys;
    vector<tuple<string, string, int>> weights_;
    vector<string> route;
    int n, m, w, k;
    string aux, aux2;

    fstream file("Bianca.txt", ios::in);
    if (file.is_open()) {
        file>>n;
        for(int i = 0; i<n; i++){
            file>>aux;
            keys.push_back(aux);
            }
        file>>m;
        for(int i = 0; i<m; i++){
            file>>aux>>aux2>>w;
            weights_.push_back({aux, aux2, w});
        }
        file>>k;
        route.push_back("A2");
        for(int i = 0; i<k; i++){
            file>>aux;
            route.push_back(aux);
        }
        route.push_back("L1");
        }
    file.close();

    Graph graphTeselia(n);
    graphTeselia.mappingTeselia(keys);
    graphTeselia.addWeights(weights_);
    cout<<"-------RECORRIDO TOTAL-------"<<endl;
    graphTeselia.getAdjacentMatrix();
    for(auto it = route.begin(); it!= route.end()-1; it++){
        graphTeselia.printPath(*it,*(it+1));
    }
    return 0;
}
