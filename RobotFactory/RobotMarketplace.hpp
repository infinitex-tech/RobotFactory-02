#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <string>

namespace Factory {
    using namespace eosio;
    using std::string;

    class RobotMarketplace : public contract {
        using contract::contract;

        public:

            RobotMarketplace(account_name self):contract(self) {}

            //@abi table robot i64
            struct robot {
                uint64_t series_number;
                string model;
                uint32_t manufactured;

                uint64_t primary_key() const { return series_number; }

                /**
                 * The EOSLIB_SERIALIZE macro provides serialize and deserialize methods so that actions can be passed back 
                 * and forth between the contracts and the nodeos system
                */
                EOSLIB_SERIALIZE(robot, (series_number)(model)(manufactured))
            };

            typedef multi_index<N(robot), robot> robotIndex;

            //@abi action
            void forsale(const account_name account, robot robotForSale);
    };

    EOSIO_ABI(RobotMarketplace, (forsale));
}
