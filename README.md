# Quill Language Specification

Programming language that is primarily influenced by C, Rust, Swift, and OCaml.

--

## Table of Contents

- [Quill Language Specification](#quill-language-specification)
  - [Table of Contents](#table-of-contents)
  - [Comments](#comments)
  - [Data Types and Structures](#data-types-and-structures)
    - [Primitive Types](#primitive-types)
    - [Data Structures](#data-structures)
    - [Structs](#structs)
  - [Statements](#statements)
  - [Expressions](#expressions)
  - [Variables and Constants](#variables-and-constants)
  - [Functions](#functions)
    - [Main Function](#main-function)
  - [Control Structures](#control-structures)
    - [If-Else](#if-else)
    - [Loops](#loops)
  - [Optionals with Structs](#optionals-with-structs)
  - [Example Program Using Structs](#example-program-using-structs)

---

## Comments

The language supports both single-line and multi-line comments for code documentation and readability.

- **Single-line Comments**: Use `//` to start a single-line comment. Anything following `//` on that line is ignored by the compiler.

  ```plaintext
  // This is a single-line comment.
  var x: int = 5; // Comments can follow code on the same line.
  ```

- **Multi-line Comments**: Enclose comments within `/*` and `*/` to span multiple lines.

  ```plaintext
  /*
     This is a multi-line comment.
     It can span multiple lines.
  */
  var y: int = 10;
  ```

---

## Data Types and Structures

### Primitive Types

- `int` — integers
- `uint` — unsigned integers
- `float` — floating-point values
- `bool` — boolean values (`true` or `false`)
- `char` — character values
- `string` — an array of characters (supports Unicode)
- `void` — represents the absence of a value, typically used for function return types

### Data Structures

- **Arrays**:
  - `[||]` — a fixed-size array containing a single data type.

    ```plaintext
    var numbers: int[||] = [|| 1, 2, 3 ||];
    ```

- **Lists**:
  - `[]` — a dynamic list of a single type.

    ```plaintext
    var items: string[] = ["apple", "banana", "cherry"];
    ```

- **Optionals**:
  - An `Optional` type represents a value that can be either `None` or `Is(type)`, denoted by appending `?` to the type.
  - **`None`** indicates the absence of a value.
  - **`Is(value)`** wraps a value of the specified type.

    ```plaintext
    var optionalNumber: int? = Is(42);
    var missingNumber: int? = None;
    ```

- **Structures**:
  - `struct` — defines a custom data type grouping multiple variables.

### Structs

- **Definition**: Custom data types that group variables under a single name.
- **Syntax**:

  ```plaintext
  struct StructName {
      field1: Type1;
      field2: Type2;
      // Additional fields...
  }
  ```

- **Instantiation**:

  ```plaintext
  var instanceName: StructName = StructName {
      field1: value1,
      field2: value2,
      // Additional field assignments...
  };
  ```

- **Field Access**:

  ```plaintext
  var value = instanceName.field1;
  ```

---

## Statements

- Do not evaluate to a value.
- Require semicolons (`;`) to be terminated.
- Examples: variable declarations, assignments, and function calls that do not return a value.
- **Note**: The `??` operator can be used to assign an alternate value if an `Optional` is `None`.

```plaintext
// Valid Syntax Examples

// Example 1
var x: int = 5;

// Example 2
var x: int?;
var y: int = x ?? 5; // x is None, 5 is the alternate value.

// Invalid Syntax Examples
x + 3 // This is an expression, not a statement.
```

---

## Expressions

- Evaluate to a value.
- Do not require semicolons unless used as a statement.
- Examples: `if-else`, `loop`, function calls that return values, and comparisons.
- **Note**: `loop` requires the `break value;` syntax to evaluate.

```plaintext
// Valid Syntax Examples

var some_value: int = if 5 > 3 {
    5 + 3 // Expression assigned to some_value.
} else {
    5 // Expression assigned to some_value.
}; // Terminated with a semicolon because it's a statement.

// Invalid Syntax Examples
var x: int = 5 // Missing semicolon; this is a statement, not an expression.
```

---

## Variables and Constants

- `const` denotes a constant value that is immutable.
- `var` denotes a variable that is mutable.
- **Mutability Modifiers**:
  - **Default**: Variables are immutable unless specified with `var`.
- **Strict Typing**: Variables must be declared with a type.
- **Prototyping Allowed**: Variables can be declared without initialization but must be assigned before use.

```plaintext
// Valid Syntax Examples

const x: int = 5;
var y: int = 6;
var z: int;

z = x + y;

// Invalid Syntax Examples

const x: int = 5;
var y: int = 6;
var z: int;

x = z + y; // Error: x is a constant and cannot be reassigned.
```

---

## Functions

- **Function Prototyping**: Allowed; functions must be declared before use. Parameter names in prototypes are optional.
- **Parameter List**: Uses parentheses `()`.
- **Function Body**: Requires braces `{}`.
- **Parameter Modifiers**:
  - `ref` implies the parameter is passed by reference.
  - `const` implies the parameter is immutable (default behavior).
  - `var` implies the parameter is mutable within the function.
- **Parameter Order**:
  - The order of modifiers is `ref`, `var` or `const`, followed by the type.
  - Example: `ref var int` (passed by reference, mutable, of type `int`).
- **Return Type**:
  - Specify `void` for functions that do not return a value.
  - The final expression serves as the return value unless the return type is `void`.

```plaintext
// Valid Syntax Examples

func add(const int, ref var int): int; // Prototype with optional parameter names

func add(param1: const int, param2: ref var int): int {
    param2 = 5;
    param1 + param2
}

var x: int = add(1, 2);

// Function returning void
func displayMessage(message: string): void {
    print(message);
}

// Invalid Syntax Examples

func add(const int, const int): int; // Prototype

var x: int = add(1, 2); // Error: Function used before definition without a prototype.

func add(param1: int, param2: int): int {
    param1 + param2
}
```

### Main Function

- **Requirement**: Every program must have a `main` function as the entry point.
- **Signature**: The `main` function must have the following signature:

  ```plaintext
  func main(argc: const int, argv: string[]): int;
  ```

  - `argc`: A constant integer representing the number of command-line arguments.
  - `argv`: A dynamic list of strings representing the command-line arguments.
  - The `main` function returns an `int`, typically used as the exit code of the program.

- **Function Definition**:

  ```plaintext
  func main(argc: const int, argv: string[]): int {
      // Function body...
      0 // Return 0 to indicate successful execution.
  }
  ```

- **Notes**:
  - The `main` function must be defined; it cannot be just a prototype.
  - The `argc` and `argv` parameters provide access to command-line arguments.
  - The return value is used to indicate the program's exit status.
  - If the program completes successfully, `main` should return `0`.

---

## Control Structures

### If-Else

- **Syntax**:
  - No parentheses around the condition.
  - Braces `{}` are required.
  - Acts as an expression if it returns a value.
- **Variable Declaration in Conditions**:
  - Variables declared in the condition are scoped within the `if-else` blocks.

```plaintext
// Valid Syntax Examples

// Example 1
if 5 > 3 {
    // Do something.
} else if 5 < 3 {
    // Do something else.
} else {
    // Default action.
}

// Example 2
var y: int;
if var x: int = add(1, 2); x > 1 {
    y = x;
} else {
    y = 5;
};

// Example 3
var z: int = if 3 > 1 {
    3 // z is assigned this value if true.
} else {
    5 // z is assigned this value if false.
};

// Invalid Syntax Examples

var x: int = if 5 < 3 {
    5
};
// Error: x may be unassigned if the condition is false.
```

### Loops

- **Primary Loop Construct**: `loop`
  - Manual breaks are required.
- **Syntactic Sugar**: `while` and `for` loops can be implemented using `loop`.
- **Break Statement**:
  - `break;` exits the loop without a value.
  - `break value;` exits the loop and evaluates to the given value.
- **Braces**: Required for the loop body.
- **Return Value**:
  - A loop can act as an expression if it uses `break value;`.

```plaintext
// Valid Syntax Examples

// Example 1
loop {
    if condition_met {
        break;
    }
    // Loop body...
}

// Example 2
var result: int = loop {
    if some_condition {
        break computed_value;
    }
    // Additional logic...
} ?? default_value;

// Invalid Syntax Examples

var x: int = loop {
    if condition_met {
        break 5;
    } else {
        break;
    }
} // Error: Assignment is a statement, requires a semicolon.
// Error: x may be unassigned if the loop exits without a value.
```

---

## Optionals with Structs

- **Optionals**:
  - Represent values that may or may not be present.
  - Use `None` for absence of value and `Is(value)` to wrap a value.
- **Defining Optional Fields in Structs**:
  - Append `?` to the type of a field to make it optional.

  ```plaintext
  struct Person {
      name: string;
      age: int;
      email: string?;
  }

  var john: Person = Person {
      name: "John Doe",
      age: 30,
      email: None
  };
  ```

- **Accessing Optional Fields**:

  ```plaintext
  var email: string = john.email ?? "No email provided";
  ```

- **Assigning to Optional Fields**:

  ```plaintext
  john.email = Is("john.doe@example.com");
  ```

---

## Example Program Using Structs

```plaintext
// Single-line comment: Define a Rectangle struct
struct Rectangle {
    width: float;
    height: float;
}

/* Multi-line comment:
   Function to calculate the area of a rectangle.
   Takes a Rectangle struct as a parameter.
*/
func area(rect: Rectangle): float {
    rect.width * rect.height
}

func main(argc: const int, argv: string[]): int {
    var myRect: Rectangle = Rectangle {
        width: 5.0,
        height: 3.0
    };

    var rectArea: float = area(myRect);
    print("Area of rectangle:", rectArea);

    0 // Return 0 to indicate successful execution.
}
```
