#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>
#include <utility>
#include <iostream>

using namespace std;
typedef long long unsigned int ll;
ll numtest;
ll calfitness(vector<ll> chromosome, vector<pair<ll, ll> > vec)
{
    ll counter = 0;
    for (size_t i = 0; i < chromosome.size(); i++)
    {
        counter += (chromosome[i]) * (vec[i].second);
    }
    return counter;
}
ll calweight(vector<ll> chromosome, vector<pair<ll, ll> > vec)
{
    ll counter = 0;
    for (size_t i = 0; i < chromosome.size(); i++)
    {
        counter += (chromosome[i]) * (vec[i].first);
    }
    return counter;
}
bool valid(vector<ll> chromosome, vector<pair<ll, ll> > vec, ll size)
{
    if (calweight(chromosome, vec) <= size)
        return true;
    else
        return false;
}
ll calNumElements(vector<ll> chromosome)
{
    ll counter = 0;
    for (size_t i = 0; i < chromosome.size(); i++)
    {
        if(chromosome[i]==1)
        {
            counter++;
        }
    }
    return counter;
}
pair<ll, vector<ll> > a7sanwa7d(vector<pair<ll, vector<ll> > > x)
{
    sort(x.begin(), x.end());
    return x[x.size()-1];
}

int main()
{

    cin >> numtest;
    for (int z = 0; z < numtest; ++z)
    {
        const int populationSize = 200;
        ll knapSackSize, numItems, x, y, counter = 0, counter2 = 0, counter3 = 0;
        ll random, parent1, parent2, numGenerations = 10;
        pair<ll, vector<ll> > chromosome[populationSize];
        pair<ll, vector<ll> > firstchild1,secondchild2;
        vector<pair<ll, vector<ll> > > candidates;
        vector<ll> chromosomesWeight, chromosomesNoOfItems, chromosomesFitness, chromosomesCumulativeFitness;
        vector<ll> firstparent, secondparent, firstchild, secondchild;
        pair<ll, ll> pair;
        vector<std::pair<ll, ll> > vec;

        cin >> knapSackSize;
        cin >> numItems;
        for (int i = 0; i < numItems; ++i)
        {
            cin >> x >> y;
            pair = make_pair(x, y);
            vec.push_back(pair);
        }
        for (int k = 0; k < populationSize; k++)
        {
            ll weight = 0;
            for (int j = 0; j < numItems; j++)
            {
                random = rand() % 2; // random  0 or 1
                if (random == 1 && weight <= knapSackSize)// handling ks size problem
                {
                    chromosome[k].second.push_back(random);
                    weight += vec[j].first;
                }
                else
                {
                    chromosome[k].second.push_back(0);
                }
                if(weight>knapSackSize)
                {
                    chromosome[k].second.pop_back();//remove last 1
                    chromosome[k].second.push_back(0);//replace it by 0
                }
            }
        }

        // loop for generations
        for(int j = 0; j < numGenerations; j++)
        {
            // applying fitness function
            for (int j = 0; j < populationSize; j++)
            {
                counter = 0;
                counter2 = 0;
                counter3 = 0;
                for (int k = 0; k < numItems; k++)
                {
                    counter += (chromosome[j].second[k]) * (vec[k].second); // fitness(value)
                    counter2 += (chromosome[j].second[k]) * (vec[k].first); // weight
                    counter3 += (chromosome[j].second[k]) * 1;              // number of items
                }
                chromosome[j].first = counter;
                chromosomesFitness.push_back(counter);
                chromosomesWeight.push_back(counter2);
                chromosomesNoOfItems.push_back(counter3);
            }
            // calculating cumulative fitness
            chromosomesCumulativeFitness = chromosomesFitness;
            chromosomesCumulativeFitness[0] == chromosomesFitness[0];
            for (int k = 1; k < populationSize; k++)
            {
                chromosomesCumulativeFitness[k] = chromosomesFitness[k] + chromosomesCumulativeFitness[k - 1];
            }

            // choosing first parent
            int r1 = rand() % (chromosomesCumulativeFitness[populationSize - 1] - 0 + 1) + 0;

            if (r1 >= 0 && r1 < chromosomesCumulativeFitness[0])
            {
                parent1 = 0;
                firstparent = chromosome[0].second;
            }
            for (int k = 1; k < chromosomesCumulativeFitness.size(); k++)
            {
                if (r1 >= chromosomesCumulativeFitness[k - 1] && r1 < chromosomesCumulativeFitness[k])
                {
                    parent1 = k;
                    firstparent = chromosome[k].second;
                    break;
                }
            }
            // choosing second parent
            int r2 = rand() % (chromosomesCumulativeFitness[populationSize - 1] - 0 + 1) + 0;
            if (r1 >= 0 && r1 < chromosomesCumulativeFitness[0])
            {
                parent2 = 0;
                secondparent = chromosome[0].second;
            }
            for (int k = 1; k < chromosomesCumulativeFitness.size(); k++)
            {
                if (r2 >= chromosomesCumulativeFitness[k - 1] && r2 < chromosomesCumulativeFitness[k])
                {
                    parent2 = k;
                    secondparent = chromosome[k].second;
                    break;
                }
            }
            int xc = rand() % ((chromosomesCumulativeFitness.size() - 1) - 1 + 1) + 1;
            int rc = rand() % (numItems-2 + 1) + 1; // random between 0 and 1
            int pc = 0.7;
            int pm = 0.1;

            if (rc <= pc) // crossover
            {
                for (int i = 0; i < xc; i++)
                {
                    firstchild[i] = firstparent[i];
                    secondchild[i] = secondparent[i];
                }
                for (int i = xc; i < firstparent.size(); i++)
                {
                    firstchild[i] = secondparent[i];
                    secondchild[i] = firstparent[i];
                }
            }
            else // no crossover
            {
                firstchild = firstparent;
                secondchild = secondparent;
            }
            // mutation
            for (int i = 0; i < firstparent.size(); i++)
            {
                int randNum = rand() % (1 - 0 + 1) + 0;
                if (firstchild[i] == 0 && randNum <= pm)
                {
                    firstchild[i] = 1;
                }
                else if (firstchild[i] == 1 && randNum <= pm)
                {
                    firstchild[i] = 0;
                }
            }
            for (int i = 0; i < secondparent.size(); i++)
            {
                int randNum = rand() % (1 - 0 + 1) + 0;
                if (secondchild[i] == 0 && randNum <= pm)
                {
                    secondchild[i] = 1;
                }
                else if (secondchild[i] == 1 && randNum <= pm)
                {
                    secondchild[i] = 0;
                }
            }
            int n = sizeof(chromosome)/sizeof(chromosome[0]);
            std::sort(chromosome, chromosome + n);
            ll ff = calfitness(firstchild, vec);  // first fitness
            ll sf = calfitness(secondchild, vec); // second fitness
            firstchild1.first = ff;
            secondchild2.first = sf;
            firstchild1.second = firstchild;
            secondchild2.second = secondchild;

            candidates.push_back(firstchild1);
            candidates.push_back(secondchild2);
            candidates.push_back(chromosome[0]);
            candidates.push_back(chromosome[1]);
            sort(candidates.begin(),candidates.end());
            if(valid(candidates[2].second,vec,knapSackSize)){
                chromosome[0]=candidates[2];
            }
            if(valid(candidates[3].second,vec,knapSackSize)){
                chromosome[1]=candidates[3];
            }
        }
        int n = sizeof(chromosome)/sizeof(chromosome[0]);
        std::sort(chromosome, chromosome + n);
        vector <ll> bestOne= chromosome[populationSize-1].second;
        ll finalFitness =calfitness(bestOne,vec);
        ll finalWeight = calweight(bestOne,vec);
        ll finalNumElements = calNumElements(bestOne);
        cout<<finalFitness<<" "<<finalWeight<<" "<<finalNumElements<<endl;
    }
    return 0;
}
