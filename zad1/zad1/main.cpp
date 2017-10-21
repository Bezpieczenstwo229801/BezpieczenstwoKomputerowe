#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>

using namespace std;

class key_char_rank
{
public:
	key_char_rank(char k, int d)
	{
		key_char = k;
		discord = d;
	}
	char key_char;
	int discord;
};

int main()
{
	//read files
	vector<string> raw_data[21];
	for (int i = 0; i < 21; i++)
	{
		fstream in;
		in.open("k" + to_string(i) + ".txt");
		while (!in.eof())
		{
			string byte;
			in >> byte;
			raw_data[i].push_back(byte);
		}
		in.close();
	}

	//convert to char
	vector<char> data[21];
	for (int i = 0; i < 21; i++)
		for (int j = 0; j < raw_data[i].size(); j++)
			data[i].push_back(bitset<32>(raw_data[i][j]).to_ulong());
	
	int max_length = 0;
	for (int i = 0; i < 21; i++)
		if (data[i].size() > max_length)
			max_length = data[i].size();

	//guessing key
	vector<char> key;
	for (int i = 0; i < max_length; i++)
	{
		int k = -1;
		vector<key_char_rank> k_rank;
		for (int d = 0; d < 256; d++)
		{
			int discord = 0;
			for (int j = 0; j < 21; j++)
			{
				if (data[j].size() > i)
				{
					char x = data[j][i] ^ d;
					if (!((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z') || x == ' ' || x == '.' || x == ','))
						discord++;
				}
			}
			if (discord == 0)
			{
				k = d;
				break;
			}
			else
				k_rank.push_back(key_char_rank(d, discord));
		}
		if (k == -1)
		{
			int min = 30;
			for (int p = 0; p < k_rank.size(); p++)
			{
				if (k_rank[p].discord < min)
				{
					min = k_rank[p].discord;
					k = k_rank[p].key_char;
				}
			}
		}
		key.push_back(k);
	}

	//display
	for (int i = 0; i < 21; i++)
	{
		cout << "dataram " << i << ": " << endl;
		for (int j = 0; j < data[i].size(); j++)
			cout << (char)(data[i][j] ^ key[j]);
		cout << endl << endl;
	}

	system("PAUSE");
	return 0;
}