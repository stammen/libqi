#pragma once
/*
*  Author(s):
*  - Cedric Gestes <gestes@aldebaran-robotics.com>
*  - Chris  Kilner <ckilner@aldebaran-robotics.com>
*
*  Copyright (C) 2010 Aldebaran Robotics
*/
#ifndef _QI_SERIALIZATION_MESSAGE_VISITOR_HPP_
#define _QI_SERIALIZATION_MESSAGE_VISITOR_HPP_


//we want JsonMessage, TextMessage
//we want to copy between message type to convert data
//we want a treeview for qigui that can display a message, or allow create one


//we want PimpL for module: we count instanciate a real module, or a proxied one

#include <qi/serialization/message.hpp>
#include <qi/signature/signature_lexer.hpp>

namespace qi {
  namespace serialization {

    class MessageVisitor
    {
    public:
      MessageVisitor(Message &msg, const char *signature);
      virtual ~MessageVisitor() {;}

      void visit();

    protected:
      virtual void onSimple(const char *simpleType);
      virtual void onList(const char *elementType);
      virtual void onMap(const char *keyType, const char *valueType);
      virtual void onProtobuf(const char *name);

    protected:
      qi::SignatureLexer          _lexer;
      qi::serialization::Message &_message;
    };

  }
}



#endif  // _QI_SERIALIZATION_MESSAGE_VISITOR_HPP_
