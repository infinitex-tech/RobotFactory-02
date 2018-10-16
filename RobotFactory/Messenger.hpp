#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <string>

namespace Factory {
    using namespace eosio;
    using std::string;

    /**
     * The Message class inherits the "contract" smart contract and use its constructor (using contract::contract)
    */
    class Messenger : public contract {
        using contract::contract;

        public:
            
            /**
             * The "Message" constructor use the base constructor of "contract" class
            */
            Messenger(account_name self):contract(self) {}

            //@abi action
            void printmessage(string& message);
    };

    /**
     * EOSIO_ABI encapsulate the logic of the apply method. apply is the action handler, it listens to all incoming actions 
     * and reacts according to the specifications within the function
    */
    EOSIO_ABI(Messenger, (printmessage));
}
