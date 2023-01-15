function createObject(o){
    function Fn() {}
    Fn.prototype = o
    return new Fn()
}

function inheritPrototype(SubType, SuperType){
    SubType.prototype = createObject(SuperType.prototype)
    Object.defineProperty(SubType.prototype, "constructor", {
        enumerable: false,
        configurable: true,
        writable: true,
        value: SubType
    })
}
function Person(name, age, friends){
    this.name = name
    this.age = age 
    this.friends = friends
}
Person.prototype.running = function (){
    console.info("running !")
}
Person.prototype.eating = function (){
    console.info("eating~ ")
}

function Student(name, age, friends, sno, score){
    Person.call(this, name, age, friends)
    this.sno = sno
    this.score = score
}
inheritPrototype(Student, Person)
// console.log(Student.prototype)
// Student.prototype = Object.create(Person.prototype)
// // Object.defineProperty(Student.prototype , "constructor", {
// //     enumerable:false,
// //     configurable: true,
// //     writable: true,
// //     value: Student
// // }) 
// Student.prototype.constructor = Student
// Student.prototype.studying = function (){
//     console.log("fdsts")
// }

var stu = new Student("w", 18, ["kbo"], 111,11111)
console.log(stu)

stu.running()
stu.eating()
console.log(stu.constructor.name)


// var personObj = { 
//     runnning: function (){
//         console.info("running")
//     }
// }
// function createStudent(name) {
//     var stu = Object.create(personObj)
//     stu.name = name 
//     stu.studying = function(){
//         console.info("studying!")
//     }
//     return stu
// }
// var stuObj = createStudent("w")



// // 寄生 继承
// function object(obj){
//     function Func(){}
//     Func.prototype = obj;
//     return new Func()
// }
// function createStudent(person){
//     var newObj = object(person)
//     newObj.studying = function(){
//         console.log(this.name + "studying")
//     }
//     return newObj
// }