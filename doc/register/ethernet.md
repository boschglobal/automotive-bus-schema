<!---
  Copyright (c) 2021 for information on the respective copyright owner
  see the NOTICE file and/or the repository https://github.com/boschglobal/automotive-bus-schema

  SPDX-License-Identifier: Apache-2.0
-->

# Automotive Bus Register Interface Ethernet

## Overview

Schema  | Register Interface Ethernet  
:---|:---
&ensp; | [Schema File](../../schemas/register/ethernet.fbs)
MIME Type  | application/x-automotive-bus; interface=register; type=Ethernet;
Data Stream | 4 byte Message Length followed by FlatBuffers Message. Repeating.  
FlatBuffers File Identifier | RIEN


## Modeled BUS Features

### Ethernet Frame

Ethernet Frame  | 68 - 1522 bytes  
--|--
Destination MAC  |  6 bytes
Source MAC  |  6 bytes
VLAN tag  |  4 bytes
Type  |  2 bytes
Data  |  42 - 1497 bytes (standard Ethernet payload)
CRC  |  4  bytes
