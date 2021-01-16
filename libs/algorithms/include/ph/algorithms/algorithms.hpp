#pragma once
#include <ph/common/common.hpp>




template <class T>
vector<T> merge (vector<T> const& lhs, vector<T> const& rhs)
{
      
      int end = lhs.size() + rhs.size();
      vector<T> res (end);
      int l = 0;
      int r = 0;
//      cout << "-------" << endl;
//      cout << lhs << "\t" << rhs << endl;
      while (l + r < end)
      {
           
            if (l < lhs.size() and lhs[l] < rhs[r])
            {
                  res[l + r] = lhs[l];
                  ++l;
            } else
            {
                  res[l + r] = rhs[r];
                  ++r;
            }
      }
//      cout << res << endl;
//      cout << "---------" << endl;
      return res;
}

template <class T>
vector<T> merge_sort (vector<T> v)
{
      if (v.size() == 1)
      {
            return v;
      }
      else if (v.size() == 2)
      {
            if ( v[0] > v[1])
                  swap(v[0], v[1]);
            return v;
      }
//      else if (v.size() == 3) {
//            if(v[0] > v[1])
//                  swap(v[0], v[1]);
//            if (v[0] > v[2])
//                  swap(v[0], v[2]);
//            else if (v[1] > v[2])
//                  swap(v[1], v[2]);
//            return v;
//      }
      
      else
      {
            vector<T> lhs = merge_sort(vector<T>(v.begin(), v.begin() + v.size()/2));
            vector<T> rhs = merge_sort(vector<T>(v.begin() + v.size()/2, v.end()));
//            cout << lhs << endl;
//            cout << rhs << endl;
            return merge (lhs, rhs);
            
      }
}








int maxsum_N2 (vector<int> const& A){
      int max = -1 * INT_MAX;
      for (int i = 0; i < A.size(); ++i) {
            int myMax = 0;
            for (int j = i; j < A.size(); ++j) {
                  myMax += A[j];
                  if ( myMax >= max ) {
                        max = myMax;
                  }
            }
      }
      return max;
}



/**
 * Linear-time maximum contiguous subsequence sum algorithm. */
int maxsum_N( const vector<int> & a ){
      int maxSum = INT_MIN, thisSum = 0;
      
      for(int j=0;j<a.size();++j) {
            thisSum += a[ j ];
            if( thisSum > maxSum ) maxSum = thisSum;
            else if( thisSum < 0 ) thisSum = 0;
            //            cout << maxSum << endl;
      }
      //      cout << endl;
      return maxSum;
}


struct Max {
      int max = INT_MIN;
      int left = INT_MIN;
      int right = INT_MIN;
      int all = INT_MIN;
      friend ostream& operator<< (ostream& os, Max const& m) {
            os << "max: " << m.max << endl << "left: " << m.left << endl << "right: " << m.right << endl << "all: " << m.all;
            return os;
      }
};


int maxsum_logN (vector<int> const& A) {
      static function<Max(vector<int> const&)>
      
      f = [](vector<int> const& A)
      -> Max
      {
            if (A.size() == 1)
                  return {A[0], A[0], A[0], A[0]};
            
            
            auto [lhs, rhs] = split (A);
            Max const l = f(lhs);
            Max const r = f(rhs);
            
            
            Max max;
            
            if (l.max > r.max)
                  max.max = l.max;
            else
                  max.max = r.max;
            
            
            
            if (l.all + r.left > l.left)
                  max.left = l.all + r.left;
            
            else
                  max.left = l.left;
            
            if (max.left > max.max)
                  max.max = max.left;
            
            
            
            
            if (r.all + l.right > r.right)
                  max.right = r.all + l.right;
            else
                  max.right = r.right;
            
            if (max.right > max.max)
                  max.max = max.right;
            
            
            max.all = l.all + r.all;
            if (max.all > max.max)
                  max.max = max.all;
            
            if (l.right + r.left > max.max)
                  max.max = l.right + r.left;
            
            
            
            //            cout << "A " << A << endl << l << endl << endl << r << endl << endl << max << endl << "----------------" << endl;
            
            
            
            
            
            
            
            return max;
      };
      
      //      cout << A << endl << "----------------" << endl;
      Max max = f (A);
      //      cout << max << endl;
      return max.max;
      
      
}

