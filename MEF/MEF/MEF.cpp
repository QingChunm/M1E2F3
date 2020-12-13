// MEF.cpp : �������̨Ӧ�ó������ڵ㡣
//

// ���룺ͼƬ�����ļ���
// ������ں�ͼƬ


#include <io.h>
#include <string>
#include <vector>


#include <opencv\highgui.h>
#include <opencv2\imgproc\imgproc.hpp>



using namespace std;
using namespace cv;

void getFiles(string path, vector<string>& files)
{
	//�ļ����
	long hFile = 0;
	//�ļ���Ϣ
	struct _finddata_t fileinfo;
	string p;

	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//�����Ŀ¼,����֮
			//�������,�����б�
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

int main(int argc, char* argv[])
{
	vector<string> files;

	char *img_seq_path = ".\\input\\Room";

	getFiles(img_seq_path, files);

	int frames = files.size();
	vector<Mat> imgs;
	vector<Mat> patchs;

	int patch_size = 11;
	unsigned char patch[361] = { 0 };
	

	//read all images
	for (int k = 0; k < frames; k++)
	{
		Mat ycrcb;
		Mat img = imread(files[k]);
		cvtColor(img, ycrcb, CV_RGB2YCrCb);
		vector<Mat> vec;
		split(ycrcb, vec);
		imgs.push_back(vec[0]);
		imshow("img seq", imgs[k]);
		waitKey(0);
	}



	int image_width = imgs[0 ].cols;
	int image_heit = imgs[0].rows;

	for (int i = patch_size / 2; i < image_heit - patch_size / 2; i++)
	{
		for (int j = patch_size / 2; j < image_width - patch_size / 2; j++)
		{
			//׼��patchs[1,K]
			for (int k = 0; k < frames; k++)
			{
				Mat patch = Mat(patch_size, patch_size, CV_8U);
				patchs.push_back(patch);
				unsigned char *p1 = imgs[k].data;
				unsigned char *p2 = patch.data;
				for (int n = 0; n < patch_size; n++)
				{
					for (int m = 0; m < patch_size; m++)
					{
						p2[n*patch_size + m] = p1[(i - patch_size / 2 + n)* image_width + j - patch_size / 2 + m];
					}
				}
				imshow("patch", patch);
				waitKey(0);
			}

			//����ֲ��Աȶ�

			//����ṹ

			//����ƽ������





			patchs.clear();
		}
	}




	return 0;
}

