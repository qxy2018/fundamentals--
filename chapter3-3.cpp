#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string first[25];
string follow[25];
int Empty[25];
int cnt;

struct String
{
	char left;
	string right;
} Str[100];
// 判断非终结符
bool is_non_terminal(char c)
{
	if (c <= 'Z' && c >= 'A')
		return true;
	return false;
}

void get_first(char ch, char opt)
{
	int i, j;
	for (i = 0; i < cnt; i++)
	{
		// 寻找形如 ch-> 的产生式
		if (Str[i].left == ch)
		{
			for (j = 0; j < Str[i].right.length(); j++)
			{
				// 判断产生式右边当前字符的前一个字符是否是非终结符并且可以不为空
				if (j != 0 && (!is_non_terminal(Str[i].right[j - 1]) || Empty[Str[i].right[j - 1] - 'A'] == 0))
				{
					break;
				}
				// 如果当前字符为非终结符
				if (is_non_terminal(Str[i].right[j]))
				{
					get_first(Str[i].right[j], opt);
				}
				else
				{
					// 如果当前终结符不是空且不在first集中
					if (Str[i].right[j] != '#' && first[opt - 'A'].find_first_of(Str[i].right[j]) == string::npos)
					{
						first[opt - 'A'] += Str[i].right[j];
						// cout << opt << "->" << Str[i].right[j] << endl;
					}
				}
			}
		}
	}
	return;
}

void get_follow(char ch)
{
	int index;
	for (int i = 0; i < cnt; i++)
	{
		// 查早产生式的右边含有ch的产生式
		index = Str[i].right.find_first_of(ch);
		if (index != string::npos)
		{
			// 判断当前字符是否是最后一个
			if (index == Str[i].right.length() - 1)
			{
				// if (follow[ch - 'A'].find_first_of("$") == string::npos)
				// follow[ch - 'A'] += "$";
				if (follow[Str[i].left - 'A'] == "")
					get_follow(Str[i].left);
				for (int j = 0; j < follow[Str[i].left - 'A'].length(); j++)
				{
					if (follow[ch - 'A'].find_first_of(follow[Str[i].left - 'A'][j]) == string::npos)
						follow[ch - 'A'] += follow[Str[i].left - 'A'][j];
				}
			}
			else
			{
				// 当前字符的下一个字符是否是非终结符
				if (is_non_terminal(Str[i].right[index + 1]))
				{

					// 将下一个字符的first集降入到当前字符的follow集中
					for (int j = 0; j < first[Str[i].right[index + 1] - 'A'].length(); j++)
					{
						if (first[Str[i].right[index + 1] - 'A'][j] == '#')
						{
							if (follow[Str[i].left - 'A'] == "")
								get_follow(Str[i].left);
							for (int j = 0; j < follow[Str[i].left - 'A'].length(); j++)
							{
								if (follow[ch - 'A'].find_first_of(follow[Str[i].left - 'A'][j]) == string::npos)
									follow[ch - 'A'] += follow[Str[i].left - 'A'][j];
							}
							continue;
						}
						if (follow[ch - 'A'].find_first_of(first[Str[i].right[index + 1] - 'A'][j]) == string::npos)
							follow[ch - 'A'] += first[Str[i].right[index + 1] - 'A'][j];
					}
				}
				else
				{
					if (follow[ch - 'A'].find_first_of(Str[i].right[index + 1]) == string::npos)
						follow[ch - 'A'] += Str[i].right[index + 1];
				}
			}
		}
	}
}

int main()
{
	string input;
	for (int i = 0; i < 25; i++)
	{
		first[i] = "";
		follow[i] = "";
	}
	while (getline(cin, input))
	{
		if (input.empty())
			break;
		// 分割字符串
		Str[cnt].left = input[0];
		Str[cnt].right = input.substr(3, input.length() - 3);
		if (Str[cnt].right == "#")
		{
			Empty[Str[cnt].left - 'A'] = 1;
			first[Str[cnt].left - 'A'] += "#";
		}
		cnt++;
	}
	// 为部分first集添加#的情况
	for (int i = 0; i < cnt; i++)
	{
		for (int j = 0; j < Str[i].right.length(); j++)
		{
			if (!is_non_terminal(Str[i].right[j]))
				break;
			if (first[Str[i].right[j] - 'A'].find_first_of("#") == string::npos)
				break;
			if (j == Str[i].right.length() - 1)
			{
				first[Str[i].left - 'A'] += "#";
				Empty[Str[i].left - 'A'] = 1;
			}
		}
	}
	// 获取first集
	for (int i = 0; i < cnt; i++)
	{
		get_first(Str[i].left, Str[i].left);
	}
	// 获取follow集
	follow[Str[0].left - 'A'] += "$";
	for (int i = 0; i < cnt; i++)
	{
		get_follow(Str[i].left);
	}

	// 输出
	for (int i = 0; i < 25; i++)
	{
		if (first[i] != "")
		{
			sort(first[i].begin(), first[i].end());
			cout << "First(" << (char)(i + 'A') << ") = {";
			for (int j = 0; j < first[i].length(); j++)
			{
				if (j == first[i].length() - 1)
				{
					cout << first[i][j] << "}" << endl;
					break;
				}
				cout << first[i][j] << ", ";
			}
		}
	}
	for (int i = 0; i < 25; i++)
	{
		if (follow[i] != "")
		{
			sort(follow[i].begin(), follow[i].end());
			cout << "Follow(" << (char)(i + 'A') << ") = {";
			for (int j = 0; j < follow[i].length(); j++)
			{
				if (j == follow[i].length() - 1)
				{
					cout << follow[i][j] << "}" << endl;
					break;
				}
				cout << follow[i][j] << ", ";
			}
		}
	}
	cout << endl;
	return 0;
}
