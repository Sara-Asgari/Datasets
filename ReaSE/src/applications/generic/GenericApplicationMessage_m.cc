//
// Generated file, do not edit! Created by opp_msgc 4.0 from applications/generic/GenericApplicationMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "GenericApplicationMessage_m.h"

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




Register_Class(GenericApplicationMessage);

GenericApplicationMessage::GenericApplicationMessage(const char *name, int kind) : cPacket(name,kind)
{
    this->replyLength_var = 0;
    this->replyPerRequest_var = 0;
    this->timeToRespond_var = 0;
    this->last_var = 0;
    this->packetNumber_var = 0;
}

GenericApplicationMessage::GenericApplicationMessage(const GenericApplicationMessage& other) : cPacket()
{
    setName(other.getName());
    operator=(other);
}

GenericApplicationMessage::~GenericApplicationMessage()
{
}

GenericApplicationMessage& GenericApplicationMessage::operator=(const GenericApplicationMessage& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    this->replyLength_var = other.replyLength_var;
    this->replyPerRequest_var = other.replyPerRequest_var;
    this->timeToRespond_var = other.timeToRespond_var;
    this->last_var = other.last_var;
    this->packetNumber_var = other.packetNumber_var;
    return *this;
}

void GenericApplicationMessage::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->replyLength_var);
    doPacking(b,this->replyPerRequest_var);
    doPacking(b,this->timeToRespond_var);
    doPacking(b,this->last_var);
    doPacking(b,this->packetNumber_var);
}

void GenericApplicationMessage::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->replyLength_var);
    doUnpacking(b,this->replyPerRequest_var);
    doUnpacking(b,this->timeToRespond_var);
    doUnpacking(b,this->last_var);
    doUnpacking(b,this->packetNumber_var);
}

int GenericApplicationMessage::getReplyLength() const
{
    return replyLength_var;
}

void GenericApplicationMessage::setReplyLength(int replyLength_var)
{
    this->replyLength_var = replyLength_var;
}

int GenericApplicationMessage::getReplyPerRequest() const
{
    return replyPerRequest_var;
}

void GenericApplicationMessage::setReplyPerRequest(int replyPerRequest_var)
{
    this->replyPerRequest_var = replyPerRequest_var;
}

double GenericApplicationMessage::getTimeToRespond() const
{
    return timeToRespond_var;
}

void GenericApplicationMessage::setTimeToRespond(double timeToRespond_var)
{
    this->timeToRespond_var = timeToRespond_var;
}

bool GenericApplicationMessage::getLast() const
{
    return last_var;
}

void GenericApplicationMessage::setLast(bool last_var)
{
    this->last_var = last_var;
}

int GenericApplicationMessage::getPacketNumber() const
{
    return packetNumber_var;
}

void GenericApplicationMessage::setPacketNumber(int packetNumber_var)
{
    this->packetNumber_var = packetNumber_var;
}

class GenericApplicationMessageDescriptor : public cClassDescriptor
{
  public:
    GenericApplicationMessageDescriptor();
    virtual ~GenericApplicationMessageDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual bool getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(GenericApplicationMessageDescriptor);

GenericApplicationMessageDescriptor::GenericApplicationMessageDescriptor() : cClassDescriptor("GenericApplicationMessage", "cPacket")
{
}

GenericApplicationMessageDescriptor::~GenericApplicationMessageDescriptor()
{
}

bool GenericApplicationMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<GenericApplicationMessage *>(obj)!=NULL;
}

const char *GenericApplicationMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int GenericApplicationMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount(object) : 5;
}

unsigned int GenericApplicationMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return FD_ISEDITABLE;
        case 1: return FD_ISEDITABLE;
        case 2: return FD_ISEDITABLE;
        case 3: return FD_ISEDITABLE;
        case 4: return FD_ISEDITABLE;
        default: return 0;
    }
}

const char *GenericApplicationMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "replyLength";
        case 1: return "replyPerRequest";
        case 2: return "timeToRespond";
        case 3: return "last";
        case 4: return "packetNumber";
        default: return NULL;
    }
}

const char *GenericApplicationMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "int";
        case 1: return "int";
        case 2: return "double";
        case 3: return "bool";
        case 4: return "int";
        default: return NULL;
    }
}

const char *GenericApplicationMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int GenericApplicationMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    GenericApplicationMessage *pp = (GenericApplicationMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

bool GenericApplicationMessageDescriptor::getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i,resultbuf,bufsize);
        field -= basedesc->getFieldCount(object);
    }
    GenericApplicationMessage *pp = (GenericApplicationMessage *)object; (void)pp;
    switch (field) {
        case 0: long2string(pp->getReplyLength(),resultbuf,bufsize); return true;
        case 1: long2string(pp->getReplyPerRequest(),resultbuf,bufsize); return true;
        case 2: double2string(pp->getTimeToRespond(),resultbuf,bufsize); return true;
        case 3: bool2string(pp->getLast(),resultbuf,bufsize); return true;
        case 4: long2string(pp->getPacketNumber(),resultbuf,bufsize); return true;
        default: return false;
    }
}

bool GenericApplicationMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    GenericApplicationMessage *pp = (GenericApplicationMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setReplyLength(string2long(value)); return true;
        case 1: pp->setReplyPerRequest(string2long(value)); return true;
        case 2: pp->setTimeToRespond(string2double(value)); return true;
        case 3: pp->setLast(string2bool(value)); return true;
        case 4: pp->setPacketNumber(string2long(value)); return true;
        default: return false;
    }
}

const char *GenericApplicationMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

void *GenericApplicationMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    GenericApplicationMessage *pp = (GenericApplicationMessage *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


