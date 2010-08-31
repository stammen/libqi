/*
** Author(s):
**  - Chris Kilner <ckilner@aldebaran-robotics.com>
**
** Copyright (C) 2010 Aldebaran Robotics
*/

#include <alcommon-ng/common/server_node.hpp>
#include <alcommon-ng/messaging/messaging.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <alcommon-ng/functor/makefunctor.hpp>
#include <allog/allog.h>

namespace AL {
  using namespace Messaging;
  namespace Common {

    void ping() {
      std::cout << "Ping Baby" << std::endl;
    }

    ServerNode::ServerNode() {}

    ServerNode::ServerNode(
      const std::string& serverName,
      const std::string& serverAddress,
      const std::string& masterAddress) :
        fClientNode(serverName, masterAddress),
        AL::Messaging::DefaultServer(serverAddress)
     {
      fInfo.name = serverName;
      fInfo.address = serverAddress;
      setMessageHandler(this);

      // TODO contact the master

      // =========================================================
      // just testing
      addLocalService(ServiceInfo(serverName, serverName, "ping", makeFunctor(&ping)));

      // use the base class client, to send to master
      // todo add serialization of local service.
      //ResultDefinition res = call(CallDefinition("master", "addService"));
      // =========================================================

      boost::thread serverThread( boost::bind(&Server::run, this));
    }

    // shame about this definition of a handler....
    // would be great if we could do R onMessage( {mod, meth, T})
    boost::shared_ptr<AL::Messaging::ResultDefinition> ServerNode::onMessage(const AL::Messaging::CallDefinition &def) {
      // handle message
      alsdebug << "  Server: " << fInfo.name << ", received message: " << def.moduleName() << "." << def.methodName();

      std::string hash = def.moduleName() + std::string(".") + def.methodName();
      const ServiceInfo& si = getLocalService(hash);
      if (si.nodeName.empty()) {
        // method not found
        alsdebug << "  Error: Method not found " << hash;
      }

      if (si.nodeName == fInfo.name) {
        alsdebug << "  Good: Method is for this node";
      } else {

        alsdebug << "  Error: Method is for node: " << si.nodeName;
      }

      boost::shared_ptr<ResultDefinition> res = boost::shared_ptr<ResultDefinition>(new ResultDefinition());
      si.functor->call(def.args(), res->value());
      return res;
    }

    const NodeInfo& ServerNode::getNodeInfo() const {
      return fInfo;
    }

    void ServerNode::addLocalService(const ServiceInfo& service) {

      // We should be making a hash here, related to
      // "modulename.methodname" + typeid(arg0).name() ... typeid(argN).name()
      
      std::string hash = service.moduleName +
        std::string(".") + service.methodName;
      
      fLocalServiceList.insert(hash, service);
      xRegisterServiceWithMaster(hash);
    }

    const ServiceInfo& ServerNode::getLocalService(const std::string& methodHash) {
      // functors ... should be found here
      return fLocalServiceList.get(methodHash);
    }

    void ServerNode::xRegisterServiceWithMaster(const std::string& methodHash) {
      if (fInfo.name != "master") { // ehem
        CallDefinition callDef;
        callDef.moduleName() = "master";
        callDef.methodName() = "registerService";
        callDef.args().push_back(fInfo.address);
        callDef.args().push_back(methodHash);

        fClientNode.call(callDef);
      }
    }
  }
}
