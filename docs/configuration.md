# Configuration Manager

## Instatiation of the configuration manager

The configuration manager must be instantiated before it can be used.


```
CConfigManager config(std::string filename);
```

Where ```filename``` is the name of the config (filename.cfg) that you wish load.

### Example implmentation

```
#include "configmanager.h"

CConfigManager config("config/config.cfg");
```
***Note:*** There is no return from the constructor.

Once the configuration manager is created, you may call the initialisation method. This will validate the configuration file and load it such that the various parts of the configuration file may be accessed.

### Accessing the configuration

By default the ```name``` and ```version``` of the configuartion file are accessable via the ```std::string CConfigManager::name()``` and ```std::string CConfigManager::version()``` methods.

#### Simulator configuration

The simulator configuration contains

| Name | Type | Description |
|------|------|------|
|type  | string | Type of simualator |
|ipAddress  | string | IP Address of the simulator |
|port  | int | IP Port of the simualtor |

#### Example

```
simulator = (
    {
      type = "prepared-3d",
      ipAddress= "192.168.2.2",
      port = 8091
    }
  )
```  

```libconfig::Setting *CConfigManager::getSimulatorConfig()```

``` std::string ip = simConfig->lookup("ipAddress");```

