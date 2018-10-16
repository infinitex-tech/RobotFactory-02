# Robot Factory - Live Demo

### Setup environment (for Mac OS)

  * Clone EOSIO repo recursively

```
git clone https://github.com/eosio/eos --recursive
```

  * Go to the eos folder and run the eosio_build.sh script with the following command
  
```
sh ./eosio_build.sh darwin
```

*Note: It could take quite some time before all the dependencies are installed and then built.*

### Running local testnet:
```
nodeos -e -p eosio --plugin eosio::wallet_api_plugin --plugin eosio::chain_api_plugin --plugin eosio::history_api_plugin --contracts-console --verbose-http-errors
```

### Commands:

1. Creating a wallet

```sh
# cleos wallet create -n {wallet_name}

cleos wallet create -n factory
```

*Note: Don't forget to save your password*

2. Import the eosio private key in the wallet

```sh
cleos wallet import --private-key=5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3 -n factory
```

3. Creating three new accounts

```sh
# cleos create account eosio {new_account_name} {public_OwnerKey} {public_ActiveKey}
# "eosio" is the name of the account who will create the new one

# Used to deploy "RobotFactory" Smart Contract 
cleos create account eosio weyland EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV

# Used to deploy "Messenger" Smart Contract 
cleos create account eosio messenger EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV

# Used to deploy "RobotMarketplace" Smart Contract 
cleos create account eosio market EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV 
```

4. Add permissions for eosio.code

```sh
# Weyland
cleos set account permission weyland active '{"threshold": 1,"keys": [{"key": "EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV","weight": 1}],"accounts": [{"permission":{"actor":"weyland","permission":"eosio.code"},"weight":1}]}' owner -p weyland

# Market
cleos set account permission market active '{"threshold": 1,"keys": [{"key": "EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV","weight": 1}],"accounts": [{"permission":{"actor":"market","permission":"eosio.code"},"weight":1}]}' owner -p market

# Messenger
cleos set account permission messenger active '{"threshold": 1,"keys": [{"key": "EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV","weight": 1}],"accounts": [{"permission":{"actor":"messenger","permission":"eosio.code"},"weight":1}]}' owner -p messenger
```

5. Creating the smart contract

6. Generating the WAST file
   
```sh
eosiocpp -o RobotFactory.wast RobotFactory.cpp
eosiocpp -o Messenger.wast Messenger.cpp
eosiocpp -o RobotMarketplace.wast RobotMarketplace.cpp
```

7. Generating the ABI file

```sh
eosiocpp -g RobotFactory.abi RobotFactory.cpp
eosiocpp -g Messenger.abi Messenger.cpp
eosiocpp -g RobotMarketplace.abi RobotMarketplace.cpp
```

8. Deploying the smart contract

```sh
# cleos set contract {account} {path_to_contract_folder} {path_to_.wast_file} {path_to_.abi_file}
cleos set contract weyland . RobotFactory.wast RobotFactory.abi
cleos set contract messenger . Messenger.wast Messenger.abi
cleos set contract market . RobotMarketplace.wast RobotMarketplace.abi
```

9. Creating new robot

```sh
# cleos push action {account} {action_name} '{data}' -p {account}
cleos push action weyland create '{"account":"weyland","newRobot":{"series_number":14001992,"model":"A330","operating_system":"DX42","profession":"engineer","owner":"","manufactured":0}}' -p weyland
```

### Example data for robots:

| Series Number | Model |  OS  |  Profession  |
|:-------------:|:-----:|:----:|:------------:|
|    14001992   |  A330 | DX42 |   engineer   |
|    14001993   |  A720 | DX49 |  babysitter  |
|    14001994   |  U835 | D33R |    farmer    |
|    14001995   |  XS33 | DZ4S | neurosurgeon |
|    14001996   |  XS33 | X99A |    cashier   |
