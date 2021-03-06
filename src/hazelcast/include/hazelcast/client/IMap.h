/*
 * Copyright (c) 2008-2015, Hazelcast, Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef HAZELCAST_IMAP
#define HAZELCAST_IMAP

#include "hazelcast/client/proxy/IMapImpl.h"
#include "hazelcast/client/map/AddInterceptorRequest.h"
#include "hazelcast/client/impl/EntryEventHandler.h"
#include "hazelcast/client/EntryListener.h"
#include "hazelcast/client/EntryView.h"
#include "hazelcast/client/map/ExecuteOnKeyRequest.h"
#include "hazelcast/client/map/ExecuteOnAllKeysRequest.h"
#include "hazelcast/client/impl/MapEntrySet.h"
#include <string>
#include <map>
#include <set>
#include <vector>
#include <stdexcept>
#include <climits>

#if  defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
#pragma warning(push)
#pragma warning(disable: 4251) //for dll export
#endif

namespace hazelcast {
    namespace client {

        /**
        * Concurrent, distributed, observable and queryable map client.
        *
        * Notice that this class have a private constructor.
        * You can access get an IMap in the following way
        *
        *      ClientConfig clientConfig;
        *      HazelcastClient client(clientConfig);
        *      IMap<int,std::string> imap = client.getMap<int,std::string>("aKey");
        *
        * @param <K> key
        * @param <V> value
        */
        template<typename K, typename V>
        class IMap : public proxy::IMapImpl {
            friend class HazelcastClient;

        public:

            /**
            * check if this map contains key.
            * @param key
            * @return true if contains, false otherwise
            * @throws IClassCastException if the type of the specified element is incompatible with the server side.
            */
            bool containsKey(const K& key) {
                return proxy::IMapImpl::containsKey(toData(key));
            };

            /**
            * check if this map contains value.
            * @param value
            * @return true if contains, false otherwise
            * @throws IClassCastException if the type of the specified element is incompatible with the server side.
            */
            bool containsValue(const V& value) {
                return proxy::IMapImpl::containsValue(toData(value));
            };

            /**
            * get the value.
            * @param key
            * @return value value in shared_ptr, if there is no mapping for key
            * then return NULL in shared_ptr.
            * @throws IClassCastException if the type of the specified element is incompatible with the server side.
            */
            boost::shared_ptr<V> get(const K& key) {
                return toObject<V>(proxy::IMapImpl::get(toData(key)));
            };

            /**
            * put new entry into map.
            * @param key
            * @param value
            * @return the previous value in shared_ptr, if there is no mapping for key
            * @throws IClassCastException if the type of the specified elements are incompatible with the server side.
            * then returns NULL in shared_ptr.
            */
            boost::shared_ptr<V> put(const K& key, const V& value) {
                return toObject<V>(proxy::IMapImpl::put(toData(key), toData(value)));
            };

            /**
            * remove entry form map
            * @param key
            * @return the previous value in shared_ptr, if there is no mapping for key
            * then returns NULL in shared_ptr.
            * @throws IClassCastException if the type of the specified element is incompatible with the server side.
            */
            boost::shared_ptr<V> remove(const K& key) {
                return toObject<V>(proxy::IMapImpl::remove(toData(key)));
            };

            /**
            * removes entry from map if there is an entry with same key and value.
            * @param key
            * @param value
            * @return true if remove is successful false otherwise
            * @throws IClassCastException if the type of the specified element is incompatible with the server side.
            */
            bool remove(const K& key, const V& value) {
                return proxy::IMapImpl::remove(toData(key), toData(value));
            };

            /**
            * removes entry from map.
            * Does not return anything.
            * @param key The key of the map entry to remove.
            * @throws IClassCastException if the type of the specified element is incompatible with the server side.
            */
            void deleteEntry(const K& key) {
                proxy::IMapImpl::deleteEntry(toData(key));
            };

            /**
            * If this map has a MapStore this method flushes
            * all the local dirty entries by calling MapStore.storeAll() and/or MapStore.deleteAll()
            */
            void flush() {
                proxy::IMapImpl::flush();
            };

            /**
            * Tries to remove the entry with the given key from this map
            * within specified timeout value. If the key is already locked by another
            * thread and/or member, then this operation will wait timeout
            * amount for acquiring the lock.
            *
            * @param key      key of the entry
            * @param timeoutInMillis  maximum time in milliseconds to wait for acquiring the lock
            *                 for the key
            */
            bool tryRemove(const K& key, long timeoutInMillis) {
                return proxy::IMapImpl::tryRemove(toData(key), timeoutInMillis);
            };

            /**
            * Tries to put the given key, value into this map within specified
            * timeout value. If this method returns false, it means that
            * the caller thread couldn't acquire the lock for the key within
            * timeout duration, thus put operation is not successful.
            *
            * @param key      key of the entry
            * @param value    value of the entry
            * @param timeoutInMillis  maximum time to wait in milliseconds
            * @return <tt>true</tt> if the put is successful, <tt>false</tt>
            *         otherwise.
            */
            bool tryPut(const K& key, const V& value, long timeoutInMillis) {
                return proxy::IMapImpl::tryPut(toData(key), toData(value), timeoutInMillis);
            };

            /**
            * Puts an entry into this map with a given ttl (time to live) value.
            * Entry will expire and get evicted after the ttl. If ttl is 0, then
            * the entry lives forever.
            *
            * @param key              key of the entry
            * @param value            value of the entry
            * @param ttlInMillis      maximum time for this entry to stay in the map in milliseconds,0 means infinite.
            * @return the previous value in shared_ptr, if there is no mapping for key
            * then returns NULL in shared_ptr.
            */
            boost::shared_ptr<V> put(const K& key, const V& value, long ttlInMillis) {
                return toObject<V>(proxy::IMapImpl::put(toData(key), toData(value), ttlInMillis));
            };

            /**
            * Same as put(K, V, long, TimeUnit) but MapStore, if defined,
            * will not be called to store/persist the entry.  If ttl is 0, then
            * the entry lives forever.
            *
            * @param key          key of the entry
            * @param value        value of the entry
            * @param ttlInMillis  maximum time for this entry to stay in the map in milliseconds, 0 means infinite.
            */
            void putTransient(const K& key, const V& value, long ttlInMillis) {
                proxy::IMapImpl::putTransient(toData(key), toData(value), ttlInMillis);
            };

            /**
            * Puts an entry into this map, if the specified key is not already associated with a value.
            *
            * @param key key with which the specified value is to be associated
            * @param value
            * @return the previous value in shared_ptr, if there is no mapping for key
            * then returns NULL in shared_ptr.
            */
            boost::shared_ptr<V> putIfAbsent(const K& key, const V& value) {
                return putIfAbsent(key, value, -1);
            }

            /**
            * Puts an entry into this map with a given ttl (time to live) value
            * if the specified key is not already associated with a value.
            * Entry will expire and get evicted after the ttl.
            *
            * @param key            key of the entry
            * @param value          value of the entry
            * @param ttlInMillis    maximum time in milliseconds for this entry to stay in the map
            * @return the previous value of the entry, if there is no mapping for key
            * then returns NULL in shared_ptr.
            */
            boost::shared_ptr<V> putIfAbsent(const K& key, const V& value, long ttlInMillis) {
                return toObject<V>(proxy::IMapImpl::putIfAbsent(toData(key), toData(value), ttlInMillis));
            }

            /**
            * Replaces the entry for a key only if currently mapped to a given value.
            * @param key key with which the specified value is associated
            * @param oldValue value expected to be associated with the specified key
            * @param newValue
            * @return <tt>true</tt> if the value was replaced
            */
            bool replace(const K& key, const V& oldValue, const V& newValue) {
                return proxy::IMapImpl::replace(toData(key), toData(oldValue), toData(newValue));
            };

            /**
            * Replaces the entry for a key only if currently mapped to some value.
            * @param key key with which the specified value is associated
            * @param value
            * @return the previous value of the entry, if there is no mapping for key
            * then returns NULL in shared_ptr.
            */
            boost::shared_ptr<V> replace(const K& key, const V& value) {
                return toObject<V>(proxy::IMapImpl::replace(toData(key), toData(value)));
            };

            /**
            * Puts an entry into this map.
            * Similar to put operation except that set
            * doesn't return the old value which is more efficient.
            * @param key key with which the specified value is associated
            * @param value
            * @param ttl maximum time in milliseconds for this entry to stay in the map
            0 means infinite.
            */
            void set(const K& key, const V& value, long ttl) {
                proxy::IMapImpl::set(toData(key), toData(value), ttl);
            };

            /**
            * Acquires the lock for the specified key.
            * <p>If the lock is not available then
            * the current thread becomes disabled for thread scheduling
            * purposes and lies dormant until the lock has been acquired.
            *
            * Scope of the lock is this map only.
            * Acquired lock is only for the key in this map.
            *
            * Locks are re-entrant so if the key is locked N times then
            * it should be unlocked N times before another thread can acquire it.
            *
            * @param key key to lock.
            */
            void lock(const K& key) {
                proxy::IMapImpl::lock(toData(key));
            };

            /**
            * Acquires the lock for the specified key for the specified lease time.
            * <p>After lease time, lock will be released..
            *
            * <p>If the lock is not available then
            * the current thread becomes disabled for thread scheduling
            * purposes and lies dormant until the lock has been acquired.
            *
            * Scope of the lock is this map only.
            * Acquired lock is only for the key in this map.
            *
            * Locks are re-entrant so if the key is locked N times then
            * it should be unlocked N times before another thread can acquire it.
            *
            *
            * @param key key to lock.
            * @param leaseTime time in milliseconds to wait before releasing the lock.
            */
            void lock(const K& key, long leaseTime) {
                proxy::IMapImpl::lock(toData(key), leaseTime);
            };

            /**
            * Checks the lock for the specified key.
            * <p>If the lock is acquired then returns true, else false.
            *
            *
            * @param key key to lock to be checked.
            * @return <tt>true</tt> if lock is acquired, <tt>false</tt> otherwise.
            */
            bool isLocked(const K& key) {
                return proxy::IMapImpl::isLocked(toData(key));
            };

            /**
            * Tries to acquire the lock for the specified key.
            * <p>If the lock is not available then the current thread
            * doesn't wait and returns false immediately.
            *
            *
            * @param key key to lock.
            * @return <tt>true</tt> if lock is acquired, <tt>false</tt> otherwise.
            */
            bool tryLock(const K& key) {
                return tryLock(key, 0);
            };

            /**
            * Tries to acquire the lock for the specified key.
            * <p>If the lock is not available then
            * the current thread becomes disabled for thread scheduling
            * purposes and lies dormant until one of two things happens:
            * <ul>
            * <li>The lock is acquired by the current thread; or
            * <li>The specified waiting time elapses
            * </ul>
            *
            *
            * @param key      key to lock in this map
            * @param timeInMillis     maximum time in milliseconds to wait for the lock
            * @return <tt>true</tt> if the lock was acquired and <tt>false</tt>
            *         if the waiting time elapsed before the lock was acquired.
            */
            bool tryLock(const K& key, long timeInMillis) {
                return proxy::IMapImpl::tryLock(toData(key), timeInMillis);
            };

            /**
            * Releases the lock for the specified key. It never blocks and
            * returns immediately.
            *
            * <p>If the current thread is the holder of this lock then the hold
            * count is decremented.  If the hold count is now zero then the lock
            * is released.  If the current thread is not the holder of this
            * lock then IllegalMonitorStateException is thrown.
            *
            *
            * @param key key to lock.
            * @throws IllegalMonitorStateException if the current thread does not hold this lock MTODO
            */
            void unlock(const K& key) {
                proxy::IMapImpl::unlock(toData(key));
            };

            /**
            * Releases the lock for the specified key regardless of the lock owner.
            * It always successfully unlocks the key, never blocks
            * and returns immediately.
            *
            *
            * @param key key to lock.
            */
            void forceUnlock(const K& key) {
                proxy::IMapImpl::forceUnlock(toData(key));
            };

            /**
            * Adds an interceptor for this map. Added interceptor will intercept operations
            * and execute user defined methods and will cancel operations if user defined method throw exception.
            *
            *
            * Interceptor should extend either Portable or IdentifiedSerializable.
            * Notice that map interceptor runs on the nodes. Because of that same class should be implemented in java side
            * with same classId and factoryId.
            * @param interceptor map interceptor
            * @return id of registered interceptor
            */
            template<typename MapInterceptor>
            std::string addInterceptor(MapInterceptor& interceptor) {
                map::AddInterceptorRequest<MapInterceptor> *request = new map::AddInterceptorRequest<MapInterceptor>(getName(), interceptor);
                serialization::pimpl::Data data = invoke(request);
                boost::shared_ptr<std::string> response = toObject(data);
                return *response;
            }

            /**
            * Removes the given interceptor for this map. So it will not intercept operations anymore.
            *
            *
            * @param id registration id of map interceptor
            */
            void removeInterceptor(const std::string& id) {
                proxy::IMapImpl::removeInterceptor(id);
            }

            /**
            * Adds an entry listener for this map.
            *
            * Warning 1: If listener should do a time consuming operation, off-load the operation to another thread.
            * otherwise it will slow down the system.
            *
            * Warning 2: Do not make a call to hazelcast. It can cause deadlock.
            *
            * @param listener     entry listener
            * @param includeValue <tt>true</tt> if <tt>EntryEvent</tt> should
            *                     contain the value.
            *
            * @return registrationId of added listener that can be used to remove the entry listener.
            */
            std::string addEntryListener(EntryListener<K, V>& listener, bool includeValue) {
                impl::EntryEventHandler<K, V> *entryEventHandler = new impl::EntryEventHandler<K, V>(getName(), context->getClusterService(), context->getSerializationService(), listener, includeValue);
                return proxy::IMapImpl::addEntryListener(entryEventHandler, includeValue);
            };

            /**
            * Removes the specified entry listener
            * Returns silently if there is no such listener added before.
            *
            *
            * @param registrationId id of registered listener
            *
            * @return true if registration is removed, false otherwise
            */
            bool removeEntryListener(const std::string& registrationId) {
                return proxy::IMapImpl::removeEntryListener(registrationId);
            };


            /**
            * Adds the specified entry listener for the specified key.
            *
            * Warning 1: If listener should do a time consuming operation, off-load the operation to another thread.
            * otherwise it will slow down the system.
            *
            * Warning 2: Do not make a call to hazelcast. It can cause deadlock.
            *
            * @param listener     entry listener
            * @param key          key to listen
            * @param includeValue <tt>true</tt> if <tt>EntryEvent</tt> should
            *                     contain the value.
            */
            std::string addEntryListener(EntryListener<K, V>& listener, const K& key, bool includeValue) {
                serialization::pimpl::Data keyData = toData(key);
                impl::EntryEventHandler<K, V> *entryEventHandler = new impl::EntryEventHandler<K, V>(getName(), context->getClusterService(), context->getSerializationService(), listener, includeValue);
                return proxy::IMapImpl::addEntryListener(entryEventHandler, keyData, includeValue);
            };

            /**
            * Returns the <tt>EntryView</tt> for the specified key.
            *
            *
            * @param key key of the entry
            * @return <tt>EntryView</tt> of the specified key
            * @see EntryView
            */
            EntryView<K, V> getEntryView(const K& key) {
                serialization::pimpl::Data keyData = toData(key);
                map::DataEntryView dataEntryView = proxy::IMapImpl::getEntryView(keyData);
                boost::shared_ptr<V> v = toObject<V>(dataEntryView.value);
                EntryView<K, V> view(key, *v, dataEntryView);
                return view;
            };

            /**
            * Evicts the specified key from this map. If
            * a <tt>MapStore</tt> defined for this map, then the entry is not
            * deleted from the underlying <tt>MapStore</tt>, evict only removes
            * the entry from the memory.
            *
            *
            * @param key key to evict
            * @return <tt>true</tt> if the key is evicted, <tt>false</tt> otherwise.
            */
            bool evict(const K& key) {
                return proxy::IMapImpl::evict(toData(key));
            };

            /**
            * Evicts all keys from this map except locked ones.
            * <p/>
            * If a <tt>MapStore</tt> is defined for this map, deleteAll is <strong>not</strong> called by this method.
            * If you do want to deleteAll to be called use the #clear() method.
            * <p/>
            * The EVICT_ALL event is fired for any registered listeners.
            * See EntryListener#mapEvicted(MapEvent)}.
            *
            * @see #clear()
            */
            void evictAll() {
                proxy::IMapImpl::evictAll();
            };


            /**
            * Returns a vector clone of the keys contained in this map.
            * The vector is <b>NOT</b> backed by the map,
            * so changes to the map are <b>NOT</b> reflected in the vector, and vice-versa.
            *
            * @return a vector clone of the keys contained in this map
            */
            std::vector<K> keySet() {
                return keySet(NO_PREDICATE);
            };

            /**
            * Returns the entries for the given keys.
            *
            * @param keys keys to get
            * @return map of entries
            */
            std::map<K, V> getAll(const std::set<K>& keys) {
                std::vector<serialization::pimpl::Data> keySet(keys.size());
                int i = 0;
                for (typename std::set<K>::iterator it = keys.begin(); it != keys.end(); ++it) {
                    keySet[i++] = toData(*it);
                }
                std::map<K, V> result;
                std::vector<std::pair<serialization::pimpl::Data, serialization::pimpl::Data> > entrySet = proxy::IMapImpl::getAll(keySet);
                for (std::vector<std::pair<serialization::pimpl::Data, serialization::pimpl::Data> >::const_iterator it = entrySet.begin(); it != entrySet.end(); ++it) {
                    boost::shared_ptr<K> key = toObject<K>(it->first);
                    boost::shared_ptr<V> value = toObject<V>(it->second);
                    result[*key] = *value;
                }
                return result;
            };

            /**
            * Returns a vector clone of the values contained in this map.
            * The vector is <b>NOT</b> backed by the map,
            * so changes to the map are <b>NOT</b> reflected in the collection, and vice-versa.
            *
            * @return a vector clone of the values contained in this map
            */
            std::vector<V> values() {
                return values(NO_PREDICATE);
            };

            /**
            * Returns a std::vector< std::pair<K, V> > clone of the mappings contained in this map.
            * The vector is <b>NOT</b> backed by the map,
            * so changes to the map are <b>NOT</b> reflected in the set, and vice-versa.
            *
            * @return a vector clone of the keys mappings in this map
            */
            std::vector<std::pair<K, V> > entrySet() {
                return entrySet(NO_PREDICATE);
            };


            /**
            * Queries the map based on the specified sql predicate and
            * returns the keys of matching entries.
            *
            * Specified predicate runs on all members in parallel.
            *
            *
            * @param sql string query criteria
            * @return result key set of the query
            */
            std::vector<K> keySet(const std::string& sql) {
                std::vector<std::pair<serialization::pimpl::Data, serialization::pimpl::Data> > dataResult = proxy::IMapImpl::keySet(sql);
                int size = dataResult.size();
                std::vector<K> keySet(size);
                for (int i = 0; i < size; ++i) {
                    boost::shared_ptr<K> key = toObject<K>(dataResult[i].first);
                    keySet[i] = *key;
                }
                return keySet;
            };

            /**
            * Queries the map based on the specified sql predicate and
            * returns the matching entries.
            *
            * Specified predicate runs on all members in parallel.
            *
            *
            * @param sql string query criteria
            * @return result entry vector of the query
            */
            std::vector<std::pair<K, V> > entrySet(const std::string& sql) {
                std::vector<std::pair<serialization::pimpl::Data, serialization::pimpl::Data> > dataResult = proxy::IMapImpl::entrySet(sql);
                int size = dataResult.size();
                std::vector<std::pair<K, V> > keySet(size);
                for (int i = 0; i < size; ++i) {
                    boost::shared_ptr<K> key = toObject<K>(dataResult[i].first);
                    boost::shared_ptr<V> value = toObject<V>(dataResult[i].second);
                    keySet[i] = std::make_pair(*key, *value);
                }
                return keySet;
            };

            /**
            * Queries the map based on the specified predicate and
            * returns the values of matching entries.
            *
            * Specified predicate runs on all members in parallel.
            *
            *
            * @param sql predicate query string
            * @return result value vector of the query
            */
            std::vector<V> values(const std::string& sql) {
                std::vector<std::pair<serialization::pimpl::Data, serialization::pimpl::Data> > dataResult = proxy::IMapImpl::values(sql);
                int size = dataResult.size();
                std::vector<V> keySet(size);
                for (int i = 0; i < size; ++i) {
                    boost::shared_ptr<V> value = toObject<V>(dataResult[i].second);
                    keySet[i] = *value;
                }
                return keySet;
            };

            /**
            * Adds an index to this map for the specified entries so
            * that queries can run faster.
            *
            * Let's say your map values are Employee objects.
            *
            *   class Employee : public serialization::Portable {
            *       //...
            *       private:
            *          bool active;
            *          int age;
            *          std::string name;
            *
            *   }
            *
            *
            * If you are querying your values mostly based on age and active then
            * you should consider indexing these fields.
            *
            *   IMap<std::string, Employee > imap = hazelcastInstance.getMap<std::string, Employee >("employees");
            *   imap.addIndex("age", true);        // ordered, since we have ranged queries for this field
            *   imap.addIndex("active", false);    // not ordered, because boolean field cannot have range
            *
            *
            * In the server side, Index  should either have a getter method or be public.
            * You should also make sure to add the indexes before adding
            * entries to this map.
            *
            * @param attribute attribute of value
            * @param ordered   <tt>true</tt> if index should be ordered,
            *                  <tt>false</tt> otherwise.
            */
            void addIndex(const std::string& attribute, bool ordered) {
                proxy::IMapImpl::addIndex(attribute, ordered);
            };

            /**
            * Applies the user defined EntryProcessor to the entry mapped by the key.
            * Returns the the ResultType which is result of the process() method of EntryProcessor.
            *
            * EntryProcessor should extend either Portable or IdentifiedSerializable.
            * Notice that map EntryProcessor runs on the nodes. Because of that, same class should be implemented in java side
            * with same classId and factoryId.
            *
            * @tparam EntryProcessor type of entry processor class
            * @tparam ResultType that entry processor will return
            * @param entryProcessor that will be applied
            * @param key of entry that entryProcessor will be applied on
            * @return result of entry process.
            */
            template<typename ResultType, typename EntryProcessor>
            ResultType executeOnKey(const K& key, EntryProcessor& entryProcessor) {
                serialization::pimpl::Data keyData = toData(key);
                int partitionId = getPartitionId(keyData);
                map::ExecuteOnKeyRequest<EntryProcessor> *request = new map::ExecuteOnKeyRequest<EntryProcessor>(getName(), entryProcessor, keyData);
                serialization::pimpl::Data data = invoke(request, partitionId);
                return *(toObject<ResultType>(data));
            }

            /**
            * Applies the user defined EntryProcessor to the all entries in the map.
            * Returns the results mapped by each key in the map.
            *
            *
            * EntryProcessor should extend either Portable or IdentifiedSerializable.
            * Notice that map EntryProcessor runs on the nodes. Because of that, same class should be implemented in java side
            * with same classId and factoryId.
            *
            * @tparam ResultType that entry processor will return
            * @tparam EntryProcessor type of entry processor class
            * @param entryProcessor that will be applied
            */
            template<typename ResultType, typename EntryProcessor>
            std::map<K, ResultType> executeOnEntries(EntryProcessor& entryProcessor) {
                map::ExecuteOnAllKeysRequest<EntryProcessor> *request = new map::ExecuteOnAllKeysRequest<EntryProcessor>(getName(), entryProcessor);
                serialization::pimpl::Data data = invoke(request);
                boost::shared_ptr<map::MapEntrySet> mapEntrySet = toObject<map::MapEntrySet>(data);
                std::map<K, ResultType> result;
                const std::vector<std::pair<serialization::pimpl::Data, serialization::pimpl::Data> >& entrySet = mapEntrySet->getEntrySet();
                for (std::vector<std::pair<serialization::pimpl::Data, serialization::pimpl::Data> >::const_iterator it = entrySet.begin(); it != entrySet.end(); ++it) {
                    K key = toObject<K>(it->first);
                    ResultType resultType = toObject<ResultType>(it->second);
                    result[key] = resultType;
                }
                return result;
            }

            /**
            * Puts an entry into this map.
            * Similar to put operation except that set
            * doesn't return the old value which is more efficient.
            * @param key
            * @param value
            */
            void set(const K& key, const V& value) {
                set(key, value, -1);
            };

            /**
            * Returns the number of key-value mappings in this map.  If the
            * map contains more than <tt>Integer.MAX_VALUE</tt> elements, returns
            * <tt>Integer.MAX_VALUE</tt>.
            *
            * @return the number of key-value mappings in this map
            */
            int size() {
                return proxy::IMapImpl::size();
            };

            /**
            * Returns <tt>true</tt> if this map contains no key-value mappings.
            *
            * @return <tt>true</tt> if this map contains no key-value mappings
            */
            bool isEmpty() {
                return proxy::IMapImpl::isEmpty();
            };


            /**
            * Copies all of the mappings from the specified map to this map
            * (optional operation).  The effect of this call is equivalent to that
            * of calling put(k, v) on this map once
            * for each mapping from key <tt>k</tt> to value <tt>v</tt> in the
            * specified map.  The behavior of this operation is undefined if the
            * specified map is modified while the operation is in progress.
            *
            * @param m mappings to be stored in this map
            */
            void putAll(const std::map<K, V>& entries) {
                return proxy::IMapImpl::putAll(toDataEntriesSet(entries));
            }

            /**
            * Removes all of the mappings from this map (optional operation).
            * The map will be empty after this call returns.
            */
            void clear() {
                proxy::IMapImpl::clear();
            }

        private:
            IMap(const std::string& instanceName, spi::ClientContext *context)
            : proxy::IMapImpl(instanceName, context) {

            }

        };
    }
}

#if  defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
#pragma warning(pop)
#endif

#endif /* HAZELCAST_IMAP */

