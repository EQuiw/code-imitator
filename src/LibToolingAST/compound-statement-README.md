# README - Compound Statement Transformer

## Purpose

This transformer deals with curly braces. If a statement has no curly braces, as it is a single stmt,
then we can add curly braces again. The other way round as well: If a statement has curly braces, but is just
a single stmt, then we can remove the curly braces.

Take, for instance, the following code snippet:
```c++
while(x--)
  printf(...)
```
By using our code transformer, it can be transformed into
```c++
while(x--) {
  printf(...)
}
```

## Calling of code transformer
You can see what options you can pass by looking at the `llvm::cl::opt<int>`
at the beginning. For instance,
```c++
static llvm::cl::opt<int> OurCMDOption1("strategy", llvm::cl::cat(MyOptionCategory));
static llvm::cl::opt<int> OurCMDOption2("seed", llvm::cl::cat(MyOptionCategory));
}
```
defines two command-line arguments. The first is the strategy that we use
for rewriting, the second is a seed that is used to decide what code snippet
will be changed if multiple code parts could be rewritten.

We usually define our strategies by using an enum; here, it is:
```c++
enum Strategy {add_curly_braces = 1, remove_curly_braces = 2};
```
We can either look out for code location where we can add curly braces (`add_curly_braces`)
or we try to find locations where we can remove curly braces (`remove_curly_braces`).
The latter can be used for a single-line statement.

## Control-flow of the code transformer

1. The code transformer starts in the main function.
2. Clang requires that we define an `ASTFrontendAction` and `ASTConsumer`
  to start the rewriting stuff. Therefore, we use `MyFrontendAction`
  from `ASTFrontendActionTemplate.inl`  which is a template that we can use
  to start the rewriting stuff in clang. This saves some lines of code.

3. We use the `RecursiveASTVisitor` API. It goes over the AST and we can
  define a callback whenever a certain type is visited.
  For instance, we want to get all statements from an AST. To this end, we
  define
  ```c++
  bool VisitStmt(Stmt *s){
      bool inmainfile = sm.isInMainFile(s->getLocStart());
      if (inmainfile) { ... }
  }
  ```
  - Here, we first check that the statement s is inside the current file
  by using `sm.isInMainFile`
  (see the limitation that we only work with single file projects,
    which makes the parsing + rewriting easier; but of course, we
    could extend the code transformations to multi-file projects).
  - You should be familiar with the `RecursiveASTVisitor` API.
  Consider that we parse and collect all information from the whole AST
  before we start to rewrite code.
    - To this end, look at the `HandleTranslationUnit` method from MyASTConsumer.
    - Here, we first call `TraverseDecl` that goes over the whole AST and
    collects all information (e.g. usable statements).
    - Then, `replacecommand` is called that does the rewriting.
  - Another note: Another method of getting all information and rewriting is to use the
  Matching API from LibTooling (look at init_decl_transformer.cpp to find
    our more about that).

4. In `VisitStmt`, we check if a statement is a control statement
  where curly braces could be used; e.g. if-statement or for-statements
  are good candidates. We collect them all before we start to rewrite a
  source code.

5. In 'replacecommand', we perform the rewriting.
  - We sort all possible code locations that could be rewritten.
  - If our code transformer was not able to rewrite a code location,
  we return the code 123:
  ```c++
  llvm::errs() << "Code 123: No transformations possible\n";
  ```
