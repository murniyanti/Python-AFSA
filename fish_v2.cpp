/*
Things need to fix:
1. Fitness function: change to rosenbrock
2. Euclidean distance- because idk where to find euclidean distance function and im too lazy to code it
3. so far thats all.
*/
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

//DEFINE*********//
#define Dimension	2
#define Population	10
#define TryTimes	3
#define Visual		0.1
#define Step		0.1


class fish_v2
{
public:
	std::vector<float> Position;
	float Fitness;
};

void Init(std::vector<fish_v2> A);	//Initialize fish

bool sortByScore(const fish_v2 &lhs, const fish_v2 &rhs) { return lhs.Fitness<rhs.Fitness; }	// sort

float calcFitness(std::vector<float> array1);			//Calculate fitness of fish. return fitness score

fish_v2 makeTemporaryFish(fish_v2 C);		//Return Object of class fish

void Prey(fish_v2 ind, fish_v2 TF, fish_v2 Be, int count, std::vector<fish_v2> GF);		//only modify object

void moveRandom(fish_v2 ind);				//only modify object

fish_v2 GetBestFish(std::vector<fish_v2> GF);			//Return Object of class fish

void Swarm(fish_v2 ind, fish_v2 B);			//only modify object

void Follow(fish_v2 ind, fish_v2 TF1);		//only modify object


int main()
{	int ITERATION = 10;
	std::vector<fish_v2> GroupFish;
	Init(GroupFish);
	fish_v2 B;
	B = GetBestFish(GroupFish);
	std::vector<fish_v2> Store;
	Store.push_back(B);

	//ITERATION
	int i=0;
	while(i<ITERATION) {
		int j=0;
		while (j<Population) {
			int k=0;
			while (k<TryTimes) {
				fish_v2 TemFish;
				TemFish = makeTemporaryFish(GroupFish[j]);
				if (GroupFish[j].Fitness<TemFish.Fitness) {
					Prey(GroupFish[j], TemFish, B, j, GroupFish);
					break;
				}k++;
			}
			moveRandom(GroupFish[j]);
			j++;
		}
		i++;
		cout<<i;
		B = GetBestFish(GroupFish);
		Store.push_back(B);
	}
	fish_v2 BestFishEvar;
	BestFishEvar = GetBestFish(Store);
	cout<< BestFishEvar.Fitness;
	cout<<"rererere";
    return 0;
	
}

void Init(std::vector<fish_v2> A) {

	for (int i = 0; i < Population; ++i) 
	{
		std::vector<float> s;
		for (int j = 0; j < Dimension; ++j)
		{
			s.push_back(rand());
		}
		fish_v2 F;
		F.Position=s;
		F.Fitness = calcFitness(s);
		A.push_back(F);
	}
}

float calcFitness(std::vector<float> array1) {
	float sum=0;
	int i=0;
	while (i<(Dimension-1)) {
		float r=100;
		sum=sum+r;
		i++;
	}
	return sum;
}

fish_v2 makeTemporaryFish( fish_v2 C) {
	std::vector<float> tempos;
	for (int i = 0; i < Dimension; ++i)
	{
		tempos.push_back((C.Position[i]+(Visual*rand())));
	}

	fish_v2 F;
	F.Position=tempos;
	F.Fitness=calcFitness(tempos);
	return F;
}

void Prey(fish_v2 ind, fish_v2 TF, fish_v2 Be, int count, std::vector<fish_v2> GF) {
	float crawdFactor = rand();
	std::vector<float> newState;

	for (int i = 0; i < Dimension; ++i)
	{
		float m = ind.Position[i] + (((TF.Position[i]-ind.Position[i])/1)*Step*rand());
		newState.push_back(m);
	}
	float newFit = calcFitness(newState);

	float nf = Visual*Population;

	std::vector<float> Xc;
	float element;
	for (int i = 0; i < round(nf); ++i) {
		for (int j = 0; j < Dimension; ++j)
		{
			element = element + GF[i].Position[j];
		}
		Xc.push_back(element);
	}
	float XcFitness=calcFitness(Xc);

	//Follow
	if ((Be.Fitness>ind.Fitness) && ((nf/Population)<crawdFactor)) {
		Follow(ind, TF);
	}
	else if ((XcFitness>ind.Fitness) && ((nf/Population)<crawdFactor)) {
		Swarm(ind, Be);
	}
	else {
		ind.Position=newState;
		ind.Fitness=newFit;
	}
}

void moveRandom(fish_v2 ind) {

	std::vector<float> newState;
	for (int i = 0; i < Dimension; ++i) {
		float m = ind.Position[i] + (Visual*rand());
		newState.push_back(m);
	}
	ind.Position=newState;
	ind.Fitness=calcFitness(newState);
}

fish_v2 GetBestFish(std::vector<fish_v2> GF) {			//Return Object of class fish
    
	sort(GF.begin(), GF.end(), sortByScore);
    fish_v2 F= GF[0];
	return F;
}

void Swarm(fish_v2 ind, fish_v2 B) {
	std::vector<float> newState;

	for (int i = 0; i < Dimension; ++i) {
		float m = ind.Position[i] + (((B.Position[i] - ind.Position[i])/1)*Step*rand());
		newState.push_back(m);
	}
	ind.Position=newState;
	ind.Fitness=calcFitness(newState);
}


void Follow(fish_v2 ind, fish_v2 TF1) {
	std::vector<float> newState;
	for (int i = 0; i < Dimension; ++i) 
	{
		float m = TF1.Position[i] + (((TF1.Position[i] - ind.Position[i])/1)*Step*rand());
		newState.push_back(m);
	}
	ind.Position=newState;
	ind.Fitness=calcFitness(newState);
}