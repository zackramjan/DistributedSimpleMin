/*
 * DistributedMap.cpp
 *
 *  Created on: Nov 2, 2015
 *      Author: zackramjan
 */

#include "DistributedMap.h"
#include "hazelcast/client/HazelcastAll.h"
#include <boost/shared_ptr.hpp>

using namespace hazelcast::client;

DistributedMap::DistributedMap(std::string host, int port) {
	  ClientConfig clientConfig;
	  Address address( host, port );
	  clientConfig.addAddress( address );
	  hazelcastClient = new HazelcastClient( clientConfig );
	  map = hazelcastClient->getMap<std::string,std::string>( "zmap" );

}

DistributedMap::~DistributedMap() {
	delete hazelcastClient;

}

void DistributedMap::put(std::string key, std::string value) {
	map.put(key,value );
}

std::string DistributedMap::get(std::string key) {
	return map.get(key).get();
}
