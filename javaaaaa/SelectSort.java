public class SelectSort {
    public int[] selectSort(int[] array){
        // 
        if(array == null || array.length <= 1){
            return array;
        } 

        for(int i = 0;i<array.length-1;i++){
            int globalMin = i;
            for(int j = i+1;j <array.length; j++){
                if(array[j] < array[globalMin]){
                    globalMin = j;
                }
            }
            swap(array, i, globalMin);
        }
        return array;
    }
    private void swap(int[] array, int i, int j){
        int temp = array[j];
        array[j] = array[i];
        array[i] = temp;
    }
}
