#include<iostream>
#include<map>
#include<set>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

void test_map()
{
	map<string, string> dict;
	dict.insert(make_pair("字符串", "string"));
	dict.insert(make_pair("排序", "sort"));
	dict.insert(make_pair("左", "left"));
	//既然支持[]的使用，这里不妨这样进行插入
	//插入的K值相同的情况，V的值不同
	dict["结束"] = "finish";
	dict["结束"] = "begin";//只关心K值，这个value会覆盖上面的那个value值（finish）
	//插入的V值相同的情况，K的值不同
	dict["糟糕"] = "beautiful";
	dict["美好"] = "beautiful";

	//从结果也可以看出来，是按照K值的ASCII值进行的排序，其中只关心K值，不在乎Value的值

	for (auto& e : dict)
	{
		cout << e.first << ":" << e.second << endl;
	}


	string strs[] = { "sort", "insert", "sort", "sort", "insert", "erase" };
	map<string, int> CountMap;

	//[]实现的使用方法是insert,insert的返回值是pair<iterator,bool>

	//for (auto& s : strs)
	//{
	//	//如果成功则返回那个新插入结点的指针，第二个参数设置为true
	//	//如果失败，说明已经存在，那就返回那个已经存在结点的指针，并且第二个参数设置为false
	//	pair<map<string, int>::iterator, bool> ret = CountMap.insert(make_pair(s, 1));
	//	//说明这个值已经存储在了vector中，不需要在插入了
	//	if (ret.second == false)
	//	{
	//		//ret是一个pair，ret.first拿到pair里面的第一个参数，再去second拿到map里面的int
	//		ret.first->second++;
	//	}

	//}


	//结论：map[]有两层作用
	//1.如果K不在，插入pair(K,V())，并且返回value的引用（便于修改）
	//2.如果K在，不插入，返回跟K相等那个结点的value的引用
	for (auto& s : strs)
	{
		CountMap[s]++;
	}

	for (auto& e : CountMap)
	{
		cout << e.first << ":" << e.second << endl;
	}
}


void test_multiset()
{
	multiset<int> ms;
	ms.insert(1);
	ms.insert(1);
	ms.insert(2);
	ms.insert(2);
	ms.insert(2);
	ms.insert(5);
	ms.insert(8);
	ms.insert(9);

	multiset<int>::iterator it = ms.begin();
	while (it != ms.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	//这个接口用来统计次数
	cout << ms.count(2) << endl;

	//如果有多个相同的值，找的是中序遍历的第一个
	auto pos = ms.find(2);
	while(pos != ms.end())
	{
		cout << *pos << " ";
		++pos;
	}
	cout << endl;

}


void test_multimap()
{
	typedef multimap<string, string> DICT;
	typedef multimap<string, string>::iterator  DICT_IT;

	DICT dict;
	dict.insert(make_pair("string", "字符串"));
	dict.insert(make_pair("left", "左边"));
	dict.insert(make_pair("left", "糟糕"));
	dict.insert(make_pair("left", "糟糕"));
	dict.insert(make_pair("right", "右边"));
	dict.insert(pair<string, string>("beautiful", "美丽"));

	DICT_IT it = dict.begin();
	while (it != dict.end())
	{
		cout << it->first << ":" << it->second << endl;
		++it;
	}
}



void GetFavoriteFruit(const vector<string>& fruits,size_t k)
{
	typedef map<string, int>::iterator CountMapIt;
	//首先统计出来每种水果的次数
	map<string, int> countMap;
	for (auto& e : fruits)
	{
		countMap[e]++;
	}
	//这就已经统计出来了，每种水果的次数了,现在就需要找到前K种就可以了
	//vector+sort
	//这个vector里面存储的是结点的指针(但是我们不知道指针，但是知道迭代器)
	vector<CountMapIt> v;
	CountMapIt it = countMap.begin();
	while (it != countMap.end())
	{
		v.push_back(it);
		++it;
	}
	//此时在v这个vector里面也就存储了所有的结点的迭代器，此时我希望他们能够按照第二个参数进行比较
	//sort(v.begin(),v.end()),这样写时过不了的，因为还需要一个仿函数

	//排升序建大堆
	//排降序建小堆
	//这里需要找到最受喜欢的前K中水果，所以排成降序更加的好
	struct CountMapItCompare
	{
		bool operator()(const CountMapIt& it1, const CountMapIt& it2)
		{
			return it1->second > it2->second;
		}
	};

	sort(v.begin(), v.end(), CountMapItCompare());

	for (auto& e : v)
	{
		cout << e->first << ":" << e->second << endl;
		k--;
		if (k == 0)
			break;
	}
}

int main()
{
	//test_map();
	test_multiset();
	//test_multimap();

	//vector<string> v = { "西瓜", "西瓜", "西瓜", "西瓜", "香蕉", "香蕉", "香蕉", "榴莲", "榴莲", "榴莲", "榴莲", "榴莲", "榴莲", "苹果", "苹果", "苹果", "苹果", "苹果" };
	//GetFavoriteFruit(v, 3);
	return 0;
}
