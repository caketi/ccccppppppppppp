rust has to know the size at compile time！！！！！！！

rust always chooses i32 for integers if you dont tell it to use different type

the trait `std::fmt::Display` is not implemented for `()`

`()` does not have the power of `'Display'`

Trait = powers for types
## print
 - {:?} debug print
- {:#?} pretty print
- {:X} 16 进制
- {:p} addr

`shadow` means u dont distroy it u block it
A reference means u borrow the value, but u dont own it.
## String and &str
two main types of string :
String--more complicated has more functions. is a pointer,with data on the heap
&str--simple string

``&str`` has ``&`` in front -- ``we dont own it`` -- ``stack needs to know the size so we give it a &``, rust knows the size of the pointer

``String`` -- ``an owned type``--String::from() to_string() format! macro .into()

``std::mem::sizeof::<String>()``

``for const and static rust will not use type inference!!!!!``

const value does not change 

static value does not change and has a fixed memory

push_str()

giving imutable reference to function --- not take the ownership!!!!! &String
1. takes a String and owns it. if it doesnt return anything, then the variable dies inside the function. -- variable: String
2. borrows a String and can look at it --variable: &String 
3. borrows a String and can change it --variable: &mut String

## Copy types 
``simple types are all on the stack and the compiler knows their size.``---easy to copy,so the compiler always ``copies`` when u send it to a function. ``so u dont need to worry about ownership for these types``.

--``integers, floats, booleans and char``

a char--trait implementations:
-----------------------------
- is copied when u send it to a function(Copyu)

- can use {} to print(Display)

- can use {:?} to print(Debug)

- string --- has clone()

``The Clone trait for types that cannot be ‘implicitly copied’.``

## Vec

with_capacity() 

_into()
