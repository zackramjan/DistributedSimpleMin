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
	Address address(host, port);
	clientConfig.addAddress(address);
	hazelcastClient = new HazelcastClient(clientConfig);

}

DistributedMap::~DistributedMap() {
	delete hazelcastClient;

}

void DistributedMap::put(std::string key, std::string value) {
	IMap<std::string, std::string> map = hazelcastClient->getMap<std::string, std::string>("zacks");
	map.put(key, value);
}

std::string DistributedMap::get(std::string key) {
	IMap<std::string, std::string> map = hazelcastClient->getMap<std::string, std::string>("zacks");
	return *map.get(key);
}

std::string DistributedMap::get(std::string mapname, std::string key) {
	IMap<std::string, std::string> map = hazelcastClient->getMap<std::string, std::string>(mapname);
	return *map.get(key);
}

void DistributedMap::put(std::string mapname, std::string key, std::string value) {
	IMap<std::string, std::string> map = hazelcastClient->getMap<std::string, std::string>(mapname);
	map.put(key, value);
}

long DistributedMap::getUniqueID() {
	IdGenerator id = hazelcastClient->getIdGenerator("zacks");
	return id.newId();
}
