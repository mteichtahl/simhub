```
const libconfig::Setting *simConfig = config.getSimulatorConfig();

std::string ip = simConfig->lookup("ipAddress");

Source el("element", "desc");

Attribute attrFloat;
attrFloat._name = "attrFloat";
attrFloat._description = "lkfjdslfjkds";
attrFloat._type = FLOAT_ATTRIBUTE;
attrFloat.setValue<float>(1.223);

Attribute attrInt;
attrInt._name = "attrInt";
attrInt._description = "lkfjdslfjkds";
attrInt._type = INT_ATTRIBUTE;
attrInt.setValue<int>(1);

el.addAttribute(attrFloat);
el.addAttribute(attrInt);

Attribute atINT = el.getAttribute("attrInt");
Attribute atFLOAT = el.getAttribute("attrFloat");

printf("atINT int ----> %i\n", atINT.getValue<int>());
printf("atINT string ----> %s\n", atINT.getValueToString<int>().c_str());
printf("atINT ----> %s\n", atINT.timestampString().c_str());

printf("atFLOAT float ----> %0.5f\n", atFLOAT.getValue<float>());
printf("atFLOAT string ----> %s\n", atFLOAT.getValueToString<float>().c_str());
printf("atFLOAT ----> %s\n", atFLOAT.timestampString().c_str());
```