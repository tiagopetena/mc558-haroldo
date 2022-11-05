#include <iostream>
#include <vector>
#include <iomanip>
#include <queue>
#include <set>
#include <list>
#include <cmath>
using namespace std;

#define NIL -1

// ATENÇÃO!
// Você é livre para incluir outras bibliotecas, implementar funções auxiliares, acrecentar definições, tipos e estruturas.


class HaroldMap
{
    public:
        int nTerras;
        int nPontes;
        list<pair<int, double> > *adj;
        HaroldMap(int n, int m, vector<vector<int> > &pontes, vector<double> &probPontes);
        void print_adj();
        void addEdge(int u,int v,int w);
};

HaroldMap::HaroldMap(int n, int m, vector<vector<int> > &pontes, vector<double> &probPontes){
    this->nTerras = n;
    this->nPontes = m;
    this->adj = new list<pair<int, double> >[this->nTerras];

    for (int i = 0; i < nPontes; i++)
    {
        int u = pontes[i][0];
        int v = pontes[i][1];
        double w = probPontes[i];
        cout << "adding "<< u << ", " << v << " - " << w << '\n';
        pair<int, double> p1(v, w);
        pair<int, double> p2(u, w);
        this->adj[u].push_back(p1);
        this->adj[v].push_back(p2);
        cout << "added " << this->adj[u].back().second << '\n';
    }
    

}
void HaroldMap::print_adj()
{
    
    for (int i = 0; i < this->nTerras; i++)
    {
        list<pair<int, double> >::iterator iter;
        for(iter = this->adj[i].begin(); iter!=this->adj[i].end(); iter++){
            int v = iter->first;
            double w = iter->second;
            cout << "(" << i << "," << v << ") - " << w << "\n";
        }
    }
    
}
void dijkstra(HaroldMap G, vector<double> &d, int source)
{
    std::priority_queue<pair<int, double>, vector<pair<int, double> >, greater<pair<int, double> > > Q;
    list<pair<int, double> >::iterator iter;
    
    Q.push(pair<int, double>(source, -1.0));
    d[0] = 1.0;

    while (!Q.empty())
    {   
        int u = Q.top().first;
        Q.pop();
        cout << "u = " << u << "\n";
        for(iter = G.adj[u].begin();iter!=G.adj[u].end(); iter++){
            int v = iter->first;
            float w = iter->second;
            cout << "u v w = " << u<< " " <<v << " " <<w << endl;
            if(d[v] < d[u] * w)
            {
                d[v] = d[u] * w;
                Q.push(pair<int, double>(v, -d[v]));
            }
        }
    }
}

// Esta função deve retornar o valor obtido pela sua solução //
/* Parâmetros: 
    n, m e k são os números de terras, pontes e ingredientes, respecitivamente.
    pontes[m][2] é uma matriz m X 2 indicando as pontes existentes.
    probPontes[j] é a probabilidade da ponte j não cair, para cada ponte j de de 0 a m-1.
    mapaIngredientes[i] é o ingrediente na terra i, para toda terra i de 0 a n-1.
*/
double melhorRota(int n, int m, vector<vector<int> > &pontes, vector<double> &probPontes, int k, vector<int> &mapaIngredientes)
{
	double resultado = NIL;
    for (int i = 0; i < m; i++)
    {
        cout << probPontes[i] << "\n";
    }
	// MODIFIQUE AQUI NO MEIO
    std::cout << pontes[0][0] << ' ';
    cout << "GG";
    HaroldMap G(n, m, pontes, probPontes);
    G.print_adj();
    vector<double> d(G.nTerras, 0.0);
    cout << "GG";
    dijkstra(G, d, 0);
    for (int i = 0; i < G.nTerras; i++)
    {
        double w = d[i];
        cout << w << " ";
    }
    cout << "\n";
    for (int i = 0; i < mapaIngredientes.size(); i++)
    {
        int w = mapaIngredientes[i];
        cout << w << " ";
    }
    
	return resultado;
}

/////////////////////////////////////////////////////
// NÃO MOFIFICAR A PARTIR DAQUI
/* Função que lida com leitura e escrita de valores */
int main()
{
	int n, m, k;
	cin >> n >> m;

	vector<vector<int> > pontes(m, vector<int>(2, NIL));
	vector<int> mapaIngredientes(n, NIL);
	vector<double> probPontes(m, NIL);

	int u, v;
	double p;
	for (int i = 0; i < m; i++)
	{
		cin >> u >> v >> p;
		pontes[i][0] = u;
		pontes[i][1] = v;
		probPontes[i] = p;
	}

	cin >> k;

	int ing;
	for (int i = 0; i < n; i++)
	{
		cin >> ing;
		mapaIngredientes[i] = ing;
	}

	double resultado = NIL;
	resultado = melhorRota(n, m, pontes, probPontes, k, mapaIngredientes);

	cout << fixed << setprecision(5) << resultado << endl;

	return 0;
}
