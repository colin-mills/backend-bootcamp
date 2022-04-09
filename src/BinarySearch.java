int[] newArr = new int[(sortedNums.length + 1)];
        int j = 0;

        for (int i = 0; i < newArr.length; i++) {

        if (i == index) {
        newArr[i] = value;
        } else {
        newArr[i] = sortedNums[j];
        j++;
        }
        }//place each value, shifting over when we are at our new index

        this.sortedNums = newArr;