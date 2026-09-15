# C++ Course Practice

This repository is a hands-on workspace for getting comfortable with C++ syntax, language features, and programming patterns. It is intended to grow alongside a C++ course or self-study plan: each exercise focuses on one concept, keeps the implementation small enough to inspect easily, and provides a place to experiment with different ways of writing the same idea.

The long-term goal is to move from basic language mechanics to small, project-based programs built with object-oriented programming principles. The repository is therefore less of a single application and more of a progressive collection of examples and practice tasks.

## Learning Goals

The exercises in this repository are designed to build familiarity with:

- C++ program structure, compilation, and the `main` function
- Primitive data types, variables, constants, and expressions
- References, pointers, pointer safety, and memory management
- Static and dynamic allocation
- Type aliases with both `typedef` and the modern `using` syntax
- Functions, parameters, return values, and scope
- Namespaces and techniques for organizing code
- Templates for writing reusable, type-independent code
- Classes, objects, constructors, methods, access control, and encapsulation
- Core object-oriented programming ideas such as abstraction, inheritance, and polymorphism
- Designing small projects by separating responsibilities into logical types and components

## Repository Structure

```text
course-practice/
├── README.md
└── base/
	├── static/
	│   ├── static
	│   └── static.cpp
	└── template/
		├── tydef
		└── tydef.cpp
```

The current folders contain introductory examples. As more topics are practiced, additional folders can be added for functions, namespaces, templates, classes, inheritance, and complete exercises or mini-projects.

## Current Exercises

### Static and Dynamic Allocation

`base/static/static.cpp` compares two basic ways of storing an integer:

- A local variable is created with automatic storage duration.
- An integer is created dynamically with `new`.
- The dynamically allocated value is accessed through a pointer.
- The memory is released with `delete`, and the pointer is reset to `nullptr`.

This example is intended to build an understanding of pointer-based memory management and the difference between ordinary local storage and explicitly allocated storage. It also provides an early opportunity to practice responsible cleanup. Later exercises can build on this foundation by introducing references, smart pointers, and safer modern C++ ownership patterns.

### Type Aliases

`base/template/tydef.cpp` demonstrates two ways to create aliases for existing types:

- `typedef` is shown with a constant `double` alias.
- `using` is shown with aliases for `int` and `double*`.

The example also highlights an important pointer declaration detail: in `int* a, b;`, only `a` is a pointer, while `b` is an ordinary `int`. An alias such as `dblePtr` makes declarations like `dblePtr i, j;` easier to read because both variables use the pointer alias.

Although the directory is currently named `template`, this exercise is about type aliases rather than C++ templates. Future template exercises can use the same area or a dedicated directory once generic functions, classes, and type parameters are introduced.

## Planned Progression

The repository can develop through the following stages:

1. **Language foundations**: variables, operators, conditionals, loops, functions, and basic input/output.
2. **Memory and types**: pointers, references, allocation, type aliases, `const`, and scope.
3. **Code organization**: namespaces, header files, source files, and separating declarations from implementations.
4. **Generic programming**: function templates, class templates, and reusable algorithms that work with multiple types.
5. **Object-oriented programming**: classes, constructors, destructors, encapsulation, composition, inheritance, and polymorphism.
6. **Project practice**: small applications that combine the concepts into a coherent design, such as a task manager, library system, inventory tracker, or simple game.

Each stage should add exercises that are small enough to understand completely while gradually introducing more realistic design decisions.

## Practice Principles

- Prefer clear, readable code over unnecessarily clever syntax.
- Compile and run each example while changing one idea at a time.
- Use comments to record questions, observations, and differences between approaches.
- Compare older C++ syntax with modern alternatives where both are useful to understand.
- Pay attention to ownership and object lifetime whenever pointers or dynamic memory are involved.
- When an exercise grows, split it into focused classes or functions instead of putting all logic in `main`.
- Revisit earlier examples and improve them as new language features become familiar.

## Building the Examples

The source files are standalone programs and can be compiled with a C++ compiler such as `g++` or `clang++`. For example:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic base/static/static.cpp -o static-practice
./static-practice
```

To compile the type-alias exercise:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic base/template/tydef.cpp -o typedef-practice
./typedef-practice
```

The compiler warnings are enabled deliberately: warnings often reveal syntax mistakes, unused values, or unclear code before they become larger problems.

## Repository Purpose

This repository is a space for repetition, experimentation, and gradual improvement. The objective is not only to memorize C++ syntax, but to understand how the language features fit together when designing and implementing small programs. Over time, the exercises should evolve from isolated syntax demonstrations into practical object-oriented projects with reusable components, well-defined responsibilities, and maintainable code.
