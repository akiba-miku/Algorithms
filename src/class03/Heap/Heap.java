import java.io.BufferedReader;
import java.io.StreamTokenizer;
import java.io.PrintWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.IOException;

//link:https://www.luogu.com.cn/problem/P3378
//提交时修改主类名为Main， 否则会编译错误。
public class Heap{
  public static int MAXN = (int)1e6+10;
  public static int[] heap = new int[MAXN];
  public static int heapSize;
  public static void heapInsert(int i){
    while(heap[i]<heap[(i-1)/2]){
      swap(i, (i-1)/2);
      i = (i-1)/2;
    }
  }
  public static void heapify(int i){
    int l=i*2+1;
    while(l<heapSize){
      int best=l+1<heapSize&&heap[l+1]<heap[l]?l+1:l;
      best = heap[best]<heap[i]?best:i;
      if(best==i) return ;
      swap(best,i);
      i = best;
      l = i*2+1;
    }
  }
  public static void swap(int i,int j){
    int temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
  }
  public static void main(String[] args) throws IOException{
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StreamTokenizer in = new StreamTokenizer(br);
    PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    while(in.nextToken()!=StreamTokenizer.TT_EOF){
      int n = (int)in.nval;
      heapSize = 0; // 重置堆大小
      int op,x;
      for(int i=0;i<n;i++){
        in.nextToken(); op=(int)in.nval;
        if(op==1){
          in.nextToken(); x=(int)in.nval;
          heap[heapSize]=x;
          heapInsert(heapSize++);
        }else if(op==2){
          out.println(heap[0]);
        }else if(op==3){
          swap(0,--heapSize);
          heapify(0);
        }
      }
    }
    out.flush();
    br.close();
    out.close();
  }
}