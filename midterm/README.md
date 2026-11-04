# Midterm Concept and Debugging Assessment - Study Guide

**Duration:** 45 minutes | **Total Marks:** 30

## Assessment Format

### Concept Questions (Multiple Choice, Fill in the Blanks, True/False, Reordering and Matching)

### Debugging Questions (Fill-in-the-blank)

- Programs that produce output (exact character sequence, no newlines)
- Programs that fail to compile → Answer: "Fails to Compile"

---

## Chapter 1: Introduction

### Object-Oriented Paradigm

**Three Core Concepts:**

1. **Encapsulation** - Couples object data to class logic
   - _Weak encapsulation_: couples state and logic without privacy
   - _Strong encapsulation_: couples state and logic with restricted access to state

2. **Inheritance** - Relationship where one class inherits another's entire structure
   - Base class defines structure inherited by derived classes
   - Derived classes add features (instance variables and logic)

3. **Polymorphism** - Supports multiple behaviors for an identifier in an inheritance hierarchy
   - Multiple behaviors associated with same identifier
   - Distinguished through object's dynamic type
   - Behavior may change as dynamic type changes throughout lifetime

### Modularity

- Modules define classes and implementations, stored in files/file sets
- Each module compiles separately
- Updates only require recompilation of changed module and directly affected modules

### Building Blocks

- Values, Objects, Variables, References, Functions, Types, Class members, Templates, Namespaces

**Key Definitions:**

- **Object**: occupies memory region, holds value, may have name
- **Variable**: named object with memory region, value, and name
- **Value**: contents of memory region defining object's current state

### Types

Type relates object to underlying implementation and identifies permissible operations.

**Type Categories:**

- **Fundamental types**: correspond directly to hardware facilities
- **Built-in types**: reflect hardware capabilities directly and efficiently
- **User-defined types**:
  - **Concrete types**: representation known (part of definition)
  - **Abstract types**: representation unknown (not part of definition)

### Declarations and Scope

Introduce names and associate them with types. Name visibility defines its **scope**.

**Scope Types:**

- **Local scope**: declared within function/code block
- **Class scope**: declared as class member
- **Namespace scope**: declared as member of named block
- **Global scope**: not declared in above scopes

**Linkage Types:**

- **External**: connected across different scopes in different modules
- **Internal**: connected across scopes within same module
- **Non-existent**: not connected outside its own scope

### Compilers

Translate module source code into binary code for executable assembly.

**Type System:**

- Provides consistency across building blocks
- Identifies admissible operations
- Enables compiler to check well-formed relations
- Breaking type system exposes bit strings, creating undefined behavior

**Compile-time vs Run-time:**

- **Statically allocated**: determined at compile-time without link/run-time info
- **Dynamically allocated**: determined during execution

### Memory Distinctions

When OS loads executable:

- **Code segment**: program instructions
- **Data segments**: data surviving program lifetime
- **Stack segment**: statically allocated local data
- **Heap segment**: dynamically allocated local data

**Statically allocated**: size known at compile-time, allocated on stack/data segment, fast, auto-deallocates, fixed size
**Dynamically allocated**: variable size, allocated at run-time on heap, managed by freestore manager, must be returned before reuse

---

## Chapter 2: C++ Building Blocks

### Key Terms

- **Entity**: Values, variables, objects, references, functions, types, class members, templates, namespaces
- **Translation Unit**: Module accepted by C++ compiler as independent unit, converted into binary code
- **Declaration**: Introduces a name into a translation unit
- **Definition**: Declaration that associates a meaning with a name
- **One Definition Rule**: A definition may not appear more than once across all translation units
- **Scope**: Region of the program throughout which the name is valid
- **Linkage**: Mechanism linking entity across different scopes and modules
- **cv-qualifiers**: Storage properties identifying mutability and side-effects
  - `none`: modifiable, no side-effects
  - `const`: unmodifiable, no side-effects
  - `volatile`: modifiable, subject to side-effects
  - `const volatile`: unmodifiable, subject to side-effects
- **Storage Duration**: Lifetime within program
  - Automatic: declaration to end of scope
  - Static: entire program lifetime
  - Dynamic: created with `new`, lasts until `delete`
  - Thread: lifetime of thread

### Scope Types

**Block Scope:**

- Set of program instructions enclosed within curly braces
- Name's scope: from declaration to end of block
- C++17: initializer expressions in selection constructs extend scope to end of construct

**Class Scope:**

- Scope of a name declared in a class definition
- Extends from memory allocation during construction to deallocation during destruction

**Global Scope:**

- Entire region of a program
- Namespaces localize otherwise global names

**Shadowing:**

- Name declared within scope of identical name shadows entity with broader scope
- Access shadowed instance variable: `this->name`
- Access shadowed global variable: `::name`

### Linkage Types

**External Linkage:**

- Keyword: `extern`
- Refers to entity declared in different scope within another translation unit
- Declaration: `extern int share_me;`
- Definition: `int share_me = 0;`
- Same address across modules proves same entity

**Internal Linkage:**

- Keyword: `static`
- Invisible outside own translation unit
- Separate memory allocation per translation unit

### Namespaces

**Declaration Syntax:**

```cpp
namespace identifier {
    // declarations
}
```

- Optional identifier (anonymous namespaces)
- Not a type - cannot create instances
- No semicolon after closing brace
- Expand by re-declaring

**Visibility Rules:**

- Names invisible outside namespace
- Access with scope resolution: `namespace::identifier`
- `using` declaration: `using namespace::identifier;`
- `using` directive: `using namespace nameOfTheNamespace;`

**Anonymous Namespaces:**

- Isolate names within translation unit
- Only visible inside own translation unit
- Definitions can differ across translation units

**Design Practices:**

- Header files: qualify all names with namespace identifiers, avoid `using`
- Implementation files: restrict `using` to after `#include` directives

### Variables and Objects

**Variable**: Occupies a region of memory, holds a value and has a name
**Object**: Occupies a region of memory, holds a value and may have a name

```cpp
A* a;        // variable with name a (pointer to object)
A  b;        // object with name b (created on stack) - a variable
a = new A(); // object without name (created on heap) - not a variable
```

**Subobject**: Object may be a subobject of another object (e.g., base object is subobject of derived object)
**Complete Object**: Object that is not part of any other object

### Storage Duration Examples

**Static Duration:**

```cpp
void display() {
    static int n = 1;
    std::cout << "n is " << n++ << std::endl;
}
```

Output: `n is 1` then `n is 2` - second call doesn't re-initialize

### Type Definitions

**typedef Syntax:**

```cpp
typedef compoundType Synonym;
```

Example:

```cpp
typedef const int constInt;
constInt myConstant; // myConstant is a const int
```

Rules: All type specifiers must be included in the type definition. Cannot insert new specifiers when invoking the synonym type. A `typedef` cannot include a linkage specifier.

---

## Chapter 3: Compilation and Execution

### Compilation Process

1. **Pre-Processing Stage**: Creates translation units from source files
   - Inserts header files (`*.h`) into implementation files (`*.cpp`)
   - Replaces/expands macros (lines starting with `#`)

2. **Compilation Stage**: Creates separate binary files from each translation unit

3. **Linking Stage**: Creates a single relocatable file from all binary files and referenced libraries

After initial build, only changed translation units need recompilation.

The loader copies the relocatable file into RAM, arranges storage locations, and transfers control to `main()`.

### Platforms and Compilers

**Microsoft Visual Studio (`cl`):**

- `/c` - compile only (creates `.obj`)
- `/E` - pre-process to stdout
- `/P` - pre-process to `*.i` file
- `/Wall` - enable all warnings
- Disable warning C4996: `#define _CRT_SECURE_NO_WARNINGS`

**Linux (`gcc`/`g++`):**

- Access GCC 9.1.0: `export LD_LIBRARY_PATH=/usr/local/gcc/9.1.0/lib64:$LD_LIBRARY_PATH`
- `-c` - pre-process and compile (creates `.o`)
- `-E` - pre-process to stdout
- `-g` - produce debug info for `gdb`

### Interface with Operating System

**main() Function Prototypes:**

```cpp
int main();                       // no command-line arguments
int main(int argc, char *argv[]); // with command-line arguments
```

**Command-Line Arguments:**

- `argc`: number of arguments (includes program name)
- `argv`: array of pointers to C-style null-terminated strings
- `argv[0]`: program name (may include absolute path)
- `argv[i]`: i-th command-line argument

**Returning Control:**

- `main()` returns `int` to OS
- Missing `return` statement defaults to `0`

### Compile-time Evaluations

**Constant Expressions (`constexpr`):**

```cpp
constexpr int N = 8;
constexpr int factorial(int i) {
    return i > 1 ? i * factorial(i - 1) : 1;
}
```

**Static Assertions (`static_assert`):**

```cpp
static_assert(bool condition, const char* message);
```

---

## Chapter 4: Fundamental Types

### Integer Types

**Standard Signed Integers (C++17):**

- `signed char`: Typically 1 byte, stores basic character set + EOF (-1)
- `short int`: At least 16 bits
- `int`: At least 32 bits
- `long int`: At least 32 bits
- `long long int`: At least 64 bits

**Constant Syntax:**

- `int`: `91`, `0133` (octal), `0x5b` (hex)
- `long int`: `91L`, `0133L`, `0x5bL`
- `long long int`: `91LL`, `0133LL`, `0x5bLL`
- `signed char`: `'['`, `'\133'` (octal), `'\x5b'` (hex)

**Unsigned Standard Integers:**

- `unsigned char`, `unsigned short int`, `unsigned int`, `unsigned long int`, `unsigned long long int`
- Suffix `U` or `u` (can combine with `L`/`LL`)

**Ranges (Two's Complement Typical):**
| Type | Min | Max |
|------|-----|-----|
| `signed char` | -128 | 127 |
| `short int` | ≤-32,768 | ≥32,767 |
| `int` | -2,147,483,648 | 2,147,483,647 |
| `long long int` | ≤-9.22×10¹⁸ | ≥9.22×10¹⁸ |
| `unsigned char` | 0 | 255 |
| `unsigned int` | 0 | 4,294,967,295 |

**Boolean Type:**

- `bool`: Typically 1 byte, values `true`/`false`

**Character Types (C++17):**

1. `char` - UTF-8, basic execution character set
2. `signed char` - Same size as `char`
3. `unsigned char` - Same size as `char`
4. `wchar_t` - Wide character, locale-dependent size
5. `char16_t` - UTF-16
6. `char32_t` - UTF-32 (fixed 32-bit)

**Literal prefixes:**

- `wchar_t`: `L'['`, `L'\133'`, `L'\x5b'`
- `char16_t`: `u'['`, `u'\133'`, `u'\x5b'`
- `char32_t`: `U'['`, `U'\133'`, `U'\x5b'`

### Floating-Point Types

- `float`: Typically 4 bytes, IEEE 754 single-precision (6 significant digits)
- `double`: Typically 8 bytes, IEEE 754 double-precision (15 significant digits)
- `long double`: At least 8 bytes, maximum precision

### Void Type

- `void`: Incomplete type, cannot create objects
- Used for functions returning no value and generic pointers

### Initialization Forms

```cpp
int n0 = 7;      // C-style copy initialization
int n1 = 7.2;    // C-style narrowing (loses information)
int n2 {6};      // Direct-list initialization (universal, type-safe)
int n3 = {5};    // Copy-list initialization (universal, type-safe)
```

**Universal form (braces) recommended** - prevents narrowing conversions.

### Type Inference

- `auto` keyword infers type from initializer:

```cpp
const auto n = 6;    // infers int
for (auto i = 0; i < n; i++)  // infers int
```

- Cannot use `auto` for array top-level declaration: `auto a[] {1,2,3};` // ERROR

### Type Alignment

- `alignof(T)`: Returns alignment requirement in bytes
- `alignas(N)`: Specifies alignment requirement (must be power of 2)

---

## Chapter 5: Pointers, References, and Arrays

### Built-in Types Overview

Built-in types are constructed from fundamental types using qualifiers (`const`) and declarator operators (`[]`, `*`, `&`). The three built-in types are **pointers**, **references**, and **arrays**.

### Pointer Types

A pointer type holds a memory address. Each type has an associated pointer type (e.g., `int*`, `double*`, `char*`).

**Null Address Constant:**

- `nullptr`: Keyword representing a constant null address
- Convention: the null address cannot be dereferenced
- Good Design: Initialize every wild pointer to `nullptr`

**Synonym Pointer Types:**

```cpp
typedef unsigned long long int* ullint_ptr;
ullint_ptr p, q; // No * needed before each identifier
```

**Generic Pointer Type (`void*`):**

- Holds an address without type information
- Converting to/from `void*` preserves the address
- Requires explicit `static_cast` for conversion between different pointer types
- Dereferencing: Not allowed directly. Must cast to the correct type first.

### References

A reference is an **alias** for an existing object. C++17 supports two kinds:

1. **lvalue reference** (`&`)
2. **rvalue reference** (`&&`)

**Restrictions:** No references to references, no arrays of references, no pointers to references.

**lvalue References:**

- Requires an initializer **unless**:
  - It has external linkage (`extern`)
  - It is a class member declaration
  - It is a function parameter or return type

**rvalue References:**

- Identifies an object "near the end of its lifetime," a temporary, or a value not associated with an object
- Enables **move semantics** (move constructors/assignment)

**Standard Library Helpers (`<utility>`):**

- `std::ref()`: Returns an lvalue reference
- `std::move()`: Returns an rvalue reference (casts to `&&`)

### Array Types

A built-in type with contiguous elements of identical type. Constructed from fundamental types (except `void`), pointers, classes, or enumerations. **Cannot** be constructed from reference types.

**One-Dimensional Array Declaration:**

- Stack: `Type identifier[c];` (`c` = constant expression)
- Heap: `Type* identifier = new Type[n];` (`n` = variable or constant)

**Aggregate Initialization:**

```cpp
Type identifier[c] = { list };
Type identifier[c] { list };
Type identifier[] = { list };     // Size deduced
Type identifier[] { list };
Type* p = new Type[n] { list };
Type* p = new Type[n] {};         // Value-initialization (zeros)
```

Rules:

- If `c` > list size, remaining elements initialized to `0`
- Empty braces `{}` or `={}` initialize all elements to `0`

**Range-Based `for`:**

```cpp
int a[]{1, 2, 3, 4, 5, 6};
for (int& e : a) std::cout << e << ' '; // Output: 1 2 3 4 5 6
for (auto& e : a) std::cout << e << ' '; // Type inference
```

---

## Chapter 6: Classes and Scoped Enumerations

### Class Keys

- `class`: Strongly encapsulated, members **private by default**
- `struct`: Weakly encapsulated, members **public by default**
- `union`: Weakly encapsulated, members **public by default**, share same memory address

### Class Definition Syntax

```
class-key Identifier{
    sub-object declarations
    member function declarations};
```

### Data Member Initialization

**Three Methods:**

1. **Default Member Initializers** (in declaration):
   - `int item = ++nItems;` (braces-enclosed or equals initializer)
   - `const std::string name {"empty"};` (braces-enclosed list)

2. **Member List Initializers** (in constructor):

   ```
   Class-name(type x, ...) : data-member-name{x},...{
       // any logic
   }
   ```

3. **Constructor Body** (not for unmodifiable members)

### Copying and Move Operations

**Copy Constructor & Assignment:**

- **Copy Constructor**: `Array(const Array& src) { *this = src; }`
- **Copy Assignment**: Deep copy with self-assignment check, cleanup, shallow copy of scalars, deep copy of resources

**Move Constructor & Assignment:**

- **Move Constructor**: `Array(Array&& src) { *this = std::move(src); }`
- **Move Assignment**: Transfers ownership by copying addresses and nullifying source

### Class Members

**Class Variables (static data members):**

- **Lifetime**: Program duration
- **Shared**: All instances share single copy
- **Access**: Through class name (`Horse::noHorses`) or object name
- **Definition**: Must be defined in implementation file: `unsigned Horse::noHorses = 0;`

**Class Functions (static member functions):**

- **Access**: Only class variables (static data members)
- **Cannot access**: Instance variables
- **Call**: `Horse::howMany()` or `object.howMany()`

### Structs and Unions

**Struct:**

- Members arranged **sequentially** (not necessarily contiguously)
- Padding/alignment gaps possible

**Union:**

- Members arranged **in parallel** (same memory address)
- Only one member holds valid value at a time
- **Tracking pattern**: Wrap in struct with enum discriminator

### Enumerations

**Plain Enumerations:**

```cpp
enum Colour { white, red, green, blue };
// Usage: wall = red;  // unscoped access
```

**Scoped Enumerations (enum class):**

```cpp
enum class Colour { white, red, green, blue };
// Usage: wall = Colour::red;  // scoped access required
```

- **Benefits**: Prevents name collisions, stronger type safety

**Underlying Types:**

- Default: `int`
- Custom values allowed: `enum class Colour { white = 0x01, red = 0x02 };`
- Values must be unique within enumeration

---

## Chapter 7: Inheritance and Inclusion Polymorphism

### Abstract and Concrete Classes

- **Abstract class**: Incomplete class serving as interface; cannot be instantiated; contains pure virtual functions (`= 0`)
- **Concrete class**: Complete implementation derived from abstract class; can be instantiated

```cpp
class Shape {
public:
    virtual double volume() const = 0;  // pure virtual function
};
```

### Pre-processor Guards

Prevents multiple definitions in translation units:

```cpp
#ifndef SHAPE_H
#define SHAPE_H
// class definition
#endif
```

### Inclusion Polymorphism

Objects with different dynamic types throughout lifetime. Dynamic type determined at runtime via virtual functions.

**Cloning Pattern:**

```cpp
class Shape {
public:
    virtual double volume() const = 0;
    virtual Shape* clone() const = 0;
};
```

**Dynamic Cast (Optional):**

```cpp
const Cube* c = dynamic_cast<const Cube*>(&s);
```

**RTTI (Optional):**

```cpp
#include <typeinfo>
if (typeid(*a) != typeid(cref)) { /* ... */ }
```

### Liskov Substitution Principle (LSP)

> "A function that uses pointers or references to base classes must be able to use objects of derived classes without knowing it."

**Correct Design**: Rectangle from Square (Square is more abstract)
**Incorrect Design**: Square from Rectangle (violates LSP)

---

## Chapter 8: Class Templates

### Template Syntax

```cpp
template <params> return-type function-name(...) { ... }
template <params> class-key Class-name { ... };
template <params> type variable_name;
```

### Template Parameters

1. **Type template parameter**: `typename identifier[=default]` or `class identifier[=default]`
2. **Non-type template parameter**: `type identifier[=default]` - integral/enum type, pointer, lvalue reference, pointer to member, `std::nullptr_t`, or `auto`
3. **Template template parameter**: `template<parameter-list> typename identifier[=default]`

### Function Templates

```cpp
template <typename T>
void swap(T& a, T& b) { T c; c = a; a = b; b = c; }
```

**Specialization:**

```cpp
template <> const char* maximum<const char*>(const char* a, const char* b) {
    return std::strcmp(a, b) > 0 ? a : b;
}
```

### Class Templates

```cpp
template <typename T, int SIZE = 50>
class Array { T a[SIZE]; /* ... */ };
```

**Static Data Members:**

```cpp
template <typename T, int SIZE>
unsigned Array<T, SIZE>::m_count = 0u;
```

### Templates and Inheritance

```cpp
template<typename S, typename T>
class Derived : public Base<T> { /* ... */ };
```

### Variadic Templates

```cpp
template<typename... Args>
void func(Args... args);
```

---

## Chapter 9: Compositions, Aggregations and Associations

### Composition

- Strong **"has-a"** relationship
- Composer _owns_ component; controls its lifetime
- Component cannot exist without composer
- Implementation: Via subobject (preferred) or owning raw pointer

### Aggregation

- Weaker **"has-a"** relationship
- Aggregator _uses_ object but does _not_ manage creation/destruction
- Objects survive aggregator destruction
- Implementation: Array/container of **non-owning pointers**

### Association

- Weakest relationship
- **"Uses-a"** service relationship
- No ownership; both classes independent
- Implementation: Non-owning pointers with bidirectional linking

---

## Chapter 10: Expressions

### Value Categories

- **prvalue** (pure rvalue): a value that does not occupy a location in storage
- **xvalue** (expiring value): an expiring value that does occupy a location in storage
- **lvalue** (locator value): a locator value that occupies a location in storage

**Key relationships:**

- lvalues + xvalues = **glvalues** (generalized lvalues)
- prvalues + xvalues = **rvalues**
- Temporary materialization conversion: prvalue → xvalue

### Operator Precedence (Highest to Lowest)

| Level | Class        | Operators                                                           | Associativity |
| ----- | ------------ | ------------------------------------------------------------------- | ------------- |
| 18    | primary      | name, literal                                                       | -             |
| 17    | postfix      | `[]`, `()`, `.`, `->`, `++`, `--`                                   | left-to-right |
| 16    | prefix/unary | `++`, `--`, `sizeof`, `!`, `~`, `-`, `+`, `&`, `*`, `new`, `delete` | right-to-left |
| 14    | binary       | `*`, `/`, `%`                                                       | left-to-right |
| 13    | binary       | `+`, `-`                                                            | left-to-right |
| 12    | binary       | `<<`, `>>`                                                          | left-to-right |
| 11    | binary       | `<`, `>`, `<=`, `>=`                                                | left-to-right |
| 10    | binary       | `==`, `!=`                                                          | left-to-right |
| 9     | binary       | `&` (bitwise)                                                       | left-to-right |
| 8     | binary       | `^`                                                                 | left-to-right |
| 7     | binary       | `\|`                                                                | left-to-right |
| 6     | binary       | `&&`                                                                | left-to-right |
| 5     | binary       | `\|\|`                                                              | left-to-right |
| 4     | ternary      | `?:`                                                                | right-to-left |
| 3     | binary       | `=`, `+=`, `-=`, `*=`, `/=`, `%=`                                   | right-to-left |
| 1     | binary       | `,`                                                                 | left-to-right |

### Postfix Expressions

**Subscripting Operator `[]`:**

- Left operand: pointer of type `T`
- Right operand: integral type value
- Result: **modifiable lvalue** of type `T` at offset

**Member Selection:**

- Direct (`.`): object.member
- Indirect (`->`): pointer->member

**Postfix Increment/Decrement:**

- Operand: integral, floating-point, or pointer type (must be modifiable lvalue)
- Changes value **after** accessing it
- Expression result: **prvalue** (not lvalue)

**Constrained Cast Operators:**

- `static_cast<T>(v)` - standard implicit conversions and their opposites
- `reinterpret_cast<T>(v)` - pointer ↔ integral, function pointer ↔ object pointer
- `const_cast<T>(v)` - cast away const-ness
- `dynamic_cast<T>(v)` - runtime type check (optional)

### Prefix Expressions

**Prefix Increment/Decrement:**

- Changes lvalue **before** accessing value
- Result: **lvalue** (unlike postfix)

### Unary Expressions

**`sizeof` / `sizeof()`:**

- `sizeof(type)` - evaluates **type** size in bytes
- `sizeof expression` - evaluates **variable/object/expression** size
- Result: constant of type `size_t` (unsigned integral)
- Evaluated at **compile time**
- Does **not** evaluate operand expression: `sizeof j++` leaves j unchanged

**Logical Negation `!`:**

- Converts operand to `bool`, returns converse
- `0`, `0.0`, `nullptr` → `true`
- Any other value → `false`

**Address-of `&`:**

- Returns pointer to operand (address value)
- Operand: **lvalue not of storage class `register`**
- Result: **prvalue**

**Indirection `*`:**

- Returns value stored at address in operand
- Result: **lvalue**
- Inverse of address-of: `*&x` is `x`

**`decltype(expression)`:**

- Evaluates to type and value category of argument
- xvalue → `T&&`, lvalue → `T&`, prvalue → `T`

**`noexcept(expression)`:**

- Returns `true` if argument doesn't throw
- Compile-time evaluation, **prvalue** of type `bool`
- Does **not** evaluate argument

### Binary Expressions

**Logical (`&&`, `||`):**

- **Short-circuit evaluation**: left-to-right, right operand skipped if left determines result
- Order matters: `if (a != nullptr && a[i] == 6)` safe; reversed order crashes

**Assignment:**

- Simple (`=`): Left operand: modifiable lvalue, right-to-left associativity
- Compound (`+=`, `-=`, etc.): Performs operation then assigns

**Sequential (`,`):**

- Evaluates left-to-right
- Result: type and value of **rightmost operand**

### Mixed-Type Binary Expressions

**Promotion hierarchy (highest to lowest):**
`long double` → `double` → `float` → `unsigned long long` → `long long` → `unsigned long` → `long` → `unsigned int` → `int` → `unsigned char` → `char` → `bool`

**Unsigned trap:** Signed promoted to unsigned before comparison

- `unsigned len = 0u; (len > -1)` evaluates to `false`

### Ternary Expression `?:`

```cpp
condition ? expr1 : expr2
```

- Condition: integral, floating-point, or pointer type
- Evaluates `expr1` if true, `expr2` if false (not both)
- Low precedence - usually requires parentheses

---

## Chapter 11: Functions

### Trailing Return-Type Declaration

```cpp
auto identifier(parameter-type-list) -> return-type;
```

### Linkage

- **External linkage** (default): Visible outside translation unit
- **Internal linkage**: Declared with `static`, invisible outside translation unit

### Recursion

```cpp
unsigned factorial(unsigned x) {
    return (x > 2u) ? x * factorial(x - 1) : x;
}
```

### Function Pointers

```cpp
return-type (*identifier)(parameter-type-list) = fn;
```

### Function Objects (Functors)

```cpp
template <typename T>
class Compare {
    bool operator()(T& a, T& b) const { /* ... */ }
};
```

### Lambda Expressions

```cpp
[capture-list](parameter-declaration-clause) -> optional-return-type { body }
```

**Capture Lists:**

- `[]` - No capture
- `[=]` - Capture all by value
- `[&]` - Capture all by reference
- `[=, &x, &y]` - x,y by reference, others by value
- `[&, x, y]` - x,y by value, others by reference
- `[this]` - Capture `this` by value

**Mutable Lambdas:**

```cpp
[capture-list](params) mutable -> return-type { body }
```

---

## Chapter 12: Error Handling

### Exceptions

**Reporting and Handling:**

```cpp
try {
    // code that might generate exceptions
} catch (Type_1 identifier) {
    // handler for specific type
} catch (Type_2 identifier) {
    // handler for another type
} catch (...) {
    // handler for all other types
}
```

**Key rules:**

- First matching `catch` block handles the exception
- `catch(...)` catches any unhandled type
- If no handler found, `std::terminate()` is called
- Functions with `throw` cannot be `noexcept`

**Standard Exception Hierarchy (`<exception>`):**

- `std::exception` - base class
  - `std::logic_error` (preventable logic problems)
    - `length_error`, `domain_error`, `out_of_range`, `invalid_argument`
  - `std::runtime_error` (execution-time problems)
    - `range_error`, `overflow_error`, `underflow_error`
  - `std::bad_alloc` - from `new` (needs `<new>`)
  - `std::bad_cast` - from `dynamic_cast` (needs `<typeinfo>`)

**Expressions That Throw:**

- `throw` expression
- `dynamic_cast` (reference type)
- `typeid` (on null pointer)
- `new` expression

### `noexcept` (C++11)

- Marks function as not throwing exceptions
- Enables compiler optimizations
- **If violated at runtime: immediate termination**

### Standard Exits

**Normal Exits:** Execute destructors, flush streams, call `atexit` functions

- `atexit(void (*func)(void))` - Registers cleanup function (max 32)
- `exit(int status)` - Initiates normal termination

**Abnormal Exits:** Do not execute destructors or call `atexit` functions

- `std::terminate()` - Called when no handler for thrown exception
- `std::abort()` - Terminates via `SIGABRT` signal

---

## Key Debugging Tips for Midterm

1. **Read code carefully** - small details affect output or compilation
2. **Check for compilation errors** first - if it fails to compile, answer "Fails to Compile"
3. **Track value categories** - lvalue, prvalue, xvalue
4. **Watch for operator precedence** and associativity
5. **Check short-circuit evaluation** in logical operators
6. **Track pointer/reference/array behavior** carefully
7. **Note initialization forms** - braces prevent narrowing
8. **Watch for signed/unsigned comparison traps**
9. **Track object lifetimes** - static, automatic, dynamic
10. **Check for const-correctness** and cv-qualifiers

---

## Common Midterm Patterns

1. **Value category questions** - identify lvalue/prvalue/xvalue
2. **Operator precedence** - determine evaluation order
3. **Pointer arithmetic** - array decay, pointer offsets
4. **Function overloading/resolution** - lvalue vs rvalue references
5. **Template instantiation** - explicit specialization
6. **Copy vs move semantics** - deep vs shallow copy
7. **Static vs dynamic binding** - virtual functions
8. **Exception handling** - catch order, noexcept
9. **Memory layout** - sizeof, alignment, padding
10. **Constexpr and static_assert** - compile-time evaluation

---

**Good luck on your midterm!** 🎓
