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
	dict.insert(make_pair("�ַ���", "string"));
	dict.insert(make_pair("����", "sort"));
	dict.insert(make_pair("��", "left"));
	//��Ȼ֧��[]��ʹ�ã����ﲻ���������в���
	//�����Kֵ��ͬ�������V��ֵ��ͬ
	dict["����"] = "finish";
	dict["����"] = "begin";//ֻ����Kֵ�����value�Ḳ��������Ǹ�valueֵ��finish��
	//�����Vֵ��ͬ�������K��ֵ��ͬ
	dict["���"] = "beautiful";
	dict["����"] = "beautiful";

	//�ӽ��Ҳ���Կ��������ǰ���Kֵ��ASCIIֵ���е���������ֻ����Kֵ�����ں�Value��ֵ

	for (auto& e : dict)
	{
		cout << e.first << ":" << e.second << endl;
	}


	string strs[] = { "sort", "insert", "sort", "sort", "insert", "erase" };
	map<string, int> CountMap;

	//[]ʵ�ֵ�ʹ�÷�����insert,insert�ķ���ֵ��pair<iterator,bool>

	//for (auto& s : strs)
	//{
	//	//����ɹ��򷵻��Ǹ��²������ָ�룬�ڶ�����������Ϊtrue
	//	//���ʧ�ܣ�˵���Ѿ����ڣ��Ǿͷ����Ǹ��Ѿ����ڽ���ָ�룬���ҵڶ�����������Ϊfalse
	//	pair<map<string, int>::iterator, bool> ret = CountMap.insert(make_pair(s, 1));
	//	//˵�����ֵ�Ѿ��洢����vector�У�����Ҫ�ڲ�����
	//	if (ret.second == false)
	//	{
	//		//ret��һ��pair��ret.first�õ�pair����ĵ�һ����������ȥsecond�õ�map�����int
	//		ret.first->second++;
	//	}

	//}


	//���ۣ�map[]����������
	//1.���K���ڣ�����pair(K,V())�����ҷ���value�����ã������޸ģ�
	//2.���K�ڣ������룬���ظ�K����Ǹ�����value������
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

	//����ӿ�����ͳ�ƴ���
	cout << ms.count(2) << endl;

	//����ж����ͬ��ֵ���ҵ�����������ĵ�һ��
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
	dict.insert(make_pair("string", "�ַ���"));
	dict.insert(make_pair("left", "���"));
	dict.insert(make_pair("left", "���"));
	dict.insert(make_pair("left", "���"));
	dict.insert(make_pair("right", "�ұ�"));
	dict.insert(pair<string, string>("beautiful", "����"));

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
	//����ͳ�Ƴ���ÿ��ˮ���Ĵ���
	map<string, int> countMap;
	for (auto& e : fruits)
	{
		countMap[e]++;
	}
	//����Ѿ�ͳ�Ƴ����ˣ�ÿ��ˮ���Ĵ�����,���ھ���Ҫ�ҵ�ǰK�־Ϳ�����
	//vector+sort
	//���vector����洢���ǽ���ָ��(�������ǲ�֪��ָ�룬����֪��������)
	vector<CountMapIt> v;
	CountMapIt it = countMap.begin();
	while (it != countMap.end())
	{
		v.push_back(it);
		++it;
	}
	//��ʱ��v���vector����Ҳ�ʹ洢�����еĽ��ĵ���������ʱ��ϣ�������ܹ����յڶ����������бȽ�
	//sort(v.begin(),v.end()),����дʱ�����˵ģ���Ϊ����Ҫһ���º���

	//�����򽨴��
	//�Ž���С��
	//������Ҫ�ҵ�����ϲ����ǰK��ˮ���������ųɽ�����ӵĺ�
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

	//vector<string> v = { "����", "����", "����", "����", "�㽶", "�㽶", "�㽶", "����", "����", "����", "����", "����", "����", "ƻ��", "ƻ��", "ƻ��", "ƻ��", "ƻ��" };
	//GetFavoriteFruit(v, 3);
	return 0;
}
