# OpenEngine
Simple OpenGL engine
 
## Fuckups
- memory management is full of crap, smart pointers were a mistake. Plan on using std::unique_ptr and giving out references instead for performance reasons
