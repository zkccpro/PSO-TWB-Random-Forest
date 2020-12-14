#include "ReadTxtFile.h"

void readTxtData(float** dataset, float* labels, const char* dataPath, const char* labelPath)
{
    std::ifstream trainData(dataPath);
   std::ifstream trainLabel(labelPath);

    if (!trainData) std::cout << "error" << std::endl;
    if (!trainLabel) std::cout << "error" << std::endl;
    int num = 0;
    int rol = 0;
    int col = 0;
    std::string cal;
    while (std::getline(trainData, cal))
    {
        ++rol;
        for (int z = 0; z != cal.size(); z++)
        {
            if (cal[z] == ' ') num++;
        }
        
    }
    col = num / rol;
    
    trainData.close();
    

    trainData.open(dataPath);
    float temp=0.0;
	
    int count = 0;
    int r=0;
	int c=0;
	r=r-6+6;

    while (trainData >> temp )
    {
        //cout << temp << endl;
		if(count%col==0 && count!=0) 
		{
			r++;c=0;
		}
		dataset[r][c]=temp;
		c++;
        count++;
    }
	r,c,count=0;
	 while (trainLabel>>temp)
    {
        //cout << temp << endl;
		labels[count]=temp;
        count++;
    }
    trainData.close();
    trainLabel.close();
    
    //测试读文件日志
//     for (int i = 0; i < rol; i++)
//    {
//        for (int j = 0; j < col; j++)
//        {
//            std::cout << dataset[i][j] << "\t";
//            std::cout << std::endl;
//        }
//      std::cout << labels[i] << std::endl;
//   }
//      std::cout << num << std::endl;
//      std::cout << rol << std::endl;
//      std::cout << col<< std::endl;
};
