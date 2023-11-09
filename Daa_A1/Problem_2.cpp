#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,i,j;
	cout<<"enter the length of the sequence\n";
	cin>>n;
	vector<int> a(n);
	cout<<"enter the sequence\n";
	for(i=0;i<n;i++)
	cin>>a[i];
	/*dp_sum[i] stores the maximum possible sum of a subsequence 
	which is sorted in ascending order upto the ith poisition*/
	// prev[i] stores the element which appears before the ith element in the required subsequence
	vector<int> dp_sum(n);
	vector<int> prev(n);
	for(i=0;i<n;i++)
	{
	dp_sum[i]=a[i];
	prev[i]=-1;
    }
	int ans=dp_sum[0];
	int maxi=0;
	for(i=1;i<n;i++)
	{
		/*
		We update dp_sum[] everytime we get a subsequence in increasing order with a hihger sum
		Upto the ith element,
		If there exists an element at index j (j < i) such that:
		1) a[i] >= a[j] (increasing order)
		2) dp_sum[j] + a[i] > dp_sum[i] (maximum sum)
		Then we update dp_sum[i] since dp_sum[j] was already claculated as a subproblem
		since j appeared before i.
		Top - down dp approach.
		*/
		for(j=0;j<i;j++)
		{
			if(a[i]>=a[j])// not a[i] > a[j] as the problem doesn't mention strictly increasing order.
			{
		    if(dp_sum[j]+a[i]>dp_sum[i])
		    {
             dp_sum[i]=dp_sum[j]+a[i];
		    prev[i]=j;
		    }
		    }
		}
        if(dp_sum[i]>ans)
        {
        	maxi=i;
        	ans=dp_sum[i];
		}
	}
	cout<<"The maximum sum of a subsequence in increasing order is:\n";
	cout<<ans<<"\n";
	i=maxi;
	/*
	The subsequence is currently in reverse order,
	to get the correct order, we just push every element in a stack 
	and keep printing the top most element of the stack after popping it.
	*/
	stack<int> s;
	while(i!=-1)
	{
		s.push(a[i]);
		i=prev[i];
	}
	cout<<"The maximum sum can be made from this subsequence:\n";
	while(!s.empty())
	{
		cout<<s.top()<<" ";
		s.pop();
	}
	return 0;
}
// Time Complexity: O( n^2 )
// Space Complexity: O(n)

/*
Sample Test Cases:

Test case 1:
enter the length of the sequence
14
enter the sequence
0 8 4 12 2 10 6 14 1 9 5 13 3 11
The maximum sum of a subsequence in increasing order is:
34
The maximum sum can be made from this subsequence:
8 12 14

***************************************************************

Test case 2:
enter the length of the sequence
12
enter the sequence
-5 4 2 -3 5 3 4 5 4 -8 3 4
The maximum sum of a subsequence in increasing order is:
17
The maximum sum can be made from this subsequence:
2 3 4 4 4
*/
