#include"RandomForest.h"
#include"ReadTxtFile.h"
#include <math.h>
#include <string.h>
#include <gsl/gsl_rng.h>
#ifndef PSO_H_
extern "C"{
#include "pso.h"
}
#endif
using namespace std;

#define TRAIN_NUM 180
#define TEST_NUM 21
#define FEATURE 10
#define NUMBER_OF_CLASSES 1

float**trainset;
float** testset;
float*trainlabels;
float*testlabels;

double pso_rf(double *vec, int dim, void *params) 
{
	//初步计划优化：treeNum, maxDeep,minLeafSample，trainedFeatureNum 这4个参数
	/*
	vec[0]------treeNum,    range from[10,100]
	vec[1]------maxDeep,    range from[5,15]
	vec[2]------minleefSample,    range from[2,20]
	vec[3]------trainedFeatureNum,    range from[2,FEATRUE]
	*/
    vec[0]=(int)(vec[0]*0.9+10);
	vec[1]=(int)(vec[1]*0.1+5);
	vec[2]=(int)(vec[2]*0.18+2);
	vec[3]=(int)(vec[3]*((FEATURE-2)/100)+2);
	//2. create RandomForest class and set some parameters
	RandomForest*randomForest=new RandomForest(vec[0],vec[1],vec[2],0);//treeNum, maxDeep,minleefSample,minInfoGain
    float*responses = new float[TEST_NUM]; //输出
	float*relative_error = new float[TEST_NUM]; //相对误差
	float RMSE_result=0;
	//3. start to train RandomForest
	srand(static_cast<unsigned int>(time(NULL)));
	for(int times=0;times<6;times++)
	{
        randomForest->train(trainset,trainlabels,TRAIN_NUM,FEATURE,1,true,vec[3]);
		//Last 3 params：classNum(1)，isRegession，trainedFeatureNum

	    //新版测试方法
	    //测试集的RMSE(均方误差),平均误差和相对误差
		float average_error = 0; //平均误差
		float average_relative_error = 0; //平均相对误差
		float square_error = 0;
		float RMSE = 0; //均方根误差
		randomForest->predict(testset, TEST_NUM, responses);
		//std::cout << "the responses of testset are:" << std::endl;
		for (int i = 0; i < TEST_NUM; i++)
		{
			//std::cout << responses[i] << std::endl;
			relative_error[i] = fabsf(responses[i] - testlabels[i]) / testlabels[i];
			average_error += fabsf(responses[i] - testlabels[i]);
			square_error += (responses[i] - testlabels[i])*(responses[i] - testlabels[i]);
		}
		for (int i = 0; i < TEST_NUM; i++)
		{
			//std::cout << relative_error[i] << std::endl;
			average_relative_error += relative_error[i];
		}
		average_relative_error /= TEST_NUM;
		average_error /= TEST_NUM;
		RMSE = sqrt(square_error / TEST_NUM);
		RMSE_result+=RMSE;
		// printf("the average error is:%f", average_error);
		// printf("\n");
		// printf("the average relative error is:%f", average_relative_error);
		// printf("\n");
		// printf("the RMSE is:%f", RMSE);
		// printf("\n");
	}
	RMSE_result /= 6;
    printf("Current result=%f\n",RMSE_result);
	delete randomForest;
	randomForest = NULL;
	delete[] responses;
	delete[] relative_error;
	
    return((double) RMSE_result);

}
int main(int argc, const char * argv[])
{
    //1. prepare data
	
	trainset=new float*[TRAIN_NUM];
	testset=new float*[TEST_NUM];
	trainlabels=new float[TRAIN_NUM];
	testlabels=new float[TEST_NUM];
	for(int i=0;i<TRAIN_NUM;++i)
	{trainset[i]=new float[FEATURE];}
	for(int i=0;i<TEST_NUM;++i)
	{testset[i]=new float[FEATURE];}
	
  
	readTxtData(trainset, trainlabels,
		"/home/zkcc/桌面/rf v3.1/data/data5/train_data5.txt",
		"/home/zkcc/桌面/rf v3.1/data/data5/train_label5.txt");
	readTxtData(testset, testlabels,
		"/home/zkcc/桌面/rf v3.1/data/data5/test_data5.txt",
		"/home/zkcc/桌面/rf v3.1/data/data5/test_label5.txt");


    // define objective function
	pso_obj_fun_t obj_fun = pso_rf;
	// initialize pso settings
	pso_settings_t settings;
	// set the default settings
	pso_set_default_settings(&settings);
	
	 // initialize GBEST solution
	pso_result_t solution;
	// allocate memory for the best position buffer
	solution.gbest = (double*) malloc(settings.dim*sizeof(double));

	// run optimization algorithm
	pso_solve(obj_fun, NULL, &solution, &settings);

	// free the gbest buffer
	free(solution.gbest);

    for(int i=0;i<TRAIN_NUM;i++) delete[] trainset[i];
	for(int i=0;i<TEST_NUM;i++) delete[] testset[i];
	delete[] trainset;
	delete[] testset;
	delete[] trainlabels;
	delete[] testlabels;
    
	return 0;
};