//
// Generated file, do not edit! Created by opp_msgc 4.0 from networklayer/ipv4/IPDatagram_hacked.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "IPDatagram_hacked_m.h"

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




Register_Class(IPDatagram_hacked);

IPDatagram_hacked::IPDatagram_hacked(const char *name, int kind) : IPDatagram(name,kind)
{
    this->attackTag_var = 0;
}

IPDatagram_hacked::IPDatagram_hacked(const IPDatagram_hacked& other) : IPDatagram()
{
    setName(other.getName());
    operator=(other);
}

IPDatagram_hacked::~IPDatagram_hacked()
{
}

IPDatagram_hacked& IPDatagram_hacked::operator=(const IPDatagram_hacked& other)
{
    if (this==&other) return *this;
    IPDatagram::operator=(other);
    this->attackTag_var = other.attackTag_var;
    return *this;
}

void IPDatagram_hacked::parsimPack(cCommBuffer *b)
{
    IPDatagram::parsimPack(b);
    doPacking(b,this->attackTag_var);
}

void IPDatagram_hacked::parsimUnpack(cCommBuffer *b)
{
    IPDatagram::parsimUnpack(b);
    doUnpacking(b,this->attackTag_var);
}

short IPDatagram_hacked::getAttackTag() const
{
    return attackTag_var;
}

void IPDatagram_hacked::setAttackTag(short attackTag_var)
{
    this->attackTag_var = attackTag_var;
}

class IPDatagram_hackedDescriptor : public cClassDescriptor
{
  public:
    IPDatagram_hackedDescriptor();
    virtual ~IPDatagram_hackedDescriptor();

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

Register_ClassDescriptor(IPDatagram_hackedDescriptor);

IPDatagram_hackedDescriptor::IPDatagram_hackedDescriptor() : cClassDescriptor("IPDatagram_hacked", "IPDatagram")
{
}

IPDatagram_hackedDescriptor::~IPDatagram_hackedDescriptor()
{
}

bool IPDatagram_hackedDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<IPDatagram_hacked *>(obj)!=NULL;
}

const char *IPDatagram_hackedDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int IPDatagram_hackedDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int IPDatagram_hackedDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return FD_ISEDITABLE;
        default: return 0;
    }
}

const char *IPDatagram_hackedDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "attackTag";
        default: return NULL;
    }
}

const char *IPDatagram_hackedDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "short";
        default: return NULL;
    }
}

const char *IPDatagram_hackedDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int IPDatagram_hackedDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    IPDatagram_hacked *pp = (IPDatagram_hacked *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

bool IPDatagram_hackedDescriptor::getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i,resultbuf,bufsize);
        field -= basedesc->getFieldCount(object);
    }
    IPDatagram_hacked *pp = (IPDatagram_hacked *)object; (void)pp;
    switch (field) {
        case 0: long2string(pp->getAttackTag(),resultbuf,bufsize); return true;
        default: return false;
    }
}

bool IPDatagram_hackedDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    IPDatagram_hacked *pp = (IPDatagram_hacked *)object; (void)pp;
    switch (field) {
        case 0: pp->setAttackTag(string2long(value)); return true;
        default: return false;
    }
}

const char *IPDatagram_hackedDescriptor::getFieldStructName(void *object, int field) const
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

void *IPDatagram_hackedDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    IPDatagram_hacked *pp = (IPDatagram_hacked *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


