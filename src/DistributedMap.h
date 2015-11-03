/*
 * DistributedMap.h
 *
 *  Created on: Nov 2, 2015
 *      Author: zackramjan
 */

#ifndef DISTRIBUTEDMAP_H_
#define DISTRIBUTEDMAP_H_
#include <string>
#include "hazelcast/client/HazelcastAll.h"
using namespace hazelcast::client;

class DistributedMap {
public:
	DistributedMap(std::string host, int port);
	virtual ~DistributedMap();
	 HazelcastClient *hazelcastClient;
	 IMap<std::string,std::string> map;
	 std::string get(std::string key);
	 void put(std::string key,std::string value);
};

#endif /* DISTRIBUTEDMAP_H_ */
