/*
 * DistributedMap.h
 *
 *  Created on: Nov 2, 2015
 *      Author: zackramjan
 */

#ifndef DISTRIBUTEDMAP_H_
#define DISTRIBUTEDMAP_H_
#include <string>
#include <vector>
#include "hazelcast/client/HazelcastAll.h"
using namespace hazelcast::client;

//template <class K, class V>
class DistributedMap {
public:
	DistributedMap(std::string host, int port);
	virtual ~DistributedMap();
	HazelcastClient *hazelcastClient;
	std::string get(std::string key);
	void put(std::string key, std::string value);
	std::string get(std::string bucketname,std::string key);
	void put(std::string bucketname,std::string key, std::string value);
	long getUniqueID();
	std::vector<std::string> getKeys(std::string bucketname);
	std::vector<std::string> getKeys();

};

#endif /* DISTRIBUTEDMAP_H_ */
