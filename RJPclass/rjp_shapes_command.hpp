#ifndef RJP_SHAPES_COMMAND_H
#define RJP_SHAPES_COMMAND_H

class shapesObCommand
{
public:
    virtual void excute() =0;
protected:
    shapesObCommand(){}
};


template<class Receiver>
class shapesObCommandTemplate: public shapesObCommand
{
public:
    typedef void (Receiver:: * Action) ();
    shapesObCommandTemplate(Receiver * r,Action a):
        _action(a),
        _receiver(r)
    {}
    virtual void excute();
private:
    Action _action;
    Receiver * _receiver;
};

template<class Receiver>
void shapesObCommandTemplate<Receiver>::excute()
{
    (_receiver->*_action)();// the *_action will not jump automatically
}










#endif // RJP_SHAPES_COMMAND_H
