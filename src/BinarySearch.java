public class BinarySearch<T extends Comparable<T>> {
    T[] sortedArr;

    public static void main(String[] args) {
        //code to test binary search method

        BinarySearch<Character> ob = new BinarySearch<>(new Character[]{'a', 'b', 'd', 'e', 'f', 'g'});
        System.out.println(ob.Search('a'));
        System.out.println(ob.Search('b'));
        System.out.println(ob.Search('c'));
        System.out.println(ob.Search('d'));
        System.out.println(ob.Search('e'));
        System.out.println(ob.Search('z'));
        System.out.println(ob.Search('A'));

    }

    public BinarySearch (T[] arr) {
        //Assumes that it will be passed a sorted array of type T
        this.sortedArr = arr;
    }

    public int Search(T val) {
        int l = 0, h = sortedArr.length -1, m =0;
        boolean found = false;

        while (!found && l <= h) {
            m = l + (h - l) / 2;

            if (sortedArr[m] == val) {
                found = true;
            } else if (val.compareTo(sortedArr[m]) < 0 ) {
                //Search bottom half
                h = m - 1;
            } else {
                //search top half
                l = m + 1;
            }
        }//While searching
        if (!found)
            m = -1;

        return m;
    }
}
