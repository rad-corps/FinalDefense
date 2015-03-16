//////////////////////////////////////////////////////////////////////////
// GeoWarp
// By Adam Hulbert
// HighScoreFile.h
// For AIE Advanced Diploma - Game Development Using CPP
/////////////////////////////////////////////////////////////////////////
#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


class HighScoreFile
{
public:
	HighScoreFile(void);
	HighScoreFile(string fileName_);
	~HighScoreFile(void);
	void Open(string fileName_);
	void Write(string text_);
	void Write(vector<string> row_, char delim_ = ',');
	string ReadAll();	
	string GetField(unsigned int row_, unsigned int col_);
	string GetField(unsigned int row_, string col_);
	void SortData(int col_);
	int Rows();
	int Cols();
	void AddHighScore(string name_, string wave_, string combo_, string score_);

private:
	void SplitData(vector<string> rows);

	vector<vector<string>> splitData;
	ifstream readFileHandle;
	ofstream writeFileHandle;
	string fileData;
	string fileName;
};

