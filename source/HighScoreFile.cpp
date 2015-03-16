//////////////////////////////////////////////////////////////////////////
// GeoWarp
// By Adam Hulbert
// HighScoreFile.cpp
// For AIE Advanced Diploma - Game Development Using CPP
/////////////////////////////////////////////////////////////////////////

#include "HighScoreFile.h"
#include <tchar.h>
#include <algorithm>


HighScoreFile::HighScoreFile(void)
{
}

HighScoreFile::HighScoreFile(string fileName_)
{
	Open(fileName_);
}

HighScoreFile::~HighScoreFile(void)
{
	int x = 0;
}

void HighScoreFile::Open(string fileName_)
{
	this->fileName = fileName_;
	readFileHandle.open(fileName_, ios::in);
	ReadAll();
	readFileHandle.close();
}

void HighScoreFile::Write(string text_)
{
	writeFileHandle.open(fileName, ios::out | ios::app);
	writeFileHandle << endl;
	writeFileHandle << text_ << endl;
	writeFileHandle.close();
}

void HighScoreFile::Write(vector<string> row_, char delim_)
{
	writeFileHandle.open(fileName, ios::out | ios::app);
	writeFileHandle << endl;
	for (unsigned int i = 0; i < row_.size(); ++i )
	{		
		writeFileHandle << row_[i];
		if ( i != row_.size() - 1 )
			writeFileHandle << delim_;
	}	
	writeFileHandle.close();
}

void HighScoreFile::AddHighScore(string name_, string wave_, string combo_, string score_)
{
	vector<string> temp;
	temp.push_back(name_);
	temp.push_back(wave_);
	temp.push_back(combo_);
	temp.push_back(score_);
	Write(temp, ',');
}

//split while reading.
string HighScoreFile::ReadAll()
{
	string line;
	vector<string> rows;
	while (getline(readFileHandle, line))
    {
		fileData += line + "\n";
		rows.push_back(line);
    }
	SplitData(rows);
	
	return fileData;
}

//TODO: col should used in this predicate when called from SortData
// atm 3 is hard coded (score column)
bool mySortFunction (vector<string> i,vector<string> j) 
{ 	
	return atoi(i[3].c_str()) > atoi(j[3].c_str());
}

void HighScoreFile::SortData(int col_)
{
	std::sort(splitData.begin(), splitData.end(), mySortFunction);
}

void HighScoreFile::SplitData(vector<string> rows)
{
	splitData.clear();

	for ( unsigned int i = 0; i < rows.size(); ++i )
	{
		splitData.push_back(vector<string>());
		string currentRow = rows[i];		
		string::size_type strPos = 0;
		string::size_type strPos2 = 0;
		while (  string::npos != strPos2 )
		{			
			strPos2 = currentRow.find(',', strPos);
			string temp = currentRow.substr(strPos, strPos2-strPos);
			strPos = strPos2 + 1;
			splitData[i].push_back(temp);
		}
	}	
}

int HighScoreFile::Rows()
{
	return splitData.size();
}

//this makes the assumption that there is at least one row loaded in splitData
//and that each vector in splitData is of equal size (this is up to the csv passed in)
int HighScoreFile::Cols()
{
	return splitData[0].size();
}

string HighScoreFile::GetField(unsigned int row_, unsigned int col_)
{
	//invalid parameter checks
	if ( col_ >= splitData[row_].size() ) 
		return "";
	if ( row_ >= splitData.size() )
		return "";

	//return the field
	return splitData[row_][col_];
}

string HighScoreFile::GetField(unsigned int row_, string col_)
{
	//invalid parameter checks
	if ( col_ != "NAME" && col_ != "WAVE" && col_ != "COMBO_COUNTER" && col_ != "SCORE") 
		return "";
	if ( row_ >= splitData.size() )
		return "";

	//return the field
	if ( col_ == "NAME" )
		return splitData[row_][0];
	if ( col_ == "WAVE" )
		return splitData[row_][1];
	if ( col_ == "COMBO_COUNTER" )
		return splitData[row_][2];
	if ( col_ == "SCORE" )
		return splitData[row_][3];

	return "";
}




