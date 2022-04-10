import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Collection;

public class MergeSort<T extends Comparable<T>> {

    T[] arr;

    public static void main(String[] args) {

        Integer[] Array = new Integer[] {1,3,4,5,43,34,1,1};

        new MergeSort<>(Array);

        for ( int num : Array) {

            System.out.println(num);
        }


    }

    public MergeSort (T[] array) {
               this.arr = array;
               Sort(this.arr, 0, arr.length-1);
    }


    public void Sort(T arr[], int l, int r) {

        if (l < r) {

            int m = l + (r-l)/2; //This will make the right side the bigger half

            //sort each half recursively
            Sort (arr, l, m);
            Sort (arr, m+1, r);

            //merge the sorted halves
            Merge (arr, l, m, r);

        }//If not size < 2

    }//End Sort

    public void Merge(T arr[], int l, int m, int r) {
        //Get the sizes of the sub arrays
        int size1 = m - l + 1;
        int size2 = r - m;

        //System.out.println("Int the Merge class");
        //Temp arrays of said sizes
        ArrayList<T> lower = new ArrayList(size1);
        ArrayList<T> upper = new ArrayList(size2);
        //T lower[] = (T[]) new Object[size1];
        //T upper[] = (T[]) new Object[size2];


        //Copy contents
        for (int i = 0; i < size1; i ++) {
            lower.add(i, arr[l + i]);
        }
        for (int i = 0; i < size2; i ++) {
            upper.add(i, arr[m + 1 + i]); //middle + 1 is starting point for upper
        }

        //indexes
        int i = 0, j = 0, k = l; // i is left sub array, j is right, k is merged array

        while (i < size1 && j < size2) {
            if ((lower.get(i)).compareTo(upper.get(j)) <= 0) {
                arr[k] = lower.get(i);
                i++;
            } else {
                arr[k] = upper.get(j);
                j++;
            }
            k++;
        }

        //Copy any remaining elements b/c loop ends when shorter arr hits limit
        //we can append to the end because the sub array should be sort so the last one is largest
        while (i < size1) {
            arr[k] = lower.get(i);
            i++;
            k++;
        }

        while (j < size2) {
            arr[k] = upper.get(j);
            j++;
            k++;
        }


    }//End Merge
}
