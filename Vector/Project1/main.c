#include <stdio.h>
#include <stdlib.h>
#include "TVector.h"
#include "check.h"

bool split(const struct TVector *aSourceVector, TVectorElement aValue, struct TVector *aVectorA, struct TVector *aVectorB);

int main()
{
	struct TVector vector1 = { 0 };
	float data;
	printf("Zadejte data vektoru1: ");
	if(scanf("%f", &data) != 1)
		return 1;
	while(data >= 0)
	{
		if(!vector_resize(&vector1, vector_size(&vector1) + 1))
		{
			vector_destroy(&vector1);
			return 2;
		}
		vector_set_value(&vector1, vector_size(&vector1) - 1, data);
		if(scanf("%f", &data) != 1)
			return 1;
	}
	printf("\nvector1: ");
	for(size_t i = 0; i < vector_size(&vector1); i++)
		printf("%f ", vector_value(&vector1, i));
	printf("\nZadejte splitter: ");
	if(scanf("%f", &data) != 1)
		return 1;
	struct TVector vector2 = { 0 };
	struct TVector vector3 = { 0 };
	if(!split(&vector1, data, &vector2, &vector3))
	{
		vector_destroy(&vector1);
		vector_destroy(&vector2);
		vector_destroy(&vector3);
		return 3;
	}
	printf("\nvector2: ");
	for(size_t i = 0; i < vector_size(&vector2); i++)
		printf("%f ", vector_value(&vector2, i));
	vector_destroy(&vector2);
	printf("\nvector3: ");
	for(size_t i = 0; i < vector_size(&vector3); i++)
		printf("%f ", vector_value(&vector3, i));
	vector_destroy(&vector3);
	vector_destroy(&vector1);
	return 0;
}

bool split(const struct TVector *aSourceVector, TVectorElement aValue, struct TVector *aVectorA, struct TVector *aVectorB)
{
	if(aSourceVector == NULL || aVectorA == NULL || aVectorB == NULL)
		return false;
	size_t sizeA = 0;
	for(; sizeA <= aSourceVector->iSize; ++sizeA)
	{
		if(aSourceVector->iValues[sizeA] == aValue)
		{
			TVectorElement *dataA;
			dataA = malloc((sizeA + 1) * sizeof(TVectorElement));
			if(dataA == NULL)
				return false;
			TVectorElement *dataB;
			size_t sizeB = aSourceVector->iSize - sizeA - 1;
			dataB = malloc(sizeB * sizeof(TVectorElement));
			if(dataB == NULL)
			{
				free(dataA);
				return false;
			}
			for(size_t i = 0; i < sizeA; i++)
				dataA[i] = aSourceVector->iValues[i];
			for(size_t i = 0; i < sizeB; i++)
				dataB[i] = aSourceVector->iValues[i + sizeA + 1];
			free(aVectorA->iValues);
			free(aVectorB->iValues);
			aVectorA->iSize = sizeA;
			aVectorB->iSize = sizeB;
			aVectorA->iValues = dataA;
			aVectorB->iValues = dataB;
			return true;
		}
	}
	return false;
}