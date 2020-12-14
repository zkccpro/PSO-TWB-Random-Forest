#include"Sample.h"

Sample::Sample(float**dataset,float*labels,int classNum,int sampleNum,int featureNum)
{
	_dataset=dataset;
	_labels=labels;
	_sampleNum=sampleNum;
	_featureNum=featureNum;
	_classNum=classNum;
	_selectedSampleNum=sampleNum;
	_selectedFeatureNum=featureNum;
	_sampleIndex=NULL;
	_featureIndex=NULL;
}

Sample::Sample(Sample* samples)
{
	_dataset=samples->_dataset;
	_labels=samples->_labels;
	_classNum=samples->getClassNum();
	_featureNum=samples->getFeatureNum();
	_sampleNum=samples->getSampleNum();
	_testNum = samples->getTestNum();
	_selectedSampleNum=samples->getSelectedSampleNum();
	_selectedFeatureNum=samples->getSelectedFeatureNum();
	_sampleIndex=samples->getSampleIndex();
	_testIndex = samples->getTestIndex();
	_featureIndex=samples->getFeatureIndex();
	_randomTemp = new int[_sampleNum*2];
}

Sample::Sample(Sample* samples,int start,int end)
{
	_dataset=samples->_dataset;
	_labels=samples->_labels;
	_classNum=samples->getClassNum();
	_sampleNum=samples->getSampleNum();
	_selectedSampleNum=end-start+1;
	_featureNum=samples->getFeatureNum();
	_selectedFeatureNum=samples->getSelectedFeatureNum();
	_sampleIndex=new int[_selectedSampleNum];
	memcpy(_sampleIndex,samples->getSampleIndex()+start,sizeof(float)*_selectedSampleNum);
}

Sample::~Sample()
{
	_sampleIndex=NULL;
	_featureIndex=NULL;
}

void Sample::randomSelectSample(int*sampleIndex,int*testIndex,int SampleNum,int selectedSampleNum)
{
	_sampleNum=SampleNum;
	if (_sampleIndex != NULL)
	{delete[] _sampleIndex;}
	_testIndex = testIndex;
	_sampleIndex=sampleIndex;
	int i=0,index=0;
	//sampling trainset with replacement
	for(i=0;i<selectedSampleNum;++i)
	{
		index=rand()%SampleNum;
		_randomTemp[i]=index;
	}
	/*for (int z = 0; z < 5; z++)
	{
		printf("%d ", _randomTemp[z]);
	}*/
	_sampleIndex[0] = _randomTemp[0];
	int item = 0;//重复元素的个数
	for (int i = 0; i < selectedSampleNum; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (_randomTemp[i] == _randomTemp[j])
			{
				item++;
				break;
			}

			if (j == i - 1 && _randomTemp[i] != _randomTemp[j])
			{
				_sampleIndex[i - item] = _randomTemp[i];
			}
		}
	}
	_selectedSampleNum = selectedSampleNum - item; //真实的每棵树的训练样本个数
	_testNum = _sampleNum - _selectedSampleNum; //每棵树的测试样本个数
	/*printf("\n");
	for (int z = 0; z < 5; z++)
	{
		printf("%d ", _sampleIndex[z]);
	}*/
	//装入测试索引
	int item1 = 0;//所有样本在_sampleIndex中出现的元素个数
	for (int i = 0; i < _sampleNum; i++)
	{
		for (int j = 0; j < _selectedSampleNum; j++)
		{
			if (i == _sampleIndex[j])
			{
				item1++;
				break;
			}
			if (j == _selectedSampleNum - 1 && i != _sampleIndex[j])
			{
				_testIndex[i - item1] = i;
			}
		}
	}
	/*printf("\n");
	for (int z = 0; z < 5; z++)
	{
		printf("%d ", _testIndex[z]);
	}*/
	delete[] _randomTemp;
	_randomTemp = NULL;
}
void Sample::randomSelectFeature(int*featureIndex,int featureNum,int selectedFeatureNum)
{
	_featureNum=featureNum;
	_selectedFeatureNum=selectedFeatureNum;
	_featureIndex=featureIndex;
	int i=0,j=0,k=0,index=0;
	//sampling feature without replacement
	for(i=0,j=featureNum-selectedFeatureNum;j<featureNum;++j,++i)
	{
        if(j == 0)
            index = 0;
        else
            index = rand()%j;
		bool flag=false;
		for(k=0;k<i;++k)
		{
			if(_featureIndex[k]==index)
			{
				flag=true;
				break;
			}
		}
		if(flag)
		{
			_featureIndex[i]=j;	
		}
		else
		{
			_featureIndex[i]=index;	
		}
	}
}
