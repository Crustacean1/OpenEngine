# OpenEngine
Simple OpenGL engine
 
## Fuckups
- memory management is full of crap, smart pointers were a mistake. Plan on using std::unique_ptr and giving out references instead for performance reasons
## TODOS:
- create Component class, base for all elements in Object
- Finish class Behaviour
- Move update from Keyboard to BehaviourManager
- Check for children transform correctness
- Standarize Components behaviour
