
echo "Generating WASM & ABI for RobotFactory contract"
eosiocpp -o RobotFactory/RobotFactory.wast RobotFactory/RobotFactory.cpp
eosiocpp -g RobotFactory/RobotFactory.abi RobotFactory/RobotFactory.cpp

echo "Generating WASM & ABI for Messenger contract"
eosiocpp -o RobotFactory/Messenger.wast RobotFactory/Messenger.cpp
eosiocpp -g RobotFactory/Messenger.abi RobotFactory/Messenger.cpp

echo "Generating WASM & ABI for RobotMarketplace contract"
eosiocpp -o RobotFactory/RobotMarketplace.wast RobotFactory/RobotMarketplace.cpp
eosiocpp -g RobotFactory/RobotMarketplace.abi RobotFactory/RobotMarketplace.cpp

echo "Deploying the EOS Smart Contracts"

cleos set contract weyland ./RobotFactory RobotFactory/RobotFactory.wast RobotFactory/RobotFactory.abi
cleos set contract messenger ./RobotFactory RobotFactory/Messenger.wast RobotFactory/Messenger.abi
cleos set contract market ./RobotFactory RobotFactory/RobotMarketplace.wast RobotFactory/RobotMarketplace.abi