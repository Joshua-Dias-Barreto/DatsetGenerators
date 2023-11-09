#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,ans=0,i,j,sum=0;
	cout<<"enter the length of set S\n";
	cin>>n;
	vector<int> S(n),S1(n);
	//S stores the elements of set S.
	//S1 stores the indices of elements in subset S1.
	cout<<"enter set S\n";
	for(i=0;i<n;i++)
	{
		cin>>S[i];
		sum+=S[i];
	}
	/*
	Let S1 and S2 be the partitioned subsets of the set S.
	Let S1 have its sum smaller than s2.
	If the total sum of all elements in set S is S_sum, then
	sum of elements in S1 <=(S_sum/2) because
	S1_sum + S2_sum = S_sum and S1_sum < S2_sum
	We have to minimize | S2_sum - S1_sum | which is
	S_sum - 2*S1_sum, since S_sum is constant for a given S, we need to 
	maximize S1_sum.
	The range of S1_sum can be anywhere between [ 0 , S_sum/2 ]
	In this range we have to find the maximum value that can be achieved by S1_sum.
	If this maximum value is s1, then S2_sum = S_sum - s1 and the answer is:
	S_sum-2*s1.
	*/
	vector<vector<int>> dp(n+1,vector<int> (sum/2 + 1,0));
	/*
	dp[i][j] = 1 if the sum j can be formed using the first i elements of S
	and 0 otherwise.
	
	dp has n+1 rows and sum/2 +1 columns since there are n elements and maximum
	possible sum of S1 is sum/2. It is initialised with all zeros.
	*/
	
	for(i=0;i<=n;i++)
	dp[i][0]=1; // A sum of 0 can always be formed by not including any element {}
	for(i=1;i<=sum/2;i++)
	dp[0][i]=0; // Other than ), no other sum can be formed with zero elements.
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=sum/2;j++)
		{
			/*
			If j < S[i-1] the sum j can ne formed by the first i elements only if:
			A sum j could be obtained by the first i-1 elements (since all elements are positive).
			We just wouldn't include the ith element to obtain j.
			*/
			if(j<S[i-1])
			dp[i][j]=dp[i-1][j];
			else
			{
				/*
				sum j can be formed from the first i elements if :
				1) A sum of j- s[i-1] could be formed with the first i-1 elements
				so on adding the ith element (S[i]), j is obtained.
				         OR
			    2) The sum j could already be formed by the first i-1 elements,
			    We just wouldn't include the ith element to obtain j.
				*/
				dp[i][j]=dp[i-1][j-S[i-1]] || dp[i-1][j];
			}
		}
	}
	for(i=sum/2;i>=0;i--)
	{
		/*
		Finding the maximum possible sum of S1.
		*/
		if(dp[n][i]==1)
		break;
	}
	// The maximum possible sum of S1 is i.
	ans=sum-2*i;
	cout<<"The minimum absolute difference between the sum of elements in two partitions is: ";
	cout<<ans<<"\n";
	
	/*
	To print the subsets s1 and S2, We just have to move up the dp table starting at dp[n][max sum of S1],
	until we find a zero above a one, this indicates that the given sum is only possible when that
	element is included in S1, so we push its index to S1 (i-1 is that index).
	When we find this zero above a one, we have to move towrads the left j= j-S[i-1], and repeat the process.
	So that we can find the elements required to create a sum of j-S[i-1].
	The overall time complexity of printing subsets S1 and S2 is O( n + S ) where n is the number of elements
	and S is the total sum of all the elements in the set.
	*/
	
	j=i;
	i=n;
	while(i>=0&&j>=0)
	{
		if(i-1>=0&&dp[i-1][j]==1)
		i--;
		else
		{
			S1[i-1]=1;
			j=j-S[i-1];
			i--;
		}
	}
	cout<<"\nSubset S1 is : ( ";
	for(i=0;i<n;i++)
	{
		if(S1[i]==1)
		cout<<S[i]<<" ";
	}
	cout<<")\n";
	
	cout<<"Subset S2 is : ( ";
	for(i=0;i<n;i++)
	{
		if(S1[i]==0)
		cout<<S[i]<<" ";
	}
	cout<<")\n";
	
	return 0;
}
// Time Complexity: O( n * S ) where S is the sum of all elements in the set.
// Space Complexity: O( n * S )

/*
Sample Test Cases:

Test case 1:
enter the length of set S
5
enter set S
10 20 15 5 25
The minimum absolute difference between the sum of elements in two partitions is: 5

Subset S1 is : ( 20 15 )
Subset S2 is : ( 10 5 25 )

************************************************************************************

Test case 2:
enter the length of set S
7
enter set S
1 2 3 4 5 6 7
The minimum absolute difference between the sum of elements in two partitions is: 0

Subset S1 is : ( 2 3 4 5 )
Subset S2 is : ( 1 6 7 )

************************************************************************************

Test case 3:
enter the length of set S
4
enter set S
4 2 3 2
The minimum absolute difference between the sum of elements in two partitions is: 1

Subset S1 is : ( 2 3 )
Subset S2 is : ( 4 2 )
*/
