#include <algorithm>
#include <array>
#include <chrono>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <deque>
#include <forward_list>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <valarray>
#include <vector>
#include <cassert>

using namespace std;

vector<vector<pair<int, int>>> computeNbServingsPossible(int N, int P, const vector<float>& R, const vector<vector<float>>& Q)
{
	vector<vector<pair<int, int>>> res(N, vector<pair<int, int>>(P));
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < P; j++)
		{
			int nbMin = int(ceil(Q[i][j] / (1.1f * R[i])));
			int nbMax = int(trunc(Q[i][j] / (0.9f * R[i])));
			res[i][j] = make_pair(nbMin, nbMax);
		}
	}
	return res;
}

int solve_wrong(int N, int P, vector<vector<pair<int, int>>> nbServingsPossible)
{
	for (int i = 0; i < N; i++)
		sort(nbServingsPossible.begin(), nbServingsPossible.end());

	int nbKits = 0;
	for (int j = 0; j < P; j++)
	{
		for (int nbServs = nbServingsPossible[0][j].first; nbServs <= nbServingsPossible[0][j].second; nbServs++)
		{
			bool allIngredientsFound = true;
			vector<int> used(N, -1);
			used[0] = j;
			for (int i = 1; i < N; i++)
			{
				bool ingredientOk = false;
				for (int j2 = 0; j2 < P; j2++)
				{
					if (nbServs >= nbServingsPossible[i][j2].first && nbServs <= nbServingsPossible[i][j2].second)
					{
						ingredientOk = true;
						used[i] = j2;
						break;
					}
				}
				if (!ingredientOk)
				{
					allIngredientsFound = false;
					break;
				}
			}
			if (allIngredientsFound)
			{
				nbKits++;
				for (int i = 0; i < N; i++)
					nbServingsPossible[i][used[i]] = make_pair(-10, -10);
				break;
			}
		}
	}
	return nbKits;
}
int solve(int N, int P, vector<vector<pair<int, int>>> nbServingsPossible)
{
	for (int i = 0; i < N; i++)
		sort(nbServingsPossible.begin(), nbServingsPossible.end());

	int nbKits = 0;
	while (true)
	{
		bool stop = false;
		for (int i = 0; i < N; i++)
			if (nbServingsPossible[i].size() == 0)
			{
				stop = true;
				break;
			}
		if (stop)
			break;

		int consideredIngredient = 0;
		int consideredPack = 0;
		pair<int, int> minInterval = nbServingsPossible[0][0];
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < nbServingsPossible[i].size(); j++)
			{
				if (nbServingsPossible[i][j] < minInterval)
				{
					consideredIngredient = i;
					consideredPack = j;
					minInterval = nbServingsPossible[i][j];
				}
			}
		}

		bool increasedNbKits = false;
		for (int nbServs = nbServingsPossible[consideredIngredient][consideredPack].first;
			nbServs <= nbServingsPossible[consideredIngredient][consideredPack].second; nbServs++)
		{
			bool allIngredientsFound = true;
			vector<int> used(N, -1);
			used[consideredIngredient] = consideredPack;
			for (int i = 0; i < N; i++)
			{
				if (i == consideredIngredient)
					continue;

				bool ingredientOk = false;
				for (int j2 = 0; j2 < nbServingsPossible[i].size(); j2++)
				{
					if (nbServs >= nbServingsPossible[i][j2].first && nbServs <= nbServingsPossible[i][j2].second)
					{
						ingredientOk = true;
						used[i] = j2;
						break;
					}
				}
				if (!ingredientOk)
				{
					allIngredientsFound = false;
					break;
				}
			}
			if (allIngredientsFound)
			{
				nbKits++;
				for (int i = 0; i < N; i++)
					nbServingsPossible[i].erase(nbServingsPossible[i].begin() + used[i]);
				increasedNbKits = true;
				break;
			}
		}
		if (!increasedNbKits)
		{
			nbServingsPossible[consideredIngredient].erase(nbServingsPossible[consideredIngredient].begin() + consideredPack);
		}
	}
	return nbKits;
}
int solveBf(int N, int P, vector<vector<pair<int, int>>> nbServingsPossible)
{
	if (N == 1)
	{
		int nbKits = 0;
		for (int j = 0; j < P; j++)
		{
			if (nbServingsPossible[0][j].first <= nbServingsPossible[0][j].second)
				nbKits++;
		}
		return nbKits;
	}

	assert(N == 2);

	int nbKits = 0;
	for (int j1 = 0; j1 < P; j1++)
	{
		for (int j2 = 0; j2 < P; j2++)
		{
			if (nbServingsPossible[0][j1].first <= nbServingsPossible[1][j2].second
				&& nbServingsPossible[1][j2].first <= nbServingsPossible[0][j1].second)
			{
				auto copy = nbServingsPossible;
				copy[0].erase(copy[0].begin() + j1);
				copy[1].erase(copy[1].begin() + j2);
				int res = 1 + solveBf(N, P - 1, copy);
				if (res > nbKits)
					nbKits = res;
			}
		}
	}
	return nbKits;
}

int main()
{
	ios::sync_with_stdio(false);

	int T;
	cin >> T;
	for (int t = 0; t < T; t++)
	{
		int N, P;
		cin >> N >> P;

		vector<float> R(N);
		for (int i = 0; i < N; i++)
			cin >> R[i];

		vector<vector<float>> Q(N, vector<float>(P));
		for (int i = 0; i < N; i++)
		{
			 for (int j = 0; j < P; j++)
			 {
				 cin >> Q[i][j];
			 }
		}

		vector<vector<pair<int, int>>> nbServingsPossible = computeNbServingsPossible(N, P, R, Q);

		int nbKits = solve(N, P, nbServingsPossible);
		cout << "Case #" << t + 1 << ": " << nbKits << endl;
	}

	return 0;
}
