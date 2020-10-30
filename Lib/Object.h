#ifndef OBJECT
#define OBJECT

class Object
{
    //Position, parent , children
public:
    virtual void render() = 0;// With renderer???
    virtual void onStart() = 0;
    virtual void update(double delta) = 0;

    //global position
    //local position

    //global transform
    //local transform

    //getID
    //Copy/Move constructor
    //Tags (rather not)
    //
};

#endif /*OBJECT*/