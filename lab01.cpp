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
        pair<int, double> p1(v, w);
        pair<int, double> p2(u, w);
        this->adj[u].push_back(p1);
        this->adj[v].push_back(p2);
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
    d[source] = 1.0;

    while (!Q.empty())
    {   
        int u = Q.top().first;
        Q.pop();
        for(iter = G.adj[u].begin();iter!=G.adj[u].end(); iter++){

            // Relaxation step:
            int v = iter->first;
            float w = iter->second;
            if(d[v] < d[u] * w)
            {
                d[v] = d[u] * w;
                Q.push(pair<int, double>(v, -d[v]));
            }
        }
    }
}

double best_tree(vector<int> &ingredients, int k, int n, vector<int> &mapaIngredientes, int source, vector< vector<double> > &all_d)
{

    // Get ingredient from current island
    for (int i = 0; i < k; i++)
    {
        if (ingredients[i] == mapaIngredientes[source])
        {
            ingredients[i] = 0;
            break;
        }
    }

    // Check number of ingredients left.
    int empty = 0;
    for (int i = 0; i < k; i++)
    { 
        if (ingredients[i] != 0)
        {
            empty = 1;
            break;
        }
        
    }
    // No more ingredients!
    if (empty == 0)
    {        
        double cost2lab = all_d[source][n - 1];
        return cost2lab;
    }

    // Some ingredients left at Q.
    else {
        vector<double> childProbs(n , -1);

        for (int i = 0; i < k; i++ )
        {
            if (ingredients[i] == 0) {continue;}
            for (int land_i = 0; land_i < n; land_i++)
            {
                // Missing ingredient at location
                if (ingredients[i] == mapaIngredientes[land_i])
                {
                    vector<int> dummy_ingredients(ingredients);
                    childProbs[land_i] = best_tree(dummy_ingredients, k, n, mapaIngredientes, land_i, all_d);
                }
                
            }
        }

        double max_prob = -1;
        double source2Land = -1;
        double pathProb = -1;
        for (int land_i = 0; land_i < n; land_i++)
        {   
            source2Land = all_d[source][land_i];
            pathProb = childProbs[land_i] * source2Land;
            if (pathProb > max_prob) 
            {
                max_prob = pathProb;
            }
        }

        if (max_prob < 0)
        {
            return 0;
        }
        

        return max_prob;
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
    HaroldMap G(n, m, pontes, probPontes);
    vector< vector<double> > all_d(G.nTerras);

    // Find all Ds
    for (int terraIdx = 0; terraIdx < G.nTerras; terraIdx++)
    {
        vector<double> d(G.nTerras, 0.0);
        dijkstra(G, d, terraIdx);
        all_d[terraIdx] = d;
    }

    vector<int> ingredients(k, 0);
    for (int i = 0; i < k; i++)
    {
        ingredients[i] = i + 1;
    }
    

    resultado = best_tree(ingredients, k, n, mapaIngredientes, 0, all_d);
    
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
