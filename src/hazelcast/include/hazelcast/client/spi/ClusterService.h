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
//
// Created by sancar koyunlu on 5/21/13.
// Copyright (c) 2013 sancar koyunlu. All rights reserved.


#ifndef HAZELCAST_CLUSTER_SERVICE
#define HAZELCAST_CLUSTER_SERVICE

#include "hazelcast/client/connection/ClusterListenerThread.h"
#include "hazelcast/util/Mutex.h"
#include "hazelcast/util/LockGuard.h"
#include <set>

#if  defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
#pragma warning(push)
#pragma warning(disable: 4251) //for dll export
#endif

namespace hazelcast {

    namespace client {
        class MembershipListener;

        class MembershipEvent;

        class InitialMembershipListener;

        class MemberAttributeEvent;

        namespace protocol {
            class UsernamePasswordCredentials;
        }
        namespace impl {
            class ClientRequest;

            class BaseEventHandler;
        }
        namespace spi {
            class ClientContext;

            class HAZELCAST_API ClusterService {
            public:
                friend class connection::ClusterListenerThread;

                ClusterService(ClientContext &clientContext);

                bool start();

                void shutdown();

                std::auto_ptr<Address> getMasterAddress();

                void addMembershipListener(MembershipListener *listener);

                void addMembershipListener(InitialMembershipListener *listener);

                bool removeMembershipListener(MembershipListener *listener);

                bool removeMembershipListener(InitialMembershipListener *listener);

                bool isMemberExists(const Address &address);

                Member getMember(const std::string &uuid);

                Member getMember(Address &address);

                std::vector<Member> getMemberList();

            private:
                ClientContext &clientContext;

                connection::ClusterListenerThread clusterThread;

                std::map<Address, Member, addressComparator > members;
                std::set< MembershipListener *> listeners;
                std::set< InitialMembershipListener *> initialListeners;
                util::Mutex listenerLock;
                util::Mutex membersLock;

                util::AtomicBoolean active;

                void initMembershipListeners();

                //--------- Used by CLUSTER LISTENER THREAD ------------
                void fireMembershipEvent(MembershipEvent &membershipEvent);

                void fireMemberAttributeEvent(MemberAttributeEvent &membershipEvent);

                void setMembers(const std::map<Address, Member, addressComparator > &map);

                boost::shared_ptr<connection::Connection> connectToOne();
                // ------------------------------------------------------

            };

        }
    }
}

#if  defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
#pragma warning(pop)
#endif

#endif //HAZELCAST_CLUSTER_SERVICE

