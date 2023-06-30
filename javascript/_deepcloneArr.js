function deepClone(arr){
    var result = []
    for(var i = 0; i < arr.length; i++){
        if(Array.isArray(arr[i])){
            result.push(deepClone(arr[i]))
        }else{
            result.push(arr[i]);
        }
    }
    return  result;
}
var arr1 = [1.3,2,4,5,[4,3]]

var arr2 = deepClone(arr1);
console.info("改变前arr1 arr2-- arr2是arr1的deepClone")
console.info(arr2);
console.info(arr1);
arr1.push(1);
arr2.push(2);
console.info("改变后arr1 arr2")
console.info(arr1);
console.info(arr2);