#ifndef SYSTEM_H_
#define SYSTEM_H_

class Message;

class System {

public:
    System();

    virtual ~System();

    virtual void update(const float &delta) = 0;

    virtual void init() = 0;

    virtual void sendMessage(Message* message) = 0;

private:



};

#endif
