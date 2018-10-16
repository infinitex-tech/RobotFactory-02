#include "RobotFactory.hpp"

namespace Factory {

    void RobotFactory::create(account_name account, robot newRobot) {
        /**
         * We access the "robot" table as creating an object of type "robotIndex"
         * As parameters we pass code & scope - _self from the parent contract
        */
        robotIndex robots(_self, _self);

        /**
         * We must verify that the robot doesn't exist yet
         * If the robot exist the iterator variable should be equal to robots.end()
        */
        auto iterator = robots.find(newRobot.series_number);
        eosio_assert(iterator == robots.end(), "Robot with this series number already exists");

        /**
         * We add the new robot in the table using emplace
         * The first argument is the payer of the storage which will store the data.
         * In our case, we have set the current account who trigger the action to be the payer. 
         * In some cases, we can set ourselves
        */
        robots.emplace(account, [&](auto& robot) {
            robot.series_number = newRobot.series_number;
            robot.model = newRobot.model;
            robot.operating_system = newRobot.operating_system;
            robot.profession = newRobot.profession;

            /**
             * name{account} - We're getting the string representation of the account
            */
            robot.owner = name{account}.to_string();

            /**
             * now() - Returns the time in seconds from 1970 of the block including this action
            */
            robot.manufactured = now();
        });

        // Execute inline action from another contract
        // action({permission_level}, {contract_deployer}, {contract_action}, {data_to_pass}).send();
        action(permission_level(account, N(active)), N(market), N(forsale), make_tuple(account, 
            newRobot.series_number, 
            newRobot.model, 
            newRobot.manufactured
        )).send();

        // Execute INLINE ACTION from another contract
        // action({permission_level}, {contract_deployer}, {contract_action}, {data_to_pass}).send();
        action(permission_level(account, N(active)), N(messenger), N(printmessage), make_tuple(newRobot.model)).send();

        // Execute DEFERRED ACTION from another contract
        // eosio::transaction tx;
        // tx.actions.emplace_back(permission_level{account, N(active)}, N(messenger), N(printmessage), make_tuple(newRobot.model));
        // tx.delay_sec = 12;
        // tx.send(N(newRobot.model), account); 
    }

    void RobotFactory::update(account_name account, uint64_t series_number, string operating_system) {
        /**
         * Verifies that name exists in the set of provided auths on a action. Throws if not found.
        */
        require_auth(account);

        /**
         * We access the "robot" table as creating an object of type "robotIndex"
         * As parameters we pass code & scope - _self from the parent contract
        */
        robotIndex robots(_self, _self);

        /**
         * We must verify that the robot exist before updating its data
         * If the robot doesn't exist the iterator variable won't be equal to robots.end()
        */
        auto iterator = robots.find(series_number);
        eosio_assert(iterator != robots.end(), "Robot not found");

        /**
         * We're updating the data using modify
        */
        robots.modify(iterator, account, [&](auto& robot) {
            robot.operating_system = operating_system;
        });
    }

    void RobotFactory::getbyid(uint64_t robotId) {
        /**
         * We access the "robot" table as creating an object of type "robotIndex"
         * As parameters we pass code & scope - _self from the parent contract
        */
        robotIndex robots(_self, _self);

        /**
         * We must verify that the robot exist before getting its data
        */
        auto iterator = robots.find(robotId);
        eosio_assert(iterator != robots.end(), "Robot not found");

        /**
         * Getting the robot by its robotId (series number) and printing the data on the console
        */
        auto robot = robots.get(robotId);

        print("Series Number: ", robot.series_number);
        print(" | Model: ", robot.model.c_str());
        print(" | OS: ", robot.operating_system.c_str());
        print(" | Profession: ", robot.profession.c_str());
        print(" | Owner: ", robot.owner.c_str());
        print(" | Manufactured On: ", robot.manufactured);
    }

    void RobotFactory::remove(account_name account, uint64_t robotId) {
        /**
         * Verifies that name exists in the set of provided auths on a action. Throws if not found.
        */
        require_auth(account);

        robotIndex robots(_self, _self);

        auto iterator = robots.find(robotId);
        eosio_assert(iterator != robots.end(), "Robot not found");

        robots.erase(iterator); 
    }
}
