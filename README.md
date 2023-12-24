# Excerpt
Excerpt is a compiler which uses the LLVM compiler backend. This README provides the basic information of the project, as well as a TODO list.

## Project Structure
- `build/`: Directory for build artifacts.
- `include/`: Header files.
  - `excerpt/`: Project-specific header files.
- `src/`: Source code files.
- `tests/`: Unit tests.

## Building
To build the project you have a choice of building with/without unit testing.

```bash
sh ./build.sh
```

```bash
sh ./build.sh --build-tests
```

## Running unit testing
To run unit testing, you may use the `build.sh` file.
```bash
sh ./build.sh --run-tests
```

## Usage
To use the Excerpt Compiler, run the compiled executable with the appropriate command-line options. For example:
```bash
./excerpt input.txt --output out
```
## TODO List

### 1. Lexical Analysis (Tokens and Tokenizer):
- [ ] Implement a basic token structure.
- [ ] Develop a tokenizer to generate tokens from source code.

### 2. Syntax Analysis (Parser):
- [ ] Design a parser for the language grammar.
- [ ] Implement parsing of statements and expressions.
- [ ] Handle control flow and conditional constructs.

### 3. Abstract Syntax Tree (AST):
- [ ] Create a representation for the AST nodes.
- [ ] Extend the parser to build the AST during parsing.

### 4. Semantic Analysis:
- [ ] Implement basic symbol table functionality.
- [ ] Perform type checking and scope analysis.

### 5. Intermediate Representation (IR) Generation:
- [ ] Generate LLVM IR from the AST.
- [ ] Handle basic optimizations at the IR level.

### 6. Code Generation:
- [ ] Implement the final step of translating IR to machine code.
- [ ] Optimize code generation for performance.

### 7. Error Handling and Reporting:
- [ ] Enhance error messages for better user feedback.

### 8. Documentation:
- [ ] Document the language syntax and features.
- [ ] Create usage examples and tutorials.

### 9. Testing:
- [ ] Expand unit tests to cover the entire compiler pipeline.
- [ ] Conduct comprehensive integration testing.

### 10. Performance Optimization:
- [ ] Profile and optimize critical sections of the compiler.

### 11. User Interface and User Experience:
- [ ] Enhance the user interface for better usability.
- [ ] Provide meaningful error messages and debugging support.

### 12. Continuous Integration (CI) Pipeline:
- [ ] Set up automated testing and integration with CI services.
