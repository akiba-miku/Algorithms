
// //优化二分版本
// /**
//  * @link https://www.luogu.com.cn/problem/P2249
//  */
// #include<bits/stdc++.h>
// using namespace std;
// const int N = 1e6+1;
// int q[N],a[N],n,m;

// void binary_search(){
// 	int ans = 0,l,r,mid;
// 	for(i=0;i<m;i++){
// 		l=0,r=n-1;
// 		ans=-1;
// 		while(l<=r){
// 			mid=l+((r-l)>>1);
// 			if(q[mid]>=a[i]){
// 				ans = mid;
// 				r = mid - 1;
// 			}else l = mid + 1;
// 		}
// 		if (ans == -1 || q[ans] != a[i]) {  // 确保找到了与 a[i] 匹配的元素
//             a[i] = -1;
//         } else {
//             a[i] = ans;
//         }
// 	}
// 	for(int i=0;i<m;i++){
// 		cout<<a[i]<<' ';
// 	}
// 	cout<<'\n';
// }
// int main(){
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 	cin>>n>>m;
// 	int i;
// 	for(i=0;i<n;i++){
// 		cin>>q[i];
// 	}
// 	for(i=0;i<m;i++){
// 		cin>>a[i];
// 	}
// 	binary_search();
// 	return 0;
// }




#include<bits/stdc++.h>
using namespace std;
#define ll long long 
const int N = 2e5+10;
int q[N],n,l,r,m,c;
int cnt = 0;
void seqlist_search(){
	int i;
	cnt = 0;
	for(i=0;i<n;i++){
		ll tar = q[i] + c;
		for(int j=0;j<n;j++){
			if(i!=j&&q[j]==tar){
				++cnt;
			}
		}
	}
	printf("%d\n",cnt);
}
void binary_search(){
	int i=0;cnt=0;
	sort(q,q+n);
	for(i=0;i<n;i++){
		ll tar = q[i] + c;
		l = 0,r = n-1;
		int ans=-1;
		while(l<=r){
			m=l+((r-l)>>1);
			if(q[m]>=tar){
				ans = m;
				r = m - 1;
			}else l = m + 1;
		}
		if(ans!=-1&&q[ans]==tar){
			int a = ans;
			l=0,r=n-1;
			while(l<=r){
				m=l+((r-l)>>1);
				if(q[m]<=tar){
					ans = m;
					l = m + 1;
				}else r = m - 1;
			}
			cnt += ans-a+1;
		}
	}
	printf("%d\n",cnt);
}
int main(void){
	scanf("%d%d",&n,&c);
	for(int i=0;i<n;i++){
		scanf("%d",q+i);
	}
	seqlist_search();
	binary_search();
	return 0;
}

