#include "RobotMarketplace.hpp"

namespace Factory {
    void RobotMarketplace::forsale(const account_name account, robot robotForSale) {
        robotIndex robots(_self, _self);

        auto iterator = robots.find(robotForSale.series_number);
        eosio_assert(iterator == robots.end(), "This robot is already selling");

        robots.emplace(account, [&](auto& robot) {
            robot.series_number = robotForSale.series_number;
            robot.model = robotForSale.model;

            /**
             * now() - Returns the time in seconds from 1970 of the block including this action
            */
            robot.manufactured = now();
        });

        /**
         * Getting the saved robot by its series number
        */
        auto savedRobot = robots.get(robotForSale.series_number);
    }
}
