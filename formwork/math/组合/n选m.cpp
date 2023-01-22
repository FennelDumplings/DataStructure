/*
n: 元素总量
picked: 已选元素的序号
toPick: 还需选择的元素数
*/

void pick(int n, vector<int> &picked, int toPick)
{
	//无可选元素时，输出已选元素
	if(toPick == 0)
	{
		printPicked(picked);
		return;
	}
	//计算可选的最小序号
	int smallest = picked.empty() ? 0 : picked.back() + 1;
	for(int next = smallest; next < n; ++next)
	{
		picked.push_back(next);
		pick(n, picked, toPick - 1);
		picked.pop_back();
	}
}