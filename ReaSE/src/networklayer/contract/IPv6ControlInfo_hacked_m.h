//
// Generated file, do not edit! Created by opp_msgc 4.0 from networklayer/contract/IPv6ControlInfo_hacked.msg.
//

#ifndef _IPV6CONTROLINFO_HACKED_M_H_
#define _IPV6CONTROLINFO_HACKED_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0400
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif

// dll export symbol
#ifndef REASE_API 
#  if defined(REASE_EXPORT)
#    define REASE_API  OPP_DLLEXPORT
#  elif defined(REASE_IMPORT)
#    define REASE_API  OPP_DLLIMPORT
#  else
#    define REASE_API 
#  endif
#endif

// cplusplus {{ ... }} section:

#include "IPv6ControlInfo.h"
#include "ReaSEDefs.h"
// end cplusplus



/**
 * Class generated from <tt>networklayer/contract/IPv6ControlInfo_hacked.msg</tt> by opp_msgc.
 * <pre>
 * class IPv6ControlInfo_hacked extends IPv6ControlInfo
 * {
 * 	
 * 	short attackTag = 0;
 * }
 * </pre>
 */
class REASE_API IPv6ControlInfo_hacked : public IPv6ControlInfo
{
  protected:
    short attackTag_var;

    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const IPv6ControlInfo_hacked&);

  public:
    IPv6ControlInfo_hacked();
    IPv6ControlInfo_hacked(const IPv6ControlInfo_hacked& other);
    virtual ~IPv6ControlInfo_hacked();
    IPv6ControlInfo_hacked& operator=(const IPv6ControlInfo_hacked& other);
    virtual IPv6ControlInfo_hacked *dup() const {return new IPv6ControlInfo_hacked(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual short getAttackTag() const;
    virtual void setAttackTag(short attackTag_var);
};

inline void doPacking(cCommBuffer *b, IPv6ControlInfo_hacked& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, IPv6ControlInfo_hacked& obj) {obj.parsimUnpack(b);}


#endif // _IPV6CONTROLINFO_HACKED_M_H_