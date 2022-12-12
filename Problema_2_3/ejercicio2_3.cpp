#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;

typedef pair<int,int> myPair;
class Graph{
    private:
        int V;
        list<int> *adj;
        vector<string> keys;
        map<string, pair<int, string>> teselia;
        map<string, int> Teselia_;
        vector<pair<list<int>::iterator,list<int>::iterator>> toDrop;
        vector<int> adjacentCities;
        int edgesNum = 0;
        int k = 0;

    public:
        Graph(int V);
        void addEdge(int ,int );
        void mappingTeselia(vector<string> );
        void addEdges(vector<pair<string, string>>);
        void printEdges();
        void getPokemonCenters();
};

Graph::Graph(int V_){
    V = V_;
    adj = new list<int>[V];
}

void Graph::addEdge(int u,int v){
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void Graph::mappingTeselia(vector<string> keys_){
    keys = keys_;
    for(int i = 0; i < V; i++){
        Teselia_.insert({keys_[i], i});
    }
}
void Graph::addEdges(vector<pair<string, string>> edges_){
    for(vector<pair<string, string>>::iterator it = edges_.begin(); it != edges_.end(); it++){
        string aux1 = (*it).first;
        string aux2 = (*it).second;
        addEdge(Teselia_[aux1], Teselia_[aux2]);
        edgesNum++;
    }
}
void Graph::printEdges(){
    for(int i = 0; i<V; i++){
        cout<<"EDGE "<<i<<endl;
        for(auto it = adj[i].begin();it!=adj[i].end();++it){
            cout<<*it<<endl;
        }
    }
}
void Graph::getPokemonCenters(){
    for(int i = 0; i<V; i++){
        adjacentCities.push_back(adj[i].size());
    }

    int visited[V] = {0};
    for(int j = 0; j<V; j++){

        int min_ = INF, argMin_ = 0;
        if(visited[j]==1)continue;
        for(int i = 0; i<V; i++){
            if(visited[i] == 1)continue;
            else{
                if(adjacentCities[i]<min_){
                    min_ = adjacentCities[i];
                    argMin_ = i;

                }
            }
        }

        auto argOtherNode = adj[argMin_].begin();
        visited[*argOtherNode]=1;
        for(auto it = adj[*argOtherNode].begin(); it != adj[*argOtherNode].end(); it++){
            if(adj[*it].size()==1){
                visited[*it]=1;
                cout<<keys[*it]<<"->"<<keys[*argOtherNode]<<endl;
            }
            else{
                toDrop.push_back({argOtherNode, it});

            }
        }
        for(int i = 0; i<toDrop.size(); i++){
            adj[*(toDrop[i].first)].erase(toDrop[i].second);
            adj[*(toDrop[i].second)].remove(*(toDrop[i].first));
            adjacentCities[*(toDrop[i].first)]-=1;
            adjacentCities[*(toDrop[i].second)] -=1 ;
        }
        toDrop.clear();
    }

}
int main(){
    int n, m;
    vector<string> keys;
    vector<pair<string, string>> edges_;
    string aux, aux2;

    fstream file("EnfermeraJoey.txt", ios::in);
    if (file.is_open()) {
        file>>n;
        for(int i = 0; i<n; i++){
            file>>aux;
            keys.push_back(aux);
        }
        file>>m;
        for(int i = 0; i<m; i++){
            file>>aux>>aux2;
            edges_.push_back({aux, aux2});
        }
    }
    file.close();

    Graph graphTeselia(n);
    graphTeselia.mappingTeselia(keys);
    graphTeselia.addEdges(edges_);

    cout<<"--------"<<"CENTROS POKEMON"<<"--------"<<endl;
    graphTeselia.getPokemonCenters();

    return 0;
}
