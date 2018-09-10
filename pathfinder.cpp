#include <vector>
#include <ostream>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <filesystem>
#include <sstream>
#include "image.h"

using namespace std;

struct ranges
{
	int Xhurmin = -1;//hurtbox
	int Xhurmax = -1;
	int Xhitmin = -1;//hitbox
	int Xhitmax = -1;
	int Xspikemin = -1;//spike
	int Xspikemax = -1;
	int XSAmin = -1;//super armor
	int XSAmax = -1;
	int XWBmin = -1;//windbox
	int XWBmax = -1;
	int Xgrabmin = -1;//grab box
	int Xgrabmax = -1;
	int Xreflectmin = -1;//reflector
	int Xreflectmax = -1;
	int Xscanmin = -1;//scan
	int Xscanmax = -1;

	int Yhurmin = -1;
	int Yhurmax = -1;
	int Yhitmin = -1;
	int Yhitmax = -1;
	int YhitminR = -1;
	int YhitmaxR = -1;
	int YhitminL = -1;
	int YhitmaxL = -1;
	int Yspikemin = -1;
	int Yspikemax = -1;
	int YSAmin = -1;
	int YSAmax = -1;
	int YWBmin = -1;
	int YWBmax = -1;
	int Ygrabmin = -1;
	int Ygrabmax = -1;
	int Yreflectmin = -1;
	int Yreflectmax = -1;
	int Yscanmin = -1;
	int Yscanmax = -1;

	char type = '0';// jab1, jab2
	bool high = false;
	bool low = false;
	bool reverse = false;
};

struct info
{
	string name;
	vector<ranges> stand;
	vector<ranges> ledgegrab;
	vector<ranges> jumpsquat;
	vector<ranges> duck;
	vector<ranges> crawlback;
	vector<ranges> crawlforth;

	vector<ranges> jabrapid;
	vector<ranges> jab;
	vector<ranges> dashattack;
	vector<ranges> jabend;

	vector<ranges> sidetilt;
	vector<ranges> uptilt;
	vector<ranges> downtilt;

	vector<ranges> sidesmash;
	vector<ranges> upsmash;
	vector<ranges> downsmash;

	vector<ranges> bair;
	vector<ranges> fair;
	vector<ranges> upair;
	vector<ranges> dair;
	vector<ranges> nair;
	vector<ranges> landingbair;
	vector<ranges> landingfair;
	vector<ranges> landingupair;
	vector<ranges> landingdair;
	vector<ranges> landingnair;

	vector<ranges> neutralbair;
	vector<ranges> neutralb;
	vector<ranges> landingneutralb;
	vector<ranges> sidebair;
	vector<ranges> sideb;
	vector<ranges> landingsideb;
	vector<ranges> upbair;
	vector<ranges> upb;
	vector<ranges> landingupb;
	vector<ranges> downbair;
	vector<ranges> downb;
	vector<ranges> landingdownb;

	vector<ranges> grab;
	vector<ranges> dashgrab;
	vector<ranges> pivotgrab;
};

bool ComparePixels(Pixel color1, Pixel color2)
{
	int redtest = int(color1.red) - int(color2.red);
	int greentest = int(color1.green) - int(color2.green);
	int bluetest = int(color1.blue) - int(color2.blue);
	if (redtest > 3 || redtest < -3)
	{
		//cout << redtest << endl;
		return false;
	}
	if (greentest > 3 || greentest < -3)
	{
	
		return false;
	}
	if (bluetest > 3 || bluetest < -3)
	{
		
		return false;
	}
	return true;
}

//mumumumu
int main(int argc, char *argv[])
{
	namespace fs = std::experimental::filesystem;
	//for testing reasons, all files are already in debug folder, but path allows you to limit files to what is in the path directory, in case you don't want to do the whole cast
	//std::string path = "C:\\Users\\richa\\OneDrive\\Desktop\\testimages\\programtests\\resizedgifs\\giftopng";
	std::string path = "C:\\Users\\richa\\OneDrive\\Desktop\\iketests";
	
	//std::string path = "C:\\Users\\richa\\OneDrive\\Desktop\\giflab\\resizedgifs\\giftopng";
	string output;
	string outputupdate = "";
	vector<string> png;
	

	ofstream out("sm4shrangedataTEST.txt");//DELETE TEST
	ofstream out2("gifstobefixedTEST.txt");

	string sortbody = "";
	string sortpast = "";
	string sortindex = "";
	int sortcount = -1;
	vector<string> sortstore;
	//SORTS IMAGE NAMES IN CORRECT ORDER TO BE PROCCESSED
	for (auto & p : fs::directory_iterator(path))
	{
		//std::cout << p << std::endl;
		output = p.path().string();
		for (int i = path.length() + 1; i < output.length() - 4; i++)
		{
			outputupdate = outputupdate + output[i];
		}
		sortcount = outputupdate.length() - 1;
		while (sortcount >= 0 && outputupdate[sortcount] != '-')
		{
			sortindex = outputupdate[sortcount] + sortindex;
			sortcount--;
		}
		sortcount--;
		while (sortcount >= 0)
		{
			sortbody = outputupdate[sortcount] + sortbody;
			sortcount--;
		}
		sortcount = 0;
		istringstream(sortindex) >> sortcount;
		if (sortbody.compare(sortpast))
		{
			for (int i = 0; i < sortstore.size(); i++)
			{
				png.push_back(sortstore[i]);
			}
			sortstore.clear();
		}
		sortpast = sortbody;
		while (sortcount + 1 > sortstore.size())
		{
			sortstore.push_back(outputupdate);
		}
		sortstore[sortcount] = outputupdate;

		sortbody = "";
		sortindex = "";
		outputupdate = "";
	}
	for (int i = 0; i < sortstore.size(); i++)
	{
		png.push_back(sortstore[i]);
	}
	
	png.push_back("finished_finished");
	vector<info> charData;
	info initial;
	initial.name = "noone";
	ranges rangeman;

	static const Pixel HIT = { 202, 35, 63, 255 };
	static const Pixel HUR = { 0, 83, 138, 255 };
	static const Pixel HITNHUR = { 167, 11, 47, 255 };
	static const Pixel SA = { 115, 10, 67, 255 };
	static const Pixel SPIKE = { 35, 35, 35, 255 };
	static const Pixel SPIKENHUR = { 0, 11, 19, 255 };
	static const Pixel WIND = { 35, 35, 254, 255 };
	static const Pixel WINDNHUR = { 0, 11, 239, 255 };
	static const Pixel SCAN = { 254, 156, 35, 255 };
	static const Pixel SCANNHUR = { 220, 132, 19, 255 };
	static const Pixel GRAB = { 145, 35, 145, 255 };
	static const Pixel GRABNHUR = { 110, 11, 129, 255 };
	static const Pixel BLANK = { 254, 215, 220, 255 };
	static const Pixel HUR2 = { 30, 70, 121, 255 };
	static const Pixel REFLECT = { 0, 254, 254, 255 };
	static const Pixel REFLECT2 = { 29, 215, 220, 255 };
	static const Pixel BORDER = { 50, 205, 50, 255 };
	static const Pixel FLOOR = { 127, 128, 48, 255 };




	Image<Pixel> image;

	//fill in png vector
	static const Pixel GREEN = { 0, 255, 0, 255 };
	static const Pixel BLUE = { 0, 0, 255, 255 };
	static const Pixel PINK = { 225, 20, 147, 255 };
	static const Pixel PURPLE = { 225, 0, 255, 255 };
	static const Pixel YELLOW = { 225, 225, 0, 255 };
	static const Pixel TEST = { 227, 18, 148, 255 };
	
	



	int xmax = -1;
	int ymax = -1;
	int xmin = -1;
	int ymin = -1;
	int strIndex;
	string currentChar;
	string charName;
	string moveData;
	string frame;
	string moveName;
	string examine;
	
	char c;
	int typecheck;
	bool inHITNHUR;
	bool inSPIKENHUR;
	bool inWINDNHUR;
	bool inSCANNHUR;
	bool inGRABNHUR;

	bool updatethis = false;
	bool updated = false;
	string currentupdate = "";

	int stand_countsaver = 0;
	int stand_start = 0;
	int stand_end = -1;
	bool standfirst = false;

	int standavg_right = 0;
	int standavg_left = 0;

	int count = 0;
	while ((count < png.size() -1 || stand_end == -1) && !(count == stand_start && stand_end == png.size() - 1) )// && count < 7)
	{
		cout << png[count] << endl;
		rangeman.Xhurmin = -1;//hurtbox
		rangeman.Xhurmax = -1;
		rangeman.Xhitmin = -1;//hitbox
		rangeman.Xhitmax = -1;
		rangeman.Xspikemin = -1;//spike
		rangeman.Xspikemax = -1;
		rangeman.XSAmin = -1;//super armor
		rangeman.XSAmax = -1;
		rangeman.XWBmin = -1;//windbox
		rangeman.XWBmax = -1;
		rangeman.Xgrabmin = -1;//grab box
		rangeman.Xgrabmax = -1;
		rangeman.Xreflectmin = -1;//reflector
		rangeman.Xreflectmax = -1;
		rangeman.Xscanmin = -1;//scan
		rangeman.Xscanmax = -1;

		rangeman.Yhurmin = -1;
		rangeman.Yhurmax = -1;
		rangeman.Yhitmin = -1;
		rangeman.Yhitmax = -1;
		rangeman.Yspikemin = -1;
		rangeman.Yspikemax = -1;
		rangeman.YSAmin = -1;
		rangeman.YSAmax = -1;
		rangeman.YWBmin = -1;
		rangeman.YWBmax = -1;
		rangeman.Ygrabmin = -1;
		rangeman.Ygrabmax = -1;
		rangeman.Yreflectmin = -1;
		rangeman.Yreflectmax = -1;
		rangeman.Yscanmin = -1;
		rangeman.Yscanmax = -1;

		rangeman.type = '0';// jab1, jab2
		rangeman.high = false;
		rangeman.low = false;
		rangeman.reverse = false;

		if (count != png.size() - 1)
		{
			try //read in file
			{
				image = readFromFile(png[count] + ".png");
			}
			catch (const runtime_error & error)
			{
				std::cerr << "Error: Input file does not exist \n";
				std::cerr << png[count] + ".png";
				return EXIT_FAILURE;
			}

		}
		


		charName = "";
		moveData = "";
		examine = "";
		frame = "";
		moveName = "";
		strIndex = 0;

		while (strIndex < png[count].length() && png[count][strIndex] != '_')//gets char name
		{
			charName = charName + png[count][strIndex];
			strIndex++;
		}
		if (count == 0)
		{
			initial.name = charName;
			charData.push_back(initial);
		}
		if (initial.name.compare(charName) && stand_end != -1)//new char
		{
			initial.name = charName;
			charData.push_back(initial);
			

			stand_countsaver = count;//searches for stand again
			standfirst = false;
			stand_end = -1;

			standavg_left = 0;
			standavg_right = 0;
			
		}
		strIndex++;//skips underscore
		while (strIndex < png[count].length() && png[count][strIndex] != '-')//char move info
		{
			moveData = moveData + png[count][strIndex];
			strIndex++;
		}
		//stand is first to make things easier for and quicker for comparer program
		if (standfirst == true)//after stand has been found
		{
			if (stand_end == -1)//if stand hasn't been finished yet
			{
				if (moveData.compare("stance_stand"))//once stand ends, go back to start and start again
				{
					for (int i = 0; i < charData[charData.size() - 1].stand.size(); i++)
					{
						standavg_right = standavg_right + charData[charData.size()-1].stand[i].Xhurmax;
						standavg_left = standavg_left + charData[charData.size() - 1].stand[i].Xhurmin;
					}
					standavg_right = standavg_right / charData[charData.size() - 1].stand.size();
					standavg_left = standavg_left / charData[charData.size() - 1].stand.size();
					stand_end = count;
					count = stand_countsaver;
					charName = "";
					moveData = "";
					strIndex = 0;
					while (strIndex < png[count].length() && png[count][strIndex] != '_')//gets char name
					{
						charName = charName + png[count][strIndex];
						strIndex++;
					}

					if (initial.name.compare(charName))//new char
					{
						initial.name = charName;
						charData.push_back(initial);
						stand_countsaver = count;
						standfirst = false;
						stand_end = -1;
						standavg_left = 0;
						standavg_right = 0;
					}
					strIndex++;//skips underscore
					while (strIndex < png[count].length() && png[count][strIndex] != '-')
					{
						moveData = moveData + png[count][strIndex];
						strIndex++;
					}

				}
			}
			else if (count == stand_start)//to avoid doing stand again, stand is skipped
			{
				count = stand_end;
				charName = "";
				moveData = "";
				strIndex = 0;
				while (strIndex < png[count].length() && png[count][strIndex] != '_')//gets char name
				{
					charName = charName + png[count][strIndex];
					strIndex++;
				}
				if (initial.name.compare(charName))//new char
				{
					initial.name = charName;
					charData.push_back(initial);
					stand_countsaver = count;
					standfirst = false;
					stand_end = -1;
					standavg_left = 0;
					standavg_right = 0;
				}
				strIndex++;//skips underscore
				while (strIndex < png[count].length() && png[count][strIndex] != '-')
				{
					moveData = moveData + png[count][strIndex];
					strIndex++;
				}

			}


		}
		while (standfirst == false)//while stand hasn't been found yet
		{
			
			if (!moveData.compare("stance_stand"))//if stand is found, record and enable while loop on top
			{
				stand_start = count;
				standfirst = true;
			}
			else//skips until stand is found
			{
				count++;


				charName = "";
				moveData = "";
				strIndex = 0;

				while (strIndex < png[count].length() && png[count][strIndex] != '_')//gets char name
				{
					charName = charName + png[count][strIndex];
					strIndex++;
				}
				if (initial.name.compare(charName))//new char
				{
					cout << "char's stand frames not found";
					return EXIT_FAILURE;
				}
				strIndex++;//skips underscore
				while (strIndex < png[count].length() && png[count][strIndex] != '-')
				{
					moveData = moveData + png[count][strIndex];
					strIndex++;
				}

			}

		}
		
		

			
		//if(moveData == "stance_stand")

		strIndex++;
		while (strIndex < png[count].length())
		{
			frame = frame + png[count][strIndex];
			strIndex++;
		}

		if (isdigit(moveData[moveData.length() - 1]))
		{
			rangeman.type = moveData[moveData.length() - 1];
		}
		if (rangeman.type == '0')//jabs
		{
			typecheck = 0;
		}
		else
		{
			typecheck = 1;
		}
		for (int i = moveData.length() - 1 - typecheck; i >= 0; i--)
		{
			examine = moveData[i] + examine;
			if (!examine.compare("low") && i > moveData.length() - 1 - typecheck - 5)
			{
				rangeman.low = true;
				examine = "";
			}

			if (!examine.compare("high") && i > moveData.length() - 1 - typecheck - 5)
			{
				rangeman.high = true;
				examine = "";
			}
			//for debugging, unessesary once all files are fixed
			if (!examine.compare("fall") && i > moveData.length() - 1 - typecheck - 6 && updated == false)
			{
				out2 << "Needs to be renamed (fall): " << png[count] << endl;
				updatethis = true;
			}
			if (!examine.compare("rise") && i > moveData.length() - 1 - typecheck - 6 && updated == false)
			{
				out2 << "Needs to be renamed (rise): " << png[count] << endl;
				updatethis = true;
			}
			if (!examine.compare("land") && i > moveData.length() - 1 - typecheck - 6 && updated == false)
			{
				out2 << "Needs to be renamed (land): " << png[count] << endl;
				updatethis = true;
			}
			//
			if (moveData[i] == '_')
			{
				for (int j = 1; j < examine.length(); j++)
				{
					moveName = moveName + examine[j];
				}
			}
		}

		if (currentupdate.compare(moveName))
		{
			updated = false;
			updatethis = false;
		}
		currentupdate = moveName;

		if (count == 0)//gets size of image
		{
			for (int y = 0; y < image.height(); y++)
			{
				for (int x = 0; x < image.width(); x++)
				{
					if (!ComparePixels(image(x, y), BORDER))
					{
						if (xmin > x || xmin == -1)
						{
							xmin = x;
						}
						if (xmax < x || xmax == -1)
						{
							xmax = x;
						}
						if (ymin > y || ymin == -1)
						{
							ymin = y;
						}
						if (ymax < y || ymax == -1)
						{
							ymax = y;
						}
					}
				}
			}
			xmax++;
			ymax++;
		}
		
		
		//if important pixels are touching the boarder, gif needs to be readjusted in order to include all important pixles, maked for later
		for (int y = ymin; y < ymax; y++)
		{
			for (int x = xmin; x < xmax; x++)
			{
				
				if (x == xmin)
				{
					if (!ComparePixels(image(x, y), WHITE)  && !ComparePixels(image(x, y), BLANK) && updated == false)
					{
						out2 << "Needs more up: " << png[count] << endl;
						updatethis = true;
					}
				}
				if (x == xmax-1)
				{
					if (!ComparePixels(image(x, y), WHITE) && !ComparePixels(image(x, y), BLANK) && updated == false)
					{
						out2 << "Needs more down: " << png[count] << endl;
						updatethis = true;
					}
				}
				if (y == ymin)
				{
					if (!ComparePixels(image(x, y), WHITE) && !ComparePixels(image(x, y), BLANK) && updated == false)
					{
						out2 << "Needs more left: " << png[count] << endl;
						updatethis = true;
					}
				}
				if (y == ymax - 1)
				{
					if (!ComparePixels(image(x, y), WHITE) && !ComparePixels(image(x, y), BLANK) && updated == false)
					{
						out2 << "Needs more right: " << png[count] << endl;
						updatethis = true;
					}
				}
				inHITNHUR = false;
				inSPIKENHUR = false;
				inWINDNHUR = false;
				inSCANNHUR = false;
				inGRABNHUR = false;
				if (ComparePixels(image(x, y), HITNHUR))
				{
					inHITNHUR = true;
				}
				if (ComparePixels(image(x, y), SPIKENHUR))
				{
					inSPIKENHUR = true;
				}
				if (ComparePixels(image(x, y), WINDNHUR))
				{
					inWINDNHUR = true;
				}
				if (ComparePixels(image(x, y), SCANNHUR))
				{
					inSCANNHUR = true;
				}
				if (ComparePixels(image(x, y), GRABNHUR))
				{
					inGRABNHUR = true;
				}


				if (ComparePixels(image(x, y), HIT) || inHITNHUR == true || ComparePixels(image(x, y), SPIKE) || inSPIKENHUR == true || ComparePixels(image(x, y), GRAB) || inGRABNHUR == true)
				{
					if (rangeman.Yhitmin < x || rangeman.Yhitmin == -1)
					{
						rangeman.Yhitmin = x;
					}
					if (rangeman.Yhitmax > x || rangeman.Yhitmax == -1)
					{
						rangeman.Yhitmax = x;
					}
					if (rangeman.Xhitmin > y || rangeman.Xhitmin == -1)
					{
						rangeman.Xhitmin = y;
					}
					if (rangeman.Xhitmax < y || rangeman.Xhitmax == -1)
					{
						rangeman.Xhitmax = y;
					}

					if (stand_end != -1)//waits until stand data is gotten
					{
						if ((rangeman.Yhitmin < x || rangeman.Yhitmin == -1) && (y < standavg_left))
						{
							rangeman.YhitminL = x;
						}
						if ((rangeman.Yhitmax > x || rangeman.Yhitmax == -1) && (y < standavg_left))
						{
							rangeman.YhitmaxL = x;
						}
						if ((rangeman.Yhitmin < x || rangeman.Yhitmin == -1) && (y < standavg_right))
						{
							rangeman.YhitminR = x;
						}
						if ((rangeman.Yhitmax > x || rangeman.Yhitmax == -1) && (y < standavg_right))
						{
							rangeman.YhitmaxR = x;
						}
					}
				}
				if (ComparePixels(image(x, y), HUR) || inHITNHUR == true || inSPIKENHUR == true || inWINDNHUR == true || inSCANNHUR == true || inGRABNHUR == true)
				{
					if (rangeman.Yhurmin < x || rangeman.Yhurmin == -1)
					{
						rangeman.Yhurmin = x;
					}
					if (rangeman.Yhurmax > x || rangeman.Yhurmax == -1)
					{
						rangeman.Yhurmax = x;
					}
					if (rangeman.Xhurmin > y || rangeman.Xhurmin == -1)
					{
						rangeman.Xhurmin = y;
					}
					if (rangeman.Xhurmax < y || rangeman.Xhurmax == -1)
					{
						rangeman.Xhurmax = y;
					}
				}
				if (ComparePixels(image(x, y), SPIKE) || inSPIKENHUR == true)
				{
					if (rangeman.Yspikemin < x || rangeman.Yspikemin == -1)
					{
						rangeman.Yspikemin = x;
					}
					if (rangeman.Yspikemax > x || rangeman.Yspikemax == -1)
					{
						rangeman.Yspikemax = x;
					}
					if (rangeman.Xspikemin > y || rangeman.Xspikemin == -1)
					{
						rangeman.Xspikemin = y;
					}
					if (rangeman.Xspikemax < y || rangeman.Xspikemax == -1)
					{
						rangeman.Xspikemax = y;
					}
				}
				if (ComparePixels(image(x, y), WIND) || inWINDNHUR == true)
				{
					if (rangeman.YWBmin < x || rangeman.YWBmin == -1)
					{
						rangeman.YWBmin = x;
					}
					if (rangeman.YWBmax > x || rangeman.YWBmax == -1)
					{
						rangeman.YWBmax = x;
					}
					if (rangeman.XWBmin > y || rangeman.XWBmin == -1)
					{
						rangeman.XWBmin = y;
					}
					if (rangeman.XWBmax < y || rangeman.XWBmax == -1)
					{
						rangeman.XWBmax = y;
					}
				}
				if (ComparePixels(image(x, y), GRAB) || inGRABNHUR == true)
				{
					if (rangeman.Ygrabmin < x || rangeman.Ygrabmin == -1)
					{
						rangeman.Ygrabmin = x;
					}
					if (rangeman.Ygrabmax > x || rangeman.Ygrabmax == -1)
					{
						rangeman.Ygrabmax = x;
					}
					if (rangeman.Xgrabmin > y || rangeman.Xgrabmin == -1)
					{
						rangeman.Xgrabmin = y;
					}
					if (rangeman.Xgrabmax < y || rangeman.Xgrabmax == -1)
					{
						rangeman.Xgrabmax = y;
					}
				}
				if (ComparePixels(image(x, y), SCAN) || inSCANNHUR == true)
				{
					if (rangeman.Yscanmin < x || rangeman.Yscanmin == -1)
					{
						rangeman.Yscanmin = x;
					}
					if (rangeman.Yscanmax > x || rangeman.Yscanmax == -1)
					{
						rangeman.Yscanmax = x;
					}
					if (rangeman.Xscanmin > y || rangeman.Xscanmin == -1)
					{
						rangeman.Xscanmin = y;
					}
					if (rangeman.Xscanmax < y || rangeman.Xscanmax == -1)
					{
						rangeman.Xscanmax = y;
					}
				}
				if (ComparePixels(image(x, y), REFLECT) || ComparePixels(image(x, y), REFLECT2))
				{
					if (rangeman.Yreflectmin < x || rangeman.Yreflectmin == -1)
					{
						rangeman.Yreflectmin = x;
					}
					if (rangeman.Yreflectmax > x || rangeman.Yreflectmax == -1)
					{
						rangeman.Yreflectmax = x;
					}
					if (rangeman.Xreflectmin > y || rangeman.Xreflectmin == -1)
					{
						rangeman.Xreflectmin = y;
					}
					if (rangeman.Xreflectmax < y || rangeman.Xreflectmax == -1)
					{
						rangeman.Xreflectmax = y;
					}
					if (updated == false)
					{
						out2 << "Contains reflector: " << png[count] << endl;
						updatethis = true;
					}
				}
				if (ComparePixels(image(x, y), SA) || ComparePixels(image(x, y), FLOOR))//CHANGE
				{
					if (rangeman.YSAmin < x || rangeman.YSAmin == -1)
					{
						rangeman.YSAmin = x;
					}
					if (rangeman.YSAmax > x || rangeman.YSAmax == -1)
					{
						rangeman.YSAmax = x;
					}
					if (rangeman.XSAmin > y || rangeman.XSAmin == -1)
					{
						rangeman.XSAmin = y;
					}
					if (rangeman.XSAmax < y || rangeman.XSAmax == -1)
					{
						rangeman.XSAmax = y;
					}
				}

				if (updatethis == true)
				{
					updated = true;
				}

			}

		}

		if (!moveName.compare("stand"))
		{
			charData[charData.size() - 1].stand.push_back(rangeman);
		}
		if (!moveName.compare("ledgegrab"))
		{
			charData[charData.size() - 1].ledgegrab.push_back(rangeman);
		}
		if (!moveName.compare("jumpsquat"))
		{
			charData[charData.size() - 1].jumpsquat.push_back(rangeman);
		}
		if (!moveName.compare("duck"))
		{
			charData[charData.size() - 1].duck.push_back(rangeman);
		}
		if (!moveName.compare("crawlback"))
		{
			charData[charData.size() - 1].crawlback.push_back(rangeman);
		}
		if (!moveName.compare("crawlforth"))
		{
			charData[charData.size() - 1].crawlforth.push_back(rangeman);
		}
		if (!moveName.compare("jabrapid"))
		{
			charData[charData.size() - 1].jabrapid.push_back(rangeman);
		}
		if (!moveName.compare("jab"))
		{
			charData[charData.size() - 1].jab.push_back(rangeman);
		}
		if (!moveName.compare("dashattack"))
		{
			charData[charData.size() - 1].dashattack.push_back(rangeman);
		}
		if (!moveName.compare("jabend"))
		{
			charData[charData.size() - 1].jabend.push_back(rangeman);
		}
		if (!moveName.compare("sidetilt"))
		{
			charData[charData.size() - 1].sidetilt.push_back(rangeman);
		}
		if (!moveName.compare("uptilt"))
		{
			charData[charData.size() - 1].uptilt.push_back(rangeman);
		}
		if (!moveName.compare("downtilt"))
		{
			charData[charData.size() - 1].downtilt.push_back(rangeman);
		}
		if (!moveName.compare("sidesmash"))
		{
			charData[charData.size() - 1].sidesmash.push_back(rangeman);
		}
		if (!moveName.compare("upsmash"))
		{
			charData[charData.size() - 1].upsmash.push_back(rangeman);
		}
		if (!moveName.compare("downsmash"))
		{
			charData[charData.size() - 1].downsmash.push_back(rangeman);
		}
		if (!moveName.compare("bair"))
		{
			charData[charData.size() - 1].bair.push_back(rangeman);
		}
		if (!moveName.compare("fair"))
		{
			charData[charData.size() - 1].fair.push_back(rangeman);
		}
		if (!moveName.compare("upair"))
		{
			charData[charData.size() - 1].upair.push_back(rangeman);
		}
		if (!moveName.compare("dair"))
		{
			charData[charData.size() - 1].dair.push_back(rangeman);
		}
		if (!moveName.compare("nair"))
		{
			charData[charData.size() - 1].nair.push_back(rangeman);
		}
		if (!moveName.compare("landingbair"))
		{
			charData[charData.size() - 1].landingbair.push_back(rangeman);
		}
		if (!moveName.compare("landingfair"))
		{
			charData[charData.size() - 1].landingfair.push_back(rangeman);
		}
		if (!moveName.compare("landingupair"))
		{
			charData[charData.size() - 1].landingupair.push_back(rangeman);
		}
		if (!moveName.compare("landingdair"))
		{
			charData[charData.size() - 1].landingdair.push_back(rangeman);
		}
		if (!moveName.compare("landingnair"))
		{
			charData[charData.size() - 1].landingnair.push_back(rangeman);
		}
		if (!moveName.compare("neutralbair"))
		{
			charData[charData.size() - 1].neutralbair.push_back(rangeman);
		}
		if (!moveName.compare("neutralb"))
		{
			charData[charData.size() - 1].neutralb.push_back(rangeman);
		}
		if (!moveName.compare("landingneutralb"))
		{
			charData[charData.size() - 1].landingneutralb.push_back(rangeman);
		}
		if (!moveName.compare("sidebair"))
		{
			charData[charData.size() - 1].sidebair.push_back(rangeman);
		}
		if (!moveName.compare("sideb"))
		{
			charData[charData.size() - 1].sideb.push_back(rangeman);
		}
		if (!moveName.compare("landingsideb"))
		{
			charData[charData.size() - 1].landingsideb.push_back(rangeman);
		}
		if (!moveName.compare("upbair"))
		{
			charData[charData.size() - 1].upbair.push_back(rangeman);
		}
		if (!moveName.compare("upb"))
		{
			charData[charData.size() - 1].upb.push_back(rangeman);
		}
		if (!moveName.compare("landingupb"))
		{
			charData[charData.size() - 1].landingupb.push_back(rangeman);
		}
		if (!moveName.compare("downbair"))
		{
			charData[charData.size() - 1].downbair.push_back(rangeman);
		}
		if (!moveName.compare("downb"))
		{
			charData[charData.size() - 1].downb.push_back(rangeman);
		}
		if (!moveName.compare("landingdownb"))
		{
			charData[charData.size() - 1].landingdownb.push_back(rangeman);
		}
		if (!moveName.compare("grab"))
		{
			charData[charData.size() - 1].grab.push_back(rangeman);
		}
		if (!moveName.compare("dashgrab"))
		{
			charData[charData.size() - 1].dashgrab.push_back(rangeman);
		}
		if (!moveName.compare("pivotgrab"))
		{
			charData[charData.size() - 1].pivotgrab.push_back(rangeman);
		}
		count++;
	}//end of loop
	/*
	cout << rangeman.Xhitmin << endl;
	cout << rangeman.Xhitmax << endl;
	cout << image.width() << endl;

	for (int i = rangeman.Xhitmin; i <= rangeman.Xhitmax; i++)
	{
		image(i, ((rangeman.Yhitmax - rangeman.Yhitmin) / 2 + rangeman.Yhitmin)) = BLUE;
	}
	cout << "here1 \n";
	for (int i = rangeman.Yhitmin; i <= rangeman.Yhitmax; i++)
	{
		image(((rangeman.Xhitmax - rangeman.Xhitmin) / 2 + rangeman.Xhitmin), i) = PURPLE;
	}
	cout << "here2 \n";
	for (int i = rangeman.Xhurmin; i <= rangeman.Xhurmax; i++)
	{
		image(i, ((rangeman.Yhurmax - rangeman.Yhurmin) / 2 + rangeman.Yhurmin)) = GREEN;
	}
	cout << "here3 \n";
	for (int i = rangeman.Yhurmin; i <= rangeman.Yhurmax; i++)
	{
		image(((rangeman.Xhurmax - rangeman.Xhurmin) / 2 + rangeman.Xhurmin), i) = YELLOW;
	}
	cout << "here4 \n";
	writeToFile(image, "ikeresults.png");
	*/


	char currentC = 'R';
	bool highcheck = false;
	bool lowcheck = false;
	
	for (int i = 0; i < charData.size(); i++)
	{
		out << charData[i].name << " : ";
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].stand.size() != 0)
		{
			for (int j = 0; j < charData[i].stand.size(); j++)
			{
				if (charData[i].stand[j].low != lowcheck || charData[i].stand[j].high != highcheck || charData[i].stand[j].type != currentC)
				{
					out << endl;
					out << "stand";
					if (charData[i].stand[j].low != lowcheck)
					{
						if (charData[i].stand[j].low == true)
						{
							out << "low";
						}
						lowcheck = charData[i].stand[j].low;
					}
					if (charData[i].stand[j].high != highcheck)
					{
						if (true == charData[i].stand[j].high)
						{
							out << "high";
						}
						highcheck = charData[i].stand[j].high;
					}
					if (charData[i].stand[j].type != currentC)
					{
						if (charData[i].stand[j].type != '0')
						{
							out << charData[i].stand[j].type;
						}
						currentC = charData[i].stand[j].type;
					}
					out << " : ";
				}

				out << charData[i].stand[j].Xhurmin << ',';//hurtbox
				out << charData[i].stand[j].Xhurmax << ',';
				out << charData[i].stand[j].Yhurmin << ',';
				out << charData[i].stand[j].Yhurmax << ',';
				out << charData[i].stand[j].Xhitmin << ',';//hitbox
				out << charData[i].stand[j].Xhitmax << ',';
				out << charData[i].stand[j].Yhitmin << ',';
				out << charData[i].stand[j].YhitmaxR << ',';
				out << charData[i].stand[j].YhitminR << ',';
				out << charData[i].stand[j].YhitmaxL << ',';
				out << charData[i].stand[j].YhitminL << ',';
				out << charData[i].stand[j].Yhitmax << ',';
				out << charData[i].stand[j].Xspikemin << ',';//spike
				out << charData[i].stand[j].Xspikemax << ',';
				out << charData[i].stand[j].Yspikemin << ',';
				out << charData[i].stand[j].Yspikemax << ',';
				out << charData[i].stand[j].XSAmin << ',';//super armor
				out << charData[i].stand[j].XSAmax << ',';
				out << charData[i].stand[j].YSAmin << ',';
				out << charData[i].stand[j].YSAmax << ',';
				out << charData[i].stand[j].XWBmin << ',';//windbox
				out << charData[i].stand[j].XWBmax << ',';
				out << charData[i].stand[j].YWBmin << ',';
				out << charData[i].stand[j].YWBmax << ',';
				out << charData[i].stand[j].Xgrabmin << ',';//grab box
				out << charData[i].stand[j].Xgrabmax << ',';
				out << charData[i].stand[j].Ygrabmin << ',';
				out << charData[i].stand[j].Ygrabmax << ',';
				out << charData[i].stand[j].Xreflectmin << ',';//reflector
				out << charData[i].stand[j].Xreflectmax << ',';
				out << charData[i].stand[j].Yreflectmin << ',';
				out << charData[i].stand[j].Yreflectmax << ',';
				out << charData[i].stand[j].Xscanmin << ',';//scan
				out << charData[i].stand[j].Xscanmax << ',';
				out << charData[i].stand[j].Yscanmin << ',';
				out << charData[i].stand[j].Yscanmax << ',';
				out << ' ';
			}
		}
		else
		{
			out << endl;
			out << "stand : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].ledgegrab.size() != 0)
		{
		for (int j = 0; j < charData[i].ledgegrab.size(); j++)
		{
			if (charData[i].ledgegrab[j].low != lowcheck || charData[i].ledgegrab[j].high != highcheck || charData[i].ledgegrab[j].type != currentC)
			{
				out << endl;
				out << "ledgegrab";
				if (charData[i].ledgegrab[j].low != lowcheck)
				{
					if (charData[i].ledgegrab[j].low == true)
					{
						out << "low";
					}
					lowcheck = charData[i].ledgegrab[j].low;
				}
				if (charData[i].ledgegrab[j].high != highcheck)
				{
					if (true == charData[i].ledgegrab[j].high)
					{
						out << "high";
					}
					highcheck = charData[i].ledgegrab[j].high;
				}
				if (charData[i].ledgegrab[j].type != currentC)
				{
					if (charData[i].ledgegrab[j].type != '0')
					{
						out << charData[i].ledgegrab[j].type;
					}
					currentC = charData[i].ledgegrab[j].type;
				}
				out << " : ";
			}

			out << charData[i].ledgegrab[j].Xhurmin << ',';//hurtbox
			out << charData[i].ledgegrab[j].Xhurmax << ',';
			out << charData[i].ledgegrab[j].Yhurmin << ',';
			out << charData[i].ledgegrab[j].Yhurmax << ',';
			out << charData[i].ledgegrab[j].Xhitmin << ',';//hitbox
			out << charData[i].ledgegrab[j].Xhitmax << ',';
			out << charData[i].ledgegrab[j].Yhitmin << ',';
			out << charData[i].ledgegrab[j].Yhitmax << ',';
			out << charData[i].ledgegrab[j].YhitmaxR << ',';
			out << charData[i].ledgegrab[j].YhitminR << ',';
			out << charData[i].ledgegrab[j].YhitmaxL << ',';
			out << charData[i].ledgegrab[j].YhitminL << ',';
			out << charData[i].ledgegrab[j].Xspikemin << ',';//spike
			out << charData[i].ledgegrab[j].Xspikemax << ',';
			out << charData[i].ledgegrab[j].Yspikemin << ',';
			out << charData[i].ledgegrab[j].Yspikemax << ',';
			out << charData[i].ledgegrab[j].XSAmin << ',';//super armor
			out << charData[i].ledgegrab[j].XSAmax << ',';
			out << charData[i].ledgegrab[j].YSAmin << ',';
			out << charData[i].ledgegrab[j].YSAmax << ',';
			out << charData[i].ledgegrab[j].XWBmin << ',';//windbox
			out << charData[i].ledgegrab[j].XWBmax << ',';
			out << charData[i].ledgegrab[j].YWBmin << ',';
			out << charData[i].ledgegrab[j].YWBmax << ',';
			out << charData[i].ledgegrab[j].Xgrabmin << ',';//grab box
			out << charData[i].ledgegrab[j].Xgrabmax << ',';
			out << charData[i].ledgegrab[j].Ygrabmin << ',';
			out << charData[i].ledgegrab[j].Ygrabmax << ',';
			out << charData[i].ledgegrab[j].Xreflectmin << ',';//reflector
			out << charData[i].ledgegrab[j].Xreflectmax << ',';
			out << charData[i].ledgegrab[j].Yreflectmin << ',';
			out << charData[i].ledgegrab[j].Yreflectmax << ',';
			out << charData[i].ledgegrab[j].Xscanmin << ',';//scan
			out << charData[i].ledgegrab[j].Xscanmax << ',';
			out << charData[i].ledgegrab[j].Yscanmin << ',';
			out << charData[i].ledgegrab[j].Yscanmax << ',';
			out << ' ';
		}
		}
		else
		{
			out << endl;
			out << "ledgegrab : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].jumpsquat.size() != 0)
		{
		for (int j = 0; j < charData[i].jumpsquat.size(); j++)
		{
			if (charData[i].jumpsquat[j].low != lowcheck || charData[i].jumpsquat[j].high != highcheck || charData[i].jumpsquat[j].type != currentC)
			{
				out << endl;
				out << "jumpsquat";
				if (charData[i].jumpsquat[j].low != lowcheck)
				{
					if (charData[i].jumpsquat[j].low == true)
					{
						out << "low";
					}
					lowcheck = charData[i].jumpsquat[j].low;
				}
				if (charData[i].jumpsquat[j].high != highcheck)
				{
					if (true == charData[i].jumpsquat[j].high)
					{
						out << "high";
					}
					highcheck = charData[i].jumpsquat[j].high;
				}
				if (charData[i].jumpsquat[j].type != currentC)
				{
					if (charData[i].jumpsquat[j].type != '0')
					{
						out << charData[i].jumpsquat[j].type;
					}
					currentC = charData[i].jumpsquat[j].type;
				}
				out << " : ";
			}

			out << charData[i].jumpsquat[j].Xhurmin << ',';//hurtbox
			out << charData[i].jumpsquat[j].Xhurmax << ',';
			out << charData[i].jumpsquat[j].Yhurmin << ',';
			out << charData[i].jumpsquat[j].Yhurmax << ',';
			out << charData[i].jumpsquat[j].Xhitmin << ',';//hitbox
			out << charData[i].jumpsquat[j].Xhitmax << ',';
			out << charData[i].jumpsquat[j].Yhitmin << ',';
			out << charData[i].jumpsquat[j].Yhitmax << ',';
			out << charData[i].jumpsquat[j].YhitmaxR << ',';
			out << charData[i].jumpsquat[j].YhitminR << ',';
			out << charData[i].jumpsquat[j].YhitmaxL << ',';
			out << charData[i].jumpsquat[j].YhitminL << ',';
			out << charData[i].jumpsquat[j].Xspikemin << ',';//spike
			out << charData[i].jumpsquat[j].Xspikemax << ',';
			out << charData[i].jumpsquat[j].Yspikemin << ',';
			out << charData[i].jumpsquat[j].Yspikemax << ',';
			out << charData[i].jumpsquat[j].XSAmin << ',';//super armor
			out << charData[i].jumpsquat[j].XSAmax << ',';
			out << charData[i].jumpsquat[j].YSAmin << ',';
			out << charData[i].jumpsquat[j].YSAmax << ',';
			out << charData[i].jumpsquat[j].XWBmin << ',';//windbox
			out << charData[i].jumpsquat[j].XWBmax << ',';
			out << charData[i].jumpsquat[j].YWBmin << ',';
			out << charData[i].jumpsquat[j].YWBmax << ',';
			out << charData[i].jumpsquat[j].Xgrabmin << ',';//grab box
			out << charData[i].jumpsquat[j].Xgrabmax << ',';
			out << charData[i].jumpsquat[j].Ygrabmin << ',';
			out << charData[i].jumpsquat[j].Ygrabmax << ',';
			out << charData[i].jumpsquat[j].Xreflectmin << ',';//reflector
			out << charData[i].jumpsquat[j].Xreflectmax << ',';
			out << charData[i].jumpsquat[j].Yreflectmin << ',';
			out << charData[i].jumpsquat[j].Yreflectmax << ',';
			out << charData[i].jumpsquat[j].Xscanmin << ',';//scan
			out << charData[i].jumpsquat[j].Xscanmax << ',';
			out << charData[i].jumpsquat[j].Yscanmin << ',';
			out << charData[i].jumpsquat[j].Yscanmax << ',';
			out << ' ';
		}
		}
		else
		{
			out << endl;
			out << "jumpsquat : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].duck.size() != 0)
		{
		for (int j = 0; j < charData[i].duck.size(); j++)
		{
			if (charData[i].duck[j].low != lowcheck || charData[i].duck[j].high != highcheck || charData[i].duck[j].type != currentC)
			{
				out << endl;
				out << "duck";
				if (charData[i].duck[j].low != lowcheck)
				{
					if (charData[i].duck[j].low == true)
					{
						out << "low";
					}
					lowcheck = charData[i].duck[j].low;
				}
				if (charData[i].duck[j].high != highcheck)
				{
					if (true == charData[i].duck[j].high)
					{
						out << "high";
					}
					highcheck = charData[i].duck[j].high;
				}
				if (charData[i].duck[j].type != currentC)
				{
					if (charData[i].duck[j].type != '0')
					{
						out << charData[i].duck[j].type;
					}
					currentC = charData[i].duck[j].type;
				}
				out << " : ";
			}

			out << charData[i].duck[j].Xhurmin << ',';//hurtbox
			out << charData[i].duck[j].Xhurmax << ',';
			out << charData[i].duck[j].Yhurmin << ',';
			out << charData[i].duck[j].Yhurmax << ',';
			out << charData[i].duck[j].Xhitmin << ',';//hitbox
			out << charData[i].duck[j].Xhitmax << ',';
			out << charData[i].duck[j].Yhitmin << ',';
			out << charData[i].duck[j].Yhitmax << ',';
			out << charData[i].duck[j].YhitmaxR << ',';
			out << charData[i].duck[j].YhitminR << ',';
			out << charData[i].duck[j].YhitmaxL << ',';
			out << charData[i].duck[j].YhitminL << ',';
			out << charData[i].duck[j].Xspikemin << ',';//spike
			out << charData[i].duck[j].Xspikemax << ',';
			out << charData[i].duck[j].Yspikemin << ',';
			out << charData[i].duck[j].Yspikemax << ',';
			out << charData[i].duck[j].XSAmin << ',';//super armor
			out << charData[i].duck[j].XSAmax << ',';
			out << charData[i].duck[j].YSAmin << ',';
			out << charData[i].duck[j].YSAmax << ',';
			out << charData[i].duck[j].XWBmin << ',';//windbox
			out << charData[i].duck[j].XWBmax << ',';
			out << charData[i].duck[j].YWBmin << ',';
			out << charData[i].duck[j].YWBmax << ',';
			out << charData[i].duck[j].Xgrabmin << ',';//grab box
			out << charData[i].duck[j].Xgrabmax << ',';
			out << charData[i].duck[j].Ygrabmin << ',';
			out << charData[i].duck[j].Ygrabmax << ',';
			out << charData[i].duck[j].Xreflectmin << ',';//reflector
			out << charData[i].duck[j].Xreflectmax << ',';
			out << charData[i].duck[j].Yreflectmin << ',';
			out << charData[i].duck[j].Yreflectmax << ',';
			out << charData[i].duck[j].Xscanmin << ',';//scan
			out << charData[i].duck[j].Xscanmax << ',';
			out << charData[i].duck[j].Yscanmin << ',';
			out << charData[i].duck[j].Yscanmax << ',';
			out << ' ';
		}
		}
		else
		{
			out << endl;
			out << "duck : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].crawlback.size() != 0)
		{
		for (int j = 0; j < charData[i].crawlback.size(); j++)
		{
			if (charData[i].crawlback[j].low != lowcheck || charData[i].crawlback[j].high != highcheck || charData[i].crawlback[j].type != currentC)
			{
				out << endl;
				out << "crawlback";
				if (charData[i].crawlback[j].low != lowcheck)
				{
					if (charData[i].crawlback[j].low == true)
					{
						out << "low";
					}
					lowcheck = charData[i].crawlback[j].low;
				}
				if (charData[i].crawlback[j].high != highcheck)
				{
					if (true == charData[i].crawlback[j].high)
					{
						out << "high";
					}
					highcheck = charData[i].crawlback[j].high;
				}
				if (charData[i].crawlback[j].type != currentC)
				{
					if (charData[i].crawlback[j].type != '0')
					{
						out << charData[i].crawlback[j].type;
					}
					currentC = charData[i].crawlback[j].type;
				}
				out << " : ";
			}

			out << charData[i].crawlback[j].Xhurmin << ',';//hurtbox
			out << charData[i].crawlback[j].Xhurmax << ',';
			out << charData[i].crawlback[j].Yhurmin << ',';
			out << charData[i].crawlback[j].Yhurmax << ',';
			out << charData[i].crawlback[j].Xhitmin << ',';//hitbox
			out << charData[i].crawlback[j].Xhitmax << ',';
			out << charData[i].crawlback[j].Yhitmin << ',';
			out << charData[i].crawlback[j].Yhitmax << ',';
			out << charData[i].crawlback[j].YhitmaxR << ',';
			out << charData[i].crawlback[j].YhitminR << ',';
			out << charData[i].crawlback[j].YhitmaxL << ',';
			out << charData[i].crawlback[j].YhitminL << ',';
			out << charData[i].crawlback[j].Xspikemin << ',';//spike
			out << charData[i].crawlback[j].Xspikemax << ',';
			out << charData[i].crawlback[j].Yspikemin << ',';
			out << charData[i].crawlback[j].Yspikemax << ',';
			out << charData[i].crawlback[j].XSAmin << ',';//super armor
			out << charData[i].crawlback[j].XSAmax << ',';
			out << charData[i].crawlback[j].YSAmin << ',';
			out << charData[i].crawlback[j].YSAmax << ',';
			out << charData[i].crawlback[j].XWBmin << ',';//windbox
			out << charData[i].crawlback[j].XWBmax << ',';
			out << charData[i].crawlback[j].YWBmin << ',';
			out << charData[i].crawlback[j].YWBmax << ',';
			out << charData[i].crawlback[j].Xgrabmin << ',';//grab box
			out << charData[i].crawlback[j].Xgrabmax << ',';
			out << charData[i].crawlback[j].Ygrabmin << ',';
			out << charData[i].crawlback[j].Ygrabmax << ',';
			out << charData[i].crawlback[j].Xreflectmin << ',';//reflector
			out << charData[i].crawlback[j].Xreflectmax << ',';
			out << charData[i].crawlback[j].Yreflectmin << ',';
			out << charData[i].crawlback[j].Yreflectmax << ',';
			out << charData[i].crawlback[j].Xscanmin << ',';//scan
			out << charData[i].crawlback[j].Xscanmax << ',';
			out << charData[i].crawlback[j].Yscanmin << ',';
			out << charData[i].crawlback[j].Yscanmax << ',';
			out << ' ';
		}
		}
		else
		{
			out << endl;
			out << "crawlback : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].crawlforth.size() != 0)
		{
		for (int j = 0; j < charData[i].crawlforth.size(); j++)
		{
			if (charData[i].crawlforth[j].low != lowcheck || charData[i].crawlforth[j].high != highcheck || charData[i].crawlforth[j].type != currentC)
			{
				out << endl;
				out << "crawlforth";
				if (charData[i].crawlforth[j].low != lowcheck)
				{
					if (charData[i].crawlforth[j].low == true)
					{
						out << "low";
					}
					lowcheck = charData[i].crawlforth[j].low;
				}
				if (charData[i].crawlforth[j].high != highcheck)
				{
					if (true == charData[i].crawlforth[j].high)
					{
						out << "high";
					}
					highcheck = charData[i].crawlforth[j].high;
				}
				if (charData[i].crawlforth[j].type != currentC)
				{
					if (charData[i].crawlforth[j].type != '0')
					{
						out << charData[i].crawlforth[j].type;
					}
					currentC = charData[i].crawlforth[j].type;
				}
				out << " : ";
			}

			out << charData[i].crawlforth[j].Xhurmin << ',';//hurtbox
			out << charData[i].crawlforth[j].Xhurmax << ',';
			out << charData[i].crawlforth[j].Yhurmin << ',';
			out << charData[i].crawlforth[j].Yhurmax << ',';
			out << charData[i].crawlforth[j].Xhitmin << ',';//hitbox
			out << charData[i].crawlforth[j].Xhitmax << ',';
			out << charData[i].crawlforth[j].Yhitmin << ',';
			out << charData[i].crawlforth[j].Yhitmax << ',';
			out << charData[i].crawlforth[j].YhitmaxR << ',';
			out << charData[i].crawlforth[j].YhitminR << ',';
			out << charData[i].crawlforth[j].YhitmaxL << ',';
			out << charData[i].crawlforth[j].YhitminL << ',';
			out << charData[i].crawlforth[j].Xspikemin << ',';//spike
			out << charData[i].crawlforth[j].Xspikemax << ',';
			out << charData[i].crawlforth[j].Yspikemin << ',';
			out << charData[i].crawlforth[j].Yspikemax << ',';
			out << charData[i].crawlforth[j].XSAmin << ',';//super armor
			out << charData[i].crawlforth[j].XSAmax << ',';
			out << charData[i].crawlforth[j].YSAmin << ',';
			out << charData[i].crawlforth[j].YSAmax << ',';
			out << charData[i].crawlforth[j].XWBmin << ',';//windbox
			out << charData[i].crawlforth[j].XWBmax << ',';
			out << charData[i].crawlforth[j].YWBmin << ',';
			out << charData[i].crawlforth[j].YWBmax << ',';
			out << charData[i].crawlforth[j].Xgrabmin << ',';//grab box
			out << charData[i].crawlforth[j].Xgrabmax << ',';
			out << charData[i].crawlforth[j].Ygrabmin << ',';
			out << charData[i].crawlforth[j].Ygrabmax << ',';
			out << charData[i].crawlforth[j].Xreflectmin << ',';//reflector
			out << charData[i].crawlforth[j].Xreflectmax << ',';
			out << charData[i].crawlforth[j].Yreflectmin << ',';
			out << charData[i].crawlforth[j].Yreflectmax << ',';
			out << charData[i].crawlforth[j].Xscanmin << ',';//scan
			out << charData[i].crawlforth[j].Xscanmax << ',';
			out << charData[i].crawlforth[j].Yscanmin << ',';
			out << charData[i].crawlforth[j].Yscanmax << ',';
			out << ' ';
		}
		}
		else
		{
			out << endl;
			out << "crawlforth : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].jabrapid.size() != 0)
		{
		for (int j = 0; j < charData[i].jabrapid.size(); j++)
		{
			if (charData[i].jabrapid[j].low != lowcheck || charData[i].jabrapid[j].high != highcheck || charData[i].jabrapid[j].type != currentC)
			{
				out << endl;
				out << "jabrapid";
				if (charData[i].jabrapid[j].low != lowcheck)
				{
					if (charData[i].jabrapid[j].low == true)
					{
						out << "low";
					}
					lowcheck = charData[i].jabrapid[j].low;
				}
				if (charData[i].jabrapid[j].high != highcheck)
				{
					if (true == charData[i].jabrapid[j].high)
					{
						out << "high";
					}
					highcheck = charData[i].jabrapid[j].high;
				}
				if (charData[i].jabrapid[j].type != currentC)
				{
					if (charData[i].jabrapid[j].type != '0')
					{
						out << charData[i].jabrapid[j].type;
					}
					currentC = charData[i].jabrapid[j].type;
				}
				out << " : ";
			}

			out << charData[i].jabrapid[j].Xhurmin << ',';//hurtbox
			out << charData[i].jabrapid[j].Xhurmax << ',';
			out << charData[i].jabrapid[j].Yhurmin << ',';
			out << charData[i].jabrapid[j].Yhurmax << ',';
			out << charData[i].jabrapid[j].Xhitmin << ',';//hitbox
			out << charData[i].jabrapid[j].Xhitmax << ',';
			out << charData[i].jabrapid[j].Yhitmin << ',';
			out << charData[i].jabrapid[j].Yhitmax << ',';
			out << charData[i].jabrapid[j].YhitmaxR << ',';
			out << charData[i].jabrapid[j].YhitminR << ',';
			out << charData[i].jabrapid[j].YhitmaxL << ',';
			out << charData[i].jabrapid[j].YhitminL << ',';
			out << charData[i].jabrapid[j].Xspikemin << ',';//spike
			out << charData[i].jabrapid[j].Xspikemax << ',';
			out << charData[i].jabrapid[j].Yspikemin << ',';
			out << charData[i].jabrapid[j].Yspikemax << ',';
			out << charData[i].jabrapid[j].XSAmin << ',';//super armor
			out << charData[i].jabrapid[j].XSAmax << ',';
			out << charData[i].jabrapid[j].YSAmin << ',';
			out << charData[i].jabrapid[j].YSAmax << ',';
			out << charData[i].jabrapid[j].XWBmin << ',';//windbox
			out << charData[i].jabrapid[j].XWBmax << ',';
			out << charData[i].jabrapid[j].YWBmin << ',';
			out << charData[i].jabrapid[j].YWBmax << ',';
			out << charData[i].jabrapid[j].Xgrabmin << ',';//grab box
			out << charData[i].jabrapid[j].Xgrabmax << ',';
			out << charData[i].jabrapid[j].Ygrabmin << ',';
			out << charData[i].jabrapid[j].Ygrabmax << ',';
			out << charData[i].jabrapid[j].Xreflectmin << ',';//reflector
			out << charData[i].jabrapid[j].Xreflectmax << ',';
			out << charData[i].jabrapid[j].Yreflectmin << ',';
			out << charData[i].jabrapid[j].Yreflectmax << ',';
			out << charData[i].jabrapid[j].Xscanmin << ',';//scan
			out << charData[i].jabrapid[j].Xscanmax << ',';
			out << charData[i].jabrapid[j].Yscanmin << ',';
			out << charData[i].jabrapid[j].Yscanmax << ',';
			out << ' ';
		}
		}
		else
		{
			out << endl;
			out << "jabrapid : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].jab.size() != 0)
		{
		for (int j = 0; j < charData[i].jab.size(); j++)
		{
			if (charData[i].jab[j].low != lowcheck || charData[i].jab[j].high != highcheck || charData[i].jab[j].type != currentC)
			{
				out << endl;
				out << "jab";
				if (charData[i].jab[j].low != lowcheck)
				{
					if (charData[i].jab[j].low == true)
					{
						out << "low";
					}
					lowcheck = charData[i].jab[j].low;
				}
				if (charData[i].jab[j].high != highcheck)
				{
					if (true == charData[i].jab[j].high)
					{
						out << "high";
					}
					highcheck = charData[i].jab[j].high;
				}
				if (charData[i].jab[j].type != currentC)
				{
					if (charData[i].jab[j].type != '0')
					{
						out << charData[i].jab[j].type;
					}
					currentC = charData[i].jab[j].type;
				}
				out << " : ";
			}

			out << charData[i].jab[j].Xhurmin << ',';//hurtbox
			out << charData[i].jab[j].Xhurmax << ',';
			out << charData[i].jab[j].Yhurmin << ',';
			out << charData[i].jab[j].Yhurmax << ',';
			out << charData[i].jab[j].Xhitmin << ',';//hitbox
			out << charData[i].jab[j].Xhitmax << ',';
			out << charData[i].jab[j].Yhitmin << ',';
			out << charData[i].jab[j].Yhitmax << ',';
			out << charData[i].jab[j].YhitmaxR << ',';
			out << charData[i].jab[j].YhitminR << ',';
			out << charData[i].jab[j].YhitmaxL << ',';
			out << charData[i].jab[j].YhitminL << ',';
			out << charData[i].jab[j].Xspikemin << ',';//spike
			out << charData[i].jab[j].Xspikemax << ',';
			out << charData[i].jab[j].Yspikemin << ',';
			out << charData[i].jab[j].Yspikemax << ',';
			out << charData[i].jab[j].XSAmin << ',';//super armor
			out << charData[i].jab[j].XSAmax << ',';
			out << charData[i].jab[j].YSAmin << ',';
			out << charData[i].jab[j].YSAmax << ',';
			out << charData[i].jab[j].XWBmin << ',';//windbox
			out << charData[i].jab[j].XWBmax << ',';
			out << charData[i].jab[j].YWBmin << ',';
			out << charData[i].jab[j].YWBmax << ',';
			out << charData[i].jab[j].Xgrabmin << ',';//grab box
			out << charData[i].jab[j].Xgrabmax << ',';
			out << charData[i].jab[j].Ygrabmin << ',';
			out << charData[i].jab[j].Ygrabmax << ',';
			out << charData[i].jab[j].Xreflectmin << ',';//reflector
			out << charData[i].jab[j].Xreflectmax << ',';
			out << charData[i].jab[j].Yreflectmin << ',';
			out << charData[i].jab[j].Yreflectmax << ',';
			out << charData[i].jab[j].Xscanmin << ',';//scan
			out << charData[i].jab[j].Xscanmax << ',';
			out << charData[i].jab[j].Yscanmin << ',';
			out << charData[i].jab[j].Yscanmax << ',';
			out << ' ';
		}
		}
		else
		{
			out << endl;
			out << "jab : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].dashattack.size() != 0)
		{
		for (int j = 0; j < charData[i].dashattack.size(); j++)
		{
			if (charData[i].dashattack[j].low != lowcheck || charData[i].dashattack[j].high != highcheck || charData[i].dashattack[j].type != currentC)
			{
				out << endl;
				out << "dashattack";
				if (charData[i].dashattack[j].low != lowcheck)
				{
					if (charData[i].dashattack[j].low == true)
					{
						out << "low";
					}
					lowcheck = charData[i].dashattack[j].low;
				}
				if (charData[i].dashattack[j].high != highcheck)
				{
					if (true == charData[i].dashattack[j].high)
					{
						out << "high";
					}
					highcheck = charData[i].dashattack[j].high;
				}
				if (charData[i].dashattack[j].type != currentC)
				{
					if (charData[i].dashattack[j].type != '0')
					{
						out << charData[i].dashattack[j].type;
					}
					currentC = charData[i].dashattack[j].type;
				}
				out << " : ";
			} 

			out << charData[i].dashattack[j].Xhurmin << ',';//hurtbox
			out << charData[i].dashattack[j].Xhurmax << ',';
			out << charData[i].dashattack[j].Yhurmin << ',';
			out << charData[i].dashattack[j].Yhurmax << ',';
			out << charData[i].dashattack[j].Xhitmin << ',';//hitbox
			out << charData[i].dashattack[j].Xhitmax << ',';
			out << charData[i].dashattack[j].Yhitmin << ',';
			out << charData[i].dashattack[j].Yhitmax << ',';
			out << charData[i].dashattack[j].YhitmaxR << ',';
			out << charData[i].dashattack[j].YhitminR << ',';
			out << charData[i].dashattack[j].YhitmaxL << ',';
			out << charData[i].dashattack[j].YhitminL << ',';
			out << charData[i].dashattack[j].Xspikemin << ',';//spike
			out << charData[i].dashattack[j].Xspikemax << ',';
			out << charData[i].dashattack[j].Yspikemin << ',';
			out << charData[i].dashattack[j].Yspikemax << ',';
			out << charData[i].dashattack[j].XSAmin << ',';//super armor
			out << charData[i].dashattack[j].XSAmax << ',';
			out << charData[i].dashattack[j].YSAmin << ',';
			out << charData[i].dashattack[j].YSAmax << ',';
			out << charData[i].dashattack[j].XWBmin << ',';//windbox
			out << charData[i].dashattack[j].XWBmax << ',';
			out << charData[i].dashattack[j].YWBmin << ',';
			out << charData[i].dashattack[j].YWBmax << ',';
			out << charData[i].dashattack[j].Xgrabmin << ',';//grab box
			out << charData[i].dashattack[j].Xgrabmax << ',';
			out << charData[i].dashattack[j].Ygrabmin << ',';
			out << charData[i].dashattack[j].Ygrabmax << ',';
			out << charData[i].dashattack[j].Xreflectmin << ',';//reflector
			out << charData[i].dashattack[j].Xreflectmax << ',';
			out << charData[i].dashattack[j].Yreflectmin << ',';
			out << charData[i].dashattack[j].Yreflectmax << ',';
			out << charData[i].dashattack[j].Xscanmin << ',';//scan
			out << charData[i].dashattack[j].Xscanmax << ',';
			out << charData[i].dashattack[j].Yscanmin << ',';
			out << charData[i].dashattack[j].Yscanmax << ',';
			out << ' ';
		}
		}
		else
		{
			out << endl;
			out << "dashattack : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].jabend.size() != 0)
		{
		for (int j = 0; j < charData[i].jabend.size(); j++)
		{
			if (charData[i].jabend[j].low != lowcheck || charData[i].jabend[j].high != highcheck || charData[i].jabend[j].type != currentC)
			{
				out << endl;
				out << "jabend";
				if (charData[i].jabend[j].low != lowcheck)
				{
					if (charData[i].jabend[j].low == true)
					{
						out << "low";
					}
					lowcheck = charData[i].jabend[j].low;
				}
				if (charData[i].jabend[j].high != highcheck)
				{
					if (true == charData[i].jabend[j].high)
					{
						out << "high";
					}
					highcheck = charData[i].jabend[j].high;
				}
				if (charData[i].jabend[j].type != currentC)
				{
					if (charData[i].jabend[j].type != '0')
					{
						out << charData[i].jabend[j].type;
					}
					currentC = charData[i].jabend[j].type;
				}
				out << " : ";
			}

			out << charData[i].jabend[j].Xhurmin << ',';//hurtbox
			out << charData[i].jabend[j].Xhurmax << ',';
			out << charData[i].jabend[j].Yhurmin << ',';
			out << charData[i].jabend[j].Yhurmax << ',';
			out << charData[i].jabend[j].Xhitmin << ',';//hitbox
			out << charData[i].jabend[j].Xhitmax << ',';
			out << charData[i].jabend[j].Yhitmin << ',';
			out << charData[i].jabend[j].Yhitmax << ',';
			out << charData[i].jabend[j].YhitmaxR << ',';
			out << charData[i].jabend[j].YhitminR << ',';
			out << charData[i].jabend[j].YhitmaxL << ',';
			out << charData[i].jabend[j].YhitminL << ',';
			out << charData[i].jabend[j].Xspikemin << ',';//spike
			out << charData[i].jabend[j].Xspikemax << ',';
			out << charData[i].jabend[j].Yspikemin << ',';
			out << charData[i].jabend[j].Yspikemax << ',';
			out << charData[i].jabend[j].XSAmin << ',';//super armor
			out << charData[i].jabend[j].XSAmax << ',';
			out << charData[i].jabend[j].YSAmin << ',';
			out << charData[i].jabend[j].YSAmax << ',';
			out << charData[i].jabend[j].XWBmin << ',';//windbox
			out << charData[i].jabend[j].XWBmax << ',';
			out << charData[i].jabend[j].YWBmin << ',';
			out << charData[i].jabend[j].YWBmax << ',';
			out << charData[i].jabend[j].Xgrabmin << ',';//grab box
			out << charData[i].jabend[j].Xgrabmax << ',';
			out << charData[i].jabend[j].Ygrabmin << ',';
			out << charData[i].jabend[j].Ygrabmax << ',';
			out << charData[i].jabend[j].Xreflectmin << ',';//reflector
			out << charData[i].jabend[j].Xreflectmax << ',';
			out << charData[i].jabend[j].Yreflectmin << ',';
			out << charData[i].jabend[j].Yreflectmax << ',';
			out << charData[i].jabend[j].Xscanmin << ',';//scan
			out << charData[i].jabend[j].Xscanmax << ',';
			out << charData[i].jabend[j].Yscanmin << ',';
			out << charData[i].jabend[j].Yscanmax << ',';
			out << ' ';
		}
		}
		else
		{
			out << endl;
			out << "jabend : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].sidetilt.size() != 0)
		{
		for (int j = 0; j < charData[i].sidetilt.size(); j++)
		{
			if (charData[i].sidetilt[j].low != lowcheck || charData[i].sidetilt[j].high != highcheck || charData[i].sidetilt[j].type != currentC)
			{
				out << endl;
				out << "sidetilt";
				if (charData[i].sidetilt[j].low != lowcheck)
				{
					if (charData[i].sidetilt[j].low == true)
					{
						out << "low";
					}
					lowcheck = charData[i].sidetilt[j].low;
				}
				if (charData[i].sidetilt[j].high != highcheck)
				{
					if (true == charData[i].sidetilt[j].high)
					{
						out << "high";
					}
					highcheck = charData[i].sidetilt[j].high;
				}
				if (charData[i].sidetilt[j].type != currentC)
				{
					if (charData[i].sidetilt[j].type != '0')
					{
						out << charData[i].sidetilt[j].type;
					}
					currentC = charData[i].sidetilt[j].type;
				}
				out << " : ";
			}


			out << charData[i].sidetilt[j].Xhurmin << ',';//hurtbox
			out << charData[i].sidetilt[j].Xhurmax << ',';
			out << charData[i].sidetilt[j].Yhurmin << ',';
			out << charData[i].sidetilt[j].Yhurmax << ',';
			out << charData[i].sidetilt[j].Xhitmin << ',';//hitbox
			out << charData[i].sidetilt[j].Xhitmax << ',';
			out << charData[i].sidetilt[j].Yhitmin << ',';
			out << charData[i].sidetilt[j].Yhitmax << ',';
			out << charData[i].sidetilt[j].YhitmaxR << ',';
			out << charData[i].sidetilt[j].YhitminR << ',';
			out << charData[i].sidetilt[j].YhitmaxL << ',';
			out << charData[i].sidetilt[j].YhitminL << ',';
			out << charData[i].sidetilt[j].Xspikemin << ',';//spike
			out << charData[i].sidetilt[j].Xspikemax << ',';
			out << charData[i].sidetilt[j].Yspikemin << ',';
			out << charData[i].sidetilt[j].Yspikemax << ',';
			out << charData[i].sidetilt[j].XSAmin << ',';//super armor
			out << charData[i].sidetilt[j].XSAmax << ',';
			out << charData[i].sidetilt[j].YSAmin << ',';
			out << charData[i].sidetilt[j].YSAmax << ',';
			out << charData[i].sidetilt[j].XWBmin << ',';//windbox
			out << charData[i].sidetilt[j].XWBmax << ',';
			out << charData[i].sidetilt[j].YWBmin << ',';
			out << charData[i].sidetilt[j].YWBmax << ',';
			out << charData[i].sidetilt[j].Xgrabmin << ',';//grab box
			out << charData[i].sidetilt[j].Xgrabmax << ',';
			out << charData[i].sidetilt[j].Ygrabmin << ',';
			out << charData[i].sidetilt[j].Ygrabmax << ',';
			out << charData[i].sidetilt[j].Xreflectmin << ',';//reflector
			out << charData[i].sidetilt[j].Xreflectmax << ',';
			out << charData[i].sidetilt[j].Yreflectmin << ',';
			out << charData[i].sidetilt[j].Yreflectmax << ',';
			out << charData[i].sidetilt[j].Xscanmin << ',';//scan
			out << charData[i].sidetilt[j].Xscanmax << ',';
			out << charData[i].sidetilt[j].Yscanmin << ',';
			out << charData[i].sidetilt[j].Yscanmax << ',';
			out << ' ';
		}
		}
		else
		{
			out << endl;
			out << "sidetilt : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].uptilt.size() != 0)
		{
			for (int j = 0; j < charData[i].uptilt.size(); j++)
			{
				if (charData[i].uptilt[j].low != lowcheck || charData[i].uptilt[j].high != highcheck || charData[i].uptilt[j].type != currentC)
				{
					out << endl;
					out << "uptilt";
					if (charData[i].uptilt[j].low != lowcheck)
					{
						if (charData[i].uptilt[j].low == true)
						{
							out << "low";
						}
						lowcheck = charData[i].uptilt[j].low;
					}
					if (charData[i].uptilt[j].high != highcheck)
					{
						if (true == charData[i].uptilt[j].high)
						{
							out << "high";
						}
						highcheck = charData[i].uptilt[j].high;
					}
					if (charData[i].uptilt[j].type != currentC)
					{
						if (charData[i].uptilt[j].type != '0')
						{
							out << charData[i].uptilt[j].type;
						}
						currentC = charData[i].uptilt[j].type;
					}
					out << " : ";
				}

				out << charData[i].uptilt[j].Xhurmin << ',';//hurtbox
				out << charData[i].uptilt[j].Xhurmax << ',';
				out << charData[i].uptilt[j].Yhurmin << ',';
				out << charData[i].uptilt[j].Yhurmax << ',';
				out << charData[i].uptilt[j].Xhitmin << ',';//hitbox
				out << charData[i].uptilt[j].Xhitmax << ',';
				out << charData[i].uptilt[j].Yhitmin << ',';
				out << charData[i].uptilt[j].Yhitmax << ',';
				out << charData[i].uptilt[j].YhitmaxR << ',';
				out << charData[i].uptilt[j].YhitminR << ',';
				out << charData[i].uptilt[j].YhitmaxL << ',';
				out << charData[i].uptilt[j].YhitminL << ',';
				out << charData[i].uptilt[j].Xspikemin << ',';//spike
				out << charData[i].uptilt[j].Xspikemax << ',';
				out << charData[i].uptilt[j].Yspikemin << ',';
				out << charData[i].uptilt[j].Yspikemax << ',';
				out << charData[i].uptilt[j].XSAmin << ',';//super armor
				out << charData[i].uptilt[j].XSAmax << ',';
				out << charData[i].uptilt[j].YSAmin << ',';
				out << charData[i].uptilt[j].YSAmax << ',';
				out << charData[i].uptilt[j].XWBmin << ',';//windbox
				out << charData[i].uptilt[j].XWBmax << ',';
				out << charData[i].uptilt[j].YWBmin << ',';
				out << charData[i].uptilt[j].YWBmax << ',';
				out << charData[i].uptilt[j].Xgrabmin << ',';//grab box
				out << charData[i].uptilt[j].Xgrabmax << ',';
				out << charData[i].uptilt[j].Ygrabmin << ',';
				out << charData[i].uptilt[j].Ygrabmax << ',';
				out << charData[i].uptilt[j].Xreflectmin << ',';//reflector
				out << charData[i].uptilt[j].Xreflectmax << ',';
				out << charData[i].uptilt[j].Yreflectmin << ',';
				out << charData[i].uptilt[j].Yreflectmax << ',';
				out << charData[i].uptilt[j].Xscanmin << ',';//scan
				out << charData[i].uptilt[j].Xscanmax << ',';
				out << charData[i].uptilt[j].Yscanmin << ',';
				out << charData[i].uptilt[j].Yscanmax << ',';
				out << ' ';
			}
		}
		else
		{
			out << endl;
			out << "uptilt : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].downtilt.size() != 0)
		{
		for (int j = 0; j < charData[i].downtilt.size(); j++)
		{
			if (charData[i].downtilt[j].low != lowcheck || charData[i].downtilt[j].high != highcheck || charData[i].downtilt[j].type != currentC)
			{
				out << endl;
				out << "downtilt";
				if (charData[i].downtilt[j].low != lowcheck)
				{
					if (charData[i].downtilt[j].low == true)
					{
						out << "low";
					}
					lowcheck = charData[i].downtilt[j].low;
				}
				if (charData[i].downtilt[j].high != highcheck)
				{
					if (true == charData[i].downtilt[j].high)
					{
						out << "high";
					}
					highcheck = charData[i].downtilt[j].high;
				}
				if (charData[i].downtilt[j].type != currentC)
				{
					if (charData[i].downtilt[j].type != '0')
					{
						out << charData[i].downtilt[j].type;
					}
					currentC = charData[i].downtilt[j].type;
				}
				out << " : ";
			}

			out << charData[i].downtilt[j].Xhurmin << ',';//hurtbox
			out << charData[i].downtilt[j].Xhurmax << ',';
			out << charData[i].downtilt[j].Yhurmin << ',';
			out << charData[i].downtilt[j].Yhurmax << ',';
			out << charData[i].downtilt[j].Xhitmin << ',';//hitbox
			out << charData[i].downtilt[j].Xhitmax << ',';
			out << charData[i].downtilt[j].Yhitmin << ',';
			out << charData[i].downtilt[j].Yhitmax << ',';
			out << charData[i].downtilt[j].YhitmaxR << ',';
			out << charData[i].downtilt[j].YhitminR << ',';
			out << charData[i].downtilt[j].YhitmaxL << ',';
			out << charData[i].downtilt[j].YhitminL << ',';
			out << charData[i].downtilt[j].Xspikemin << ',';//spike
			out << charData[i].downtilt[j].Xspikemax << ',';
			out << charData[i].downtilt[j].Yspikemin << ',';
			out << charData[i].downtilt[j].Yspikemax << ',';
			out << charData[i].downtilt[j].XSAmin << ',';//super armor
			out << charData[i].downtilt[j].XSAmax << ',';
			out << charData[i].downtilt[j].YSAmin << ',';
			out << charData[i].downtilt[j].YSAmax << ',';
			out << charData[i].downtilt[j].XWBmin << ',';//windbox
			out << charData[i].downtilt[j].XWBmax << ',';
			out << charData[i].downtilt[j].YWBmin << ',';
			out << charData[i].downtilt[j].YWBmax << ',';
			out << charData[i].downtilt[j].Xgrabmin << ',';//grab box
			out << charData[i].downtilt[j].Xgrabmax << ',';
			out << charData[i].downtilt[j].Ygrabmin << ',';
			out << charData[i].downtilt[j].Ygrabmax << ',';
			out << charData[i].downtilt[j].Xreflectmin << ',';//reflector
			out << charData[i].downtilt[j].Xreflectmax << ',';
			out << charData[i].downtilt[j].Yreflectmin << ',';
			out << charData[i].downtilt[j].Yreflectmax << ',';
			out << charData[i].downtilt[j].Xscanmin << ',';//scan
			out << charData[i].downtilt[j].Xscanmax << ',';
			out << charData[i].downtilt[j].Yscanmin << ',';
			out << charData[i].downtilt[j].Yscanmax << ',';
			out << ' ';
		}
		}
		else
		{
			out << endl;
			out << "downtilt : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].sidesmash.size() != 0)
		{
		for (int j = 0; j < charData[i].sidesmash.size(); j++)
		{
			if (charData[i].sidesmash[j].low != lowcheck || charData[i].sidesmash[j].high != highcheck || charData[i].sidesmash[j].type != currentC)
			{
				out << endl;
				out << "sidesmash";
				if (charData[i].sidesmash[j].low != lowcheck)
				{
					if (charData[i].sidesmash[j].low == true)
					{
						out << "low";
					}
					lowcheck = charData[i].sidesmash[j].low;
				}
				if (charData[i].sidesmash[j].high != highcheck)
				{
					if (true == charData[i].sidesmash[j].high)
					{
						out << "high";
					}
					highcheck = charData[i].sidesmash[j].high;
				}
				if (charData[i].sidesmash[j].type != currentC)
				{
					if (charData[i].sidesmash[j].type != '0')
					{
						out << charData[i].sidesmash[j].type;
					}
					currentC = charData[i].sidesmash[j].type;
				}
				out << " : ";
			}

			out << charData[i].sidesmash[j].Xhurmin << ',';//hurtbox
			out << charData[i].sidesmash[j].Xhurmax << ',';
			out << charData[i].sidesmash[j].Yhurmin << ',';
			out << charData[i].sidesmash[j].Yhurmax << ',';
			out << charData[i].sidesmash[j].Xhitmin << ',';//hitbox
			out << charData[i].sidesmash[j].Xhitmax << ',';
			out << charData[i].sidesmash[j].Yhitmin << ',';
			out << charData[i].sidesmash[j].Yhitmax << ',';
			out << charData[i].sidesmash[j].YhitmaxR << ',';
			out << charData[i].sidesmash[j].YhitminR << ',';
			out << charData[i].sidesmash[j].YhitmaxL << ',';
			out << charData[i].sidesmash[j].YhitminL << ',';
			out << charData[i].sidesmash[j].Xspikemin << ',';//spike
			out << charData[i].sidesmash[j].Xspikemax << ',';
			out << charData[i].sidesmash[j].Yspikemin << ',';
			out << charData[i].sidesmash[j].Yspikemax << ',';
			out << charData[i].sidesmash[j].XSAmin << ',';//super armor
			out << charData[i].sidesmash[j].XSAmax << ',';
			out << charData[i].sidesmash[j].YSAmin << ',';
			out << charData[i].sidesmash[j].YSAmax << ',';
			out << charData[i].sidesmash[j].XWBmin << ',';//windbox
			out << charData[i].sidesmash[j].XWBmax << ',';
			out << charData[i].sidesmash[j].YWBmin << ',';
			out << charData[i].sidesmash[j].YWBmax << ',';
			out << charData[i].sidesmash[j].Xgrabmin << ',';//grab box
			out << charData[i].sidesmash[j].Xgrabmax << ',';
			out << charData[i].sidesmash[j].Ygrabmin << ',';
			out << charData[i].sidesmash[j].Ygrabmax << ',';
			out << charData[i].sidesmash[j].Xreflectmin << ',';//reflector
			out << charData[i].sidesmash[j].Xreflectmax << ',';
			out << charData[i].sidesmash[j].Yreflectmin << ',';
			out << charData[i].sidesmash[j].Yreflectmax << ',';
			out << charData[i].sidesmash[j].Xscanmin << ',';//scan
			out << charData[i].sidesmash[j].Xscanmax << ',';
			out << charData[i].sidesmash[j].Yscanmin << ',';
			out << charData[i].sidesmash[j].Yscanmax << ',';
			out << ' ';
		}
		}
		else
		{
			out << endl;
			out << "sidesmash : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].upsmash.size() != 0)
		{
		for (int j = 0; j < charData[i].upsmash.size(); j++)
		{
			if (charData[i].upsmash[j].low != lowcheck || charData[i].upsmash[j].high != highcheck || charData[i].upsmash[j].type != currentC)
			{
				out << endl;
				out << "upsmash";
				if (charData[i].upsmash[j].low != lowcheck)
				{
					if (charData[i].upsmash[j].low == true)
					{
						out << "low";
					}
					lowcheck = charData[i].upsmash[j].low;
				}
				if (charData[i].upsmash[j].high != highcheck)
				{
					if (true == charData[i].upsmash[j].high)
					{
						out << "high";
					}
					highcheck = charData[i].upsmash[j].high;
				}
				if (charData[i].upsmash[j].type != currentC)
				{
					if (charData[i].upsmash[j].type != '0')
					{
						out << charData[i].upsmash[j].type;
					}
					currentC = charData[i].upsmash[j].type;
				}
				out << " : ";
			}

			out << charData[i].upsmash[j].Xhurmin << ',';//hurtbox
			out << charData[i].upsmash[j].Xhurmax << ',';
			out << charData[i].upsmash[j].Yhurmin << ',';
			out << charData[i].upsmash[j].Yhurmax << ',';
			out << charData[i].upsmash[j].Xhitmin << ',';//hitbox
			out << charData[i].upsmash[j].Xhitmax << ',';
			out << charData[i].upsmash[j].Yhitmin << ',';
			out << charData[i].upsmash[j].Yhitmax << ',';
			out << charData[i].upsmash[j].YhitmaxR << ',';
			out << charData[i].upsmash[j].YhitminR << ',';
			out << charData[i].upsmash[j].YhitmaxL << ',';
			out << charData[i].upsmash[j].YhitminL << ',';
			out << charData[i].upsmash[j].Xspikemin << ',';//spike
			out << charData[i].upsmash[j].Xspikemax << ',';
			out << charData[i].upsmash[j].Yspikemin << ',';
			out << charData[i].upsmash[j].Yspikemax << ',';
			out << charData[i].upsmash[j].XSAmin << ',';//super armor
			out << charData[i].upsmash[j].XSAmax << ',';
			out << charData[i].upsmash[j].YSAmin << ',';
			out << charData[i].upsmash[j].YSAmax << ',';
			out << charData[i].upsmash[j].XWBmin << ',';//windbox
			out << charData[i].upsmash[j].XWBmax << ',';
			out << charData[i].upsmash[j].YWBmin << ',';
			out << charData[i].upsmash[j].YWBmax << ',';
			out << charData[i].upsmash[j].Xgrabmin << ',';//grab box
			out << charData[i].upsmash[j].Xgrabmax << ',';
			out << charData[i].upsmash[j].Ygrabmin << ',';
			out << charData[i].upsmash[j].Ygrabmax << ',';
			out << charData[i].upsmash[j].Xreflectmin << ',';//reflector
			out << charData[i].upsmash[j].Xreflectmax << ',';
			out << charData[i].upsmash[j].Yreflectmin << ',';
			out << charData[i].upsmash[j].Yreflectmax << ',';
			out << charData[i].upsmash[j].Xscanmin << ',';//scan
			out << charData[i].upsmash[j].Xscanmax << ',';
			out << charData[i].upsmash[j].Yscanmin << ',';
			out << charData[i].upsmash[j].Yscanmax << ',';
			out << ' ';
		}
		}
		else
		{
			out << endl;
			out << "upsmash : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].downsmash.size() != 0)
		{
		for (int j = 0; j < charData[i].downsmash.size(); j++)
		{
			if (charData[i].downsmash[j].low != lowcheck || charData[i].downsmash[j].high != highcheck || charData[i].downsmash[j].type != currentC)
			{
				out << endl;
				out << "downsmash";
				if (charData[i].downsmash[j].low != lowcheck)
				{
					if (charData[i].downsmash[j].low == true)
					{
						out << "low";
					}
					lowcheck = charData[i].downsmash[j].low;
				}
				if (charData[i].downsmash[j].high != highcheck)
				{
					if (true == charData[i].downsmash[j].high)
					{
						out << "high";
					}
					highcheck = charData[i].downsmash[j].high;
				}
				if (charData[i].downsmash[j].type != currentC)
				{
					if (charData[i].downsmash[j].type != '0')
					{
						out << charData[i].downsmash[j].type;
					}
					currentC = charData[i].downsmash[j].type;
				}
				out << " : ";
			}

			out << charData[i].downsmash[j].Xhurmin << ',';//hurtbox
			out << charData[i].downsmash[j].Xhurmax << ',';
			out << charData[i].downsmash[j].Yhurmin << ',';
			out << charData[i].downsmash[j].Yhurmax << ',';
			out << charData[i].downsmash[j].Xhitmin << ',';//hitbox
			out << charData[i].downsmash[j].Xhitmax << ',';
			out << charData[i].downsmash[j].Yhitmin << ',';
			out << charData[i].downsmash[j].Yhitmax << ',';
			out << charData[i].downsmash[j].YhitmaxR << ',';
			out << charData[i].downsmash[j].YhitminR << ',';
			out << charData[i].downsmash[j].YhitmaxL << ',';
			out << charData[i].downsmash[j].YhitminL << ',';
			out << charData[i].downsmash[j].Xspikemin << ',';//spike
			out << charData[i].downsmash[j].Xspikemax << ',';
			out << charData[i].downsmash[j].Yspikemin << ',';
			out << charData[i].downsmash[j].Yspikemax << ',';
			out << charData[i].downsmash[j].XSAmin << ',';//super armor
			out << charData[i].downsmash[j].XSAmax << ',';
			out << charData[i].downsmash[j].YSAmin << ',';
			out << charData[i].downsmash[j].YSAmax << ',';
			out << charData[i].downsmash[j].XWBmin << ',';//windbox
			out << charData[i].downsmash[j].XWBmax << ',';
			out << charData[i].downsmash[j].YWBmin << ',';
			out << charData[i].downsmash[j].YWBmax << ',';
			out << charData[i].downsmash[j].Xgrabmin << ',';//grab box
			out << charData[i].downsmash[j].Xgrabmax << ',';
			out << charData[i].downsmash[j].Ygrabmin << ',';
			out << charData[i].downsmash[j].Ygrabmax << ',';
			out << charData[i].downsmash[j].Xreflectmin << ',';//reflector
			out << charData[i].downsmash[j].Xreflectmax << ',';
			out << charData[i].downsmash[j].Yreflectmin << ',';
			out << charData[i].downsmash[j].Yreflectmax << ',';
			out << charData[i].downsmash[j].Xscanmin << ',';//scan
			out << charData[i].downsmash[j].Xscanmax << ',';
			out << charData[i].downsmash[j].Yscanmin << ',';
			out << charData[i].downsmash[j].Yscanmax << ',';
			out << ' ';
		}
		}
		else
		{
			out << endl;
			out << "downsmash : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].bair.size() != 0)
		{
		for (int j = 0; j < charData[i].bair.size(); j++)
		{
			if (charData[i].bair[j].low != lowcheck || charData[i].bair[j].high != highcheck || charData[i].bair[j].type != currentC)
			{
				out << endl;
				out << "bair";
				if (charData[i].bair[j].low != lowcheck)
				{
					if (charData[i].bair[j].low == true)
					{
						out << "low";
					}
					lowcheck = charData[i].bair[j].low;
				}
				if (charData[i].bair[j].high != highcheck)
				{
					if (true == charData[i].bair[j].high)
					{
						out << "high";
					}
					highcheck = charData[i].bair[j].high;
				}
				if (charData[i].bair[j].type != currentC)
				{
					if (charData[i].bair[j].type != '0')
					{
						out << charData[i].bair[j].type;
					}
					currentC = charData[i].bair[j].type;
				}
				out << " : ";
			}

			out << charData[i].bair[j].Xhurmin << ',';//hurtbox
			out << charData[i].bair[j].Xhurmax << ',';
			out << charData[i].bair[j].Yhurmin << ',';
			out << charData[i].bair[j].Yhurmax << ',';
			out << charData[i].bair[j].Xhitmin << ',';//hitbox
			out << charData[i].bair[j].Xhitmax << ',';
			out << charData[i].bair[j].Yhitmin << ',';
			out << charData[i].bair[j].Yhitmax << ',';
			out << charData[i].bair[j].YhitmaxR << ',';
			out << charData[i].bair[j].YhitminR << ',';
			out << charData[i].bair[j].YhitmaxL << ',';
			out << charData[i].bair[j].YhitminL << ',';
			out << charData[i].bair[j].Xspikemin << ',';//spike
			out << charData[i].bair[j].Xspikemax << ',';
			out << charData[i].bair[j].Yspikemin << ',';
			out << charData[i].bair[j].Yspikemax << ',';
			out << charData[i].bair[j].XSAmin << ',';//super armor
			out << charData[i].bair[j].XSAmax << ',';
			out << charData[i].bair[j].YSAmin << ',';
			out << charData[i].bair[j].YSAmax << ',';
			out << charData[i].bair[j].XWBmin << ',';//windbox
			out << charData[i].bair[j].XWBmax << ',';
			out << charData[i].bair[j].YWBmin << ',';
			out << charData[i].bair[j].YWBmax << ',';
			out << charData[i].bair[j].Xgrabmin << ',';//grab box
			out << charData[i].bair[j].Xgrabmax << ',';
			out << charData[i].bair[j].Ygrabmin << ',';
			out << charData[i].bair[j].Ygrabmax << ',';
			out << charData[i].bair[j].Xreflectmin << ',';//reflector
			out << charData[i].bair[j].Xreflectmax << ',';
			out << charData[i].bair[j].Yreflectmin << ',';
			out << charData[i].bair[j].Yreflectmax << ',';
			out << charData[i].bair[j].Xscanmin << ',';//scan
			out << charData[i].bair[j].Xscanmax << ',';
			out << charData[i].bair[j].Yscanmin << ',';
			out << charData[i].bair[j].Yscanmax << ',';
			out << ' ';
		}
		}
		else
		{
			out << endl;
			out << "bair : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].fair.size() != 0)
		{
		for (int j = 0; j < charData[i].fair.size(); j++)
		{
			if (charData[i].fair[j].low != lowcheck || charData[i].fair[j].high != highcheck || charData[i].fair[j].type != currentC)
			{
				out << endl;
				out << "fair";
				if (charData[i].fair[j].low != lowcheck)
				{
					if (charData[i].fair[j].low == true)
					{
						out << "low";
					}
					lowcheck = charData[i].fair[j].low;
				}
				if (charData[i].fair[j].high != highcheck)
				{
					if (true == charData[i].fair[j].high)
					{
						out << "high";
					}
					highcheck = charData[i].fair[j].high;
				}
				if (charData[i].fair[j].type != currentC)
				{
					if (charData[i].fair[j].type != '0')
					{
						out << charData[i].fair[j].type;
					}
					currentC = charData[i].fair[j].type;
				}
				out << " : ";
			}

			out << charData[i].fair[j].Xhurmin << ',';//hurtbox
			out << charData[i].fair[j].Xhurmax << ',';
			out << charData[i].fair[j].Yhurmin << ',';
			out << charData[i].fair[j].Yhurmax << ',';
			out << charData[i].fair[j].Xhitmin << ',';//hitbox
			out << charData[i].fair[j].Xhitmax << ',';
			out << charData[i].fair[j].Yhitmin << ',';
			out << charData[i].fair[j].Yhitmax << ',';
			out << charData[i].fair[j].YhitmaxR << ',';
			out << charData[i].fair[j].YhitminR << ',';
			out << charData[i].fair[j].YhitmaxL << ',';
			out << charData[i].fair[j].YhitminL << ',';
			out << charData[i].fair[j].Xspikemin << ',';//spike
			out << charData[i].fair[j].Xspikemax << ',';
			out << charData[i].fair[j].Yspikemin << ',';
			out << charData[i].fair[j].Yspikemax << ',';
			out << charData[i].fair[j].XSAmin << ',';//super armor
			out << charData[i].fair[j].XSAmax << ',';
			out << charData[i].fair[j].YSAmin << ',';
			out << charData[i].fair[j].YSAmax << ',';
			out << charData[i].fair[j].XWBmin << ',';//windbox
			out << charData[i].fair[j].XWBmax << ',';
			out << charData[i].fair[j].YWBmin << ',';
			out << charData[i].fair[j].YWBmax << ',';
			out << charData[i].fair[j].Xgrabmin << ',';//grab box
			out << charData[i].fair[j].Xgrabmax << ',';
			out << charData[i].fair[j].Ygrabmin << ',';
			out << charData[i].fair[j].Ygrabmax << ',';
			out << charData[i].fair[j].Xreflectmin << ',';//reflector
			out << charData[i].fair[j].Xreflectmax << ',';
			out << charData[i].fair[j].Yreflectmin << ',';
			out << charData[i].fair[j].Yreflectmax << ',';
			out << charData[i].fair[j].Xscanmin << ',';//scan
			out << charData[i].fair[j].Xscanmax << ',';
			out << charData[i].fair[j].Yscanmin << ',';
			out << charData[i].fair[j].Yscanmax << ',';
			out << ' ';
		}
		}
		else
		{
			out << endl;
			out << "fair : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].upair.size() != 0)
		{
		for (int j = 0; j < charData[i].upair.size(); j++)
		{
			if (charData[i].upair[j].low != lowcheck || charData[i].upair[j].high != highcheck || charData[i].upair[j].type != currentC)
			{
				out << endl;
				out << "upair";
				if (charData[i].upair[j].low != lowcheck)
				{
					if (charData[i].upair[j].low == true)
					{
						out << "low";
					}
					lowcheck = charData[i].upair[j].low;
				}
				if (charData[i].upair[j].high != highcheck)
				{
					if (true == charData[i].upair[j].high)
					{
						out << "high";
					}
					highcheck = charData[i].upair[j].high;
				}
				if (charData[i].upair[j].type != currentC)
				{
					if (charData[i].upair[j].type != '0')
					{
						out << charData[i].upair[j].type;
					}
					currentC = charData[i].upair[j].type;
				}
				out << " : ";
			}

			out << charData[i].upair[j].Xhurmin << ',';//hurtbox
			out << charData[i].upair[j].Xhurmax << ',';
			out << charData[i].upair[j].Yhurmin << ',';
			out << charData[i].upair[j].Yhurmax << ',';
			out << charData[i].upair[j].Xhitmin << ',';//hitbox
			out << charData[i].upair[j].Xhitmax << ',';
			out << charData[i].upair[j].Yhitmin << ',';
			out << charData[i].upair[j].Yhitmax << ',';
			out << charData[i].upair[j].YhitmaxR << ',';
			out << charData[i].upair[j].YhitminR << ',';
			out << charData[i].upair[j].YhitmaxL << ',';
			out << charData[i].upair[j].YhitminL << ',';
			out << charData[i].upair[j].Xspikemin << ',';//spike
			out << charData[i].upair[j].Xspikemax << ',';
			out << charData[i].upair[j].Yspikemin << ',';
			out << charData[i].upair[j].Yspikemax << ',';
			out << charData[i].upair[j].XSAmin << ',';//super armor
			out << charData[i].upair[j].XSAmax << ',';
			out << charData[i].upair[j].YSAmin << ',';
			out << charData[i].upair[j].YSAmax << ',';
			out << charData[i].upair[j].XWBmin << ',';//windbox
			out << charData[i].upair[j].XWBmax << ',';
			out << charData[i].upair[j].YWBmin << ',';
			out << charData[i].upair[j].YWBmax << ',';
			out << charData[i].upair[j].Xgrabmin << ',';//grab box
			out << charData[i].upair[j].Xgrabmax << ',';
			out << charData[i].upair[j].Ygrabmin << ',';
			out << charData[i].upair[j].Ygrabmax << ',';
			out << charData[i].upair[j].Xreflectmin << ',';//reflector
			out << charData[i].upair[j].Xreflectmax << ',';
			out << charData[i].upair[j].Yreflectmin << ',';
			out << charData[i].upair[j].Yreflectmax << ',';
			out << charData[i].upair[j].Xscanmin << ',';//scan
			out << charData[i].upair[j].Xscanmax << ',';
			out << charData[i].upair[j].Yscanmin << ',';
			out << charData[i].upair[j].Yscanmax << ',';
			out << ' ';
		}
		}
		else
		{
			out << endl;
			out << "upair : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].dair.size() != 0)
		{
		for (int j = 0; j < charData[i].dair.size(); j++)
		{
			if (charData[i].dair[j].low != lowcheck || charData[i].dair[j].high != highcheck || charData[i].dair[j].type != currentC)
			{
				out << endl;
				out << "dair";
				if (charData[i].dair[j].low != lowcheck)
				{
					if (charData[i].dair[j].low == true)
					{
						out << "low";
					}
					lowcheck = charData[i].dair[j].low;
				}
				if (charData[i].dair[j].high != highcheck)
				{
					if (true == charData[i].dair[j].high)
					{
						out << "high";
					}
					highcheck = charData[i].dair[j].high;
				}
				if (charData[i].dair[j].type != currentC)
				{
					if (charData[i].dair[j].type != '0')
					{
						out << charData[i].dair[j].type;
					}
					currentC = charData[i].dair[j].type;
				}
				out << " : ";
			}

			out << charData[i].dair[j].Xhurmin << ',';//hurtbox
			out << charData[i].dair[j].Xhurmax << ',';
			out << charData[i].dair[j].Yhurmin << ',';
			out << charData[i].dair[j].Yhurmax << ',';
			out << charData[i].dair[j].Xhitmin << ',';//hitbox
			out << charData[i].dair[j].Xhitmax << ',';
			out << charData[i].dair[j].Yhitmin << ',';
			out << charData[i].dair[j].Yhitmax << ',';
			out << charData[i].dair[j].YhitmaxR << ',';
			out << charData[i].dair[j].YhitminR << ',';
			out << charData[i].dair[j].YhitmaxL << ',';
			out << charData[i].dair[j].YhitminL << ',';
			out << charData[i].dair[j].Xspikemin << ',';//spike
			out << charData[i].dair[j].Xspikemax << ',';
			out << charData[i].dair[j].Yspikemin << ',';
			out << charData[i].dair[j].Yspikemax << ',';
			out << charData[i].dair[j].XSAmin << ',';//super armor
			out << charData[i].dair[j].XSAmax << ',';
			out << charData[i].dair[j].YSAmin << ',';
			out << charData[i].dair[j].YSAmax << ',';
			out << charData[i].dair[j].XWBmin << ',';//windbox
			out << charData[i].dair[j].XWBmax << ',';
			out << charData[i].dair[j].YWBmin << ',';
			out << charData[i].dair[j].YWBmax << ',';
			out << charData[i].dair[j].Xgrabmin << ',';//grab box
			out << charData[i].dair[j].Xgrabmax << ',';
			out << charData[i].dair[j].Ygrabmin << ',';
			out << charData[i].dair[j].Ygrabmax << ',';
			out << charData[i].dair[j].Xreflectmin << ',';//reflector
			out << charData[i].dair[j].Xreflectmax << ',';
			out << charData[i].dair[j].Yreflectmin << ',';
			out << charData[i].dair[j].Yreflectmax << ',';
			out << charData[i].dair[j].Xscanmin << ',';//scan
			out << charData[i].dair[j].Xscanmax << ',';
			out << charData[i].dair[j].Yscanmin << ',';
			out << charData[i].dair[j].Yscanmax << ',';
			out << ' ';
		}
		}
		else
		{
			out << endl;
			out << "dair : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].nair.size() != 0)
		{
		for (int j = 0; j < charData[i].nair.size(); j++)
		{
			if (charData[i].nair[j].low != lowcheck || charData[i].nair[j].high != highcheck || charData[i].nair[j].type != currentC)
			{
				out << endl;
				out << "nair";
				if (charData[i].nair[j].low != lowcheck)
				{
					if (charData[i].nair[j].low == true)
					{
						out << "low";
					}
					lowcheck = charData[i].nair[j].low;
				}
				if (charData[i].nair[j].high != highcheck)
				{
					if (true == charData[i].nair[j].high)
					{
						out << "high";
					}
					highcheck = charData[i].nair[j].high;
				}
				if (charData[i].nair[j].type != currentC)
				{
					if (charData[i].nair[j].type != '0')
					{
						out << charData[i].nair[j].type;
					}
					currentC = charData[i].nair[j].type;
				}
				out << " : ";
			}

			out << charData[i].nair[j].Xhurmin << ',';//hurtbox
			out << charData[i].nair[j].Xhurmax << ',';
			out << charData[i].nair[j].Yhurmin << ',';
			out << charData[i].nair[j].Yhurmax << ',';
			out << charData[i].nair[j].Xhitmin << ',';//hitbox
			out << charData[i].nair[j].Xhitmax << ',';
			out << charData[i].nair[j].Yhitmin << ',';
			out << charData[i].nair[j].Yhitmax << ',';
			out << charData[i].nair[j].YhitmaxR << ',';
			out << charData[i].nair[j].YhitminR << ',';
			out << charData[i].nair[j].YhitmaxL << ',';
			out << charData[i].nair[j].YhitminL << ',';
			out << charData[i].nair[j].Xspikemin << ',';//spike
			out << charData[i].nair[j].Xspikemax << ',';
			out << charData[i].nair[j].Yspikemin << ',';
			out << charData[i].nair[j].Yspikemax << ',';
			out << charData[i].nair[j].XSAmin << ',';//super armor
			out << charData[i].nair[j].XSAmax << ',';
			out << charData[i].nair[j].YSAmin << ',';
			out << charData[i].nair[j].YSAmax << ',';
			out << charData[i].nair[j].XWBmin << ',';//windbox
			out << charData[i].nair[j].XWBmax << ',';
			out << charData[i].nair[j].YWBmin << ',';
			out << charData[i].nair[j].YWBmax << ',';
			out << charData[i].nair[j].Xgrabmin << ',';//grab box
			out << charData[i].nair[j].Xgrabmax << ',';
			out << charData[i].nair[j].Ygrabmin << ',';
			out << charData[i].nair[j].Ygrabmax << ',';
			out << charData[i].nair[j].Xreflectmin << ',';//reflector
			out << charData[i].nair[j].Xreflectmax << ',';
			out << charData[i].nair[j].Yreflectmin << ',';
			out << charData[i].nair[j].Yreflectmax << ',';
			out << charData[i].nair[j].Xscanmin << ',';//scan
			out << charData[i].nair[j].Xscanmax << ',';
			out << charData[i].nair[j].Yscanmin << ',';
			out << charData[i].nair[j].Yscanmax << ',';
			out << ' ';
		}
		}
		else
		{
			out << endl;
			out << "nair : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].landingbair.size() != 0)
		{
		for (int j = 0; j < charData[i].landingbair.size(); j++)
		{
			if (charData[i].landingbair[j].low != lowcheck || charData[i].landingbair[j].high != highcheck || charData[i].landingbair[j].type != currentC)
			{
				out << endl;
				out << "landingbair";
				if (charData[i].landingbair[j].low != lowcheck)
				{
					if (charData[i].landingbair[j].low == true)
					{
						out << "low";
					}
					lowcheck = charData[i].landingbair[j].low;
				}
				if (charData[i].landingbair[j].high != highcheck)
				{
					if (true == charData[i].landingbair[j].high)
					{
						out << "high";
					}
					highcheck = charData[i].landingbair[j].high;
				}
				if (charData[i].landingbair[j].type != currentC)
				{
					if (charData[i].landingbair[j].type != '0')
					{
						out << charData[i].landingbair[j].type;
					}
					currentC = charData[i].landingbair[j].type;
				}
				out << " : ";
			}

			out << charData[i].landingbair[j].Xhurmin << ',';//hurtbox
			out << charData[i].landingbair[j].Xhurmax << ',';
			out << charData[i].landingbair[j].Yhurmin << ',';
			out << charData[i].landingbair[j].Yhurmax << ',';
			out << charData[i].landingbair[j].Xhitmin << ',';//hitbox
			out << charData[i].landingbair[j].Xhitmax << ',';
			out << charData[i].landingbair[j].Yhitmin << ',';
			out << charData[i].landingbair[j].Yhitmax << ',';
			out << charData[i].landingbair[j].YhitmaxR << ',';
			out << charData[i].landingbair[j].YhitminR << ',';
			out << charData[i].landingbair[j].YhitmaxL << ',';
			out << charData[i].landingbair[j].YhitminL << ',';
			out << charData[i].landingbair[j].Xspikemin << ',';//spike
			out << charData[i].landingbair[j].Xspikemax << ',';
			out << charData[i].landingbair[j].Yspikemin << ',';
			out << charData[i].landingbair[j].Yspikemax << ',';
			out << charData[i].landingbair[j].XSAmin << ',';//super armor
			out << charData[i].landingbair[j].XSAmax << ',';
			out << charData[i].landingbair[j].YSAmin << ',';
			out << charData[i].landingbair[j].YSAmax << ',';
			out << charData[i].landingbair[j].XWBmin << ',';//windbox
			out << charData[i].landingbair[j].XWBmax << ',';
			out << charData[i].landingbair[j].YWBmin << ',';
			out << charData[i].landingbair[j].YWBmax << ',';
			out << charData[i].landingbair[j].Xgrabmin << ',';//grab box
			out << charData[i].landingbair[j].Xgrabmax << ',';
			out << charData[i].landingbair[j].Ygrabmin << ',';
			out << charData[i].landingbair[j].Ygrabmax << ',';
			out << charData[i].landingbair[j].Xreflectmin << ',';//reflector
			out << charData[i].landingbair[j].Xreflectmax << ',';
			out << charData[i].landingbair[j].Yreflectmin << ',';
			out << charData[i].landingbair[j].Yreflectmax << ',';
			out << charData[i].landingbair[j].Xscanmin << ',';//scan
			out << charData[i].landingbair[j].Xscanmax << ',';
			out << charData[i].landingbair[j].Yscanmin << ',';
			out << charData[i].landingbair[j].Yscanmax << ',';
			out << ' ';
		}
		}
		else
		{
			out << endl;
			out << "landingbair : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].landingfair.size() != 0)
		{
		for (int j = 0; j < charData[i].landingfair.size(); j++)
		{
			if (charData[i].landingfair[j].low != lowcheck || charData[i].landingfair[j].high != highcheck || charData[i].landingfair[j].type != currentC)
			{
				out << endl;
				out << "landingfair";
				if (charData[i].landingfair[j].low != lowcheck)
				{
					if (charData[i].landingfair[j].low == true)
					{
						out << "low";
					}
					lowcheck = charData[i].landingfair[j].low;
				}
				if (charData[i].landingfair[j].high != highcheck)
				{
					if (true == charData[i].landingfair[j].high)
					{
						out << "high";
					}
					highcheck = charData[i].landingfair[j].high;
				}
				if (charData[i].landingfair[j].type != currentC)
				{
					if (charData[i].landingfair[j].type != '0')
					{
						out << charData[i].landingfair[j].type;
					}
					currentC = charData[i].landingfair[j].type;
				}
				out << " : ";
			}

			out << charData[i].landingfair[j].Xhurmin << ',';//hurtbox
			out << charData[i].landingfair[j].Xhurmax << ',';
			out << charData[i].landingfair[j].Yhurmin << ',';
			out << charData[i].landingfair[j].Yhurmax << ',';
			out << charData[i].landingfair[j].Xhitmin << ',';//hitbox
			out << charData[i].landingfair[j].Xhitmax << ',';
			out << charData[i].landingfair[j].Yhitmin << ',';
			out << charData[i].landingfair[j].Yhitmax << ',';
			out << charData[i].landingfair[j].YhitmaxR << ',';
			out << charData[i].landingfair[j].YhitminR << ',';
			out << charData[i].landingfair[j].YhitmaxL << ',';
			out << charData[i].landingfair[j].YhitminL << ',';
			out << charData[i].landingfair[j].Xspikemin << ',';//spike
			out << charData[i].landingfair[j].Xspikemax << ',';
			out << charData[i].landingfair[j].Yspikemin << ',';
			out << charData[i].landingfair[j].Yspikemax << ',';
			out << charData[i].landingfair[j].XSAmin << ',';//super armor
			out << charData[i].landingfair[j].XSAmax << ',';
			out << charData[i].landingfair[j].YSAmin << ',';
			out << charData[i].landingfair[j].YSAmax << ',';
			out << charData[i].landingfair[j].XWBmin << ',';//windbox
			out << charData[i].landingfair[j].XWBmax << ',';
			out << charData[i].landingfair[j].YWBmin << ',';
			out << charData[i].landingfair[j].YWBmax << ',';
			out << charData[i].landingfair[j].Xgrabmin << ',';//grab box
			out << charData[i].landingfair[j].Xgrabmax << ',';
			out << charData[i].landingfair[j].Ygrabmin << ',';
			out << charData[i].landingfair[j].Ygrabmax << ',';
			out << charData[i].landingfair[j].Xreflectmin << ',';//reflector
			out << charData[i].landingfair[j].Xreflectmax << ',';
			out << charData[i].landingfair[j].Yreflectmin << ',';
			out << charData[i].landingfair[j].Yreflectmax << ',';
			out << charData[i].landingfair[j].Xscanmin << ',';//scan
			out << charData[i].landingfair[j].Xscanmax << ',';
			out << charData[i].landingfair[j].Yscanmin << ',';
			out << charData[i].landingfair[j].Yscanmax << ',';
			out << ' ';
		}
		}
		else
		{
			out << endl;
			out << "landingfair : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].landingupair.size() != 0)
		{
		for (int j = 0; j < charData[i].landingupair.size(); j++)
		{
			if (charData[i].landingupair[j].low != lowcheck || charData[i].landingupair[j].high != highcheck || charData[i].landingupair[j].type != currentC)
			{
				out << endl;
				out << "landingupair";
				if (charData[i].landingupair[j].low != lowcheck)
				{
					if (charData[i].landingupair[j].low == true)
					{
						out << "low";
					}
					lowcheck = charData[i].landingupair[j].low;
				}
				if (charData[i].landingupair[j].high != highcheck)
				{
					if (true == charData[i].landingupair[j].high)
					{
						out << "high";
					}
					highcheck = charData[i].landingupair[j].high;
				}
				if (charData[i].landingupair[j].type != currentC)
				{
					if (charData[i].landingupair[j].type != '0')
					{
						out << charData[i].landingupair[j].type;
					}
					currentC = charData[i].landingupair[j].type;
				}
				out << " : ";
			}

			out << charData[i].landingupair[j].Xhurmin << ',';//hurtbox
			out << charData[i].landingupair[j].Xhurmax << ',';
			out << charData[i].landingupair[j].Yhurmin << ',';
			out << charData[i].landingupair[j].Yhurmax << ',';
			out << charData[i].landingupair[j].Xhitmin << ',';//hitbox
			out << charData[i].landingupair[j].Xhitmax << ',';
			out << charData[i].landingupair[j].Yhitmin << ',';
			out << charData[i].landingupair[j].Yhitmax << ',';
			out << charData[i].landingupair[j].YhitmaxR << ',';
			out << charData[i].landingupair[j].YhitminR << ',';
			out << charData[i].landingupair[j].YhitmaxL << ',';
			out << charData[i].landingupair[j].YhitminL << ',';
			out << charData[i].landingupair[j].Xspikemin << ',';//spike
			out << charData[i].landingupair[j].Xspikemax << ',';
			out << charData[i].landingupair[j].Yspikemin << ',';
			out << charData[i].landingupair[j].Yspikemax << ',';
			out << charData[i].landingupair[j].XSAmin << ',';//super armor
			out << charData[i].landingupair[j].XSAmax << ',';
			out << charData[i].landingupair[j].YSAmin << ',';
			out << charData[i].landingupair[j].YSAmax << ',';
			out << charData[i].landingupair[j].XWBmin << ',';//windbox
			out << charData[i].landingupair[j].XWBmax << ',';
			out << charData[i].landingupair[j].YWBmin << ',';
			out << charData[i].landingupair[j].YWBmax << ',';
			out << charData[i].landingupair[j].Xgrabmin << ',';//grab box
			out << charData[i].landingupair[j].Xgrabmax << ',';
			out << charData[i].landingupair[j].Ygrabmin << ',';
			out << charData[i].landingupair[j].Ygrabmax << ',';
			out << charData[i].landingupair[j].Xreflectmin << ',';//reflector
			out << charData[i].landingupair[j].Xreflectmax << ',';
			out << charData[i].landingupair[j].Yreflectmin << ',';
			out << charData[i].landingupair[j].Yreflectmax << ',';
			out << charData[i].landingupair[j].Xscanmin << ',';//scan
			out << charData[i].landingupair[j].Xscanmax << ',';
			out << charData[i].landingupair[j].Yscanmin << ',';
			out << charData[i].landingupair[j].Yscanmax << ',';
			out << ' ';
		}
		}
		else
		{
			out << endl;
			out << "landingupair : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].landingdair.size() != 0)
		{
		for (int j = 0; j < charData[i].landingdair.size(); j++)
		{
			if (charData[i].landingdair[j].low != lowcheck || charData[i].landingdair[j].high != highcheck || charData[i].landingdair[j].type != currentC)
			{
				out << endl;
				out << "landingdair";
				if (charData[i].landingdair[j].low != lowcheck)
				{
					if (charData[i].landingdair[j].low == true)
					{
						out << "low";
					}
					lowcheck = charData[i].landingdair[j].low;
				}
				if (charData[i].landingdair[j].high != highcheck)
				{
					if (true == charData[i].landingdair[j].high)
					{
						out << "high";
					}
					highcheck = charData[i].landingdair[j].high;
				}
				if (charData[i].landingdair[j].type != currentC)
				{
					if (charData[i].landingdair[j].type != '0')
					{
						out << charData[i].landingdair[j].type;
					}
					currentC = charData[i].landingdair[j].type;
				}
				out << " : ";
			}

			out << charData[i].landingdair[j].Xhurmin << ',';//hurtbox
			out << charData[i].landingdair[j].Xhurmax << ',';
			out << charData[i].landingdair[j].Yhurmin << ',';
			out << charData[i].landingdair[j].Yhurmax << ',';
			out << charData[i].landingdair[j].Xhitmin << ',';//hitbox
			out << charData[i].landingdair[j].Xhitmax << ',';
			out << charData[i].landingdair[j].Yhitmin << ',';
			out << charData[i].landingdair[j].Yhitmax << ',';
			out << charData[i].landingdair[j].YhitmaxR << ',';
			out << charData[i].landingdair[j].YhitminR << ',';
			out << charData[i].landingdair[j].YhitmaxL << ',';
			out << charData[i].landingdair[j].YhitminL << ',';
			out << charData[i].landingdair[j].Xspikemin << ',';//spike
			out << charData[i].landingdair[j].Xspikemax << ',';
			out << charData[i].landingdair[j].Yspikemin << ',';
			out << charData[i].landingdair[j].Yspikemax << ',';
			out << charData[i].landingdair[j].XSAmin << ',';//super armor
			out << charData[i].landingdair[j].XSAmax << ',';
			out << charData[i].landingdair[j].YSAmin << ',';
			out << charData[i].landingdair[j].YSAmax << ',';
			out << charData[i].landingdair[j].XWBmin << ',';//windbox
			out << charData[i].landingdair[j].XWBmax << ',';
			out << charData[i].landingdair[j].YWBmin << ',';
			out << charData[i].landingdair[j].YWBmax << ',';
			out << charData[i].landingdair[j].Xgrabmin << ',';//grab box
			out << charData[i].landingdair[j].Xgrabmax << ',';
			out << charData[i].landingdair[j].Ygrabmin << ',';
			out << charData[i].landingdair[j].Ygrabmax << ',';
			out << charData[i].landingdair[j].Xreflectmin << ',';//reflector
			out << charData[i].landingdair[j].Xreflectmax << ',';
			out << charData[i].landingdair[j].Yreflectmin << ',';
			out << charData[i].landingdair[j].Yreflectmax << ',';
			out << charData[i].landingdair[j].Xscanmin << ',';//scan
			out << charData[i].landingdair[j].Xscanmax << ',';
			out << charData[i].landingdair[j].Yscanmin << ',';
			out << charData[i].landingdair[j].Yscanmax << ',';
			out << ' ';
		}
		}
		else
		{
			out << endl;
			out << "landingdair : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].landingnair.size() != 0)
		{
		for (int j = 0; j < charData[i].landingnair.size(); j++)
		{
			if (charData[i].landingnair[j].low != lowcheck || charData[i].landingnair[j].high != highcheck || charData[i].landingnair[j].type != currentC)
			{
				out << endl;
				out << "landingnair";
				if (charData[i].landingnair[j].low != lowcheck)
				{
					if (charData[i].landingnair[j].low == true)
					{
						out << "low";
					}
					lowcheck = charData[i].landingnair[j].low;
				}
				if (charData[i].landingnair[j].high != highcheck)
				{
					if (true == charData[i].landingnair[j].high)
					{
						out << "high";
					}
					highcheck = charData[i].landingnair[j].high;
				}
				if (charData[i].landingnair[j].type != currentC)
				{
					if (charData[i].landingnair[j].type != '0')
					{
						out << charData[i].landingnair[j].type;
					}
					currentC = charData[i].landingnair[j].type;
				}
				out << " : ";
			}

			out << charData[i].landingnair[j].Xhurmin << ',';//hurtbox
			out << charData[i].landingnair[j].Xhurmax << ',';
			out << charData[i].landingnair[j].Yhurmin << ',';
			out << charData[i].landingnair[j].Yhurmax << ',';
			out << charData[i].landingnair[j].Xhitmin << ',';//hitbox
			out << charData[i].landingnair[j].Xhitmax << ',';
			out << charData[i].landingnair[j].Yhitmin << ',';
			out << charData[i].landingnair[j].Yhitmax << ',';
			out << charData[i].landingnair[j].YhitmaxR << ',';
			out << charData[i].landingnair[j].YhitminR << ',';
			out << charData[i].landingnair[j].YhitmaxL << ',';
			out << charData[i].landingnair[j].YhitminL << ',';
			out << charData[i].landingnair[j].Xspikemin << ',';//spike
			out << charData[i].landingnair[j].Xspikemax << ',';
			out << charData[i].landingnair[j].Yspikemin << ',';
			out << charData[i].landingnair[j].Yspikemax << ',';
			out << charData[i].landingnair[j].XSAmin << ',';//super armor
			out << charData[i].landingnair[j].XSAmax << ',';
			out << charData[i].landingnair[j].YSAmin << ',';
			out << charData[i].landingnair[j].YSAmax << ',';
			out << charData[i].landingnair[j].XWBmin << ',';//windbox
			out << charData[i].landingnair[j].XWBmax << ',';
			out << charData[i].landingnair[j].YWBmin << ',';
			out << charData[i].landingnair[j].YWBmax << ',';
			out << charData[i].landingnair[j].Xgrabmin << ',';//grab box
			out << charData[i].landingnair[j].Xgrabmax << ',';
			out << charData[i].landingnair[j].Ygrabmin << ',';
			out << charData[i].landingnair[j].Ygrabmax << ',';
			out << charData[i].landingnair[j].Xreflectmin << ',';//reflector
			out << charData[i].landingnair[j].Xreflectmax << ',';
			out << charData[i].landingnair[j].Yreflectmin << ',';
			out << charData[i].landingnair[j].Yreflectmax << ',';
			out << charData[i].landingnair[j].Xscanmin << ',';//scan
			out << charData[i].landingnair[j].Xscanmax << ',';
			out << charData[i].landingnair[j].Yscanmin << ',';
			out << charData[i].landingnair[j].Yscanmax << ',';
			out << ' ';
		}
		}
		else
		{
			out << endl;
			out << "landingnair : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].neutralbair.size() != 0)
		{
		for (int j = 0; j < charData[i].neutralbair.size(); j++)
		{
			if (charData[i].neutralbair[j].low != lowcheck || charData[i].neutralbair[j].high != highcheck || charData[i].neutralbair[j].type != currentC)
			{
				out << endl;
				out << "neutralbair";
				if (charData[i].neutralbair[j].low != lowcheck)
				{
					if (charData[i].neutralbair[j].low == true)
					{
						out << "low";
					}
					lowcheck = charData[i].neutralbair[j].low;
				}
				if (charData[i].neutralbair[j].high != highcheck)
				{
					if (true == charData[i].neutralbair[j].high)
					{
						out << "high";
					}
					highcheck = charData[i].neutralbair[j].high;
				}
				if (charData[i].neutralbair[j].type != currentC)
				{
					if (charData[i].neutralbair[j].type != '0')
					{
						out << charData[i].neutralbair[j].type;
					}
					currentC = charData[i].neutralbair[j].type;
				}
				out << " : ";
			}

			out << charData[i].neutralbair[j].Xhurmin << ',';//hurtbox
			out << charData[i].neutralbair[j].Xhurmax << ',';
			out << charData[i].neutralbair[j].Yhurmin << ',';
			out << charData[i].neutralbair[j].Yhurmax << ',';
			out << charData[i].neutralbair[j].Xhitmin << ',';//hitbox
			out << charData[i].neutralbair[j].Xhitmax << ',';
			out << charData[i].neutralbair[j].Yhitmin << ',';
			out << charData[i].neutralbair[j].Yhitmax << ',';
			out << charData[i].neutralbair[j].YhitmaxR << ',';
			out << charData[i].neutralbair[j].YhitminR << ',';
			out << charData[i].neutralbair[j].YhitmaxL << ',';
			out << charData[i].neutralbair[j].YhitminL << ',';
			out << charData[i].neutralbair[j].Xspikemin << ',';//spike
			out << charData[i].neutralbair[j].Xspikemax << ',';
			out << charData[i].neutralbair[j].Yspikemin << ',';
			out << charData[i].neutralbair[j].Yspikemax << ',';
			out << charData[i].neutralbair[j].XSAmin << ',';//super armor
			out << charData[i].neutralbair[j].XSAmax << ',';
			out << charData[i].neutralbair[j].YSAmin << ',';
			out << charData[i].neutralbair[j].YSAmax << ',';
			out << charData[i].neutralbair[j].XWBmin << ',';//windbox
			out << charData[i].neutralbair[j].XWBmax << ',';
			out << charData[i].neutralbair[j].YWBmin << ',';
			out << charData[i].neutralbair[j].YWBmax << ',';
			out << charData[i].neutralbair[j].Xgrabmin << ',';//grab box
			out << charData[i].neutralbair[j].Xgrabmax << ',';
			out << charData[i].neutralbair[j].Ygrabmin << ',';
			out << charData[i].neutralbair[j].Ygrabmax << ',';
			out << charData[i].neutralbair[j].Xreflectmin << ',';//reflector
			out << charData[i].neutralbair[j].Xreflectmax << ',';
			out << charData[i].neutralbair[j].Yreflectmin << ',';
			out << charData[i].neutralbair[j].Yreflectmax << ',';
			out << charData[i].neutralbair[j].Xscanmin << ',';//scan
			out << charData[i].neutralbair[j].Xscanmax << ',';
			out << charData[i].neutralbair[j].Yscanmin << ',';
			out << charData[i].neutralbair[j].Yscanmax << ',';
			out << ' ';
		}
		}
		else
		{
			out << endl;
			out << "neutralbair : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].neutralb.size() != 0)
		{
		for (int j = 0; j < charData[i].neutralb.size(); j++)
		{
			if (charData[i].neutralb[j].low != lowcheck || charData[i].neutralb[j].high != highcheck || charData[i].neutralb[j].type != currentC)
			{
				out << endl;
				out << "neutralb";
				if (charData[i].neutralb[j].low != lowcheck)
				{
					if (charData[i].neutralb[j].low == true)
					{
						out << "low";
					}
					lowcheck = charData[i].neutralb[j].low;
				}
				if (charData[i].neutralb[j].high != highcheck)
				{
					if (true == charData[i].neutralb[j].high)
					{
						out << "high";
					}
					highcheck = charData[i].neutralb[j].high;
				}
				if (charData[i].neutralb[j].type != currentC)
				{
					if (charData[i].neutralb[j].type != '0')
					{
						out << charData[i].neutralb[j].type;
					}
					currentC = charData[i].neutralb[j].type;
				}
				out << " : ";
			}

			out << charData[i].neutralb[j].Xhurmin << ',';//hurtbox
			out << charData[i].neutralb[j].Xhurmax << ',';
			out << charData[i].neutralb[j].Yhurmin << ',';
			out << charData[i].neutralb[j].Yhurmax << ',';
			out << charData[i].neutralb[j].Xhitmin << ',';//hitbox
			out << charData[i].neutralb[j].Xhitmax << ',';
			out << charData[i].neutralb[j].Yhitmin << ',';
			out << charData[i].neutralb[j].Yhitmax << ',';
			out << charData[i].neutralb[j].YhitmaxR << ',';
			out << charData[i].neutralb[j].YhitminR << ',';
			out << charData[i].neutralb[j].YhitmaxL << ',';
			out << charData[i].neutralb[j].YhitminL << ',';
			out << charData[i].neutralb[j].Xspikemin << ',';//spike
			out << charData[i].neutralb[j].Xspikemax << ',';
			out << charData[i].neutralb[j].Yspikemin << ',';
			out << charData[i].neutralb[j].Yspikemax << ',';
			out << charData[i].neutralb[j].XSAmin << ',';//super armor
			out << charData[i].neutralb[j].XSAmax << ',';
			out << charData[i].neutralb[j].YSAmin << ',';
			out << charData[i].neutralb[j].YSAmax << ',';
			out << charData[i].neutralb[j].XWBmin << ',';//windbox
			out << charData[i].neutralb[j].XWBmax << ',';
			out << charData[i].neutralb[j].YWBmin << ',';
			out << charData[i].neutralb[j].YWBmax << ',';
			out << charData[i].neutralb[j].Xgrabmin << ',';//grab box
			out << charData[i].neutralb[j].Xgrabmax << ',';
			out << charData[i].neutralb[j].Ygrabmin << ',';
			out << charData[i].neutralb[j].Ygrabmax << ',';
			out << charData[i].neutralb[j].Xreflectmin << ',';//reflector
			out << charData[i].neutralb[j].Xreflectmax << ',';
			out << charData[i].neutralb[j].Yreflectmin << ',';
			out << charData[i].neutralb[j].Yreflectmax << ',';
			out << charData[i].neutralb[j].Xscanmin << ',';//scan
			out << charData[i].neutralb[j].Xscanmax << ',';
			out << charData[i].neutralb[j].Yscanmin << ',';
			out << charData[i].neutralb[j].Yscanmax << ',';
			out << ' ';
		}
		}
		else
		{
			out << endl;
			out << "neutralb : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].landingneutralb.size() != 0)
		{
		for (int j = 0; j < charData[i].landingneutralb.size(); j++)
		{
			if (charData[i].landingneutralb[j].low != lowcheck || charData[i].landingneutralb[j].high != highcheck || charData[i].landingneutralb[j].type != currentC)
			{
				out << endl;
				out << "landingneutralb";
				if (charData[i].landingneutralb[j].low != lowcheck)
				{
					if (charData[i].landingneutralb[j].low == true)
					{
						out << "low";
					}
					lowcheck = charData[i].landingneutralb[j].low;
				}
				if (charData[i].landingneutralb[j].high != highcheck)
				{
					if (true == charData[i].landingneutralb[j].high)
					{
						out << "high";
					}
					highcheck = charData[i].landingneutralb[j].high;
				}
				if (charData[i].landingneutralb[j].type != currentC)
				{
					if (charData[i].landingneutralb[j].type != '0')
					{
						out << charData[i].landingneutralb[j].type;
					}
					currentC = charData[i].landingneutralb[j].type;
				}
				out << " : ";
			}

			out << charData[i].landingneutralb[j].Xhurmin << ',';//hurtbox
			out << charData[i].landingneutralb[j].Xhurmax << ',';
			out << charData[i].landingneutralb[j].Yhurmin << ',';
			out << charData[i].landingneutralb[j].Yhurmax << ',';
			out << charData[i].landingneutralb[j].Xhitmin << ',';//hitbox
			out << charData[i].landingneutralb[j].Xhitmax << ',';
			out << charData[i].landingneutralb[j].Yhitmin << ',';
			out << charData[i].landingneutralb[j].Yhitmax << ',';
			out << charData[i].landingneutralb[j].YhitmaxR << ',';
			out << charData[i].landingneutralb[j].YhitminR << ',';
			out << charData[i].landingneutralb[j].YhitmaxL << ',';
			out << charData[i].landingneutralb[j].YhitminL << ',';
			out << charData[i].landingneutralb[j].Xspikemin << ',';//spike
			out << charData[i].landingneutralb[j].Xspikemax << ',';
			out << charData[i].landingneutralb[j].Yspikemin << ',';
			out << charData[i].landingneutralb[j].Yspikemax << ',';
			out << charData[i].landingneutralb[j].XSAmin << ',';//super armor
			out << charData[i].landingneutralb[j].XSAmax << ',';
			out << charData[i].landingneutralb[j].YSAmin << ',';
			out << charData[i].landingneutralb[j].YSAmax << ',';
			out << charData[i].landingneutralb[j].XWBmin << ',';//windbox
			out << charData[i].landingneutralb[j].XWBmax << ',';
			out << charData[i].landingneutralb[j].YWBmin << ',';
			out << charData[i].landingneutralb[j].YWBmax << ',';
			out << charData[i].landingneutralb[j].Xgrabmin << ',';//grab box
			out << charData[i].landingneutralb[j].Xgrabmax << ',';
			out << charData[i].landingneutralb[j].Ygrabmin << ',';
			out << charData[i].landingneutralb[j].Ygrabmax << ',';
			out << charData[i].landingneutralb[j].Xreflectmin << ',';//reflector
			out << charData[i].landingneutralb[j].Xreflectmax << ',';
			out << charData[i].landingneutralb[j].Yreflectmin << ',';
			out << charData[i].landingneutralb[j].Yreflectmax << ',';
			out << charData[i].landingneutralb[j].Xscanmin << ',';//scan
			out << charData[i].landingneutralb[j].Xscanmax << ',';
			out << charData[i].landingneutralb[j].Yscanmin << ',';
			out << charData[i].landingneutralb[j].Yscanmax << ',';
			out << ' ';
		}
		}
		else
		{
			out << endl;
			out << "landingneutralb : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].sidebair.size() != 0)
		{
		for (int j = 0; j < charData[i].sidebair.size(); j++)
		{
			if (charData[i].sidebair[j].low != lowcheck || charData[i].sidebair[j].high != highcheck || charData[i].sidebair[j].type != currentC)
			{
				out << endl;
				out << "sidebair";
				if (charData[i].sidebair[j].low != lowcheck)
				{
					if (charData[i].sidebair[j].low == true)
					{
						out << "low";
					}
					lowcheck = charData[i].sidebair[j].low;
				}
				if (charData[i].sidebair[j].high != highcheck)
				{
					if (true == charData[i].sidebair[j].high)
					{
						out << "high";
					}
					highcheck = charData[i].sidebair[j].high;
				}
				if (charData[i].sidebair[j].type != currentC)
				{
					if (charData[i].sidebair[j].type != '0')
					{
						out << charData[i].sidebair[j].type;
					}
					currentC = charData[i].sidebair[j].type;
				}
				out << " : ";
			}

			out << charData[i].sidebair[j].Xhurmin << ',';//hurtbox
			out << charData[i].sidebair[j].Xhurmax << ',';
			out << charData[i].sidebair[j].Yhurmin << ',';
			out << charData[i].sidebair[j].Yhurmax << ',';
			out << charData[i].sidebair[j].Xhitmin << ',';//hitbox
			out << charData[i].sidebair[j].Xhitmax << ',';
			out << charData[i].sidebair[j].Yhitmin << ',';
			out << charData[i].sidebair[j].Yhitmax << ',';
			out << charData[i].sidebair[j].YhitmaxR << ',';
			out << charData[i].sidebair[j].YhitminR << ',';
			out << charData[i].sidebair[j].YhitmaxL << ',';
			out << charData[i].sidebair[j].YhitminL << ',';
			out << charData[i].sidebair[j].Xspikemin << ',';//spike
			out << charData[i].sidebair[j].Xspikemax << ',';
			out << charData[i].sidebair[j].Yspikemin << ',';
			out << charData[i].sidebair[j].Yspikemax << ',';
			out << charData[i].sidebair[j].XSAmin << ',';//super armor
			out << charData[i].sidebair[j].XSAmax << ',';
			out << charData[i].sidebair[j].YSAmin << ',';
			out << charData[i].sidebair[j].YSAmax << ',';
			out << charData[i].sidebair[j].XWBmin << ',';//windbox
			out << charData[i].sidebair[j].XWBmax << ',';
			out << charData[i].sidebair[j].YWBmin << ',';
			out << charData[i].sidebair[j].YWBmax << ',';
			out << charData[i].sidebair[j].Xgrabmin << ',';//grab box
			out << charData[i].sidebair[j].Xgrabmax << ',';
			out << charData[i].sidebair[j].Ygrabmin << ',';
			out << charData[i].sidebair[j].Ygrabmax << ',';
			out << charData[i].sidebair[j].Xreflectmin << ',';//reflector
			out << charData[i].sidebair[j].Xreflectmax << ',';
			out << charData[i].sidebair[j].Yreflectmin << ',';
			out << charData[i].sidebair[j].Yreflectmax << ',';
			out << charData[i].sidebair[j].Xscanmin << ',';//scan
			out << charData[i].sidebair[j].Xscanmax << ',';
			out << charData[i].sidebair[j].Yscanmin << ',';
			out << charData[i].sidebair[j].Yscanmax << ',';
			out << ' ';
		}
		}
		else
		{
			out << endl;
			out << "sidebair : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].sideb.size() != 0)
		{
		for (int j = 0; j < charData[i].sideb.size(); j++)
		{
			if (charData[i].sideb[j].low != lowcheck || charData[i].sideb[j].high != highcheck || charData[i].sideb[j].type != currentC)
			{
				out << endl;
				out << "sideb";
				if (charData[i].sideb[j].low != lowcheck)
				{
					if (charData[i].sideb[j].low == true)
					{
						out << "low";
					}
					lowcheck = charData[i].sideb[j].low;
				}
				if (charData[i].sideb[j].high != highcheck)
				{
					if (true == charData[i].sideb[j].high)
					{
						out << "high";
					}
					highcheck = charData[i].sideb[j].high;
				}
				if (charData[i].sideb[j].type != currentC)
				{
					if (charData[i].sideb[j].type != '0')
					{
						out << charData[i].sideb[j].type;
					}
					currentC = charData[i].sideb[j].type;
				}
				out << " : ";
			}

			out << charData[i].sideb[j].Xhurmin << ',';//hurtbox
			out << charData[i].sideb[j].Xhurmax << ',';
			out << charData[i].sideb[j].Yhurmin << ',';
			out << charData[i].sideb[j].Yhurmax << ',';
			out << charData[i].sideb[j].Xhitmin << ',';//hitbox
			out << charData[i].sideb[j].Xhitmax << ',';
			out << charData[i].sideb[j].Yhitmin << ',';
			out << charData[i].sideb[j].Yhitmax << ',';
			out << charData[i].sideb[j].YhitmaxR << ',';
			out << charData[i].sideb[j].YhitminR << ',';
			out << charData[i].sideb[j].YhitmaxL << ',';
			out << charData[i].sideb[j].YhitminL << ',';
			out << charData[i].sideb[j].Xspikemin << ',';//spike
			out << charData[i].sideb[j].Xspikemax << ',';
			out << charData[i].sideb[j].Yspikemin << ',';
			out << charData[i].sideb[j].Yspikemax << ',';
			out << charData[i].sideb[j].XSAmin << ',';//super armor
			out << charData[i].sideb[j].XSAmax << ',';
			out << charData[i].sideb[j].YSAmin << ',';
			out << charData[i].sideb[j].YSAmax << ',';
			out << charData[i].sideb[j].XWBmin << ',';//windbox
			out << charData[i].sideb[j].XWBmax << ',';
			out << charData[i].sideb[j].YWBmin << ',';
			out << charData[i].sideb[j].YWBmax << ',';
			out << charData[i].sideb[j].Xgrabmin << ',';//grab box
			out << charData[i].sideb[j].Xgrabmax << ',';
			out << charData[i].sideb[j].Ygrabmin << ',';
			out << charData[i].sideb[j].Ygrabmax << ',';
			out << charData[i].sideb[j].Xreflectmin << ',';//reflector
			out << charData[i].sideb[j].Xreflectmax << ',';
			out << charData[i].sideb[j].Yreflectmin << ',';
			out << charData[i].sideb[j].Yreflectmax << ',';
			out << charData[i].sideb[j].Xscanmin << ',';//scan
			out << charData[i].sideb[j].Xscanmax << ',';
			out << charData[i].sideb[j].Yscanmin << ',';
			out << charData[i].sideb[j].Yscanmax << ',';
			out << ' ';
		}
		}
		else
		{
			out << endl;
			out << "sideb : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].landingsideb.size() != 0)
		{
		for (int j = 0; j < charData[i].landingsideb.size(); j++)
		{
			if (charData[i].landingsideb[j].low != lowcheck || charData[i].landingsideb[j].high != highcheck || charData[i].landingsideb[j].type != currentC)
			{
				out << endl;
				out << "landingsideb";
				if (charData[i].landingsideb[j].low != lowcheck)
				{
					if (charData[i].landingsideb[j].low == true)
					{
						out << "low";
					}
					lowcheck = charData[i].landingsideb[j].low;
				}
				if (charData[i].landingsideb[j].high != highcheck)
				{
					if (true == charData[i].landingsideb[j].high)
					{
						out << "high";
					}
					highcheck = charData[i].landingsideb[j].high;
				}
				if (charData[i].landingsideb[j].type != currentC)
				{
					if (charData[i].landingsideb[j].type != '0')
					{
						out << charData[i].landingsideb[j].type;
					}
					currentC = charData[i].landingsideb[j].type;
				}
				out << " : ";
			}

			out << charData[i].landingsideb[j].Xhurmin << ',';//hurtbox
			out << charData[i].landingsideb[j].Xhurmax << ',';
			out << charData[i].landingsideb[j].Yhurmin << ',';
			out << charData[i].landingsideb[j].Yhurmax << ',';
			out << charData[i].landingsideb[j].Xhitmin << ',';//hitbox
			out << charData[i].landingsideb[j].Xhitmax << ',';
			out << charData[i].landingsideb[j].Yhitmin << ',';
			out << charData[i].landingsideb[j].Yhitmax << ',';
			out << charData[i].landingsideb[j].YhitmaxR << ',';
			out << charData[i].landingsideb[j].YhitminR << ',';
			out << charData[i].landingsideb[j].YhitmaxL << ',';
			out << charData[i].landingsideb[j].YhitminL << ',';
			out << charData[i].landingsideb[j].Xspikemin << ',';//spike
			out << charData[i].landingsideb[j].Xspikemax << ',';
			out << charData[i].landingsideb[j].Yspikemin << ',';
			out << charData[i].landingsideb[j].Yspikemax << ',';
			out << charData[i].landingsideb[j].XSAmin << ',';//super armor
			out << charData[i].landingsideb[j].XSAmax << ',';
			out << charData[i].landingsideb[j].YSAmin << ',';
			out << charData[i].landingsideb[j].YSAmax << ',';
			out << charData[i].landingsideb[j].XWBmin << ',';//windbox
			out << charData[i].landingsideb[j].XWBmax << ',';
			out << charData[i].landingsideb[j].YWBmin << ',';
			out << charData[i].landingsideb[j].YWBmax << ',';
			out << charData[i].landingsideb[j].Xgrabmin << ',';//grab box
			out << charData[i].landingsideb[j].Xgrabmax << ',';
			out << charData[i].landingsideb[j].Ygrabmin << ',';
			out << charData[i].landingsideb[j].Ygrabmax << ',';
			out << charData[i].landingsideb[j].Xreflectmin << ',';//reflector
			out << charData[i].landingsideb[j].Xreflectmax << ',';
			out << charData[i].landingsideb[j].Yreflectmin << ',';
			out << charData[i].landingsideb[j].Yreflectmax << ',';
			out << charData[i].landingsideb[j].Xscanmin << ',';//scan
			out << charData[i].landingsideb[j].Xscanmax << ',';
			out << charData[i].landingsideb[j].Yscanmin << ',';
			out << charData[i].landingsideb[j].Yscanmax << ',';
			out << ' ';
		}
		}
		else
		{
			out << endl;
			out << "landingsideb : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].upbair.size() != 0)
		{
		for (int j = 0; j < charData[i].upbair.size(); j++)
		{
			if (charData[i].upbair[j].low != lowcheck || charData[i].upbair[j].high != highcheck || charData[i].upbair[j].type != currentC)
			{
				out << endl;
				out << "upbair";
				if (charData[i].upbair[j].low != lowcheck)
				{
					if (charData[i].upbair[j].low == true)
					{
						out << "low";
					}
					lowcheck = charData[i].upbair[j].low;
				}
				if (charData[i].upbair[j].high != highcheck)
				{
					if (true == charData[i].upbair[j].high)
					{
						out << "high";
					}
					highcheck = charData[i].upbair[j].high;
				}
				if (charData[i].upbair[j].type != currentC)
				{
					if (charData[i].upbair[j].type != '0')
					{
						out << charData[i].upbair[j].type;
					}
					currentC = charData[i].upbair[j].type;
				}
				out << " : ";
			}

			out << charData[i].upbair[j].Xhurmin << ',';//hurtbox
			out << charData[i].upbair[j].Xhurmax << ',';
			out << charData[i].upbair[j].Yhurmin << ',';
			out << charData[i].upbair[j].Yhurmax << ',';
			out << charData[i].upbair[j].Xhitmin << ',';//hitbox
			out << charData[i].upbair[j].Xhitmax << ',';
			out << charData[i].upbair[j].Yhitmin << ',';
			out << charData[i].upbair[j].Yhitmax << ',';
			out << charData[i].upbair[j].YhitmaxR << ',';
			out << charData[i].upbair[j].YhitminR << ',';
			out << charData[i].upbair[j].YhitmaxL << ',';
			out << charData[i].upbair[j].YhitminL << ',';
			out << charData[i].upbair[j].Xspikemin << ',';//spike
			out << charData[i].upbair[j].Xspikemax << ',';
			out << charData[i].upbair[j].Yspikemin << ',';
			out << charData[i].upbair[j].Yspikemax << ',';
			out << charData[i].upbair[j].XSAmin << ',';//super armor
			out << charData[i].upbair[j].XSAmax << ',';
			out << charData[i].upbair[j].YSAmin << ',';
			out << charData[i].upbair[j].YSAmax << ',';
			out << charData[i].upbair[j].XWBmin << ',';//windbox
			out << charData[i].upbair[j].XWBmax << ',';
			out << charData[i].upbair[j].YWBmin << ',';
			out << charData[i].upbair[j].YWBmax << ',';
			out << charData[i].upbair[j].Xgrabmin << ',';//grab box
			out << charData[i].upbair[j].Xgrabmax << ',';
			out << charData[i].upbair[j].Ygrabmin << ',';
			out << charData[i].upbair[j].Ygrabmax << ',';
			out << charData[i].upbair[j].Xreflectmin << ',';//reflector
			out << charData[i].upbair[j].Xreflectmax << ',';
			out << charData[i].upbair[j].Yreflectmin << ',';
			out << charData[i].upbair[j].Yreflectmax << ',';
			out << charData[i].upbair[j].Xscanmin << ',';//scan
			out << charData[i].upbair[j].Xscanmax << ',';
			out << charData[i].upbair[j].Yscanmin << ',';
			out << charData[i].upbair[j].Yscanmax << ',';
			out << ' ';
		}
		}
		else
		{
			out << endl;
			out << "upbair : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].upb.size() != 0)
		{
		for (int j = 0; j < charData[i].upb.size(); j++)
		{
			if (charData[i].upb[j].low != lowcheck || charData[i].upb[j].high != highcheck || charData[i].upb[j].type != currentC)
			{
				out << endl;
				out << "upb";
				if (charData[i].upb[j].low != lowcheck)
				{
					if (charData[i].upb[j].low == true)
					{
						out << "low";
					}
					lowcheck = charData[i].upb[j].low;
				}
				if (charData[i].upb[j].high != highcheck)
				{
					if (true == charData[i].upb[j].high)
					{
						out << "high";
					}
					highcheck = charData[i].upb[j].high;
				}
				if (charData[i].upb[j].type != currentC)
				{
					if (charData[i].upb[j].type != '0')
					{
						out << charData[i].upb[j].type;
					}
					currentC = charData[i].upb[j].type;
				}
				out << " : ";
			}

			out << charData[i].upb[j].Xhurmin << ',';//hurtbox
			out << charData[i].upb[j].Xhurmax << ',';
			out << charData[i].upb[j].Yhurmin << ',';
			out << charData[i].upb[j].Yhurmax << ',';
			out << charData[i].upb[j].Xhitmin << ',';//hitbox
			out << charData[i].upb[j].Xhitmax << ',';
			out << charData[i].upb[j].Yhitmin << ',';
			out << charData[i].upb[j].Yhitmax << ',';
			out << charData[i].upb[j].YhitmaxR << ',';
			out << charData[i].upb[j].YhitminR << ',';
			out << charData[i].upb[j].YhitmaxL << ',';
			out << charData[i].upb[j].YhitminL << ',';
			out << charData[i].upb[j].Xspikemin << ',';//spike
			out << charData[i].upb[j].Xspikemax << ',';
			out << charData[i].upb[j].Yspikemin << ',';
			out << charData[i].upb[j].Yspikemax << ',';
			out << charData[i].upb[j].XSAmin << ',';//super armor
			out << charData[i].upb[j].XSAmax << ',';
			out << charData[i].upb[j].YSAmin << ',';
			out << charData[i].upb[j].YSAmax << ',';
			out << charData[i].upb[j].XWBmin << ',';//windbox
			out << charData[i].upb[j].XWBmax << ',';
			out << charData[i].upb[j].YWBmin << ',';
			out << charData[i].upb[j].YWBmax << ',';
			out << charData[i].upb[j].Xgrabmin << ',';//grab box
			out << charData[i].upb[j].Xgrabmax << ',';
			out << charData[i].upb[j].Ygrabmin << ',';
			out << charData[i].upb[j].Ygrabmax << ',';
			out << charData[i].upb[j].Xreflectmin << ',';//reflector
			out << charData[i].upb[j].Xreflectmax << ',';
			out << charData[i].upb[j].Yreflectmin << ',';
			out << charData[i].upb[j].Yreflectmax << ',';
			out << charData[i].upb[j].Xscanmin << ',';//scan
			out << charData[i].upb[j].Xscanmax << ',';
			out << charData[i].upb[j].Yscanmin << ',';
			out << charData[i].upb[j].Yscanmax << ',';
			out << ' ';
		}
		}
		else
		{
			out << endl;
			out << "upb : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].landingupb.size() != 0)
		{
		for (int j = 0; j < charData[i].landingupb.size(); j++)
		{
			if (charData[i].landingupb[j].low != lowcheck || charData[i].landingupb[j].high != highcheck || charData[i].landingupb[j].type != currentC)
			{
				out << endl;
				out << "landingupb";
				if (charData[i].landingupb[j].low != lowcheck)
				{
					if (charData[i].landingupb[j].low == true)
					{
						out << "low";
					}
					lowcheck = charData[i].landingupb[j].low;
				}
				if (charData[i].landingupb[j].high != highcheck)
				{
					if (true == charData[i].landingupb[j].high)
					{
						out << "high";
					}
					highcheck = charData[i].landingupb[j].high;
				}
				if (charData[i].landingupb[j].type != currentC)
				{
					if (charData[i].landingupb[j].type != '0')
					{
						out << charData[i].landingupb[j].type;
					}
					currentC = charData[i].landingupb[j].type;
				}
				out << " : ";
			}

			out << charData[i].landingupb[j].Xhurmin << ',';//hurtbox
			out << charData[i].landingupb[j].Xhurmax << ',';
			out << charData[i].landingupb[j].Yhurmin << ',';
			out << charData[i].landingupb[j].Yhurmax << ',';
			out << charData[i].landingupb[j].Xhitmin << ',';//hitbox
			out << charData[i].landingupb[j].Xhitmax << ',';
			out << charData[i].landingupb[j].Yhitmin << ',';
			out << charData[i].landingupb[j].Yhitmax << ',';
			out << charData[i].landingupb[j].YhitmaxR << ',';
			out << charData[i].landingupb[j].YhitminR << ',';
			out << charData[i].landingupb[j].YhitmaxL << ',';
			out << charData[i].landingupb[j].YhitminL << ',';
			out << charData[i].landingupb[j].Xspikemin << ',';//spike
			out << charData[i].landingupb[j].Xspikemax << ',';
			out << charData[i].landingupb[j].Yspikemin << ',';
			out << charData[i].landingupb[j].Yspikemax << ',';
			out << charData[i].landingupb[j].XSAmin << ',';//super armor
			out << charData[i].landingupb[j].XSAmax << ',';
			out << charData[i].landingupb[j].YSAmin << ',';
			out << charData[i].landingupb[j].YSAmax << ',';
			out << charData[i].landingupb[j].XWBmin << ',';//windbox
			out << charData[i].landingupb[j].XWBmax << ',';
			out << charData[i].landingupb[j].YWBmin << ',';
			out << charData[i].landingupb[j].YWBmax << ',';
			out << charData[i].landingupb[j].Xgrabmin << ',';//grab box
			out << charData[i].landingupb[j].Xgrabmax << ',';
			out << charData[i].landingupb[j].Ygrabmin << ',';
			out << charData[i].landingupb[j].Ygrabmax << ',';
			out << charData[i].landingupb[j].Xreflectmin << ',';//reflector
			out << charData[i].landingupb[j].Xreflectmax << ',';
			out << charData[i].landingupb[j].Yreflectmin << ',';
			out << charData[i].landingupb[j].Yreflectmax << ',';
			out << charData[i].landingupb[j].Xscanmin << ',';//scan
			out << charData[i].landingupb[j].Xscanmax << ',';
			out << charData[i].landingupb[j].Yscanmin << ',';
			out << charData[i].landingupb[j].Yscanmax << ',';
			out << ' ';
		}
		}
		else
		{
			out << endl;
			out << "landingupb : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].downbair.size() != 0)
		{
		for (int j = 0; j < charData[i].downbair.size(); j++)
		{
			if (charData[i].downbair[j].low != lowcheck || charData[i].downbair[j].high != highcheck || charData[i].downbair[j].type != currentC)
			{
				out << endl;
				out << "downbair";
				if (charData[i].downbair[j].low != lowcheck)
				{
					if (charData[i].downbair[j].low == true)
					{
						out << "low";
					}
					lowcheck = charData[i].downbair[j].low;
				}
				if (charData[i].downbair[j].high != highcheck)
				{
					if (true == charData[i].downbair[j].high)
					{
						out << "high";
					}
					highcheck = charData[i].downbair[j].high;
				}
				if (charData[i].downbair[j].type != currentC)
				{
					if (charData[i].downbair[j].type != '0')
					{
						out << charData[i].downbair[j].type;
					}
					currentC = charData[i].downbair[j].type;
				}
				out << " : ";
			}

			out << charData[i].downbair[j].Xhurmin << ',';//hurtbox
			out << charData[i].downbair[j].Xhurmax << ',';
			out << charData[i].downbair[j].Yhurmin << ',';
			out << charData[i].downbair[j].Yhurmax << ',';
			out << charData[i].downbair[j].Xhitmin << ',';//hitbox
			out << charData[i].downbair[j].Xhitmax << ',';
			out << charData[i].downbair[j].Yhitmin << ',';
			out << charData[i].downbair[j].Yhitmax << ',';
			out << charData[i].downbair[j].YhitmaxR << ',';
			out << charData[i].downbair[j].YhitminR << ',';
			out << charData[i].downbair[j].YhitmaxL << ',';
			out << charData[i].downbair[j].YhitminL << ',';
			out << charData[i].downbair[j].Xspikemin << ',';//spike
			out << charData[i].downbair[j].Xspikemax << ',';
			out << charData[i].downbair[j].Yspikemin << ',';
			out << charData[i].downbair[j].Yspikemax << ',';
			out << charData[i].downbair[j].XSAmin << ',';//super armor
			out << charData[i].downbair[j].XSAmax << ',';
			out << charData[i].downbair[j].YSAmin << ',';
			out << charData[i].downbair[j].YSAmax << ',';
			out << charData[i].downbair[j].XWBmin << ',';//windbox
			out << charData[i].downbair[j].XWBmax << ',';
			out << charData[i].downbair[j].YWBmin << ',';
			out << charData[i].downbair[j].YWBmax << ',';
			out << charData[i].downbair[j].Xgrabmin << ',';//grab box
			out << charData[i].downbair[j].Xgrabmax << ',';
			out << charData[i].downbair[j].Ygrabmin << ',';
			out << charData[i].downbair[j].Ygrabmax << ',';
			out << charData[i].downbair[j].Xreflectmin << ',';//reflector
			out << charData[i].downbair[j].Xreflectmax << ',';
			out << charData[i].downbair[j].Yreflectmin << ',';
			out << charData[i].downbair[j].Yreflectmax << ',';
			out << charData[i].downbair[j].Xscanmin << ',';//scan
			out << charData[i].downbair[j].Xscanmax << ',';
			out << charData[i].downbair[j].Yscanmin << ',';
			out << charData[i].downbair[j].Yscanmax << ',';
			out << ' ';
		}
		}
		else
		{
			out << endl;
			out << "downbair : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].downb.size() != 0)
		{
		for (int j = 0; j < charData[i].downb.size(); j++)
		{
			if (charData[i].downb[j].low != lowcheck || charData[i].downb[j].high != highcheck || charData[i].downb[j].type != currentC)
			{
				out << endl;
				out << "downb";
				if (charData[i].downb[j].low != lowcheck)
				{
					if (charData[i].downb[j].low == true)
					{
						out << "low";
					}
					lowcheck = charData[i].downb[j].low;
				}
				if (charData[i].downb[j].high != highcheck)
				{
					if (true == charData[i].downb[j].high)
					{
						out << "high";
					}
					highcheck = charData[i].downb[j].high;
				}
				if (charData[i].downb[j].type != currentC)
				{
					if (charData[i].downb[j].type != '0')
					{
						out << charData[i].downb[j].type;
					}
					currentC = charData[i].downb[j].type;
				}
				out << " : ";
			}

			out << charData[i].downb[j].Xhurmin << ',';//hurtbox
			out << charData[i].downb[j].Xhurmax << ',';
			out << charData[i].downb[j].Yhurmin << ',';
			out << charData[i].downb[j].Yhurmax << ',';
			out << charData[i].downb[j].Xhitmin << ',';//hitbox
			out << charData[i].downb[j].Xhitmax << ',';
			out << charData[i].downb[j].Yhitmin << ',';
			out << charData[i].downb[j].Yhitmax << ',';
			out << charData[i].downb[j].YhitmaxR << ',';
			out << charData[i].downb[j].YhitminR << ',';
			out << charData[i].downb[j].YhitmaxL << ',';
			out << charData[i].downb[j].YhitminL << ',';
			out << charData[i].downb[j].Xspikemin << ',';//spike
			out << charData[i].downb[j].Xspikemax << ',';
			out << charData[i].downb[j].Yspikemin << ',';
			out << charData[i].downb[j].Yspikemax << ',';
			out << charData[i].downb[j].XSAmin << ',';//super armor
			out << charData[i].downb[j].XSAmax << ',';
			out << charData[i].downb[j].YSAmin << ',';
			out << charData[i].downb[j].YSAmax << ',';
			out << charData[i].downb[j].XWBmin << ',';//windbox
			out << charData[i].downb[j].XWBmax << ',';
			out << charData[i].downb[j].YWBmin << ',';
			out << charData[i].downb[j].YWBmax << ',';
			out << charData[i].downb[j].Xgrabmin << ',';//grab box
			out << charData[i].downb[j].Xgrabmax << ',';
			out << charData[i].downb[j].Ygrabmin << ',';
			out << charData[i].downb[j].Ygrabmax << ',';
			out << charData[i].downb[j].Xreflectmin << ',';//reflector
			out << charData[i].downb[j].Xreflectmax << ',';
			out << charData[i].downb[j].Yreflectmin << ',';
			out << charData[i].downb[j].Yreflectmax << ',';
			out << charData[i].downb[j].Xscanmin << ',';//scan
			out << charData[i].downb[j].Xscanmax << ',';
			out << charData[i].downb[j].Yscanmin << ',';
			out << charData[i].downb[j].Yscanmax << ',';
			out << ' ';
		}
		}
		else
		{
			out << endl;
			out << "downb : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].landingdownb.size() != 0)
		{
		for (int j = 0; j < charData[i].landingdownb.size(); j++)
		{
			if (charData[i].landingdownb[j].low != lowcheck || charData[i].landingdownb[j].high != highcheck || charData[i].landingdownb[j].type != currentC)
			{
				out << endl;
				out << "landingdownb";
				if (charData[i].landingdownb[j].low != lowcheck)
				{
					if (charData[i].landingdownb[j].low == true)
					{
						out << "low";
					}
					lowcheck = charData[i].landingdownb[j].low;
				}
				if (charData[i].landingdownb[j].high != highcheck)
				{
					if (true == charData[i].landingdownb[j].high)
					{
						out << "high";
					}
					highcheck = charData[i].landingdownb[j].high;
				}
				if (charData[i].landingdownb[j].type != currentC)
				{
					if (charData[i].landingdownb[j].type != '0')
					{
						out << charData[i].landingdownb[j].type;
					}
					currentC = charData[i].landingdownb[j].type;
				}
				out << " : ";
			}

			out << charData[i].landingdownb[j].Xhurmin << ',';//hurtbox
			out << charData[i].landingdownb[j].Xhurmax << ',';
			out << charData[i].landingdownb[j].Yhurmin << ',';
			out << charData[i].landingdownb[j].Yhurmax << ',';
			out << charData[i].landingdownb[j].Xhitmin << ',';//hitbox
			out << charData[i].landingdownb[j].Xhitmax << ',';
			out << charData[i].landingdownb[j].Yhitmin << ',';
			out << charData[i].landingdownb[j].Yhitmax << ',';
			out << charData[i].landingdownb[j].YhitmaxR << ',';
			out << charData[i].landingdownb[j].YhitminR << ',';
			out << charData[i].landingdownb[j].YhitmaxL << ',';
			out << charData[i].landingdownb[j].YhitminL << ',';
			out << charData[i].landingdownb[j].Xspikemin << ',';//spike
			out << charData[i].landingdownb[j].Xspikemax << ',';
			out << charData[i].landingdownb[j].Yspikemin << ',';
			out << charData[i].landingdownb[j].Yspikemax << ',';
			out << charData[i].landingdownb[j].XSAmin << ',';//super armor
			out << charData[i].landingdownb[j].XSAmax << ',';
			out << charData[i].landingdownb[j].YSAmin << ',';
			out << charData[i].landingdownb[j].YSAmax << ',';
			out << charData[i].landingdownb[j].XWBmin << ',';//windbox
			out << charData[i].landingdownb[j].XWBmax << ',';
			out << charData[i].landingdownb[j].YWBmin << ',';
			out << charData[i].landingdownb[j].YWBmax << ',';
			out << charData[i].landingdownb[j].Xgrabmin << ',';//grab box
			out << charData[i].landingdownb[j].Xgrabmax << ',';
			out << charData[i].landingdownb[j].Ygrabmin << ',';
			out << charData[i].landingdownb[j].Ygrabmax << ',';
			out << charData[i].landingdownb[j].Xreflectmin << ',';//reflector
			out << charData[i].landingdownb[j].Xreflectmax << ',';
			out << charData[i].landingdownb[j].Yreflectmin << ',';
			out << charData[i].landingdownb[j].Yreflectmax << ',';
			out << charData[i].landingdownb[j].Xscanmin << ',';//scan
			out << charData[i].landingdownb[j].Xscanmax << ',';
			out << charData[i].landingdownb[j].Yscanmin << ',';
			out << charData[i].landingdownb[j].Yscanmax << ',';
			out << ' ';
		}
		}
		else
		{
			out << endl;
			out << "landingdownb : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].grab.size() != 0)
		{
		for (int j = 0; j < charData[i].grab.size(); j++)
		{
			if (charData[i].grab[j].low != lowcheck || charData[i].grab[j].high != highcheck || charData[i].grab[j].type != currentC)
			{
				out << endl;
				out << "grab";
				if (charData[i].grab[j].low != lowcheck)
				{
					if (charData[i].grab[j].low == true)
					{
						out << "low";
					}
					lowcheck = charData[i].grab[j].low;
				}
				if (charData[i].grab[j].high != highcheck)
				{
					if (true == charData[i].grab[j].high)
					{
						out << "high";
					}
					highcheck = charData[i].grab[j].high;
				}
				if (charData[i].grab[j].type != currentC)
				{
					if (charData[i].grab[j].type != '0')
					{
						out << charData[i].grab[j].type;
					}
					currentC = charData[i].grab[j].type;
				}
				out << " : ";
			}

			out << charData[i].grab[j].Xhurmin << ',';//hurtbox
			out << charData[i].grab[j].Xhurmax << ',';
			out << charData[i].grab[j].Yhurmin << ',';
			out << charData[i].grab[j].Yhurmax << ',';
			out << charData[i].grab[j].Xhitmin << ',';//hitbox
			out << charData[i].grab[j].Xhitmax << ',';
			out << charData[i].grab[j].Yhitmin << ',';
			out << charData[i].grab[j].Yhitmax << ',';
			out << charData[i].grab[j].YhitmaxR << ',';
			out << charData[i].grab[j].YhitminR << ',';
			out << charData[i].grab[j].YhitmaxL << ',';
			out << charData[i].grab[j].YhitminL << ',';
			out << charData[i].grab[j].Xspikemin << ',';//spike
			out << charData[i].grab[j].Xspikemax << ',';
			out << charData[i].grab[j].Yspikemin << ',';
			out << charData[i].grab[j].Yspikemax << ',';
			out << charData[i].grab[j].XSAmin << ',';//super armor
			out << charData[i].grab[j].XSAmax << ',';
			out << charData[i].grab[j].YSAmin << ',';
			out << charData[i].grab[j].YSAmax << ',';
			out << charData[i].grab[j].XWBmin << ',';//windbox
			out << charData[i].grab[j].XWBmax << ',';
			out << charData[i].grab[j].YWBmin << ',';
			out << charData[i].grab[j].YWBmax << ',';
			out << charData[i].grab[j].Xgrabmin << ',';//grab box
			out << charData[i].grab[j].Xgrabmax << ',';
			out << charData[i].grab[j].Ygrabmin << ',';
			out << charData[i].grab[j].Ygrabmax << ',';
			out << charData[i].grab[j].Xreflectmin << ',';//reflector
			out << charData[i].grab[j].Xreflectmax << ',';
			out << charData[i].grab[j].Yreflectmin << ',';
			out << charData[i].grab[j].Yreflectmax << ',';
			out << charData[i].grab[j].Xscanmin << ',';//scan
			out << charData[i].grab[j].Xscanmax << ',';
			out << charData[i].grab[j].Yscanmin << ',';
			out << charData[i].grab[j].Yscanmax << ',';
			out << ' ';
		}
		}
		else
		{
			out << endl;
			out << "grab : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].dashgrab.size() != 0)
		{
		for (int j = 0; j < charData[i].dashgrab.size(); j++)
		{
			if (charData[i].dashgrab[j].low != lowcheck || charData[i].dashgrab[j].high != highcheck || charData[i].dashgrab[j].type != currentC)
			{
				out << endl;
				out << "dashgrab";
				if (charData[i].dashgrab[j].low != lowcheck)
				{
					if (charData[i].dashgrab[j].low == true)
					{
						out << "low";
					}
					lowcheck = charData[i].dashgrab[j].low;
				}
				if (charData[i].dashgrab[j].high != highcheck)
				{
					if (true == charData[i].dashgrab[j].high)
					{
						out << "high";
					}
					highcheck = charData[i].dashgrab[j].high;
				}
				if (charData[i].dashgrab[j].type != currentC)
				{
					if (charData[i].dashgrab[j].type != '0')
					{
						out << charData[i].dashgrab[j].type;
					}
					currentC = charData[i].dashgrab[j].type;
				}
				out << " : ";
			}

			out << charData[i].dashgrab[j].Xhurmin << ',';//hurtbox
			out << charData[i].dashgrab[j].Xhurmax << ',';
			out << charData[i].dashgrab[j].Yhurmin << ',';
			out << charData[i].dashgrab[j].Yhurmax << ',';
			out << charData[i].dashgrab[j].Xhitmin << ',';//hitbox
			out << charData[i].dashgrab[j].Xhitmax << ',';
			out << charData[i].dashgrab[j].Yhitmin << ',';
			out << charData[i].dashgrab[j].Yhitmax << ',';
			out << charData[i].dashgrab[j].YhitmaxR << ',';
			out << charData[i].dashgrab[j].YhitminR << ',';
			out << charData[i].dashgrab[j].YhitmaxL << ',';
			out << charData[i].dashgrab[j].YhitminL << ',';
			out << charData[i].dashgrab[j].Xspikemin << ',';//spike
			out << charData[i].dashgrab[j].Xspikemax << ',';
			out << charData[i].dashgrab[j].Yspikemin << ',';
			out << charData[i].dashgrab[j].Yspikemax << ',';
			out << charData[i].dashgrab[j].XSAmin << ',';//super armor
			out << charData[i].dashgrab[j].XSAmax << ',';
			out << charData[i].dashgrab[j].YSAmin << ',';
			out << charData[i].dashgrab[j].YSAmax << ',';
			out << charData[i].dashgrab[j].XWBmin << ',';//windbox
			out << charData[i].dashgrab[j].XWBmax << ',';
			out << charData[i].dashgrab[j].YWBmin << ',';
			out << charData[i].dashgrab[j].YWBmax << ',';
			out << charData[i].dashgrab[j].Xgrabmin << ',';//grab box
			out << charData[i].dashgrab[j].Xgrabmax << ',';
			out << charData[i].dashgrab[j].Ygrabmin << ',';
			out << charData[i].dashgrab[j].Ygrabmax << ',';
			out << charData[i].dashgrab[j].Xreflectmin << ',';//reflector
			out << charData[i].dashgrab[j].Xreflectmax << ',';
			out << charData[i].dashgrab[j].Yreflectmin << ',';
			out << charData[i].dashgrab[j].Yreflectmax << ',';
			out << charData[i].dashgrab[j].Xscanmin << ',';//scan
			out << charData[i].dashgrab[j].Xscanmax << ',';
			out << charData[i].dashgrab[j].Yscanmin << ',';
			out << charData[i].dashgrab[j].Yscanmax << ',';
			out << ' ';
		}
		}
		else
		{
			out << endl;
			out << "dashgrab : missing";
		}
		currentC = 'R';
		highcheck = false;
		lowcheck = false;
		if (charData[i].pivotgrab.size() != 0)
		{
		for (int j = 0; j < charData[i].pivotgrab.size(); j++)
		{
			if (charData[i].pivotgrab[j].low != lowcheck || charData[i].pivotgrab[j].high != highcheck || charData[i].pivotgrab[j].type != currentC)
			{
				out << endl;
				out << "pivotgrab";
				if (charData[i].pivotgrab[j].low != lowcheck)
				{
					if (charData[i].pivotgrab[j].low == true)
					{
						out << "low";
					}
					lowcheck = charData[i].pivotgrab[j].low;
				}
				if (charData[i].pivotgrab[j].high != highcheck)
				{
					if (true == charData[i].pivotgrab[j].high)
					{
						out << "high";
					}
					highcheck = charData[i].pivotgrab[j].high;
				}
				if (charData[i].pivotgrab[j].type != currentC)
				{
					if (charData[i].pivotgrab[j].type != '0')
					{
						out << charData[i].pivotgrab[j].type;
					}
					currentC = charData[i].pivotgrab[j].type;
				}
				out << " : ";
			}

			out << charData[i].pivotgrab[j].Xhurmin << ',';//hurtbox
			out << charData[i].pivotgrab[j].Xhurmax << ',';
			out << charData[i].pivotgrab[j].Yhurmin << ',';
			out << charData[i].pivotgrab[j].Yhurmax << ',';
			out << charData[i].pivotgrab[j].Xhitmin << ',';//hitbox
			out << charData[i].pivotgrab[j].Xhitmax << ',';
			out << charData[i].pivotgrab[j].Yhitmin << ',';
			out << charData[i].pivotgrab[j].Yhitmax << ',';
			out << charData[i].pivotgrab[j].YhitmaxR << ',';
			out << charData[i].pivotgrab[j].YhitminR << ',';
			out << charData[i].pivotgrab[j].YhitmaxL << ',';
			out << charData[i].pivotgrab[j].YhitminL << ',';
			out << charData[i].pivotgrab[j].Xspikemin << ',';//spike
			out << charData[i].pivotgrab[j].Xspikemax << ',';
			out << charData[i].pivotgrab[j].Yspikemin << ',';
			out << charData[i].pivotgrab[j].Yspikemax << ',';
			out << charData[i].pivotgrab[j].XSAmin << ',';//super armor
			out << charData[i].pivotgrab[j].XSAmax << ',';
			out << charData[i].pivotgrab[j].YSAmin << ',';
			out << charData[i].pivotgrab[j].YSAmax << ',';
			out << charData[i].pivotgrab[j].XWBmin << ',';//windbox
			out << charData[i].pivotgrab[j].XWBmax << ',';
			out << charData[i].pivotgrab[j].YWBmin << ',';
			out << charData[i].pivotgrab[j].YWBmax << ',';
			out << charData[i].pivotgrab[j].Xgrabmin << ',';//grab box
			out << charData[i].pivotgrab[j].Xgrabmax << ',';
			out << charData[i].pivotgrab[j].Ygrabmin << ',';
			out << charData[i].pivotgrab[j].Ygrabmax << ',';
			out << charData[i].pivotgrab[j].Xreflectmin << ',';//reflector
			out << charData[i].pivotgrab[j].Xreflectmax << ',';
			out << charData[i].pivotgrab[j].Yreflectmin << ',';
			out << charData[i].pivotgrab[j].Yreflectmax << ',';
			out << charData[i].pivotgrab[j].Xscanmin << ',';//scan
			out << charData[i].pivotgrab[j].Xscanmax << ',';
			out << charData[i].pivotgrab[j].Yscanmin << ',';
			out << charData[i].pivotgrab[j].Yscanmax << ',';
			out << ' ';
		}
		}
		else
		{
			out << endl;
			out << "pivotgrab : missing";
		}
		out << endl;
	}

	return 0;
}

/*
for (int y = 150; y < ymax-150; y++)
{
for (int x = 210; x < xmax - 210; x++)
{
*/