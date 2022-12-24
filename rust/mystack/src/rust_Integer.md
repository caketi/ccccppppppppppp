rust has to know the size at compile time！！！！！！！

rust always chooses i32 for integers if you dont tell it to use different type

the trait `std::fmt::Display` is not implemented for `()`
() does not have the power of 'Display'
Trait = powers fro types

{:?} debug print
{:#?} pretty print
{:X} 16 进制
{:p} addr
`shadow` u dont distroy it u block it
A reference means u borrow the value, but u dont own it.

two main types of string :
String--more complicated has more functions. is a pointer,with data on the heap
&str--simple string

&str has & in front -- we dont own it -- stack needs to know the size so we give it a &, rust knows the size of the pointer
String -- an owned type--String::from() to_string() format! macro .into()

std::mem::sizeof::<String>()

for const and static rust will not use type inference!!!!!
const value does not change 
static value does not change and has a fixed memory

