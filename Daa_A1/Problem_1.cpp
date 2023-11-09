#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int main()
{
	unsigned long long n,i,j;
	cout<<"enter rod length\n";
	cin>>n;
	if(n==0)
	cout<<n;
	else
	{
	vector<unsigned long long> dp(n+1);
	vector<int> gap(n);
	// dp[i] stores the maximum possible product of a rod of length i.
	// The answer is stored in dp[n].
	//gap[i] stores the interval gap after which a cut should be made 
	for(i=0;i<=n;i++)
	{
	dp[i]=i; 
	gap[i]=-1; 
    }
	for(i=2;i<=n;i++)
	{
		int ans=0;
		/*
		We update dp[] everytime we obtain a higher product.
		For a rod of length i,
		If the cut is made at j, i-j of the rod is remaining.
		The highest product of rod of length i-j is already calculated as a subproblem
		since it occured before i.
		Hence, the new product is j*dp[i-j]
		and the gap interval at which it is cut is j. 
		Top - down dp approach.
		*/
		for(j=1;j<i;j++)
		{
		  if(j*dp[i-j]>dp[i])
		  {
		  	gap[i]=j;
		  	dp[i]=j*dp[i-j];
		  }
		}
	}
	
	cout<<"The maximum product possible from a rod of length "<<n<<" is "<<dp[n]<<"\n";
	i=n;
    cout<<"We can obtain this product by cutting the rod at intervals:\n";
    for(i=n;gap[i]!=-1;i=i-gap[i])
    cout<<gap[i]<<" ";
    cout<<i;
    }
    return 0;
}
// Time Complexity: O( n^2 )
// Space Complexity: O(n)

/*
Sample Test Cases:

Test case 1:
enter rod length
4
The maximum product possible from a rod of length 4 is 4
We can obtain this product by cutting the rod at intervals:
4

********************************************************************

Test case 2:
enter rod length
6
The maximum product possible from a rod of length 6 is 9
We can obtain this product by cutting the rod at intervals:
3 3

********************************************************************

Test case 3:
enter rod length
8
The maximum product possible from a rod of length 8 is 18
We can obtain this product by cutting the rod at intervals:
2 3 3

********************************************************************

Test case 4:
enter rod length
15
The maximum product possible from a rod of length 15 is 243
We can obtain this product by cutting the rod at intervals:
3 3 3 3 3

*/
