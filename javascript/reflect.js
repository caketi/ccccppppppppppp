function Student(name, age){
    this.name = name
    this.age = age 
}
function Teacher(){

}

const teacher = Reflect.construct(Student, ["why","89"], Teacher)
console.log(teacher)
console.info(teacher.__proto__ == Teacher.prototype)