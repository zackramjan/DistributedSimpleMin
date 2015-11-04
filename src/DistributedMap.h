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
#include <boost/shared_ptr.hpp>
using namespace hazelcast::client;

//this is a templated way to access hazelcast KV stores.

template<class KEYZ, class VALZ>
class DistributedMap {
public:
	HazelcastClient *hazelcastClient; //the client object

	//connect to hazelcast when created at the following hostname and port
	DistributedMap(std::string host, int port) {
		ClientConfig clientConfig;
		Address address(host, port);
		clientConfig.addAddress(address);
		hazelcastClient = new HazelcastClient(clientConfig);
	}

	//clean up
	virtual ~DistributedMap() {
		delete hazelcastClient;
	}

	//get the value associated with a particular key within the particular "bucket"
	VALZ get(std::string bucketname, KEYZ key) {
		IMap<KEYZ, VALZ> map = hazelcastClient->getMap<KEYZ, VALZ>(bucketname);
		return *map.get(key);
	}

	//if you dont get from specified a bucket, we assume you want the default bucket hardcoded here
	VALZ get(KEYZ key) {
		return this->get("zacks,key");
	}

	//store a value with the particular key in the given bucket.
	void put(std::string bucketname, KEYZ key, VALZ value) {
		IMap<KEYZ, VALZ> map = hazelcastClient->getMap<KEYZ, VALZ>(bucketname);
		map.put(key, value);
	}

	//store a value with the particular key within the "default" bucket (hardcoded here)
	void put(KEYZ key, VALZ value) {
		this->put("zacks", key, value);
	}

	//get a unique identifier. this id is unique across all processes in the cluster.
	long getUniqueID() {
		IdGenerator id = hazelcastClient->getIdGenerator("zacks");
		return id.newId();
	}

	//get a list of all keys within the specified bucket
	std::vector<KEYZ> getKeys(std::string bucketname) {
		IMap<KEYZ, VALZ> map = hazelcastClient->getMap<KEYZ, VALZ>(bucketname);
		std::vector<KEYZ> keys = map.keySet();
		return keys;
	}

	//get a list of all keys within the default bucket
	std::vector<KEYZ> getKeys() {
		return getKeys("zacks");
	}

};
#endif /* DISTRIBUTEDMAP_H_ */
