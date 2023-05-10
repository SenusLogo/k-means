#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <fstream>

using namespace std;

#define MAX_CLUSTER_VALUE 50

vector<vector<vector<double>>> data_distribution(vector<vector<double>> array, vector<vector<double>> cluster, size_t k)
{
	size_t n = array.size();
	size_t dim = array.at(0).size();

	vector<vector<vector<double>>> cluster_content(k);

	for (int i(0); i < n; i++)
	{
		double min_distance = pow(2, 32) - 1;
		size_t situable_cluster = -1;

		for (int j(0); j < k; j++)
		{
			double distance = 0;
			for (int q(0); q < dim; q++)
				distance += pow(array[i][q] - cluster[j][q], 2);

			distance = pow(distance, 0.5);

			if (distance < min_distance)
			{
				min_distance = distance;
				situable_cluster = j;
			}
		}

		cluster_content[situable_cluster].push_back(array[i]);
	}

	return cluster_content;
}

vector<vector<double>> cluster_update(vector<vector<double>> cluster, vector<vector<vector<double>>> cluster_content, size_t dim)
{
	size_t k = cluster.size();

	for (int i(0); i < k; i++)
	{
		for (int q(0); q < dim; q++)
		{
			double updated_parameter = 0;
			for (int j(0); j < cluster_content[i].size(); j++)
				updated_parameter += cluster_content[i][j][q];

			if (cluster_content[i].size() != 0)
				updated_parameter /= cluster_content[i].size();

			cluster[i][q] = updated_parameter;
		}
	}
	return cluster;
}

void clusterization(vector<vector<double>> array, size_t k)
{
	size_t n = array.size();
	size_t dim = array.at(0).size();

	vector<vector<double>> cluster(k, vector<double>(dim));
	vector<vector<vector<double>>> cluster_content(k);

	srand(unsigned int(time(nullptr)));

	for (int i(0); i < dim; i++)
		for (int j(0); j < k; j++)
			cluster[j][i] = rand() % MAX_CLUSTER_VALUE;

	cluster_content = data_distribution(array, cluster, k);

	vector<vector<double>> previous_cluster(k, vector<double>(dim));
	std::copy(cluster.begin(), cluster.end(), previous_cluster.begin());

	while (true)
	{
		cluster = cluster_update(cluster, cluster_content, dim);
		cluster_content = data_distribution(array, cluster, k);

		if (std::equal(cluster.begin(), cluster.end(), previous_cluster.begin()))
			break;

		std::copy(cluster.begin(), cluster.end(), previous_cluster.begin());
	}

	cout << "\n\nClusterization:\n";
	for (int i(0); i < k; i++)
	{
		cout << i + 1 << " cluster:\n";
		for (auto iter : cluster_content[i])
		{
			for (auto elements : iter)
				cout << elements << " ";
			cout << endl;
		}
		cout << '\n';
	}
}

int main()
{
	vector<vector<double>> array(20, vector<double>(5));

	fstream data;
	data.open("data.txt");

	for (int i(0); i < 20; i++)
		for (int j(0); j < 5; j++)
			data >> array[i][j];

	for (int i(0); i < 20; i++)
	{
		for (int j(0); j < 5; j++)
			cout << array[i][j] << " ";
		cout << endl;
	}

	size_t k;
	cout << "count cluster's: "; cin >> k;

	clusterization(array, k);

	system("pause");
	return 1;
}