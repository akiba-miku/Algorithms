import java.io.OutputStreamWriter;
import java.io.StreamTokenizer;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.io.IOException;
import java.util.Arrays;

public class AVL {
  public static int MAXN = (int)1e6+10;
  public static int head, cnt;
  public static int[] key = new int[MAXN];
  public static int[] left = new int[MAXN];
  public static int[] right = new int[MAXN];
  public static int[] size = new int[MAXN];
  public static int[] count = new int[MAXN];
  public static int[] height = new int[MAXN];

  public static void init(){
    Arrays.fill(key,1,cnt+1,0);
    Arrays.fill(left,1,cnt+1,0);
    Arrays.fill(right,1,cnt+1,0);
    Arrays.fill(size,1,cnt+1,0);
    Arrays.fill(count,1,cnt+1,0);
    Arrays.fill(height,1,cnt+1,0);
    cnt = head = 0;
  }

  public static void up(int i){
    size[i] = size[left[i]]+size[right[i]]+count[i];
    height[i] = Math.max(height[left[i]], height[right[i]])+1;
  }
  public static int leftRotate(int i){
    int r = right[i];
    right[i] = left[r];
    left[r] = i;
    up(i);
    up(r);
    return r;
  }
  public static int rightRotate(int i){
    int l = left[i];
    left[i] = right[l];
    right[l] = i;
    up(i);
    up(l);
    return l;
  }
  public static int maintain(int i){
    int lh = height[left[i]];
    int rh = height[right[i]];
    if(lh-rh>1){
      if(height[left[left[i]]]>=height[right[left[i]]]){
        i = rightRotate(i);
      }else{
        left[i] = leftRotate(left[i]);
        i = rightRotate(i);
      }
    }else if(rh-lh>1){
      if(height[right[right[i]]]>=height[left[right[i]]]){
        i = leftRotate(i);
      }else{
        right[i] = rightRotate(right[i]);
        i = leftRotate(i);
      }
    }
    return i;
  }
  public static void add(int x){
    head = add(head, x);
  }
  public static int add(int i,int x){
    if(i==0){
      ++cnt;
      key[cnt]=x;
      size[cnt]=count[cnt]=height[cnt]=1;
      return cnt;
    }
    if(key[i]==x){
      count[i]++;
    }else if(key[i]>x){
      left[i] = add(left[i], x);
    }else{
      right[i] = add(right[i], x);
    }
    up(i);
    return maintain(i);
  }

  public static void remove(int x){
    if(rank(x)!=rank(x+1)){
      head = remove(head, x);
    }
  }
  public static int remove(int i,int x){
    if(key[i]>x){
      left[i] = remove(left[i], x);
    }else if(key[i]<x){
      right[i] = remove(right[i], x);
    }else{
      if(count[i]>1){
        count[i]--;
      }else if(left[i]==0&&right[i]==0){
        return 0;
      }else if(left[i]!=0&&right[i]==0){
        i = left[i];
      }else if(left[i]==0&&right[i]!=0){
        i = right[i];
      }else{
        int mostLeft = right[i];
        while(left[mostLeft]!=0){
          mostLeft = left[mostLeft];
        }
        right[i] = removeMostLeft(right[i], mostLeft);
        left[mostLeft] = left[i];
        right[mostLeft] = right[i];
        i = mostLeft;
      }
    }
    up(i);
    return maintain(i); 
  }

  public static int removeMostLeft(int i,int mostLeft){
    if(i==mostLeft){
      return right[mostLeft];
    }else{
      left[i] = removeMostLeft(left[i], mostLeft);
      up(i);
      return maintain(i);
    }
  }

  public static int small(int i,int x){
    if(i==0){
      return 0;
    }
    if(key[i]>=x){
      return small(left[i], x);
    }else{
      return size[left[i]]+count[i]+small(right[i],x);
    }
  }
  public static int rank(int x){
    return small(head,x)+1;
  }

  public static int index(int x){
    return index(head, x);
  }
  public static int index(int i,int x){
    if(size[left[i]]>=x){
      return index(left[i],x);
    }else if(size[left[i]]+count[i]<x){
      return index(right[i],x-size[left[i]]-count[i]);
    }
    return key[i];
  }


  public static int pre(int x){
    return pre(head, x);
  }
  public static int pre(int i,int x){
    if(i==0){
      return Integer.MIN_VALUE;
    }
    if(key[i]>=x){
      return pre(left[i], x);
    }else{
      return Math.max(key[i], pre(right[i],x));
    }
  }
  public static int post(int x){
    return post(head, x);
  }

  public static int post(int i,int x){
    if(i==0){
      return Integer.MAX_VALUE;
    }
    if(key[i]<=x){
      return post(right[i], x);
    }else{
      return Math.min(key[i], post(left[i], x));
    }
  }

  public static void main(String[] args) throws IOException{
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StreamTokenizer in = new StreamTokenizer(br);
    PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    init();
    while(in.nextToken()!=StreamTokenizer.TT_EOF){
      int n = (int)in.nval;
      for(int i=1,op,x;i<=n;i++){
        in.nextToken();
        op = (int)in.nval;
        in.nextToken();
        x = (int)in.nval;
        switch(op){
          case 1:
            add(x);
            break;
          case 2:
            remove(x);
            break;
          case 3:
            out.println(rank(x));
            break;
          case 4:
            out.println(index(x));
            break;
          case 5:
            out.println(pre(x));
            break;
          case 6:
            out.println(post(x));
            break; 
        }
      }
    } 
    out.flush();
    out.close();
    br.close();
  }
}
